#include <iostream>
#include <fstream>
using namespace std;

int main() {
  int value;
  ofstream outputFile("case5.txt");
  //ofstream file ("case1.txt");
    
  if (outputFile.is_open()) {
    int i = 0;
    int number = 5000;
    outputFile << number <<"\n";

    while (i < number) {
      value = rand()%number; 
      outputFile << value<<"\n";
      i++;
    }
    outputFile.close();
  }
}