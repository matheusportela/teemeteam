#include <Ethernet.h>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

std::string ip1 = "192.168.0.200";
std::string ip2 = "192.168.0.201";

void setup() {
  system("ifconfig eth0 192.168.0.202 netmask 255.255.255.0 up");
  Serial.begin(9600);
  Serial.println(Ethernet.localIP());
}

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

void loop() {
  vector<int> vetor(2);
  for (int i = 0; i < 2; ++i)
    vetor[i] = i;
  vector< vector<int> > vetdividido = divideArray(vetor);
  Serial.println(cvtToString(vetdividido[0]).c_str());
  Serial.println(cvtToString(vetdividido[1]).c_str());
  Serial.println(cvtToString(vetdividido[2]).c_str());
  Serial.println("----");
}

