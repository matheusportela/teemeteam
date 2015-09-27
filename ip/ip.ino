#include <Ethernet.h>
#include <EthernetUdp.h>

EthernetUDP udp;
unsigned int udpPort = 8888;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

void setup() {
  system("ifconfig eth0 192.168.0.200 netmask 255.255.255.0 up");
  udp.begin(udpPort);
  
  Serial.begin(9600);
  Serial.println(Ethernet.localIP());
}

void loop() {
  int packetSize;
  IPAddress remote;
  
  packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.println("Received packet");
    Serial.print("Size: ");
    Serial.println(packetSize);
    Serial.print("From: ");
    Serial.print(udp.remoteIP());
    Serial.print(":");
    Serial.println(udp.remotePort());
  }
}
