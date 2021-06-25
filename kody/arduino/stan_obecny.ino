#define ENCODEROUTPUT 7125

int thisChar = 0; 
volatile long encoderValue1 = 0;
volatile long encoderValue2 = 0;
long previousMillis = 0;
long currentMillis = 0;
int rpm1 = 0;
int rpm2 = 0;
boolean measureRpm = false;
int interval = 1000;
int flag=0;

void setup() {
Serial.begin(9600);//Initialize the serial port
 EncoderInit();//Initialize the module
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
      Serial.write(thisChar); 
      Serial.println(" ");
      
      
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
          flag =1;
  
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
          flag =-1;
      }
      if (thisChar == 'z'){      // warunek przeuniecia w prawo
          digitalWrite(9, HIGH);  //Engage the Brake for Channel A
          digitalWrite(8, HIGH);  //Engage the Brake for Channel B
          delay(1000);
          flag =0;
      }
  }

  int b1= digitalRead(4);
  int a1= digitalRead(2);
 // Serial.print("A1 ");
 // Serial.print(a1);
 // Serial.print("B1 ");
 // Serial.println(b1);
  
  if(a1>0&&b1<1){
      encoderValue1++;
    }
   if(a1<1&&b1>0){
     encoderValue1++;
  }

  int a2= digitalRead(3);
  int b2= digitalRead(5);
  //Serial.print("A2 ");
 // Serial.print(a2);
  //Serial.print("B2 ");
  //Serial.println(b2);
  if(a2>0&&b2<1){
      encoderValue2++;
    }
   if(a2<1&&b2>0){
     encoderValue2++;
  }
  
  // Update RPM value on every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;


    // Revolutions per minute (RPM) =
    // (total encoder pulse in 1s / motor encoder output) x 60s
    rpm1 = (float)(encoderValue1*flag * 60 / ENCODEROUTPUT);
    rpm2 = (float)(encoderValue2*flag * 60 / ENCODEROUTPUT);

    // Only update display when there have readings
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
      Serial.println(" RPM2");

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
