#ifndef BTCONTROL_VIEW_HPP
#define BTCONTROL_VIEW_HPP
#include <gui/btcontrol_screen/BTControlPresenter.hpp>

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/btcontrol_screen/BTControlPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <gui/common/DemoView.hpp>
#include <gui/common/CustomListElement.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <map>
using namespace touchgfx;
using namespace std;

class BTControlView : public DemoView<BTControlPresenter>
{
public:
    BTControlView();
    virtual ~BTControlView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void setBluetoothState(bool);
    void startAnimation();
    void stopAnimation();
    bool isAnimationRunning();
     /*void updateListMenuElements();*/
    void updateListMenuElements(touchgfx::Unicode::UnicodeChar* strDeviceName, touchgfx::Unicode::UnicodeChar* strAddress);
protected:
    /*
     * Member Declarations
     */
    int count;
    Image menuBg;
    ToggleButton switchBTBtn;
    Button backBtn;
    TextArea BtControlDevicesTitle;
    TextArea BTControlTitle;
    CustomListElement MenuContainer;
    AnimatedImage animation;
    TextArea BtTurnOnTips;
    int numberOfListElements;

    ScrollableContainer scrollCnt;
    ListLayout list;

    CustomListElement listElements;

    Callback<BTControlView, const uint8_t> onImageMenuItemSelected;

    void getBluetoothState(bool);

    map<int, CustomListElement> ListMenuMap;

    void handleTickEvent();
private:

    /*
    * Callback Handler Declarations
    */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void animationEnded(const AnimatedImage& source);
    void listElementClicked(CustomListElement& element);
    /*
    * Callback Declarations
    */
    Callback<BTControlView, const touchgfx::AbstractButton&> buttonCallback;

    Callback<BTControlView, const AnimatedImage&> animationEndedCallback;
    Callback<BTControlView, CustomListElement&> listElementClickedCallback;
};

#endif // BTCONTROL_VIEW_HPP
