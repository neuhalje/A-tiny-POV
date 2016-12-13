#ifndef ATPOV_BU4094BC_H
#define ATPOV_BU4094BC_H


#include <stdint.h>
#include "device.h"

/*!
 * Drives a BU4094BC shift register.
 *
 * From the ROHM datasheet:
 *
 *   The BU4094BC, BU4094BCF, and BU4094BCFV are shift / store registers, each consisting of an 8-bit register and
 *   an 8-bit latch.
 *   As the data in the shift register can be latched by an asynchronous strobe input, it is possible to hold the
 *   output in the data transfer mode.
 *   The tri-state parallel output can be connected directly with an 8-bit bus line.
 *   These registers are suitable for in-line / parallel data conversion, data receivers and other similar
 *   applications.
 *
 * This implementation assumes that OE is enabled (pull-up).
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

    /*!
     * \brief Set clock to HIGH.
     *
     * Make sure that the minimum timings  of the BU4094BC are respected
     */
    inline void tick() {
        high(_pin_mask_BU4094BC_clk);

        // TODO: better check timings
        _device.delay_us(10);
    }


    /*!
      * \brief Set clock to LOW.
      *
      * Make sure that the minimum timings  of the BU4094BC are respected
      */
    inline void tock() {
        low(_pin_mask_BU4094BC_clk);

        // TODO: better check timings
        _device.delay_us(10);
    }

    inline void write_Sout(bool value) {
        if (value) {
            high(_pin_mask_BU4094BC_serial_in);
        } else {
            low(_pin_mask_BU4094BC_serial_in);
        }
    }
};


#endif //ATPOV_BU4094BC_H
