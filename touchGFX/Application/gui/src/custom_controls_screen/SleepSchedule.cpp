
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
    background.setPosition(0, 0, 240, 105);
    background.setScalingAlgorithm(ScalableImage::NEAREST_NEIGHBOR);
    add(background);

	imageGradiantBGDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_WHEEL_GRADIENT_ID));
    imageGradiantBGDuration.setXY((background.getWidth() - imageGradiantBGDuration.getWidth()) / 3, background.getHeight() - imageGradiantBGDuration.getHeight());
	add(imageGradiantBGDuration);

	add(wheelDuration);

	imageShadowTopDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_TOP_GRADIENT_ID));
	imageShadowTopDuration.setXY(imageGradiantBGDuration.getX(), imageGradiantBGDuration.getY());
	add(imageShadowTopDuration);
	imageShadowBottomDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_BOTTOM_GRADIENT_ID));
	imageShadowBottomDuration.setXY(imageGradiantBGDuration.getX(), imageGradiantBGDuration.getY() + imageGradiantBGDuration.getHeight() - imageShadowBottomDuration.getHeight());
	add(imageShadowBottomDuration);
	glassOverlayDuration.setBitmap(Bitmap(BITMAP_SCHEDULE_SET_TIME_DURATION_GLASS_OVERLAY_ID));
	glassOverlayDuration.setXY(imageGradiantBGDuration.getX() + imageGradiantBGDuration.getWidth() / 2 - glassOverlayDuration.getWidth() / 2,
		imageGradiantBGDuration.getY() + imageGradiantBGDuration.getHeight() / 2 - glassOverlayDuration.getHeight() / 2);
	add(glassOverlayDuration);

	uint16_t normalTextColor = Color::getColorFrom24BitRGB(TEXT_BLACK_ON_WHITE_R, TEXT_BLACK_ON_WHITE_G, TEXT_BLACK_ON_WHITE_B);
	uint16_t selectedTextColor = Color::getColorFrom24BitRGB(PROGRESS_BAR_COLOR_R, PROGRESS_BAR_COLOR_G, PROGRESS_BAR_COLOR_B);
	uint16_t selectedBackgroundColor = Color::getColorFrom24BitRGB(246, 246, 246);

	wheelDuration.setXY(imageGradiantBGDuration.getX(), imageGradiantBGDuration.getY());
	wheelDuration.setup(imageGradiantBGDuration.getWidth() - 2, imageGradiantBGDuration.getHeight() - 5, 5, 42/*imageGradiantBGDuration.getY()*/, T_TIME_PICKER_DURATION);
	wheelDuration.setTextColor(normalTextColor, selectedTextColor, selectedBackgroundColor, glassOverlayDuration.getY() - imageGradiantBGDuration.getY() + 2, glassOverlayDuration.getHeight() - 5);
    wheelDuration.setElementSelectedCallback(onSelectedElementChanged);

    textDurationTitle.setTypedText(TypedText(T_SLEEPWHEEL_HEADLINE));
    textDurationTitle.setXY(background.getX() + 5, glassOverlayDuration.getY() - (glassOverlayDuration.getHeight() - textDurationTitle.getHeight()/2));
    textDurationTitle.setColor(Color::getColorFrom24BitRGB(0x17, 0x3C, 0x51));
    add(textDurationTitle);

    //Unicode::snprintf(scheduleTextBuffer, 5, "%d", 1);
    //scheduleText.setWildcard(scheduleTextBuffer);
    scheduleText.setTypedText(TypedText(T_SLEEPWHEEL_READOUT));
    scheduleText.setPosition(imageGradiantBGDuration.getX() + imageGradiantBGDuration.getWidth(), glassOverlayDuration.getY() + 5, 100, 20);
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
    wheelDuration.setSelectedIndex(index, 20);
}

void SleepSchedule::selectedElementChangedHandler(const WheelSelector& wheel, const int& index)
{
    static_cast<FrontendApplication*>(Application::getInstance())->getControlData().setSleepSchedule(index);
}