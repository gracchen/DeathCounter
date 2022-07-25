#include <iostream>
#include <string>
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

    char input = getchar();
    int i = 0;
    while(input != 'q')
    {
      i++;
      cout << "Death this session: " << i << endl;
      cout << "Death total: " << endl;
      input = getchar();
    }
}