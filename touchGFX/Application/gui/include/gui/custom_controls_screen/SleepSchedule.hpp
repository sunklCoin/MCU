
#ifndef _SLEEPSCHEDULE_HPP_
#define _SLEEPSCHEDULE_HPP_

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/containers/ModalWindow.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>
#include <touchgfx/containers/Container.hpp>
#include <gui/custom_controls_screen/WheelSelector.hpp>
#include <gui/custom_controls_screen/HorizontalWheelSelector.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/common/FrontendApplication.hpp>
using namespace touchgfx;
// Global color definitions
#define TEXT_BLACK_ON_WHITE_R  (0x29)
#define TEXT_BLACK_ON_WHITE_G  (0x2b)
#define TEXT_BLACK_ON_WHITE_B  (0x30)

#define TEXT_DESHBOARD_DARK_R (0x24)
#define TEXT_DESHBOARD_DARK_G (0x28)
#define TEXT_DESHBOARD_DARK_B (0x2a)

#define PROGRESS_BAR_COLOR_R (0x3e)
#define PROGRESS_BAR_COLOR_G (0xaa)
#define PROGRESS_BAR_COLOR_B (0xe3)

#define TEXT_WHITE_ON_BLACK_R  (0xff)
#define TEXT_WHITE_ON_BLACK_G  (0xff)
#define TEXT_WHITE_ON_BLACK_B  (0xff)

#define MENUOPT_BACKGROUND_R (0x2b)
#define MENUOPT_BACKGROUND_G (0x2f)
#define MENUOPT_BACKGROUND_B (0x32)

#define MENUOPT_LEGEND_BG_R (0x24)
#define MENUOPT_LEGEND_BG_G (0x28)
#define MENUOPT_LEGEND_BG_B (0x2a)

#define MENUOPT_LEGEND_TEXT_R (0x6c)
#define MENUOPT_LEGEND_TEXT_G (0x73)
#define MENUOPT_LEGEND_TEXT_B (0x7a)

class SleepSchedule : public Container {
public:
	virtual ~SleepSchedule() {};

	SleepSchedule();
protected:

	static const uint16_t WHEELS_TOP_Y = 0;

	//Image background;
    ScalableImage background;
	TextArea textDurationTitle;
    TextArea scheduleText;
    //TextAreaWithOneWildcard scheduleText;
    //Unicode::UnicodeChar scheduleTextBuffer[5];

	Image imageGradiantBGDuration;
	Image imageShadowTopDuration;
	Image imageShadowBottomDuration;
	Image glassOverlayDuration;
    HorizontalWheelSelector wheelDuration;

	Button buttonOK;

	Callback<SleepSchedule, const AbstractButton&> buttonClickedCallback;
	void buttonClicked(const AbstractButton& source);

	void SetDefaultTimes();

    Callback<SleepSchedule, const HorizontalWheelSelector&, const int&> onSelectedElementChanged;
    void selectedElementChangedHandler(const HorizontalWheelSelector& wheel, const int& index);
};
#endif //_SLEEPSCHEDULE_HPP_