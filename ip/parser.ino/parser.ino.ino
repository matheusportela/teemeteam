#include <vector>
#include <string>
#include <sstream>

//START MIN 0 1 2 3 4
//MIN 0 1 2 3 4

class Parser {
  public:
    void parse(std::string message);
    
    std::string message;
    bool manager;
    std::string instruction;
    std::vector<int> list;
  private:
    void parseStart();
    void parseInstruction();
    void parseArray();
};

void Parser::parseStart() {
  std::string start;
  for (int i=0; i< 5; i++)
    start.push_back(message[i]);
  if (start == "START") {
    manager = true;
    message.erase(0,5);
    Serial.println(message.c_str());
  }
}

void Parser::parseInstruction() {
  instruction.clear();
  for (int i=0;i<3;i++)
    instruction.push_back(message[i]);
}

void Parser::parseArray() {
   for (int i = 5; i < message.size(); i++)
     list.push_back((int)message[i]);
}

void Parser::parse(std::string message) {
  this->message = message;
  parseStart();
  parseInstruction();
  parseArray();
}

void setup() {
  Parser parser;
  parser.parse("START MIN 1 2 3 4 5");
}

void loop() {
  // put your main code here, to run repeatedly:

}
