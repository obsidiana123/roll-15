
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <MaxMatrix.h>
#include <HMC5883L_Simple.h>
#include <Arduino.h>

#define SERVO 11 // Porta Digital horizontal
#define SERVO1 12 // Porta Digital vertical

//3 azul
//9 vernelho
//10 verde


int ledPin3 = 3;
int ledPin9 = 9;
int ledPin10 = 10;
float sinVal;
int ledVal;

//sensor de velocidade
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



///////////////////configuração do giroscopio//////////////////////////////////////

//Endereco I2C do MPU6050
const int MPU=0x68;  //pino aberto 0X68 , pino ligado em 3,3V 0x69
 
//Variaveis globais
int acelX,acelY,acelZ,temperatura,giroX,giroY,giroZ;

//parametros da bulsulas

HMC5883L_Simple Compass;
//////////////////////////////////////////////////////////////////////////////////////



char tecla = "ww" ; 
////////////////////////0/////////////////// pinaagem da matriz de leds///////////////////////////
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
              

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////variaveis para medidor decorrentes ///////////////
const int analogIn = A3;
int mVperAmp = 66;
int RawValue = 0;
int ACSoffset = 2500;
double Voltage = 0;
double Amps = 0;
double Amps1 = 0;

int x = 0;
/////////////////////////////////////////////////

int LED = 13;
int pisca =0;
int pisca2 =0;
char entrada;

Servo s; // Variável Servo
Servo s2; // Variável Servo
int q2 = 480;
int q1 = 120;

int q3 = 480;
int q4 = 120;

double Qa;
double Qb;

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

    // senso de velocidade
    pinMode(pino_D0, INPUT);
  //Interrupcao 0 - pino digital 2
  //Aciona o contador a cada pulso
  attachInterrupt(0, contador, FALLING);
  pulsos = 0;
  rpm = 0;
  timeold = 0;



  
  pinMode(pinoSensor, INPUT); //DEFINE O PINO COMO ENTRADA DO SENSOR DE TENSAO
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin9, OUTPUT);
  pinMode(ledPin10, OUTPUT);
  
  ///parametros da bulsola
  Compass.SetDeclination(-0, 23, 'W');
  Compass.SetSamplingMode(COMPASS_SINGLE);
  Compass.SetScale(COMPASS_SCALE_130);
  Compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH);
  ///parametros da bulsola


  
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

///////////////////////// giroscopio//////////////////////////////////////////////////

  Serial.begin(9600);         //inicia a comunicação serial
  Wire.begin();                 //inicia I2C
  Wire.beginTransmission(MPU);  //Inicia transmissão para o endereço do MPU
  Wire.write(0x6B);             
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);


///////////////////////////////////////////////////////////////////////////////////////


  
}


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


//m.writeSprite(0, 0, olhos);// olhos abertos

                  // alinha servos










void sensor() {


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




if(Amps1 > 1.50){
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
 


    double Qa;
    Qa=(q1-120)*0.157;

Serial.println( " servo="+String(pos)+" X="+String(giroX)+" Y="+String(giroY)+" Z="+String(giroZ)+" Norte="+String(heading)+" A="+String(Amps1)+" V="+String(tensaoMedida,2)); 

   
}

void contador()
{
  //Incrementa contador
  pulsos++;
}


void loop() {



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
       Serial.println( " servo="+String(pos));

       } 
     }
      if(pos >= 90){
      for(pos = pos; pos >= 90; pos--)
     {
      delay(40);
      tecla = Serial.read();
      if(tecla == 'p'){break;}
      s.write(pos);
      Serial.println( " servo="+String(pos));
  
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
     Serial.println( " servo="+String(pos));
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
      Serial.println( " servo="+String(pos));
     delay(40);
     tecla = Serial.read();
     if(tecla == 'p'){break;}
     s.write(pos); 

     }
    } 
  
 ///////////////////servo vertical////////////////////////////////////////////////////////



 
/////////////////caba;a para centro vertical////////////////////////////////////////////


    if(tecla == 'w')// tecla w para teste
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

                  while (1){
                      analogWrite(ledPin3, 130);
                      tecla = Serial.read();
                      if(tecla == 'j'){break; }
                    //Atualiza contador a cada segundo
  if (millis() - timeold >= 1000)
  {
    //Desabilita interrupcao durante o calculo
    detachInterrupt(0);
    rpm = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos;
    timeold = millis();
    pulsos = 0;
    //Mostra o valor de RPM no serial monitor
    //Serial.print("RPM = ");
    //Serial.println(rpm, DEC);
    //Habilita interrupcao
    attachInterrupt(0, contador, FALLING);
  }

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





                 Serial.print("para frente");
                 Serial.print(" A=");
                 Serial.print(String(Amps1));
                 Serial.print(" RPM = ");
                 Serial.println(rpm, DEC);
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);
                 pwm.setPin(0 , 4500); 
                 pwm.setPin(2 , 4500);
                 
                 if(Amps1 > 0.8){ 
                 Serial.println("para rodas por corrente excessiva");
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);

                 olhos_fechados();
                 break;
}
}   

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
////////////////////////////servo moto////////////////////////////////////////////////


 /////////servo vertical    

