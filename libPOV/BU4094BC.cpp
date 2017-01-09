#include "BU4094BC.h"

void BU4094BC::output(uint8_t byte) {


    // Strobe:
    //    - High: Keep old values
    //    - Low: Copy shift register to latch (output)
    //
    //  OE (Output Enabled): Assumed to be high via pull-up
    //
    //  Clock:
    //    - Data is read from Sin at rising edge


    uint8_t mask = 1;
    for (uint8_t i = 0; i < 8; i++) {
        clockLow();  // force known clock state

        write_Sout(byte & mask);

        clockHigh();

        mask <<= 1;
    }

    clockLow();

    // now latch
    low(_pin_mask_BU4094BC_strobe);
    clockHigh();
    clockLow();
    high(_pin_mask_BU4094BC_strobe);


}

BU4094BC::BU4094BC(Device &_device, uint8_t _pin_BU4094BC_strobe, uint8_t _pin_BU4094BC_clk,
                   uint8_t _pin_BU4094BC_serial_in)
        : _device(_device), _pin_mask_BU4094BC_strobe((uint8_t) (1 << _pin_BU4094BC_strobe)),
          _pin_mask_BU4094BC_clk((uint8_t) (1 << _pin_BU4094BC_clk)),
          _pin_mask_BU4094BC_serial_in((uint8_t) (1 << _pin_BU4094BC_serial_in)) {

    DDRB = (DDRB | _pin_mask_BU4094BC_clk | _pin_mask_BU4094BC_serial_in | _pin_mask_BU4094BC_strobe);
    high(_pin_mask_BU4094BC_strobe);
    low(_pin_mask_BU4094BC_clk);
}
