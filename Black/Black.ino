#include <Encoder.h>
#include <ros.h>
#include <std_msgs/Float.h>

ros::NodeHandle nh;

Encoder myEnc_L(2, 12); // Encoder of Motor left
Encoder myEnc_R(3, 13); // Encoder of Motor Right
long oldPosition_L  = -999;
long oldPosition_R  = -999;
void setup() {
  Serial.begin(115200);
}

void loop() {
  long Enc_L = myEnc_L.read();
  long Enc_R = myEnc_R.read();

}
