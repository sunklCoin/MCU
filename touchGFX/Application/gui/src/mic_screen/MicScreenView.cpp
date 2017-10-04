/***********************************/
/********** sunkelong add **********/
/*************2017-10-03************/

#include <gui/mic_screen/MicScreenView.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <stdlib.h>
MicScreenView::MicScreenView() :
DemoView(),
animationState(NO_ANIMATION),
recordState(STOPPED),
animationCounter(0),
tickCounter(0),
dragY(0),
onButtonPressed(this, &MicScreenView::buttonPressedhandler)
{
	//background.setXY(0, 0);
	//background.setBitmap(Bitmap(BITMAP_CONTROLS_BACKGROUND_ID));
	//soundRecAnim.add(background);
	setDemoVieBackground(BITMAP_CONTROLS_BACKGROUND_ID);
}

void MicScreenView::setupScreen()
{
	soundRecAnim.setPosition(0, 90, HAL::DISPLAY_WIDTH, 64);

	for (uint8_t i = 0; i < NUMBER_OF_SOUND_LEVEL_INDICATORS; i++)
	{
		soundLevels[i] = 0;
		if (i == 1){
			soundLevels[i] = 1;
		}
		else if (i == 3){
			soundLevels[i] = 2;
		}
		soundLevelIndicators[i].setXY(95 + i * 10, 0);

		soundLevelIndicators[i].setBitmap(Bitmap(BITMAP_RECORD_SOUND_LEVLE_0_ID + soundLevels[i]));
		soundRecAnim.add(soundLevelIndicators[i]);
	}
	add(soundRecAnim);

    undoTxt.setTypedText(TypedText(T_CANCELRECORD));
    undoTxt.setPosition(0, soundRecAnim.getY() + soundRecAnim.getHeight() + (32 - undoTxt.getHeight()) / 2, HAL::DISPLAY_WIDTH, 32);
    undoTxt.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    add(undoTxt);

	recordBtn.setPosition(35, 217, 170, 60);
    recordBtnImg.setXY(0, 0);
    recordBtnImg.setBitmap(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID));
    recordBtn.add(recordBtnImg);
	//recordBtn.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
    recordTxt.setTypedText(TypedText(T_STARTRECORD));
    recordTxt.setPosition(0, (recordBtn.getHeight() - recordTxt.getHeight())/2, recordBtn.getWidth(), recordBtn.getHeight());
    recordTxt.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    recordBtn.add(recordTxt);
	add(recordBtn);


	gotoMenuButton.setBitmaps(Bitmap(BITMAP_CONTROL_MENU_BUTTON_ID), Bitmap(BITMAP_CONTROL_MENU_BUTTON_PRESSED_ID));
	gotoMenuButton.setXY(0, 279);
	gotoMenuButton.setAction(onButtonPressed);
	add(gotoMenuButton);
}

void MicScreenView::handleTickEvent()
{
    //tickCounter++;
    animateSoundLevelIndicators();
}

void MicScreenView::animateSoundLevelIndicators()
{
	if (recordState == RECORDING)
	{
		// Random change of the sound level indicators
		for (uint8_t i = 0; i < NUMBER_OF_SOUND_LEVEL_INDICATORS; i++)
		{
			// Only change sound level sometimes
			if ((rand() / (float)(RAND_MAX) < 0.2f))
			{
				if ((rand() / (float)(RAND_MAX) < 0.5f))
				{
					soundLevels[i]--;
				}
				else
				{
					soundLevels[i]++;
				}

				if (soundLevels[i] < 0)
				{
					soundLevels[i] = 0;
				}
				else if (soundLevels[i] >= 3)
				{
					soundLevels[i] = 2;
				}

				soundLevelIndicators[i].setBitmap(Bitmap(BITMAP_RECORD_SOUND_LEVLE_0_ID + soundLevels[i]));
				soundLevelIndicators[i].invalidate();
			}

		}
	}
	// Fade out sound level indicators when stopping.
	// Do this at reduced speed
	else if (animationState == ANIMATE_PICKUP_OUT && tickCounter % 3 == 0)
	{
		for (uint8_t i = 0; i < NUMBER_OF_SOUND_LEVEL_INDICATORS; i++)
		{
			if (soundLevels[i] > 0)
			{
				soundLevels[i]--;
				soundLevelIndicators[i].setBitmap(Bitmap(BITMAP_RECORD_SOUND_LEVLE_0_ID + soundLevels[i]));
				soundLevelIndicators[i].invalidate();
			}
		}
	}
}

bool MicScreenView::checkPositionToSend(int16_t y)
{
    if (dragY - y > 20){
        return false;
    }
    return true;
}

void MicScreenView::handleClickEvent(const ClickEvent& evt)
{
    int x = evt.getX();
	int y = evt.getY();
	if (evt.getType() == ClickEvent::PRESSED){
		if (evt.getX() < recordBtn.getX()
			|| evt.getX() > (recordBtn.getX() + recordBtn.getWidth())
			|| evt.getY() < recordBtn.getY()
			|| evt.getY() > (recordBtn.getY() + recordBtn.getHeight()))
		{
            DemoView<MicScreenPresenter>::handleClickEvent(evt);
			return;
		}
        dragY = recordBtn.getY();
		recordState = RECORDING;
        recordBtnImg.setBitmap(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
		recordTxt.setTypedText(TypedText(T_ENDRECORD));
        recordBtnImg.invalidate();
        recordTxt.invalidate();
		presenter->startRecord();
	}
	else if (evt.getType() == ClickEvent::RELEASED)
	{
        recordState = STOPPED;
        recordBtnImg.setBitmap(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID));
        recordBtnImg.invalidate();
        recordTxt.setTypedText(TypedText(T_STARTRECORD));
        recordTxt.invalidate();
        undoTxt.setTypedText(TypedText(T_CANCELRECORD));
        undoTxt.invalidate();

        if (!checkPositionToSend(evt.getY()))
        {
            presenter->cancelRecord();
        }
        else
        {
            presenter->finishRecord();
        }
            DemoView<MicScreenPresenter>::handleClickEvent(evt);
	}
}

//void MicScreenView::handleGestureEvent(const GestureEvent& evt)
//{
//	// Do not accept gestures while animating
//	int Y = evt.getY();
//	if (evt.getType() == evt.SWIPE_VERTICAL)
//	{
//        if (/*evt.getVelocity() > 0 &&*/ (dragY - Y) > 100){
//			recordState = STOPPED;
//            dragY = 0;
//			presenter->cancelRecord();
//		}
//	}
//}

void MicScreenView::handleDragEvent(const DragEvent& evt)
{
    // Do not accept gestures while animating
    //dragY += evt.getDeltaY();
    if (!checkPositionToSend(evt.getNewY()))
    {
        if (recordState == RECORDING){
            undoTxt.setTypedText(TypedText(T_RELEASECANCEL));
            undoTxt.invalidate();
        }
    }
    else{
        undoTxt.setTypedText(TypedText(T_CANCELRECORD));
        undoTxt.invalidate();
    }
}


void MicScreenView::buttonPressedhandler(const AbstractButton& button)
{
//	if (&button == &recordBtn)
//	{
////		recordState = RECORDING;
////		presenter->startRecord();
//	}
//	else if (&button == &gotoMenuButton)
	{
		presenter->backOptionSelected();
	}
}
