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
//v imprime a corrente 
//z imprime a tensao
//a centraliza a cabeça
//s servo horizontal para direita
//d servo horzolntal par aesquerda
//f servo vertical baixo
//h servo vertical cima


/*
 * GY-273 Compass Module  ->  Arduino
 * VCC  -> VCC  (See Note Below)
 * GND  -> GND
 * SCL  -> A5/SCL, (Use Pin 21 on the Arduino Mega)
 * SDA  -> A4/SDA, (Use Pin 20 on the Arduino Mega)
 * DRDY -> Not Connected (in this example)
 * 
 */
 
#include <Arduino.h> 
#include <Wire.h>
#include <HMC5883L_Simple.h>
#include <Arduino.h>
#include <MaxMatrix.h> 
#include <Adafruit_PWMServoDriver.h>

//variaveis de sensores
const int analogIn = A3;
int mVperAmp = 66;
int RawValue = 0;
int ACSoffset = 2500;
double Voltage = 0;
double Amps = 0;
double Amps1 = 0;

/////////////encoder/////////////////////////
int pinoSensor1 = 3; //PINO DIGITAL UTILIZADO PELO SENSOR
int pinoSensor2 = 4; //PINO DIGITAL UTILIZADO PELO SENSOR 
int cont =0;

//////////////////////////////////////////////
int pino_D0 = 2;
int rpm;
volatile byte pulsos;
unsigned long timeold;
//Altere o numero abaixo de acordo com o seu disco encoder
unsigned int pulsos_por_volta = 20;

const int pinoSensor = A2; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
float tensaoEntrada = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
float tensaoMedida = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR
 
float valorR1 = 30000.0; //VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
float valorR2 = 7500.0; // VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
int leituraSensor = 0; //VARIÁVEL PARA ARMAZENAR A LEITURA DO PINO ANALÓGICO
int x = 0;
////////////////////////////////


///////////////////configuração do giroscopio//////////////////////////////////////

//Endereco I2C do MPU6050
const int MPU=0x68;  //pino aberto 0X68 , pino ligado em 3,3V 0x69
 
//Variaveis globais
int acelX,acelY,acelZ,temperatura,giroX,giroY,giroZ;


//////////////////////////////////////////////////////////////////////////////////////



///////////variaveis do servo motor 
int x1 = 211;
int y1 = 299;




char controleX = 'a';
char controleY = 'a';

//inicializa bulsula
HMC5883L_Simple Compass;


// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


uint8_t servoX = 5;
uint8_t servoY = 4;

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


///////velocimetro
void contador()
{
  //Incrementa contador
  pulsos++;
}



void setup() {

  Wire.begin();
  ///parametros da bulsola
  Compass.SetDeclination(-0, 23, 'W');
  Compass.SetSamplingMode(COMPASS_SINGLE);
  Compass.SetScale(COMPASS_SCALE_130);
  Compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH);
  ///parametros da bulsola

//velocimetro
   // senso de velocidade
    pinMode(pinoSensor1, INPUT); //DEFINE O PINO COMO ENTRADA
    pinMode(pinoSensor2, INPUT); //DEFINE O PINO COMO ENTRADA
    
     
   pinMode(pino_D0, INPUT);
  //Interrupcao 0 - pino digital 2
  //Aciona o contador a cada pulso
  attachInterrupt(0, contador, FALLING);
  pulsos = 0;
  rpm = 0;
  timeold = 0;
  
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
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

  pinMode(pinoSensor, INPUT); //DEFINE O PINO COMO ENTRADA DO SENSOR DE TENSAO

  ///////////////////////// giroscopio//////////////////////////////////////////////////


  Wire.begin();                 //inicia I2C
  Wire.beginTransmission(MPU);  //Inicia transmissão para o endereço do MPU
  Wire.write(0x6B);             
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);


///////////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop() {



  
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
if( tem < 100){digitalWrite(LED_BUILTIN, HIGH);m.writeSprite(0, 0, olhos);}// liga led por 1 segundo
if( tem > 100){digitalWrite(LED_BUILTIN, LOW);}// DESLIGA LED POR 1 SEGUNDO 
if( tem > 250){ tem =0; } //apaga temporalizador
/////////////////////////////////////////////////////
  

tecla = Serial.read();  

m.writeSprite(0, 0, olhos);

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

