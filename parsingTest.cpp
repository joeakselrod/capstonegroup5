//Test for parsing Functions
//print last 4 char of string -> +INQ:2:72:D2224,3E0104,FFBC

#include <iostream>
#include <string.h>
using namespace std;




int main()
{
char array[] = "AAAA;A1:3;B1:5;ZZZZ";
char *strings[10];
char *ptr = NULL;

    //Serial.begin(9600);
    //Serial.print(array);
    byte index = 0;
    ptr = strtok(array, ":;");  // takes a list of delimiters
    while(ptr != NULL)
    {
        strings[index] = ptr;
        index++;
        ptr = strtok(NULL, ":;");  // takes a list of delimiters
    }
    //Serial.println(index);
    // print the tokens
    for(int n = 0; n < index; n++)
   {
    cout<<strings[n];
   }

return 0;
}
