/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc. All Rights Reserved.
 * (now owned by Analog Devices, Inc.),
 * Copyright (C) 2023 Analog Devices, Inc. All Rights Reserved. This software
 * is proprietary to Analog Devices, Inc. and its licensors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/
#include <string.h>

#include "bitmap.h"
#include "keypad.h"
#include "state.h"
#include "tft_ssd2119.h"

/*********************************      DEFINES      *************************/
#define BUTTON_SIZE_X 42 + 4 // 6 for free space
#define BUTTON_SIZE_Y 41 + 6 // 6 for free space

#define MAX_CHAR_ON_SCREEN 8

/*********************************      VARIABLES    *************************/
static unsigned char input_buf[MAX_CHAR_ON_SCREEN + 1] = { 0 };

static text_t text_msg[] = { { (char *)"Pressed", 7 }, { (char *)input_buf, 0 } };

static text_t *input_text = &text_msg[1];

/********************************* Static Functions **************************/
static int init(void)
{
    int x, y;
    int x0 = 120;
    int y0 = 40;

    MXC_TS_RemoveAllButton();
    MXC_TFT_SetPalette(logo_white_bg_white_bmp);
    MXC_TFT_SetBackGroundColor(0);

    MXC_TFT_ShowImage(11, 7, logo_white_bg_white_bmp);

    x = x0;
    y = y0;
    MXC_TFT_ShowImage(x, y, key_1_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_1);

    x += BUTTON_SIZE_X;
    MXC_TFT_ShowImage(x, y, key_2_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_2);

    x += BUTTON_SIZE_X;
    MXC_TFT_ShowImage(x, y, key_3_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_3);

    x += BUTTON_SIZE_X;
    MXC_TFT_ShowImage(x, y, key_clear_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_F);

    //
    x = x0;
    y += BUTTON_SIZE_Y;
    MXC_TFT_ShowImage(x, y, key_4_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_4);

    x += BUTTON_SIZE_X;
    MXC_TFT_ShowImage(x, y, key_5_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_5);

    x += BUTTON_SIZE_X;
    MXC_TFT_ShowImage(x, y, key_6_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_6);

    x += BUTTON_SIZE_X;
    MXC_TFT_ShowImage(x, y, key_cancel_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_E);

    //
    x = x0;
    y += BUTTON_SIZE_Y;
    MXC_TFT_ShowImage(x, y, key_7_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_7);

    x += BUTTON_SIZE_X;
    MXC_TFT_ShowImage(x, y, key_8_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_8);

    x += BUTTON_SIZE_X;
    MXC_TFT_ShowImage(x, y, key_9_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_9);

    x += BUTTON_SIZE_X;
    MXC_TFT_ShowImage(x, y, key_enter_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_D);

    //
    x = x0;
    x += BUTTON_SIZE_X;
    y += BUTTON_SIZE_Y;
    MXC_TFT_ShowImage(x, y, key_0_bg_white_bmp);
    MXC_TS_AddButton(x, y, x + 42, y + 41, KEY_0);

    MXC_TFT_PrintFont(11, 80, urw_gothic_13_grey_bg_white, &text_msg[0], NULL);
    input_text->len = 0;

    return 0;
}

static void print_inputs(int key)
{
    static area_t area;

    if (key == 0) { // means clear screen
        MXC_TFT_ClearArea(&area, 0);
        input_text->len = 0;
    } else if (key == -1) { // means clear last key
        if (input_text->len > 0) {
            input_text->len--;
            MXC_TFT_ClearArea(&area, 0);
            MXC_TFT_PrintFont(11, 120, urw_gothic_13_grey_bg_white, input_text, &area);
        }
    } else if (input_text->len < MAX_CHAR_ON_SCREEN) {
        input_text->data[input_text->len++] = key;
        MXC_TFT_PrintFont(11, 120, urw_gothic_13_grey_bg_white, input_text, &area);
    }
}

static int key_process(int key)
{
    switch (key) {
    case KEY_0:
    case KEY_1:
    case KEY_2:
    case KEY_3:
    case KEY_4:
    case KEY_5:
    case KEY_6:
    case KEY_7:
    case KEY_8:
    case KEY_9:
    case KEY_A:
    case KEY_B:
        print_inputs(key);
        break;

    case KEY_C: // exit
        state_set_current(get_home_state());
        break;

    case KEY_D: // enter
        state_set_current(get_home_state());
        break;

    case KEY_E: // cancel
        print_inputs(-1);
        break;

    case KEY_F: // clear
        print_inputs(0);
        break;

    default:
        break;
    }

    return 0;
}

static State g_state = { "keypad", init, key_process, NULL, 0 };

/********************************* Public Functions **************************/
State *get_keypad_state(void)
{
    return &g_state;
}
