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

}

void MicScreenPresenter::deactivate()
{

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

