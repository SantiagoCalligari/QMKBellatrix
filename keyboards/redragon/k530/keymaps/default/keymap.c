#include "kb.h"
#include "config.h"
#include QMK_KEYBOARD_H
enum layer_names {
	Base,
	capa1,
	capa2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[Base] = KEYMAP(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MEDIA_PLAY_PAUSE, KC_HOME,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_INS, KC_PGUP,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_HASH, KC_ENT, KC_DEL, KC_PGDN,
		KC_LSFT, KC_BSLS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, KC_UP, KC_END,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, TO(capa1), TO(capa2), KC_LEFT, KC_DOWN, KC_RGHT),

	[capa1]=KEYMAP(
		KC_F1, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD, _______),

	[capa2]=KEYMAP(
        _______, KC_PIPE, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MPLY, KC_MPRV, KC_MNXT, _______, _______, _______, RESET,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

};
