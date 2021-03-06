#include <ArduinoHardware.h>
#include <ros.h> 
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>  
#include <Encoder.h>

Encoder myEnc_L(2, 12); // Encoder of Motor left
Encoder myEnc_R(3, 13); // Encoder of Motor Right
long oldPosition_L  = -999;
long oldPosition_R  = -999;
long newPosition_L;
long newPosition_R;

ros::NodeHandle nh;

std_msgs::Float32 encL_msg;
std_msgs::Float32 encR_msg;
std_msgs::Float32 V_L_msg;
std_msgs::Float32 V_R_msg;

ros::Publisher EncL("Enc_L", &encL_msg);
ros::Publisher EncR("Enc_R", &encR_msg);
ros::Publisher Velocity_L("Velocity_L", &V_L_msg);
ros::Publisher Velocity_R("Velocity_R", &V_R_msg);

void CallBack_L(const std_msgs::Int32& pwm_L) {
  if (pwm_L.data > 0) {digitalWrite(11, HIGH);}
  else {digitalWrite(11, LOW);}
  analogWrite(10, pwm_L.data);
}
void CallBack_R(const std_msgs::Int32& pwm_R) {
  if (pwm_R.data > 0) {digitalWrite(9, HIGH);}
  else {digitalWrite(9, LOW);}
  analogWrite(8, pwm_R.data);
}

ros::Subscriber <std_msgs::Int32> Motor_L("/pwm_L", CallBack_L);
ros::Subscriber <std_msgs::Int32> Motor_R("/pwm_R", CallBack_R);

void setup() {
  pinMode(11, OUTPUT); pinMode(10, OUTPUT); // Motor Left
  pinMode(9, OUTPUT); pinMode(8, OUTPUT); // Motor Right
  nh.initNode();
  nh.subscribe(Motor_L);
  nh.subscribe(Motor_R);
  nh.advertise(EncL);
  nh.advertise(EncR);
} 

void loop() {
  newPosition_L = myEnc_L.read();
  newPosition_R = myEnc_R.read()*-1;
  
  if (newPosition_L != oldPosition_L) {
    oldPosition_L = newPosition_L;
    encL_msg.data = newPosition_L;
    }
  if (newPosition_R != oldPosition_R) {
    oldPosition_R = newPosition_R;
    encR_msg.data = newPosition_R;
    }
  if((abs(newPosition_L)>1000000)||(abs(newPosition_R)>1000000)) {
    myEnc_L.write(0);
    myEnc_R.write(0);
    }
  Velocity_L.publish( &V_L_msg );
  Velocity_R.publish( &V_R_msg );
  EncL.publish( &encL_msg );
  EncR.publish( &encR_msg );
  nh.spinOnce();
  delay(10);
}
