#include <Ethernet.h>

unsigned int localPort = 8888;

void setup() {
  system("ifconfig eth0 192.168.0.200 netmask 255.255.255.0 up");
  Serial.begin(9600);
  Serial.println(Ethernet.localIP());
}

void loop() {
}
