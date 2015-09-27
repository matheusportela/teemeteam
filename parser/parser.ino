#include <vector>
#include <string>
#include <sstream>
#include <Ethernet.h>
#include <stdio.h>

class Parser {
  public:
    void parse(std::string message);
    
    char command[1024]; 
    bool manager;
    int ip[4];  
};

void Parser::parse(std::string message) {
  char stat[1024]; 
  sscanf(message.c_str(), "IP: %d.%d.%d.%d\nSTATUS: %s\nCMD: %s", &ip[0], &ip[1], &ip[2], &ip[3], stat, command);
  
  if (stat == "START")
    manager = true;
  else
    manager = false;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Parser parser;
  parser.parse("IP: 192.168.0.12\nSTATUS: START\n CMD: MIN");
}
