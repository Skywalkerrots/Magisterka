

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

int dane = 0;
int flaga = 0;
char wiadomosc[3] = "40" ;
ros::NodeHandle  nh;

Servo servo;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
void servo_cb( const std_msgs::UInt16& cmd_msg){
  dane = cmd_msg.data;
  flaga = 1;
  if(dane == 10){
    wiadomosc[3]=dane;
    str_msg.data= wiadomosc;
    chatter.publish( &str_msg );
  servo.write(80); //set servo angle, should be from 0-180  
  }
  if(dane == 20){
    wiadomosc[3]=dane;
    str_msg.data= wiadomosc;
    chatter.publish( &str_msg );
  servo.write(100); //set servo angle, should be from 0-180  
  }
}


ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);


void setup(){

  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
  
  servo.attach(9); //attach it to pin 9
}

void loop(){
 // str_msg.data= wiadomosc;
  //if (flaga==1){
  //  chatter.publish( &str_msg );
  //  flaga=0;
 // }
  nh.spinOnce();
  delay(1);
}
