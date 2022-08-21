/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once


/* key matrix size */
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


#include <stdint.h>
#include "keyboard.h"
#include "action.h"

#ifdef DYNAMIC_KEYMAP_ENABLE
#    ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#        define DYNAMIC_KEYMAP_LAYER_COUNT 4
#    endif
#    if DYNAMIC_KEYMAP_LAYER_COUNT <= 8
#        ifndef LAYER_STATE_8BIT
#            define LAYER_STATE_8BIT
#        endif
#    elif DYNAMIC_KEYMAP_LAYER_COUNT <= 16
#        ifndef LAYER_STATE_16BIT
#            define LAYER_STATE_16BIT
#        endif
#    else
#        ifndef LAYER_STATE_32BIT
#            define LAYER_STATE_32BIT
#        endif
#    endif
#endif

#if !defined(LAYER_STATE_8BIT) && !defined(LAYER_STATE_16BIT) && !defined(LAYER_STATE_32BIT)
#    define LAYER_STATE_32BIT
#endif

#if defined(LAYER_STATE_8BIT)
typedef uint8_t layer_state_t;
#    define MAX_LAYER_BITS 3
#    ifndef MAX_LAYER
#        define MAX_LAYER 8
#    endif
#    define get_highest_layer(state) biton(state)
#elif defined(LAYER_STATE_16BIT)
typedef uint16_t layer_state_t;
#    define MAX_LAYER_BITS 4
#    ifndef MAX_LAYER
#        define MAX_LAYER 16
#    endif
#    define get_highest_layer(state) biton16(state)
#elif defined(LAYER_STATE_32BIT)
typedef uint32_t layer_state_t;
#    define MAX_LAYER_BITS 5
#    ifndef MAX_LAYER
#        define MAX_LAYER 32
#    endif
#    define get_highest_layer(state) biton32(state)
#else
#    error Layer Mask size not specified.  HOW?!
#endif

/*
 * Default Layer
 */
extern layer_state_t default_layer_state;
void                 default_layer_debug(void);
void                 default_layer_set(layer_state_t state);

__attribute__((weak)) layer_state_t default_layer_state_set_kb(layer_state_t state);
__attribute__((weak)) layer_state_t default_layer_state_set_user(layer_state_t state);

#ifndef NO_ACTION_LAYER
/* bitwise operation */
void default_layer_or(layer_state_t state);
void default_layer_and(layer_state_t state);
void default_layer_xor(layer_state_t state);
#else
#    define default_layer_or(state)
#    define default_layer_and(state)
#    define default_layer_xor(state)
#endif

/*
 * Keymap Layer
 */
#ifndef NO_ACTION_LAYER
extern layer_state_t layer_state;

void layer_state_set(layer_state_t state);
bool layer_state_is(uint8_t layer);
bool layer_state_cmp(layer_state_t layer1, uint8_t layer2);

void layer_debug(void);
void layer_clear(void);
void layer_move(uint8_t layer);
void layer_on(uint8_t layer);
void layer_off(uint8_t layer);
void layer_invert(uint8_t layer);
/* bitwise operation */
void          layer_or(layer_state_t state);
void          layer_and(layer_state_t state);
void          layer_xor(layer_state_t state);
layer_state_t layer_state_set_user(layer_state_t state);
layer_state_t layer_state_set_kb(layer_state_t state);
#else
#    define layer_state 0

#    define layer_state_set(layer)
#    define layer_state_is(layer) (layer == 0)
#    define layer_state_cmp(state, layer) (state == 0 ? layer == 0 : (state & (layer_state_t)1 << layer) != 0)

#    define layer_debug()
#    define layer_clear()
#    define layer_move(layer) (void)layer
#    define layer_on(layer) (void)layer
#    define layer_off(layer) (void)layer
#    define layer_invert(layer) (void)layer
#    define layer_or(state) (void)state
#    define layer_and(state) (void)state
#    define layer_xor(state) (void)state
#    define layer_state_set_kb(state) (void)state
#    define layer_state_set_user(state) (void)state
#endif

/* pressed actions cache */
#if !defined(NO_ACTION_LAYER) && !defined(STRICT_LAYER_RELEASE)

void    update_source_layers_cache(keypos_t key, uint8_t layer);
uint8_t read_source_layers_cache(keypos_t key);
#endif
action_t store_or_get_action(bool pressed, keypos_t key);

/* return the topmost non-transparent layer currently associated with key */
uint8_t layer_switch_get_layer(keypos_t key);

/* return action depending on current layer status */
action_t layer_switch_get_action(keypos_t key);
