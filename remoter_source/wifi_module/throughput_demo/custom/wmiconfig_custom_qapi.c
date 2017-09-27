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

#include <main.h>
#include <throughput.h>
#include "qcom_api.h"
#include "qcom_legacy.h"
#if !ENABLE_STACK_OFFLOAD
#include <sh_rtcs.h>
#endif
//by colin
#include "port.h"

A_STATUS is_driver_initialized()
{
    A_INT32 error,dev_status; 
    _enet_handle enethandle;
    
    enethandle = get_active_device_handle();
    
    error = ENET_mediactl (enethandle,ENET_MEDIACTL_IS_INITIALIZED,&dev_status);
    if (ENET_OK != error || dev_status == A_FALSE)
    {
        return A_ERROR;
    }   
    
    return A_OK;
}

extern A_UINT8 g_driverState;
extern A_UINT32 concurrent_connect_flag;
extern A_UINT16 ap_channel_hint;
extern A_UINT8 ssid_str_concurrent[MAX_SSID_LENGTH];
/*FUNCTION*-----------------------------------------------------------------
*
* Function Name  : check_driver_state
* Returned Value : A_OK or A_ERROR
* Comments       : Checks if driver is loaded or not
*
*END------------------------------------------------------------------*/
A_INT32 check_driver_state()
{
#if 0	
    A_UINT32 state;
    ATH_IOCTL_PARAM_STRUCT ath_param;
    A_UINT32 error;

    ath_param.cmd_id = ATH_IS_DRIVER_INITIALIZED;
    ath_param.data = &state;
    error = ath_ioctl_handler (handle,&ath_param);
    if (A_OK != error)
    {
      printf("Driver not initialized\n");
    }
#else
    if(g_driverState != DRIVER_STATE_RUN)
    {
      printf("Driver is still in INIT state\n");
      return (A_ERROR);
    }
#endif    
    return (A_OK);
}

A_STATUS handle_ioctl(ATH_IOCTL_PARAM_STRUCT* inout_param)
{ 
    _enet_handle enethandle;
    
    enethandle = get_active_device_handle();
    A_STATUS error = (A_STATUS) ENET_mediactl (enethandle,ENET_MEDIACTL_VENDOR_SPECIFIC,inout_param);

    return error;
}

/*FUNCTION*-------------------------------------------------------------
*
* Function Name   : driver_updown_indicator()
* Returned Value  : A_OK - success, A_ERROR - failure
* Comments	: handles the state of driver either up/down
*
*END*-----------------------------------------------------------------*/
A_UINT8 driver_status(A_UINT8 val)
{
    static A_UINT8 driver_down_flag = DRIVER_UP;
    /* if the driver is up set this val to driver_up*/
    if(val == DRIVER_UP)
    {
        driver_down_flag = DRIVER_UP;
    }
    /* if the driver is down set this val to driver_down*/
    else if(val == DRIVER_DOWN)
    {
       driver_down_flag = DRIVER_DOWN;
    }
    /* we will read the driver status from reset fn
       if the driver status indicates down we will
       not allow reset
     */
    else if(val == READ_STATUS)
    {
       return driver_down_flag;
    }
    return driver_down_flag;
}

/*FUNCTION*-------------------------------------------------------------
*
* Function Name   : NetConnect()
* Returned Value  : 0 - success, 1 - failure
* Comments	: Handles connection to AP after WPS
*
*END*-----------------------------------------------------------------*/
A_INT32 NetConnect(ATH_NETPARAMS *pNetparams)
{
    A_INT32 status = A_ERROR;
    qcom_wps_credentials_t wpsCred;
    A_UINT32 enet_device = get_active_device();
	
    A_MEMZERO(&wpsCred, sizeof(qcom_wps_credentials_t));  	    

	do{
		if(pNetparams->ssid_len == 0)
		{
			//printf("WPS failed\n");
			break;
		}
		else
		{	
			printf("SSID received %s\n",pNetparams->ssid);
			if(pNetparams->sec_type == ENET_MEDIACTL_SECURITY_TYPE_WPA2)
			{
		    	printf("Security type is WPA2\n");
				printf("Passphrase %s\n",(char*)pNetparams->u.passphrase);
			}
			else if(pNetparams->sec_type == ENET_MEDIACTL_SECURITY_TYPE_WPA)
		    {
		    	printf("Security type is WPA\n");
				printf("Passphrase %s\n",(char*)pNetparams->u.passphrase);
			}
			else if(pNetparams->sec_type == ENET_MEDIACTL_SECURITY_TYPE_WEP)
		    {
		    	printf("Security type is WEP\n");
				printf("WEP key %s\n",(char*)pNetparams->u.wepkey);
				printf("Key index %d\n",pNetparams->key_index);
			}
			else if(pNetparams->sec_type == ENET_MEDIACTL_SECURITY_TYPE_NONE)
		    {
		    	printf("Security type is None\n");
		    }
		    
	    	set_callback();
	    
	    	strcpy((char *) wpsCred.ssid, (char*)pNetparams->ssid);
		wpsCred.ssid_len = strlen((char *) wpsCred.ssid);
	    	strcpy((char*)original_ssid,(char*)pNetparams->ssid);
                qcom_set_ssid(enet_device, (char *)wpsCred.ssid);
	    	
			if(pNetparams->sec_type == ENET_MEDIACTL_SECURITY_TYPE_WPA2){
				wpsCred.auth_type = WLAN_AUTH_WPA2_PSK;
				wpsCred.encr_type = WLAN_CRYPT_AES_CRYPT;
				
		        if(strlen((char*)pNetparams->u.passphrase) != 64)
				{								
					qcom_sec_set_passphrase(enet_device,(char*)pNetparams->u.passphrase);
				}
				else
				{
					if(A_OK != qcom_sec_set_pmk(enet_device,(char*)pNetparams->u.passphrase))
						break;
				}
			}else if (pNetparams->sec_type == ENET_MEDIACTL_SECURITY_TYPE_WPA){
				wpsCred.auth_type = WLAN_AUTH_WPA_PSK;
				wpsCred.encr_type = WLAN_CRYPT_TKIP_CRYPT;
		        if(strlen((char*)pNetparams->u.passphrase) != 64)
				{								
					qcom_sec_set_passphrase(enet_device,(char*)pNetparams->u.passphrase);
				}
				else
				{
					if(A_OK != qcom_sec_set_pmk(enet_device,(char*)pNetparams->u.passphrase))
						break;
				}
			}else if (pNetparams->sec_type == ENET_MEDIACTL_SECURITY_TYPE_WEP){
				wpsCred.key_idx = pNetparams->key_index;
				strcpy((char *)wpsCred.key, (char*)pNetparams->u.wepkey); 
				wpsCred.key_len = strlen((char*)pNetparams->u.wepkey);
			}else if (pNetparams->sec_type == ENET_MEDIACTL_SECURITY_TYPE_NONE){
			    wpsCred.auth_type = WLAN_AUTH_NONE;
			//	ATH_SET_SEC_TYPE (IPCFG_default_enet_device,"none");
			}
				
			//iwcfg_set_mode (IPCFG_default_enet_device,"managed");
			qcom_wps_set_credentials(enet_device, &wpsCred); 
		    qcom_wps_connect(enet_device);
		    status = 0;
		}
	}while(0);

	return status;
}

