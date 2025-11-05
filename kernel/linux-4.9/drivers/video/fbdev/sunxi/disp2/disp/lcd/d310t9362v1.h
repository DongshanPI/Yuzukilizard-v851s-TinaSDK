/* drivers/video/sunxi/disp2/disp/lcd/d310t9362v1.h
 *
 * Copyright (c) 2022 YuzukiTsuru <gloomyghost@gloomyghost.com>
 *
 * D310T9362V1 panel driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
#ifndef _D310T9362V1_H
#define _D310T9362V1_H

#include "panels.h"

extern struct __lcd_panel d310t9362v1_panel;

extern s32 bsp_disp_get_panel_info(u32 screen_id, struct disp_panel_para *info);

#endif /*End of file*/