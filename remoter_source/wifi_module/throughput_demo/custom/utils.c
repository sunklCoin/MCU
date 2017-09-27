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

#include "main.h"
#include "throughput.h"
#include <stdlib.h>
#include <ctype.h>
char hextoa(int val);

//by colin
#include "port.h"

/*FUNCTION*-----------------------------------------------------------------
*
* Function Name  : mystrtoul
* Returned Value : unsigned long
* Comments       : coverts string to unsigned long
*
*END------------------------------------------------------------------*/

uint_32 mystrtoul(const char* arg, const char* endptr, int base)
{
	uint_32 res = 0;
	int i;
	
	if(arg){
		if(arg[0] == '0' && (arg[1] == 'x' || arg[1] == 'X')) arg+=2;
		
		i=0;
		while(arg[i] != '\0' && &arg[i] != endptr){
			if(arg[i] >= '0' && arg[i] <= '9'){
				res *= base;
				res += arg[i] - '0';
			}else if(arg[i] >= 'a' && arg[i] <= 'f' && base == 16){
				res *= base;
				res += arg[i] - 'a' + 10;
			}else if(arg[i] >= 'A' && arg[i] <= 'F' && base == 16){
				res *= base;
				res += arg[i] - 'A' + 10;
			}else{
				//error
				break;
			}
					
			i++;
		}
	
	}
	
	return res;
}


int_32 ath_inet_aton
   (
      const char*  name,
         /* [IN] dotted decimal IP address */
      A_UINT32*     ipaddr_ptr
         /* [OUT] binary IP address */
   )
{ /* Body */
   boolean     ipok = FALSE;
   uint_32     dots;
   uint_32     byte;
   _ip_address addr;

   addr = 0;
   dots = 0;
   for (;;) {

      if (!isdigit(*name)) break;

      byte = 0;
      while (isdigit(*name)) {
         byte *= 10;
         byte += *name - '0';
         if (byte > 255) break;
         name++;
      } /* Endwhile */
      if (byte > 255) break;
      addr <<= 8;
      addr += byte;

      if (*name == '.') {
         dots++;
         if (dots > 3) break;
         name++;
         continue;
      } /* Endif */

      if ((*name == '\0') && (dots == 3)) {
         ipok = TRUE;
      } /* Endif */

      break;

   } /* Endfor */

   if (!ipok) {
      return 0;
   } /* Endif */

   if (ipaddr_ptr) {
      *ipaddr_ptr = addr;
   } /* Endif */

   return -1;

} /* Endbody */



/************************************************************************
* NAME: inet_ntoa
*
* DESCRIPTION:The function converts an (IPv4) Internet network address 
*             into a string in Internet standard dotted format.
*************************************************************************/
char *inet_ntoa( A_UINT32 /*struct in_addr*/ addr, char *res_str )
{
    unsigned char *ptr;

    ptr = (unsigned char *) &addr;
    sprintf(res_str, "%d.%d.%d.%d", ptr[0], ptr[1], ptr[2], ptr[3]);

    return res_str;
}








char
hextoa(int val)
{
   val &= 0x0f;
   if(val < 10)
      return (char)(val + '0');
   else
      return (char)(val + 55);   /* converts 10-15 -> "A-F" */
}





int_32 parse_ipv4_ad(unsigned long * ip_addr,   /* pointer to IP address returned */
   unsigned *  sbits,      /* default subnet bit number */
   char *   stringin)
{
   int_32 error = -1;
   char *   cp;
   int   dots  =  0; /* periods imbedded in input string */
   int   number;
   union
   {
      unsigned char   c[4];
      unsigned long   l;
   } retval;

   cp = stringin;
   while (*cp)
   {
      if (*cp > '9' || *cp < '.' || *cp == '/')
         return(error);
      if (*cp == '.')dots++;
         cp++;
   }

   if ( dots < 1 || dots > 3 )
      return(error);

   cp = stringin;
   if ((number = atoi(cp)) > 255)
      return(error);

   retval.c[0] = (unsigned char)number;

   while (*cp != '.')cp++; /* find dot (end of number) */
      cp++;             /* point past dot */

   if (dots == 1 || dots == 2) retval.c[1] = 0;
      else
   {
      number = atoi(cp);
      while (*cp != '.')cp++; /* find dot (end of number) */
         cp++;             /* point past dot */
      if (number > 255) return(error);
         retval.c[1] = (unsigned char)number;
   }

   if (dots == 1) retval.c[2] = 0;
      else
   {
      number = atoi(cp);
      while (*cp != '.')cp++; /* find dot (end of number) */
         cp++;             /* point past dot */
      if (number > 255) return(error);
         retval.c[2] = (unsigned char)number;
   }

   if ((number = atoi(cp)) > 255)
      return(error);
   retval.c[3] = (unsigned char)number;

   if (retval.c[0] < 128) *sbits = 8;
      else if(retval.c[0] < 192) *sbits = 16;
      else *sbits = 24;

      *ip_addr = retval.l;
   return(0);
}