A_INT32 CompleteWPS(ATH_NETPARAMS *pNetparams, A_UINT8 block, qcom_mode_t mode_flag)
{
    A_UINT32 status = 0;
    ATH_IOCTL_PARAM_STRUCT param;
    A_STATUS error;
    A_UINT32    enet_device, wifimode;

    enet_device = get_active_device();
    
    pNetparams->error = 0;
    pNetparams->dont_block = (block)? 0:1;

    param.cmd_id = ATH_AWAIT_WPS_COMPLETION;
    param.data = pNetparams;
    param.length = sizeof(*pNetparams);

    /* this will block until the WPS operation completes or times out */
    error = HANDLE_IOCTL (&param);

    qcom_op_get_mode(enet_device, &wifimode);
    if (wifimode == QCOM_WLAN_DEV_MODE_STATION) {
	if(error != A_OK)
	{
            pNetparams->error = pNetparams->error?pNetparams->error:A_EBUSY;
	}
    }
    
    do{
	    if (A_PENDING == error)
	    {
	        break;
	    }

	    status =1;

	    if(A_OK != error && pNetparams->error==A_OK){
		    pNetparams->error=error;
	    	printf("ATH_AWAIT_WPS_COMPLETION failed!\n");
	    	break;
	    }

	    if(pNetparams->error !=0)
	    {
	        switch (pNetparams->error)
	        {

	        	case ATH_WPS_ERROR_INVALID_START_INFO:

	        	printf("WPS error: invalid start info\n");
	        	break;
	        	case ATH_WPS_ERROR_MULTIPLE_PBC_SESSIONS:
	        	printf("WPS error: Multiple PBC Sessions\n");
	        	break;

	        	case ATH_WPS_ERROR_WALKTIMER_TIMEOUT:
	        	printf("WPS error: Walktimer Timeout\n");
	        	break;

	        	case ATH_WPS_ERROR_M2D_RCVD:
	        	printf("WPS error: M2D RCVD\n");
	        	break;

				case ATH_WPS_ERROR_PWD_AUTH_FAIL:
				printf("WPS error: AUTH FAIL\n");
				break;

				case ATH_WPS_ERROR_CANCELLED:
				printf("WPS error: WPS CANCEL\n");
				break;

				case ATH_WPS_ERROR_INVALID_PIN:
				printf("WPS error: INVALID PIN\n");
				break;

	        	default:
	        	//printf("WPS error: unknown %d\n",pNetparams->error);
	        	break;
	        }
	    }
    }while(0);

    qcom_op_get_mode(enet_device, &wifimode);
    if (wifimode == QCOM_WLAN_DEV_MODE_AP) {
        if (0x00 == pNetparams->error && A_OK == error) {
            printf("\n***** WPS PROFILE ****\n %s\n", pNetparams->ssid);
            printf("SSID received %s\n", pNetparams->ssid);
            if (pNetparams->sec_type == ENET_MEDIACTL_SECURITY_TYPE_WPA2)
            {
                printf ("Security type is WPA2, Encryption Type is AES\n");
                printf ("Passphrase %s\n",(char*)pNetparams->u.passphrase);
            }
            else
            {
                printf ("Security type is Open\n");
            }
            status = 0;
        }
        else
        {
            pNetparams->error = (pNetparams->error)?pNetparams->error:A_EBUSY;
            status = 0;
        }

    }

    return status;
}

void application_frame_cb(A_VOID *ptr)
{	
	A_UINT16 i,print_length,j=0;
	A_UINT8 *pData;
	
	print_length = 32;
	printf("frame (%d):\n", A_NETBUF_LEN(ptr));
	/* only print the first 64 bytes of each frame */
	if(A_NETBUF_LEN(ptr) < print_length) 
		print_length = A_NETBUF_LEN(ptr);
	
	pData = A_NETBUF_DATA(ptr);
	
	for(i=0 ; i<print_length ; i++){
		printf("0x%02x, ", pData[i]);
		if(j++==7){
			j=0;
			printf("\n");
		}
	}
	
	if(j){
	    printf("\n");
	}

	A_NETBUF_FREE(ptr);
}

extern A_UINT32 ar4XXX_boot_param;

/*FUNCTION*-------------------------------------------------------------
*
* Function Name   : ath_driver_state()
* Returned Value  : A_OK - successful completion or 
*		   A_ERROR - failed.
* Comments		  : Handles sriver reset functionality
*
*END*-----------------------------------------------------------------*/

A_INT32 ath_driver_state( A_INT32 argc, char* argv[])
{
    A_INT32 error;
    ATH_IOCTL_PARAM_STRUCT ath_param;
    A_UINT32 value;
    
    do{
        if(argc != 1) break;
        
        ath_param.cmd_id = ATH_CHIP_STATE;
        ath_param.length = sizeof(value);
        //value = atoi(argv[0]);
        
        if(strcmp(argv[0],"up") == 0)
        {
            value = 1;
            
            ath_param.data = &value;		   
            error = HANDLE_IOCTL (&ath_param);
            
            if(error == A_OK){			
                    driver_status(DRIVER_UP);
                    return A_OK;
            }else{
                    printf("driver ioctl error\n");
                    return A_ERROR;
            }
        }
        else if(strcmp(argv[0],"down") == 0)
        {
            value = 0;
            ath_param.data = &value;
            error = HANDLE_IOCTL (&ath_param);
            
            if(error == A_OK){			
                    driver_status(DRIVER_DOWN);
                    return A_OK;
            }else{
                    printf("driver ioctl error\n");
                    return A_ERROR;
            }
        }
        else if(strcmp(argv[0],"flushdown") == 0)
        {
            /*Check if no packets are queued, if TX is pending, then wait*/
            while(get_tx_status() != ATH_TX_STATUS_IDLE){
            qosal_time_delay(500); 
            }
            
            value = 0;
            ath_param.data = &value;
            error = HANDLE_IOCTL ( &ath_param);
            
            if(error == A_OK){			
                    return A_OK;
            }else{
                    printf("driver ioctl error\n");
                    return A_ERROR;
            }
        }
        else if(strcmp(argv[0],"raw") == 0)
        {
            ar4XXX_boot_param = AR4XXX_PARAM_RAWMODE_BOOT;
            value = 0;
            ath_param.data = &value;
            if((error = HANDLE_IOCTL (&ath_param)) != A_OK)
                    return A_ERROR;	
            
            value = 1;
            ath_param.data = &value;
            if((error = HANDLE_IOCTL (&ath_param)) != A_OK)
                    return A_ERROR;
        }
        else if(strcmp(argv[0],"rawq") == 0)
        {
            printf("Not supported on MQX platform\n");
            return A_OK;
        }
        else if(strcmp(argv[0],"quad") == 0)
        {
            printf("Not supported on MQX platform\n");
            return A_OK;
        }
        else if(strcmp(argv[0],"normal") == 0)
        {
            ar4XXX_boot_param = AR4XXX_PARAM_MODE_NORMAL;
            value = 0;
            ath_param.data = &value;
            if((error = HANDLE_IOCTL (&ath_param)) != A_OK)
                    return A_ERROR;	
            
            value = 1;
            ath_param.data = &value;
            if((error = HANDLE_IOCTL (&ath_param)) != A_OK)
                    return A_ERROR;	
        }        
        else
        {
            printf("Invalid parameter: try wmiconfig --help\n");
        }
                        
        return A_OK;
    
    }while(0);
    
    printf("param error: driver state\n");
    return A_ERROR;  
}


