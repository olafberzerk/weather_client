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
	Serial.println("Entering setup");
	//setup the radio
	radio.begin();
	radio.setChannel(100);

	// Set the PA Level low to prevent power supply related issues since this is a
	// getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
	/*
	   Set Power Amplifier (PA) level to one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
	   The power levels correspond to the following output levels respectively: NRF24L01: -18dBm, -12dBm,-6dBM, and 0dBm
	 */
	Serial.println("Setting power level");
	radio.setPALevel(RF24_PA_MIN);

	Serial.println("Opening write pipe");
	radio.openWritingPipe(addresses[0]);
	//radio.openReadingPipe(1,addresses[1]);
	// just going to write to the server

	Serial.println("Starting to listen");
	radio.startListening();

}

void loop()
{

	// READ DATA

  //const char error[] = "sensor fail";
  //int status = DHT.read22(DHT22_PIN);
  Serial.println("Getting sensor status");
  status = DHT.read22(DHT22_PIN);
  Serial.println("Got sensor status");

  switch (status)
  {
    case DHTLIB_OK:
    {
    	Serial.println("Got temp information");
    	Serial.println(DHT.humidity, 2);
    	Serial.println(DHT.temperature, 2);

    	Serial.println("Stopping listening");
    	radio.stopListening();
    	Serial.println("Converting temp to string");
    	String temperature(DHT.temperature,2);
    	Serial.println("Converting hum to string");
    	String humidity(DHT.humidity,2);
    	Serial.println(humidity);
    	Serial.println(temperature);


    	// Length (with one extra character for the null terminator)
    	int temp_len = temperature.length() + 1;
    	int hum_len = humidity.length() + 1;

    	// Prepare the character array (the buffer)
    	char temp_array[temp_len];
    	char hum_array[hum_len];

    	// Copy it over
    	temperature.toCharArray(temp_array, temp_len);
    	humidity.toCharArray(hum_array, hum_len);

    	Serial.println("Converted to char array");
    	Serial.println(hum_array);
    	Serial.println(temp_array);

    	//few ways to do it differently maybe?
    	//dtostrf();  //one way to convert from double to string
    	//string.getBytes((&buf, sizeof(buf));

        	if (!radio.write(&temp_array, sizeof(temp_array) )){
        	         Serial.println(F("failed to send humidity"));
        	       }
        	if (!radio.write(&hum_array, sizeof(hum_array) )){
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

  Serial.println("Delaying 10s");
  delay(10000);
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
