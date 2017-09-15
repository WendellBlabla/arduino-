#include<Ultrasonic.h>
#include<Stepper.h>

Stepper motorDireito(4096, 48, 44, 46, 42);
Stepper motorEsquerdo(4096, 34, 38, 36, 40);

const int sensorEsquerdo = 31;
const int sensorMeio = 33;
const int sensorDireito = 35;
int sensorDeLinha;

int mapaDaPista[3][3]={{-1,-1,-1},
                       {-1,-1,-1},
                       {-1,-1,-1}};

// ultrasonico de baixo
#define TRIGGER_PIN 28 
#define ECHO_PIN 5
//sensor da Direita
#define TRIGGER_PIN3 51 
#define ECHO_PIN3 4
//sensor da Esquerda
#define TRIGGER_PIN4 50
#define ECHO_PIN4 3

Ultrasonic ultrasonicBaixo(TRIGGER_PIN,ECHO_PIN);
Ultrasonic ultrasonicDireito(TRIGGER_PIN3,ECHO_PIN3); 
Ultrasonic ultrasonicEsquerdo(TRIGGER_PIN4,ECHO_PIN4); 

int sensorUltraB,sensorUltraD,sensorUltraE;

void setup() {
  motorDireito.setSpeed(7); 
  motorEsquerdo.setSpeed(7);

  pinMode(sensorDireito,INPUT);
  pinMode(sensorMeio,INPUT);
  pinMode(sensorEsquerdo,INPUT);
  
  Serial.begin(9600);
}

void loop() {
  estadoInicial();
  estadoDeAcao();
}
void estadoDeAcao(){
  atualizarMapa();
  int esquerdo = mapaDaPista[0][0];
  int meio = mapaDaPista[0][1];
  int direito = mapaDaPista[0][2];
  if(esquerdo == 0 && meio == 1 && direito == 0){
    /*leituraDoOjetoB();
    if(sensorUltraB == 10) objeto();*/
    frente();}
  if(esquerdo == 1 && meio == 1 && direito == 1) frente();
  if(esquerdo == 1 && meio == 0 && direito == 1) frente();
  if(esquerdo == 0 && meio == 0 && direito == 0){ 
    frente();
    //gap();
    //birfucacao();
     }
  if(esquerdo == 1 && meio == 0 && direito == 0){
    esquerda();
    }
  if(esquerdo == 0 && meio == 0 && direito == 1){
    direita();
    }  
  if(esquerdo == 1 && meio == 1 && direito == 0){
    delay(1000);
    birfucacao();
    //esquerda();
    }
  if(esquerdo == 0 && meio == 1 && direito == 1){
    delay(1000);
    birfucacao();
    //direita();
    }
  }
void estadoInicial(){
  atualizarMapa();
  if(mapaDaPista[2][0] == -1 && mapaDaPista[2][1] == -1 && mapaDaPista[2][2] == -1){
    for(int x = 1; x < 50; x++){
      frente();}
  }
}
void atualizarMapa(){
  for(int j = 2; j > 0; j--){
    for(int i = 0; i < 3; i++){
      mapaDaPista[j][i]=mapaDaPista[j-1][i];
    }
  }
   mapaDaPista[0][2]= digitalRead(sensorDireito);
   mapaDaPista[0][1]= digitalRead(sensorMeio);
   mapaDaPista[0][0]= digitalRead(sensorEsquerdo);
  }