/*FUNCTION*--------------------------------------------------------------------
*
* Function Name   : ath_reg_query()
* Returned Value  : A_OK - on successful completion
*					A_ERROR - on any failure. 
* Comments        : reads / writes AR600X registers.
*
*END*------------------------------------------------------------------------*/
A_INT32 ath_reg_query( A_INT32 argc, char* argv[])
{
	A_INT32 error;
	A_UINT8 print_result=0;
	ATH_IOCTL_PARAM_STRUCT ath_param;
	ATH_REGQUERY ath_regquery;
    _enet_handle enethandle;
    
    enethandle = get_active_device_handle();

        /*Check if driver is loaded*/
        if(IS_DRIVER_READY != A_OK){
            return A_ERROR;
        } 
	do{
		if(argc < 2 || argc > 4) break;
		
		ath_regquery.operation = atoi(argv[0]);
		ath_regquery.address = mystrtoul(argv[1], NULL, 16);
		
		if(ath_regquery.operation == ATH_REG_OP_READ){
			if(argc != 2) break;
			
			print_result = 1;			
		}else if(ath_regquery.operation == ATH_REG_OP_WRITE){
			if(argc != 3) break;
			
			ath_regquery.value = mystrtoul(argv[2], NULL, 16);
		}else if(ath_regquery.operation == ATH_REG_OP_RMW){
			if(argc != 4) break;
			
			ath_regquery.value = mystrtoul(argv[2], NULL, 16);
			ath_regquery.mask = mystrtoul(argv[3], NULL, 16);
		}else{
			break;
		}
	
		ath_param.cmd_id = ATH_REG_QUERY;
	    ath_param.data = &ath_regquery;
	    ath_param.length = sizeof(ath_regquery);
	    
		error = ENET_mediactl (enethandle, ENET_MEDIACTL_VENDOR_SPECIFIC, &ath_param);
		
		if(error == A_OK){
			if(print_result){
				printf("value=%08x\n", ath_regquery.value);
			}
			return A_OK;
		}else{
			printf("driver ioctl error\n");
			return A_ERROR;
		}
	}while(0);
	
	printf("param error: register query\n");
	return A_ERROR; 
}

/*FUNCTION*--------------------------------------------------------------------
*
* Function Name   : ath_mem_query()
* Returned Value  : A_OK - on successful completion
*					A_ERROR - on any failure. 
* Comments        : reads / writes AR600X registers.
*
*END*------------------------------------------------------------------------*/
A_INT32 ath_mem_query( A_INT32 argc, char* argv[])
{
	A_INT32 error;
	ATH_IOCTL_PARAM_STRUCT ath_param;
	ATH_MEMQUERY ath_memquery;
    _enet_handle enethandle;
    
    enethandle = get_active_device_handle();

	do{									
		ath_param.cmd_id = ATH_MEM_QUERY;
	    ath_param.data = &ath_memquery;
	    ath_param.length = sizeof(ath_memquery);
	    
		error = ENET_mediactl (enethandle, ENET_MEDIACTL_VENDOR_SPECIFIC, &ath_param);
		
		printf("firmware memory stats:\n");
		
		if(error == A_OK){
			
			printf("literals = %d\n", ath_memquery.literals);
			
			printf("rodata = %d\n", ath_memquery.rodata);
			
			printf("data = %d\n", ath_memquery.data);
		
			printf("bss = %d\n", ath_memquery.bss);
			
			printf("text = %d\n", ath_memquery.text);
			
			printf("heap remaining = %d\n", ath_memquery.heap);
														
			return A_OK;
		}else{
			printf("driver ioctl error\n");
			return A_ERROR;
		}
	}while(0); 
}

_enet_handle get_active_device_handle()
{
    return(enet_handle[active_device]);
}

/*FUNCTION*-------------------------------------------------------------
*
* Function Name   : set_power_mode
* Returned Value  : A_OK if success else ERROR 
*                   
* Comments        : Sets current power mode to Power-Save or Max-Perf
*
*END*-----------------------------------------------------------------*/
A_INT32 set_power_mode_old(char* pwr_mode)
{
	int mode;
    A_UINT32 enet_device;
    
    enet_device = get_active_device();
	
	mode = atoi(pwr_mode);
	
	if (mode != 0 && mode != 1)
	{
		printf("Invalid power mode\n");
		return A_ERROR;
	}	
	
	return(iwcfg_set_power(enet_device,mode,0));
}

/*
 * huang
 */
A_INT32 wmi_set_scan_param(ENET_SCAN_LIST_PTR pEnetScanList, A_INT16 * num_scan)
{
    A_INT32 error,i=0;
    ENET_SCAN_LIST  param;
    A_UINT8 temp_ssid[33];
//    A_INT16 num_scan;
    A_UINT32 dev_num;
// haung
#if 0
    A_UINT8 scan_ssid_flag = 0;			//Flag to decide whether to scan all ssid/channels
	A_UINT8 scan_ssid[MAX_SSID_LENGTH];
//	A_INT32 error = A_OK;
	A_UINT32 enet_device, wifimode;
	A_UINT8  orig_ssid[MAX_SSID_LENGTH];
#if 0 //ENABLE_P2P_MODE
	if(p2p_session_in_progress)
	{
		printf("p2p event in progress \n");
		return A_ERROR;
	}
#endif
	enet_device = get_active_device();

	memset(scan_ssid,0,MAX_SSID_LENGTH);
	memset(orig_ssid,0,MAX_SSID_LENGTH);

	qcom_get_ssid(enet_device, (char *)orig_ssid);
	qcom_op_get_mode(enet_device, &wifimode);

	if (wifimode == QCOM_WLAN_DEV_MODE_AP)
	{
		printf("AP mode cannot scan\n");
		return A_ERROR;
	}

	/*Set SSID for scan*/
	if(scan_ssid_flag)
	{
		error = qcom_set_ssid (enet_device,(char*)scan_ssid);
		if(error != A_OK)
		{
			printf("Unable to set SSID\n");
			return error;
		}
	}
	else
	{
		error = qcom_set_ssid (enet_device,"");
		if(error != A_OK)
		{
			printf("Unable to set SSID\n");
			return error;
		}
	}
#endif
//end
	dev_num = get_active_device();

    /*Check if driver is loaded*/
    if(IS_DRIVER_READY != A_OK){
        return A_ERROR;
    }
    if (dev_num < BSP_ENET_DEVICE_COUNT)
    {
#ifndef USE_QCOM_REL_3_3_API
        error = qcom_set_scan(dev_num, NULL);
#else
        error = qcom_set_scan(dev_num);
#endif
        if (A_OK != error)
        {
            return error;
        }

        error = qcom_get_scan(dev_num, (QCOM_BSS_SCAN_INFO**)&(pEnetScanList->scan_info_list), num_scan);
        if (A_OK != error)
        {
            return error;
        }

        return A_OK;
    }
    printf("IWCONFIG_ERROR: Invalid Device number\n");
    return ENETERR_INVALID_DEVICE;
}
//end

