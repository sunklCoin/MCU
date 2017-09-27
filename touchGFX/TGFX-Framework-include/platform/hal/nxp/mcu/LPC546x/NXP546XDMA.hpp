/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.6.0 standard distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * Copyright (C) 2014-2016 Draupner Graphics A/S <http://www.touchgfx.com>.
 * All rights reserved.
 *
 * TouchGFX is protected by international copyright laws and the knowledge of
 * this source code may not be used to write a similar product. This file may
 * only be used in accordance with a license and should not be re-
 * distributed in any way without the prior permission of Draupner Graphics.
 *
 * This is licensed software, any use must strictly comply with the signed
 * license agreement and associated Terms & Conditions.
 *
 * Standard Terms & Conditions can be seen on www.touchgfx.com
 *
 * @section Disclaimer
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
 * no obligation to support this software. Draupner Graphics A/S is providing
 * the software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Draupner Graphics A/S can not be held liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this software.
 *
 *****************************************************************************/
#ifndef NXP546XDMA_HPP
#define NXP546XDMA_HPP

#include <touchgfx/hal/DMA.hpp>
#include "board.h"
#include "fsl_dma.h"
  
#ifndef NO_USING_NAMESPACE_TOUCHGFX
using namespace touchgfx;
#endif

/**
 * @class NXP546XDMA NXP546XDMA.hpp platform/hal/nxp/mcu/LPC43xx/NXP546XDMA.hpp
 *
 * @brief This class specializes DMA_Interface for the NXP LPC43XX processors.
 *
 *        This class specializes DMA_Interface for the NXP LPC43XX processors.
 *
 * @sa touchgfx::DMA_Interface
 */
class NXP546XDMA : public touchgfx::DMA_Interface
{
    /**
     * @typedef touchgfx::DMA_Interface Base
     *
     * @brief Defines an alias representing the base.
     *
     *        Defines an alias representing the base.
     */
    typedef touchgfx::DMA_Interface Base;

public:
    /**
     * @fn NXP546XDMA::NXP546XDMA(GPDMA_LLI_Type* lliMemory);
     *
     * @brief Constructor.
     *
     *        Constructor.
     *
     * @param [in,out] lliMemory Pointer to an array containing the number of elements equivalent
     *                           to the height of the display in pixels.
     */
    NXP546XDMA(dma_descriptor_t* lliMemory);

    /**
     * @fn virtual NXP546XDMA::~NXP546XDMA();
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~NXP546XDMA();

    /**
     * @fn virtual touchgfx::BlitOperations NXP546XDMA::getBlitCaps()
     *
     * @brief Gets the blit operation capabilities of this DMA.
     *
     *        Gets the blit operation capabilities of this DMA.
     *
     * @return BlitOperations the blit operation capabilities of this DMA (BLIT_OP_COPY).
     */
    virtual touchgfx::BlitOperations getBlitCaps()
    {
        return static_cast<touchgfx::BlitOperations>(touchgfx::BLIT_OP_COPY | touchgfx::BLIT_OP_FILL);
    }

    /**
     * @fn virtual void NXP546XDMA::initialize();
     *
     * @brief Perform hardware specific initialization.
     *
     *        Perform hardware specific initialization.
     */
    virtual void initialize();

    /**
     * @fn uint8_t NXP546XDMA::isDmaQueueEmpty();
     *
     * @brief Checks if DMA queue is empty.
     *
     *        Checks if DMA queue is empty.
     *
     * @return 1 if DMA queue is empty, else 0.
     */
    uint8_t isDmaQueueEmpty();

    /**
     * @fn virtual void NXP546XDMA::signalDMAInterrupt();
     *
     * @brief Raises a Dma interrupt signal.
     *
     *        Raises a Dma interrupt signal.
     */
    virtual void signalDMAInterrupt();

protected:
    /**
     * @fn virtual void NXP546XDMA::setupDataCopy(const touchgfx::BlitOp& blitOp);
     *
     * @brief Configures the DMA for copying data to the frame-buffer.
     *
     *        Configures the DMA for copying data to the frame-buffer.
     *
     * @param blitOp Details on the copy to perform.
     */
    virtual void setupDataCopy(const touchgfx::BlitOp& blitOp);

    /**
     * @fn virtual void NXP546XDMA::setupDataFill(const touchgfx::BlitOp& blitOp);
     *
     * @brief Configures the DMA for "filling" the frame-buffer with a single color.
     *
     *        Configures the DMA for "filling" the frame-buffer with a single color.
     *
     * @param blitOp Details on the "fill" to perform.
     */
    virtual void setupDataFill(const touchgfx::BlitOp& blitOp);


private:
    /**
     * @fn NXP546XDMA::NXP546XDMA();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    NXP546XDMA();

    /**
     * @fn bool NXP546XDMA::finished();
     *
     * @brief Interrupt call-back: Used for DMA transfers.
     *
     *        Interrupt call-back: Used for DMA transfers, which are known to complete the
     *        current BlitOp processing.
     *
     * @return true always (since the BlitOp processing has been completed).
     */
    bool finished();

    static const unsigned int channel = 0; ///< The used DMA channel. Only channel 0 supports 2D transfers

    int cnt1;
    int cnt2;

    dma_descriptor_t*           MyLLI;
    touchgfx::LockFreeDMA_Queue dma_queue;
    touchgfx::BlitOp            queue_storage[96];
    const touchgfx::BlitOp*     pBlitOp;      ///< Reference to current BlitOp (the queue is in-accessible from outside DMA_Interface)
    uint16_t                    numLines;     ///< Number of lines remaining in current transfer.
    unsigned                    use32Bit : 1; ///< set to non-zero when using 32bit transfers (optimization)

};

#endif // NXP546XDMA_HPP
