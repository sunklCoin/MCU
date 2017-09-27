/*HEADER**********************************************************************
*
* Copyright 2009 Freescale Semiconductor, Inc.
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
*   This file contains the Ethernet IOCTL implementation
*
*
*END************************************************************************/
//by colin
#if MQX_RTOS || MQX_LITE
#include <mqx.h>
#include <bsp.h>
#endif

#include "enet.h"
#include "enetprv.h"
#include "sys_arch.h"
#if 0
uint16_t _psp_swap2byte(uint16_t n)
{
    uint16_t ret;

    __asm volatile ("rev16 ret, n");
    return(ret);
}

/*!
 * \brief Swap 4 bytes
 * 
 * \param n 
 *
 * \return uint32_t
 */

uint32_t _psp_swap4byte(uint32_t n)
{
    uint32_t ret;

    __asm volatile ("rev ret, n");
    return(ret);
}
#endif

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : ENET_max_framesize
*  Returned Value :
*  Comments       :
*
*     Calculate maximum frame size based on user parameters.
*  If the user specifies large buffers, then the max will be the largest
*  frame size (based on vlan).
*
*
*END*-----------------------------------------------------------------*/

uint16_t ENET_max_framesize(uint16_t best_buffer_size, uint16_t num_large_buffers, bool vlan)
{

  if (num_large_buffers || (best_buffer_size==0)) {
      if (vlan) {
         return ENET_FRAMESIZE_VLAN;
      } else {
         return ENET_FRAMESIZE;
      }
   } else {
      return best_buffer_size;
   }
}



/*---------------------------------------------------------------------------*
 * Routine:  sys_sem_new
 *---------------------------------------------------------------------------*
 * Description:
 *      Creates and returns a new semaphore. The "ucCount" argument specifies
 *      the initial state of the semaphore.
 *      NOTE: Currently this routine only creates counts of 1 or 0
 * Inputs:
 *      sys_mbox_t mbox         -- Handle of mailbox
 *      u8_t ucCount						-- Initial ucCount of semaphore (1 or 0)
 * Outputs:
 *      sys_sem_t               -- Created semaphore or 0 if could not create.
 *---------------------------------------------------------------------------*/
int8_t sys_sem_new( sys_sem_t *pxSemaphore, uint8_t ucCount )
{
  int8_t xReturn = ERR_MEM;

  vSemaphoreCreateBinary( ( *pxSemaphore ) );

  if( *pxSemaphore != NULL ) {
    if( ucCount == 0U ) {
      xSemaphoreTake( *pxSemaphore, 1UL );
    }
    xReturn = ERR_OK;
    SYS_STATS_INC_USED( sem );
  } else {
    SYS_STATS_INC( sem.err );
  }

  return xReturn;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_arch_sem_wait
 *---------------------------------------------------------------------------*
 * Description:
 *      Blocks the thread while waiting for the semaphore to be
 *      signaled. If the "timeout" argument is non-zero, the thread should
 *      only be blocked for the specified time (measured in
 *      milliseconds).
 *
 *      If the timeout argument is non-zero, the return value is the number of
 *      milliseconds spent waiting for the semaphore to be signaled. If the
 *      semaphore wasn't signaled within the specified time, the return value is
 *      SYS_ARCH_TIMEOUT. If the thread didn't have to wait for the semaphore
 *      (i.e., it was already signaled), the function may return zero.
 *
 *      Notice that lwIP implements a function with a similar name,
 *      sys_sem_wait(), that uses the sys_arch_sem_wait() function.
 * Inputs:
 *      sys_sem_t sem           -- Semaphore to wait on
 *      u32_t timeout           -- Number of milliseconds until timeout
 * Outputs:
 *      u32_t                   -- Time elapsed or SYS_ARCH_TIMEOUT.
 *---------------------------------------------------------------------------*/
uint32_t sys_arch_sem_wait( sys_sem_t *pxSemaphore, uint32_t ulTimeout )
{
	portTickType xStartTime, xEndTime, xElapsed;
	unsigned long ulReturn;

	xStartTime = xTaskGetTickCount();

	if( ulTimeout != 0UL ) {
		if( xSemaphoreTake( *pxSemaphore, ulTimeout ) == pdTRUE ) {
			xEndTime = xTaskGetTickCount();
			xElapsed = (xEndTime - xStartTime) * portTICK_RATE_MS;
			ulReturn = xElapsed;
		} else {
			ulReturn = SYS_ARCH_TIMEOUT;
		}
	} else {
		while( xSemaphoreTake( *pxSemaphore, portMAX_DELAY ) != pdTRUE );
		xEndTime = xTaskGetTickCount();
		xElapsed = ( xEndTime - xStartTime ) * portTICK_RATE_MS;

		if( xElapsed == 0UL ) {
			xElapsed = 1UL;
		}

		ulReturn = xElapsed;
	}

	return ulReturn;
}

/**
 * @brief	Create a new mutex
 * @param	pxMutex pointer to the mutex to create
 * @return	a new mutex
 */
int8_t sys_mutex_new( sys_mutex_t *pxMutex )
{
  int8_t xReturn = ERR_MEM;

	*pxMutex = xSemaphoreCreateMutex();

	if( *pxMutex != NULL ) {
		xReturn = ERR_OK;
		SYS_STATS_INC_USED( mutex );
	} else {
		SYS_STATS_INC( mutex.err );
	}

	return xReturn;
}

/** Lock a mutex
 * @param pxMutex the mutex to lock */
int8_t sys_mutex_lock( sys_mutex_t *pxMutex )
{
  while( xSemaphoreTake( *pxMutex, portMAX_DELAY ) != pdPASS );
  return ERR_OK;
}

/** Unlock a mutex
 * @param pxMutex the mutex to unlock */
int8_t sys_mutex_unlock(sys_mutex_t *pxMutex )
{
  xSemaphoreGive( *pxMutex );
  return ERR_OK;
}


/** Delete a semaphore
 * @param pxMutex the mutex to delete */
int8_t sys_mutex_free( sys_mutex_t *pxMutex )
{
  SYS_STATS_DEC( mutex.used );
  vQueueDelete( *pxMutex );
  return ERR_OK;
}


/*---------------------------------------------------------------------------*
 * Routine:  sys_sem_signal
 *---------------------------------------------------------------------------*
 * Description:
 *      Signals (releases) a semaphore
 * Inputs:
 *      sys_sem_t sem           -- Semaphore to signal
 *---------------------------------------------------------------------------*/
void sys_sem_signal( sys_sem_t *pxSemaphore )
{
  xSemaphoreGive( *pxSemaphore );
}

void sys_sem_clear( sys_sem_t *pxSemaphore, uint32_t time)
{
  xSemaphoreTake( *pxSemaphore, time );
}


/*---------------------------------------------------------------------------*
 * Routine:  sys_sem_free
 *---------------------------------------------------------------------------*
 * Description:
 *      Deallocates a semaphore
 * Inputs:
 *      sys_sem_t sem           -- Semaphore to free
 *---------------------------------------------------------------------------*/
void sys_sem_free( sys_sem_t *pxSemaphore )
{
	SYS_STATS_DEC(sem.used);
	vQueueDelete( *pxSemaphore );
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_init
 *---------------------------------------------------------------------------*
 * Description:
 *      Initialize sys arch
 *---------------------------------------------------------------------------*/
void sys_init(void)
{
}

uint32_t sys_now(void)
{
	return xTaskGetTickCount();
}

/* EOF */
