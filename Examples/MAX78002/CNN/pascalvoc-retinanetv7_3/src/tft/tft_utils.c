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

#include <stddef.h>
#include <string.h>
#include "tft_utils.h"
#include "camera.h"
#include "labels.h"

int font = (int)&Liberation_Sans16x16[0];

void TFT_Print(char *str, int x, int y)
{
    int len = strlen(str);
    text_t text = { .data = str, .len = len };
    MXC_TFT_PrintFont(x, y, font, &text, NULL);
}

void draw_obj_rect(float *xy, int class_idx)
{
    // Top left
    unsigned int x1 = (unsigned int)(xy[0] * IMAGE_WIDTH);
    if (x1 < 0)
        x1 = 0;
    unsigned int y1 = (unsigned int)(xy[1] * IMAGE_HEIGHT);
    if (y1 < 0)
        y1 = 0;
    // Bottom right
    unsigned int x2 = (unsigned int)(xy[2] * IMAGE_WIDTH);
    if (x2 > DISPLAY_WIDTH)
        x2 = DISPLAY_WIDTH - LINE_WIDTH;
    unsigned int y2 = (unsigned int)(xy[3] * IMAGE_HEIGHT);
    if (y2 > DISPLAY_HEIGHT)
        y2 = DISPLAY_HEIGHT - LINE_WIDTH;

    int color = RED;
    switch (class_idx) {
    case 0:
        color = BLACK;
        break;
    case 1:
        color = NAVY;
        break;
    case 2:
        color = DARK_GREEN;
        break;
    case 3:
        color = DARK_CYAN;
        break;
    case 4:
        color = MAROON;
        break;
    case 5:
        color = PURPLE;
        break;
    case 6:
        color = OLIVE;
        break;
    case 7:
        color = LIGHT_GREY;
        break;
    case 8:
        color = DARK_GREY;
        break;
    case 9:
        color = BLUE;
        break;
    case 10:
        color = GREEN;
        break;
    case 11:
        color = CYAN;
        break;
    case 12:
        color = RED;
        break;
    case 13:
        color = MAGENTA;
        break;
    case 14:
        color = YELLOW;
        break;
    case 15:
        color = WHITE;
        break;
    case 16:
        color = ORANGE;
        break;
    case 17:
        color = GREEN_YELLOW;
        break;
    default:
        color = RED;
        break;
    }

    TFT_SPI_Init();

    for (int x = x1; x < x2; x++) {
        MXC_TFT_WritePixel(x, y1, LINE_WIDTH, LINE_WIDTH, color);
        MXC_TFT_WritePixel(x, y2, LINE_WIDTH, LINE_WIDTH, color);
    }

    for (int y = y1; y < y2; ++y) {
        MXC_TFT_WritePixel(x1, y, LINE_WIDTH, LINE_WIDTH, color);
        MXC_TFT_WritePixel(x2, y, LINE_WIDTH, LINE_WIDTH, color);
    }

    TFT_Print(voc_labels[class_idx], x1, y1 + 4);
}