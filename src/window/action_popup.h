#ifndef WINDOW_ACTION_DIALOG_H
#define WINDOW_ACTION_DIALOG_H

#include <stdint.h>

void window_action_popup_show(int title, int subtitle, option_menu_item *options,
    void (*close_func)(int selection), int show_cancel_button);



#endif // WINDOW_ACTION_DIALOG_H