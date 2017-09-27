#include "main.h"
#include "enet_wifi.h"

//by colin
#if MQX_RTOS || MQX_LITE
#include "mqx.h"
#include "bsp.h"
#endif
#include "enet.h"
#include <a_types.h>
#include <a_osapi.h>
#include <atheros_wifi.h>
#include <atheros_wifi_api.h>
#include <port.h> //by colin

typedef struct storeblock_struct
{
   uint16_t                   TASK_NUMBER;
   uint16_t                      MEM_TYPE;
   uint32_t                      BLOCKSIZE;
   void*                        MEM_POOL_PTR;
   void*                        NEXTBLOCK;
   struct storeblock_struct * PREVBLOCK;
   uint32_t                      CHECKSUM;
#ifdef PSP_MEM_STOREBLOCK_ALIGNMENT
   uint32_t                      RESERVED[PSP_MEM_STOREBLOCK_ALIGNMENT];
#endif
   void*                        USER_AREA;

} STOREBLOCK_STRUCT, * STOREBLOCK_STRUCT_PTR;
#define FIELD_OFFSET(item,field) (uint32_t)&(((item _PTR_)0)->field)

#define GET_MEMBLOCK_PTR(addr) \
   (STOREBLOCK_STRUCT_PTR)((void *)(((unsigned char*)(addr) - \
      FIELD_OFFSET(STOREBLOCK_STRUCT,USER_AREA))))
	 
#define CALC_CHECKSUM(block) \
   ((STOREBLOCK_STRUCT_PTR)(block))->CHECKSUM = \
   (uint32_t) ( ((STOREBLOCK_STRUCT_PTR)(block))->BLOCKSIZE) + \
   (uint32_t) ( ((STOREBLOCK_STRUCT_PTR)(block))->PREVBLOCK) + \
   (uint32_t) ( ((STOREBLOCK_STRUCT_PTR)(block))->TASK_NUMBER) + \
   (uint32_t) ( ((STOREBLOCK_STRUCT_PTR)(block))->MEM_TYPE);


A_BOOL _mem_set_type
(
    void*   mem_ptr,
    uint16_t mem_type
)
{
    STOREBLOCK_STRUCT_PTR block_ptr;
		//sys_prot_t err;
	
    if (mem_ptr != NULL) {
        block_ptr = GET_MEMBLOCK_PTR(mem_ptr);
//    _int_enable(); Magicoe
		//err = sys_arch_protect();
        block_ptr->MEM_TYPE = mem_type;
        CALC_CHECKSUM(block_ptr);
//    _int_enable(); Magicoe
		//sys_arch_unprotect(err);
        return TRUE;
    }
    else {
        return FALSE;
    }
}