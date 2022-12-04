#include "drivers/gfx/fb.h"
#include "drivers/gfx/mb.h"
#include "drivers/gfx/terminal.h"

uint32_t width, height, pitch, isrgb;
unsigned char *fb;

/**
 * Setup frame buffer for RPI4.
 */
void fb_init() {
    mbox[0] = 35 * 4; // Length of message in bytes
    mbox[1] = MBOX_REQUEST;

    mbox[2] = MBOX_TAG_SETPHYWH; // Tag identifier
    mbox[3] = 8; // Value size in bytes
    mbox[4] = 0;
    mbox[5] = 1920; // Value(width)
    mbox[6] = 1080; // Value(height)

    mbox[7] = MBOX_TAG_SETVIRTWH;
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = 1920;
    mbox[11] = 1080;

    mbox[12] = MBOX_TAG_SETVIRTOFF;
    mbox[13] = 8;
    mbox[14] = 8;
    mbox[15] = 0; // Value(x)
    mbox[16] = 0; // Value(y)

    mbox[17] = MBOX_TAG_SETDEPTH;
    mbox[18] = 4;
    mbox[19] = 4;
    mbox[20] = 32; // Bits per pixel

    mbox[21] = MBOX_TAG_SETPXLORDR;
    mbox[22] = 4;
    mbox[23] = 4;
    mbox[24] = 1; // RGB

    mbox[25] = MBOX_TAG_GETFB;
    mbox[26] = 8;
    mbox[27] = 8;
    mbox[28] = 4096; // FrameBufferInfo.pointer
    mbox[29] = 0;    // FrameBufferInfo.size

    mbox[30] = MBOX_TAG_GETPITCH;
    mbox[31] = 4;
    mbox[32] = 4;
    mbox[33] = 0; // Bytes per line

    mbox[34] = MBOX_TAG_LAST;

    // Check call is successful and we have a pointer with depth 32
    if (mbox_call(MBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0) {
        mbox[28] &= 0x3FFFFFFF; // Convert GPU address to ARM address
        width = mbox[10];       // Actual physical width
        height = mbox[11];      // Actual physical height
        pitch = mbox[33];       // Number of bytes per line
        isrgb = mbox[24];       // Pixel order
        fb = (unsigned char *) ((int64_t) mbox[28]);
    }
}

/**
 * Draws a pixel onto the screen
 *
 * @param x X position of the first point from top-left corner
 * @param y Y position of the first point from top-left corner
 * @param color Color of the pixel
 */
void drawPixel(int32_t x, int32_t y, unsigned char color) {
    int32_t offs = (y * pitch) + (x * 4);
    *((uint32_t * )(fb + offs)) = vgapal[color & 0x0f];
}

/**
 * Draws a rectangle onto the screen
 *
 * @param x1 X position of the first point from top-left corner
 * @param y1 Y position of the first point from top-left corner
 * @param x2 X position of the second point from top-left corner
 * @param y2 Y position of the second point from top-left corner
 * @param color Color of the rectangle
 * @param fill  "Bool" whether to fill the rectangle or not.
 */
void drawRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, unsigned char color, int32_t fill) {
    int32_t y = y1;

    while (y <= y2) {
        int32_t x = x1;
        while (x <= x2) {
            if ((x == x1 || x == x2) || (y == y1 || y == y2)) drawPixel(x, y, color);
            else if (fill) drawPixel(x, y, (color & 0xf0) >> 4);
            x++;
        }
        y++;
    }
}

/**
 * Draws a line onto the screen
 *
 * @param x1 X position of the first point from top-left corner
 * @param y1 Y position of the first point from top-left corner
 * @param x2 X position of the second point from top-left corner
 * @param y2 Y position of the second point from top-left corner
 * @param color Color of the line
 */
void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, unsigned char color) {
    int32_t dx, dy, p, x, y;

    dx = x2 - x1;
    dy = y2 - y1;
    x = x1;
    y = y1;
    p = 2 * dy - dx;

    while (x < x2) {
        if (p >= 0) {
            drawPixel(x, y, color);
            y++;
            p = p + 2 * dy - 2 * dx;
        } else {
            drawPixel(x, y, color);
            p = p + 2 * dy;
        }
        x++;
    }
}

/**
 * Draws a circle onto the screen.
 *
 * @param x0 X position of the center from top-left corner
 * @param y0 Y position of the center from top-left corner
 * @param radius Radius of the circle
 * @param color Color of the circle
 * @param fill "Bool" whether to fill the circle or not.
 */
void drawCircle(int32_t x0, int32_t y0, int32_t radius, unsigned char color, int32_t fill) {
    int32_t x = radius;
    int32_t y = 0;
    int32_t err = 0;

    while (x >= y) {
        if (fill) {
            drawLine(x0 - y, y0 + x, x0 + y, y0 + x, (color & 0xf0) >> 4);
            drawLine(x0 - x, y0 + y, x0 + x, y0 + y, (color & 0xf0) >> 4);
            drawLine(x0 - x, y0 - y, x0 + x, y0 - y, (color & 0xf0) >> 4);
            drawLine(x0 - y, y0 - x, x0 + y, y0 - x, (color & 0xf0) >> 4);
        }
        drawPixel(x0 - y, y0 + x, color);
        drawPixel(x0 + y, y0 + x, color);
        drawPixel(x0 - x, y0 + y, color);
        drawPixel(x0 + x, y0 + y, color);
        drawPixel(x0 - x, y0 - y, color);
        drawPixel(x0 + x, y0 - y, color);
        drawPixel(x0 - y, y0 - x, color);
        drawPixel(x0 + y, y0 - x, color);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }

        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

/**
 * Draws a character onto the screen.
 *
 * @param character Character to draw
 * @param x X position from top-left corner
 * @param y Y position from top-left corner
 * @param color Color of the character
 */
void drawChar(unsigned char character, int32_t x, int32_t y, unsigned char color) {
    unsigned char *glyph = (unsigned char *) &font + (character < FONT_NUMGLYPHS ? character : 0) * FONT_BPG;

    for (int32_t i = 0; i < FONT_HEIGHT; i++) {
        for (int32_t j = 0; j < FONT_WIDTH; j++) {
            unsigned char mask = 1 << j;
            unsigned char col = (*glyph & mask) ? color & 0x0f : (color & 0xf0) >> 4;

            drawPixel(x + j, y + i, col);
        }
        glyph += FONT_BPL;
    }
}

/**
 * Draw a string onto the screen
 *
 * @param x X position from top-left corner
 * @param y Y position from top-left corner
 * @param string String to write on the screen
 * @param color Color of the string
 */
void drawString(int32_t x, int32_t y, char *string, unsigned char color) {
    while (*string) {
        if (*string == '\r') {
            x = 0;
        } else if (*string == '\n') {
            x = 0;
            y += FONT_HEIGHT;
        } else {
            drawChar(*string, x, y, color);
            x += FONT_WIDTH;
        }
        string++;
    }
}

/**
 * Clears the screen.
 */
void fb_clear() {
    uint32_t x = 0;
    uint32_t y = 0;

    for (x = 0; x < 1920; x++) {
        for (y = 0; y < 1080; y++) {
            drawPixel(x, y, 0x00);
        }
    }
}