#include <Wire.h>
#include <VL53L0X.h>
#include <TCA9548A.h>

TCA9548A mux;
VL53L0X senzor;

int brojSenzora = 2;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  mux.begin(Wire);
  mux.closeAll();

}

void loop() {
  odabirKanala(0);

}

void odabirKanala(int opcija){
  // za opciju: 0 znaci samo citaj parne, 1 samo neparne, 2 sve

  // slucaj samo neparnih
  if(opcija == 1){

    // citanje sa neparnih kanala
    for(int i = 1; i < brojSenzora; i = i + 2){

      mux.openChannel(i);

      //inicijalizacija senzora
      senzor.setTimeout(500);
      if (!senzor.init()){
      Serial.println("Senzor se nije inicijalizovao");
      while (1) {}
      }

      //citanje sa senzora
      Serial.print("Senzor ");
      Serial.print(i);
      Serial.print(":");
      Serial.println(senzor.readRangeSingleMillimeters());
      if(senzor.timeoutOccurred()){
        Serial.println("timeout");
      }
      
      mux.closeChannel(i);
    }

  }

  // slucaj samo parnih
  if(opcija == 0){

    // citanje sa parnih kanala
    for(int i = 0; i < brojSenzora; i = i + 2){

      mux.openChannel(i);

      //inicijalizacija senzora
      senzor.setTimeout(500);
      if (!senzor.init()){
      Serial.println("Senzor se nije inicijalizovao");
      while (1) {}
      }

      //citanje sa senzora
      Serial.print("Senzor ");
      Serial.print(i);
      Serial.print(":");
      Serial.println(senzor.readRangeSingleMillimeters());
      if(senzor.timeoutOccurred()){
        Serial.println("timeout");
      }
      
      mux.closeChannel(i);
    }

  }



}
