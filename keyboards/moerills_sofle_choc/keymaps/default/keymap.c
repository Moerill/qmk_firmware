/* Copyright 2023 Brian Low
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_german.h"

enum layers { _KOY, _PROG, _NAVI, _QWERTZ };

#define M_PROG MO(_PROG)
#define M_NAVI MO(_NAVI)

const uint16_t PROGMEM switch_default_koy_combo[]    = {KC_LCTL, KC_RCTL, DE_1, COMBO_END};
const uint16_t PROGMEM switch_default_qwertz_combo[] = {KC_LCTL, KC_RCTL, DE_2, COMBO_END};

enum toggles { KOY_TOGGLE, QWE_TOGGLE };

combo_t key_combos[] = {
    [KOY_TOGGLE] = COMBO_ACTION(switch_default_koy_combo),
    [QWE_TOGGLE] = COMBO_ACTION(switch_default_qwertz_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case KOY_TOGGLE:
            if (pressed) {
                layer_off(_QWERTZ);
                layer_on(_KOY);
            }
            break;
        case QWE_TOGGLE:
            if (pressed) {
                layer_off(_KOY);
                layer_on(_QWERTZ);
            }
            break;
    }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case KOY_TOGGLE:
        case QWE_TOGGLE:
            return 200;
    }

    return COMBO_TERM;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
     * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LCTL | LGUI | LCMD | LALT | /Enter  /       \Space \  | RALT | RCMD | RGUI | RCTL |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */

    [_KOY] = LAYOUT(KC_ESC, DE_1, DE_2, DE_3, DE_4, DE_5, /**/ DE_6, DE_7, DE_8, DE_9, DE_0, DE_SS,        //
                    KC_TAB, DE_K, DE_DOT, DE_O, DE_COMM, DE_Y, /**/ DE_P, DE_C, DE_L, DE_M, DE_F, DE_ADIA, //
                    KC_LSFT, DE_H, DE_A, DE_E, DE_I, DE_U, /**/ DE_D, DE_T, DE_R, DE_N, DE_S, KC_BSPC,     //
                    M_PROG, DE_X, DE_Q, DE_B, DE_UDIA, DE_ODIA, KC_MUTE, /**/ KC_MPLY, DE_J, DE_G, DE_W, DE_V, DE_Z,
                    KC_RSFT, //
                    KC_LCTL, KC_LALT, KC_LGUI, M_NAVI, KC_SPC, /**/ KC_ENT, M_NAVI, M_PROG, KC_RGUI, KC_RCTL),

    [_PROG] = LAYOUT(_______, _______, _______, _______, _______, _______, /* */ _______, _______, _______, _______, _______, _______,               //
                     QK_LEAD, _______, DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC, /* */ DE_EXLM, DE_LABK, DE_RABK, DE_EQL, DE_AMPR, _______,                //
                     _______, DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR, /* */ DE_QUES, DE_LPRN, DE_RPRN, DE_MINS, DE_COLN, _______,               //
                     _______, DE_HASH, DE_DLR, DE_PIPE, DE_TILD, DE_GRV, _______, /* */ _______, DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, DE_SCLN, DE_AT, //
                     _______, _______, _______, _______, _______, /* */ _______, _______, _______, _______, _______                                  //
                     ),

    [_NAVI] = LAYOUT(_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, /**/ KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,                                      //
                     KC_ESC, KC_PAGE_UP, KC_BSPC, KC_UP, KC_DEL, KC_PAGE_DOWN, /* */ _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_F23, KC_BSPC,              //
                     _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, /* */ _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_F22, _______,                  //
                     _______, KC_ESC, KC_TAB, KC_INSERT, KC_ENT, KC_UNDO, _______, /* */ _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_F21, _______, //
                     _______, _______, _______, _______, _______, /* */ _______, _______, _______, _______, _______                                    //
                     ),

    [_QWERTZ] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, /**/ KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV,                             //
                       KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, /**/ KC_Z, KC_U, KC_I, KC_O, KC_P, KC_BSPC,                            //
                       KC_GRV, KC_A, KC_S, KC_D, KC_F, KC_G, /**/ KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,                         //
                       KC_LSFT, KC_Y, KC_X, KC_C, KC_V, KC_B, KC_MUTE, /**/ KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, //
                       KC_LCTL, KC_LALT, KC_LGUI, M_NAVI, KC_SPC, /**/ KC_ENT, M_NAVI, M_PROG, KC_RGUI, KC_RCTL),

    //     KC_TAB,
    // DE_K, DE_U, DE_UDIA, DE_DOT, DE_ADIA, DE_V, DE_G, DE_C, DE_L, DE_J, DE_F, M_PROG, DE_H, DE_I, DE_E, DE_A, DE_O, DE_D, DE_T, DE_R, DE_N, DE_S, M_PROG, M_LSFT, DE_X, DE_Y, DE_ODIA, DE_COMM, DE_Q, DE_B, DE_P, DE_W, DE_M, DE_Z, M_RSFT, KC_LCTL, KC_LGUI, M_NAVI, KC_SPC, KC_ENT, M_NAVI, _______, KC_LALT, KC_1, KC_2, KC_3, KC_4
    //
    // ) LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, KC_LGUI, KC_LCMD, KC_LALT, KC_ENT, KC_SPC, KC_RALT, KC_RCMD, KC_RGUI, KC_RCTL)};
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_KOY]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
    [_PROG]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
    [_NAVI]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
    [_QWERTZ] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
};
#endif