//centraliza cabeça
if(controleX =='a'){controleX = 'b'; pwm.setPin(servoX , 211);}
if(controleY =='a'){controleY = 'b'; pwm.setPin(servoY , 299);}
  
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


/////sensores//////////////////////////////////////////////////////////////////////////////////////

// SENSOR DE TENSAO 
if(tecla =='z'){ 
   leituraSensor = analogRead(pinoSensor); //FAZ A LEITURA DO PINO ANALÓGICO E ARMAZENA NA VARIÁVEL O VALOR LIDO
   tensaoEntrada = (leituraSensor * 5.0) / 1024.0; //VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
   tensaoMedida = tensaoEntrada / (valorR2/(valorR1+valorR2)); //VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR
  Serial.println(String(tensaoMedida,2));    
}
//sensor de corrente
if(tecla =='x'){ 
Amps1 = 0;
for ( x = 0; x < 100;) {
   

  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  delay(1);
  
  x++;
  Amps1 = Amps1 + Amps;
 }
Amps1 = ((Amps1/100)*-1);
  Serial.println(String(Amps1,2)); 
if(Amps1 > 1.50){
                 Serial.println("para rodas por corrente excessiva");
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);

                 olhos_fechados();
}
                   
}


////////////motores////////////////////////////////////////////////////////////////////////////

 
                 
////////////para frente//////////////////////////////////////////////////   
 if(tecla =='j'){Serial.println("para frente");
                for (int x = 0; x < 20; ) {
                 
                 
                

                 pwm.setPin(1 , 4500);                   
                 pwm.setPin(2 , 4500);
                 
                 ////////////sensor de velocidadeencoder/////////////////////////////////////////////
                 if (digitalRead(pinoSensor1) == HIGH){ if(cont == 1){ cont =0;Serial.println(x);x++;}}
              
                 if (digitalRead(pinoSensor1) == LOW){ cont =1;}
                 
                 // if (digitalRead(pinoSensor2) == HIGH){ //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
                 // Serial.println("roda esquerda");
                 // }
                  ////////////////////////////////////////////////////////////////////////////// 
                 

                 

                 //para rodas
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
}                                          
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
      
                 pwm.setPin(1 , 4500);                   
                 pwm.setPin(0 , 4500);
                 delay(1000);
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 }                            
 
/////////////////////////////////////////////////////////////////////////////

////////////esquerda//////////////////////////////////////////////////                           
                 if(tecla == 'x')
                 {
                 Serial.println("esquerda");

                 pwm.setPin(2 , 4500);                   
                 pwm.setPin(3 , 4500);
                 delay(1000);
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 
                 }                            
 
