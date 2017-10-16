/***********************************/
/********** sunkelong add **********/
/*************2017-10-03************/

#ifndef MIC_SCREEN_VIEW_HPP
#define MIC_SCREEN_VIEW_HPP

#include <gui/common/DemoView.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/mic_screen/MicScreenPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/containers/progress_indicators/TextProgress.hpp>
using namespace touchgfx;

class MicScreenView : public DemoView<MicScreenPresenter>
{
public:
	MicScreenView();
	virtual ~MicScreenView() {}
	virtual void handleTickEvent();
	virtual void handleClickEvent(const ClickEvent& evt);
	//virtual void handleGestureEvent(const GestureEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);
	void setupScreen();
    void onPrepareState(bool state);
    void popMicViewOkHandle();
    void popMicViewCancelHandle();
    void resetMicViewEle(bool isReset);
protected:
	FrontendApplication& application() {
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}

private:
	enum AnimationStates
	{
		ANIMATE_PICKUP_IN,
		ANIMATE_PICKUP_OUT,
		NO_ANIMATION
	} animationState;

	enum RecordStates
	{
		STOPPED,
		RECORDING,
        SENDING,
		ANIMATE_TO_SEND_ELEMENT,
		ANIMATE_TO_WAIT_ELEMENT,
		ANIMATE_TO_REC_ELEMENTS,
	} recordState;
	/*
	* Member Declarations
	*/
	//Image background;
	static const uint8_t NUMBER_OF_SOUND_LEVEL_INDICATORS = 5;
	Image soundLevelIndicators[NUMBER_OF_SOUND_LEVEL_INDICATORS];
	uint8_t  soundLevels[NUMBER_OF_SOUND_LEVEL_INDICATORS];
    Image recordBtnImg;
    TextArea recordTxt;
    Container recordBtn;
	Container soundRecAnim;
    TextArea undoTxt;
    TextArea loadingTxt;
    Container micViewEle;
	PopModal popMessage;
    TextProgress textProgress;
	TextArea sendingTxt;
	Container Progress;

	uint8_t animationCounter;
	uint32_t tickCounter;
    int16_t dragY;
    int32_t process;
	void animateSoundLevelIndicators();
	Callback<MicScreenView, const AbstractButton&> onButtonPressed;
	void buttonPressedhandler(const AbstractButton& button);
    bool checkPositionToSend(int16_t);
    void updateProgress(int32_t);
    AnimatedImage loadingAnimation;

    Callback<MicScreenView> onMicViewPopOkEvent;
    Callback<MicScreenView> onMicViewPopCancelEvent;
	void animateToRecElement();
	void animateToSendElement();
	void setState(RecordStates newState);
};

#endif // MIC_SCREEN_VIEW_HPP
