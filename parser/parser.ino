#include <vector>
#include <string>
#include <sstream>
#include <Ethernet.h>
#include <stdio.h>

class Parser {
  public:
    void parse(std::string message);
    
    char command[1024]; //CMD
    char stat[1024]; //STATUS
    int ip[4]; //IP
    std::vector<int> numbers; //MSG
  private:
    void parseMSG(std::string message);
};

void Parser::parse(std::string message) {
  sscanf(message.c_str(), "IP: %d.%d.%d.%d\nSTATUS: %s\nCMD: %s\nMSG: %*s", &ip[0], &ip[1], &ip[2], &ip[3], stat, command);
  parseMSG(message);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Parser parser;
  parser.parse("IP: 192.168.0.12\nSTATUS: START\n CMD: MIN\nMSG: 0 1 20 -33432 4 5");
}

void Parser::parseMSG(std::string message) {
    char line1[1024];
    char line2[1024];
    char line3[1024];
    char line[1024];
    sscanf(message.c_str(), "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]", line1, line2, line3, line);
    
    char numBuffer[64];
    int numbers[1024];
    int numberIndex = 0;
    int i, j;
    for (i = 5; i < strlen(line); i++)
    {
        for (j = 0; line[i + j] != ' ' && (i + j) < strlen(line); j++)
            numBuffer[j] = line[i + j];
        numBuffer[j] = '\0';
        i += j;
        sscanf(numBuffer, "%d", &numbers[numberIndex]);
        numberIndex += 1;
    }
    
    for (i = 0; i < numberIndex; i++)
      this->numbers.push_back(numbers[i]);
}
