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
  return buffer;
}

void printDict(map<string,size_t>& Dict){
  for(auto it = Dict.cbegin(); it != Dict.cend(); ++it)
      cout << it->first << ": " << it->second << "\n";
}

void writeStats(map<string,size_t>& Dict){
  fstream file;
  file.open("count.csv", ios_base::out | std::ios_base::trunc);
  file.close();

  fstream file2;
  file2.open("count.csv", std::ios_base::app);

  if (file2.is_open()){
    for(auto it = Dict.cbegin(); it != Dict.cend(); ++it)
    {
      string line = it->first + "," + to_string(it->second) + "\n";
      file2 << line;
    }
  }
  file2.close();
}

void countNames (stack<string>& nameList, map<string,size_t>& Dict)
{
  while (nameList.size() > 1)
  {
    string key_to_find = nameList.top();
    auto it = Dict.find(key_to_find);
    if (it != Dict.end())
            it->second++;
    else
      Dict.insert(make_pair(key_to_find, 1));
    nameList.pop();
  }
}

int main() 
{
  cout << "Welcome to Death Counter. \nEnter enemy upon death, *enemy upon victory, q to quit." << endl;
  time_t t2;
  time (&t2); stack<string> nameList; map<string, size_t> Dict;
  ifstream myFile ("log.csv");
  string line, name;
  size_t total = 0;
  if (myFile.is_open()){
    while (myFile.good()){
      getline(myFile, line);
      //myFile >> line;
      name = "";
      for (size_t i = 0; i < line.size(); i++)
      {
        if (line[i] == ',') break;
        name += line[i];
      }
      if (name.size() != 0)
        nameList.push(name);
      total++;
    }
  }
  
  countNames(nameList, Dict);
  total--;
  getline (cin, line);
  int i = 0;
  fstream file;
  file.open("log.csv", std::ios_base::app);
  time_t tt;struct tm * ti; //initialize
  if (file.is_open()){
    file << "\n";
    while(line != "q")
    {
      i++;
      time (&tt); ti = localtime(&tt);
      char output[30]; strftime(output, 30, "%m/%d/%Y,%H:%M:%S", ti);
      file << endl << line << "," << output << "," << diffTime(t2,tt);
      nameList.push(line);
      countNames(nameList, Dict);
      auto it = Dict.find(line);
      cout << "Total deaths to " << line << ": " << to_string(it->second) << endl;
      cout << "Deaths this session: " << i << "\t" << "Total: " << total + i<< endl;
      getline (cin, line);
    }
  }
  file.close();
  writeStats(Dict);
  printDict(Dict);
  cout << "Press ENTER to close...";
  std::cin.get(); 
}
