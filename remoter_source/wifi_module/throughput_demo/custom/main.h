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
* $FileName: main.h$
* $Version : 1.0$
* $Date    : 
*
* Comments:
*   The header file for Atheros wmiconfig tool.
*
*END************************************************************************/

#ifndef _main_h_
#define _main_h_
//by colin
#if MQX_RTOS || MQX_LITE
#include <psptypes.h>
#include <mqx.h>
#include <bsp.h>
#include <lwevent.h>
#include <message.h>
#endif
#include <string.h>

#include <stdlib.h>
//#include "rtcs.h"
//#include "ipcfg.h"
//#include <shell.h>
#include "atheros_wifi_api.h"
#include "atheros_stack_offload.h"

#include "enet_wifi.h"///E.Y.
//#include "iwcfg.h"///E.Y.

#define IPADDR(a,b,c,d)       (((uint32_t)(a)&0xFF)<<24)|(((uint32_t)(b)&0xFF)<<16)|(((uint32_t)(c)&0xFF)<<8)|((uint32_t)(d)&0xFF) //by colin

#define A_CHANNEL_MISMATCH 11
/* define MACROS required by common code. */
#define ATH_STRCMP(_a, _b) strcmp((char const*)(_a), (const char *)(_b))
//#define ATH_TIME_DELAY_MSEC(_a) _time_delay((_a)) //by colin
#define ATH_TIME_DELAY_MSEC(_a) qosal_usec_delay((_a))

#define DEMOCFG_ENABLE_SERIAL_SHELL    0   /* enable shell task for serial console */
#define DEMOCFG_ENABLE_SWITCH_TASK     0   /* enable button sensing task (otherwise keys are polled) */
#define DEMOCFG_ENABLE_AUTO_LOGGING    0   /* enable logging to serial console (or USB drive) */
#define DEMOCFG_ENABLE_USB_FILESYSTEM  0   /* enable USB mass storage */
//E.Y. hide #define DEMOCFG_ENABLE_RTCS            1   /* enable RTCS operation */
#define DEMOCFG_ENABLE_RTCS            1   /* enable RTCS operation */
#define DEMOCFG_ENABLE_FTP_SERVER      0   /* enable ftp server */
#define DEMOCFG_ENABLE_TELNET_SERVER   0   /* enable telnet server */
#define DEMOCFG_ENABLE_KLOG            0   /* enable kernel logging */
#define DEMOCFG_USE_POOLS              0   /* enable external memory pools for USB and RTCS */
#define DEMOCFG_USE_WIFI               1  /* USE WIFI Interface */
#define DEMOCFG_USE_SENSOR             0 //cy bolin   /*enable sensor functions*/
/* default addresses for external memory pools and klog */
#if BSP_M52259EVB
    #define DEMOCFG_RTCS_POOL_ADDR  (uint_32)(BSP_EXTERNAL_MRAM_RAM_BASE)
    #define DEMOCFG_RTCS_POOL_SIZE  0x0000A000
    #define DEMOCFG_MFS_POOL_ADDR   (uint_32)(DEMOCFG_RTCS_POOL_ADDR + DEMOCFG_RTCS_POOL_SIZE)
    #define DEMOCFG_MFS_POOL_SIZE   0x00002000
    #define DEMOCFG_KLOG_ADDR       (uint_32)(DEMOCFG_MFS_POOL_ADDR + DEMOCFG_MFS_POOL_SIZE)
    #define DEMOCFG_KLOG_SIZE       4000
#elif DEMOCFG_USE_POOLS
    #warning External pools will not be used on this board.
#endif

#if DEMOCFG_ENABLE_RTCS


   
   extern void HVAC_initialize_networking(void);

   #ifndef ENET_IPADDR
   //   #define ENET_IPADDR  IPADDR(15,15,103,25) 
     #define ENET_IPADDR  IPADDR(192,168,1,90)
   //#define ENET_IPADDR  IPADDR(172,16,83,25)
   #endif

   #ifndef ENET_IPMASK
      #define ENET_IPMASK  IPADDR(255,255,255,0) 
   #endif

   #ifndef ENET_IPGATEWAY
    //  #define ENET_IPGATEWAY  IPADDR(15,15,103,10) 
     #define ENET_IPGATEWAY  IPADDR(192,168,1,1)
   #endif
