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


struct Stats
{
  unsigned short deaths;
  unsigned short wins;
} stats;

string diffTime(time_t start, time_t end) {
  unsigned short sec = (long)difftime(end, start);
  unsigned short min = sec / 60;
  unsigned __int8 hours = min / 60;
  char buffer [8];
  sprintf(buffer, "%02d:%02d:%02d",short(hours),short(min%60),short(sec%60));
  return buffer;
}

void printDict(map<string,Stats>& Dict){
  for(auto it = Dict.cbegin(); it != Dict.cend(); ++it)
      cout << it->first << ": " << it->second.deaths << ", " << it->second.wins << "\n";
}

void writeStats(map<string,Stats>& Dict){
  fstream file;
  file.open("count.csv", ios_base::out | std::ios_base::trunc);
  file.close();

  fstream file2;
  file2.open("count.csv", std::ios_base::app);
  file2 << "Name,Deaths,Victories\n";
  if (file2.is_open()){
    for(auto it = Dict.cbegin(); it != Dict.cend(); ++it)
    {
      string line = it->first + "," + to_string(it->second.deaths) + "," + to_string(it->second.wins) + "\n";
      file2 << line;
    }
  }
  file2.close();
}

unsigned int countNames (stack<string>& nameList, map<string,Stats>& Dict)
{
  unsigned int deaths = 0;
  while (nameList.size() > 1)
  {
    string key_to_find = nameList.top();
    bool isWin = false;
    if (key_to_find[0] == '*')
    {
      key_to_find.erase(0,1); 
      isWin = true;
    }

    auto it = Dict.find(key_to_find);
    if (it != Dict.end()){
      if (isWin)
        it->second.wins++;
      else {
        it->second.deaths++;
        deaths++;
      }
    }
    else {
      struct Stats temp;
      if (isWin)
        temp = {0,1};
      else {
        temp = {1,0};
        deaths++;
      }
      Dict.insert(make_pair(key_to_find, temp));
    }
    nameList.pop();
  }
  return deaths;
}



int main() 
{
  cout << "Welcome to Death Counter. \n[enemy] = death, *enemy = victory, p for stats, q to quit." << endl;
  time_t t2;
  time (&t2); stack<string> nameList; map<string, Stats> Dict;
  ifstream myFile ("log.csv");
  string line, name;

  if (myFile.is_open()){
    while (myFile.good()){
      getline(myFile, line);
      //myFile >> line;
      name = "";
      for (unsigned short i = 0; i < line.size(); i++)
      {
        if (line[i] == ',') break;
        name += line[i];
      }
      if (name.size() != 0)
        nameList.push(name);
    }
  }
  
  unsigned int total = countNames(nameList, Dict);
  getline (cin, line);
  unsigned short deathCount = 0; unsigned short winCount = 0;
  fstream file;
  file.open("log.csv", std::ios_base::app);
  time_t tt;struct tm * ti; //initialize
  if (file.is_open()){
    while(line != "q")
    {
      if (line == "p") {
        printDict(Dict); cout << endl;
      }
      else if (line.size() != 0) {
      time (&tt); ti = localtime(&tt);
      char output[20]; strftime(output, 20, "%m/%d/%Y,%H:%M:%S", ti);
      file << endl << line << "," << output << "," << diffTime(t2,tt);
      nameList.push(line);
      countNames(nameList, Dict);
      if (line[0] == '*')
        line.erase(0,1);
      else
        deathCount++;
      auto it = Dict.find(line);
      cout << "Deaths to " << line << ": " << to_string(it->second.deaths) << endl;
      cout << "Victories to " << line << ": " << to_string(it->second.wins) << endl;
      cout << "Deaths this session: " << deathCount << "\t" << "Total: " << total + deathCount << endl << endl;
      }
      getline (cin, line);
    }
  }
  file << "\n";
  file.close();
  writeStats(Dict);
  //print shortDict(Dict);
  //cout << "Press ENTER to close...";
  //std::cin.get(); 
}
