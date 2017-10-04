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
protected:
	FrontendApplication& application() {
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}

	/*
	* Member Declarations
	*/
	//Image background;
	static const uint8_t NUMBER_OF_SOUND_LEVEL_INDICATORS = 5;
	Image soundLevelIndicators[NUMBER_OF_SOUND_LEVEL_INDICATORS];
	uint8_t soundLevels[NUMBER_OF_SOUND_LEVEL_INDICATORS];
    Image recordBtnImg;
    TextArea recordTxt;
    Container recordBtn;
	Container soundRecAnim;
    TextArea undoTxt;
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
		RECORDING
	} recordState;

	uint8_t animationCounter;
	uint32_t tickCounter;
    int16_t dragY;
	void animateSoundLevelIndicators();
	Callback<MicScreenView, const AbstractButton&> onButtonPressed;
	void buttonPressedhandler(const AbstractButton& button);
    bool checkPositionToSend(int16_t);
};

#endif // MIC_SCREEN_VIEW_HPP
