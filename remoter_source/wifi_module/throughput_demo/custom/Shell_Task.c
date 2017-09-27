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
* $FileName: Shell_Task.c$
* $Version : 3.0.4.0$
* $Date    : Nov-21-2008$
*
* Comments:
*
*   
*
*END************************************************************************/



#include "main.h"
#include "FreeRTOS_CLI.h"
#include "throughput.h"


/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_Task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/

#if 1

static BaseType_t prvShellParamHandler( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );

typedef struct _shell_cmd_ {
	char *parameter;
	int len;
} SHELL_PARAM_STRUCT;
static SHELL_PARAM_STRUCT params[MAX_ARGC] = {0};

typedef struct _shell_cmd_list_ {
	CLI_Command_Definition_t shellCmd;
	int_32 (*shell_callback)(int_32 argc, char_ptr argv[] );
} SHELL_CMD_LIST;

static const SHELL_CMD_LIST shellCmds[] = {
//	{
//		{
//			"exit",
//			"\r\nexit:\r\n exit shell.\r\n",
//			prvShellParamHandler,
//			0
//		}, Shell_exit
//	},
	{
		{
			"benchtx",
			"\r\nbenchtx:\r\n benchtx shell.\r\n",
			prvShellParamHandler,
			-1
		}, worker_cmd_handler
	},
	{
		{
			"benchrx",
			"\r\nbenchrx:\r\n shell benchrx.\r\n",
			prvShellParamHandler,
			-1
		}, worker_cmd_handler
	},
	{
		{
			"benchrx_multi_socket",
			"\r\nbenchrx_multi_socket:\r\n shell benchrx_multi_socket.\r\n",
			prvShellParamHandler,
			-1
		}, worker_cmd_handler
	},
	{
		{
			"benchquit",
			"\r\nbenchquit:\r\n shell benchquit.\r\n",
			prvShellParamHandler,
			-1
		}, worker_cmd_quit
	},
	{
		{
			"benchmode",
			"\r\nbenchmode:\r\n shell benchmode.\r\n",
			prvShellParamHandler,
			-1
		}, worker_cmd_handler
	},
	{
		{
			"perf",
			"\r\nperf:\r\n shell perf.\r\n",
			prvShellParamHandler,
			-1
		}, print_perf
	},
	{
		{
			"ipconfig",
			"\r\nipconfig:\r\n shell ipconfig.\r\n",
			prvShellParamHandler,
			-1
		}, ipconfig_query
	},
	{
		{
			"iwconfig",
			"\r\niwconfig:\r\n shell iwconfig.\r\n",
			prvShellParamHandler,
			-1
		}, worker_cmd_handler
	},
	{
		{
			"wmiconfig",
			"\r\nwmiconfig:\r\n shell wmiconfig.\r\n",
			prvShellParamHandler,
			-1
		}, worker_cmd_handler
	},
	{
		{
			"ping",
			"\r\nping:\r\n shell ping.\r\n",
			prvShellParamHandler,
			-1
		}, wmi_ping
	},
	{
		{
			"ping6",
			"\r\nping6:\r\n shell ping6.\r\n",
			prvShellParamHandler,
			-1
		}, wmi_ping6
	},
	{
		{
			"getcert",
			"\r\ngetcert:\r\n shell getcert.\r\n",
			prvShellParamHandler,
			-1
		}, worker_cmd_handler
	},
	{
		{
			"httpss",
			"\r\nhttpss:\r\n shell httpss.\r\n",
			prvShellParamHandler,
			-1
		}, worker_cmd_handler
	},
	{
		{
			"httpsc",
			"\r\nhttpsc:\r\n shell httpsc.\r\n",
			prvShellParamHandler,
			-1
		}, worker_cmd_handler
	}
};

