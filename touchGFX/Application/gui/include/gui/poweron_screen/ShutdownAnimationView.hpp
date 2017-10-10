/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.8.0 evaluation distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * This file is free software and is provided for example purposes. You may
 * use, copy, and modify within the terms and conditions of the license
 * agreement.
 *
 * This is licensed software for evaluation use, any use must strictly comply
 * with the evaluation license agreement provided with delivery of the
 * TouchGFX software.
 *
 * The evaluation license agreement can be seen on www.touchgfx.com
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
#ifndef SHUTDOWN_ANIMATION_VIEW_HPP
#define SHUTDOWN_ANIMATION_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/poweron_screen/ShutdownAnimationPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/containers/progress_indicators/AbstractProgressIndicator.hpp>
#include <touchgfx/containers/progress_indicators/BoxProgress.hpp>
#include <touchgfx/containers/progress_indicators/TextProgress.hpp>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888Bitmap.hpp>
#elif USE_BPP==4
#include <touchgfx/widgets/canvas/PainterGRAY4.hpp>
#include <touchgfx/widgets/canvas/PainterGRAY4Bitmap.hpp>
#elif USE_BPP==2
#include <touchgfx/widgets/canvas/PainterGRAY2.hpp>
#include <touchgfx/widgets/canvas/PainterGRAY2Bitmap.hpp>
#else
#error Unknown USE_BPP
#endif
#include <touchgfx/containers/progress_indicators/CircleProgress.hpp>
#include <touchgfx/containers/progress_indicators/LineProgress.hpp>
#include <touchgfx/containers/progress_indicators/ImageProgress.hpp>

/**
 * The View for a Main screen. In the MVP paradigm, the view is a
 * passive interface that only displays the user interface and routes
 * any events from the user interface to the presenter. Normally it is the
 * responsibility of the presenter to act upon those events.
 *
 * By deriving from View, this class has a presenter pointer, which is configured
 * automatically.
 */
class ShutdownAnimationView : public View<ShutdownAnimationPresenter>
{
public:
    /**
     * The view constructor. Note that the constructor runs before the new screen is
     * completely initialized, so do not place code here that causes anything to be drawn.
     * Use the setupScreen function instead.
     */
	ShutdownAnimationView()
    {
    }
	virtual ~ShutdownAnimationView() { }

    /**
     * This function is called automatically when the view is activated. This function
     * should add widgets to the root container, configure widget sizes and event
     * callbacks, et cetera.
     */
    virtual void setupScreen();

    /**
     * This function is called automatically when transitioning to a different screen
     * than this one. Can optionally be used to clean up.
     */
    virtual void tearDownScreen() {}

    virtual void handleTickEvent();

    void updateProgress(uint16_t tick);

private:
    Image background;
	CircleProgress circleProgress;
    //ImageProgress imageProgress;
	TextArea shuttingdownTxt;

#if !defined(USE_BPP) || USE_BPP==16
	PainterRGB565Bitmap lineProgressPainter;
	PainterRGB565 tiltedLineProgressPainter;
	PainterRGB565Bitmap circleProgressPainter;
#elif USE_BPP==24
	PainterRGB888Bitmap lineProgressPainter;
	PainterRGB888 tiltedLineProgressPainter;
	PainterRGB888Bitmap circleProgressPainter;
#elif USE_BPP==4
	PainterGRAY4Bitmap lineProgressPainter;
	PainterGRAY4 tiltedLineProgressPainter;
	PainterGRAY4Bitmap circleProgressPainter;
#elif USE_BPP==2
	PainterGRAY2Bitmap lineProgressPainter;
	PainterGRAY2 tiltedLineProgressPainter;
	PainterGRAY2Bitmap circleProgressPainter;
#else
#error Unknown USE_BPP
#endif

    uint16_t tickCounter;
};

#endif // SHUTDOWN_ANIMATION_VIEW_HPP
