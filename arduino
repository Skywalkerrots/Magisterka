"
 */

#include <ros.h>
#include <std_msgs/Int16MultiArray.h>

ros::NodeHandle  nh;
int table[6]={0,0,0,0,0,0};
std_msgs::Int16MultiArray str_msg;
ros::Publisher chatter("chatter", &str_msg);

#define echoPin1 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin2 5 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin3 6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin3 7 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration1; // variable for the duration of sound wave travel
int distance1; // variable for the distance measurement
long duration2; // variable for the duration of sound wave travel
int distance2; // variable for the distance measurement
long duration3; // variable for the duration of sound wave travel
int distance3; // variable for the distance measurement


void setup()
{
nh.initNode();
nh.advertise(chatter);

  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin3, INPUT); // Sets the echoPin as an INPUT
Serial.begin(57600); // // Serial Communication is starting with 9600 of baudrate speed

}
void loop()
{
str_msg.data = table;
str_msg.data_length = 6;
chatter.publish( &str_msg );
nh.spinOnce();
delay(1000);

//czujnik1
// Clears the trigPin condition
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  table[0]=distance1;

  //czujnik 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  table[1]=distance2;
  
//czujnik3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration3 = pulseIn(echoPin3, HIGH);
  // Calculating the distance
  distance3 = duration3 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  table[2]=distance3;

}
