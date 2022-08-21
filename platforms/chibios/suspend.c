/* TODO */

#include <ch.h>
#include <hal.h>
#include "config_common.h"

/* USB Device descriptor parameter */
/* VID:PID = AB16:B00B */
#define VENDOR_ID       0xAB16
#define PRODUCT_ID      0xB00B
#define DEVICE_VER      0x0001

#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define DIODE_DIRECTION COL2ROW

#define MATRIX_COL_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5, B6, B7}
#define MATRIX_ROW_PINS { D11, D10, D9, D8, D7}

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define LED_MATRIX_ROWS MATRIX_ROWS
#define LED_MATRIX_ROW_CHANNELS 3
#define LED_MATRIX_ROWS_HW (LED_MATRIX_ROWS * LED_MATRIX_ROW_CHANNELS)
/*                                                       (DISABLED)  PINS for UNDERGLOW------------=V------=-V */
#define LED_MATRIX_ROW_PINS { C6, C5, C4, C9, C8, C7, C12, C11, C10, B13, C14, C13, B14, B15, D3/*, D4, D5, D6*/}

#define LED_MATRIX_COLS MATRIX_COLS
/*               (DISABLED) PINS for UNDERGLOW (LAST TwO DISABLED TO AVOID PWM CHANNEL CONFLICT-------V-----------------------V */
#define LED_MATRIX_COL_PINS { A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5, B6, B7/*, B12, B11, B10, B9, C0, C1*/}

#define DRIVER_LED_TOTAL 72

/* RGB Matrix */
#ifdef RGB_MATRIX_ENABLE

#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define RGB_MATRIX_KEYPRESSES
#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_BAND_SAT
#   define ENABLE_RGB_MATRIX_BAND_VAL
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#   define ENABLE_RGB_MATRIX_CYCLE_ALL
#   define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#   define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#   define ENABLE_RGB_MATRIX_DUAL_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   define ENABLE_RGB_MATRIX_RAINDROPS
#   define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   define ENABLE_RGB_MATRIX_HUE_BREATHING
#   define ENABLE_RGB_MATRIX_HUE_PENDULUM
#   define ENABLE_RGB_MATRIX_HUE_WAVE
#   define ENABLE_RGB_MATRIX_PIXEL_RAIN
#   define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define ENABLE_RGB_MATRIX_SPLASH
#   define ENABLE_RGB_MATRIX_MULTISPLASH
#   define ENABLE_RGB_MATRIX_SOLID_SPLASH
#   define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
#include "matrix.h"
#include "action.h"
#include "action_util.h"
#include "mousekey.h"
#include "programmable_button.h"
#include "host.h"
#include "suspend.h"
#include "led.h"
#include "wait.h"

/** \brief suspend idle
 *
 * FIXME: needs doc
 */
void suspend_idle(uint8_t time) {
    // TODO: this is not used anywhere - what units is 'time' in?
    wait_ms(time);
}

/** \brief suspend power down
 *
 * FIXME: needs doc
 */
void suspend_power_down(void) {
    suspend_power_down_quantum();
    // on AVR, this enables the watchdog for 15ms (max), and goes to
    // SLEEP_MODE_PWR_DOWN

    wait_ms(17);
}

/** \brief suspend wakeup condition
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void matrix_power_up(void) {}
__attribute__((weak)) void matrix_power_down(void) {}
bool                       suspend_wakeup_condition(void) {
    matrix_power_up();
    matrix_scan();
    matrix_power_down();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        if (matrix_get_row(r)) return true;
    }
    return false;
}

/** \brief run user level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_wakeup_init_user(void) {}

/** \brief run keyboard level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_wakeup_init_kb(void) { suspend_wakeup_init_user(); }

/** \brief suspend wakeup condition
 *
 * run immediately after wakeup
 * FIXME: needs doc
 */
void suspend_wakeup_init(void) {
    // clear keyboard state
    // need to do it manually, because we're running from ISR
    //  and clear_keyboard() calls print
    // so only clear the variables in memory
    // the reports will be sent from main.c afterwards
    // or if the PC asks for GET_REPORT
    clear_mods();
    clear_weak_mods();
    clear_keys();
#ifdef MOUSEKEY_ENABLE
    mousekey_clear();
#endif /* MOUSEKEY_ENABLE */
#ifdef PROGRAMMABLE_BUTTON_ENABLE
    programmable_button_clear();
#endif /* PROGRAMMABLE_BUTTON_ENABLE */
#ifdef EXTRAKEY_ENABLE
    host_system_send(0);
    host_consumer_send(0);
#endif /* EXTRAKEY_ENABLE */

    suspend_wakeup_init_quantum();
}
