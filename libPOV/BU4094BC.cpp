#include "BU4094BC.h"

void BU4094BC::output(uint8_t byte) {

    uint8_t mask = 1;
    for (uint8_t i = 0; i < 8; i++) {

        low(_pin_mask_BU4094BC_clk);
        _device.delay_us(1);

        if (byte & mask) {
            high(_pin_mask_BU4094BC_serial_in);
        } else {
            low(_pin_mask_BU4094BC_serial_in);
        }

        high(_pin_mask_BU4094BC_clk);
        _device.delay_us(1);

        mask <<= 1;
    }


    // now latch
    low(_pin_mask_BU4094BC_clk);
    high(_pin_mask_BU4094BC_strobe);
    _device.delay_us(1);

    high(_pin_mask_BU4094BC_clk);
    _device.delay_us(1);
    low(_pin_mask_BU4094BC_clk);
}

BU4094BC::BU4094BC(Device &_device, uint8_t _pin_BU4094BC_strobe, uint8_t _pin_BU4094BC_clk,
                   uint8_t _pin_BU4094BC_serial_in)
        : _device(_device), _pin_mask_BU4094BC_strobe(1 << _pin_BU4094BC_strobe),
          _pin_mask_BU4094BC_clk(1 << _pin_BU4094BC_clk),
          _pin_mask_BU4094BC_serial_in(1 << _pin_BU4094BC_serial_in) {

    DDRB = (DDRB | _pin_mask_BU4094BC_clk | _pin_mask_BU4094BC_serial_in | _pin_mask_BU4094BC_strobe);
}