A_INT32 wmi_set_scan(A_UINT32 dev_num, void *start_scan)
{
    A_INT32 error,i=0;
    ENET_SCAN_LIST  param;
    A_UINT8 temp_ssid[33];
    A_INT16 num_scan;
    
    /*Check if driver is loaded*/
    if(IS_DRIVER_READY != A_OK){
        return A_ERROR;
    }     
    if (dev_num < BSP_ENET_DEVICE_COUNT)
    {
#ifndef USE_QCOM_REL_3_3_API
        error = qcom_set_scan(dev_num, (qcom_start_scan_params_t *) start_scan); 
#else
        error = qcom_set_scan(dev_num);
#endif 
        if (A_OK != error)
        {
            return error;
        }

        error = qcom_get_scan(dev_num, (QCOM_BSS_SCAN_INFO**)&(param.scan_info_list), &num_scan);
        if (A_OK != error)
        {
            return error;
        }
	printf("Scan result count:%d\n",num_scan);
   
        for (i = 0;i<num_scan;i++)
        {
			memcpy(temp_ssid,param.scan_info_list[i].ssid,param.scan_info_list[i].ssid_len);
		
			temp_ssid[param.scan_info_list[i].ssid_len] = '\0';
        
            if (param.scan_info_list[i].ssid_len == 0)
            {            	           
               printf("ssid = SSID Not available\n");
            }
            else {
#if ENABLE_SCC_MODE 
              if((concurrent_connect_flag == 0x0F) && (strcmp((char const *)ssid_str_concurrent, (char const *)temp_ssid) == 0))
              {
                ap_channel_hint = param.scan_info_list[i].channel;
                printf("scan res ch : %d \n", ap_channel_hint);
                return A_OK;
              }
              else if((concurrent_connect_flag == 0x0F))
              {
                 return A_OK;
              }
              else 
#endif
             {
               printf ("ssid = %s\n",temp_ssid);
            
            printf ("bssid = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",param.scan_info_list[i].bssid[0],param.scan_info_list[i].bssid[1],param.scan_info_list[i].bssid[2],param.scan_info_list[i].bssid[3],param.scan_info_list[i].bssid[4],param.scan_info_list[i].bssid[5]);
            printf ("channel = %d\n",param.scan_info_list[i].channel);
            
            printf("indicator = %d\n",param.scan_info_list[i].rssi);

	        printf("security = ");

	        if(param.scan_info_list[i].security_enabled){
	            if(param.scan_info_list[i].rsn_auth || param.scan_info_list[i].rsn_cipher){
	                printf("\n\r");
	                printf("RSN/WPA2= ");
	            }

	            if(param.scan_info_list[i].rsn_auth){
	                printf(" {");
	                if(param.scan_info_list[i].rsn_auth & SECURITY_AUTH_1X){
	                    printf("802.1X ");
	                }

	                if(param.scan_info_list[i].rsn_auth & SECURITY_AUTH_PSK){
	                    printf("PSK ");
	                }
	                printf("}");
	            }

	            if(param.scan_info_list[i].rsn_cipher){
	                printf(" {");
	                /* AP security can support multiple options hence
	                 * we check each one separately. Note rsn == wpa2 */
	                if(param.scan_info_list[i].rsn_cipher & ATH_CIPHER_TYPE_WEP){
	                    printf("WEP ");
	                }

	                if(param.scan_info_list[i].rsn_cipher & ATH_CIPHER_TYPE_TKIP){
	                    printf("TKIP ");
	                }

	                if(param.scan_info_list[i].rsn_cipher & ATH_CIPHER_TYPE_CCMP){
	                    printf("AES ");
	                }
	                printf("}");
	            }

	            if(param.scan_info_list[i].wpa_auth || param.scan_info_list[i].wpa_cipher){
	                printf("\n\r");
	                printf("WPA= ");
	            }

	            if(param.scan_info_list[i].wpa_auth){
	                printf(" {");
	                if(param.scan_info_list[i].wpa_auth & SECURITY_AUTH_1X){
	                    printf("802.1X ");
	                }

	                if(param.scan_info_list[i].wpa_auth & SECURITY_AUTH_PSK){
	                    printf("PSK ");
	                }
	                printf("}");
	            }

	            if(param.scan_info_list[i].wpa_cipher){
	                printf(" {");
	                if(param.scan_info_list[i].wpa_cipher & ATH_CIPHER_TYPE_WEP){
	                    printf("WEP ");
	                }

	                if(param.scan_info_list[i].wpa_cipher & ATH_CIPHER_TYPE_TKIP){
	                    printf("TKIP ");
	                }

	                if(param.scan_info_list[i].wpa_cipher & ATH_CIPHER_TYPE_CCMP){
	                    printf("AES ");
	                }
	                printf("}");
	            }
	            /* it may be old-fashioned WEP this is identified by
	             * absent wpa and rsn ciphers */
	            if(param.scan_info_list[i].rsn_cipher == 0 &&
	                param.scan_info_list[i].wpa_cipher == 0){
	                printf("WEP ");
	            }
	        }else{
	            printf("NONE! ");
	        }
              }
            }
	    if(i!= param.num_scan_entries-1)
	    {
                 printf("\n ");
                 printf("\n \r");
	    }
	    else
	    {
                 printf("\nshell> ");
	    }
        }
        return A_OK;
    }
    printf("IWCONFIG_ERROR: Invalid Device number\n");
    return ENETERR_INVALID_DEVICE;
}


