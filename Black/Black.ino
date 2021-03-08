/* 
Publish real velocity of left & right wheel
Publish tick encoder of left & right wheel
Subscribe ideal velocity of left & right wheel
*/

// Import library
#include <ArduinoHardware.h>
#include <ros.h> 
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>  
#include <Encoder.h>

// Config variable
Encoder myEnc_L(2, 12); // Encoder of Motor left
Encoder myEnc_R(3, 13); // Encoder of Motor Right
const int PPR = 1881; // pulse per rotation of motor
const float r = 0.005; // radius of wheel
long oldPosition_L  = -999;
long oldPosition_R  = -999;
long newPosition_L; // Tick of left wheel
long newPosition_R; // Tick of right wheel
long Pulse_L = 0;
long Pulse_R = 0;
float rpm_L = 0; // round per minute of left wheel
float rpm_R = 0; // round per minute of right wheel

ros::NodeHandle nh;

// Config message variable
std_msgs::Float32 encL_msg; // message encoder of left wheel
std_msgs::Float32 encR_msg; // message encoder of right wheel
std_msgs::Float32 V_L_msg; // message velocity of left wheel
std_msgs::Float32 V_R_msg; // message velocity of right wheel

// Call publisher
ros::Publisher EncL("Enc_L", &encL_msg); // Publish encoder of left wheel
ros::Publisher EncR("Enc_R", &encR_msg); // Publish encoder of right wheel
ros::Publisher Velocity_L("Velocity_L", &V_L_msg); // Publish velocity of left wheel
ros::Publisher Velocity_R("Velocity_R", &V_R_msg); // Publish velocity of right wheel

// Callback for subscribe
void CallBack_L(const std_msgs::Int32& pwmL_msg) {
  if (pwmL_msg.data > 0) {digitalWrite(11, HIGH);}
  else {digitalWrite(11, LOW);}
  analogWrite(10, abs(pwmL_msg.data));
}
void CallBack_R(const std_msgs::Int32& pwmR_msg) {
  if (pwmR_msg.data > 0) {digitalWrite(9, HIGH);}
  else {digitalWrite(9, LOW);}
  analogWrite(8, abs(pwmR_msg.data));
}

// Call subscriber
ros::Subscriber <std_msgs::Int32> Motor_L("/pwm_L", CallBack_L); // Subscribe pwm for drive left motor
ros::Subscriber <std_msgs::Int32> Motor_R("/pwm_R", CallBack_R); // Subscribe pwm for drive right motor

void setup() {
  // Set pin mode
  pinMode(11, OUTPUT); pinMode(10, OUTPUT); // Motor Left
  pinMode(9, OUTPUT); pinMode(8, OUTPUT); // Motor Right

  // ROS
  nh.initNode();
  nh.subscribe(Motor_L);
  nh.subscribe(Motor_R);
  nh.advertise(EncL);
  nh.advertise(EncR);
  nh.advertise(Velocity_L);
  nh.advertise(Velocity_R);
  V_L_msg.data = 0;
  V_R_msg.data = 0;
} 
long Time_start = micros();

void loop() {
  // Read encoder
  newPosition_L = myEnc_L.read();
  newPosition_R = myEnc_R.read();
  
  // value tick encoder and Pulse in 1 second
  if (newPosition_L != oldPosition_L) {
    oldPosition_L = newPosition_L;
    encL_msg.data = newPosition_L;
    Pulse_L ++;
    }
  if (newPosition_R != oldPosition_R) {
    oldPosition_R = newPosition_R;
    encR_msg.data = newPosition_R;
    Pulse_R ++;
    }

  // Compute velocity in one second
  float dt = (float)((micros() - Time_start)/1000000.0); // Delta time
  if (dt >= 1.0) {
    rpm_L = (Pulse_L/PPR)*60/dt;
    rpm_R = (Pulse_R/PPR)*60/dt;
    V_L_msg.data = rpm_L * 2*3.14/60 * r;
    V_R_msg.data = rpm_R * 2*3.14/60 * r;
    Pulse_L = 0;
    Pulse_R = 0;
    Time_start = micros();
    }

  // If tick encoder have more value, set value to zero
  if((abs(newPosition_L)>1000000)||(abs(newPosition_R)>1000000)) {
    myEnc_L.write(0);
    myEnc_R.write(0);
    }

  // Publish value to Nvidia Jetson nano
  Velocity_L.publish( &V_L_msg );
  Velocity_R.publish( &V_R_msg );
  EncL.publish( &encL_msg );
  EncR.publish( &encR_msg );

  // ROS spin
  nh.spinOnce();
  delay(10);
}