#endif
#if DEMOCFG_USE_WIFI
   #include "iwcfg.h"
   
   #define DEMOCFG_SSID            "iot"
   //Possible Values managed or adhoc
   #define DEMOCFG_NW_MODE         "managed" 
   #define DEMOCFG_AP_MODE         "softap"
   //Possible vales 
   // 1. "wep"
   // 2. "wpa"
   // 3. "wpa2"
   // 4. "none"
   #define DEMOCFG_SECURITY        "none"
   #define DEMOCFG_PASSPHRASE      NULL
   #define DEMOCFG_WEP_KEY         "abcde"
   //Possible values 1,2,3,4
   #define DEMOCFG_WEP_KEY_INDEX   1
   #define DEMOCFG_DEFAULT_DEVICE  0 /*ATHEROS_WIFI_DEFAULT_ENET_DEVICE vivi*/
#endif

#ifndef DEMOCFG_DEFAULT_DEVICE
   #define DEMOCFG_DEFAULT_DEVICE   BSP_DEFAULT_ENET_DEVICE
#endif
   
#if DEMOCFG_ENABLE_WEBSERVER
   #include "httpd.h"
#endif

#include <port_shell.h>


typedef struct {
    uint_8 ssid[32];
    uint_8 macaddress[6];
    uint_16 channel;
} wps_scan_params;

#define PRINT_HOSTVERSION(ver) 	(ver&0xF0000000)>>28,(ver&0x0F000000)>>24, \
                               	(ver&0x00FC0000)>>18,(ver&0x0003FF00)>>8,(ver&0x000000FF)

#define PRINT_TARGETVERSION(ver) ver
									
#define PRINT_FWVERSION(ver)	(ver&0xF0000000)>>28,(ver&0x0F000000)>>24, \
                                (ver&0x00FC0000)>>18,(ver&0x0003FF00)>>8,(ver&0x000000FF)
									
#define PRINT_ABIVERSION(ver) 	ver


typedef struct version {
    uint_32        host_ver;
    uint_32        target_ver;
    uint_32        wlan_ver;
    uint_32        abi_ver;
}version_t;

typedef struct versionstr {
    uint_8        host_ver[20];
    uint_8        target_ver[20];
    uint_8        wlan_ver[20];
    uint_8        abi_ver[20];
}versionstr_t;

typedef struct key
{
	char key[30];
	uint_8 key_index;
} qcom_key_t; /* key_t is  conflicting types wiht types.h */



enum wps_mode_e 
{
	PUSH_BUTTON = 1,
	PIN
};

#if ENABLE_P2P_MODE
enum p2p_mode_e
{
	CONNECT = 1,
	P2P_FIND,
	JOIN,
	LISTEN,
	CANCEL,
	STOP,
	CONNECT_CLIENT,
	NODE_LIST,
	SET_CONFIG,
	WPS_CONFIG,
	AUTH,
	DISC_REQ,
	SET,
	P2P_INVITE_AUTH,
    LIST_NETWORK,
	P2P_INVITE,
	INV_CONNECT,
	JOIN_PROFILE,
	AP_MODE,
	AP_MODE_PP,
    P2P_ON_OFF,
    P2P_SET_NOA,
    P2P_SET_OPPPS
};
#endif

typedef enum mode {

	MODE_STATION = 0,
	MODE_AP,
	MODE_ADHOC,
	MODE_MAXIMUM

}qcom_mode_t; /* mode_t is  conflicting types wiht types.h */

