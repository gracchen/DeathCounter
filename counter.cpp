#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <ctime> 
#include <stack>
#include <map>
using namespace std;

string diffTime(time_t start, time_t end) {
  int sec = (int)difftime(end, start);
  int min = sec / 60;
  int hours = min / 60;
  char buffer [10];
  sprintf(buffer, "%02d:%02d:%02d",int(hours),int(min%60),int(sec%60));
  //printf("%02d:%02d:%02d\n",int(hours),int(min%60),int(sec%60));
  return buffer;
}

void printDict(map<string,size_t>& Dict){
  for(auto it = Dict.cbegin(); it != Dict.cend(); ++it)
  {
      cout << it->first << "\t" << it->second << "\n";
  }
}

void countNames (stack<string>& nameList, map<string,size_t>& Dict)
{
  while (nameList.size() > 1)
  {
    string key_to_find = nameList.top();
    auto it = Dict.find(key_to_find);
    if (it != Dict.end()) {
            it->second++;    // increment map's value for key `c`
        }
    else {
      Dict.insert(make_pair(key_to_find, 1));
    }
    nameList.pop();
  }
  printDict(Dict); cout<< endl;
}

int main() 
{
    time_t t2;
    time (&t2); stack<string> nameList; map<string, size_t> Dict;
    ifstream myFile ("count.csv");
    string line;
    size_t total = 0;
    if (myFile.is_open()){
      while (myFile.good()){
        myFile >> line;
        auto name = line.substr(0, line.find(','));
        nameList.push(name);
        total++;
      }
    }

    countNames(nameList, Dict);
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
        cout << "Death this session: " << i << "\t" << "Death total: " << total + i<< endl;
        nameList.push(line);
        countNames(nameList, Dict);
        getline (cin, line);
      }
    }
    file.close();
}
