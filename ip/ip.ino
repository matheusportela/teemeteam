#include <Ethernet.h>
#include <EthernetUdp.h>

#define MESSAGE_MAX_SIZE 1024

unsigned int udpPort = 8888;
EthernetUDP udp;

void receiveMessage(char* dest, int maxSize) {
  int packetSize = 0;
  IPAddress remote;
  
  // Clear message buffer
  memset(dest, 0, maxSize);

  // Check whether received a message
  while (!packetSize)
    packetSize = udp.parsePacket();
  
  // Read message
  udp.read(dest, maxSize);
  
  // Output message to serial
  Serial.print("Received packet of size ");
  Serial.println(packetSize);
  Serial.print("From ");
  Serial.print(udp.remoteIP());
  Serial.print(":");
  Serial.println(udp.remotePort());
  Serial.print("Contents: ");
  Serial.println(dest);
}

void sendMessage(IPAddress ip, char* msg) {
  udp.beginPacket(ip, udpPort);
  udp.print(msg);
  udp.endPacket();
  
  Serial.println("Sent message");
  Serial.print("To: ");
  Serial.println(ip);
  Serial.print("Contents: ");
  Serial.println(msg);
}

void setup() {
  system("ifconfig eth0 192.168.0.200 netmask 255.255.255.0 up");
  udp.begin(udpPort);
  Serial.begin(9600);
  Serial.println(Ethernet.localIP());
}

void loop() {
  IPAddress remoteIp(192, 168, 0, 12);
  char message[MESSAGE_MAX_SIZE];
  
  receiveMessage(message, MESSAGE_MAX_SIZE);
  sendMessage(remoteIp, message);

  delay(1000);
}
