#ifndef __port_h__
#define __port_h__
/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
* Copyright 2004-2008 Embedded Access Inc.
* Copyright 1989-2008 ARC International
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
*
*   This file contains the defines and data structure definitions that
*   reperesent ethernet packets.
*
*
*END************************************************************************/

/*--------------------------------------------------------------------------*/
/*
 *                  ENDIAN SWAP MACROS AND PROTOTYPES
 */
// #include <core_cm4.h>
// #include <core_cmInstr.h>
 
#define BIG_ENDIAN    (0)
#define LITTLE_ENDIAN (1)


#define BSP_ENET_DEVICE_COUNT 2

#define PSP_ENDIAN LITTLE_ENDIAN

/* Macros for converting values between host and big-/little-endian byte order */
#define _PSP_SWAP2BYTE(n) ((((n) & 0x00FF) << 8) | (((n) & 0xFF00) >> 8))
#define _PSP_SWAP4BYTE(n) ((((n) & 0x000000FF) << 24) | (((n) & 0x0000FF00) << 8) | (((n) & 0x00FF0000) >> 8) | (((n) & 0xFF000000) >> 24))

#if 0
extern uint16_t _psp_swap2byte(uint16_t n);
extern uint32_t _psp_swap4byte(uint32_t n);

#define _PSP_SWAP2BYTE(n)   _psp_swap2byte(n)
#define _PSP_SWAP4BYTE(n)   _psp_swap4byte(n)
#endif

#if (PSP_ENDIAN == BIG_ENDIAN)
    #define HOST_TO_BE_SHORT(n)           (n)
    #define HOST_TO_BE_SHORT_CONST(n)     (n)
    #define HOST_TO_LE_SHORT(n)           _PSP_SWAP2BYTE(n)
    #define HOST_TO_LE_SHORT_CONST(n)     _PSP_SWAP2BYTE_CONST(n)
    #define SHORT_BE_TO_HOST(n)           (n)
    #define SHORT_BE_TO_HOST_CONST(n)     (n)
    #define SHORT_LE_TO_HOST(n)           _PSP_SWAP2BYTE(n)
    #define SHORT_LE_TO_HOST_CONST(n)     _PSP_SWAP2BYTE_CONST(n)

    #define HOST_TO_BE_LONG(n)            (n)
    #define HOST_TO_BE_LONG_CONST(n)      (n)
    #define HOST_TO_LE_LONG(n)            _PSP_SWAP4BYTE(n)
    #define HOST_TO_LE_LONG_CONST(n)      _PSP_SWAP4BYTE_CONST(n)
    #define LONG_BE_TO_HOST(n)            (n)
    #define LONG_BE_TO_HOST_CONST(n)      (n)
    #define LONG_LE_TO_HOST(n)            _PSP_SWAP4BYTE(n)
    #define LONG_LE_TO_HOST_CONST(n)      _PSP_SWAP4BYTE_CONST(n)

#else /* (PSP_ENDIAN == BIG_ENDIAN) */

    #define HOST_TO_BE_SHORT(n)           _PSP_SWAP2BYTE(n)
    #define HOST_TO_BE_SHORT_CONST(n)     _PSP_SWAP2BYTE_CONST(n)
    #define HOST_TO_LE_SHORT(n)           (n)
    #define HOST_TO_LE_SHORT_CONST(n)     (n)
    #define SHORT_BE_TO_HOST(n)           _PSP_SWAP2BYTE(n)
    #define SHORT_BE_TO_HOST_CONST(n)     _PSP_SWAP2BYTE_CONST(n)
    #define SHORT_LE_TO_HOST(n)           (n)
    #define SHORT_LE_TO_HOST_CONST(n)     (n)

    #define HOST_TO_BE_LONG(n)            _PSP_SWAP4BYTE(n)
    #define HOST_TO_BE_LONG_CONST(n)      _PSP_SWAP4BYTE_CONST(n)
    #define HOST_TO_LE_LONG(n)            (n)
    #define HOST_TO_LE_LONG_CONST(n)      (n)
    #define LONG_BE_TO_HOST(n)            _PSP_SWAP4BYTE(n)
    #define LONG_BE_TO_HOST_CONST(n)      _PSP_SWAP4BYTE_CONST(n)
    #define LONG_LE_TO_HOST(n)            (n)
    #define LONG_LE_TO_HOST_CONST(n)      (n)

#endif /* (PSP_ENDIAN == MQX_BIG_ENDIAN) */

/* Host to network / network to host conversion functions conforming to POSIX API */
#define htons(x)       HOST_TO_BE_SHORT(x)
#define htonl(x)       HOST_TO_BE_LONG(x)

#define ntohs(x)       SHORT_BE_TO_HOST(x)
#define ntohl(x)       LONG_BE_TO_HOST(x)

#endif
/* EOF */
