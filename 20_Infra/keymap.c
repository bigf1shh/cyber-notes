/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
// 1. Los nombres de los bailes
enum {
    TD_AMPR_PASTE= 0,
    TD_PLUS_COPY
};
enum custom_keycodes {
    M_PIPE = SAFE_RANGE, // | (AltGr + 1)
    M_AT,               // @ (AltGr + 2)
    M_HASH,             // # (AltGr + 3)
    M_TILDE,            // ~ (AltGr + 4)
    M_EURO,             // € (AltGr + 5)
    M_LBRC,             // [ (AltGr + [)
    M_RBRC,             // ] (AltGr + ])
    M_LCBR,             // { (AltGr + ')
    M_RCBR,             // } (AltGr + ç)
    M_BSLS,             // \ (AltGr + º)
    //M_LPRN,             // ( (Shift + 8)
    //M_RPRN,             // ) (Shift + 9)
    //M_COPY,             // Ctrl + C
    //M_PASTE             // Ctrl + V
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            // --- GRUPO ALT GR (Símbolos de programación y €) ---
            case M_PIPE:  register_code(KC_RALT); wait_ms(20); register_code(KC_1);    unregister_code(KC_1);    unregister_code(KC_RALT); return false;
            case M_AT:    register_code(KC_RALT); wait_ms(20); register_code(KC_2);    unregister_code(KC_2);    unregister_code(KC_RALT); return false;
            case M_HASH:  register_code(KC_RALT); wait_ms(20); register_code(KC_3);    unregister_code(KC_3);    unregister_code(KC_RALT); return false;
            case M_TILDE: register_code(KC_RALT); wait_ms(20); register_code(KC_4);    unregister_code(KC_4);    unregister_code(KC_RALT); return false;
            case M_EURO:  register_code(KC_RALT); wait_ms(20); register_code(KC_5);    unregister_code(KC_5);    unregister_code(KC_RALT); return false;
            case M_LBRC:  register_code(KC_RALT); wait_ms(20); register_code(KC_LBRC); unregister_code(KC_LBRC); unregister_code(KC_RALT); return false;
            case M_RBRC:  register_code(KC_RALT); wait_ms(20); register_code(KC_RBRC); unregister_code(KC_RBRC); unregister_code(KC_RALT); return false;
            case M_LCBR:  register_code(KC_RALT); wait_ms(20); register_code(KC_QUOT); unregister_code(KC_QUOT); unregister_code(KC_RALT); return false;
            case M_RCBR:  register_code(KC_RALT); wait_ms(20); register_code(KC_NUHS); unregister_code(KC_NUHS); unregister_code(KC_RALT); return false;
            case M_BSLS:  register_code(KC_RALT); wait_ms(20); register_code(KC_GRV);  unregister_code(KC_GRV);  unregister_code(KC_RALT); return false;

            // --- GRUPO SHIFT (Paréntesis) ---
            //case M_LPRN:  register_code(KC_LSFT); wait_ms(20); register_code(KC_8);    unregister_code(KC_8);    unregister_code(KC_LSFT); return false;
            //case M_RPRN:  register_code(KC_LSFT); wait_ms(20); register_code(KC_9);    unregister_code(KC_9);    unregister_code(KC_LSFT); return false;

            // --- GRUPO CONTROL (Copiar/Pegar) ---
            //case M_COPY:  register_code(KC_LCTL); wait_ms(20); register_code(KC_C);    unregister_code(KC_C);    unregister_code(KC_LCTL); return false;
            ////case M_PASTE: register_code(KC_LCTL); wait_ms(20); register_code(KC_V);    unregister_code(KC_V);    unregister_code(KC_LCTL); return false;
        }
    }
    return true;
}

// Función para & (1 toque) y Pegar (2 toques)
//void dance_ampr_paste_finished(tap_dance_state_t *state, void *user_data) {
//    if (state->count == 1) {
//        // Un toque: & (Shift + 6) + 20ms para RDP
//        register_code(KC_LSFT); wait_ms(20); register_code(KC_6); unregister_code(KC_6); unregister_code(KC_LSFT);
//    } else {
//        // Dos toques: Ctrl + V (Tu macro M_PASTE)
//        register_code(KC_LCTL); wait_ms(20); register_code(KC_V); unregister_code(KC_V); unregister_code(KC_LCTL);
//    }
//}
//
//// Función para / (1 toque) y Copiar (2 toques)
//void dance_plus_copy_finished(tap_dance_state_t *state, void *user_data) {
//    if (state->count == 1) {
//        // Un toque: / (Shift + 7) + 20ms para RDP
//        register_code(KC_LSFT); wait_ms(20); register_code(KC_7); unregister_code(KC_7); unregister_code(KC_LSFT);
//    } else {
//        // Dos toques: Ctrl + C (Tu macro M_COPY)
//        register_code(KC_LCTL); wait_ms(20); register_code(KC_C); unregister_code(KC_C); unregister_code(KC_LCTL);
//    }
//}

tap_dance_action_t tap_dance_actions[] = {
    // Usamos FN_ADVANCED: (Función al pulsar, Función al terminar, Función al cancelar)
    [TD_AMPR_PASTE] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_6), LCTL(KC_V)),
    [TD_PLUS_COPY]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_7), LCTL(KC_C))
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  LT(3,KC_TAB),  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,MO(1),LALT_T(KC_SPC),  KC_SPC,  LT(2,KC_ENT), KC_LCTL
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                         KC_6,     KC_7,    KC_8,   KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX,KC_LCTL, KC_LSFT, KC_DEL,                     KC_LEFT,  KC_DOWN, KC_UP,  KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_PGUP, KC_HOME,  KC_END,  KC_PGDN, KC_PSCR, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,     KC_SPC,   MO(4), _______
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TAB,   M_PIPE,  M_AT,   M_HASH ,  M_TILDE, M_EURO,                     KC_EQL,  KC_MINS,  M_LCBR,  M_RCBR,   KC_BSLS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL,  KC_EXLM,  KC_AT, KC_HASH,  KC_DLR, KC_PERC,                 TD(TD_AMPR_PASTE),TD(TD_PLUS_COPY), KC_ASTR, KC_LPRN, KC_RPRN, KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT,  KC_CAPS, XXXXXXX, XXXXXXX, KC_NUBS, S(KC_NUBS),                  KC_RBRC, LSFT(KC_RBRC),M_LBRC,M_RBRC, M_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,  MO(4),  _______,     KC_ENT, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PPLS, KC_1,    KC_2,    KC_3,   KC_AMPR, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PAST , KC_4,   KC_5,    KC_6,    KC_SLSH,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,     KC_ENT, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                  KC_F6 ,KC_F7 ,   KC_F8 ,  KC_F9 , KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,                    KC_VOLU, KC_BRMU, KC_MPLY,  KC_F11, KC_F12, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                   KC_VOLD,KC_BRMD,KC_MPRV,KC_MNXT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,     KC_ENT, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
