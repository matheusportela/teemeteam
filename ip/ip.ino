#include <Ethernet.h>
#include <EthernetUdp.h>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <stdio.h>

#define MESSAGE_MAX_SIZE 1024

unsigned int udpPort = 8888;
EthernetUDP udp;

/////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////

int leftFold(const std::vector<int> &vet, int acc, int(*eval)(int, int)) {
  int vetsize = vet.size();
  for (unsigned i = 0; i < vetsize; ++i) {
    acc = eval(vet[i], acc);
  }
  return acc;
}

int evalMax(int a, int b) {
  return (a > b ? a : b);
}

int evalMin(int a, int b) {
  return (a < b ? a : b);
}

int calcMax(const std::vector<int> &nums) {
  return leftFold(nums, 0xFFFFFFFF, evalMax);
}

int calcMin(const std::vector<int> &nums) {
  return leftFold(nums, 0x7FFFFFFF, evalMin);
}

std::vector< std::vector<int> > divideArray(const std::vector<int> &numbers) {
  std::vector< std::vector<int> > result(3);
  int vetSize = ceil((float)numbers.size()/(float)3);
  for (int i = 0, j = 0, k = 0; i < numbers.size(); ++i) {
    result[k].push_back(numbers[i]);
    if (++j >= vetSize && k < 2) {
      ++k;
      vetSize = (int)numbers.size()-j;
      vetSize = ceil((float)vetSize/(float)2);
      j = 0;
    }
  }
  return result;
}

using namespace std;

string cvtToString(const vector<int> &numbers) {
  if (numbers.size() == 0)
    return string();
  
  stringstream stream;
  stream << numbers[0];
  for (int i = 1; i < numbers.size(); ++i) {
    stream << " " << numbers[i];
  }
  return stream.str();
}

/////////////////////////////////////////////////////////////////////////



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

void sendMessage(IPAddress ip, char msgStatus[], char msg[]) {
  udp.beginPacket(ip, udpPort);
  udp.print("IP: ");
  udp.println("192.168.0.200");
  udp.print("STATUS: ");
  udp.println(msgStatus);
  udp.println("CMD: MIN");
  udp.print("MSG: ");
  udp.println(msg);
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

int streq(char str1[], char str2[]) {
  return (strcmp(str1, str2) == 0);
}

int calculate(vector<int> numbers, char cmd[]) {
  if (streq(cmd, "MIN"))
    return calcMin(numbers);
  else if (streq(cmd, "MAX"))
    return calcMax(numbers);

  Serial.print("Unknown command: ");
  Serial.println(cmd);
}

void loop() {
  char message[MESSAGE_MAX_SIZE];
  receiveMessage(message, MESSAGE_MAX_SIZE);
  Parser parser;
  Parser parser1;
  Parser parser2;
  parser.parse(std::string(message));
  
  int result;
  IPAddress remoteIp(parser.ip[0], parser.ip[1], parser.ip[2], parser.ip[3]);
  IPAddress galileo1(192, 168, 0, 201);
  IPAddress galileo2(192, 168, 0, 202);
  int result1;
  int result2;
  
  if (streq(parser.stat, "START")) {
    Serial.println("START LOGIC");
    std::vector< std::vector<int> > dividedNumbers = divideArray(parser.numbers);
    std::string arrayStr = cvtToString(dividedNumbers[1]);
    sendMessage(galileo1, "RUNNING", (char*)arrayStr.c_str());
    arrayStr = cvtToString(dividedNumbers[2]);
    sendMessage(galileo2, "RUNNING", (char*)arrayStr.c_str());
    result = calculate(dividedNumbers[0], parser.command);
//    result1 = calcMin(dividedNumbers[1]);
//    result2 = calcMin(dividedNumbers[2]);
    receiveMessage(message, MESSAGE_MAX_SIZE);
    parser1.parse(std::string(message));
    receiveMessage(message, MESSAGE_MAX_SIZE);
    parser2.parse(std::string(message));
    std:vector<int> results;
    results.push_back(result);
    results.push_back(parser1.numbers[0]);
    results.push_back(parser2.numbers[0]);
    result = calculate(results, parser.command);
    sprintf(message, "%d", result);
    sendMessage(remoteIp, "RESULT", message);
  } else if (streq(parser.stat, "RUNNING")) {
    result = calculate(parser.numbers, parser.command);
    sprintf(message, "%d", result);
    delay((parser.ip[3] - 200)*500);
    sendMessage(remoteIp, "RESULT", message);
  }

  delay(1000);
}
