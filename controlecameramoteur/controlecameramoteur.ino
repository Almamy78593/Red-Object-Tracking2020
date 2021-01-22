#include <Servo.h>

Servo monServoVertical;
Servo monServoHorizontal;
int led =13;
int positionH = 40;
int positionV = 30;

void setup(){
  monServoVertical.attach(6);
  monServoHorizontal.attach(7);
  monServoHorizontal.write(positionH);
  monServoVertical.write(positionV);
  pinMode(led,OUTPUT);
  Serial.begin(9600);

}

void loop(){
 while(Serial.available()>0){
   switch(Serial.read()){
     case 's': positionV += 1;
               monServoVertical.write(positionV);
               
               break;
     case 'z': positionV -= 1;
               monServoVertical.write(positionV);
               
               break;
               
     case 'j': positionV += 1;
               monServoVertical.write(positionV);
               
               break;
     case 'u': positionV -= 1;
               monServoVertical.write(positionV);
               
               break;
               
               
     case 'm': positionH += 2;
               monServoHorizontal.write(positionH);
     
               break;
     case 'f': positionH -= 2;
               monServoHorizontal.write(positionH);
               
               break;
               
     case 'l': positionH += 2;
               monServoHorizontal.write(positionH);
     
               break;
     case 'g': positionH -= 2;
               monServoHorizontal.write(positionH);
               
               break;
               
     case 'k': positionH += 1;
               monServoHorizontal.write(positionH);
     
               break;
     case 'h': positionH -= 1;
               monServoHorizontal.write(positionH);
               
               break;
     default : for(int i=0; i<3;i++){
                 digitalWrite(led,HIGH);
                 
                 digitalWrite(led,LOW);
                 monServoVertical.write(positionV);
                 monServoHorizontal.write(positionH);
               }
               break;      
   }
 }
  
  
}

