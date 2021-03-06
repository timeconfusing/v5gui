# v5gui
Example LVGL GUI code for Vex V5 Brain

There are two examples included. The first uses individual buttons that can be placed anywhere on the screen. The second uses a button matrix.

The GUI consists of two regions: the Button Region and the Status Region. Inside the Status region is a Label object. This split is done to make sure the status information can be display if the buttons exceed the size of the button region. Which is good when debugging placment issues.

In the first example, individual buttons are placed on the screen using using lv_obj_align. All buttons use one callback function defined by lv_btn_set_action. The lv_obj_set_free_num assigns a numeric value to the button pressed for the callback function to use.

The Buttons look like this when run in the LVGL PC Simulator.
![](https://raw.githubusercontent.com/timeconfusing/Images/master/LVGL-buttons.PNG)

In the second example, 

The button matrix allow for fast definition of multiple rows and columns of buttons. The defintion of the matrix is as follows:
 
```// Create a button descriptor string array w/ no repeat "\224"
  static const char * btnm_map[] = { "\2241", "\2242", "\2243", "\n",
                                     "\2244", "\2245", "\2246", "" };
```
 
The escape section prevents a press of the button being interpreted as a multipress of the button. The matrix is created by lv_btnm_set_map. The last character in the string for the button_map is what the callback function receives when pressed. The callback function is defined by lv_btnm_set_action.

The Button Matrix looks like this when run in the LVGL PC Simulator.
![](https://raw.githubusercontent.com/timeconfusing/Images/master/LVGL-btnm.PNG)
