// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: indicator_ha

#include "ui.h"
#include "view_data.h"
#include "widgets/lv_slider.h"
#include "widgets/lv_textarea.h"

static char* TAG = "ui_events";

// When the widget value changed, this function will be triggered.
void switch_event_cb(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    if (target == NULL) {
        ESP_LOGE(TAG, "Invalid event target");
        return;
    }

    struct view_data_ha_switch_data switch_data = {
        .value = lv_obj_has_state(target, LV_STATE_CHECKED) ? 1 : 0,
        .index = -1
    };

    if (target == ui_switch1) switch_data.index = 0;
    else if (target == ui_switch2) switch_data.index = 1;
    else if (target == ui_switch3) switch_data.index = 2;
    else if (target == ui_switch4) switch_data.index = 3;
    else if (target == ui_switch6) switch_data.index = 5;
    else if (target == ui_switch7) switch_data.index = 6;
    else {
        ESP_LOGW(TAG, "Unknown switch target");
        return;
    }

    ESP_LOGI(TAG, "Switch %d: %d", switch_data.index + 1, switch_data.value);

    esp_err_t err = esp_event_post_to(view_event_handle, VIEW_EVENT_BASE, VIEW_EVENT_HA_SWITCH_ST, 
                                      &switch_data, 
                                      sizeof(switch_data), 
                                      portMAX_DELAY);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to post switch event: %s", esp_err_to_name(err));
    }
}

void switch_arc_event_cb(lv_event_t* e) {
	lv_obj_t* target = lv_event_get_target(e);

	struct view_data_ha_switch_data switch_data = {0};

	if(target == ui_switch5_arc1)
	{
		lv_arc_t* tr_arc = (lv_arc_t*)target;
		switch_data.value = (int)tr_arc->value;
		switch_data.index = 4;
	}
	else if(target == ui_switch8_slider1)
	{
		switch_data.value = (int)lv_slider_get_value(target);
		switch_data.index = 7;
	}

	ESP_LOGI(TAG, " switch%d: %d", switch_data.index + 1, switch_data.value);
	esp_event_post_to(view_event_handle, VIEW_EVENT_BASE, VIEW_EVENT_HA_SWITCH_ST, &switch_data, sizeof(switch_data),
					  portMAX_DELAY);
}

void ui_event_wifi_config(lv_event_t* e) {
	// When load the wifi panel, try to retrive the wifi nearby information
	ESP_LOGI(TAG, "send wifi request");
	esp_event_post_to(view_event_handle, VIEW_EVENT_BASE, VIEW_EVENT_WIFI_LIST_REQ, NULL, 0, portMAX_DELAY);
}

void ui_event_wifi_start(lv_event_t* e) {
	ESP_LOGI(TAG, "entry wifi request");
	esp_event_post_to(view_event_handle, VIEW_EVENT_BASE, VIEW_EVENT_WIFI_LIST_START, NULL, 0, portMAX_DELAY);
}

void mqtt_addr_changed(lv_event_t* e) {
	ESP_LOGI(TAG, "addr button comfirmed");
	esp_event_post_to(view_event_handle, VIEW_EVENT_BASE, VIEW_EVENT_MQTT_ADDR_CHANGED, NULL, NULL, portMAX_DELAY);
}
