#include "UbidotsMicroESP8266.h"
#include "DHT.h"
#define TOKEN  "A1E-kr8WgZeSvBcJ4mp3VaSWzgk4wNTI4j"  // Put here your Ubidots TOKEN
//#define ID_1 "Your_variable_ID_here"
//#define ID_2 "Your_variable_ID_here"
#define WIFISSID "Adesh"
#define PASSWORD "*********"

Ubidots client(TOKEN);

#define DHTPIN D7 // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11
float hum;
float temp;
 
DHT dht(DHTPIN, DHTTYPE);

void setup(){
    Serial.begin(9600);
    delay(10);
    dht.begin();
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop()
{

  for (int i=0;i<50;i++)
  {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
        hum += dht.readHumidity();
  // Read temperature as Celsius (the default)
        temp += dht.readTemperature();
        delay(10);
 // Check if any reads failed and exit early (to try again).
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  }
   hum = hum/50;
   temp = temp/50;
    {
    client.add("LAB TEMPERATURE",temp);
    client.add("LAB HUMIDITY",hum);
    client.sendAll(true);
    delay(10000);
    }
}

