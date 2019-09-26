#include "gui.h"
#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static lv_obj_t *g_btn_region; //tab view region of the screen
static lv_obj_t *g_sb_region; //status bar region of the screen
static lv_obj_t *g_sb_label;  // sb text label

int auton_sel = 0;

static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt) {

  int btnm_num = atoi(txt);

  switch (btnm_num) {
  case 1:
    lv_label_set_text(g_sb_label, "Red Right Auton");
    auton_sel = 1;
    break;
  case 2:
    lv_label_set_text(g_sb_label, "Red Left Auton");
    auton_sel = 2;
    break;
  case 3:
    lv_label_set_text(g_sb_label, "Blue Right Auton");
    auton_sel = 3;
break;
  case 4:
    lv_label_set_text(g_sb_label, "Blue Left Auton");
    auton_sel = 4;
break;
  case 5:
    lv_label_set_text(g_sb_label, "Skills Auton1");
    auton_sel = 5;
break;
  case 6:
    lv_label_set_text(g_sb_label, "Skills Auton2");
    auton_sel = 6;
break;
  }

  lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

void gui_btnm(void) {
  // Create a button descriptor string array w/ no repeat "\224"
  static const char * btnm_map[] = { "\2241", "\2242", "\2243", "\n",
                                     "\2244", "\2245", "\2246", "" };

  // Create a default button matrix* no repeat
  lv_obj_t *btnm = lv_btnm_create(g_btn_region, NULL);
  lv_obj_set_size(btnm, lv_obj_get_width(g_btn_region),
      lv_obj_get_height(g_btn_region) - 32);

  lv_btnm_set_map(btnm, btnm_map);
  lv_btnm_set_action(btnm, btnm_action);
}


static lv_res_t btn_click_action(lv_obj_t * btn) {
   uint8_t id = lv_obj_get_free_num(btn);
   static char buffer[32];
   auton_sel = id;

   snprintf(buffer, 32, "Selection is %d \n", id);
   lv_label_set_text(g_sb_label, buffer);
   lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

   return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void gui_3btn(void) {

 /*Create a title label*/
 lv_obj_t * label = lv_label_create(g_btn_region, NULL);
 lv_label_set_text(label, "Selection Buttons");
 lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

 /*Create a normal button*/
 lv_obj_t * btn1 = lv_btn_create(g_btn_region, NULL);
 lv_btn_set_style(btn1,LV_BTN_STYLE_REL,&lv_style_btn_rel);
 lv_btn_set_style(btn1,LV_BTN_STYLE_PR,&lv_style_btn_pr);
 lv_obj_align(btn1, NULL, LV_ALIGN_IN_LEFT_MID, 30, 0);
 lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
 lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the button*/
 label = lv_label_create(btn1, NULL);
 lv_label_set_text(label, "Sel 1");

 /*Copy the button and set toggled state. (The release action is copied too)*/
 lv_obj_t * btn2 = lv_btn_create(g_btn_region, btn1);
 lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 0);
 lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/
 lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the toggled button*/
 label = lv_label_create(btn2, NULL);
 lv_label_set_text(label, "Sel 2");

 /*Copy the button and set inactive state.*/
 lv_obj_t * btn3 = lv_btn_create(g_btn_region, btn1);
 lv_obj_align(btn3, NULL, LV_ALIGN_IN_RIGHT_MID, -30, 0);
 lv_obj_set_free_num(btn3, 3);                  /*Set a unique number for the button*/
 lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the inactive button*/
 label = lv_label_create(btn3, NULL);
 lv_label_set_text(label, "Sel 3");
}

static lv_res_t switch_action (lv_obj_t * sw) {
  uint8_t id = lv_obj_get_free_num(sw);
  static char buffer[32];

  snprintf(buffer, 32, "SW%d Toggled to %s\n",id,lv_sw_get_state(sw)?"On":"Off");
  lv_label_set_text(g_sb_label, buffer);
  lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void set_switch_style (lv_obj_t * sw) {
  /*Create styles for the switch*/
  static lv_style_t bg_style;
  static lv_style_t indic_style;
  static lv_style_t knob_on_style;
  static lv_style_t knob_off_style;

  lv_style_copy(&bg_style, &lv_style_pretty);
  bg_style.body.radius = LV_RADIUS_CIRCLE;

  lv_style_copy(&indic_style, &lv_style_pretty_color);
  indic_style.body.radius = LV_RADIUS_CIRCLE;
  indic_style.body.main_color = LV_COLOR_HEX(0x9fc8ef);
  indic_style.body.grad_color = LV_COLOR_HEX(0x9fc8ef);
  indic_style.body.padding.hor = 0;
  indic_style.body.padding.ver = 0;

  lv_style_copy(&knob_off_style, &lv_style_pretty);
  knob_off_style.body.radius = LV_RADIUS_CIRCLE;
  knob_off_style.body.main_color = LV_COLOR_RED;
  knob_off_style.body.grad_color = LV_COLOR_MAROON; //misspelled should be MAROON
  knob_off_style.body.shadow.width = 4;
  knob_off_style.body.shadow.type = LV_SHADOW_BOTTOM;

  lv_style_copy(&knob_on_style, &lv_style_pretty_color);
  knob_on_style.body.radius = LV_RADIUS_CIRCLE;
  knob_on_style.body.main_color = LV_COLOR_LIME;
  knob_on_style.body.grad_color = LV_COLOR_GREEN;
  knob_on_style.body.shadow.width = 4;
  knob_on_style.body.shadow.type = LV_SHADOW_BOTTOM;

  lv_sw_set_style(sw, LV_SW_STYLE_BG, &bg_style);
  lv_sw_set_style(sw, LV_SW_STYLE_INDIC, &indic_style);
  lv_sw_set_style(sw, LV_SW_STYLE_KNOB_ON, &knob_on_style);
  lv_sw_set_style(sw, LV_SW_STYLE_KNOB_OFF, &knob_off_style);
}

void gui_switch(void) {
  /*Create a title label*/
  lv_obj_t * label = lv_label_create(g_btn_region, NULL);
  lv_label_set_text(label, "Flip Switches");
  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

  lv_obj_t * sw1 = lv_sw_create(g_btn_region, NULL);
  lv_obj_set_free_num(sw1, 1);                  /*Set a unique number for the object*/
  set_switch_style(sw1);  // style is in separate function for cleaner code
  lv_obj_align(sw1, NULL, LV_ALIGN_IN_LEFT_MID, 50, 0);

  lv_obj_t * sw2 = lv_sw_create(g_btn_region, sw1); // copy sw1 to sw2
  lv_obj_set_free_num(sw2, 2);                  /*Set a unique number for the object*/
  lv_obj_align(sw2, NULL, LV_ALIGN_IN_RIGHT_MID, -50, 0);

  // both switches use the same call back function
  lv_sw_set_action(sw1, switch_action);
  lv_sw_set_action(sw2, switch_action);
}

lv_obj_t * gauge1;
lv_obj_t * gauge2;
lv_obj_t * gauge3;

void gui_gauges(void) {
  /*Create a style*/
  static lv_style_t style;
  lv_style_copy(&style, &lv_style_pretty_color);
  style.body.main_color = LV_COLOR_HEX3(0x666);     /*Line color at the beginning*/
  style.body.grad_color =  LV_COLOR_HEX3(0x666);    /*Line color at the end*/
  style.body.padding.hor = 10;                      /*Scale line length*/
  style.body.padding.inner = 8 ;                    /*Scale label padding*/
  style.body.border.color = LV_COLOR_HEX3(0x333);   /*Needle middle circle color*/
  style.line.width = 2;
  style.text.color = LV_COLOR_HEX3(0x333);
  style.line.color = LV_COLOR_RED;                  /*Line color after the critical value*/

  /*Describe the color for the needles*/

  /*Create a gauge*/
  lv_coord_t gauge_size =  lv_obj_get_width(lv_scr_act())/3-10;
  gauge1 = lv_gauge_create(lv_scr_act(), NULL);
  lv_gauge_set_style(gauge1, &style);
  lv_obj_set_size(gauge1, gauge_size, gauge_size);
  lv_obj_align(gauge1, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 10);

  /*Create a gauge*/
  gauge2 = lv_gauge_create(lv_scr_act(), NULL);
  lv_gauge_set_style(gauge2, &style);
  lv_obj_set_size(gauge2, gauge_size, gauge_size);
  lv_obj_align(gauge2, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

  /*Create a gauge*/
  gauge3 = lv_gauge_create(lv_scr_act(), NULL);
  lv_gauge_set_style(gauge3, &style);
  lv_obj_set_size(gauge3, gauge_size, gauge_size);
  lv_obj_align(gauge3, NULL, LV_ALIGN_IN_TOP_RIGHT, -5, 10);

}

void gauge_update(void* param) {
  /*Set the values*/
  int i=23;
  while (1) {
    lv_gauge_set_value(gauge1, 0, 1*i%100);
    lv_gauge_set_value(gauge1, 1, i%2?40:50);
    lv_gauge_set_value(gauge2, 0, 2*i%100);
    lv_gauge_set_value(gauge3, 0, 3*i%100);
    pros::Task::delay(1000);
    i++;
  }
}

uint8_t demo_id = 0;

static lv_res_t demo_click_action(lv_obj_t * btn) {
   demo_id = lv_obj_get_free_num(btn);

   g_btn_region = lv_obj_create(lv_scr_act(), NULL);
   lv_obj_set_size(g_btn_region, lv_obj_get_width(lv_scr_act()),
       lv_obj_get_height(lv_scr_act()) * 0.8);
   lv_obj_align(g_btn_region, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
   lv_obj_set_style(g_btn_region, &lv_style_pretty_color);

   //
   g_sb_region = lv_obj_create(lv_scr_act(), NULL);
   lv_obj_set_size(g_sb_region, lv_obj_get_width(lv_scr_act()),
       lv_obj_get_height(lv_scr_act()) * 0.2);
   lv_obj_align(g_sb_region, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
   lv_obj_set_style(g_sb_region, &lv_style_pretty_color);

   g_sb_label = lv_label_create(g_sb_region, NULL);
   lv_obj_set_style(g_sb_label, &lv_style_pretty_color);
   lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0);

   if (demo_id==1) {
    gui_btnm();
  } else if (demo_id==2) {
    gui_3btn();
  } else if (demo_id==3) {
    gui_switch();
  } else {
    gui_gauges();
    pros::Task telm_task (gauge_update, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "guage");
  }

   return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void gui(void) {

// select demo
  /*Create a title label*/
  lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(label, "Selection A Demo - V0.1.6");
  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

  lv_coord_t btn_width =  (lv_obj_get_width(lv_scr_act())/4)-10;
  lv_coord_t btn_height =  btn_width/2;

  /*Create a normal button*/
  lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btn1, btn_width, btn_height);
  lv_obj_align(btn1, NULL, LV_ALIGN_IN_LEFT_MID, 8, 0);
  lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, demo_click_action);

  /*Add a label to the button*/
  label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "MATRIX");

  /*Copy the button and set toggled state. (The release action is copied too)*/
  lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btn2, btn_width, btn_height);
  lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, -btn_width/2-4, 0);
  lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/
  lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, demo_click_action);

  /*Add a label to the toggled button*/
  label = lv_label_create(btn2, NULL);
  lv_label_set_text(label, "BUTTONS");

  /*Copy the button and set toggled state. (The release action is copied too)*/
  lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btn3, btn_width, btn_height);
  lv_obj_align(btn3, NULL, LV_ALIGN_CENTER, btn_width/2+4, 0);
  lv_obj_set_free_num(btn3, 3);               /*Set a unique number for the button*/
  lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, demo_click_action);

  /*Add a label to the toggled button*/
  label = lv_label_create(btn3, NULL);
  lv_label_set_text(label, "SWITCH");

  /*Copy the button and set toggled state. (The release action is copied too)*/
  lv_obj_t * btn4 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btn4, btn_width, btn_height);
  lv_obj_align(btn4, NULL, LV_ALIGN_IN_RIGHT_MID, -8, 0);
  lv_obj_set_free_num(btn4, 4);               /*Set a unique number for the button*/
  lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, demo_click_action);

  /*Add a label to the toggled button*/
  label = lv_label_create(btn4, NULL);
  lv_label_set_text(label, "GUAGE");
}
