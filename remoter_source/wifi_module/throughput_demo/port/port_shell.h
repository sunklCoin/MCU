/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved                       
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
* All Rights Reserved
*
*************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: shell.h$
* $Version : 3.8.23.0$
* $Date    : Jun-7-2012$
*
* Comments:
*
*   This file contains the shell API.
*
*END************************************************************************/

#ifndef __port_shell_h__
#define __port_shell_h__

/** MGCT: <category name="Shell Settings"> */

/*
** MGCT: <option type="bool"/>
*/  
#ifndef SHELLCFG_USES_MFS
#define SHELLCFG_USES_MFS   1
#endif

/*
** MGCT: <option type="bool"/>
*/  
#ifndef SHELLCFG_USES_RTCS
#define SHELLCFG_USES_RTCS  1
#endif

/** MGCT: </category> */

#ifdef BSP_DEFAULT_ENET_DEVICE
#include <sh_enet.h>
#endif

#define SHELL_MAX_ARGS       16

#define SHELL_EXIT_SUCCESS   0
#define SHELL_EXIT_ERROR    -1

#define SHELL_MAX_DEVLEN    8
#define SHELL_MAX_FILELEN   256
#define SHELL_PATHNAME_LEN  260
#define SHELL_BLOCK_SIZE    128

#define MEM_TYPE_SHELL_BASE                   ( (IO_SHELL_COMPONENT) << (MEM_TYPE_COMPONENT_SHIFT))
#define MEM_TYPE_SHELL_CONTEXT                (MEM_TYPE_SHELL_BASE+1)

#define hexnum(c)  ((c<='9')?(c-'0'):((c<='F')?(c-'A'+10) :(c-'a'+10))) 

//#define SHELL_COMMAND(cmd) { #cmd, Shell_##cmd },  //by colin

//typedef struct shell_command_struct  {
//   char *  COMMAND;
//   int32_t      (*SHELL_FUNC)(int32_t argc, char * argv[]);
//} SHELL_COMMAND_STRUCT, * SHELL_COMMAND_PTR; 


///*
//** Function prototypes 
//*/

//#ifdef __cplusplus
//extern "C" {
//#endif

//extern int opterr;
//extern int optind;
//extern int optopt;
//extern char *optarg;
//extern const SHELL_COMMAND_STRUCT Shell_commands[];

//extern int32_t   Shell( const SHELL_COMMAND_STRUCT[], char * );
//extern int32_t   Shell_getopt(int argc, char** argv, char* opts);
//extern int32_t   Shell_parse_command_line( char * command_line_ptr, char * argv[] );
//extern unsigned long  Shell_parse_number( char * arg, uint32_t * num_ptr);
//extern unsigned long  Shell_check_help_request(int32_t argc, char * argv[], unsigned long * short_ptr );
//extern unsigned long  Shell_parse_uint32_t( char * arg, uint32_t * num_ptr);
//extern unsigned long  Shell_parse_uint_16( char * arg, uint16_t * num_ptr);
//extern unsigned long  Shell_parse_int32_t( char * arg, int32_t * num_ptr);
//extern unsigned long    Shell_parse_hexnum( char * arg, uint32_t * num_ptr);
//extern void     Shell_create_prefixed_filename( char * new_ptr, char * in_ptr,  pointer argv);
//extern int32_t   Shell_abort(int32_t argc, char * argv[] ); 
//extern int32_t   Shell_command_list(int32_t argc, char * argv[] );
//extern int32_t   Shell_exit(int32_t argc, char * argv[] );
//extern int32_t   Shell_help(int32_t argc, char * argv[] ); 
//extern int32_t   Shell_kill(int32_t argc, char * argv[] ); 
//extern int32_t   Shell_pause(int32_t argc, char * argv[] );
//extern int32_t   Shell_tad(int32_t argc, char * argv[] );
//extern int32_t   Shell_sh(int32_t argc, char * argv[] );
//extern int32_t   Shell_md(int32_t argc, char * argv[] );

#ifdef __cplusplus
}
#endif

#endif
/*EOF */
