//
//  main.cpp
//  reversePolishNotation
//
//  Created by Mykola Medynsky on 11/5/18.
//  Copyright © 2018 Mykola Medynskyi. All rights reserved.
//
#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;
bool isNumber(const string &symbol)
{
    bool isNumber = false;
    for(int i = 0; i < symbol.size(); i++)
    {
        if(!isdigit(symbol[i]))
        {
            isNumber = false;
        }

        else
        {
            isNumber = true;
        }
    }
    return isNumber;
}
int priority(const string &c)
{
    if(c == "^")
    {
        return 3;
    }
    if(c == "*" || c == "/")
    {
        return 2;
    }
    if(c == "+" || c == "-")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool isBracket(char b)
{
    return (b=='('|| b==')');
}
bool isOperator(char o)
{
    return (o == '+' || o == '-' || o == '*' || o == '/' || o == '^');
}
bool isOperator(string& o)
{
    return (o == "+" || o == "-" || o == "*" || o == "/" || o == "^");
}
vector <string> parse(string& str, bool& flag, bool& isNum)
{
    vector<string> tokens;
    string k = "";
    int open = 0;
    int close = 0;
    int count = 0;
    int countOperator = 0;
    while (count != str.size() && flag == true)
    {
        if (str[count]==' ')
        {
            count++;
            continue;
        }
        else{
            if (!isdigit(str[count])&&!isOperator(str[count])&&!isBracket(str[count]))
            {
                cout << "Сторонні знаки!"<<endl;
                flag=false;
            }
            else{
                while (isdigit(str[count]))
                {
                    k+=str[count];
                    if (str[count+1]=='('&&str.length()>1)
                    {
                        cout << "Мабуть це не нормально вводити відкриваючу дужку після числа" <<endl;
                        flag = false;
                    }
                    count++;
                    isNum = true;
                }
                tokens.push_back(k);
                k.erase(k.begin(), k.end());
                if (str[count]=='(')
                {
//                    if (str[count+1]==')'&&str.length()>1)
//                    {
//                        cout << "У виразі тільки дужки"<<endl;
//                        flag = false;
//                    }
                    
                    
                    open++;
                    k+=str[count];
                    count++;
                    tokens.push_back(k);
                    k.erase(k.begin(), k.end());
                    if (str[count]=='-'||str[count]=='+')
                    {
                        k+=str[count];
                        count++;
                        if (isdigit(str[count])) continue;
                    }
                    
                }
                else if (str[count]==')')
                {
                    close++;
                    if (close>open)
                    {
                        cout << "Неправильний порядок дужок" <<endl;
                        flag=false;
                    }
                    else{
                        k+=str[count];
                        count++;
                        tokens.push_back(k);
                        k.erase(k.begin(), k.end());
                    }
                }
                if (isOperator(str[count]))
                {
                    if (isOperator(str[count-1])&& str.length()>1)
                    {
                        cout<<"Два оператори підряд"<<endl;
                        flag=false;
                    }
                    else{
                        if (str[count-1]=='('&&str.length()>1&&(str[count]=='*'||str[count]=='/'||str[count]=='^'))
                        {
                            cout<< ""<<endl;
                            flag = false;
                        }
                        else {
                            k+=str[count];
                            count++;
                            tokens.push_back(k);
                            k.erase(k.begin(), k.end());
                        }
                    }
                    
                }
                
            }
        }
    }
    if (flag==true){
        if (open> close)
        {
            flag = false;
            cout << "ЗА ВІДКРИВАЮЧИМИ ДУЖКАМИ СЛІДКУЙТЕ!" <<endl;
        }
    }
    return tokens;
}
void calculate(const string &s, bool& flag)
{
    vector <double> arr;
    istringstream stream(s);
    
    while (stream && flag)
    {
        string temp;
        stream >> temp;
        if (temp == "+")
        {
            double k = arr[arr.size()-1];
            
            arr.erase(arr.end()-1);
            arr[arr.size()-1]+=k;
            
        }
        else if(temp == "*")
        {
            double k = arr[arr.size()-1];
            
            arr.erase(arr.end()-1);
            arr[arr.size()-1]*=k;
        }
        else if(temp == "/")
        {
            double k = arr[arr.size()-1];
            if (k == 0||arr.size()==1)
            {
                cout << "error"<<endl;
                flag = false;
                
            }
            else{
                arr.erase(arr.end()-1);
                arr[arr.size()-1]/=k;
            }
        }
        else if (temp == "-")
        {
            double k = arr[arr.size()-1];
            if (arr.size()==1)
            {
                arr[arr.size()-1] = 0-k;
            }
            else{
                arr.erase(arr.end()-1);
                arr[arr.size()-1]-=k;
            }
        }
        else if (temp == "^")
        {
            double k = arr[arr.size()-1];
            
            arr.erase(arr.end()-1);
            arr[arr.size()-1] = pow(arr[arr.size()-1],k);
            
        }
        else
        {
            if (temp == """") continue;
            int k = stoi(temp);
            arr.push_back(k);
        }
        
    }
    if (flag == true)
    {
        cout << arr[arr.size()-1]<<endl;
    }
}
int main()
{
    string infix = "2^3^2";
    bool flag = true;
    bool isNum = false;
    bool newFlag = true;
    if (infix.length()==0)
    {
        cout << "Довжина цього рядка дорівнює 0"<<endl;
    }
    else{
        vector<string> tokens = parse(infix, flag,isNum);
        string outputList;
        stack<string> s;
        
        if (flag && isNum &&newFlag){
            for(int i = 0; i < tokens.size(); i++)
            {
                if(isNumber(tokens[i])&&tokens[i+2]=="(")
                {
                    cout << "ERror3"<<endl;
                    flag= false;
                    continue;
                }
                if (isNumber(tokens[i])&&isNumber(tokens[i+1])&&tokens.size()>1)
                {
                    newFlag = false;
                    continue;
                }
                if(isNumber(tokens[i]))
                {
                    outputList+=(tokens[i])+' ';
                }

                if(tokens[i] == "(")
                {
                    s.push(tokens[i]);
                }
                
                if(tokens[i] == ")")
                {
                    while(!s.empty() && s.top() != "(")
                    {
                        outputList+=(s.top()) + ' ';
                        s.pop();
                    }
                    s.pop();
                }
                if(isOperator(tokens[i]))
                {
                    while(!s.empty() && (priority(s.top()) >= priority(tokens[i])))
                    {
                        outputList+=(s.top()) + ' ';
                        s.pop();
                    }
                    s.push(tokens[i]);
                }
            }
            while(!s.empty())
            {
                outputList+=(s.top())+' ';
                s.pop();
            }
            if(flag&&newFlag&&isNum){
                for(int i = 0; i < outputList.size(); i++)
                {
                    cout<<outputList[i];
                }
            }
            cout<< endl;
            if(newFlag&&flag&&isNum){
                calculate(outputList,flag);
            }
        }
        
    }
    if(!isNum||!newFlag)
    {
        cout << "Error2"<<endl;
    }
    return 0;
}
