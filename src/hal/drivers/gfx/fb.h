#ifndef MOKAFR_FB_H
#define MOKAFR_FB_H

#include "intdef.h"

void fb_init();
void drawPixel(int32_t x, int32_t y, unsigned char attr);
void drawChar(unsigned char ch, int32_t x, int32_t y, unsigned char attr);
void drawString(int32_t x, int32_t y, char *s, unsigned char attr);
void drawRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, unsigned char attr, int32_t fill);
void drawCircle(int32_t x0, int32_t y0, int32_t radius, unsigned char attr, int32_t fill);
void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, unsigned char attr);

#endif //MOKAFR_FB_H