int ishexdigit(char digit)
{
   if((digit >= '0' ) && (digit <= '9'))
     return 1;

   digit |= 0x20;       /* mask letters to lowercase */
   if ((digit >= 'a') && (digit <= 'f'))
      return 1;
   else
      return 0;
}

unsigned int hexnibble(char digit)
{
   if (digit <= '9')
      return (digit-'0'    );

   digit &= ~0x20;   /* letter make uppercase */
   return (digit-'A')+10 ;
}

unsigned int atoh(char * buf)
{
   unsigned int retval = 0;
   char *   cp;
   char  digit;

   cp = buf;

   /* skip past spaces and tabs */
   while (*cp == ' ' || *cp == 9)
      cp++;

   /* while we see digits and the optional 'x' */
   while (ishexdigit(digit = *cp++) || (digit == 'x'))
   {
      /* its questionable what we should do with input like '1x234',
       * or for that matter '1x2x3', what this does is ignore all
       */
      if (digit == 'x')
         retval = 0;
      else
         retval = (retval << 4) + hexnibble(digit);
   }

   return retval;
}


#if ENABLE_STACK_OFFLOAD

void app_time_get_elapsed(TIME_STRUCT* time)
{
//by colin
#if 0
    uint_32 ticks_per_sec = _time_get_ticks_per_sec();    
    MQX_TICK_STRUCT tick_struct;
      
    //qosal_get_elapsed_tick_time(&tick_struct);
    _time_get_ticks(&tick_struct);
    
    time->SECONDS = tick_struct.TICKS[0] / ticks_per_sec;
    time->MILLISECONDS = (tick_struct.TICKS[0] - (time->SECONDS * ticks_per_sec)) * 1000 / ticks_per_sec;      
#else
    qosal_time_get_elapsed(time);
#endif
}

void app_time_get(TIME_STRUCT* time)
{
    app_time_get_elapsed(time);
}



char * print_ip6(IP6_ADDR_T * addr, char * str)
{
   int         i;
   unsigned short *   up;
   char *      cp;
   unsigned short     word;
   int         skip = 0;   /* skipping zeros flag */

   if(addr == NULL)     /* trap NULL pointers */
      return NULL;

   up = (unsigned short *)addr;
   cp = str;

   for(i = 0; i < 8; i++)  /* parse 8 16-bit words */
   {
#if MQX_VERSION == (402)   
      htons(&word,*up);
#else
      word = htons(*up);
#endif
      up++;

      /* If word has a zero value, see if we can skip it */
      if(word == 0)
      {
         /* if we haven't already skipped a zero string... */
         if(skip < 2)
         {
            /* if we aren't already skipping one, start */
            if(!skip)
            {
               skip++;
               if (i == 0)
                  *cp++ = ':';
            }
            continue;
         }
      }
      else
      {
         if(skip == 1)  /* If we were skipping zeros... */
         {
            skip++;        /* ...stop now */
            *cp++ = ':';   /* make an extra colon */
         }
      }

      if(word & 0xF000)
         *cp++ = hextoa(word >> 12);
      if(word & 0xFF00)
         *cp++ = hextoa((word & 0x0F00) >> 8);
      if(word & 0xFFF0)
         *cp++ = hextoa((word & 0x00F0) >> 4);
      *cp++ = hextoa(word & 0x000F);
      *cp++ = ':';
   }
   if(skip == 1)  /* were we skipping trailing zeros? */
   {
      *cp++ = ':';
      *cp = 0;
   }
   else
      *--cp = 0;  /* turn trailing colon into null */
   return str;
}









