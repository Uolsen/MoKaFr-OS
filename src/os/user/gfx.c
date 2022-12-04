#include "user/gfx.h"
#include "stdlib/stdstring.h"
#include "filesystem/fat.h"
#include "debug/debug.h"

int run = 100;

/**
 * Entry point of the GFX process.
 */
void gfx_main() {
        DEBUG_F("Running GFX Process");
    while (1) {
//    if (run <= 0) return;

        // TODO: while loop -> check for data in pipe
        uint8_t buffer[1024];
        bzero(buffer, 1024);

        uint32_t index = 0;

        DirectoryEntry *gfx_entry = get_gfx_pipe();
        Node gfx_node = fs_get_node(gfx_entry->node_id);
        Pipe *gfx_pipe = fs_node_get_pipe(gfx_node);

        while (gfx_pipe->read_pointer != gfx_pipe->write_pointer) {
//        DEBUG_F("reading");
            //    run--;
            uint8_t character = fs_pread(gfx_entry);
            //    DEBUG_P("char: %c", character);
            if (character == ';') {
//            char * new_buffer;
//            strncmp(new_buffer, buffer, strlen(buffer));
//            process(buffer);
                index = 0;

                DEBUG_F("PROCESSING");
                DEBUG_P("Buffer: %s", buffer);
                // split buffer by ','
                // render stuff on monitor
                char *split = strsplit(buffer, '|', 0);

                char *shape = get_split(split, 0);
                DEBUG_P("SHAPE: %s", shape);

                if (strncmp(shape, "circle", strlen("circle")) == 0) { // replace with strncmp
//        if (verify_circle(split))
//        {
                    uint32_t x = atoi(get_split(split, 1));
                    uint32_t y = atoi(get_split(split, 2));
                    uint32_t radius = atoi(get_split(split, 3));
                    uint8_t *color = get_split(split, 4);
                    uint32_t fill = atoi(get_split(split, 5));

//            DEBUG_P("x: %u", x);
//            DEBUG_P("y: %u", y);
//            DEBUG_P("radius: %u", radius);
//            DEBUG_P("color: %s", color);
//            DEBUG_P("fill: %u", fill);

                    drawCircle(x, y, radius, color, fill);
                    //            drawCircle(300, 300, 50, 0x13, 1);
//        }
                } else if (strncmp(shape, "rect", strlen("rect")) == 0) {
                    uint32_t x = atoi(get_split(split, 1));
                    uint32_t y = atoi(get_split(split, 2));
                    uint32_t width = atoi(get_split(split, 3));
                    uint32_t height = atoi(get_split(split, 4));
                    uint8_t *color = get_split(split, 5);
                    uint32_t fill = atoi(get_split(split, 6));

                    drawRect(x, y, width, height, color, fill);
                    //       drawRect(500, 500, 30, 30, 0x13, 0);
                } else if (strncmp(shape, "string", strlen("string")) == 0) {
                    uint32_t x = atoi(get_split(split, 1));
                    uint32_t y = atoi(get_split(split, 2));
                    uint8_t *string = get_split(split, 3);
                    uint8_t *color = get_split(split, 4);
                    //drawString(100, 100, "test", 0x13);
                    drawString(x, y, string, color);
                    //      DEBUG_F("AFTER STRING");
                }

                DEBUG_F("AFTER PROCESS");
                bzero(buffer, 1024);

                continue;
            }
            // if (character == ' ') continue;
            buffer[index++] = character;
            DEBUG_P("Char: %c", buffer[index - 1]);

//        if (run == 0) {
//            break;
//        }

            // read pipe
            // process data from pipe
            // ex: circle,320,0xFF|rect,20,40,0xFF
            // circle, 320 = radius, 0xFF = color
            // rect, 20 = width, 40 = height, 0xff = color
        }
    }
}

/**
 * Verifies the circle draw input.
 * @param split
 * @return
 */
uint32_t verify_circle(uint8_t * split) {
    return 1;
    //  TODO: Check if there are right data
}// TODO: functions to render stuff (write to pipe?)

void process(char * buffer) {

}



