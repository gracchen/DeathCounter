#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <ctime> 
using namespace std;

int main() 
{
    time_t tt;
    struct tm * ti;
    time (&tt);
    ti = localtime(&tt);
    cout << asctime(ti);

    char output[30];
    strftime(output, 30, "%m %d %Y, %H:%M:%S\n", ti);
    cout << output;

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
    if (file.is_open()){
      while(line != "q")
      {
        i++;
        file << endl << line;
        cout << "Death this session: " << i << endl;
        cout << "Death total: " << total + i<< endl;
        getline (cin, line);
      }
    }
    file.close();
}
