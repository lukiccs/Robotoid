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

  //kreiram taskove
  xTaskCreatePinnedToCore(neparniKanali, "neparni", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(parniKanali, "parni", 2048, NULL, 1, NULL, 1);

}

void loop() {
  

}


void neparniKanali(void *pvParameters){

  while(1){

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
  vTaskDelay(1);
}


void parniKanali(void *pvParameters){

  while(1){

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

  vTaskDelay(1);
  }
}






