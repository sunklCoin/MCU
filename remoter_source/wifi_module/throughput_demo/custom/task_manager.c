// Copyright (c) Qualcomm Atheros, Inc.
// All rights reserved.
// Redistribution and use in source and binary forms, with or without modification, are permitted (subject to
// the limitations in the disclaimer below) provided that the following conditions are met:
//
// � Redistributions of source code must retain the above copyright notice, this list of conditions and the
//   following disclaimer.
// � Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
//   following disclaimer in the documentation and/or other materials provided with the distribution.
// � Neither the name of nor the names of its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE. THIS SOFTWARE IS
// PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//==============================================================================
// Author(s): ="Atheros"
//==============================================================================
/*
* $FileName: Task_Manager.c$
* $Version : $
* $Date    : May-20-2011$
*
* Comments: Handles all task management functions including mutithreaded support. 
*
*   
*
*END************************************************************************/
//by colin
#if MQX_RTOS || MQX_LITE
#include <mqx.h>
#include <mutex.h>
#include <lwevent.h>
#endif
#include "main.h"
#include <string.h>
#include <stdlib.h>

#include "throughput.h"

#if READ_HOST_MEMORY
extern int_32 __END_BSS;
extern int_32 __START_BSS;
extern int_32 __END_TEXT;
extern int_32 __START_TEXT;
extern int_32 __END_DATA;
extern int_32 __START_DATA;
extern int_32 __END_RODATA;
extern int_32 __START_RODATA;
#endif

/*************************** GLOBALS **************************/
//by colin
/*MUTEX_STRUCT task_mutex, mutex_tskcnt;
LWEVENT_STRUCT task_event, task_event1;*/
A_MUTEX_T task_mutex, mutex_tskcnt;
QOSAL_EVENT_STRUCT task_event, task_event1;
extern WMI_POWER_MODE power_mode;
int_32 task_argc;
char_ptr task_argv[MAX_ARGC];
char arg[MAX_ARGC][MAX_STRLEN];
uint_8 hvac_init = 0, task_counter = 0;
uint_8 wps_in_progress = 0;
uint_8 number_streams = 0; 			//Counter to control number of streams




/*************************** Function Declarations **************************/

int_32 worker_cmd_handler(int_32 argc, char_ptr argv[] );
int_32 worker_cmd_quit(int_32 argc, char_ptr argv[] );
static void WakeWorkerTask(void);
#if ENABLE_P2P_MODE
extern A_UINT32 task2_msec;
extern A_INT32 p2p_callback(A_UINT8 evt_flag);
#endif

/************************************************************************
* NAME: incrementTaskCount
*
* DESCRIPTION: Increment task counter when a new command is handled
************************************************************************/
static void incrementTaskCount()
{
	qosal_mutex_acquire(&mutex_tskcnt, 0);
	task_counter ++;
	qosal_mutex_release(&mutex_tskcnt);
}


/************************************************************************
* NAME: decrementTaskCount
*
* DESCRIPTION: Decrement task counter when command handling is over
************************************************************************/
static void decrementTaskCount()
{
	qosal_mutex_acquire(&mutex_tskcnt, 0);
	if(task_counter != 0)
		task_counter--;
	else
		printf("Error: decrementing task counter: counter already 0\n");
	
	qosal_mutex_release(&mutex_tskcnt);
}



/************************************************************************
* NAME: DoPeriodic
*
* DESCRIPTION: Periodic WPS query. 
************************************************************************/
static void DoPeriodic(void)
{
#if USE_ATH_CHANGES
	wps_query(0);
#endif
#if ENABLE_P2P_MODE				
	p2p_callback(1);
#endif	
}


/************************************************************************
* NAME: worker_cmd_quit
*
* DESCRIPTION: Called when user enters "benchquit" 
************************************************************************/
int_32 worker_cmd_quit(int_32 argc, char_ptr argv[] )
{
	bench_quit = 1;
    return 0;
}


