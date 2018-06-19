#include <PS4BT.h>
#include <SPI.h>

USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd);

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while(!Serial); // wait for serial port to connect
#endif
  if(Usb.Init() == -1) {
    Serial.print(F("USB host shield failed to start\n"));
    while(1); // halt program
  }
  Serial.print(F("USB host shield started\n"));
}

void loop() {
  Usb.Task();

  if(PS4.connected()) {
    Serial.print(F("\nLeft X: "));
    Serial.print(PS4.getAnalogHat(LeftHatX));
  }
}
