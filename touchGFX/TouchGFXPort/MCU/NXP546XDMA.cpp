#include <touchgfx/hal/OSWrappers.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/GPIO.hpp>
#include <cassert>

#include <platform/hal/nxp/mcu/LPC546x/NXP546XDMA.hpp>
#include <string.h>

#define DMA_ADDR(addr)      ((uint32_t) (addr))
dma_handle_t g_DMA_Handle;
dma_transfer_config_t transferConfig;

/* User callback function for DMA transfer. */
void DMA_Callback(dma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
  
  //DMA_AbortTransfer(handle);
  
  // This should be always true
  if (transferDone)
  {
    touchgfx::HAL::getInstance()->signalDMAInterrupt();
  }
}

NXP546XDMA::NXP546XDMA(dma_descriptor_t* lliMemory)
: DMA_Interface(dma_queue), MyLLI(lliMemory), dma_queue(queue_storage, sizeof(queue_storage) / sizeof(queue_storage[0])),
pBlitOp(0), numLines(0), use32Bit(0)
{
}


NXP546XDMA::~NXP546XDMA()
{
}

// Init the DMA
void NXP546XDMA::initialize()
{
  DMA_Init(DMA0);
  DMA_EnableChannel(DMA0, 0);
  DMA_CreateHandle(&g_DMA_Handle, DMA0, 0);
  DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
}

// Signal TGFX framework that the copy\fill operation has been finished.
void NXP546XDMA::signalDMAInterrupt(void)
{
  executeCompleted();
}

void NXP546XDMA::setupDataCopy(const touchgfx::BlitOp& blitOp)
{
  int i;
  uint32_t src, dst;
  
  numLines = blitOp.nLoops;
  
  use32Bit = (blitOp.nSteps % 2) == 0 &&                // Pixels pr line is even
             ((unsigned long)blitOp.pSrc & 3) == 0 &&   // src-address is 32bit-aligned
             ((unsigned long)blitOp.pDst & 3) == 0 &&   // dst-address us 32bit-aligned
             (blitOp.srcLoopStride % 2) == 0 &&         // src-stride is even
             (blitOp.dstLoopStride % 2) == 0;           // dst-stride is even
  
  src = DMA_ADDR(blitOp.pSrc);
  dst = DMA_ADDR(blitOp.pDst);
  
  // Create first descriptor and fill the transferConfig.xfercfg
  DMA_PrepareTransfer(&transferConfig,  (void*)src, 
                      (void*)dst, 
                      (use32Bit ? 4 : 2),
                      blitOp.nSteps*2,
                      kDMA_MemoryToMemory, 
                      &MyLLI[0]); 
  
  // If we have just one DMA operation
  if (blitOp.nLoops == 1)
  {
    transferConfig.xfercfg.intA = true; // Trigger interrupt after one operation
    transferConfig.xfercfg.swtrig = false;
    transferConfig.xfercfg.reload = false; // Reset to false after calling DMA_PrepareTransfer with non-null descriptor 
    transferConfig.nextDesc = NULL;
  }
  // If we have multiple DMA operations
  else
  {
    // Overwrite the transferConfig.xfercfg with the working values
    transferConfig.xfercfg.intA = false; // Do not trigger interrupt before the last transfer operation
    transferConfig.xfercfg.swtrig = 1;
    
    for (i=0; i <(blitOp.nLoops-1); i++)
    {
      DMA_CreateDescriptor(&MyLLI[i], 
                           &transferConfig.xfercfg,
                           (void*)(src + ((i+1) * blitOp.srcLoopStride * 2 )), 
                           (void*)(dst + ((i+1) * blitOp.dstLoopStride * 2)),
                           (void*)DMA_ADDR(MyLLI + i + 1));
    }
    ////  Last descriptors touch up
    MyLLI[i-1].xfercfg |= DMA_CHANNEL_XFERCFG_SETINTA_MASK; // Set the interrupt to be triggered for the last operation
    MyLLI[i-1].xfercfg &= ~DMA_CHANNEL_XFERCFG_RELOAD_MASK;
    MyLLI[i-1].linkToNextDesc = NULL;
  }
  
  DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig);
  DMA_StartTransfer(&g_DMA_Handle);
}

uint16_t DMAFillColor16;
uint32_t DMAFillColor32;


void NXP546XDMA::setupDataFill(const touchgfx::BlitOp& blitOp)
{
  int i;
  uint32_t src, dst;
  
  numLines = blitOp.nLoops;
  
  use32Bit = (blitOp.nSteps % 2) == 0 &&                // Pixels pr line is even
             ((unsigned long)blitOp.pSrc & 3) == 0 &&   // src-address is 32bit-aligned
             ((unsigned long)blitOp.pDst & 3) == 0 &&   // dst-address us 32bit-aligned
             (blitOp.srcLoopStride % 2) == 0 &&         // src-stride is even
             (blitOp.dstLoopStride % 2) == 0;           // dst-stride is even
  
  if (use32Bit)
  {
      DMAFillColor32 = blitOp.color << 16 | blitOp.color;
      src = DMA_ADDR(&DMAFillColor32);
  }
  else
  {
      DMAFillColor16 = blitOp.color;
      src = DMA_ADDR(&DMAFillColor16);
  }

  dst = DMA_ADDR(blitOp.pDst);
  
  // Create first descriptor and fill the transferConfig.xfercfg
  DMA_PrepareTransfer(&transferConfig,  (void*)src, 
                      (void*)dst, 
                      (use32Bit ? 4 : 2),
                      blitOp.nSteps*2,
                      kDMA_MemoryToMemory, 
                      &MyLLI[0]); 
  
  transferConfig.xfercfg.srcInc = 0;
  
  if (blitOp.nLoops == 1)
  {
    transferConfig.xfercfg.intA = true;
    transferConfig.xfercfg.swtrig = false;
    transferConfig.xfercfg.reload = false;
    transferConfig.nextDesc = NULL;
  }
  else
  {
    // Overwrite the transferConfig.xfercfg with the working values
    transferConfig.xfercfg.intA = false;
    transferConfig.xfercfg.swtrig = 1;
    
    for (i=0; i <(blitOp.nLoops-1); i++)
    {
      DMA_CreateDescriptor(&MyLLI[i], 
                           &transferConfig.xfercfg,
                           (void*)(src + ((i+1) * blitOp.srcLoopStride * 2 )), 
                           (void*)(dst + ((i+1) * blitOp.dstLoopStride * 2)),
                           (void*)DMA_ADDR(MyLLI + i + 1));
    }
    ////  Last descriptors touch up
    MyLLI[i-1].xfercfg |= DMA_CHANNEL_XFERCFG_SETINTA_MASK;
    MyLLI[i-1].xfercfg &= ~DMA_CHANNEL_XFERCFG_RELOAD_MASK;
    MyLLI[i-1].linkToNextDesc = NULL;
    
  }
  
  DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig);
  DMA_StartTransfer(&g_DMA_Handle);

}