/////////////////////////////////////////////////////////////////////////////
                 if(tecla == 'v')
                 {
                  Amps1 = 0;
                  for ( x = 0; x < 100;) {
                     
                  
                    RawValue = analogRead(analogIn);
                    Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
                    Amps = ((Voltage - ACSoffset) / mVperAmp);
                    //delay(1);
                    
                    x++;
                    Amps1 = Amps1 + Amps;
                   }
                  Amps1 = ((Amps1/100)*-1);
                  
                  
                  Serial.print(Amps1);
                  
                  if(Amps1 > 2.50){
                                   Serial.println("para rodas por corrente excessiva");
                                   pwm.setPin(0 , 0); 
                                   pwm.setPin(1 , 0);
                                   pwm.setPin(2 , 0); 
                                   pwm.setPin(3 , 0);
                  
                                   olhos_fechados();
                  }

              }    

               //servo/////////////////////////////////////////////////
                 if(tecla == 'n')
                 {
                  pwm.setPin(servoX ,x1);
                  Serial.print(x1);

                 }
                 
                 if(tecla == 'm')
                 {

                  pwm.setPin(servoY ,y1);
                  Serial.print(y1);
                 }
               //////////////////////////////////////////////////

               
                 
                //bulsula
                if(tecla == '1')
                 {
                   float heading = Compass.GetHeadingDegrees();         
                   Serial.print(String(heading));
                 }

               if(tecla == '2')
                 {
                 
                  Wire.beginTransmission(MPU);      //transmite
                  Wire.write(0x3B);                 // Endereço 0x3B (ACCEL_XOUT_H)
                  Wire.endTransmission(false);     //Finaliza transmissão
                  
                  Wire.requestFrom(MPU,14,true);   //requisita bytes
                   
                  //Armazena o valor dos sensores nas variaveis correspondentes
                  //Armazena o valor dos sensores nas variaveis correspondentes
                  //acelX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
                  //acelY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
                  //acelZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
                  //temperatura=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
                  giroX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
                  giroY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
                  giroZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
                  
                  Serial.println( " Y="+String(giroY)+" Z="+String(giroZ));   
                 }

                 
               if(tecla == '3')
                 {  

                
                  //////////////sensor de corente /////////////////////////////////
                Amps1 = 0;
                for ( x = 0; x < 100;) {
                   
                
                  RawValue = analogRead(analogIn);
                  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
                  Amps = ((Voltage - ACSoffset) / mVperAmp);
                  delay(1);
                  
                  x++;
                  Amps1 = Amps1 + Amps;
                 }
                Amps1 = ((Amps1/100)*-1);
                
                
                
                
                if(Amps1 > 2.50){
                                 Serial.println("para rodas por corrente excessiva");
                                 pwm.setPin(0 , 0); 
                                 pwm.setPin(1 , 0);
                                 pwm.setPin(2 , 0); 
                                 pwm.setPin(3 , 0);
                
                                 olhos_fechados();
                }
                
                  ////////////////sensor bulsola///////////////////////////////////
                float heading = Compass.GetHeadingDegrees();
                   
                  
                ////////////////////giroscopio/////////////////////////////////////////////
                Wire.beginTransmission(MPU);      //transmite
                  Wire.write(0x3B);                 // Endereço 0x3B (ACCEL_XOUT_H)
                  Wire.endTransmission(false);     //Finaliza transmissão
                  
                  Wire.requestFrom(MPU,14,true);   //requisita bytes
                   
                  //Armazena o valor dos sensores nas variaveis correspondentes
                  //Armazena o valor dos sensores nas variaveis correspondentes
                  //acelX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
                  //acelY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
                  //acelZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
                  //temperatura=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
                  giroX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
                  giroY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
                  giroZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
                
                
                 //temperatura = temperatura/340.00+36.53;
                   
                  //Envia valores lidos do acelerômetro
                  //Serial.print(" Acel:"); 
                  //Serial.print(" X=");Serial.print(acelX);
                  //Serial.print(" Y=");Serial.print(acelY);
                  //erial.print(" Z=");Serial.print(acelZ);
                  
                  //Envia valores lidos do giroscópio
                  //Serial.print("\tGiro:");
                  //Serial.print("My="); 
                  //Serial.print( q1 ); 
                  //Serial.print(" X=");Serial.print(giroX);
                  //Serial.print(" Y=");Serial.print(giroY);
                  //Serial.print(" Z=");Serial.print(giroZ);
                   
                
                
                //Envia valor da temperatura em graus Celsius
                //Serial.print(" T=");Serial.print(temperatura);
                
                //Serial.print("\tA=");
                //Serial.print(Amps1); // corrente
                //Serial.print(" Norte=");
                //Serial.println( heading ); //angulo bulsula
                
                   // SENSOR DE TENSAO 
                   leituraSensor = analogRead(pinoSensor); //FAZ A LEITURA DO PINO ANALÓGICO E ARMAZENA NA VARIÁVEL O VALOR LIDO
                   tensaoEntrada = (leituraSensor * 5.0) / 1024.0; //VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
                   tensaoMedida = tensaoEntrada / (valorR2/(valorR1+valorR2)); //VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR
                   
                   //Serial.print("Tensão DC medida: "); //IMPRIME O TEXTO NA SERIAL
                   //Serial.print(tensaoMedida,2); //IMPRIME NA SERIAL O VALOR DE TENSÃO DC MEDIDA E LIMITA O VALOR A 2 CASAS DECIMAIS
                   //Serial.println("V"); //IMPRIME O TEXTO NA SERIAL
                 
                  pwm.setPin(servoX ,x1);
                    
                              
                   pwm.setPin(servoY ,y1);
                      
                
                Serial.println( " servoX="+String(x1)+"servoY="+String(y1)+" X="+String(giroX)+" Y="+String(giroY)+" Z="+String(giroZ)+" Norte="+String(heading)+" A="+String(Amps1)+" V="+String(tensaoMedida,2)); 
                                                  
                 }
}
