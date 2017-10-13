/***********************************/
/********** sunkelong add **********/
/*************2017-10-03************/
#ifndef MIC_SCREEN_PRESENTER_HPP
#define MIC_SCREEN_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/common/DemoPresenter.hpp>

using namespace touchgfx;

class MicScreenView;

class MicScreenPresenter : public DemoPresenter
{
public:
	MicScreenPresenter(MicScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

	virtual ~MicScreenPresenter() {};
	virtual void startRecord();
	virtual void finishRecord();
	virtual void cancelRecord();
    virtual void onTransferConnectState(bool state);
    void transferReConnect();
    int getWifiSendDataState();
private:
	MicScreenPresenter();

	MicScreenView& view;
};


#endif // MIC_SCREEN_PRESENTER_HPP
