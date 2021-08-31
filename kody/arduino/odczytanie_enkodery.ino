/*
 * Author: Automatic Addison
 * Website: https://automaticaddison.com
 * Description: Calculate the angular velocity in radians/second of a DC motor
 * with a built-in encoder (forward = positive; reverse = negative) 
 */
 
// Motor encoder output pulses per 360 degree revolution (measured manually)
#define ENC_COUNT_REV 341.2
 
// Encoder output to Arduino Interrupt pin. Tracks the pulse count.
#define ENC_IN_RIGHT_A 3
#define ENC_IN_LEFT_A 2
 
// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.
#define ENC_IN_RIGHT_B 5
#define ENC_IN_LEFT_B 4
 
// True = Forward; False = Reverse
boolean Direction_right = true;
boolean Direction_left = true;
 
// Keep track of the number of right wheel pulses
volatile long right_wheel_pulse_count = 0;
volatile long left_wheel_pulse_count = 0;
 
// One-second interval for measurements
int interval = 1000;
  
// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;

long time_begin = 0;
long time_end = 0;
// Variable for RPM measuerment
float rpm_right = 0;
float rpm_linear = 0;
float rpm_left = 0;
float rpm_linear_left = 0;
 
// Variable for angular velocity measurement
float ang_velocity_right = 0;
float ang_velocity_right_deg = 0;
 
const float rpm_to_radians = 0.10471975512;
const float rad_to_deg = 57.29578;
 
void setup() {
 
  // Open the serial port at 9600 bps
  Serial.begin(9600); 
 
  // Set pin states of the encoder
  pinMode(ENC_IN_LEFT_A , INPUT_PULLUP);
  pinMode(ENC_IN_LEFT_B , INPUT);
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
    //Setup Channel B
  pinMode(8, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT);  //Initiates Brake Channel A pin
  pinMode(10, OUTPUT); //Initiates Motor Channel A pin
  pinMode(11, OUTPUT);  //Initiates Brake Channel A pin
 
  // Every time the pin goes high, this is a pulse
  //attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), left_wheel_pulse, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING);
}
 
void loop() {
  //Motor B backward @ half speed
  digitalWrite(8, HIGH);  //Establishes backward direction of Channel B
  digitalWrite(9, LOW);   //Disengage the Brake for Channel B
  analogWrite(7, 225);    //Spins the motor on Channel B at half speed

  digitalWrite(10, HIGH);  //Establishes backward direction of Channel B
  digitalWrite(11, LOW);   //Disengage the Brake for Channel B
  analogWrite(6, 225);    //Spins the motor on Channel B at half speed
  // Record the time
  currentMillis = millis();
 
  // If one second has passed, print the number of pulses
  if (currentMillis - previousMillis > interval) {
 
    previousMillis = currentMillis;
 
    // Calculate revolutions per minute
    rpm_right = (float)(right_wheel_pulse_count * 60 / ENC_COUNT_REV);
    rpm_linear = rpm_right*0.062*3.14/ 60;
    rpm_left = (float)(left_wheel_pulse_count * 60 / ENC_COUNT_REV);
    rpm_linear_left = rpm_left*0.062*3.14/ 60;
   
    ang_velocity_right = rpm_right * rpm_to_radians;   
    ang_velocity_right_deg = ang_velocity_right * rad_to_deg;
     
    Serial.print(" Pulses right: ");
    Serial.println(right_wheel_pulse_count);
    Serial.print(" Pulses left: ");
    Serial.println(left_wheel_pulse_count);
    Serial.print(" Speed right: ");
    Serial.print(rpm_right);
    Serial.print(" Speed left: ");
    Serial.print(rpm_left);
    Serial.println(" RPM");
    Serial.print(" Linear Velocity: ");
    Serial.println(rpm_linear);
    Serial.print(" Angular Velocity: ");
    Serial.print(rpm_right);
    Serial.print(" rad per second");
    Serial.print("\t");
    Serial.print(ang_velocity_right_deg);
    Serial.println(" deg per second");
    Serial.println();
 
    right_wheel_pulse_count = 0;
    left_wheel_pulse_count = 0;
   
  }
}
 
// Increment the number of pulses by 1
void left_wheel_pulse() {

  // Read the value for the encoder for the right wheel
  int val = digitalRead(ENC_IN_LEFT_B);
 
  if(val == LOW) {
    Direction_left = false; // Reverse
  }
  else {
    Direction_left = true; // Forward
  }
   
  if (Direction_left) {
   left_wheel_pulse_count++;
  }
  else {
    left_wheel_pulse_count--;
  }
}
void right_wheel_pulse() {

  // Read the value for the encoder for the right wheel
  int val = digitalRead(ENC_IN_RIGHT_B);
 
  if(val == LOW) {
    Direction_right = false; // Reverse
  }
  else {
    Direction_right = true; // Forward
  }
   
  if (Direction_right) {
    right_wheel_pulse_count++;
  }
  else {
    right_wheel_pulse_count--;
  }
}
