#include <Encoder.h>

Encoder knobLeft(5, 6);
Encoder knobRight(7, 8);

#define ENCODEROUTPUT 341

#define ENA1  2
#define ENA2  4

//The sample code for driving one way motor encoder
volatile long encoderValue1 = 0;
volatile long encoderValue2 = 0;
int thisChar = 0;  
int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;
int rpm1 = 0;
int rpm2 = 0;
boolean measureRpm = false;

void setup() {

  Serial.begin(57600);//Initialize the serial port
 // pinMode(ENA1,INPUT);
 // pinMode(ENA2,INPUT);
 // EncoderInit();//Initialize the module
    //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
    //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
  encoderValue1 = 0;
  encoderValue2 = 0;
  previousMillis = millis();
   
}

void loop() {

  
if (Serial.available() > 0) {          // sprawdzamy, czy są dane w buforze portu szeregowego:
       thisChar = Serial.read();         //pobieramy pierwszy bajt z bufora:
      Serial.print("Wysłano: ");
      Serial.write(thisChar);            //wysyłamy zwrotnie ten sam odczytany bajt(potwierdzenie)
      
      
      if (thisChar == 'w'){    // warunek przeuniecia w lewo
          digitalWrite(9, HIGH);  //Engage the Brake for Channel A
          digitalWrite(8, HIGH);  //Engage the Brake for Channel B
          delay(1000);
          
          digitalWrite(12, HIGH); //Establishes forward direction of Channel A
          digitalWrite(9, LOW);   //Disengage the Brake for Channel A
          analogWrite(3, 255);   //Spins the motor on Channel A at full speed

          digitalWrite(13, LOW); //Establishes forward direction of Channel B
          digitalWrite(8, LOW);   //Disengage the Brake for Channel B
          analogWrite(11, 255);   //Spins the motor on Channel B at full speed
  
      }
      if (thisChar == 's'){      // warunek przeuniecia w prawo
          digitalWrite(9, HIGH);  //Engage the Brake for Channel A
          digitalWrite(8, HIGH);  //Engage the Brake for Channel B
          delay(1000);
          
          digitalWrite(12, LOW);  //Establishes backward direction of Channel A
          digitalWrite(9, LOW);   //Disengage the Brake for Channel A
          analogWrite(3, 123);    //Spins the motor on Channel A at half speed

          digitalWrite(13, HIGH); //Establishes forward direction of Channel B
          digitalWrite(8, LOW);   //Disengage the Brake for Channel B
          analogWrite(11, 255);   //Spins the motor on Channel B at full speed
      }
      if (thisChar == 'z'){      // warunek przeuniecia w prawo
          digitalWrite(9, HIGH);  //Engage the Brake for Channel A
          digitalWrite(8, HIGH);  //Engage the Brake for Channel B
          delay(1000);
      }
} 
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
   Serial.print("Left = ");
   Serial.print(newLeft);
   Serial.print(", Right = ");
   Serial.print(newRight);
   Serial.println();
 // Update RPM value on every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    // Revolutions per minute (RPM) =
    // (total encoder pulse in 1s / motor encoder output) x 60s
    rpm1 = (float)(newLeft * 60 / ENCODEROUTPUT);
    rpm2 = (float)(newRight * 60 / ENCODEROUTPUT);

   /* // Only update display when there have readings
      Serial.print(encoderValue1);
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

    encoderValue1 = 0;
    encoderValue2 = 0;
  }
}

void EncoderInit()
{
 // Attach interrupt at hall sensor A on each rising signal
  attachInterrupt(digitalPinToInterrupt(ENA2), updateEncoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(ENA1), updateEncoder1, RISING);
//  attachInterrupt(digitalPinToInterrupt(ENA2), updateEncoder2, RISING);
}


void updateEncoder1()
{
  int b= digitalRead(3);
  if(b>0){
    encoderValue1++;
  }
  else{
   encoderValue1--;
  }
}
void updateEncoder2()
{
  int b= digitalRead(7);
  if(b>0){
    encoderValue2++;
  }
  else{
   encoderValue2--;
  }
}
