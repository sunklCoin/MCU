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

#ifndef _THROUGHPUT_H_

#define _THROUGHPUT_H_

#if !ENABLE_STACK_OFFLOAD
#include <rtcs.h>
#endif

#define USE_ATH_CHANGES                 1	 // Macro to control Atheros specific changes to FNET tools	  
#define ATH_RECV_TIMEOUT  		(60000)
#define TX_DELAY_INTERVAL 		500
#define TCP_TXTEST_TX_BUF_SIZE          4096	 // TCP Transmit Test TX Buffer
#define TCP_TXTEST_HT_TX_BUF_SIZE       7360	 // High Throughput buffer, only used in case of single stream	
#define TCP_TXTEST_RX_BUF_SIZE          1460	 // TCP Transmit Test RX Buffer
#define TCP_RXTEST_TX_BUF_SIZE          1460	 // TCP Receive Test TX Buffer 
#define TCP_RXTEST_RX_BUF_SIZE            2920	 // TCP Receive Test RX Buffer 	
#define TCP_RXTEST_HT_RX_BUF_SIZE         2920*3 // High Throughput buffer, only used in case of single stream
#define MAX_END_MARK_RETRY                50   // Max number of End Mark retries in UDP Tx test
#define MSEC_HEARTBEAT 			  10000
#define MAX_TASKS_ALLOWED 		  2	 // For now, we allow ony 2 tasks
#define MAX_STREAMS_ALLOWED 		  2	 // Max number of allowed TCP/UDP streams- limited by memory
#define TCP_CONNECTION_WAIT_TIME          50 
#define UDP_CONNECTION_WAIT_TIME          500
#define UDP_CONNECTION_WAIT_TIME_MULTI_SOCK 50
#define MAX_ARGC 		          (19)
#define MAX_STRLEN 			  (64+1)
#define CFG_PORT                     	 (7007)
#define CFG_PACKET_SIZE_MAX_TX           (1576) /* Defines size of Application and Socket TX&RX buffers.*/
#define CFG_PACKET_SIZE_MAX_RX           (1556) /* Defines size of Application and Socket TX&RX buffers.*/
#define CFG_TX_PACKET_SIZE_DEFAULT       (1400)
#define END_OF_TEST_CODE                 (0xAABBCCDD) 
#define MAX_END_MARK_RETRY                50   // Max number of End Mark retries in UDP Tx test
#define TX_DELAY_INTERVAL 		 500
#define CFG_MAX_IPV6_PACKET_SIZE         1220
/* Socket Tx&Rx buffer sizes. */
#define CFG_SOCKET_BUF_SIZE      		(CFG_PACKET_SIZE_MAX_RX)
#define CFG_BUFFER_SIZE         		(CFG_PACKET_SIZE_MAX_RX)
#define ATH_RECV_TIMEOUT  		(60000)
#define TX_DELAY			 5
#define SMALL_TX_DELAY                   1
#define _ip_address                                A_UINT32 
#define MAX_STREAMS_ALLOWED 		 2	 // Max number of allowed TCP/UDP streams- limited by memory
#define MAX_SSL_INST                 1
#define SSL_SERVER_INST              0
#define SSL_CLIENT_INST              0
#define SSL_INBUF_SIZE               4500
#define SSL_OUTBUF_SIZE              3000

/*structure to manage stats received from peer during UDP traffic test*/
typedef struct stat_packet
{
    A_UINT32 bytes;  
    A_UINT32 kbytes;
    A_UINT32 msec;
    A_UINT32 numPackets;
}stat_packet_t;


/* IP header's structure */
typedef PREPACK struct ipheader_s {
    A_UINT8      iph_ihl:4, iph_ver:4;
    A_UINT8      iph_tos;
    A_UINT16     iph_len;
    A_UINT16     iph_ident;
    A_UINT16     iph_offset;
    A_UINT8      iph_ttl;
    A_UINT8      iph_protocol;
    A_UINT16     iph_chksum;
    A_UINT32     iph_sourceip;
    A_UINT32     iph_destip;
}POSTPACK ip_header;

/**************************************************************************/ /*!
 * TX/RX Test parameters
 ******************************************************************************/
typedef struct transmit_params
{
    _ip_address ip_address;  
    unsigned char v6addr[16];
    unsigned short port;
    int packet_size;
    int tx_time;
    int packet_number;
    int interval;
    int raw_mode;   // 0- raw  1 - raw with ip header
	int ip_hdr_inc; 
    unsigned short test_mode;
    unsigned short multicast_if;
    _ip_address local_address;
    unsigned char local_v6addr[16];
}TX_PARAMS;

typedef struct receive_params
{     
    int raw_mode;   // 0- raw  1 - raw with ip header
    unsigned short port;
#if ENABLE_STACK_OFFLOAD
    IP_MREQ_T group;
    IPV6_MREQ_T group6;
    unsigned short mcastEnabled;    
    unsigned short local_if;
    _ip_address local_address;
    unsigned char local_v6addr[16];
    int ip_hdr_inc; 
#else
    struct ip_mreq group;
#endif  
}RX_PARAMS;


