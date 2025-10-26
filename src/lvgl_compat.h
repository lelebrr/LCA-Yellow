#pragma once
#ifndef LVGL_COMPAT_H
#define LVGL_COMPAT_H

#include <lvgl.h>

/*
 * Este arquivo de compatibilidade mapeia funções e tipos da LVGL v7 (API antiga)
 * para a v8 (API nova), permitindo que o código legado compile com o mínimo
 * de alterações manuais.
 *
 * Mapeamentos Chave:
 * - Funções de objeto: lv_obj_...() -> lv_obj_...() (geralmente nomes similares)
 * - Cores: lv_color_make(...) -> lv_color_hex(...)
 * - Símbolos: LV_SYMBOL_... -> LV_SYMBOL_... (sem alterações)
 * - Alinhamento: LV_ALIGN_... -> LV_ALIGN_... (sem alterações)
 * - Eventos: LV_EVENT_... -> LV_EVENT_... (sem alterações)
 *
 * Funções que exigem refatoração manual (não mapeadas aqui):
 * - lv_cont_create() -> lv_obj_create()
 * - lv_page_create() -> lv_obj_create()
 * - lv_btn_create() -> lv_btn_create() (já é um tipo de objeto)
 * - lv_label_create() -> lv_label_create() (já é um tipo de objeto)
 * - Estilos: A API de estilos da v8 é completamente diferente e requer
 *   refatoração manual usando lv_obj_add_style() e objetos lv_style_t.
 *   Este arquivo NÃO trata de estilos.
 */

// Mapeamento de Funções de Criação de Widgets (Básico)
// NOTA: O código original deve ser atualizado para usar os novos widgets
// quando possível. Isso é apenas para compatibilidade básica.
#define lv_cont_create(parent, obj_to_copy) lv_obj_create(parent)
#define lv_page_create(parent, obj_to_copy) lv_obj_create(parent)

// Funções de Objeto (Mapeamentos diretos 1:1)
#define lv_obj_set_size(obj, w, h) lv_obj_set_size(obj, w, h)
#define lv_obj_set_pos(obj, x, y) lv_obj_set_pos(obj, x, y)
#define lv_obj_align(obj, base, align, x_mod, y_mod) lv_obj_align(obj, align, x_mod, y_mod)
#define lv_obj_set_event_cb(obj, cb) lv_obj_add_event_cb(obj, cb, LV_EVENT_ALL, NULL)
#define lv_obj_get_event_data(obj) lv_event_get_user_data(obj) // Varia, mas é um ponto de partida
#define lv_event_get_data() lv_event_get_user_data(NULL) // Substituir por `lv_event_get_user_data(e)` no callback

// Funções de Label
#define lv_label_set_text(obj, txt) lv_label_set_text(obj, txt)
#define lv_label_set_long_mode(obj, mode) lv_label_set_long_mode(obj, mode)
#define lv_label_set_align(obj, align) lv_label_set_text_align(obj, align)

// Funções de Lista
#define lv_list_create(parent, obj_to_copy) lv_list_create(parent)
#define lv_list_add_btn(list, icon, txt) lv_list_add_text(list, txt) // Simplificado: v8 usa `lv_list_add_text`
#define lv_list_get_btn_text(list, btn) lv_list_get_btn_text(list, btn)
#define lv_list_clean(list) lv_obj_clean(list)

// Funções de Cores
#define lv_color_make(r, g, b) lv_color_hex((r << 16) | (g << 8) | b)
#define LV_COLOR_WHITE lv_color_hex(0xFFFFFF)
#define LV_COLOR_BLACK lv_color_hex(0x000000)
#define LV_COLOR_RED lv_color_hex(0xFF0000)
#define LV_COLOR_LIME lv_color_hex(0x00FF00)
#define LV_COLOR_BLUE lv_color_hex(0x0000FF)

// Estados de Objeto (v7 -> v8)
#define LV_STATE_DEFAULT LV_STATE_DEFAULT
#define LV_STATE_CHECKED LV_STATE_CHECKED
#define LV_STATE_FOCUSED LV_STATE_FOCUSED
#define LV_STATE_EDITED LV_STATE_EDITED
#define LV_STATE_HOVERED LV_STATE_HOVERED
#define LV_STATE_PRESSED LV_STATE_PRESSED
#define LV_STATE_DISABLED LV_STATE_DISABLED

// Funções de Estilo (AVISO: Mapeamento de compatibilidade MUITO limitado)
// O código que usa estilos DEVE SER REATORADO.
// Isto é apenas para evitar erros de compilação em casos simples.
#define lv_obj_set_style_local_bg_color(obj, part, state, color) lv_obj_set_style_bg_color(obj, color, part | state)
#define lv_obj_set_style_local_text_color(obj, part, state, color) lv_obj_set_style_text_color(obj, color, part | state)
#define LV_OBJ_PART_MAIN LV_PART_MAIN

#endif // LVGL_COMPAT_H