/*FUNCTION*--------------------------------------------------------------------
*
* Function Name   : pb_interrupt_handler()
* Returned Value  : None
* Comments        : Handler for interrupt from pushbutton on MAUI
*
*END*------------------------------------------------------------------------*/
void pb_interrupt_handler()
{
#if 0 //PVH Need to implement this for kl25     
    int tmp = GPIO_IntGetEnabled();

    if(tmp & 1<<PUSH_BUTTON_PIN){
      /*Received pushbutton interrupt, initiate WPS*/
      GPIO_IntClear(1<<PUSH_BUTTON_PIN);
      wps_context.wps_pbc_interrupt = 1;
#if DRIVER_CONFIG_MULTI_TASKING
      WakeWorkerTask();
#endif
    }
#endif    
}

/*FUNCTION*--------------------------------------------------------------------
*
* Function Name   : pushButtonWPS()
* Returned Value  : None
* Comments        :Called in response to MAUI pushbutton press
*
*END*------------------------------------------------------------------------*/
void pushButtonWPS(void)
{
    qcom_wps_credentials_t wpsCred;  
    A_UINT32    enet_device;
    
    enet_device = get_active_device();    
    printf("Start WPS\n");
    wps_context.wps_in_progress = 1;
    wps_context.connect_flag = 1;
    set_power_mode(MAX_PERF_POWER,WPS);

    A_MEMZERO(&wpsCred, sizeof(qcom_wps_credentials_t));
    qcom_wps_set_credentials(enet_device, &wpsCred);
    if(qcom_wps_start(enet_device, wps_context.connect_flag, 1, NULL) != A_OK)    
    {
        printf("WPS connect error\n");
    }
}


/*FUNCTION*--------------------------------------------------------------------
*
* Function Name   : pushButtonSetup()
* Returned Value  : None
* Comments        : Setup interrupt settings on push button port and pin
*
*END*------------------------------------------------------------------------*/
void pushButtonSetup(void)
{
#if 0 //PVH Need to implement this for kl25   
  /* Configure PF5 as input */
  GPIO_PinModeSet(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN, gpioModeInputPull, 1);

  /* Set falling edge interrupt */
  GPIO_IntConfig(PUSH_BUTTON_PORT, PUSH_BUTTON_PIN, false, true, true);

  /*Install the interrupt handler*/
  ath_install_interrupt((T_ISR_HANDLER)pb_interrupt_handler, NULL);
#endif  
}

typedef struct{
#define SENTINAL 0xa55a1234
	A_UINT32 sentinal;
	int_8 ssid[33];
	A_UINT8 ipaddr[4];
	int_8 passphrase[128];
}FLASH_CONTENTS;

A_INT32 test_flash(void)
{
//by colin
#if 0
	FLASHX_BLOCK_INFO_STRUCT_PTR info_ptr;
    MQX_FILE_PTR   flash_hdl;
    _mqx_uint      error_code;
   _mem_size      base_addr;
 //  _mem_size      sector_size;
   _mqx_uint      num_sectors;
 //  _mqx_uint      test_val;
   _mqx_uint      num_blocks;
   _mqx_uint      width;
   _mem_size      total_size = 0;
 //  uchar*       write_buffer;
 //  uchar*       read_buffer;
//   uchar*       old_buffer;
   _mqx_int       i;//, test_block;
 //  _mqx_uint      j, k, n;
   _mem_size      seek_location;
//   _mem_size      read_write_size = 0;
   _mqx_uint      ident_arr[3];
//   boolean        test_completed = FALSE; 
   FLASH_CONTENTS flash_buffer;     
   /* Open the flash device */
    flash_hdl = fopen("flashx:", NULL);
    _io_ioctl(flash_hdl, IO_IOCTL_DEVICE_IDENTIFY, &ident_arr[0]);
    printf("\nFlash Device Identity: %#010x, %#010x, %#010x",
             ident_arr[0], ident_arr[1], ident_arr[2]);
      
   error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_BASE_ADDRESS, &base_addr);
   if (error_code != MQX_OK) {
      printf("\nFLASH_IOCTL_GET_BASE_ADDRESS failed.");
      qosal_task_suspend(NULL);
   } else {
      printf("\nThe BASE_ADDRESS: 0x%x", base_addr);
   } /* Endif */
     
   error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_NUM_SECTORS, &num_sectors);
   if (error_code != MQX_OK) {
      printf("\nFLASH_IOCTL_GET_NUM_SECTORS failed.");
      qosal_task_suspend(NULL);
   } else {
      printf("\nNumber of sectors: %d", num_sectors);
   } /* Endif */

   error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_WIDTH, &width);
   if (error_code != MQX_OK) {
      printf("\nFLASH_IOCTL_GET_WIDTH failed.");
      qosal_task_suspend(NULL);
   } else {
      printf("\nThe WIDTH: %d", width);
   } /* Endif */

   error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_BLOCK_MAP, 
      (A_UINT32 _PTR_)&info_ptr);      
   if (error_code != MQX_OK) {
      printf("\nFLASH_IOCTL_GET_BLOCK_MAP failed.");
      qosal_task_suspend(NULL);
   } /* Endif */
            
   error_code = ioctl(flash_hdl, FLASH_IOCTL_GET_BLOCK_GROUPS, &num_blocks);
   if (error_code != MQX_OK) {
      printf("\nFLASH_IOCTL_GET_NUM_BLOCKS failed");
      qosal_task_suspend(NULL);
   } /* Endif */

   for ( i = 0; i < num_blocks; i++ ) {
       printf("\nThere are %d sectors in Block %d", info_ptr[i].NUM_SECTORS, 
          (i + 1));
#if MQX_VERSION == 380
       printf("\nBlock %d Sector Size: %d (0x%x)", (i + 1),
                 info_ptr[i].SECTOR_SIZE, info_ptr[i].SECTOR_SIZE);
       total_size += (info_ptr[i].SECTOR_SIZE * info_ptr[i].NUM_SECTORS);
#else       
       //printf("\nBlock %d Sector Size: %d (0x%x)", (i + 1),
       //   info_ptr[i].SECT_SIZE, info_ptr[i].SECT_SIZE);
       //total_size += (info_ptr[i].SECT_SIZE * info_ptr[i].NUM_SECTORS);
#endif       
      
   } /* Endfor */
   
   /* init seek_location to the first write-able address */
   seek_location = info_ptr[0].START_ADDR;
   
   
   printf("\nTotal size of the Flash device is: %d (0x%x)", total_size,
      total_size); 
   fseek(flash_hdl, seek_location, IO_SEEK_SET);
   i = read(flash_hdl, &flash_buffer, sizeof(FLASH_CONTENTS));
   
   if(i==sizeof(FLASH_CONTENTS) && flash_buffer.sentinal == SENTINAL){
   		printf("\nsuccessfully read contents from flash\n");
   		printf("ipadddr=%d.%d.%d.%d\n", flash_buffer.ipaddr[0],
   			flash_buffer.ipaddr[1],
   			flash_buffer.ipaddr[2],
   			flash_buffer.ipaddr[3]);
   		printf("ssid=%s\n", flash_buffer.ssid);
   		printf("passphrase=%s\n", flash_buffer.passphrase);
   }else{
   		printf("\nfailed reading contents from flash--attempting write\n");

		memset(&flash_buffer, 0,sizeof(FLASH_CONTENTS));
   		flash_buffer.sentinal = SENTINAL;   		
   		flash_buffer.ipaddr[0] =  192;
   		flash_buffer.ipaddr[1] =  168;
   		flash_buffer.ipaddr[2] =  1;
   		flash_buffer.ipaddr[3] =  90;
   		memcpy(flash_buffer.ssid, "atheros_demo", 12);
   		memcpy(flash_buffer.passphrase, "my security passphrase", strlen("my security passphrase"));
   		fseek(flash_hdl, seek_location, IO_SEEK_SET);
   		i = write(flash_hdl, &flash_buffer, sizeof(FLASH_CONTENTS) );
   		
   		printf("write result = %d\n", i);
   		
   		printf("try read now\n");
   		memset(&flash_buffer, 0,sizeof(FLASH_CONTENTS));
   		fseek(flash_hdl, seek_location, IO_SEEK_SET);
   		i = read(flash_hdl, &flash_buffer, sizeof(FLASH_CONTENTS));
   		if(i==sizeof(FLASH_CONTENTS)){
	   		printf("\nsuccessfully read contents from flash\n");
	   		printf("ipadddr=%d.%d.%d.%d\n", flash_buffer.ipaddr[0],
	   			flash_buffer.ipaddr[1],
	   			flash_buffer.ipaddr[2],
	   			flash_buffer.ipaddr[3]);
	   		printf("ssid=%s\n", flash_buffer.ssid);
	   		printf("passphrase=%s\n", flash_buffer.passphrase);
	    }else{
	   		printf("\nfailed reading contents from flash--aborting!!!\n");
   		}
   }
    
   fclose(flash_hdl);
