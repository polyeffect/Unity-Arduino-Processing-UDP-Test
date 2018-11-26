#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

int inputPin = D6;
int val = 0;

// wi-fi connection variables
const char* ssid = "polyeffect";
const char* password = "12420165hh";
boolean wifiConnected = false;
String macAdr;

// UDP variables
unsigned int localPort = 8888;
unsigned int UDPPort = 6000;
IPAddress UDPRemote(192,168,0,255);
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
char ReplyBuffer[] = "acknowledged";
String command = "";

boolean pressState = false;

void setup() {
  Serial.begin(115200);
  wifiConnected = connectWifi();

  if (wifiConnected) {
    udpConnected = connectUDP();
    if (udpConnected) {
      // PIN setup
      pinMode(BUILTIN_LED, OUTPUT);
      pinMode(inputPin, INPUT);
    }
  }
}

void loop() {
  if (wifiConnected) {
    if (udpConnected) {
      int packetSize = UDP.parsePacket();
      if (packetSize) {
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remote = UDP.remoteIP();
        for (int i = 0; i < 4; i++) {
          Serial.print(remote[i], DEC);
          if (i < 3) {
            Serial.print(".");
          }
        }
        Serial.print(", port ");
        Serial.println(UDP.remotePort());

        // read the packet into packetBufffer
        UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        Serial.println("Contents:");
        Serial.println(packetBuffer);

        // send a reply to the IP address and port that sent us the packet we received
        UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
        UDP.write(ReplyBuffer);
        UDP.endPacket();
      }
      val = digitalRead(inputPin);
      digitalWrite(BUILTIN_LED, val);
      if(val == 0 && !pressState) {
        UDP.beginPacket(UDPRemote, UDPPort);
        UDP.write(ReplyBuffer);
        UDP.endPacket();
        pressState = true;
      } else if (val == 1 && pressState) {
        pressState = false;
      }
    }
  }
  delay(10);
}


/*
   connect to wifi and UDP
*/

// connect to UDP - return true if successful or false if not
boolean connectUDP() {
  boolean state = false;

  Serial.print("");
  Serial.println("Connecting to UDP...");

  if (UDP.begin(localPort) == 1) {
    Serial.println("UDP Connection successful.");
    state = true;
  } else {
    Serial.println("UDP Connection failed.");
  }
  return state;
}

// connect to wifi - return true if successful or false if not
boolean connectWifi() {
  boolean state = true;
  int i = 0;
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi...");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10) {
      state = false;
      break;
    }
    i++;
  }

  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.printf("Chip ID = %08X\n", ESP.getChipId());
    Serial.print("MAC address: ");
    macAdr = WiFi.macAddress();
    Serial.println(macAdr);
  } else {
    Serial.println("");
    Serial.println("WiFi Connection failed.");
  }
  return state;
}