typedef struct {
	union {

		struct{
			A_UINT8 hidden_ssid;
		} wmi_ap_hidden_ssid_cmd;

		struct {
			A_UINT32 period;
		} wmi_ap_conn_inact_cmd;

		struct {
			A_UINT16 beaconInterval;
		} wmi_beacon_int_cmd;

		struct {
			A_UINT8 dtimval;
		}wmi_ap_dtim_cmd;

		struct {
			A_UINT8 ps_val[2];
		}wmi_ap_ps_buf_cmd;
	}u;
}AP_CFG_CMD;

#include "atheros_wifi_api.h"

enum ath_private_ioctl_cmd
{
	ATH_REG_QUERY=ATH_CMD_LAST,
	ATH_MEM_QUERY
};



typedef struct
{
	uint_32 address;
	uint_32 value;
	uint_32 mask;
	uint_32 size;
	uint_32 operation;
}ATH_REGQUERY;

typedef struct
{
	uint_32 literals;
	uint_32 rodata;
	uint_32 data;
	uint_32 bss;
	uint_32 text;
	uint_32 heap;
}ATH_MEMQUERY;


typedef struct {
	uint_8 wps_in_progress;
	uint_8 connect_flag;
        A_UINT8 wps_pbc_interrupt;
        ATH_NETPARAMS netparams;
        A_UINT8 wps_init_key;
}wps_context_t;


#define ATH_REG_OP_READ 			(1)
#define ATH_REG_OP_WRITE 			(2)
#define ATH_REG_OP_RMW 				(3)
#define MAX_ACK_RETRY  			   (20)	 //Max number of times ACK issent to Peer with stats
#define MAX_SSID_LENGTH 		 (32+1)

#define MIN_WEP_KEY_SIZE			10
#define MAX_WEP_KEY_SIZE			26
#define MAX_PASSPHRASE_SIZE         64
#define MAX_NUM_WEP_KEYS             4
#define MAX_WPS_PIN_SIZE            32

#define DRIVER_UP               (0)
#define DRIVER_DOWN             (1)
#define READ_STATUS             (2)

/* Security modes */
#define SEC_MODE_OPEN 			(0)
#define SEC_MODE_WEP 			(1)
#define SEC_MODE_WPA 			(2)

#define getByte(n, data) ((data>>(8*n))&0xFF)

#define IS_DRIVER_READY             is_driver_initialized()
#define HANDLE_IOCTL(inout_param)   handle_ioctl(inout_param)
#define ATH_COMMIT(device)          ath_commit(device)
#define ATH_SET_MODE(device,mode)   ath_set_mode(device,mode)
#define ATH_SET_ESSID(device, essid) ath_set_essid(device, essid)
#define ATH_SET_SEC_TYPE(device, sectype)  ath_set_sec_type(device, sectype)
#define ATH_SET_PASSPHRASE(device, passphrase)  ath_set_passphrase(device, passphrase) 
#define ATH_GET_ESSID(device,essid)   ath_get_essid(device,essid)
#define ATH_NET_CONNECT(pNetparams)   NetConnect(pNetparams)
//#define SET_POWER_MODE(pwr_mode)      set_power_mode(pwr_mode)
#define TURN_LED_ON                       
#define TURN_LED_OFF                      
#define TEST_FLASH                    test_flash()
#define ATH_MEM_QUERY(argc,argv)           ath_mem_query(argc,argv)
#define ATH_REG_QUERY(argc,argv)           ath_reg_query(argc,argv)


/********************** Function Prototypes **************************************/

A_STATUS is_driver_initialized();
void SystemReset();
A_UINT32 ext_scan();
A_STATUS handle_ioctl(ATH_IOCTL_PARAM_STRUCT* inout_param);
//A_INT32 set_power_mode(char* pwr_mode);
A_INT32 test_flash(void);
A_INT32 ath_mem_query( A_INT32 argc, char* argv[]);
A_INT32 ath_reg_query( A_INT32 argc, char* argv[]);
A_INT32 wmi_set_scan(A_UINT32 dev_num, void *start_scan);
/*
 * huang
 */
