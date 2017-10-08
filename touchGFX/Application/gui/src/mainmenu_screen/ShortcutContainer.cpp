/***********************************/
/********** sunkelong add **********/
/*************2017-10-07************/
#include <gui/mainmenu_screen/ShortcutContainer.hpp>
#include "BitmapDatabase.hpp"

ShortcutContainer::ShortcutContainer():
onshortcutContainer(this, &ShortcutContainer::shortcutContainerHandler)
{
	/*image1.setXY(0, 0);
	image1.setBitmap(Bitmap(BITMAP_MAIN_BG_240X320PX_ID));
	add(image1);*/

	buttonScreenSaver.setPosition(88, 70, 64, 64);
	buttonScreenSaver.setBitmaps(Bitmap(BITMAP_SHUTCUT_BTN_SCREENSAVER_ID), Bitmap(BITMAP_SHUTCUT_BTN_SCREENSAVER_PRESSED_ID));
	buttonScreenSaver.setAction(onshortcutContainer);
	add(buttonScreenSaver);

	buttonSleep.setPosition(88, 160, 64, 64);
	buttonSleep.setBitmaps(Bitmap(BITMAP_SHUTCUT_BTN_SLEEP_ID), Bitmap(BITMAP_SHUTCUT_BTN_SLEEP_PRESSED_ID));
	buttonSleep.setAction(onshortcutContainer);
	add(buttonSleep);

	setWidth(240);
	setHeight(buttonSleep.getY() + buttonSleep.getHeight());
}


void ShortcutContainer::shortcutContainerHandler(const AbstractButton& button)
{

	if (&buttonSleep == &button)
	{
		application().getControlData().gotoSleep();
	}
	else if (&buttonScreenSaver == &button)
	{
		application().gotoScreenSaverClockTransition();
	}
}