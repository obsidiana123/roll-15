/////////////////////////

int x1 = 211;
int y1 = 299;




char controleX = 'a';
char controleY = 'a';
//////////////////////////////
char tecla = 'r' ;

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


uint8_t servoX = 5;
uint8_t servoY = 4;

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);
}



void loop() {
  tecla = Serial.read();  
  
  
//centraliza cabeça
if(controleX =='a'){controleX = 'b'; pwm.setPin(servoX , 211);Serial.println("servo_x ok");}
if(controleY =='a'){controleY = 'b'; pwm.setPin(servoY , 299);Serial.println("servo_y ok");}
  
if(tecla =='a'){
    
  if(x1 < 211){
    for ( x1 = x1; x1 < 211;) {
      x1++;  
      delay(10);
      pwm.setPin(servoX , x1);
      Serial.println(x1);
      }
  }
}

if(tecla =='a'){ 
   if(x1 > 211){ 
    for ( x1 = x1; x1 > 211;) {  
      x1--;
      delay(10);
      pwm.setPin(servoX , x1);
     Serial.println(x1);  
    } 
  }
}
if(tecla =='a'){
    
  if(x1 < 299){
    for ( y1 = y1; y1 < 299;) {
      y1++;  
      delay(10);
      pwm.setPin(servoY , y1);
      Serial.println(y1);
      }
  }
}

if(tecla =='a'){ 
   if(y1 > 299){ 
    for ( y1 = y1; y1 > 299;) {  
      y1--;
      delay(10);
      pwm.setPin(servoX , y1);
     Serial.println(y1);  
    } 
  }
}

//controla servo horizontal x
if(tecla =='s'){for (int x = 0; x < 11; x++) { delay(10);x1++; pwm.setPin(servoX , x1);Serial.println(x1);}}
if(tecla =='d'){for (int x = 0; x < 11; x++) { delay(10);x1--; pwm.setPin(servoX , x1);Serial.println(x1);}}

//controla servo vertical y
if(tecla =='f'){for (int y = 0; y < 11; y++) { delay(10);y1++; pwm.setPin(servoY , y1);Serial.println(y1);}}
if(tecla =='h'){for (int y = 0; y < 11; y++) { delay(10);y1--; pwm.setPin(servoY , y1);Serial.println(y1);}}

/////////////////////////////////////////////////////////////////////////////




////////////motores////////////////////////////////////////////////////////////////////////////

 
                 
////////////para frente//////////////////////////////////////////////////   
 if(tecla =='j'){for (int x = 0; x < 20; x++) {

                 Serial.println("para frente");

                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 4500);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 4500);
                 

                 

                }  

                 //para rodas
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
}                                          
 
/////////////////////////////////////////////////////////////////////////////

//////////////////////para rodas///////////////////////////////////////////////////////

                 if(tecla == 'k')
                 {
                 Serial.println("para rodas");
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 }                          

/////////////////////////////////////////////////////////////////////////////


////////////direita//////////////////////////////////////////////////                           
                 if(tecla == 'l')
                 {
                 Serial.println("direita");
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 pwm.setPin(1 , 4500);                   
                 pwm.setPin(2 , 4500);
                 delay(1000);
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 }                            
 
/////////////////////////////////////////////////////////////////////////////

////////////esquerda//////////////////////////////////////////////////                           
                 if(tecla == 'ç')
                 {
                 Serial.println("esquerda");
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 pwm.setPin(0 , 4500);                   
                 pwm.setPin(3 , 4500);
                 delay(1000);
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 
                 }                            
 
/////////////////////////////////////////////////////////////////////////////



}
