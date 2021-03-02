/*Recieve Encoder
 */
 
const int in_D3_Pin_M1 = 3;  // D3
const int in_D2_Pin_M1 = 2;  // D2
const int out_PWM_Pin_M1 = 5;  // PWM
const int out_Dir_Pin_M1 = 4;  // Dir
const int in_D3_Pin_M2 = 13;  // D3
const int in_D2_Pin_M2 = 12;  // D2
const int out_PWM_Pin_M2 = 9;  // PWM
const int out_Dir_Pin_M2 = 8;  // Dir
const char CTCW = HIGH;
const char CW = LOW;
long pulse = 0;
int Value_PWM_M1 = 10;  // Value PWM
int Value_PWM_M2 = 0;  // Value PWM
int Switch = 1;
long P_time;
long Time;
int old_pulse_M1 = digitalRead(in_D3_Pin_M1);
int old_pulse_M2 = digitalRead(in_D3_Pin_M2);
int Round = 4;

void encoder() {
  
}

void setup() {
  pinMode(in_D3_Pin_M1, INPUT);
  pinMode(in_D2_Pin_M1, INPUT);
  pinMode(out_PWM_Pin_M1, OUTPUT);
  pinMode(out_Dir_Pin_M1, OUTPUT);
  pinMode(in_D3_Pin_M2, INPUT);
  pinMode(in_D2_Pin_M2, INPUT);
  pinMode(out_PWM_Pin_M2, OUTPUT);
  pinMode(out_Dir_Pin_M2, OUTPUT);
  Serial.begin (115200);
}

void loop() {
  int new_pulse = digitalRead(in_D3_Pin_M2);
  if (new_pulse != old_pulse) {
    old_pulse = new_pulse;
    pulse++;
    if (Switch == 1) {
      P_time = millis();
      Switch = 0;
      }
    if (pulse==1040*floor(1+Value_PWM_M2/100)) { // 2ppr (HIGH+LOW)
      Serial.print(Value_PWM_M2);
      Time = millis() - P_time;
      Serial.print(" ");
      Serial.println(1000*2*3.14159265*floor(1+Value_PWM_M2/100)/Time, 5);
      if (Value_PWM_M2 == 255) {
        if (Round == 1) {Value_PWM_M2 = -10;}
        else {
          Value_PWM_M2 = 6;  // Value_PWM_M2-10
          Round --;
          }
        }
      Value_PWM_M2 = min(Value_PWM_M2+10, 255);
      pulse = 0;
      Switch = 1;
    }
  }
    
  analogWrite(out_PWM_Pin_M2,Value_PWM_M2);
  digitalWrite(out_Dir_Pin_M2,CW);
}

// analogWrite(pin, pwm)

moveL = ideal_rpm
error = real_rpm() - ideal_rpm 
pwm = sdgsrdzgdhd
pwm = pwm + error 


void real_rpm(){
  encoder.Read() = 
  rpm = dsfasf
  return rpm 
}
