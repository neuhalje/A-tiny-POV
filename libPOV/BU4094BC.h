#ifndef ATPOV_BU4094BC_H
#define ATPOV_BU4094BC_H


#include <stdint.h>
#include "device.h"

/*!
 * Drives a BU4094BC shift register.
 */
class BU4094BC {
public:

    /*!
     *
     * @param _device
     * @param pin_BU4094BC_strobe       0-based pin (on PORTB) that connects to STROBE on the BU4094BC
     * @param pin_BU4094BC_clk          0-based pin (on PORTB) that connects to CLK on the BU4094BC
     * @param pin_BU4094BC_serial_in    0-based pin (on PORTB) that connects to SERIAL IN on the BU4094BC
     */
    BU4094BC(Device &_device, uint8_t pin_BU4094BC_strobe, uint8_t pin_BU4094BC_clk,
             uint8_t pin_BU4094BC_serial_in);

    /*!
     * \brief Output \byte column on the LEDs.
     * \param byte Bit encoded state of the LEDs (0: off, 1: on).
     *               LEDs are counted from the bottom (LSB) to
     *               the top (MSB) of the glyph.
     * \return void
     */
    void output(uint8_t byte);

protected:
    Device &_device;

    /*!
     * The pin (on PORTB) that connects to STROBE on the BU4094BC
     *
     * 0 : PIN1
     * 1 : PIN2
     * 2 : PIN3
     * 4 : PIN4
     * ..
     * 2^(n-1) : PIN n
     */
    uint8_t _pin_mask_BU4094BC_strobe;

    /*!
    * The pin (on PORTB) that connects to CLK on the BU4094BC
    */
    uint8_t _pin_mask_BU4094BC_clk;

    /*!
    * The pin (on PORTB) that connects to SERIAL IN on the BU4094BC
    */
    uint8_t _pin_mask_BU4094BC_serial_in;


    inline void high(uint8_t mask) {
        PORTB |= mask;
    }

    inline void low(uint8_t mask) {
        PORTB &= ~mask;
    }
};


#endif //ATPOV_BU4094BC_H
