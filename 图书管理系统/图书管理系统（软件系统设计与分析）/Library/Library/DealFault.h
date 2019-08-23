#pragma once
#include<string>
#include<iostream>
using namespace std;

int DealFault();

/*从标准输入流中获得一个整数并返回
如果输入的一行字符串中全是数字，就返回这个数字
只要有字符出现，这个函数就会返回-1*/
int GetIntFromCin();

/*判断一个字符串表示的是否是一个ISBN*/
bool IsISBN(string isbn);


/*判断输入的密码中是否含有全角字符，含有的话返回true，否则返回false*/
bool IsDoubleChar(string str);