void birfucacao(){
    atualizarMapa();
    for(int x = 1; x < 250; x++) frente();
    atualizarMapa();
    delay(1000);
    for(int k = 1; k < 250; k++) frente();
    atualizarMapa();
    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 0 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 1 && mapaDaPista[1][1] == 1 && mapaDaPista[1][2] == 1 && mapaDaPista[2][0] == 0 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 1){
     for(int x = 1; x <= 1050; x++) direita();
     atualizarMapa();
     if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 1)
     for(int x = 1; x < 250; x++) frente();
      /*B-D-Q
      0,1,0
      0,1,1
      0,1,1
      */
    }
    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 0 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 1 && mapaDaPista[1][1] == 1 && mapaDaPista[1][2] == 1 && mapaDaPista[2][0] == 1 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 0){
     for(int x = 1; x <= 1050; x++) esquerda();
     atualizarMapa();
     if(mapaDaPista[0][0] == 1 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 0)
     for(int x = 1; x < 250; x++) frente();
     /*B-E-Q
      0,1,1
      0,1,1
      0,1,0
      */
      }
    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 1 && mapaDaPista[1][1] == 1 && mapaDaPista[1][2] == 1 && mapaDaPista[2][0] == 1 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 0){
    for(int x = 1; x < 250; x++) frente();
    for(int x = 1; x <= 1050; x++) esquerda(); 
    delay(1000);
    for(int x = 1; x < 300; x++) frente();
    /*B-E-R
      0,1,1
      1,1,1
      0,1,0
      */
     }
    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 1 && mapaDaPista[1][1] == 1 && mapaDaPista[1][2] == 1 && mapaDaPista[2][0] == 0 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 1){
    for(int x = 1; x < 250; x++) frente();
    for(int x = 1; x <= 1050; x++) direita();
    delay(1000); 
    for(int x = 1; x < 300; x++) frente();
    /*B-D-R
      0,1,0
      1,1,1
      0,1,1
      */
     }    
    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 1 && mapaDaPista[1][1] == 1 && mapaDaPista[1][2] == 0 && mapaDaPista[2][0] == 1 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 0){
    for(int x = 1; x < 250; x++) frente();
    for(int x = 1; x <= 1050; x++) esquerda(); 
    delay(1000);
    for(int x = 1; x < 300; x++) frente();
    /*B-E
      0,1,1
      1,1,1
      0,0,0
      */
     }
     if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 0 && mapaDaPista[1][1] == 1 && mapaDaPista[1][2] == 1 && mapaDaPista[2][0] == 0 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 1){
     for(int x = 1; x < 250; x++) frente();
     for(int x = 1; x <= 1050; x++) direita();
     delay(1000);
     for(int x = 1; x < 300; x++) frente();
     /*B-D
      0,0,0
      1,1,1
      0,1,1
      */
     }

    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 0 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 1 && mapaDaPista[1][1] == 1 && mapaDaPista[1][2] == 0 && mapaDaPista[2][0] == 1 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 0){
     for(int x = 1; x < 250; x++) frente();
     for(int x = 1; x <= 1050; x++) esquerda();
     atualizarMapa();
     if(mapaDaPista[0][0] == 1 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 0)
     for(int x = 1; x < 250; x++) frente();
     /*B-E-B
      0,1,1
      0,1,1
      0,0,0
      */
     }
    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 0 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 0 && mapaDaPista[1][1] == 1 && mapaDaPista[1][2] == 1 && mapaDaPista[2][0] == 0 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 1){
     for(int x = 1; x < 250; x++) frente();
     for(int x = 1; x <= 1050; x++) direita();
     atualizarMapa();
     if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 1)
     for(int x = 1; x < 250; x++) frente();
     /*B-D-B
      0,0,0
      0,1,1
      0,1,1
      */
     }
    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 0 && mapaDaPista[1][1] == 1 && mapaDaPista[1][2] == 0 && mapaDaPista[2][0] == 0 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 1){
     frente();
     /*PEG-D   
      0,0,0
      1,1,1
      0,0,1
      */
    }
    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 0 && mapaDaPista[1][1] == 1 && mapaDaPista[1][2] == 0 && mapaDaPista[2][0] == 1 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 0){
     frente();
     /* PEG-E
      0,0,1
      1,1,1
      0,0,0
      */
    }
    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 0 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 0 && mapaDaPista[1][1] == 0 && mapaDaPista[1][2] == 0 && mapaDaPista[2][0] == 1 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 0){
     for(int x = 0; x <= 100; x++)paraTras();
     for(int x = 1; x <= 1050; x++) esquerda();
     atualizarMapa();
     if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 0)
     for(int x = 1; x < 250; x++) frente();
     /* 90º E
      0,0,1
      0,0,1
      0,0,0
      */
    }
    if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 0 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 0 && mapaDaPista[1][1] == 0 && mapaDaPista[1][2] == 0 && mapaDaPista[2][0] == 0 && mapaDaPista[2][1] == 1 && mapaDaPista[2][2] == 1){
     for(int x = 0; x <= 100; x++)paraTras();
     for(int x = 1; x <= 1050; x++) direita();
     atualizarMapa();
     if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 1 && mapaDaPista[0][2] == 0)
     for(int x = 1; x < 250; x++) frente();
     /* 90º D
      0,0,0
      0,0,1
      0,0,1
      */
    }
}
void leituraDoOjetoB(){
  long tempoSensorBaixo = ultrasonicBaixo.timing();
  sensorUltraB = ultrasonicBaixo.convert(tempoSensorBaixo, Ultrasonic::CM);
  }