/************************************************************************
* NAME: worker_cmd_handler
*
* DESCRIPTION: Handles incoming commands from Shell task 
************************************************************************/
int_32 worker_cmd_handler(int_32 argc, char_ptr argv[] )
{
	int_32 str_len;
	int_32 ret=0;
	/* for now we don't use a queue because worker commands are coming from the user 
	 * shell and if commands start to back up then we just discard that most recent
	 */
	if(hvac_init){
		qosal_mutex_acquire(&task_mutex, 0);
		
		if(task_counter < MAX_TASKS_ALLOWED){
			do{
				if(argc > MAX_ARGC){
					printf("Command discarded; too many arguments %d < %d\n", MAX_ARGC, argc);
					ret = 1;
					break;
				}
				
				task_argc = argc;
				while(argc){
					str_len = strlen(argv[task_argc-argc])+1;
					
					if(str_len > MAX_STRLEN){
						printf("Command discarded; argument too long %d < %d\n", MAX_STRLEN, str_len);
						break;
					}
					
					memcpy(task_argv[task_argc-argc], argv[task_argc - argc], str_len);
					
					argc--;
				}
				
				if(argc){
					ret = 1;
					break;
				}
			
				WakeWorkerTask();
				
			}while(0);	
		}
		else
		{
			printf("Only 2 simultaneous commands allowed\n");
			ret = 1;
		}
		qosal_mutex_release(&task_mutex);
	}else{
		printf("worker thread not yet initialized\n");
	}
	
	return ret;
}



/************************************************************************
* NAME: DoWork
*
* DESCRIPTION: Calls functions corresponding to shell command. 
************************************************************************/
static void DoWork(void)
{
	if(strcmp(task_argv[0], "benchtx") == 0){
		
		if(wifi_connected_flag)
		{
			if(number_streams < MAX_STREAMS_ALLOWED)
			{
				number_streams++;
				tx_command_parser(task_argc, task_argv);
				number_streams--;
			}
			else
			{
				printf("ERROR: Only 2 simultaneous traffic streams allowed\n");
			}
		}			
		else
			printf("ERROR: No WiFi connection available, please connect to an Access Point\n");
		
	}else if(strcmp(task_argv[0], "benchrx") == 0){
		if(wifi_connected_flag)	
		{
			if(number_streams < MAX_STREAMS_ALLOWED)
			{
				number_streams++;
				rx_command_parser(task_argc, task_argv);
				number_streams--;
			}	
			else
			{
				printf("ERROR: Only 2 simultaneous traffic streams allowed\n");
			}
		}
		else
			printf("No WiFi connection available, please connect to an Access Point\n");
		
	}
#if READ_HOST_MEMORY        
	else if(strcmp(task_argv[0], "hostmemmap") == 0){
		   printf("text   : %d bytes\n", (int_32)&__END_TEXT - (int_32)&__START_TEXT);
		   printf("bss    : %d bytes\n", (int_32)&__END_BSS - (int_32)&__START_BSS);
		   printf("data   : %d bytes\n", (int_32)&__END_DATA - (int_32)&__START_DATA);
		   printf("rodata : %d bytes\n", (int_32)&__END_RODATA - (int_32)&__START_RODATA);
	}
#endif        
#if (ENABLE_STACK_OFFLOAD && MULTI_SOCKET_SUPPORT)
	else if(strcmp(task_argv[0], "benchrx_multi_socket") == 0){
			if(wifi_connected_flag)	
			{
				rx_command_parser_multi_socket(task_argc, task_argv);
			}
			else
				printf("No WiFi connection available, please connect to an Access Point\n");
		
	}
#endif
#if USE_ATH_CHANGES
	else if(strcmp(task_argv[0], "wmiconfig") == 0){
		wmiconfig_handler(task_argc, task_argv);
	}else if(strcmp(task_argv[0], "iwconfig") == 0){
		wmi_iwconfig(task_argc, task_argv);
	}
#endif	
#if ENABLE_STACK_OFFLOAD 
    else if (strcmp(task_argv[0], "benchmode") == 0)
    {
    	if(number_streams == 0)
    		setBenchMode(task_argc, task_argv);
    	else
    		printf("Cannot change mode while test is running\n");
    }
#if ENABLE_SSL
   else if(strcmp(task_argv[0], "getcert") == 0){
       ssl_get_cert_handler(task_argc, task_argv);
   }
#if ENABLE_HTTPS_SERVER
    else if(strcmp(task_argv[0], "httpss") == 0){
        https_server_handler(task_argc, task_argv);
    }
#endif
#if ENABLE_HTTPS_CLIENT
    else if(strcmp(task_argv[0], "httpsc") == 0){
        https_client_handler(task_argc, task_argv);
    }
#endif
#endif // ENABLE_SSL
#endif // ENABLE_STACK_OFFLOAD
    else{
//        printf("unknown cmd: %s\n", task_argv[0]);
    }
}



