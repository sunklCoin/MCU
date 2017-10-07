
#include <gui/custom_controls_screen/SleepSchedule.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <stddef.h>

SleepSchedule::SleepSchedule() :
onSelectedElementChanged(this, &SleepSchedule::selectedElementChangedHandler),
buttonClickedCallback(this, &SleepSchedule::buttonClicked)
{

	//setBackground(BITMAP_SET_TIME_BACKGROUND_ID);
	/*background.setBitmap(Bitmap(BITMAP_CONTROLS_MENU_BACKGROUND_ID));
	background.setXY(0, 0);
	add(background);*/

    background.setBitmap(Bitmap(BITMAP_CONTROLS_MENU_BACKGROUND_ID));
    background.setPosition(0, 0, 240, 100);
    background.setScalingAlgorithm(ScalableImage::NEAREST_NEIGHBOR);
    add(background);

	imageGradiantBGDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_WHEEL_GRADIENT_ID));
    imageGradiantBGDuration.setXY((background.getWidth() - imageGradiantBGDuration.getWidth()) / 2, (background.getHeight() - imageGradiantBGDuration.getHeight())/2);
	add(imageGradiantBGDuration);

	add(wheelDuration);

	imageShadowTopDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_TOP_GRADIENT_ID));
	imageShadowTopDuration.setXY(imageGradiantBGDuration.getX(), imageGradiantBGDuration.getY());
	add(imageShadowTopDuration);
	imageShadowBottomDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_BOTTOM_GRADIENT_ID));
    imageShadowBottomDuration.setXY(imageGradiantBGDuration.getX() + imageGradiantBGDuration.getWidth() - imageShadowBottomDuration.getWidth(), imageGradiantBGDuration.getY());
	add(imageShadowBottomDuration);
	glassOverlayDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_GLASS_OVERLAY_ID));
	glassOverlayDuration.setXY(imageGradiantBGDuration.getX() + imageGradiantBGDuration.getWidth() / 2 - glassOverlayDuration.getWidth() / 2,
		imageGradiantBGDuration.getY() + imageGradiantBGDuration.getHeight() / 2 - glassOverlayDuration.getHeight() / 2);
	add(glassOverlayDuration);

	uint16_t normalTextColor = Color::getColorFrom24BitRGB(0x0a, 0x0a, 0x0a); //Color::getColorFrom24BitRGB(TEXT_BLACK_ON_WHITE_R, TEXT_BLACK_ON_WHITE_G, TEXT_BLACK_ON_WHITE_B);
    uint16_t selectedTextColor = Color::getColorFrom24BitRGB(TEXT_WHITE_ON_BLACK_R, TEXT_WHITE_ON_BLACK_G, TEXT_WHITE_ON_BLACK_B);
    uint16_t selectedBackgroundColor = Color::getColorFrom24BitRGB(0x17, 0x3C, 0x51);

	wheelDuration.setXY(imageGradiantBGDuration.getX(), imageGradiantBGDuration.getY());
	wheelDuration.setup(imageGradiantBGDuration.getWidth(), imageGradiantBGDuration.getHeight(), 80, imageGradiantBGDuration.getHeight()/3, T_TIME_PICKER_DURATION);
    wheelDuration.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, glassOverlayDuration.getX() - imageGradiantBGDuration.getX(), glassOverlayDuration.getWidth() - 5);
    wheelDuration.setElementSelectedCallback(onSelectedElementChanged);

    textDurationTitle.setTypedText(TypedText(T_SLEEPWHEEL_HEADLINE));
	textDurationTitle.setPosition(0, background.getY() + 1, 240, 20);
    textDurationTitle.setColor(Color::getColorFrom24BitRGB(0x17, 0x3C, 0x51));
    add(textDurationTitle);

    Unicode::snprintf(scheduleTextBuffer, 6, "%dsec", 30);
    scheduleText.setWildcard(scheduleTextBuffer);
    scheduleText.setTypedText(TypedText(T_SLEEPWHEEL_READOUT));
	scheduleText.setPosition(0, imageGradiantBGDuration.getY() + imageGradiantBGDuration.getHeight() + 1, 240, 20);
    scheduleText.setColor(Color::getColorFrom24BitRGB(0x17, 0x3C, 0x51));// (0xFF, 0xFF, 0xFF)
    add(scheduleText);

	SetDefaultTimes();
	setWidth(background.getWidth());
    setHeight(background.getHeight());

}


void SleepSchedule::buttonClicked(const AbstractButton& source) {
    if (&source == &buttonOK) {
		SetDefaultTimes();
	}
}


void SleepSchedule::SetDefaultTimes() {
    int index = static_cast<FrontendApplication*>(Application::getInstance())->getControlData().getSleepSchedule();
	updateScheduleTimeText(index);
    wheelDuration.setSelectedIndex(index, 20);
}

void SleepSchedule::updateScheduleTimeText(const int& index) {
	int scheduleTime = sleepScheduleArr[index];
	if (scheduleTime<60)
	{
		Unicode::snprintf(scheduleTextBuffer, 6, "%dsec", scheduleTime);
	}
	else{
		Unicode::snprintf(scheduleTextBuffer, 6, "%dmin", scheduleTime/60);
	}
	scheduleText.invalidate();
}

void SleepSchedule::selectedElementChangedHandler(const HorizontalWheelSelector& wheel, const int& index)
{
	updateScheduleTimeText(index);
    static_cast<FrontendApplication*>(Application::getInstance())->getControlData().setSleepSchedule(index);
}