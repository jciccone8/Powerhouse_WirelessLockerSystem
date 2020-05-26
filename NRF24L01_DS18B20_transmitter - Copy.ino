#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 2

RF24 radio(7, 8);

const byte address[6] = "00001";

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
	radio.begin();
	radio.openWritingPipe(address);
	radio.setPALevel(RF24_PA_MIN);
	radio.stopListening();

  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
	float data = sensors.getTempCByIndex(0);
  
	radio.write(&data, sizeof(data));
 
	delay(1000);
}
