#include <Arduino.h>
#include <Stepper.h>

byte dpE = 41;
byte dpD = 43;
byte dpC = 45;
byte dpB = 47;
byte dpA = 49;
byte dpF = 51;
byte dpG = 53;

byte pb1 = 39;
byte pb2 = 37;
byte pb3 = 35;

byte led1 = 48;
byte led2 = 50;
byte led3 = 52;

int andarAtual = 1;
int andarAnterior = 1;
int valButton = 0;

Stepper motor(32, 8,9,10,11);

int dist_andar = 4950;
int velocidade = 900;

void setup() {
  pinMode(dpA, OUTPUT);
  pinMode(dpB, OUTPUT);
  pinMode(dpC, OUTPUT);
  pinMode(dpD, OUTPUT);
  pinMode(dpE, OUTPUT);
  pinMode(dpF, OUTPUT);
  pinMode(dpG, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(pb1, INPUT);
  pinMode(pb2, INPUT);
  pinMode(pb3, INPUT);
}

void changeDisplay(byte E, byte D, byte C, byte B, byte A, byte F, byte G){
    digitalWrite(dpA, A);
    digitalWrite(dpB, B);
    digitalWrite(dpC, C);
    digitalWrite(dpD, D);
    digitalWrite(dpE, E);
    digitalWrite(dpF, F);
    digitalWrite(dpG, G);
}

void updateDisplay(int andar){
  if(andar == 1){
    changeDisplay(LOW,LOW,HIGH,HIGH,LOW,LOW,LOW);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }else if(andar == 2){
    changeDisplay(HIGH,HIGH,LOW,HIGH,HIGH,LOW,HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }else{
    changeDisplay(LOW,HIGH,HIGH,HIGH,HIGH,LOW,HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  }
}

int move(int andar, int destino){
  if(destino > andar){
    motor.step(dist_andar);
    andar++;
  }else{
    motor.step(dist_andar * -1);
    andar--;
  }
  return andar;
}

void loop() {
  motor.setSpeed(900);
  updateDisplay(andarAtual);
  valButton = digitalRead(pb1);
  if((valButton == HIGH) && (andarAtual != 1)){
    do{
      andarAtual = move(andarAtual, 1);
      updateDisplay(andarAtual);
    }while(andarAtual != 1);
    valButton = LOW;
  }
  valButton = digitalRead(pb2);
  if((valButton == HIGH) && (andarAtual != 2)){
    do{
      andarAtual = move(andarAtual, 2);
      updateDisplay(andarAtual);
    }while(andarAtual != 2);
    valButton = LOW;
  }
  valButton = digitalRead(pb3);
  if((valButton == HIGH) && (andarAtual != 3)){
    do{
      andarAtual = move(andarAtual, 3);
      updateDisplay(andarAtual);
    }while(andarAtual != 3);
  valButton = LOW;
  }
}