/* requires
 * DHTlib
 * RF24-master
 * SPI
 * Wire
*/

#include <SPI.h> //radio
#include <RF24.h> //radio

#include <dht.h> //sensor

#define DHT22_PIN 2 // pin that the sensor is on for uno.  Digital pin 4 on atmega

dht DHT;
RF24 radio(7,8);

byte addresses[][6] = {"1Node","2Node"};
// 1Node = pipe going to server
// 2Node = local pipe

int status;
const char error[] = "sensor fail";

void setup()
{
	delay(2000);
	Serial.begin(115200);
	Serial.println("Entering setup\n\n");
	//setup the radio
	radio.begin();
	radio.setChannel(100);

	// Set the PA Level low to prevent power supply related issues since this is a
	// getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
	/*
	   Set Power Amplifier (PA) level to one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
	   The power levels correspond to the following output levels respectively: NRF24L01: -18dBm, -12dBm,-6dBM, and 0dBm
	 */
	Serial.println("Setting power level\n\n");
	radio.setPALevel(RF24_PA_MIN);

	Serial.println("Opening write pipe\n\n");
	radio.openWritingPipe(addresses[0]);
	//radio.openReadingPipe(1,addresses[1]);
	// just going to write to the server

	Serial.println("Starting to listen\n\n");
	radio.startListening();

}

void loop()
{
  // READ DATA

  //const char error[] = "sensor fail";
  //int status = DHT.read22(DHT22_PIN);
  Serial.println("Getting sensor status\n\n");
  status = DHT.read22(DHT22_PIN);
  Serial.println("Got sensor status\n\n");

  switch (status)
  {
    case DHTLIB_OK:
    {
    	Serial.println("Got temp information\n\n");
    	Serial.println(DHT.humidity, 2);
    	Serial.println(DHT.temperature, 2);

    	Serial.println("Stopping listening\n\n");
    	radio.stopListening();
        	if (!radio.write(&DHT.humidity, sizeof(double) )){
        	         Serial.println(F("failed to send humidity"));
        	       }
        	if (!radio.write(&DHT.temperature, sizeof(double) )){
        	           Serial.println(F("failed to send temperature"));
        	         }
    }
    break;
    case DHTLIB_ERROR_CHECKSUM:
    {
    	radio.stopListening();
    	        if (!radio.write(&error, sizeof(error) )){
    	        	        Serial.println(F("sensor fail"));
    	        }
    }
    break;
    case DHTLIB_ERROR_TIMEOUT:
    {
    	radio.stopListening();
    	        if (!radio.write(&error, sizeof(error) )){
    	        	         Serial.println(F("sensor fail"));
    	        }
    }
    break;
    default:
    {
    	radio.stopListening();
    	        if (!radio.write(&error, sizeof(error) )){
    	        	         Serial.println(F("sensor fail"));
    	        }
    }
    break;
  }

  Serial.println("Delaying 3s\n\n");
  delay(3000);
  Serial.println("End of loop and start listening\n\n");

  //radio.startListening();
  //needed?

  //power management routine
  /*
  radio.powerDown();
  delay(20000);
  radio.powerUp();
  */
}
