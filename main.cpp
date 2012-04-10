#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
class fuhao
{
    private:
    string s1;
    string s2;
    public:
    fuhao()
    {
    }
    fuhao(string s1,string s2)
    {
        this->s1 = s1;
        this->s2 = s2;
    }
    string getID()
    {
        return s1;
    }
    string getRESULT()
    {
        return s2;
    }
    void printALL()
    {
        printf("( %s , %s )\n",s1.c_str(),s2.c_str());
    }
    void input(string s1,string s2)
    {
        this->s1 = s1;
        this->s2 = s2;
    }
};
class stack
{
    private:
        int i;
        fuhao mystack[200];
    public:
    stack()
    {
        i = -1;
    }
    void push(fuhao f)
    {
        i++;
        mystack[i] = f;
    }
    void push(string s1,string s2)
    {
        i++;
        mystack[i].input(s1,s2);
    }
    fuhao pop()
    {
        fuhao r("NULL","NULL");
        if(i >= 0)
        {
            r = mystack[i];
            i--;
        }
        else
        {
            printf("The stack is empty");
        }
        return r;
    }
    fuhao top()
    {
        fuhao r("NULL","NULL");
        if(i >= 0)
        {
            r = mystack[i];
        }
        else
        {
            printf("The stack is empty");
        }
        return r;
    }
    bool isempty()
    {
        if(i <= -1)
            return true;
        else
            return false;
    }
    void empty()
    {
        i = -1;
    }
    void printALL()
    {
        int j = i;
        printf("{ ");
        for(j = 0 ; j <= i ; j++)
        {
            printf("[%s , %s] ",mystack[j].getID().c_str(),mystack[j].getRESULT().c_str());
            if(j != i)
            printf(",");
        }
        printf(" }\n");
    }

};
bool verification_num(string s);//judge the string whether is a double or not
double stod(string s);//string to double
int f(string s);
int g(string s);
int main()
{
    FILE *input = fopen("cal","r");
    stack mystack;
    fuhao input_data[100];
    int ii = 0;
    //cifa
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
            {
                input_data[ii++].input("id",word);
            }
            else
                printf("This is not a current double\n");
            word = "";
        }
        else if(get_c == '+' || get_c == '-' || get_c == '*' || get_c == '/' || get_c == '(' || get_c == ')')
        {
            word = get_c;
            input_data[ii++].input(word,word);
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
    input_data[ii].input("#","#");
    for(int i = 0; i <=ii ; i++)
        printf("%s ",input_data[i].getID().c_str());
    printf("\n");
    //yufa
    int i = 0;
    fuhao last_pop;
    mystack.push("#","#");
    mystack.printALL();
    while(!(input_data[i].getID() == "#" && mystack.top().getID() == "#"))
    //for(int k = 0 ; k < 25 ; k ++)
    {
        if(f(mystack.top().getID()) <= g(input_data[i].getID()))
        {
            //printf("%d %s %d %s\n",f(mystack.top().getID()),mystack.top().getID().c_str(),g(input_data[i].getID()),input_data[i].getID().c_str());
            mystack.push(input_data[i]);
            //mystack.printALL();
            i++;
        }
        else if (f(mystack.top().getID()) > g(input_data[i].getID()))
        {
            do
            {
                last_pop = mystack.pop();
                //mystack.printALL();
            }
            while(f(mystack.top().getID()) >= g(last_pop.getID()));
        }
    }
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
int f(string s)
{
    if(s == "+" || s == "-")
        return 2;
    else if(s == "*" || s == "/")
        return 4;
    else if(s == "(" || s == "#")
        return 0;
    else if(s == ")" || s == "id")
        return 6;
    else
        return -1;
}
int g(string s)
{
    if(s == "+" || s == "-")
        return 1;
    else if(s == "*" || s == "/")
        return 3;
    else if(s == "(" || s == "id")
        return 5;
    else if(s == ")" || s == "#")
        return 0;
    else
        return -1;
}
