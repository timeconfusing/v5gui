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

   return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void gui_3btn(void) {

 /*Create a title label*/
 lv_obj_t * label = lv_label_create(g_btn_region, NULL);
 lv_label_set_text(label, "Selection Buttons");
 lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

 /*Create a normal button*/
 lv_obj_t * btn1 = lv_btn_create(g_btn_region, NULL);
 lv_obj_align(btn1, NULL, LV_ALIGN_IN_LEFT_MID, 50, 0);
 lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
 lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the button*/
 label = lv_label_create(btn1, NULL);
 lv_label_set_text(label, "Sel 1");

 /*Copy the button and set toggled state. (The release action is copied too)*/
 lv_obj_t * btn2 = lv_btn_create(g_btn_region, NULL);
 lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 0);
 lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/
 lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the toggled button*/
 label = lv_label_create(btn2, NULL);
 lv_label_set_text(label, "Sel 2");

 /*Copy the button and set inactive state.*/
 lv_obj_t * btn3 = lv_btn_create(g_btn_region, NULL);
 lv_obj_align(btn3, NULL, LV_ALIGN_IN_RIGHT_MID, -50, 0);
 lv_obj_set_free_num(btn3, 3);                  /*Set a unique number for the button*/
 lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the inactive button*/
 label = lv_label_create(btn3, NULL);
 lv_label_set_text(label, "Sel 3");
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
   } else {
    gui_3btn();
   }

   return LV_RES_OK; /*Return OK if the button is not deleted*/
}


void gui(void) {

// select demo
  /*Create a title label*/
  lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(label, "Selection A Demo");
  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

  /*Create a normal button*/
  lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, -150, 0);
  lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, demo_click_action);

  /*Add a label to the button*/
  label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "MATRIX");

  /*Copy the button and set toggled state. (The release action is copied too)*/
  lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 150, 0);
  lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/
  lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, demo_click_action);

  /*Add a label to the toggled button*/
  label = lv_label_create(btn2, NULL);
  lv_label_set_text(label, "BUTTONS");

}
