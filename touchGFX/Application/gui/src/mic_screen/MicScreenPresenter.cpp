/***********************************/
/********** sunkelong add **********/
/*************2017-10-03************/
#include <gui/mic_screen/MicScreenView.hpp>
#include <gui/mic_screen/MicScreenPresenter.hpp>
#include <gui/framework/DevicePort.h>

MicScreenPresenter::MicScreenPresenter(MicScreenView& v)
:DemoPresenter(v),
 view(v)
{

}

void MicScreenPresenter::activate()
{
    //Mic_CreatTransferConnect();
    view.onPrepareState(true);
}

void MicScreenPresenter::deactivate()
{
    Mic_DestroyTransferConnect();
}

void MicScreenPresenter::startRecord()
{
	Mic_StartRecord();
}

void MicScreenPresenter::finishRecord()
{
	Mic_FinishRecord();
}

void MicScreenPresenter::cancelRecord()
{
	Mic_CancelRecord();
}

void MicScreenPresenter::onTransferConnectState(bool state)
{
    view.onPrepareState(state);
}

void MicScreenPresenter::transferReConnect()
{
    Mic_CreatTransferConnect();
}

int MicScreenPresenter::getWifiSendDataState()
{
    return  10;
}