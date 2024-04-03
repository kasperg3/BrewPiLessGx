
#include "../ui.h"

static void draw_event_cb(lv_event_t * e)
{
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
    if(dsc->part == LV_PART_TICKS && dsc->id == LV_CHART_AXIS_PRIMARY_X) {
        const char * month[] = {"Jan", "Febr", "March", "Apr", "May", "Jun", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
        lv_snprintf(dsc->text, sizeof(dsc->text), "%s", month[dsc->value]);
    }
}

void chart_init(){

    /*Add ticks and label to every axis*/
    lv_chart_set_axis_tick(ui_screenChart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 12, 3, true, 40);
    lv_chart_set_axis_tick(ui_screenChart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 2, true, 50);
    lv_chart_set_axis_tick(ui_screenChart, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 3, 4, true, 50);

    /*Zoom in a little in X*/
    lv_chart_set_zoom_x(ui_screenChart, LV_IMG_ZOOM_NONE);

    /*Add two data series*/
    lv_chart_series_t * ser1 = lv_chart_add_series(ui_screenChart, lv_palette_lighten(LV_PALETTE_GREEN, 2), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * ser2 = lv_chart_add_series(ui_screenChart, lv_palette_darken(LV_PALETTE_GREEN, 2), LV_CHART_AXIS_SECONDARY_Y);

    /*Set the next points on 'ser1'*/
    lv_chart_set_next_value(ui_screenChart, ser1, 31);
    lv_chart_set_next_value(ui_screenChart, ser1, 66);
    lv_chart_set_next_value(ui_screenChart, ser1, 10);
    lv_chart_set_next_value(ui_screenChart, ser1, 89);
    lv_chart_set_next_value(ui_screenChart, ser1, 63);
    lv_chart_set_next_value(ui_screenChart, ser1, 56);
    lv_chart_set_next_value(ui_screenChart, ser1, 32);
    lv_chart_set_next_value(ui_screenChart, ser1, 35);
    lv_chart_set_next_value(ui_screenChart, ser1, 57);
    lv_chart_set_next_value(ui_screenChart, ser1, 85);
    lv_chart_set_next_value(ui_screenChart, ser1, 22);
    lv_chart_set_next_value(ui_screenChart, ser1, 58);

    lv_coord_t * ser2_array =  lv_chart_get_y_array(ui_screenChart, ser2);
    /*Directly set points on 'ser2'*/
    ser2_array[0] = 92;
    ser2_array[1] = 71;
    ser2_array[2] = 61;
    ser2_array[3] = 15;
    ser2_array[4] = 21;
    ser2_array[5] = 35;
    ser2_array[6] = 35;
    ser2_array[7] = 58;
    ser2_array[8] = 31;
    ser2_array[9] = 53;
    ser2_array[10] = 33;
    ser2_array[11] = 73;
}

/**
 * Add ticks and labels to the axis and demonstrate scrolling
 */
void ui_screenChart_screen_init(void)
{
    /*Create a chart*/
    ui_screenChart = lv_chart_create(lv_scr_act());
    lv_obj_set_height( ui_screenChart, lv_pct(80));
    lv_obj_set_width( ui_screenChart, lv_pct(80));
    lv_obj_set_x( ui_screenChart, 0 );
    lv_obj_set_y( ui_screenChart, 0 );
    lv_obj_center(ui_screenChart);

    lv_chart_set_type(ui_screenChart, LV_CHART_TYPE_LINE);
    lv_chart_set_range(ui_screenChart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_range(ui_screenChart, LV_CHART_AXIS_SECONDARY_Y, 0, 400);
    lv_chart_set_point_count(ui_screenChart, 12);
    lv_obj_add_event_cb(ui_screenChart, draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);


    ui_btnChartBack = lv_imgbtn_create(ui_screenTempControl);
    lv_imgbtn_set_src(ui_btnChartBack, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_backbutton_png, NULL);
    lv_obj_set_width( ui_btnChartBack, 20);
    lv_obj_set_height( ui_btnChartBack, 36);
 
    /*Create a button to go to the main screen*/
    lv_obj_add_event_cb(ui_btnChartBack, ui_event_back, LV_EVENT_ALL, NULL);
    
    // // Fill the chart with values   
    chart_init();
    lv_chart_refresh(ui_screenChart); /*Required after direct set*/

}