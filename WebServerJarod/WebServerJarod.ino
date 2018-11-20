/*
  Web Server
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0F, 0xFB, 0xBC
};
IPAddress ip(192, 168, 137, 237);
int motorPin = A4;
int eTapePin = A5;
int tempPin = 2;
int led = 4;
int blinkPin = 13;
bool demo;
float volume = 0;
float targetVolume = 4;
float initVolume;
float testVolume;

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(blinkPin, OUTPUT);
  pinMode(tempPin,OUTPUT);
  digitalWrite(led,LOW);
  sensors.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  float initVolume = measureVolume();
  float testVolume = initVolume - targetVolume;

  demo = true;
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          //for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            //int sensorReading = analogRead(analogChannel);
            //client.print("analog input ");
            //client.print(analogChannel);
            //client.print(" is ");
            //client.print(sensorReading);
            //client.println("<br />");
          //}

          //int sensorReading = analogRead(tempPin);
          sensors.requestTemperatures();
          double temperatureValue = sensors.getTempCByIndex(0);
          double temperatureValueFahr = (sensors.getTempCByIndex(0) * 1.8) + 32;
          //double temperatureValue = analogRead(tempPin);
          //double temperatureValueFahr = (analogRead(tempPin) * 1.8) + 32;
          client.println("<head>");
          
          client.println("<title>Cloud Keg Stats</title>");
          //client.println("<link rel=\"stylesheet\" href=\"cloud_styles.css\">");
          client.println("<style>");
          
          client.println("h1, h3 {");
          client.println("font-family: Goudy Old Style,Garamond,Big Caslon,Times New Roman,serif;");
          client.println("}");
          
          client.println("h1 {"); 
          client.println("text-shadow: 2px 2px 2px #3d3d3d;");
          client.println("text-align: center;");
          client.println("}");

          client.println("h3 {");
          client.println("text-align: center;");
          client.println("}");

          client.println("body {");
          client.println("background-image: url(\"clouds.jpg\");");
          client.println("background-repeat: no-repeat;");
          client.println("background-size: 100%");
          client.println("}");

          client.println(".value {");
          client.println("color: black;");
          client.println("}");

          client.println(".value2 {");
          client.println("color: black;");
          client.println("}");

          client.println(".value3 {");
          client.println("color: black;");
          client.println("}");
          
          client.println("</style>");
          client.println("</head>");
          client.println("<h1>COULD SMART KEG - JAROD MOORE AND COLBY MCGUINN</h1>");
          
          client.println("<br>");
          
          client.print("<h2>Current Temperature reads: <b class=\"value\">");
          client.print(temperatureValue);
          client.println("</b> degrees Celsius</h2>");
          
          client.println("<br>");
          
          client.print("<h2>Current Temperature reads: <b class=\"value\">");
          client.print(temperatureValueFahr);
          client.println("</b> degrees Fahrenheit</h2>");
          
          client.println("<br>");
          
          client.println("<h2>Current volume of liquid: <b class=\"value3\">");
          volume = measureVolume();
          client.print(volume);
          client.println(" mL</b></h2>");
                    if (demo) {
            digitalWrite(motorPin, HIGH);
            delay(120000);
            digitalWrite(motorPin, LOW);
            demo = false;
          }
          //delay(400);                       // wait for this much time before printing next value
          client.println("</html>");
          break;

        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
  
  if (measureVolume() > (testVolume)) {
    //digitalWrite(motorPin, HIGH);
  }

  if (measureVolume() <= (testVolume)) {
    //digitalWrite(motorPin, LOW);
  }
  
  if (analogRead(A1) == 0) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}

float measureVolume() {
  float sensorValue1 = 0;
  float sensorValue2 = 0;
  float sensorValue3 = 0;
  float sensorValue4 = 0;
  float sensorValue5 = 0;
  float voltage = 0;
  float height = 0;
  float kiloOhms = 0;
  
  sensorValue1 = analogRead(eTapePin);
  sensorValue2 = analogRead(eTapePin);
  sensorValue3 = analogRead(eTapePin);
  sensorValue4 = analogRead(eTapePin);
  sensorValue5 = analogRead(eTapePin);
  voltage = (sensorValue1 + sensorValue2 + sensorValue3 + sensorValue4 + sensorValue5) / 5;
  
  kiloOhms = voltage / 1000;

  height = (kiloOhms - 2.2) / (-0.14);

  return((3.14 * (1.75 * 1.75) * height) * 16.387) - 500;
}
