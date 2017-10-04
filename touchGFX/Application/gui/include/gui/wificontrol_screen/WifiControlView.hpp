#ifndef WIFICONTROL_VIEW_HPP
#define WIFICONTROL_VIEW_HPP

#include <gui/wificontrol_screen/WifiControlPresenter.hpp>
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
#include <map>
using namespace touchgfx;
using namespace std;

class WifiControlView : public DemoView<WifiControlPresenter>
{
public:
    WifiControlView();
    virtual ~WifiControlView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void setWifiState(bool);
    void startAnimation();
    void stopAnimation();
    bool isAnimationRunning();
    /*void updateListMenuElements();*/
    void clearListMenuElements();
    void updateListMenuElements(touchgfx::Unicode::UnicodeChar* strName, uint8_t address[], int rssi);
    void updateListMenuLayout();
    void stopListAnimation() { mList.stopAnimation(); }
protected:
    /*
    * Member Declarations
    */
    int count;
    Image menuBg;
    ToggleButton switchBtn;
    Button backBtn;
    TextArea WifiControlDevicesTitle;
    TextArea WifiControlTitle;
    CustomListElement MenuContainer;
    AnimatedImage animation;
    int tickCount;
    /*int numberOfListElements;
    CustomListElement listElements;*/
    ScrollableContainer scrollCnt;
    ListLayout list;
    CustomList mList;
    Callback<WifiControlView, const uint8_t> onImageMenuItemSelected;

	void getWifiState(bool);
    //map<int, CustomListElement> ListMenuMap;
    void handleTickEvent();

private:
    /*
    * Callback Handler Declarations
    */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void animationEnded(const AnimatedImage& source);
    void listElementClicked(CustomListElement& element);
    void onListMenuClick(CustomListElement element, const AbstractButton &button);

    /*
    * Callback Declarations
    */
    Callback<WifiControlView, const touchgfx::AbstractButton&> buttonCallback;
    Callback<WifiControlView, const AnimatedImage&> animationEndedCallback;
    Callback<WifiControlView, CustomListElement&> listElementClickedCallback;
};

#endif // WIFICONTROL_VIEW_HPP
