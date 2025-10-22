#ifndef LVGL_COMPAT_H
#define LVGL_COMPAT_H

#include <lvgl.h>

// ===== LVGL 7.x → 8.x COMPATIBILITY MACROS =====

// ===== 1. DISPLAY BUFFER =====
// LVGL 7: lv_disp_buf_t, lv_disp_buf_init()
// LVGL 8: lv_disp_draw_buf_t, lv_disp_draw_buf_init()
#define lv_disp_buf_t lv_disp_draw_buf_t
#define lv_disp_buf_init lv_disp_draw_buf_init

// ===== 2. DISPLAY DRIVER =====
// LVGL 7: disp_drv.buffer
// LVGL 8: disp_drv.draw_buf
// (Não é macro, correção manual necessária)

// ===== 3. EVENT CALLBACKS =====
// LVGL 7: lv_obj_set_event_cb(obj, callback)
// LVGL 8: lv_obj_add_event_cb(obj, callback, LV_EVENT_ALL, NULL)
// Wrapper para compatibilidade
static inline void lv_obj_set_event_cb_compat(lv_obj_t* obj, lv_event_cb_t cb) {
    lv_obj_add_event_cb(obj, cb, LV_EVENT_ALL, NULL);
}
#define lv_obj_set_event_cb lv_obj_set_event_cb_compat

// ===== 4. BUTTON FLAGS =====
// LVGL 7: lv_btn_set_checkable(btn, true/false)
// LVGL 8: lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE)
static inline void lv_btn_set_checkable(lv_obj_t* btn, bool enable) {
    if (enable)
        lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
    else
        lv_obj_clear_flag(btn, LV_OBJ_FLAG_CHECKABLE);
}

// ===== 5. BUTTON TOGGLE =====
// LVGL 7: lv_btn_toggle(btn)
// LVGL 8: lv_obj_add_state() / lv_obj_clear_state()
static inline void lv_btn_toggle(lv_obj_t* btn) {
    if (lv_obj_has_state(btn, LV_STATE_CHECKED))
        lv_obj_clear_state(btn, LV_STATE_CHECKED);
    else
        lv_obj_add_state(btn, LV_STATE_CHECKED);
}

// ===== 6. BUTTON STATE =====
// LVGL 7: lv_btn_get_state(btn) → retorna estado
// LVGL 8: lv_obj_get_state(btn) & LV_STATE_CHECKED
static inline uint8_t lv_btn_get_state(lv_obj_t* btn) {
    return lv_obj_get_state(btn) & LV_STATE_CHECKED ? LV_STATE_CHECKED : 0;
}
static inline void lv_btn_set_state(lv_obj_t* btn, uint8_t state) {
    if (state == LV_STATE_CHECKED)
        lv_obj_add_state(btn, LV_STATE_CHECKED);
    else
        lv_obj_clear_state(btn, LV_STATE_CHECKED);
}

// ===== 7. BUTTON STATE CONSTANTS =====
#define LV_BTN_STATE_RELEASED 0
#define LV_BTN_STATE_CHECKED_RELEASED LV_STATE_CHECKED

// ===== 8. KEYBOARD =====
// LVGL 7: lv_keyboard_set_cursor_manage(kb, bool)
// LVGL 8: Não existe mais (comportamento padrão)
static inline void lv_keyboard_set_cursor_manage(lv_obj_t* kb, bool manage) {
    // NOOP - recurso removido em LVGL 8.x
    (void)kb;
    (void)manage;
}

// ===== 9. TEXTAREA =====
// LVGL 7: lv_textarea_set_cursor_hidden(ta, bool)
// LVGL 8: lv_obj_set_style_opa()
static inline void lv_textarea_set_cursor_hidden(lv_obj_t* ta, bool hidden) {
    if (hidden)
        lv_obj_set_style_opa(ta, 0, LV_PART_CURSOR);
    else
        lv_obj_set_style_opa(ta, 255, LV_PART_CURSOR);
}

// ===== 10. ALIGN CONSTANTS =====
// LVGL 7: LV_ALIGN_IN_TOP_MID, LV_ALIGN_IN_BOTTOM_MID, etc.
// LVGL 8: LV_ALIGN_TOP_MID (sem "IN_")
#define LV_ALIGN_IN_TOP_MID LV_ALIGN_TOP_MID
#define LV_ALIGN_IN_BOTTOM_MID LV_ALIGN_BOTTOM_MID
#define LV_ALIGN_IN_LEFT_MID LV_ALIGN_LEFT_MID
#define LV_ALIGN_IN_RIGHT_MID LV_ALIGN_RIGHT_MID

// ===== 11. EVENT CONSTANTS =====
// LVGL 7: LV_EVENT_APPLY
// LVGL 8: LV_EVENT_READY (mais genérico)
#define LV_EVENT_APPLY LV_EVENT_READY

#endif // LVGL_COMPAT_H
