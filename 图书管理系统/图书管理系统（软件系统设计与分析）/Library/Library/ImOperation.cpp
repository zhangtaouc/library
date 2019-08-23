#include"stdafx.h"
#include"Operation.h"
#include<time.h>
#include<iostream>
using namespace std;

//去掉字符串s首尾的空格
void trimFLSpace(string& s) {
	if (!s.empty()) {
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}
}


//find 函数返回值：The position of the first character of the first match.
//If no matches were found, the function returns string::npos.
// 第二个参数是 Position of the first character in the string to be considered in the search.
//去掉字符串s中的所有空格
void trimAllSpace(string& s) {
	int index = 0;
	if (!s.empty()) {//该函数的功能是：每找到一个空格，就将其抹去，然后继续寻找下一个空格所在的位置直至结束
		while ((index = s.find(' ', index)) != string::npos) {
			s.erase(index, 1);// erase(offset,count) 从offset位置开始抹去count个字符
		}
	}
}


/*把s2的字符串复制到s1中去，n表示s1的有效长度
如果s2的字符长度大于等于n，函数不复制，直接返回false
否则将s2复制到s1后，s1剩余的有效存储空间都用'\0'填充
*/
bool copy(char* s1, string s2, unsigned n) {
	unsigned n2 = s2.length();
	if (n2 >= n) return false;// n2 >= n 是为了保证s1一定至少有一个字符串结束符 '\0'
	const char* c2 = s2.data();
	for (unsigned i = 0; i < n; i++)
	{
		if (i < n2)
			s1[i] = c2[i];
		else
			s1[i] = '\0';
	}
	return true;
}






/*
void test(int* a) {
cout << "test:" << sizeof(a) << endl;
}

经过测试后发现：
int a[5];
cout << sizeof(a);
test(a);
它们输出的值分别是20和4  
也就是说在将整型指针作为参数传递时，数组信息不会被保存下来
*/
/*将b数组的内容依次复制到a数组中去
n1是a数组的长度 n2是b数组的长度
如果b数组的长度大于n1
函数不复制，直接返回false
*/
bool copy(int* a, int* b, unsigned n1, unsigned n2) {
	if (n2 > n1) return false;
	for (unsigned i = 0; i < n1; i++) {
		if (i < n2) a[i] = b[i];
		else a[i] = 0;
	}
	return true;
}








/*测试使用
int main() {
int i;
string s = "   kkkkllll    ";
cout << s.data() <<"end"<< endl;
trimFLSpace(s);
cout << s.data() << "end"<<endl;
cin >> i;
return 0;
}
*/