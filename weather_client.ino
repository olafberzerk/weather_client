#include <SPI.h>
#include "RF24.h"

#include <dht.h>
#include <Wire.h>
#include "convert.h"

#define DHT22_PIN 2 // pin that the sensor is on for uno.  Digital pin 4 on atmega

dht DHT;
RF24 nrf(7,8);

byte addresses[][6] = {"1Node","2Node"};

void setup()
{

	nrf.begin();
	// Set the PA Level low to prevent power supply related issues since this is a
	// getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
	nrf.setPALevel(RF24_PA_LOW);

	nrf.openWritingPipe(addresses[1]);
	nrf.openReadingPipe(1,addresses[0]);

	nrf.startListening();


}

void loop()
{
  // READ DATA

  int status = DHT.read22(DHT22_PIN);
  switch (status)
  {
    case DHTLIB_OK:
    	{
    		nrf.stopListening();
        	if (!nrf.write( &DHT.humidity, sizeof(double) )){
        	         Serial.println(F("failed to send humidity"));
        	       }
        	if (!nrf.write( &DHT.temperature, sizeof(double) )){
        	           Serial.println(F("failed to send temp"));
        	         }
    	}
    break;
    case DHTLIB_ERROR_CHECKSUM:
    {

    }
    break;
    case DHTLIB_ERROR_TIMEOUT:
    {

    }
    break;
    default:
    {

    }
    break;
  }

  nrf.startListening();
  delay(2000);
}
