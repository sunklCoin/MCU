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
#include <gui/common/CustomList.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
///#include <map>

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
    void clearListMenuElements();
    void updateListMenuElements(touchgfx::Unicode::UnicodeChar* strDeviceName, uint8_t address[]);
    void updateListMenuLayout();
    void stopListAnimation() { mList.stopAnimation(); }
    void setCustomListStatus(CustomListElementStatus status);

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
    ScrollableContainer scrollCnt;
    ListLayout list;
    CustomList mList;
    PopModal popMessage;
    Callback<BTControlView> onBTControlViewPopOkEvent;
    Callback<BTControlView> onBTControlViewPopCancelEvent;
/*
    int numberOfListElements;
    CustomListElement listElements;
    map<int, CustomListElement> ListMenuMap;
*/
    Callback<BTControlView, const uint8_t> onImageMenuItemSelected;
    void getBluetoothState(bool);
    void handleTickEvent();
private:
    int mBTConnectTickCount;

    /*
    * Callback Handler Declarations
    */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void animationEnded(const AnimatedImage& source);
    void listElementClicked(CustomListElement& element);
    void popBTControlViewOkHandle();
    void popBTControlViewCancelHandle();

    /*
    * Callback Declarations
    */
    Callback<BTControlView, const touchgfx::AbstractButton&> buttonCallback;
    Callback<BTControlView, const AnimatedImage&> animationEndedCallback;
    Callback<BTControlView, CustomListElement&> listElementClickedCallback;
};

#endif // BTCONTROL_VIEW_HPP
