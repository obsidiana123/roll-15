//k animacao
//g led vermelho
//r led verde
//b led azul
//q pisca led
//w sorriso grande
//e sorriso pequeno
//t sorriso triste
//y falando
//u piscando olhos
//i leds em espera
//o reiniciando arduino

#include <Wire.h>
#include <HMC5883L_Simple.h>
#include <Arduino.h>
#include <MaxMatrix.h> 
#include <Adafruit_PWMServoDriver.h>


///////////variaveis do servo motor 
int q2 = 480;
int q1 = 120;

int q3 = 480;
int q4 = 120;

double Qa;
double Qb;

//servo horizintal porta do modulo
int v = 4;

//servo vertical porta do modulo
int h =5;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

/////////////////////////////////////////


///////////////////////////////////// pinaagem da matriz de leds//////////////////////////
int DIN = 7;
int CLK = 6;
int CS = 5;
int maxInUse = 1;


MaxMatrix m(DIN, CS, CLK, maxInUse);

byte olhoesquerda[] = {8, 8,0x00, 0x78, 0xcc, 0xcc, 0xfc, 0xfc, 0x78, 0x00};

byte olhos[] = {8, 8,0x00, 0x78, 0xf8, 0x98, 0x98, 0xf8, 0x78, 0x00};

byte olhobaixo[] = {8, 8,0x00, 0x78, 0xfc, 0x9c, 0x9c, 0xfc, 0x78, 0x00};
              
byte olhodireita[] = {8, 8,0x00, 0x78, 0xfc, 0xfc, 0xcc, 0xcc, 0x78, 0x00};
 
byte olhocima[] = {8, 8,0x00, 0x78, 0xfc, 0xe4, 0xe4, 0xfc, 0x78, 0x00};  
  
byte olhopisca[] = {8, 8,0x10, 0x08, 0x08, 0xe8, 0x08, 0x08, 0x10, 0x00};               
              

