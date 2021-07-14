//roscore
// do catkina_ws -> source ./devel/setup.bash -> rosrun rosserial_python serial_node.py /dev/ttyUSB0
// sub -> rostopic pub silniki std_msgs/UInt16  1 --once 1- przod / 2-tyl / 3-lewo / 4-prawo / 5-stop
// pub -> rostopic echo encoder_info 
#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32MultiArray.h>

#define ENCODEROUTPUT 7125

Servo servo;

int sterowanie;
float encoderValue1;
float encoderValue2;
long previousMillis = 0;
long currentMillis = 0;
float rpm1 = 0;
float rpm2 = 0;
boolean measureRpm = false;
int interval = 1000;
int flag=0;
int pos = 95; 

ros::NodeHandle  nh;
std_msgs::Float32MultiArray encoder_msg;
ros::Publisher pub_encoder("encoder_info", &encoder_msg);

void sub_silniki(const std_msgs::UInt16& cmd_msg){
  sterowanie=cmd_msg.data;

  
  if (sterowanie == 1){    // warunek przeuniecia w lewo
    digitalWrite(9, HIGH);  //Engage the Brake for Channel A
    digitalWrite(8, HIGH);  //Engage the Brake for Channel B
    delay(1000);
          
    digitalWrite(12, HIGH); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 255);   //Spins the motor on Channel A at full speed

    digitalWrite(13, LOW); //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 255);   //Spins the motor on Channel B at full speed
    flag =1;
    pos=95;
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    }
  if (sterowanie == 2){      // warunek przeuniecia w prawo
    digitalWrite(9, HIGH);  //Engage the Brake for Channel A
    digitalWrite(8, HIGH);  //Engage the Brake for Channel B
    delay(1000);
          
    digitalWrite(12, LOW);  //Establishes backward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 255);    //Spins the motor on Channel A at half speed

    digitalWrite(13, HIGH); //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 255);   //Spins the motor on Channel B at full speed
    flag =-1;
    pos=95;
    servo.write(pos); 
    }
  if (sterowanie == 3){
    pos=pos+10;
    servo.write(pos);    
    }
  if (sterowanie == 4){
    pos=pos-10;
    servo.write(pos);    
    }
  if (sterowanie == 5){      // warunek przeuniecia w prawo
    digitalWrite(9, HIGH);  //Engage the Brake for Channel A
    digitalWrite(8, HIGH);  //Engage the Brake for Channel B
    delay(1000);
    }
}

ros::Subscriber<std_msgs::UInt16> sub("silniki", sub_silniki);

void setup() {
  
  //zdefiniowanie portow shield'a do silnikow
    //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
    //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
  EncoderInit();//Initialize the module
  
  //poczatkowa wartosc z encoderow
  encoderValue1 = 0;
  encoderValue2 = 0;
  
  //ustawienie serwa na "prosto"
  servo.attach(7);  // attaches the servo on pin 9 to the servo object
  servo.write(pos);              // tell servo to go to position in variable 'pos'


  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_encoder);
  encoder_msg.data = (float*)malloc(sizeof(float) * 2);
  encoder_msg.data_length = 2;
}

void loop() {
 nh.spinOnce();
 

 //odczytwyanie danch z encoderow
  int b1= digitalRead(5);
  int a1= digitalRead(2);
  
  if(a1>0&&b1<1){
      encoderValue1++;
    }
   if(a1<1&&b1>0){
     encoderValue1++;
  }

  int a2= digitalRead(4);
  int b2= digitalRead(6);
  if(a2>0&&b2<1){
      encoderValue2++;
    }
   if(a2<1&&b2>0){
     encoderValue2++;
  }
  
//
  // Update RPM value on every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;


    // Revolutions per minute (RPM) =
    // (total encoder pulse in 1s / motor encoder output) x 60s
    rpm1 = (float)(encoderValue1*flag * 60 / ENCODEROUTPUT);
    rpm2 = (float)(encoderValue2*flag * 60 / ENCODEROUTPUT);

    // Only update display when there have readings
     /* Serial.print(encoderValue1);
      Serial.print(" pulse / ");
      Serial.print(ENCODEROUTPUT);
      Serial.print(" pulse per rotation x 60 seconds = ");
      Serial.print(rpm1);
      Serial.println(" RPM1");
    
      Serial.print(encoderValue2);
      Serial.print(" pulse / ");
      Serial.print(ENCODEROUTPUT);
      Serial.print(" pulse per rotation x 60 seconds = ");
      Serial.print(rpm2);
      Serial.println(" RPM2");*/
      encoder_msg.data[0]=rpm1;
      encoder_msg.data[1]=rpm2;
      pub_encoder.publish( &encoder_msg );
      encoderValue1 = 0;
      encoderValue2 = 0;
  }

}

void EncoderInit()
{
 // Attach interrupt at hall sensor A on each rising signal
  int b1= digitalRead(4);
  int a1= digitalRead(2);
  Serial.print("A1 ");
  Serial.print(a1);
  Serial.print("B1 ");
  Serial.println(b1);
  
  if(a1>0){
    if(b1>0){
      encoderValue1++;
    }
  else{
   encoderValue1--;
  }
 }

  int a2= digitalRead(3);
  int b2= digitalRead(5);
  Serial.print("A2 ");
  Serial.print(a2);
  Serial.print("B2 ");
  Serial.println(b2);
  if(a2>0){
    if(b2>0){
      encoderValue2++;
    }
  else{
   encoderValue2--;
  }
 }
}
