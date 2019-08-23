#include "stdafx.h"
#include<string>
#include<iostream>
using namespace std;


int DealFault() {

	string choice;
	cout << endl << "请选择继续或是退出" << endl;
	cout << endl << "1：继续    0：退出" << endl;
	//cin >> choice;
	getline(cin, choice);
	while (choice != "1" && choice != "0") {
		cout << endl << "您输入的信息不符合要求，请选择重新输入或是退出" << endl;
		cout << endl << "1：继续			0：退出" << endl;
		//cin >> choice;
		getline(cin, choice);
	}
	if (choice == "1") {
		return 1;
	}
	else {
		return 0;
	}
}

//主函数的容错处理
int GetIntFromCin() {

	/**/
	string str;
	string str2;
	int choice;
	getline(cin, str);
	choice = atoi(str.c_str());
	str2 = "" + to_string(choice);
	if (str != str2) {
		return -1;
	}
	return choice;
}

/*判断一个字符串表示的是否是一个ISBN*/
bool IsISBN(string isbn) {

	if (isbn == "") return false;

	/*检验ISBN是否满足校验条件
	ISBN分两种，9位的和13位的
	对于9位的，用10-2分别去乘前8位（从左到右依次）
	将这些乘积加起来为sum 然后计算 f = 11 - (sum%11)
	根据f的不同取值得到不同的校验位bit，然后去检验最后一位是否就是这个bit

	对于13位的，用1,3,1,3...去依次乘以前12位，然后将其加起来得到sum
	f = 10 - (sum%10) 由f的取值去判断校验位应该是什么
	*/
	unsigned i = 0;
	for (i = 0; i < isbn.length(); i++) {
		if (!(isbn[i] >= '0' && isbn[i] <= '9')) return false;
	}

	string frontStr = isbn.substr(0, isbn.length() - 1);
	string backStr = isbn.substr(isbn.length() - 1, 1);
	const char* c = backStr.data();
	if (!(frontStr.length() == 9 || frontStr.length() == 12))
		return false;
	const char* s = isbn.data();
	char rightChar;
	if (frontStr.length() == 9) {
		int sum = 0;
		int mul = 10;
		for (i = 1; i <= 9; i++) {
			sum += mul * (s[i - 1] - '0');
			mul--;
		}
		int num = 11 - (sum % 11);
		if (num == 10) rightChar = 'X';
		else if (num == 11) rightChar = '0';
		else rightChar = num + '0';

	}
	else {
		int mul;
		int sum = 0;
		for (i = 1; i <= 12; i++) {
			if (i % 2 == 1) mul = 1;
			else mul = 3;
			sum += mul * (s[i - 1] - '0');
		}
		int num = 10 - (sum % 10);
		if (num == 10) rightChar = '0';
		else rightChar = '0' + num;
	}
	if (rightChar == c[0]) return true;
	else return false;
}

/*判断输入的密码中是否含有全角字符，含有的话返回true，否则返回false*/
bool IsDoubleChar(string str) {
	const char* ch = str.c_str();//把一个常字符指针指向一个字符串
	char c;//定义一个字符遍历该字符串
	while (c = *ch++) {
		if ((c & 0x80) && (*ch & 0x80)) {
			return true;
		}
	}
	return false;
}