#endif
	return A_OK;
}

extern void __boot(void);
extern A_UINT8 bench_quit;


/*FUNCTION*-------------------------------------------------------------
*
* Function Name   : SystemReset()
* Returned Value  : None
*
* Comments        : Sample function to depict how to safely reset the host 
*
*END*-----------------------------------------------------------------*/
void SystemReset()
{
	A_INT32 error;
	ATH_IOCTL_PARAM_STRUCT ath_param;
	A_UINT32 value, dev_status;
//#if PSP_MQX_CPU_IS_KINETIS     //by colin
#if 1   	
//  A_UINT32 read_value = SCB->AIRCR;
#endif 
    _enet_handle enethandle;
    
    enethandle = get_active_device_handle();
	/* 
     *  If benchrx is already started and reset is given,
	 * stop the benchrx thread by making bench_quit = 1 */        
	bench_quit = 1;
	ath_param.cmd_id = ATH_CHIP_STATE;
	ath_param.length = sizeof(value);
        A_MDELAY(100);
        if(driver_status(READ_STATUS) != DRIVER_UP)
        {
            printf("driver is down reset issued only in driver up state \n");
            return;
        }

        while((error = ENET_mediactl (enethandle,ENET_MEDIACTL_IS_INITIALIZED,&dev_status))!=A_OK)
        {
            /*Wait for driver to be ready before proceeding*/
        }
	value = 0;
	ath_param.data = &value;
	error = ENET_mediactl (enethandle, ENET_MEDIACTL_VENDOR_SPECIFIC, &ath_param);
	if(error != A_OK){
          printf("IOCTL error\n");
        }
        /*Wait for a short period before reset*/
        A_MDELAY(100);

//#if PSP_MQX_CPU_IS_KINETIS     //by colin
#if 1  
#define SCB_AIRCR_VECTKEY_MASK                   0xFFFF0000u
#define SCB_AIRCR_VECTKEY_SHIFT                  16
#define SCB_AIRCR_VECTKEY(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_AIRCR_VECTKEY_SHIFT))&SCB_AIRCR_VECTKEY_MASK)
#define SCB_AIRCR_SYSRESETREQ_MASK               0x4u
	
//  read_value &= ~SCB_AIRCR_VECTKEY_MASK;
//  read_value |= SCB_AIRCR_VECTKEY(0x05FA);
//  read_value |= SCB_AIRCR_SYSRESETREQ_MASK;

//  //_int_disable();//by colin
//	__disable_irq();
//  SCB->AIRCR = read_value;
  while(1);
#else
        __boot();
#endif   
}

A_UINT32 ext_scan()
{
	A_INT32 error,i=0;
	ATH_IOCTL_PARAM_STRUCT inout_param;   
	ATH_GET_SCAN param;
	A_UINT8 temp_ssid[33];
	
    /*Check if driver is loaded*/
    if(IS_DRIVER_READY != A_OK){
        return A_ERROR;
    } 
		inout_param.cmd_id = ATH_START_SCAN_EXT;
		inout_param.data = NULL;
			   
		 
		error = HANDLE_IOCTL( &inout_param);
		
		if (A_OK != error)
		{
			return error;
		}
		
		inout_param.cmd_id = ATH_GET_SCAN_EXT;
		inout_param.data = (A_VOID*)&param;
			
		error = HANDLE_IOCTL(&inout_param);
		
		if (A_OK != error)
		{
			return error;
		}	
		
		
		if(param.num_entries){
			for(i=0 ; i<param.num_entries ; i++){
				memcpy(temp_ssid,param.scan_list[i].ssid,param.scan_list[i].ssid_len);
			
				temp_ssid[param.scan_list[i].ssid_len] = '\0';
	        
	            if (param.scan_list[i].ssid_len == 0)
	            {            	           
	               printf("ssid = SSID Not available\n");
	            }
	            else
	               printf ("ssid = %s\n",temp_ssid);
	            
	            printf ("bssid = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",param.scan_list[i].bssid[0],param.scan_list[i].bssid[1],param.scan_list[i].bssid[2],param.scan_list[i].bssid[3],param.scan_list[i].bssid[4],param.scan_list[i].bssid[5]);
	            printf ("channel = %d\n",param.scan_list[i].channel);
	            
	            printf("indicator = %d\n",param.scan_list[i].rssi);
	            printf("security = ");
	            
	            if(param.scan_list[i].security_enabled){	            	            	
	            	if(param.scan_list[i].rsn_auth || param.scan_list[i].rsn_cipher){
	            		printf("\n\r");
	            		printf("RSN/WPA2= ");	            		
	            	}
	            	
	            	if(param.scan_list[i].rsn_auth){
	            		printf(" {");  
	            		if(param.scan_list[i].rsn_auth & SECURITY_AUTH_1X){
	            			printf("802.1X ");
	            		}
	            		
	            		if(param.scan_list[i].rsn_auth & SECURITY_AUTH_PSK){
	            			printf("PSK ");
	            		}
	            		printf("}");
	            	}
	            	
	            	if(param.scan_list[i].rsn_cipher){
	            		printf(" {");     	
		            	/* AP security can support multiple options hence 
		            	 * we check each one separately. Note rsn == wpa2 */
		            	if(param.scan_list[i].rsn_cipher & ATH_CIPHER_TYPE_WEP){
			            	printf("WEP ");
			            }
			        
			            if(param.scan_list[i].rsn_cipher & ATH_CIPHER_TYPE_TKIP){
			            	printf("TKIP ");
			            }
			        
			            if(param.scan_list[i].rsn_cipher & ATH_CIPHER_TYPE_CCMP){
			            	printf("AES ");
			            }
			            printf("}");
			        }
			        
			        if(param.scan_list[i].wpa_auth || param.scan_list[i].wpa_cipher){
	            		printf("\n\r");
	            		printf("WPA= ");	            		
	            	}
			        
			        if(param.scan_list[i].wpa_auth){
			        	printf(" {");
	            		if(param.scan_list[i].wpa_auth & SECURITY_AUTH_1X){
	            			printf("802.1X ");
	            		}
	            		
	            		if(param.scan_list[i].wpa_auth & SECURITY_AUTH_PSK){
	            			printf("PSK ");
	            		}
	            		printf("}");
	            	}
	            	
	            	if(param.scan_list[i].wpa_cipher){ 
	            		printf(" {");    	
			            if(param.scan_list[i].wpa_cipher & ATH_CIPHER_TYPE_WEP){
			            	printf("WEP ");
			            }
			         
			            if(param.scan_list[i].wpa_cipher & ATH_CIPHER_TYPE_TKIP){
			            	printf("TKIP ");
			            }
			         
			            if(param.scan_list[i].wpa_cipher & ATH_CIPHER_TYPE_CCMP){
			            	printf("AES ");
			            }
			            printf("}");
			        }		            
		            /* it may be old-fashioned WEP this is identified by 
		             * absent wpa and rsn ciphers */
		            if(param.scan_list[i].rsn_cipher == 0 &&
		             	param.scan_list[i].wpa_cipher == 0){
		             	printf("WEP ");
		            }
		        }else{
		        	printf("NONE! ");
		        }

	            printf("\n");
	            

	            printf("\n\r");
			}
		}else{
			printf("no scan results found\n");
		}
	   
		return A_OK;	
}





