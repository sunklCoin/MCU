#ifndef SCREENSAVERCLOCK_MODAL_HPP
#define SCREENSAVERCLOCK_MODAL_HPP

#include <gui/common/FrontendApplication.hpp>
//#include <mvp/View.hpp>
#include <gui/common/TimeUtils.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <gui/screensaverclock_screen/AnalogClock.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <gui/screensaverclock_screen/DigitalClock.hpp>
#include <touchgfx/containers/ModalWindow.hpp>
using namespace touchgfx;
class ScreenSaverClockModal : public ModalWindow 
{
public:
ScreenSaverClockModal();
virtual ~ScreenSaverClockModal() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void afterTransition();
    void handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds, bool is24Hour, bool isAnalogClock);
    // Updates the clock view
    void updateClock(uint8_t hourCounter, uint8_t minuteCounter, uint8_t secondCounter, bool is24Hour);
protected:
    FrontendApplication& application()
    {
        return *static_cast<FrontendApplication*>(Application::getInstance());
    }

    /*
    * Member Declarations
    */
    uint8_t currentSecondCounter;
    uint8_t currentMinuteCounter;
    uint8_t currentHourCounter;

    bool transitionDone;
    bool firstPresenterCall;

    Button backBtn;
    Image ScreenSaverClockBg;
    AnalogClock mAnalogClock;
    DigitalClock mDigitalClock;

	TextAreaWithOneWildcard dateText;
	Unicode::UnicodeChar dateTextBuffer[11];

	TextArea dayOfWeekTxt;
    /*
    * Wildcard Buffers
    */
    static const uint16_t SCREENSAVERDATA_SIZE = 1;
    touchgfx::Unicode::UnicodeChar ScreenSaverDataBuffer[SCREENSAVERDATA_SIZE];


    Callback<ScreenSaverClockModal, const AbstractButton&> onButtonPressed;
    void buttonPressedHandler(const AbstractButton& button);
};

#endif // SCREENSAVERCLOCK_MODAL_HPP