void leituraDoOjetoD(){
  long tempoSensorDireito = ultrasonicDireito.timing();
  sensorUltraD = ultrasonicDireito.convert(tempoSensorDireito, Ultrasonic::CM);
  }
void leituraDoOjetoE(){
  long tempoSensorEsquerdo = ultrasonicEsquerdo.timing();
  sensorUltraE = ultrasonicEsquerdo.convert(tempoSensorEsquerdo, Ultrasonic::CM);
  }
 /*void objeto(){
   for(int i = 0; i < 1050; i++) esquerda();
   for(int i = 0; i < 1600; i++) frente();
   for(int i = 0; i < 1050; i++) direita();
   for(int i = 0; i < 3000; i++) frente();
   for(int i = 0; i < 1050; i++) direita();
   for(int i = 0; i < 1600; i++) frente();
   for(int i = 0; i < 1050; i++) esquerda(); 
    }
  */
/*
void objeto(){
  delay(1000);
  for(int i = 0; i <= 1050; i++)esquerda();
  leituraDoObjetoD();
  while(sensorUltraD <= 10){
    frente();
    leituraDoObjetoD();  
    }
  for(int i = 0; i < 600; i++) frente();
  for(int i = 0; i < 1050; i++) direita();
  while(sensorUltraE > 10){
    frente();
    leituraDoObjetoE();
    }
  while()
  }
  */
void gap(){
  delay(1000);
  atualizarMapa();
  for(int x = 1; x < 940; x++)frente();
  atualizarMapa();
  if(mapaDaPista[0][0] == 0 && mapaDaPista[0][1] == 0 && mapaDaPista[0][2] == 0 && mapaDaPista[1][0] == 0 && mapaDaPista[1][1] == 0 && mapaDaPista[1][2] == 0 && mapaDaPista[2][0] == 0 && mapaDaPista[2][1] == 0 && mapaDaPista[2][2] == 0){
  for(int x = 1; x < 940; x++)paraTras(); 
  for(int x = 1; x < 300; x++)direita();
  for(int x = 1; x < 170; x++)frente();
  atualizarMapa();
  if(mapaDaPista[0][0] != 0 && mapaDaPista[0][1] != 0 && mapaDaPista[0][2] != 0) frente();
  else{
  for(int x = 1; x < 300; x++)esquerda();
  for(int x = 1; x < 170; x++)frente();}
    }
  }
void frente(){
  motorEsquerdo.step(1);
  motorDireito.step(1);
  }
void esquerda(){
  motorEsquerdo.step(-1);
  motorDireito.step(1);
  }
void direita(){
  motorEsquerdo.step(1);
  motorDireito.step(-1);
  }
void paraTras(){
  motorEsquerdo.step(-1);
  motorDireito.step(-1);
  }