#if ENABLE_HTTP_CLIENT
typedef struct httpc_params
{
    A_UINT32          command;
    A_UINT8           url[64];
    A_UINT8           data[128];
}HTTPC_PARAMS;



#endif /* ENABLE_HTTP_CLIENT */


/************************************************************************
*    Benchmark server control structure.
*************************************************************************/

typedef struct throughput_cxt
{
    int sock_local;                /* Listening socket.*/
    int sock_peer;                  /* Foreign socket.*/    
    char* buffer;    
    TIME_STRUCT first_time;         //Test start time
    TIME_STRUCT last_time;          //Current time
    unsigned long long bytes;		 //Number of bytes received in current test
    unsigned long kbytes;            //Number of kilo bytes received in current test
    unsigned long last_bytes;        //Number of bytes received in the previous test
    unsigned long last_kbytes;
    unsigned long sent_bytes;
    A_UINT32     pkts_recvd;
    A_UINT32     pkts_expctd;
    A_UINT32     last_interval;
    union params_u {
    TX_PARAMS    tx_params;
    RX_PARAMS    rx_params;
    } params;
    A_UINT8      test_type; 
}THROUGHPUT_CXT;

typedef struct end_of_test{
  int code;
  int packet_count;
} EOT_PACKET;



enum test_type
{
	UDP_TX,   //UDP Transmit (Uplink Test)
	UDP_RX,   //UDP Receive (Downlink Test)
	TCP_TX,   //TCP Transmit (Uplink Test)
	TCP_RX,   //TCP Receive (Downlink Test)
	RAW_TX,   //RAW Transmit (Uplink Test)
	RAW_RX,   //RAW Receive (Downlink Test)
        SSL_TX,   //SSL Transmit (Uplink Test)
        SSL_RX    //SSL Receive (Downlink Test)
};

enum Test_Mode
{
	TIME_TEST,
	PACKET_TEST
};

A_INT32 rx_command_parser(A_INT32 argc, char_ptr argv[] );
A_INT32 tx_command_parser(A_INT32 argc, char_ptr argv[] );
#if ENABLE_STACK_OFFLOAD
A_INT32 rx_command_parser_multi_socket(A_INT32 argc, char_ptr argv[] );
A_INT32 tx_command_parser_multi_socket(A_INT32 argc, char_ptr argv[] );
#endif



enum 
{
   
   SWITCH_TASK=1,
   SHELL_TASK,
   LOGGING_TASK,
   USB_TASK,
   ALIVE_TASK,
   WMICONFIG_TASK1,
   WMICONFIG_TASK2

};


enum Raw_Mode
{
	IP_RAW = 1,
	ETH_RAW
};




int_32 worker_cmd_handler(int_32 argc, char_ptr argv[]);
int_32 worker_cmd_quit(int_32 argc, char_ptr argv[]);
A_INT32 setBenchMode(A_INT32 argc, char_ptr argv[] );
int_32 test_for_quit(void);
uint_32 check_test_time(THROUGHPUT_CXT *p_tCxt);
int_32 test_for_delay(TIME_STRUCT *pCurr, TIME_STRUCT *pBase);
char *inet_ntoa( A_UINT32 /*struct in_addr*/ addr, char *res_str );
void wmiconfig_Task2(uint_32);
void wmiconfig_Task1(uint_32);
int ishexdigit(char digit);
unsigned int hexnibble(char digit);
unsigned int atoh(char * buf);
int_32 ath_inet_aton
   (
      const char*  name,
         /* [IN] dotted decimal IP address */
      A_UINT32*     ipaddr_ptr
         /* [OUT] binary IP address */
   );
int_32 parse_ipv4_ad(unsigned long * ip_addr,   /* pointer to IP address returned */
   unsigned *  sbits,      /* default subnet bit number */
   char *   stringin);


#if ENABLE_STACK_OFFLOAD

char * print_ip6(IP6_ADDR_T * addr, char * str);
char * inet6_ntoa(char* addr, char * str);
int Inet6Pton(char * src, void * dst);

A_INT32 httpc_command_parser(A_INT32 argc, char_ptr argv[]);


#if ENABLE_SSL
typedef struct ssl_inst
{
    SSL_CTX*     sslCtx;
    SSL*         ssl;
    SSL_CONFIG   config;
    A_UINT8      config_set;
    SSL_ROLE_T   role;
} SSL_INST;

extern SSL_INST ssl_inst[MAX_SSL_INST];
extern A_UINT8 *ssl_cert_data_buf;
extern A_UINT16 ssl_cert_data_buf_len;
extern A_UINT8 const *ssl_default_cert;
extern const A_UINT16 ssl_default_cert_len;
extern A_UINT8 const *ssl_default_calist;
extern const A_UINT16 ssl_default_calist_len;

A_INT32 ssl_get_cert_handler(A_INT32 argc, char* argv[]);
A_INT32 https_server_handler(A_INT32 argc, char* argv[]);
A_INT32 https_client_handler(A_INT32 argc, char* argv[]);

#endif


#endif

#endif
