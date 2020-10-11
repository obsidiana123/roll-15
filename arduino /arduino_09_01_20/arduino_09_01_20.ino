#include <Ultrasonic.h>
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <MaxMatrix.h>



#define SERVO 11 // Porta Digital horizontal
#define SERVO1 10 // Porta Digital vertical


char tecla = "ww" ; 
////////////////////////0/////////////////// pinaagem da matriz de leds///////////////////////////
int DIN = 7;
int CLK = 6;
int CS = 5;
int maxInUse = 1;
int yy;

MaxMatrix m(DIN, CS, CLK, maxInUse);

byte olhoesquerda[] = {8, 8,0x00, 0x78, 0xcc, 0xcc, 0xfc, 0xfc, 0x78, 0x00};

byte olhos[] = {8, 8,0x00, 0x78, 0xf8, 0x98, 0x98, 0xf8, 0x78, 0x00};

byte olhobaixo[] = {8, 8,0x00, 0x78, 0xfc, 0x9c, 0x9c, 0xfc, 0x78, 0x00};
              
byte olhodireita[] = {8, 8,0x00, 0x78, 0xfc, 0xfc, 0xcc, 0xcc, 0x78, 0x00};
 
byte olhocima[] = {8, 8,0x00, 0x78, 0xfc, 0xe4, 0xe4, 0xfc, 0x78, 0x00};  
  
byte olhopisca[] = {8, 8,0x10, 0x08, 0x08, 0xe8, 0x08, 0x08, 0x10, 0x00};               
              

///////////////////////////////////////////////////////////////////////////////////////////////////////////////



int LED = 13;
int pisca =0;
int pisca2 =0;
char entrada;

Servo s; // Variável Servo
Servo s2; // Variável Servo


char str[15];

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin
 
// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int i = 0;
int pos= 90;
int pos1= 90;
int number = 0;



char test;

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 100;           // interval at which to blink (milliseconds)


void setup() {

  m.init();
  m.setIntensity(0);
  
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  Wire.begin(0x18);
  s.attach(SERVO);
  s2.attach(SERVO1);


  Serial.println("GPIO test!");
  pwm.begin();
  pwm.setPWMFreq(60);  // Set to whatever you like, we don't use it in this demo!
  Wire.setClock(400000);






  
}

void Pisca() {

//FECHA OLHOS
byte A1[] = {8, 8,0x00, 0x78, 0xf8, 0x98, 0x98, 0xf8, 0x78, 0x00}; delay(100);  m.writeSprite(0, 0, A1);
byte A2[] = {8, 8,0x00, 0x70, 0x70, 0x50, 0x50, 0x70, 0x70, 0x00}; delay(100);  m.writeSprite(0, 0, A2);
byte A3[] = {8, 8,0x00, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x00}; delay(100);  m.writeSprite(0, 0, A3);
byte A4[] = {8, 8,0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00}; delay(200);  m.writeSprite(0, 0, A4);

//ABRE OLHOS
byte B4[] = {8, 8,0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00}; delay(100);  m.writeSprite(0, 0, B4);
byte B3[] = {8, 8,0x00, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x00}; delay(100);  m.writeSprite(0, 0, B3);
byte B2[] = {8, 8,0x00, 0x70, 0x70, 0x50, 0x50, 0x70, 0x70, 0x00}; delay(100);  m.writeSprite(0, 0, B2);
byte b1[] = {8, 8,0x00, 0x78, 0xf8, 0x98, 0x98, 0xf8, 0x78, 0x00}; delay(100);  m.writeSprite(0, 0, b1);
}

