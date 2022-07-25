#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <ctime> 
using namespace std;

string diffTime(time_t start, time_t end) {
  int sec = (int)difftime(end, start);
  int min = sec / 60;
  int hours = min / 60;
  char buffer [10];
  sprintf(buffer, "%02d:%02d:%02d",int(hours),int(min%60),int(sec%60));
  return buffer;
}

int main() 
{
    time_t t2;
    time (&t2);
    ifstream myFile ("count.csv");
    string line;
    size_t total = 0;
    if (myFile.is_open()){
      while (myFile.good()){
        myFile >> line;
        cout << line << endl;
        total++;
      }
    }
    total--;
    getline (cin, line);
    int i = 0;
    fstream file;
    file.open("count.csv", std::ios_base::app);
    time_t tt;struct tm * ti; //initialize
    if (file.is_open()){
      while(line != "q")
      {
        i++;
        time (&tt); ti = localtime(&tt);
        char output[30]; strftime(output, 30, "%m/%d/%Y,%H:%M:%S", ti);
        file << endl << line << "," << output << "," << diffTime(t2,tt);
        cout << "Death this session: " << i << endl;
        cout << "Death total: " << total + i<< endl;
        getline (cin, line);
      }
    }
    file.close();
}
