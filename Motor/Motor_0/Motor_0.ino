/*Test Motor
 */
const int in_pwm_Pin_M2 = 9;  // PWM
const int in_dir_Pin_M2 = 8;  // Dir
const int in_pwm_Pin_M1 = 5;  // PWM
const int in_dir_Pin_M1 = 4;  // Dir
const int value_M2 = 0;  // Value PWM 16
const int value_M1 = 0;  // Value PWM 10
const int value = 0;  // Value PWM

void setup() {
  pinMode(in_pwm_Pin_M2, OUTPUT); 
  pinMode(in_dir_Pin_M2, OUTPUT);
  pinMode(in_pwm_Pin_M1, OUTPUT); 
  pinMode(in_dir_Pin_M1, OUTPUT); 
}

void loop() {
  analogWrite(in_pwm_Pin_M2,value_M2);
  digitalWrite(in_dir_Pin_M2,HIGH); // HIGH=CTCW, LOW=CW
  analogWrite(in_pwm_Pin_M1,value_M1);
  digitalWrite(in_dir_Pin_M1,HIGH); // HIGH=CTCW, LOW=CW
}
