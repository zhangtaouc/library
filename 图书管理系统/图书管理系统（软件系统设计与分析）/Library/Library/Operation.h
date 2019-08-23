#pragma once
#include<iostream>
using namespace std;





/*将s2字符串复制到 s1指向的字符数组中去，复制长度为n，如果s2所占字节数大于n，函数返回false*/
bool copy(char* s1, string s2, unsigned n);

/*将b数组的内容依次复制到a数组中去
n1是a数组的长度 n2是b数组的长度
如果b数组的长度大于n1
函数不复制，直接返回false

否则进行复制，a中不够的用0填充
*/
bool copy(int* a,int* b,unsigned n1,unsigned n2);




//去掉字符串s首尾的空格
void trimFLSpace(string& s);

//去掉字符串s中的所有空格
void trimAllSpace(string& s);