#if ENABLE_STACK_OFFLOAD


/*FUNCTION*-------------------------------------------------------------
*
* Function Name   : wmi_ping()
* Returned Value  : None
*
* Comments        : Sample function to depict IPv4 ping functionality
*                   Only used with On-Chip IP stack
*END*-----------------------------------------------------------------*/
A_INT32 wmi_ping(A_INT32 argc, char* argv[] ){
    unsigned long   hostaddr;
    A_INT32 	    error;
    char            ip_str[16];
    A_UINT32 	    count = 1, size = 64, interval = 0;
    A_UINT32        index;

    if((argc < 2) || (argc%2 == 1))
    {
        printf("Incomplete parameters\n");
        printf("Usage: %s <host> -c <count> -s <size> -i <interval>\n", argv[0]);
        printf("or %s <host>\n", argv[0]);
        printf("   <host>      = host ip address or name\n");
        printf("   <count>     = number of pings\n");
        printf("   <size>      = size of ping packet\n");
        printf("   <interval>  = interval between packet(in ms)\n");
        return A_ERROR;
    }
    
    for(index = 1; index < argc ; index++)
    {
        if(argv[index][0] == '-')
        {
            switch(argv[index][1])
            {
            case 'c':
                index++;
                count = atoi(argv[index]);
                break;
            case 'i':
                index++;
                interval = atoi(argv[index]);
                break;
            case 's':
                index++;
                size  = atoi(argv[index]);
                if(size > CFG_PACKET_SIZE_MAX_TX)
                {
                    printf("Error: Invalid Parameter %s \n", argv[index]);
                    printf("Enter size <= %d \n",CFG_PACKET_SIZE_MAX_TX);
                    return A_ERROR;
                }
                break;
            default:
                printf("Unknown option: %s\n", argv[index]);
                return A_ERROR;
            }
        }
        else /* It must be a IP address or host name */
        {
            error=ath_inet_aton(argv[index], (A_UINT32 *)&hostaddr);
            if (error != -1)
            {
#if ENABLE_DNS_CLIENT
                if(strlen(argv[index]) > 32) 
                {
                    printf("host name cannot be more then 32 Bytes\n");
                    return A_ERROR;
                }
                if(ip_get_addr_for_host_name(argv[index],(A_UINT32 *)&hostaddr,NULL,2) != A_OK)
#endif
                {  
                    printf("Invalid IP address\n");
                    return error;
                } 
#if ENABLE_DNS_CLIENT
                else
                {
                    hostaddr = A_CPU2BE32(hostaddr);
                    printf("Ping %s: \n", inet_ntoa(A_CPU2BE32(hostaddr),ip_str));
                }  
#endif
            }
        }
    } /* for loop */

    /*Check if driver is loaded*/
    if(check_driver_state() == A_ERROR)
        return A_ERROR;
 
    for (index = 0; index < count; index++)
    {
        if(wifi_connected_flag == 0)
        {
           printf("ERROR: No WiFi connection available, please connect to an Access Point\n");
           break;
        }   
        error =qcom_ping(hostaddr,size);
        
        if(error == 0)
            printf("Ping reply from %s: time<1ms\r\n", inet_ntoa(A_CPU2BE32(hostaddr),ip_str));
        else
            printf("Request timed out\r\n");
        
        if(interval)
            qosal_msec_delay(interval);
    }

    return A_OK;
}



/*FUNCTION*-------------------------------------------------------------
*
* Function Name   : wmi_ping6()
* Returned Value  : None
*
* Comments        : Sample function to depict IPv6 ping functionality
*                   Only used with On-Chip IP stack
*END*-----------------------------------------------------------------*/
A_INT32 wmi_ping6(A_INT32 argc, char* argv[] ){
    A_INT32 			error = -1;
    A_UINT8             ip6addr[16];
    char                ip_str[48];
    A_UINT32 	    count, index, size;

    if(argc < 2)
    {
        printf("Incomplete parameters\n");
        printf("Usage: %s <host> -c <count> -s <size>\n", argv[0]);
        printf("or %s <host> \n", argv[0]);
        printf("   <host>   = host ip address or name\n");
        printf("   <count>  = number of pings\n");
        printf("   <size>   = size of ping packet\n");
        return A_ERROR;
    }

    error=Inet6Pton(argv[1],ip6addr);
    
    if(error != 0)
    {
#if ENABLE_DNS_CLIENT
       if(strlen(argv[1]) > 32) 
       {
         printf("host name cannot be more then 32 Bytes\n");
         return A_ERROR;
       }
       if(ip_get_addr_for_host_name(argv[1],NULL,(IP6_ADDR_T *)&ip6addr,3) != A_OK)
#endif
       {  
         printf("Invalid IP address\n");
         return error;
       } 
#if ENABLE_DNS_CLIENT
       else
       {
           printf("Ping %s \n", inet6_ntoa((char *)ip6addr,ip_str));
       }  
#endif
    }  

    /*Check if driver is loaded*/
    if(check_driver_state() == A_ERROR)
        return A_ERROR;

    if (argc == 2)
    {
        count = 1;
        size  = 64;
    }
    else if (argc == 6)
    {
        count = atoi(argv[3]);
        size  = atoi(argv[5]);
    }
    else
    {
        printf("Usage: %s <host> -c <count> -s <size>\n", argv[0]);
        printf("or %s <host> \n", argv[0]);
        return A_ERROR;
    }
    
    if(size > CFG_PACKET_SIZE_MAX_TX)
    {
        printf("Error: Invalid Parameter %s \n", argv[5]);
        printf("Enter size <= %d \n",CFG_PACKET_SIZE_MAX_TX);
        return A_ERROR;
    }

    for (index = 0; index < count; index++)
    {
        error =qcom_ping6(ip6addr,size);
        
        if(error == 0)
            printf("Ping reply from %s: time<1ms\n", inet6_ntoa((char *)ip6addr,ip_str));
        else
            printf("Request timed outE\n");
    }

    return A_OK;
}