A_INT32 wmi_set_scan_param(ENET_SCAN_LIST_PTR pEnetScanList, A_INT16 * num_scan);
//end
A_INT32 ath_driver_state( A_INT32 argc, char* argv[]);
A_STATUS ath_set_essid(A_UINT32 device, char* essid);
A_STATUS ath_set_sec_type(A_UINT32 device, char*  sec_type);
A_STATUS ath_set_passphrase(A_UINT32 device,char* passphrase);
A_STATUS ath_get_essid(A_UINT32 device, char*  essid);
A_INT32 get_power_mode(char* pwr_mode);
A_STATUS set_power_mode(A_BOOL pwr_mode, A_UINT8 pwr_module);
A_STATUS ath_commit(A_UINT32 device);
A_INT32 set_callback();
A_STATUS ath_set_mode(A_UINT32 device,char* mode);
A_UINT8 driver_status(A_UINT8 val);
A_INT32 CompleteWPS(ATH_NETPARAMS *pNetparams, A_UINT8 block, qcom_mode_t mode_flag);
A_INT32 NetConnect(ATH_NETPARAMS *pNetparams);
int handle_pmk(char* pmk);
int_32 wmi_iwconfig(int_32 argc, char_ptr argv[]);
A_STATUS is_driver_initialized();
A_STATUS handle_ioctl(ATH_IOCTL_PARAM_STRUCT* inout_param);
void Shell_Task(uint_32);
int_32 print_perf(int_32 argc, char_ptr argv[]);
void atheros_driver_setup(void);
int_32 wmi_ping(int_32 argc, char_ptr argv[] );
int_32 wmi_ping6(int_32 argc, char_ptr argv[] );
extern int_32 wps_query(uint_8 block);
int_32 ipconfig_query(int_32 argc, char_ptr argv[]);
void resetTarget();
A_INT32 set_callback();
int_32 wmiconfig_handler(int_32 argc, char_ptr argv[] );
A_INT32 set_wep_keys 
    (
        A_UINT32 dev_num,
        char* wep_key1,
        char* wep_key2,
        char* wep_key3,
        char* wep_key4,
        A_UINT32 key_len,
        A_UINT32 key_index        
    ); 

#if ENABLE_STACK_OFFLOAD
char *inet_ntoa( A_UINT32 addr, char *res_str );
char * inet6_ntoa(char* addr, char * str);
void ath_udp_echo (int_32 argc, char_ptr argv[]);
char * print_ip6(IP6_ADDR_T * addr, char * str);
A_INT32 ipconfig_static(A_INT32 argc, char* argv[]);
A_INT32 ipconfig_dhcp(A_INT32 argc, char* argv[]);
#endif
A_INT32 wmi_ping(A_INT32 argc, char* argv[] );
A_INT32 wmi_ping6(A_INT32 argc, char* argv[] );
uint_32 mystrtoul(const char* arg, const char* endptr, int base);
void application_frame_cb(A_VOID *ptr);
A_INT32 get_tx_status( );    
A_INT32 StartWPS(ATH_NETPARAMS *pNetparams, A_UINT8 use_pinmode, wps_scan_params* wpsScan_p );
_enet_handle get_active_device_handle();
extern A_INT32 get_active_device(void);
A_INT32 get_dev_mode();
//void app_time_delay(int msec);
A_INT32 ip_get_addr_for_host_name(char *hostname,A_UINT32 *v4addr,IP6_ADDR_T *ip6addr,A_UINT32 domain);
void clear_kf_profile();
void output_kf_pfm ();
/*********************** Extern Variables ******************************************/
extern uint_8 access_category;
extern A_UINT32 wifi_connected_flag;     //Flag to indicate WIFI connectivity status
extern uint_8 bench_quit;
extern _enet_handle    handle;
extern _enet_handle    enet_handle[2];
extern A_UINT8 original_ssid[];
extern wps_context_t wps_context;
extern int active_device;

#endif
