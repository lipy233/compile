#include <iostream>
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
using namespace std;


//标识符
int it = 0;

//字符
int ct = 1;

//字符串
int st = 2;

//常数
int dig = 3;

//关键字
const string keywords[6] = {"int", "main", "void", "if", "else", "char"};
int keynum[6] = {4, 5, 6, 7, 8, 9};

//运算符和界符
const string symbol[20] = {">=", "<=", "==", "=", ">", "<", "+", "-", "*", "/", "{", "}", ",", ";", "(", ")", "'", "\"", "[", "]"};
int symnum[20] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};





char letter[500];
int length;


int iskey(string str){//关键字
    for(int i = 0; i < 6; i++){
        if (str == keywords[i])
            return keynum[i];//关键字种类
    }
    return 0;//标识符
}

int issymbol(string str){//界符和操作符
    int i;
    for(i = 0; i < 20; i++){
        if(str == symbol[i])
            return symnum[i];
    }

    return -1;//未定义的界符或操作符
}

bool isDigit(char ch){//数字
    if (ch >= '0' && ch <= '9')
        return true;
    return false;
}

bool isLetter(char ch){//字母
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return true;
    return false;
}

void DFA(){
    int i = 0;
    while (i < length){

        int syn , c_or_s = 0;//syn:种类码，c_or_s：取0，不是‘c’或“s”

            string token = "";
            

            if(isLetter(letter[i])){//字母开头
                
                while(isDigit(letter[i]) || isLetter(letter[i])){//字母|数字
                    token += letter[i];
                    i++;
                    if(iskey(token)) break;
                }
                
                syn = iskey(token) > 0 ? iskey(token):0;//key||it

            }

            else if(isDigit(letter[i])){//数字开头
                while(isDigit(letter[i])){
                    token += letter[i];
                    i++;    
                }
                syn = 3;//dig

            }

            else{//界符和操作符
                token += letter[i];
                i++;
                syn = issymbol(token);
                //cout << "syn: " << syn << "token" << token <<endl;
                /*
                >= 10, <= 11, == 12, = 13, > 14, < 15, + 16, - 17 ;
                * 18, / 19, { 20, } 21, , 22, ; 23, ( 24, ) 25, ' 26, " 27;
                [ 28, 29 ];
                */
                if(syn >= 13 && syn <= 15){// >, <, = 开头
                    string k = token;
                    k += letter[i];
                    //cout << "k:"<< k << endl;
                    if(issymbol(k) >= 10 && issymbol(k) <= 12){//>=, <=, ==
                    syn = issymbol(k);
                    i++;
                    token = k;
                    }
                }
                else if(syn == 26 || syn == 27){//字符或字符串
                    c_or_s = syn == 26 ? ct:st;

                }
                
            }

            cout << "(" <<token << ", " << syn << ")" << endl;

            if(c_or_s != 0){//字符或字符串
                string token1 = "";
                while(isLetter(letter[i])){
                    token1 += letter[i++];

                }
                cout << "(" <<token1 << ", " << c_or_s << ")" << endl;
                i++;
                cout << "(" <<token << ", " << syn << ")" << endl;//将‘和“的右半部打印

            }


    }
    
    
}

int main(){
    freopen("E://2021//vs//compile//demo.c", "r", stdin);
    freopen("E://2021//vs//compile//tokens.txt", "w", stdout);

    char w;
    length = 0;
    while(cin >> w){//跳过空格
        if(w != ' '){
            letter[length] = w;
            length++;
        }
    }

        DFA();
    
    

    fclose(stdin);
    fclose(stdout);

    return 0;

}