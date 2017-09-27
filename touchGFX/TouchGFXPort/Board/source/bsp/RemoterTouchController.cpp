#include <bsp/RemoterTouchController.hpp>
#include <touchgfx/transforms/TouchCalibration.hpp>

extern "C"
{
#include "board.h"
#include "fsl_i2c.h"
#include "fsl_touch_ft5406.h"
}
using namespace touchgfx;

ft5406_handle_t touchgfx_tp_handle;
touch_event_t touchgfx_tp_event;


void RemoterTouchController::init()
{   
  FT5406_Init(&touchgfx_tp_handle, EXAMPLE_I2C_MASTER);
}

bool RemoterTouchController::sampleTouch(int32_t& x, int32_t& y)
{
  int tmp_x = -1, tmp_y = -1;
  
  if (kStatus_Success == FT5406_GetSingleTouch(&touchgfx_tp_handle, &touchgfx_tp_event, &tmp_x, &tmp_y))
  {
    if ((touchgfx_tp_event == kTouch_Down) || (touchgfx_tp_event == kTouch_Contact))
    {
      /*Swap X, Y coordinates */
      x = tmp_y;
      y = tmp_x;
      return true;
    }
  }
  return false;
}

