#pragma once

static lv_color_t m5dial_anim_from;
static lv_color_t m5dial_anim_to;

static void m5dial_bg_anim_cb(void* obj, int32_t v) {
    // v runs 0→255; mix(to, from, 255-v) gives from→to
    lv_color_t c = lv_color_mix(m5dial_anim_to, m5dial_anim_from, v);
    lv_obj_set_style_bg_color((lv_obj_t*)obj, c, LV_PART_MAIN);
}

static void m5dial_animate_bg(lv_obj_t* obj, lv_color_t target, uint32_t ms) {
    lv_anim_del(obj, m5dial_bg_anim_cb);
    m5dial_anim_from = lv_obj_get_style_bg_color(obj, LV_PART_MAIN);
    m5dial_anim_to = target;
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_exec_cb(&a, m5dial_bg_anim_cb);
    lv_anim_set_time(&a, ms);
    lv_anim_set_values(&a, 0, 255);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
    lv_anim_start(&a);
}
