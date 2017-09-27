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
#ifndef NXP546XHAL_HPP
#define NXP546XHAL_HPP

#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/hal/HAL.hpp>
//#include <platform/hal/nxp/mcu/LPC546x/NXP546XDMA.hpp>

#include <platform/driver/touch/TouchController.hpp>

/**
 * @class NXP546XHAL NXP546XHAL.hpp platform/hal/nxp/mcu/LPC546x/NXP546XHAL.hpp
 *
 * @brief HAL implementation for NXP LPC546X.
 *
 *        HAL implementation for NXP LPC546X.
 *
 * @sa touchgfx::HAL
 */
class NXP546XHAL : public touchgfx::HAL
{
public:
    /**
     * @fn NXP546XHAL::NXP546XHAL(touchgfx::DMA_Interface& dma, touchgfx::LCD& display, touchgfx::TouchController& tc, uint16_t width, uint16_t height) : touchgfx::HAL(dma,display,tc,width,height)
     *
     * @brief Constructor.
     *
     *        Constructor. Initializes members.
     *
     * @param [in,out] dma     Reference to DMA interface.
     * @param [in,out] display Reference to LCD interface.
     * @param [in,out] tc      Reference to Touch Controller driver.
     * @param width            Width of the display.
     * @param height           Height of the display.
     */
    NXP546XHAL(touchgfx::DMA_Interface& dma, touchgfx::LCD& display, touchgfx::TouchController& tc, uint16_t width, uint16_t height) : touchgfx::HAL(dma, display, tc, width, height)
    {
    }

    /**
     * @fn virtual void NXP546XHAL::configureInterrupts();
     *
     * @brief Sets the DMA and LCD interrupt priorities.
     *
     *        Sets the DMA and LCD interrupt priorities.
     */
    virtual void configureInterrupts();

    /**
     * @fn virtual void NXP546XHAL::enableLCDControllerInterrupt();
     *
     * @brief Enables the LCD interrupt in the LCD controller.
     *
     *        Enables the LCD interrupt in the LCD controller.
     */
    virtual void enableLCDControllerInterrupt();

    /**
     * @fn virtual void NXP546XHAL::enableInterrupts();
     *
     * @brief Enables the DMA and LCD interrupts.
     *
     *        Enables the DMA and LCD interrupts.
     */
    virtual void enableInterrupts();

    /**
     * @fn virtual void NXP546XHAL::disableInterrupts();
     *
     * @brief Disables the DMA and LCD interrupts.
     *
     *        Disables the DMA and LCD interrupts.
     */
    virtual void disableInterrupts();

    /**
     * @fn virtual void NXP546XHAL::backPorchExited()
     *
     * @brief Reverses the order of tick and swap for this specific platform.
     *
     *        Reverses the order of tick and swap for this specific platform. Has to be called
     *        from within the LCD IRQ routine when the Back Porch Exit is reached.
     */
    virtual void backPorchExited()
    {
        swapFrameBuffers();
        tick();
    }

protected:
    /**
     * @fn virtual uint16_t* NXP546XHAL::getTFTFrameBuffer() const;
     *
     * @brief Gets the frame buffer address used by the TFT controller.
     *
     *        Gets the frame buffer address used by the TFT controller.
     *
     * @return The address of the frame buffer currently being displayed on the TFT.
     */
    virtual uint16_t* getTFTFrameBuffer() const;

    /**
     * @fn virtual void NXP546XHAL::setTFTFrameBuffer(uint16_t* adr);
     *
     * @brief Sets the frame buffer address used by the TFT controller.
     *
     *        Sets the frame buffer address used by the TFT controller.
     *
     * @param [in,out] adr New frame buffer address.
     */
    virtual void setTFTFrameBuffer(uint16_t* adr);
};

#endif // NXP546XHAL_HPP
