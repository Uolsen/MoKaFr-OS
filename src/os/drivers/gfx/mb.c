#include "drivers/gfx/mb.h"
#include "libc.h"
#include "intdef.h"

// The buffer must be 16-byte aligned as only the upper 28 bits of the address can be passed via the mailbox
volatile uint32_t __attribute__((aligned(16))) mbox[36];

enum {
    VIDEOCORE_MBOX = (PERIPHERAL_BASE + 0x0000B880),
    MBOX_READ      = (VIDEOCORE_MBOX + 0x0),
    MBOX_POLL      = (VIDEOCORE_MBOX + 0x10),
    MBOX_SENDER    = (VIDEOCORE_MBOX + 0x14),
    MBOX_STATUS    = (VIDEOCORE_MBOX + 0x18),
    MBOX_CONFIG    = (VIDEOCORE_MBOX + 0x1C),
    MBOX_WRITE     = (VIDEOCORE_MBOX + 0x20),
    MBOX_RESPONSE  = 0x80000000,
    MBOX_FULL      = 0x80000000,
    MBOX_EMPTY     = 0x40000000
};

/**
 * Handles mailbox communication.
 *
 * @param character
 * @return
 */
uint32_t mbox_call(unsigned char character)
{
    // 28-bit address (MSB) and 4-bit value (LSB)
    uint32_t r = ((uint32_t)((int64_t) &mbox) &~ 0xF) | (character & 0xF);

    // Wait until we can write
    while (mmio_read(MBOX_STATUS) & MBOX_FULL);

    // Write the address of our buffer to the mailbox with the channel appended
    mmio_write(MBOX_WRITE, r);

    while (1) {
        // Is there a reply?
        while (mmio_read(MBOX_STATUS) & MBOX_EMPTY);

        // Is it a reply to our message?
        if (r == mmio_read(MBOX_READ)) return mbox[1]==MBOX_RESPONSE; // Is it successful?

    }
    return 0;
}