#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

bool verification_num(string s);//judge the string whether is a double or not
double stod(string s);//string to double
int main()
{
    FILE *input = fopen("cal","r");
    string word = "";
    char get_c;
    get_c = getc(input);
    do
    {
        if(isdigit(get_c))
        {
            do
            {
                word += get_c;
                get_c = getc(input);
            }
            while(isdigit(get_c) || get_c == '.');
            if(verification_num(word))
                printf("%s\n",word.c_str());
            else
                printf("This is not a current double\n");
            word = "";
        }
        else if(get_c == '+' || get_c == '-' || get_c == '*' || get_c == '/' || get_c == '(' || get_c == ')')
        {
            word = get_c;
            printf("%s\n",word.c_str());
            word = "";
            get_c = getc(input);
        }
        else if(get_c == ' ' || get_c == '\n'){
            get_c = getc(input);
        }
        else
        {
            printf("Can't understand the Vocabulary: %c\n",get_c);
            break;
        }
        //printf("%c\n",get_c);
    }
    while(get_c != EOF);

    return 0;
}
bool verification_num(string s)
{
    int float_n = 0;
    int last_point = -1;
    if(s[0] == '0' && s.length() != 1 && s[1] != '.')
        return false;
    else
    {
        for(int i = 0 ; i < s.length(); i++)
        {
            if(s[i] == '.')
            {
                last_point = i;
                float_n++;
            }
        }
        if(float_n > 1 || (last_point == s.length() - 1)|| (last_point == 0))
            return false;

    }
    return true;

}
double stod(string s)
{
    double result = 0;
    int shi = 1;
    int flag = false;//when read the '.' the flag will be true
    for(int i = 0 ;i < s.length();i++)
    {
        if(s[i] == '.')
            flag = true;
        else
        {
            if(flag)
                shi *= 10;
            result = result * 10 + (s[i] - '0');
        }
    }
    result /= shi;
    return result;
}

