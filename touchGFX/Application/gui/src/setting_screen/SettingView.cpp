#include <gui/setting_screen/SettingView.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
using namespace touchgfx;
SettingView::SettingView(): 
#if GUI_RESOURCE_ONLY_INTERNAL_FLASH == 1
DemoView(),
#endif
onButtonPressed(this, &SettingView::buttonPressedHandler)
{
    setDemoVieBackground(BITMAP_CONTROLS_BACKGROUND_ID);
    backlightSlider.setXY(0, 60);
    add(backlightSlider);

    /*sleepSet.setXY(45, backlightSlider.getY() + backlightSlider.getHeight() + 5);
    add(sleepSet);*/
    sleepSchedule.setXY(0, 133);
    add(sleepSchedule);

    gotoMenuButton.setBitmaps(Bitmap(BITMAP_CONTROL_MENU_BUTTON_ID), Bitmap(BITMAP_CONTROL_MENU_BUTTON_PRESSED_ID));
    gotoMenuButton.setXY(0, 279);
    gotoMenuButton.setAction(onButtonPressed);
    add(gotoMenuButton);
}

SettingView::~SettingView()
{

}


void SettingView::setupScreen()
{

}

void SettingView::tearDownScreen()
{

}


void SettingView::buttonPressedHandler(const AbstractButton& button)
{
    if (&button == &gotoMenuButton)
    {
        presenter->backOptionSelected();
    }
}
//Called when the screen is done with transition/load

//Handles when a key is pressed
void SettingView::handleKeyEvent(uint8_t key)
{
    if (1 == key)
    {
        //Interaction1
        //When hardware button 1 clicked change color of BackgroundBox
        //Set RGB color R:230, G:8, B:8 on BackgroundBox
        backlightSlider.setXY(0, 80);
        backlightSlider.invalidate();
    }
}