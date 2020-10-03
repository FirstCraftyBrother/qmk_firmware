/* Copyright 2019-2020 DMQ Design
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

enum layers
{
  NumPad,
  Gaming,
  Work
};

uint8_t currentLayer;

//The below layers are intentionally empty in order to give a good starting point for how to configure multiple layers.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NumPad] = LAYOUT(/* Base */
                KC_KP_7, KC_KP_8, KC_KP_9, TO(NumPad),
                KC_KP_4, KC_KP_5, KC_KP_6, TO(Gaming),
                KC_KP_1, KC_KP_2, KC_KP_3, TO(Work),
                RGB_TOG, KC_KP_0, KC_ENTER
                ),

    [Gaming] = LAYOUT(/* Base */
                KC_F22, KC_F23, KC_F24, KC_TRNS,
                KC_F19, KC_F20, KC_F21, KC_TRNS,
                KC_F16, KC_F17, KC_F18, KC_TRNS,
                KC_F13, KC_F14, KC_F15
                ),

    [Work] = LAYOUT(/* Base */
                KC_F5, KC_NO, KC_NO, KC_TRNS,
                KC_NO, KC_NO, KC_NO, KC_TRNS,
                KC_NO, KC_NO, KC_NO, KC_TRNS,
                C(KC_C), C(KC_S), C(KC_V)
                )
};



void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        switch (currentLayer) {     //break each encoder update into a switch statement for the current layer
            case NumPad:
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
                break;
            case Gaming:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case Work:
                if (clockwise) {
                    tab_code16(C(KC_Y));
                } else {
                    tap_code16(C(KC_Z));
                }
                break;
        }
    } else if (index == 1) { /* Second encoder */
        switch (currentLayer) {
            case NumPad:
                if (clockwise) {
                } else {
                }
                break;
            case Gaming:
                if (clockwise) {
                } else {
                }
                break;
            case Work:
                if (clockwise) {
                    tab_code16(G(KC_RIGHT));
                } else {
                    tab_code16(G(KC_LEFT));
                }
                break;
        }
    } else if (index == 2) { /* Third encoder */
        switch (currentLayer) {
            case NumPad:
                if (clockwise) {
                } else {
                }
                break;
            case Gaming:
                if (clockwise) {
                } else {
                }
                break;
            case Work:
                if (clockwise) {
                    tap_code16(A(KC_TAB));
                } else {
                    tap_code16(A(S(KC_TAB)));
                }
                break;
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) { //This will run every time the layer is updated
    currentLayer = get_highest_layer(state);

    switch (currentLayer) {
        case NumPad:
            sethsv(HSV_WHITE, &led[0]); //Set the top LED to white for the bottom layer
            setrgb(0, 0, 0, &led[1]);
            setrgb(0, 0, 0, &led[2]);
            break;
        case Gaming:
            setrgb(0, 0, 0, &led[0]); //Set the middle LED to white for the middle layer
            sethsv(HSV_WHITE, &led[0]);
            setrgb(0, 0, 0, &led[2]);
            break;
        case Work:
            setrgb(0, 0, 0, &led[0]);
            setrgb(0, 0, 0, &led[1]);
            sethsv(HSV_WHITE, &led[0]);  //Set the bottom LED to white for the top layer
            break;
    }
    rgblight_set();
    return state;
}