#else

/*FUNCTION*-------------------------------------------------------------
*
* Function Name   : wmi_ping()
* Returned Value  : None
*
* Comments        : Sample function to depict IPv4 ping functionality
*                   Only used with RTCS IP stack
*END*-----------------------------------------------------------------*/
A_INT32 wmi_ping(A_INT32 argc, char* argv[] )
{
 _ip_address          hostaddr;
   char                 hostname[MAX_HOSTNAMESIZE];
   A_UINT32              i;
   A_INT32               time, error;
   A_UINT16              pingid = 0;
   boolean              print_usage, shorthelp = FALSE;
   A_INT32               return_code = A_OK;
   A_UINT8               num_dots = 0,param_miss = 0;
   A_UINT8               index = 0;
   A_UINT32              num_pings = 4;
   char 		*ping_send_buffer=NULL;
    PING_PARAM_STRUCT   ping_params;
     
   print_usage = Shell_check_help_request(argc, argv, &shorthelp );

   if (!print_usage)  {
      if (argc > 1)  {
         memset (hostname, 0, sizeof (hostname));
      
         index = 1;
         
         if(strcmp(argv[index],"-c")==0)
         {
         	if(argc != 4)
         	{
         		printf("missing parameters\n");
         		return A_ERROR;
         	}
         	else
         	{
         		index++;
         		num_pings = atoi(argv[index]);
         	}
                  
	        index++;
         }
         for (i=0;i<strlen(argv[index]);i++)
         {
         	if(argv[index][i] == '.')
         	 num_dots++;
         	
         	if(num_dots == 3)
         	{
         		if(i == strlen(argv[index])-1)
         		{
         			param_miss = 1;
         		}
         		else
         		{
         			param_miss = 0;
         			break;
         		}
         	}
         }
         if(num_dots != 3 || param_miss != 0)
         {
         	printf("Invalid IP address\n");
         	return A_ERROR;
         }
         
         RTCS_resolve_ip_address( argv[index], &hostaddr, hostname, MAX_HOSTNAMESIZE ); 

         if (!hostaddr)  {
#if RTCSCFG_ENABLE_DNS | RTCSCFG_ENABLE_LWDNS
            printf("Unable to resolve host\n");
#else
            printf("Unable to resolve host - dns service disabled\n");
#endif            
            return_code = A_ERROR;

         } else  {
            printf("Pinging %s [%ld.%ld.%ld.%ld]:\n", hostname, IPBYTES(hostaddr));
	     ping_send_buffer = RTCS_mem_alloc(1024); /* ping6_param[5].value - value of bytes in packet */
                if(ping_send_buffer)
                {
                    /* Set value of bytes of data buffer in according with patterns
                     * ping6_param[4].value - patterns.
                     * ping6_param[5].value - size of buffer.
                     */
                    memset(ping_send_buffer, 'p', 1024);
                }
                else
                {
                    printf("Ping error - can not allocate ping buffer. Size is too big.\n");
                    return A_NO_MEMORY;
                    
                }

            for (i=0; i<num_pings ; i++) {
               time = 5000; /* 5 seconds */
	       _mem_zero(&ping_params, sizeof(ping_params));  
                ping_params.addr.sin_family =AF_INET;
	       ping_params.addr.sin_addr.s_addr=hostaddr;	
                ping_params.timeout =time ; /* Maximum waiting time for answer */
                ping_params.id = ++pingid;
                ping_params.hop_limit = 255;          
                ping_params.data_buffer = ping_send_buffer;             
                ping_params.data_buffer_size = 1024;  
               error = RTCS_ping(&ping_params);
               if (error == RTCSERR_ICMP_ECHO_TIMEOUT) {
                  printf("Request timed out\n");
               } else if (error) {
                  if(error == 0x1000515)
                  {
                     printf("Error 0x%04lX - illegal ip address\n", error);
                  }
                  else if( error == 0x1000510) 
                  {
                     printf("Error 0x%04lX - no route to host\n", error);
                  }
                  else
                  {
                     printf("Error 0x%04lX\n", error);
                  }
               } else {
                  if (time < 1)
                  {
                     printf("Reply from %ld.%ld.%ld.%ld: time<1ms\n", IPBYTES(hostaddr));
                  }
                  else
                  {
                     printf("Reply from %ld.%ld.%ld.%ld: time=%ldms\n", IPBYTES(hostaddr), time);
                  }
                  if ((time<1000) && (i<num_pings - 1)) 
                  {
                     RTCS_time_delay(1000-time);
                  } 
               } 
            } /* Endfor */
	     _mem_free(ping_send_buffer);
         }
      } else  {
         printf("Error, %s invoked with incorrect number of arguments\n", argv[0]);
         print_usage = TRUE;
      }
   }
   
   if (print_usage)  {
      if (shorthelp)  {
         printf("%s <host>\n", argv[0]);
         printf("Usage: %s -c <count> <host>\n", argv[0]);
      } else  {
         printf("Usage: %s <host>\n", argv[0]);
         printf("Usage: %s -c <count> <host>\n", argv[0]);
         printf("   <host>   = host ip address or name\n");
         printf("   <count>  = number of pings\n");
      }
   }
   return return_code;
	
	
}

/*FUNCTION*-------------------------------------------------------------
*
* Function Name   : wmi_ping6()
* Returned Value  : None
*
* Comments        : Sample function to depict IPv6 ping functionality
*                   Not supported on RTCS
*END*-----------------------------------------------------------------*/
A_INT32 wmi_ping6(A_INT32 argc, char* argv[] )
{
   printf("ping6 command not supported ...\n");
   return A_OK;
}
#endif