void olhos_fechados() {

byte A11[] = {8, 8,0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}; delay(100);  m.writeSprite(0, 0, A11);
byte A12[] = {8, 8,0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00}; delay(100);  m.writeSprite(0, 0, A12); 
byte A13[] = {8, 8,0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}; delay(100);  m.writeSprite(0, 0, A13); 
byte A14[] = {8, 8,0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00}; delay(100);  m.writeSprite(0, 0, A14);
byte A15[] = {8, 8,0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}; delay(100);  m.writeSprite(0, 0, A15);


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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////




char tecla = 'r' ;
char contagem = 'a' ;
int pino = 11 ;


int cor      = (0,255,0);
int vermelho = (255,0,0);
int verde    = (0,255,0);
int azul     = (0,0,255);

//VARIAVEIS DO LE RGB
int pinoRed = 9; //PINO DIGITAL UTILIZADO PELO TERMINAL VERMELHO
int pinoGreen = 10; //PINO DIGITAL UTILIZADO PELO TERMINAL VERDE
int pinoBlue = 11; //PINO DIGITAL UTILIZADO PELO TERMINAL AZUL
int val; //VARIÁVEL DO TIPO INTEIRA
//////////////////////////////////////////////////////////////

//////////////////////// LEDS ANEL 
#include <FastLED.h>
#define LED_PIN 8
#define NUM_LEDS 16
uint8_t i = 0;
CRGB leds[NUM_LEDS];
CRGB leds1[NUM_LEDS];

//////////////////////////////

int tem;// VARIAVEL DO TEMPORALIZADOR 
int tem1;// VARIAVEL DO TEMPORALIZADOR 
int tem2;// VARIAVEL DO TEMPORALIZADOR 
int tem2a;// VARIAVEL DO TEMPORALIZADOR 




/////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  FastLED.addLeds<WS2811,LED_PIN,GRB>(leds,NUM_LEDS);
  //matriz de led
  m.init();
  m.setIntensity(3);


//TEMPORALIZADOR
  pinMode(pinoRed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoBlue, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoGreen, OUTPUT); //DEFINE O PINO COMO SAÍDA

  pinMode(9,  OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(10, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(11, OUTPUT); //DEFINE O PINO COMO SAÍDA
 ///////////

//servo motor
  pwm.begin();
  pwm.setPWMFreq(50);  // Set to whatever you like, we don't use it in this demo!
  Wire.setClock(400000);
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop() {

 m.writeSprite(0, 0, olhos);

  
//temporalizador
delay(1);
tem1++;// 
tem2++;
tem++;
if(contagem == 'a'){
                    if(tem2 == 5){tem2a++;tem2 =0;}
                    if(tem2a == 250){contagem = 'b';}  
                    }

if(contagem == 'b'){
                    if(tem2 == 5){tem2a--;tem2 =0;}
                    if(tem2a == 0){contagem = 'a';}  
                    }



/////LED DA PLACA ARDUINO
if( tem < 100){digitalWrite(LED_BUILTIN, HIGH);}// liga led por 1 segundo
if( tem > 100){digitalWrite(LED_BUILTIN, LOW);}// DESLIGA LED POR 1 SEGUNDO 
if( tem > 250){ tem =0; } //apaga temporalizador
/////////////////////////////////////////////////////
  

tecla = Serial.read();  



  if(tecla == 'k')
                 {
                        
                        for(int pos1 = 0; pos1 < 10; pos1++)
                             {
                              Serial.println("animacao");
      
     
                                               
                              //TEMPORALIZADOR 
                               delay(1);
                              
                              
                              /////////////////
                              
                              
  
                              
                              
                                for(val = 255; val > 0; val --){ //PARA val IGUAL A 255, ENQUANTO val MAIOR QUE 0, DECREMENTA val
                                    analogWrite(pinoRed, val); //PINO RECEBE O VALOR
                                    analogWrite(pinoBlue, 255-val); //PINO RECEBE O VALOR
                                    analogWrite(pinoGreen, 128-val); //PINO RECEBE O VALOR
                                    delay (200); //INTERVALO DE 10 MILISSEGUNDOS
                                    
                                    leds[i] = CRGB(val,128-val,255-val);
                                    if (i > 0){leds[i-1] = CRGB(0);}
                                    FastLED.show();
                                    i = i > 17 ? 0 : i+1;
                              
                                    
                                }
                                for(val = 0; val < 255; val ++){ //PARA val IGUAL A 0, ENQUANTO val MENOR QUE 255, INCREMENTA val
                                    analogWrite(pinoRed, val); //PINO RECEBE O VALOR
                                    analogWrite(pinoBlue, 255-val); //PINO RECEBE O VALOR
                                    analogWrite(pinoGreen, 128-val); //PINO RECEBE O VALOR
                                    delay (500); //INTERVALO DE 10 MILISSEGUNDOS
                                    
                                    leds[i] = CRGB(val,128-val,255-val);
                                    if (i > 0){leds[i-1] = CRGB(0);}
                                    FastLED.show();
                                    i = i > 17 ? 0 : i+1;
                                    }
                            }
                      }



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




 
if(tecla == 'g') { 
      Serial.println("led vermelho");
      cor = verde;
      pino = 9;   
      analogWrite(10, 0); //PINO RECEBE O VALOR  
      analogWrite(11,0); //PINO RECEBE O VALOR
      leds1[0]  = CRGB(0,125,0);
  }

  
if(tecla == 'r')    { 
      Serial.println("led verde");      
      cor = vermelho; 
      pino = 10;
      analogWrite(9, 0); //PINO RECEBE O VALOR     
      analogWrite(11, 0); //PINO RECEBE O VALOR
      leds1[0]  = CRGB(125,0,0);
      
  }
if(tecla == 'b')     { 
      Serial.println("led azul");
      cor = azul;
      pino = 11;
      analogWrite(9, 0); //PINO RECEBE O VALOR
      analogWrite(10, 0); //PINO RECEBE O VALOR  
      leds1[0]  = CRGB(0,0,250);
        
 }

if(tecla == 'q')     { 
    Serial.println("pisca led");
       for (int i = 0; i <= 10; i++){ 
       analogWrite(pino,250); //PINO RECEBE O VALOR
       delay(100);
       analogWrite(pino,0); //PINO RECEBE O VALOR
       delay(100);
       Serial.println("pisca led");
       }     
 }


analogWrite(pino,tem2a); //PINO RECEBE O VALOR

if(tecla == 'w')     { 
  

//sorriso grande
Serial.println("sorriso grande");
    leds[1] =  CRGB(0,0,0);
    leds[2] =  CRGB(0,0,0);
    leds[3] =  CRGB(0,0,0);
    leds[4] =  CRGB(0,0,0);
    leds[5] =  CRGB(0,0,0);
    leds[6] =  CRGB(0,0,0);
    leds[7] =  CRGB(0,0,0);
    leds[8] =  CRGB(0,0,0);
    leds[9] =  CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);
    leds[15] = CRGB(0,0,0);
    leds[0] = CRGB(0,0,0);
  
  leds[0]  =  leds1[0];
  leds[1]  =  leds1[0];
  leds[2]  =  leds1[0];
  leds[11]  = leds1[0];
  leds[12] =  leds1[0];
  leds[13] =  leds1[0];
  leds[14] =  leds1[0];
  leds[15] =  leds1[0];
  FastLED.show();
}



//sorriso pequeno
if(tecla == 'e')     { 
  Serial.println("sorriso pequeno");
    leds[1] =  CRGB(0,0,0);
    leds[2] =  CRGB(0,0,0);
    leds[3] =  CRGB(0,0,0);
    leds[4] =  CRGB(0,0,0);
    leds[5] =  CRGB(0,0,0);
    leds[6] =  CRGB(0,0,0);
    leds[7] =  CRGB(0,0,0);
    leds[8] =  CRGB(0,0,0);
    leds[9] =  CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);
    leds[15] = CRGB(0,0,0);
    leds[0] = CRGB(0,0,0);
      
  leds[0]  =  leds1[0];
  leds[13] =  leds1[0];
  leds[14] =  leds1[0];
  leds[15] =  leds1[0];
  FastLED.show();  
}

if(tecla == 't')     { // sorriso triste
  

// sorriso triste
Serial.println("sorriso triste");
    leds[1] =  CRGB(0,0,0);
    leds[2] =  CRGB(0,0,0);
    leds[3] =  CRGB(0,0,0);
    leds[4] =  CRGB(0,0,0);
    leds[5] =  CRGB(0,0,0);
    leds[6] =  CRGB(0,0,0);
    leds[7] =  CRGB(0,0,0);
    leds[8] =  CRGB(0,0,0);
    leds[9] =  CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);
    leds[15] = CRGB(0,0,0);
    leds[0] = CRGB(0,0,0); 
  
  
  
  leds[3]  =  leds1[0];
  leds[4]  =  leds1[0];
  leds[5]  =  leds1[0];
  leds[6]  =  leds1[0];
  leds[7] =   leds1[0];
  leds[8] =   leds1[0];
  leds[9] =   leds1[0];
  leds[10] =  leds1[0]; 
  FastLED.show();
  }

  //falando
if(tecla == 'y')     { 
  for (int i = 0; i <= 10; i++){
    Serial.println("falando"); 
    leds[1] =  CRGB(0,0,0);
    leds[2] =  CRGB(0,0,0);
    leds[3] =  CRGB(0,0,0);
    leds[4] =  CRGB(0,0,0);
    leds[5] =  CRGB(0,0,0);
    leds[6] =  CRGB(0,0,0);
    leds[7] =  CRGB(0,0,0);
    leds[8] =  CRGB(0,0,0);
    leds[9] =  CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);
    leds[15] = CRGB(0,0,0);
    leds[0] = CRGB(0,0,0);
    delay(200);
    FastLED.show();
        
    leds[0]  =  leds1[0];
    leds[13] =  leds1[0];
    leds[14] =  leds1[0];
    leds[15] =  leds1[0];
    delay(200);
    FastLED.show(); 
     } 
   }

   //////////olhos///////////////////////////////////////////
   /////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////
   
