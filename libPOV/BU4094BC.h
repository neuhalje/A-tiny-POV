#ifndef ATPOV_BU4094BC_H
#define ATPOV_BU4094BC_H


#include <stdint.h>
#include "device.h"

/*!
 * \brief Drives a BU4094BC shift register.
 *
 * From the ROHM datasheet:
 *
 *  >  The BU4094BC, BU4094BCF, and BU4094BCFV are shift / store registers, each consisting of an 8-bit register and
 *  > an 8-bit latch.
 *  > As the data in the shift register can be latched by an asynchronous strobe input, it is possible to hold the
 *  > output in the data transfer mode.
 *  > The tri-state parallel output can be connected directly with an 8-bit bus line.
 *  > These registers are suitable for in-line / parallel data conversion, data receivers and other similar
 *  > applications.
 *
 * This implementation assumes that OE is enabled (pull-up).
 */
class BU4094BC {
public:

    /*!
     *
     * Creates the driver and initializes the shift register.
     *
     * @param _device
     * @param port                      port to use, e.g. PORTB. The pins must already be set to 'out'
     * @param pin_BU4094BC_strobe       0-based pin (on \ref port) that connects to STROBE on the BU4094BC
     * @param pin_BU4094BC_clk          0-based pin (on \ref port) that connects to CLK on the BU4094BC
     * @param pin_BU4094BC_serial_in    0-based pin (on \ref port) that connects to SERIAL IN on the BU4094BC
     */
    BU4094BC(Device &_device, volatile uint8_t &port, uint8_t pin_BU4094BC_strobe, uint8_t pin_BU4094BC_clk,
             uint8_t pin_BU4094BC_serial_in);

    /*!
     * \brief Output \ref byte column on the LEDs.
     *
     * @param byte Bit encoded state of the LEDs (0: off, 1: on).
     *               LEDs are counted from the bottom (LSB) to
     *               the top (MSB) of the glyph.
     *
     * @return void
     */
    void output(uint8_t byte);

protected:
    Device &_device;
    volatile uint8_t &_port;

public: // for testing!

    /*!
     * The pin mask (on \ref port) that connects to STROBE on the BU4094BC
     *
     * e.g.
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
    * The pin (on \ref port) that connects to CLK on the BU4094BC
    */
    uint8_t _pin_mask_BU4094BC_clk;

    /*!
    * The pin (on \ref port) that connects to SERIAL IN on the BU4094BC
    */
    uint8_t _pin_mask_BU4094BC_serial_in;

    /*!
    * \brief Set all port bits set in \ref mask to HIGH.
    *
    * The following code will set  bit#2 in port to HIGH and keeps the other bits untouched.
    *
    * \code  low(0b00000100)  \endcode
    *
    * @param mask E.g. 0b10100100
    */
    inline void high(uint8_t mask) {
        _port |= mask;
    }

    /*!
    * \brief Set all port bits set in \ref mask to LOW.
    *
    * The following code will set  bit#2 in port to LOW and keeps the other bits untouched.
     *
    * \code  low(0b00000100)  \endcode
    *
    * @param mask E.g. 0b00000100
    */
    inline void low(uint8_t mask) {
        _port &= (uint8_t) ~mask;
    }

    /*!
     * \brief Set clock to HIGH.
     *
     * Ensures that the minimum timings of the BU4094BC are respected
     */
    inline void clockHigh() {
        high(_pin_mask_BU4094BC_clk);

        // TODO: better check timings
        _device.delay_us(10);
    }


    /*!
      * \brief Set clock to LOW.
      *
      * Ensures that the minimum timings  of the BU4094BC are respected
      */
    inline void clockLow() {
        low(_pin_mask_BU4094BC_clk);

        // TODO: better check timings
        _device.delay_us(10);
    }

    /*!
   * \brief Set strobe to HIGH.
   *
   */
    inline void strobeHigh() {
        high(_pin_mask_BU4094BC_strobe);
    }


    /*!
      * \brief Set clock to LOW.
      *
      * Ensures that the minimum timings  of the BU4094BC are respected
      */
    inline void strobeLow() {
        low(_pin_mask_BU4094BC_strobe);

    }

    /*!
     * \brief Write bit \ref value into the shift register.
     *
     * @param value
     */
    inline void write_Sout(bool value) {
        if (value) {
            high(_pin_mask_BU4094BC_serial_in);
        } else {
            low(_pin_mask_BU4094BC_serial_in);
        }
    }
};


#endif //ATPOV_BU4094BC_H