/************************************************************************
* NAME: wmiconfig_Task1
*
* DESCRIPTION: Handler for 1st task, waits for Shell task to provide command 
************************************************************************/
void wmiconfig_Task1(uint_32 temp)
{
   	uint_32 flags = 0;

    qosal_create_event(&task_event1);
    qosal_set_event_auto_clear(&task_event1, 1/* autoclear */);
		
	/* block for events from other tasks */
	for(;;){
		switch(qosal_wait_for_event(&task_event1, 0x01, TRUE, 0, MSEC_HEARTBEAT))
		{
		case QOSAL_OK:
			/* check for new work */
			DoWork();
				decrementTaskCount();
			break;
		case QOSAL_ERROR:
			/* perform periodic tasks */
		//	DoPeriodic();
			break;
		default:
			printf("worker task error\n");
			flags = 1;
			break;
		}

	    if(flags == 1){
	    	break;
	    }
	}
	qosal_delete_event(&task_event1);
}



/************************************************************************
* NAME: wmiconfig_Task2
*
* DESCRIPTION: Handler for 2nd task, waits for Shell task to provide command 
************************************************************************/
extern WMI_POWER_MODE power_mode;
void wmiconfig_Task2(uint_32 temp)
{
   	uint_32 flags = 0, i=0;
#if ENABLE_P2P_MODE	
   	int msec = task2_msec;
#endif   	
    qosal_create_event(&task_event);
    qosal_set_event_auto_clear(&task_event, 1/* autoclear */);
      
   	qosal_mutex_init(&task_mutex); //, NULL);
   	qosal_mutex_init(&mutex_tskcnt); //, NULL);
        
        atheros_driver_setup();
        
#if DEMOCFG_ENABLE_RTCS
   	HVAC_initialize_networking();
#endif
        for(i=0 ; i<MAX_ARGC ; i++){
   		task_argv[i] = &arg[i][0];
   	}


	hvac_init = 1;

        qosal_create_event(&task_event);
        qosal_set_event_auto_clear(&task_event, 1/* autoclear */);
		
	/* block for events from other tasks */

	for(;;){
#if ENABLE_P2P_MODE
        switch(qosal_wait_for_event(&task_event, 0x01, TRUE, 0, msec))
#else
		switch(qosal_wait_for_event(&task_event, 0x01, TRUE, MSEC_HEARTBEAT))
#endif
		{
		case QOSAL_OK:
			/* check for new work */
			DoWork();
				decrementTaskCount();
			break;
		case QOSAL_ERROR:
			/* perform periodic tasks */
			DoPeriodic();
			break;
		default:
			printf("worker task error\n");
			flags = 1;
			break;
		}

	    if(flags == 1){
	    	break;
	    }
	}

	qosal_delete_event(&task_event);
}




/************************************************************************
* NAME: WakeWorkerTask
*
* DESCRIPTION: Wakes task on incoming command
************************************************************************/
static void WakeWorkerTask(void)
{
	if(hvac_init){
	
		if(task_counter < MAX_TASKS_ALLOWED)	
		{
			incrementTaskCount();	
			switch(task_counter)
			{
				
				case 1:
				qosal_set_event(&task_event1, 0x01);
				break;
				
				case 2:
				qosal_set_event(&task_event, 0x01);
				break;							
				
				default:
					printf("Invalid task number\n");
			}
			
		}
	}
}