void loop() {

  // if (Serial.available())  //verifica se tem dados diponível para leitura
   // {m.writeSprite(0, 0, olhos);}

    m.writeSprite(0, 0, olhos);
    

  

  


 
  //Serial.println("on line");


  tecla = Serial.read();  
    
    
///////////////////servo horizontal////////////////////////////////////////////////  


////////////////cabeca para centro horizontal//////////////////////////////////////////////
  
    if(tecla == 's')// tecla t para teste
    {
      if(pos <= 90){
      for(pos = pos; pos <= 90; pos++)
     {
      delay(40);
      tecla = Serial.read();
      if(tecla == 'p'){break;}
      s.write(pos);

       } 
     }
      if(pos >= 90){
      for(pos = pos; pos >= 90; pos--)
     {
      delay(40);
      tecla = Serial.read();
      if(tecla == 'p'){break;}
      s.write(pos);
  
       } 
     }      
    }

/////////////////////////////////////////////////////////////////////////////////////////////


    
/////////////cabeca para direita////////////////////////////////////////////////////////////
    
    if(tecla == 'a')// tecla t para teste
    {
     for(pos = pos; pos >= 1; pos--)
     {
     m.writeSprite(0, 0, olhoesquerda);
     //m.setIntensity(3);
     Serial.println("olho para direita");
     delay(40);
     tecla = Serial.read();
     if(tecla == 'p'){break;}
     s.write(pos);

     }
    }    

    
///////////////////////cabe;a para esquerda////////////////////////////////////////////  
    if(tecla == 'd')// tecla t para teste
    {
     for(pos = pos; pos <= 179; pos++)
     {
     m.writeSprite(0, 0, olhodireita);
     //m.setIntensity(0);
     Serial.println("olho para direita");
     delay(40);
     tecla = Serial.read();
     if(tecla == 'p'){break;}
     s.write(pos); 

     }
    } 
  
 ///////////////////servo vertical////////////////////////////////////////////////////////



 
/////////////////caba;a para centro vertical////////////////////////////////////////////


    if(tecla == 'w')// tecla t para teste
    { 
      Serial.println("centro vertical");
      if(pos1 <= 45){
      for(pos1 = pos1; pos1 <= 45; pos1++)
     {
      delay(40);
      tecla = Serial.read();
      if(tecla == 'p'){break;}
      s2.write(pos1);
       } 
     }
      if(pos1 >= 45){
      for(pos1 = pos1; pos1 >= 45; pos1--)
     {
      delay(40);
      tecla = Serial.read();
      if(tecla == 'p'){break;}
      s2.write(pos1);
       } 
     }      
    }



//////////cabe;a para cima////////////////////////////////////////////////////////        
    if(tecla == 'q')// tecla t para teste
    {Serial.println("cabe;a para cima");
     for(pos1 = pos1; pos1 >= 1; pos1--)
     {
     delay(40);
     tecla = Serial.read();
     if(tecla == 'p'){break;}
     s2.write(pos1); 
     m.writeSprite(0, 0, olhocima);
     }
    }    
//////////////cabe;a para baixo///////////////////////////////////////////////////  
    if(tecla == 'e')// tecla t para teste
    {Serial.println("cabe;a para baixo");
     for(pos1 = pos1; pos1 <= 60; pos1++)
     {
     delay(40);
     tecla = Serial.read();
     if(tecla == 'p'){break;} 
     s2.write(pos1); 
     m.writeSprite(0, 0, olhobaixo);
     }
    } 
  
    test = tecla;
 ///////////////////////////////////////////////////////////////////////
////////////para atrais//////////////////////////////////////////////////   
                 if(test == 'k')
                 {
                 Serial.println("para atrais");
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 pwm.setPin(1 , 4500);
                 pwm.setPin(3 , 4500);
                 }                            
                
/////////////////////////////////////////////////////////////////////////////

////////////para frente//////////////////////////////////////////////////                           
                 if(test == 'l')
                 {
                 Serial.println("para frente");
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 pwm.setPin(0 , 4500); 
                 pwm.setPin(2 , 4500);
                 }                            
 
/////////////////////////////////////////////////////////////////////////////

//////////////////////para rodas///////////////////////////////////////////////////////

                 if(test == 'j')
                 {
                 Serial.println("para rodas");
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 }                          

/////////////////////////////////////////////////////////////////////////////


////////////direita//////////////////////////////////////////////////                           
                 if(test == 'h')
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
                 if(test == 'g')
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


///////////pisca olhos))))))))))))))))))))))
                  if(test == 'v')
                 {
                     Serial.println("piscando olhos");
             
                    // m.writeSprite(0, 0,  olhopisca);
                     Pisca();
                     delay(2000);
                     m.clear();
                 } 

/////////////////////////espera////////////////////////////////////////////////////
                 if(test == 't')
                 {
                  for (int t = 0; t <= 2; t++) {
                  Serial.println("Em espera");
                  m.setIntensity(1);
                  m.writeSprite(0, 0, olhos);
                  delay(700);
                  m.setIntensity(0); 
                  m.writeSprite(0, 0, olhos);  
                  delay(700);  
                        }
                       

                  
                 }



////////////pisca com tempo//////////////////////////////////
                 

                   
                     pisca = pisca + 1;
    
                     if (pisca <100){digitalWrite(LED_BUILTIN, HIGH); }
                     if (pisca >100){digitalWrite(LED_BUILTIN, LOW); }
                     if (pisca >200){pisca = 1; }
                  
                 
                 


   
                 
                 
/////////////////////////////////////////////////////////////// 


 
}
