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
#include <gui/custom_controls_screen/HorizontalSlideMenu.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/EasingEquations.hpp>

HorizontalSlideMenu::HorizontalSlideMenu() :
    size(0),
    animationDuration(10),
    animationEndedCallback(this, &HorizontalSlideMenu::animationEndedHandler)
{
}

void HorizontalSlideMenu::setup(int numberOfElements, int selectedElementIndex, Bitmap smallBmp, Bitmap largeBmp)
{
    assert(selectedElementIndex < numberOfElements);
    assert(numberOfElements <= MAX_SIZE);

    size = numberOfElements;
    //imagesYPositionDelta = 16;
    imagesXPositionDelta = 9;

    smallImageWidth = smallBmp.getWidth();
    smallImageHeight = smallBmp.getHeight();
    largeImageWidth = largeBmp.getWidth();
    largeImageHeight = largeBmp.getHeight();
    largeImageX = (getWidth() - largeImageWidth) / 2;
    largeImageY = (getHeight() - largeImageHeight) / 2;
    //smallImageX = (getWidth() - smallImageWidth) / 2;
    smallImageY = (getHeight() - smallImageHeight) / 2;

    //fixedCenterCorrection = (largeImageHeight - smallImageHeight) / 2;
    fixedCenterCorrection = (largeImageWidth - smallImageWidth) / 2;

    currentSelected = selectedElementIndex;

    images[currentSelected].setWidth(largeImageWidth);
    images[currentSelected].setHeight(largeImageHeight);
    images[currentSelected].setXY(largeImageX, largeImageY);
    images[currentSelected].setAnimationEndedCallback(animationEndedCallback);
    add(images[currentSelected]);

    for (int i = currentSelected - 1; i >= 0; i--)
    {
        images[i].setWidth(smallImageWidth);
        images[i].setHeight(smallImageHeight);

        images[i].setXY(images[i + 1].getX() - imagesXPositionDelta - images[i].getWidth(), smallImageY);

        images[i].setAnimationEndedCallback(animationEndedCallback);
        add(images[i]);
    }

    for (int i = currentSelected + 1; i < size; i++)
    {
        images[i].setWidth(smallImageWidth);
        images[i].setHeight(smallImageHeight);

        images[i].setXY(images[i - 1].getX() + images[i - 1].getWidth() + imagesXPositionDelta, smallImageY);

        images[i].setAnimationEndedCallback(animationEndedCallback);
        add(images[i]);
    }
}

HorizontalSlideMenu::~HorizontalSlideMenu()
{
}

void HorizontalSlideMenu::setBitmapsForElement(int elementIndex, BitmapId smallBmp, BitmapId largeBmp)
{
    // Make sure that the dimensions of the bitmap stays the same
    int oldWidth = images[elementIndex].getWidth();
    int oldHeight = images[elementIndex].getHeight();

    images[elementIndex].setBitmaps(Bitmap(smallBmp), Bitmap(largeBmp));

    images[elementIndex].setWidth(oldWidth);
    images[elementIndex].setHeight(oldHeight);
}

void HorizontalSlideMenu::animateUp()
{
    if (animating() || currentSelected == size - 1)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        // If image is not visible and will not be after animation just move it
        if (images[i].getX() + images[i].getWidth() < 0)
        {
            images[i].moveTo(images[i].getX() - images[i].getWidth() - imagesXPositionDelta, images[i].getY());
        }
        // If image is not visible and will not be after animation just move it
        else if (images[i].getX() - images[i].getWidth() - imagesXPositionDelta > getWidth())
        {
            images[i].moveTo(images[i].getX() - images[i].getWidth() - imagesXPositionDelta, images[i].getY());
        }
        else if (i == currentSelected + 1)
        {
            images[i].startZoomAndMoveAnimation(images[i].getX() - largeImageWidth - imagesXPositionDelta + fixedCenterCorrection, images[i].getY(), largeImageWidth, largeImageHeight, animationDuration,
                                                ZoomAnimationImage::FIXED_CENTER, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
        }
        else if (i == currentSelected)
        {
            images[i].startZoomAndMoveAnimation(images[i].getX() - smallImageWidth - imagesXPositionDelta - fixedCenterCorrection, images[i].getY(), smallImageWidth, smallImageHeight, animationDuration,
                                                ZoomAnimationImage::FIXED_CENTER, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
        }
        else
        {
            images[i].startZoomAndMoveAnimation(images[i].getX() - smallImageWidth - imagesXPositionDelta, images[i].getY(), smallImageWidth, smallImageHeight, animationDuration,
                                                ZoomAnimationImage::FIXED_CENTER, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
        }
    }
    currentSelected++;
}

void HorizontalSlideMenu::animateDown()
{
    if (animating() || currentSelected == 0)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        // If image is not visible and will not be after animation just move it
        if (images[i].getX() > getWidth())
        {
            images[i].moveTo(images[i].getX() + images[i].getWidth() + imagesXPositionDelta, images[i].getY());
        }
        // If image is not visible and will not be after animation just move it
        else if (images[i].getX() + 2 * images[i].getWidth() + imagesXPositionDelta < 0)
        {
            images[i].moveTo(images[i].getX() + images[i].getWidth() + imagesXPositionDelta, images[i].getY());
        }
        else if (i == currentSelected - 1)
        {
            images[i].startZoomAndMoveAnimation(images[i].getX() + largeImageWidth + imagesXPositionDelta - fixedCenterCorrection, images[i].getY(), Bitmap(BITMAP_CONTROL_MENU_ICON_DATEPICKER_LARGE_ID).getWidth(), Bitmap(BITMAP_CONTROL_MENU_ICON_DATEPICKER_LARGE_ID).getHeight(), animationDuration,
                                                ZoomAnimationImage::FIXED_CENTER, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
        }
        else if (i == currentSelected)
        {
            images[i].startZoomAndMoveAnimation(images[i].getX() + smallImageWidth + imagesXPositionDelta + fixedCenterCorrection, images[i].getY(), Bitmap(BITMAP_CONTROL_MENU_ICON_DATEPICKER_SMALL_ID).getWidth(), Bitmap(BITMAP_CONTROL_MENU_ICON_DATEPICKER_SMALL_ID).getHeight(), animationDuration,
                                                ZoomAnimationImage::FIXED_CENTER, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
        }
        else
        {
            images[i].startZoomAndMoveAnimation(images[i].getX() + smallImageWidth + imagesXPositionDelta, images[i].getY(), images[i].getWidth(), images[i].getHeight(), animationDuration,
                                                ZoomAnimationImage::FIXED_CENTER, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);
        }
    }
    currentSelected--;
}

void HorizontalSlideMenu::animationEndedHandler(const ZoomAnimationImage& image)
{
    if (elementSelectedAction && elementSelectedAction->isValid())
    {
        elementSelectedAction->execute(*this);
    }

}

bool HorizontalSlideMenu::animating()
{
    for (int i = 0; i < size; i++)
    {
        if (images[i].isRunning())
        {
            return true;
        }
    }
    return false;
}
