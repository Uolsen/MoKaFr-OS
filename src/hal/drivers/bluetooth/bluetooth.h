#ifndef MOKAFR_BLUETOOTH_H
#define MOKAFR_BLUETOOTH_H

void bt_init();

void bt_flushrx();

unsigned int bt_isReadByteReady();

unsigned char bt_readByte();
void bt_writeByte(char byte);

unsigned char low(unsigned int value);
unsigned char high(unsigned int value);

void bt_reset();
void bt_loadfirmware();
void bt_setbaud();
void bt_setbdaddr();
void bt_getbdaddr(unsigned char *bdaddr);
unsigned char bt_waitReadByte();
void setLEeventmask(unsigned char mask);
void startActiveScanning();
void stopScanning();
void startActiveAdvertising();
void connect(unsigned char *addr);
void sendACLsubscribe(unsigned int handle);

#endif //MOKAFR_BLUETOOTH_H
