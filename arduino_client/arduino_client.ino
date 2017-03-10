#include <DHT.h>

#include <Ethernet2.h>


#include <SPI.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x77, 0x08 }; // RESERVED MAC ADDRESS
//char server[] = "www.google.com"; 
IPAddress ip(192, 168, 0, 177);
IPAddress server(192, 168, 0, 5);
EthernetClient client;

#define DHTPIN 2 // SENSOR PIN
#define DHTTYPE DHT11 // SENSOR TYPE - THE ADAFRUIT LIBRARY OFFERS SUPPORT FOR MORE MODELS
DHT dht(DHTPIN, DHTTYPE);

int t = 0;  // TEMPERATURE VAR
int h = 0;  // HUMIDITY VAR

String data;

int readingInterval = 5000; // in minutes

void setup() { 
  Serial.begin(115200);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP"); 
  }

  dht.begin(); 
  delay(10000); // GIVE THE SENSOR SOME TIME TO START

  h = (int) dht.readHumidity(); 
  t = (int) dht.readTemperature(); 

  data = "";
}

void loop(){
  
  h = (int) dht.readHumidity();
  t = (int) dht.readTemperature();

  data = "temp1=" + String(t) + "&hum1=" + String(h);

  if (client.connect(server,80)) { // REPLACE WITH YOUR SERVER ADDRESS
    client.println("POST /meteo/includes/add.php HTTP/1.1"); 
    client.println("Host: 192.168.0.5"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
    Serial.print(data);
    Serial.print(server);
  } 

  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }

  delay(readingInterval); // WAIT FIVE MINUTES BEFORE SENDING AGAIN
}