if(test =='1'){

  for ( q1 = q1; q1 < 480;) {
    q1++;
    q2--;
    delay(10);
    pwm.setPin(13 , q1);
    pwm.setPin(12 , q2);
    //sensor();
    tecla = Serial.read();
    if(tecla == '0'){break;} 
    double Qa;
    Qa=(q1-120)*0.157;;// tranfosrma em radianos
    Serial.println( " My="+String(Qa));
    
  }

}


if(test =='2'){

  for ( q1 = q1; q1 > 120;) {
    q2++;
    q1--;
    delay(10);
    pwm.setPin(13 , q1);
    pwm.setPin(12 , q2);
    //sensor();
    tecla = Serial.read();
    if(tecla == '0'){break;} 
    double Qa;
    Qa=(q1-120)*0.157;// tranfosrma em radianos
    Serial.println( " My="+String(Qa));
    
  }                 
                  
}


////////para 30 graus
if(test =='5'){
 if(q1 > 298){
  for ( q1 = q1; q1 > 298;) {
    q2++;
    q1--;
    delay(10);
    pwm.setPin(13 , q1);
    pwm.setPin(12 , q2);
    //sensor();
    tecla = Serial.read();
    if(tecla == '0'){break;} 
    double Qa;
    Qa=(q1-120)*0.157;// tranfosrma em radianos
    Serial.println( " My="+String(Qa));
  }
  }                 



if(q1 < 298){

  for ( q1 = q1; q1 < 298;) {
    q1++;
    q2--;
    delay(10);
    pwm.setPin(13 , q1);
    pwm.setPin(12 , q2);
    //sensor();
    tecla = Serial.read();
    if(tecla == '0'){break;} 
    double Qa;
    Qa=(q1-120)*0.157;;// tranfosrma em radianos
    Serial.println( " My="+String(Qa));
    
  }

}
}


/////////////////////servo motor horizontal
if(test =='3'){

  for ( q3 = q3; q3 < 480;) {
    q3++;
    q4--;
    delay(10);
    pwm.setPin(13 , q3);
    pwm.setPin(12 , q4);
    //sensor();
    tecla = Serial.read();
    if(tecla == '0'){break;} 
    double Qb;
    Qb=(q3-120)*0.157;;// tranfosrma em radianos
    Serial.print( " My="+String(Qa));
    Serial.println( " Mx="+String(Qb));
    
  }

}


if(test =='4'){

  for ( q3 = q3; q3 > 120;) {
    q4++;
    q3--;
    delay(10);
    pwm.setPin(13 , q3);
    pwm.setPin(12 , q4);
    //sensor();
    tecla = Serial.read();
    if(tecla == '0'){break;} 
    double Qb;
    Qb=(q3-120)*0.157;// tranfosrma em radianos
    Serial.print( " My="+String(Qa));
    Serial.println( " Mx="+String(Qb));
    
  }                 
                  
}

///////////////////////////////////////////////////////////////////////////////////////////



                  
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




if(Amps1 > 1.50){
                 Serial.println("para rodas por corrente excessiva");
                 pwm.setPin(0 , 0); 
                 pwm.setPin(1 , 0);
                 pwm.setPin(2 , 0); 
                 pwm.setPin(3 , 0);

                 olhos_fechados();
}

///////////////////////////////////////////////////////////////////



sensor();
delay(100);

////////////////////////////////////////////////////////////////
////////////pisca com tempo//////////////////////////////////
                 

                   
                     pisca = pisca + 1;
    
                     if (pisca <100){digitalWrite(LED_BUILTIN, HIGH); }
                     if (pisca >100){digitalWrite(LED_BUILTIN, LOW); }
                     if (pisca >200){pisca = 1; }
                  
                 
                 


   
                 
                 
/////////////////////////////////////////////////////////////// 


 /////////////////////////led rgb

if(test == '0')
{
  for ( int xx = 10; xx < 131;) { //azul

    xx++;   
    delay(20);
    analogWrite(ledPin3, xx);
    

    
  }


  for ( int xx = 131; xx > 10 ;) { //azul

    xx--;   
    
    analogWrite(ledPin3, xx);
    

    delay(20);
  }
  }



if(test == '9')
{
  while (1){
  analogWrite(ledPin3, 130);
  delay(100);
  analogWrite(ledPin3, 0);
  delay(100);
  tecla = Serial.read();
  if(tecla == '8'){break; }
  
  }}
                 

analogWrite(ledPin3, 10);
 
}
