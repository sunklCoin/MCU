#ifndef REMOTERTOUCHCONTROLLER_HPP
#define REMOTERTOUCHCONTROLLER_HPP

#include <platform/driver/touch/TouchController.hpp>

#define EXAMPLE_I2C_MASTER_BASE (I2C2_BASE)
#define I2C_MASTER_CLOCK_FREQUENCY (12000000)
#define EXAMPLE_I2C_MASTER ((I2C_Type *)EXAMPLE_I2C_MASTER_BASE)
#define I2C_MASTER_SLAVE_ADDR_7BIT 0x7EU
#define I2C_BAUDRATE 100000U

namespace touchgfx
{
  class RemoterTouchController : public TouchController
  {
    void init();
    bool sampleTouch(int32_t& x, int32_t& y);
  };
  
}

#endif /* REMOTERTOUCHCONTROLLER_HPP */
