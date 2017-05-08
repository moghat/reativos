#include "xtea.c.h"

#define LED 13

unsigned long all=0;
int i=0,j,w=1,x=0;
int sizeV = 1;
unsigned int ROUNDS =32;
unsigned long t1=0,time1;
int led = 0;
void setup () {
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
    
}
 
uint32_t key[] = { 1, 2, 3, 4 };
uint32_t v[]   = { 10, 20 };

void loop () {
  if(time1+50<=millis()){
      led=!led;
      time1=millis();
      digitalWrite(LED, led);
    }

    
/*
    Serial.print("antes: ");
        Serial.print(v[0]);
        Serial.print(" ");
        Serial.println(v[1]);
*/
    if(w==1)
      encipher(ROUNDS, v, key);
    else
      decipher(ROUNDS, v, key);
    /*
    Serial.print("durante: ");
        Serial.print(v[0]);
        Serial.print(" ");
        Serial.println(v[1]);
*/
/*
    Serial.print("depois: ");
        Serial.print(v[0]);
        Serial.print(" ");
        Serial.println(v[1]);
*/
    if(++x==sizeV){
      if(w==0){//estava decipher
        i++;
        all += millis()-t1;
        t1 = millis();
      }
      w=!w;
      x=0;
    }
    if(i==10){
      Serial.print(all/10.0);
      Serial.print(" ");
      Serial.println(sizeV);
      i=0;
      all=0;
      sizeV*=2;
    }
    if(sizeV<=0){
      Serial.println("Overflow");
      while(1);
    }
}