///////////pisca olhos))))))))))))))))))))))
                  if(tecla == 'u')
                 {
                     Serial.println("piscando olhos");
             
                    // m.writeSprite(0, 0,  olhopisca);
                     Pisca();
                     delay(2000);
                     m.clear();
                 } 

/////////////////////////espera////////////////////////////////////////////////////
                 if(tecla == 'i')
                 {
                  for (int t = 0; t <= 2; t++) {
                  Serial.println("leds em esper");
                  m.setIntensity(1);
                  m.writeSprite(0, 0, olhos);
                  delay(700);
                  m.setIntensity(0); 
                  m.writeSprite(0, 0, olhos);  
                  delay(700);  
                        }
                      
                  
                 }
////////////////////////////////////////////////////////////////////////////
                 
                 
                 if(tecla == 'o')
                 {
                  Serial.println("reiniciando arduino ");
                  delay(1000);
                  asm volatile ("  jmp 0");
                                   
                 }

////////////////////////////servo moto////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


 /////////servo vertical    

if(tecla =='a'){

  for ( q1 = q1; q1 < 480;) {
    q1++;  
    delay(10);
    pwm.setPin(h , q1);
    
    //sensor();
    tecla = Serial.read();
    if(tecla == 'd'){break;} 
    double Qa;
    Qa=(q1-120)*0.157;;// tranfosrma em radianos
    Serial.println( " My="+String(Qa));
    
  }

}


if(tecla =='s'){

  for ( q1 = q1; q1 > 120;) {  
    q1--;
    delay(10);
    pwm.setPin(h , q1);
   
    //sensor();
    tecla = Serial.read();
    if(tecla == 'd'){break;} 
    double Qa;
    Qa=(q1-120)*0.157;// tranfosrma em radianos
    Serial.println( " My="+String(Qa));
    
  }                 
                  
}






/////////////////////servo motor horizontal
if(tecla =='f'){

  for ( q3 = q3; q3 < 480;) {
    q3++;
Serial.println(q3);
    delay(10);
    pwm.setPin(v , q3);
   
    //sensor();
    tecla = Serial.read();
    if(tecla == 'd'){break;} 
    double Qb;
    Qb=(q3-120)*0.157;;// tranfosrma em radianos
    //Serial.print( " My="+String(Qa));
    //Serial.println( " Mx="+String(Qb));
    
  }

}


if(tecla =='h'){

  for ( q3 = q3; q3 > 120;) {
    q3++;
Serial.println(q3);  
    delay(10);
    pwm.setPin(v , q3);
   
    //sensor();
    tecla = Serial.read();
    if(tecla == 'd'){break;} 
    double Qb;
    Qb=(q3-120)*0.157;// tranfosrma em radianos
    //Serial.print( " My="+String(Qa));
    //Serial.println( " Mx="+String(Qb));
    
  }                 
                  
}

///////////////////////////////////////////////////////////////////////////////////////////

                 
}
