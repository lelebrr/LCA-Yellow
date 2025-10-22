#ifndef LVGL_COMPAT_H
#define LVGL_COMPAT_H

#include <lvgl.h>

// ===== LVGL 7.x → 8.x COMPATIBILITY LAYER =====

// Display buffer
#define lv_disp_buf_init lv_disp_draw_buf_init
#define lv_disp_buf_t lv_disp_draw_buf_t

// Display driver
#define buffer draw_buf

// Events
#define lv_obj_set_event_cb(obj, cb) lv_obj_add_event_cb(obj, cb, LV_EVENT_ALL, NULL)

// Buttons
#define lv_btn_set_checkable(btn, en) \
    if(en) lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE); \
    else lv_obj_clear_flag(btn, LV_OBJ_FLAG_CHECKABLE)

#define lv_btn_toggle(btn) \
    lv_obj_has_state(btn, LV_STATE_CHECKED) ? \
    lv_obj_clear_state(btn, LV_STATE_CHECKED) : \
    lv_obj_add_state(btn, LV_STATE_CHECKED)

#define lv_btn_get_state(btn) \
    (lv_obj_get_state(btn) & LV_STATE_CHECKED ? LV_STATE_CHECKED : 0)

#define lv_btn_set_state(btn, state) \
    (state == LV_STATE_CHECKED ? \
    lv_obj_add_state(btn, LV_STATE_CHECKED) : \
    lv_obj_clear_state(btn, LV_STATE_CHECKED))

// Button states
#define LV_BTN_STATE_RELEASED 0
#define LV_BTN_STATE_CHECKED_RELEASED LV_STATE_CHECKED

// Keyboard
#define lv_keyboard_set_cursor_manage(kb, en) // NOOP in LVGL 8.x

// Textarea
#define lv_textarea_set_cursor_hidden(ta, en) lv_obj_set_style_opa(ta, en ? 0 : 255, LV_PART_CURSOR)

// Align
#define LV_ALIGN_IN_TOP_MID LV_ALIGN_TOP_MID
#define LV_ALIGN_IN_BOTTOM_MID LV_ALIGN_BOTTOM_MID
#define LV_ALIGN_IN_LEFT_MID LV_ALIGN_LEFT_MID
#define LV_ALIGN_IN_RIGHT_MID LV_ALIGN_RIGHT_MID
#define LV_ALIGN_CENTER LV_ALIGN_CENTER

// Events comparison fix
static inline bool lv_event_equals(lv_event_t* e, lv_event_code_t code) {
    return lv_event_get_code(e) == code;
}

#define event_equals(e, code) (lv_event_get_code(e) == code)

#endif // LVGL_COMPAT_H