char * inet6_ntoa(char* addr, char * str)
{
   int         i;
   unsigned short *   up;
   char *      cp;
   unsigned short     word;
   int         skip = 0;   /* skipping zeros flag */

   if(addr == NULL)     /* trap NULL pointers */
      return NULL;

   up = (unsigned short *)addr;
   cp = str;

   for(i = 0; i < 8; i++)  /* parse 8 16-bit words */
   {
#if MQX_VERSION == (402)    
      htons(&word,(*up));
#else
      word = htons(*up);
#endif	  
      up++;

      /* If word has a zero value, see if we can skip it */
      if(word == 0)
      {
         /* if we haven't already skipped a zero string... */
         if(skip < 2)
         {
            /* if we aren't already skipping one, start */
            if(!skip)
            {
               skip++;
               if (i == 0)
                  *cp++ = ':';
            }
            continue;
         }
      }
      else
      {
         if(skip == 1)  /* If we were skipping zeros... */
         {
            skip++;        /* ...stop now */
            *cp++ = ':';   /* make an extra colon */
         }
      }

      if(word & 0xF000)
         *cp++ = hextoa(word >> 12);
      if(word & 0xFF00)
         *cp++ = hextoa((word & 0x0F00) >> 8);
      if(word & 0xFFF0)
         *cp++ = hextoa((word & 0x00F0) >> 4);
      *cp++ = hextoa(word & 0x000F);
      *cp++ = ':';
   }
   if(skip == 1)  /* were we skipping trailing zeros? */
   {
      *cp++ = ':';
      *cp = 0;
   }
   else
      *--cp = 0;  /* turn trailing colon into null */
   return str;
}


int
Inet6Pton(char * src, void * dst)
{
   char *   cp;      /* char after previous colon */
   A_UINT16 *      dest;    /* word pointer to dst */
   int            colons;  /* number of colons in src */
   int            words;   /* count of words written to dest */

   /* count the number of colons in the address */
   cp = src;
   colons = 0;
   while(*cp)
   {
      if(*cp++ == ':') colons++;
   }

   if(colons < 2 || colons > 7)
   {
      printf("must have 2-7 colons");
      return 1;
   }

   /* loop through address text, parseing 16-bit chunks */
   cp = src;
   dest = dst;
   words = 0;

   if(*cp == ':') /* leading colon has implied zero, e.g. "::1" */
   {
      *dest++ = 0;
      words++;
      cp++;       /* bump past leading colon, eg ":!" */
   }

   while(*cp > ' ')
   {
      if(words >= 8)
      {
	 printf("***  inet_pton: logic error?\n");
         return 1;
      }
      if(*cp == ':')   /* found a double-colon? */
      {
         int i;
         for(i = (8 - colons); i > 0; i--)
         {
            *dest++ = 0;   /* add zeros to dest address */
            words++;       /* count total words */
         }
         cp++;             /* bump past double colon */
         if(*cp <= ' ')    /* last colon was last char? */
         {
            *dest++ = 0;   /* add one final zero */
            words++;       /* count total words */
         }
      }
      else
      {
         A_UINT16 wordval;
         A_UINT16 temp;
         wordval = atoh(cp);
	 temp = wordval;
#if MQX_VERSION == (402)	 
         htons(&wordval,temp);    /* get next 16 bit word */
#else
         wordval = htons(temp);    /* get next 16 bit word */
#endif
         if((wordval == 0) && (*cp != '0'))  /* check format */
         {
            printf("must be hex numbers or colons \n");
            return 1;
         }
         *dest++ = wordval;
         words++;       /* count total words set in dest */
         cp = strchr((char *)cp, ':');   /* find next colon */
         if(cp)                  /* bump past colon */
            cp++;
         else                 /* no more colons? */
            break;            /* done with parsing */
      }
   }
   if(words != 8)
   {
      printf("too short - missing colon?\n");
      return 1;
   }
   return 0;
}

#endif