# if 0
static BaseType_t prvShellParamHandler( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
const char *pcParameter;
BaseType_t xParameterStringLength, xReturn;
static UBaseType_t uxParameterNumber = 0;
//	char (*argv)[MAX_STRLEN];
	char *argv[MAX_ARGC];
	int argc;
	int i;
	int index;

	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) pcCommandString;
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );

	if( uxParameterNumber == 0 )
	{
		/* Obtain the parameter string. */
		pcParameter = FreeRTOS_CLIGetParameter
						(
							pcCommandString,		/* The command string itself. */
							uxParameterNumber,		/* Return the next parameter. */
							&xParameterStringLength	/* Store the parameter string length. */
						);

		/* Sanity check something was returned. */
		configASSERT( pcParameter );

		if (uxParameterNumber < MAX_ARGC) {
			params[uxParameterNumber].len = xParameterStringLength;
			params[uxParameterNumber].parameter = (char *) malloc(sizeof(char) * params[uxParameterNumber].len + 1);
			memset(params[uxParameterNumber].parameter, 0x00, xParameterStringLength + 1);
			for (i = 0; i < xParameterStringLength; i++) {
				params[uxParameterNumber].parameter[i] = pcParameter[i];
			}
		}

		/* The first time the function is called after the command has been
		entered just a header string is returned. */
		sprintf( pcWriteBuffer, "The parameters were:\r\n" );

		/* Next time the function is called the first parameter will be echoed
		back. */
		uxParameterNumber = 1U;

		/* There is more data to be returned as no parameters have been echoed
		back yet. */
		xReturn = pdPASS;
	}
	else
	{
		/* Obtain the parameter string. */
		pcParameter = FreeRTOS_CLIGetParameter
						(
							pcCommandString,		/* The command string itself. */
							uxParameterNumber,		/* Return the next parameter. */
							&xParameterStringLength	/* Store the parameter string length. */
						);

		if( pcParameter != NULL )
		{
			if (uxParameterNumber < MAX_ARGC) {
				params[uxParameterNumber].len = xParameterStringLength;
				params[uxParameterNumber].parameter = (char *) malloc(sizeof(char) * params[uxParameterNumber].len + 1);
				memset(params[uxParameterNumber].parameter, 0x00, xParameterStringLength + 1);
				for (i = 0; i < xParameterStringLength; i++) {
					params[uxParameterNumber].parameter[i] = pcParameter[i];
				}
			}

			/* Return the parameter string. */
			memset( pcWriteBuffer, 0x00, xWriteBufferLen );
			sprintf( pcWriteBuffer, "%d: ", ( int ) uxParameterNumber );
			strncat( pcWriteBuffer, ( char * ) pcParameter, ( size_t ) xParameterStringLength );
			strncat( pcWriteBuffer, "\r\n", strlen( "\r\n" ) );

			/* There might be more parameters to return after this one. */
			xReturn = pdTRUE;
			uxParameterNumber++;
		}
		else
		{
			argc = uxParameterNumber;
//			argv = (char (*)[MAX_STRLEN]) malloc(argc * MAX_STRLEN * sizeof(char));
			memset( pcWriteBuffer, 0x00, xWriteBufferLen );
			for (i = 0; i < argc; i++) {
				argv[i] = (char *) malloc(sizeof(char) * params[i].len);
				memset(argv[i], 0x00, params[i].len);
				strncpy(argv[i], params[i].parameter, params[i].len);
				free(params[i].parameter);
			}

			for (i = 0; i < sizeof(shellCmds) / sizeof (shellCmds[0]); i++) {
				if (0 == strncmp(argv[0], shellCmds[i].shellCmd.pcCommand, strlen(shellCmds[i].shellCmd.pcCommand))) {
					shellCmds[i].shell_callback(argc, argv);
				}
			}

//			for (i = 0; i < argc; i++) {
//				strncat(pcWriteBuffer, argv[i], strlen(argv[i]));
//				strncat(pcWriteBuffer, ".\r\n", strlen(".\r\n"));
//			}

			/* No more parameters were found.  Make sure the write buffer does
			not contain a valid string. */
//			pcWriteBuffer[ 0 ] = 0x00;

			/* No more data to return. */
			xReturn = pdFALSE;

			/* Start over the next time this command is executed. */
			uxParameterNumber = 0;
		}
	}

//	if (pdTRUE == xReturn || pdPASS == xReturn) {
//		index = uxParameterNumber - 1;
//		if (index < MAX_ARGC) {
//			params[index].len = xParameterStringLength;
//			params[index].parameter = (char *) malloc(sizeof(char) * params[index].len);
//			for (i = 0; i < xParameterStringLength; i++) {
//				params[index].parameter[i] = pcParameter[i];
//			}
//		}
//	} else if (pdFALSE == xReturn) {
//		argv = (char (*)[MAX_STRLEN]) malloc(argc * MAX_STRLEN * sizeof(char));
//		for (i = 0; i < argc; i++) {
//			memset(argv[i], 0x00, MAX_STRLEN);
//			strncpy(argv[i], params[i].parameter, params[i].len);
//			free(params[i].parameter);
//		}
//
//		for (i = 0; i < sizeof(shellCmds) / sizeof (shellCmds[0]); i++) {
//			if (0 == strncmp(argv[0], shellCmds[i].shellCmd.pcCommand, strlen(shellCmds[i].shellCmd.pcCommand))) {
//				shellCmds[i].shell_callback(argc, argv);
//			}
//		}
//	}

	return xReturn;
}
#else
static BaseType_t prvShellParamHandler( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
const char *pcParameter;
BaseType_t xParameterStringLength, xReturn;
static UBaseType_t uxParameterNumber = 0;
//	char (*argv)[MAX_STRLEN];
	char *argv[MAX_ARGC];
	int argc;
	int i;
	int index;

	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) pcCommandString;
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );

	while (1) {
		pcParameter = FreeRTOS_CLIGetParameter
					(
						pcCommandString,		/* The command string itself. */
						uxParameterNumber,		/* Return the next parameter. */
						&xParameterStringLength	/* Store the parameter string length. */
					);
		i = uxParameterNumber;
		if (pcParameter != NULL) {
			argv[i] = (char *) malloc(sizeof(char) * xParameterStringLength + 1);
			memset(argv[i], 0x00, sizeof(char) * xParameterStringLength + 1);
			strncpy(argv[i], pcParameter, xParameterStringLength);
			uxParameterNumber++;
		} else {
			xReturn = pdFALSE;
			argc = uxParameterNumber;
			uxParameterNumber = 0;
			break;
		}
	}

	for (i = 0; i < sizeof(shellCmds) / sizeof (shellCmds[0]); i++) {
		if (0 == strncmp(argv[0], shellCmds[i].shellCmd.pcCommand, strlen(shellCmds[i].shellCmd.pcCommand))) {
			shellCmds[i].shell_callback(argc, argv);
		}
	}
	for (i = 0; i < argc; i++) {
		free(argv[i]);
	}

	return xReturn;
}
#endif

void RegisteShellCmds(const SHELL_CMD_LIST * const pxCmdsToRegister, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		FreeRTOS_CLIRegisterCommand( &(pxCmdsToRegister[i].shellCmd) );
	}
}

void Shell_Task(uint_32 temp)
{ 
	RegisteShellCmds(shellCmds, sizeof(shellCmds) / sizeof(shellCmds[0]));
	vUARTCommandConsoleStart(2000, 2);

   /* Run the shell on the serial port */
//   for(;;)  {
//      Shell(Shell_commands, NULL);
//      printf("Shell exited, restarting...\n");
//   }
}
#endif

/* EOF */
