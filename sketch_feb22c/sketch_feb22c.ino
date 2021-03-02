#include <Encoder.h>

Encoder myEncL(2, 12);
Encoder myEncR(3, 13);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
}

long oldPositionl  = -999;
long oldPositionr  = -999;

void loop() {
  long newPositionl = myEncL.read();
  if (newPositionl != oldPositionl) {
    oldPositionl = newPositionl;
    Serial.print(newPositionl);
    Serial.print(" ");
  }
  
  long newPositionr = myEncR.read();
  if (newPositionr != oldPositionr) {
    oldPositionr = newPositionr;
    Serial.println(newPositionr);
  }
}
