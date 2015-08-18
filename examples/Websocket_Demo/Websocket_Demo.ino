#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "<your ssid>";
const char* password = "<your password>";

WiFiServer server(80);

// Enabe debug tracing to Serial port.
#define DEBUGGING true

// Here we define a maximum framelength to 64 bytes. Default is 256.
#define MAX_FRAME_LENGTH 256

// Define how many callback functions you have. Default is 1.
#define CALLBACK_FUNCTIONS 1

#include <WebSocketServer2866.h>

WebSocketServer webSocketServer;


// Called when a new message from the WebSocket is received
// Looks for a message in this form:
//
// DPV
//
// Where: 
//        D is either 'd' or 'a' - digital or analog
//        P is a pin #
//        V is the value to apply to the pin
//

void handleClientData(String &dataString) {
  //bool isDigital = dataString[0] == 'd';
  //int pin = dataString[1] - '0';
  //int value;

  //value = dataString[2] - '0';

    
  //pinMode(pin, OUTPUT);
   
  //if (isDigital) {
    //digitalWrite(pin, value);
  //} else {
    //analogWrite(pin, value);
  //}
    
  Serial.println(dataString);
}

// send the client the analog value of a pin
void sendClientData(int pin) {
  String data = "a";
  
  //pinMode(pin, INPUT);
  data += String(pin);
  webSocketServer.sendData(data);  
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  //if (mdns.begin("esp8266", WiFi.localIP())) {
    //Serial.println("MDNS responder started");
  //}

  // Start TCP (HTTP) server
  server.begin();
  Serial.println("TCP server started");
  
  // Add service to MDNS-SD
  //MDNS.addService("http", "tcp", 80);
  
}

void loop() {
  String data;
  WiFiClient client = server.available();

  if (!client) {
    return;
  }
  Serial.println("");
  Serial.println("New client");
  
  if (client.connected() && webSocketServer.handshake(client)) {
    Serial.println("connected, handshake");
    
    while (client.connected()) {
      data = webSocketServer.getData();

      if (data.length() > 0) {
        handleClientData(data);
      }

      sendClientData(1);
      sendClientData(2);
      sendClientData(3);
    }
  }
  
  // wait to fully let the client disconnect
  delay(100);
}
