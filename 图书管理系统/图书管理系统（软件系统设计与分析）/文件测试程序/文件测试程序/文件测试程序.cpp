// 文件测试程序.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
using namespace std;

class Book {
public:
	void Input(int a, int b, int c, char* d, char* e, char* f)
	{
		id = a;
		numInLib = b;
		count = c;
		*ISBN = d;
		*bookName = e;
		*author = f;
	}
	Book()
	{

	}
	void Print()
	{
		cout << "id: " << id << endl;
		cout << "numInLib: " << numInLib << endl;
		cout << "count: " << count << endl;
		cout << "ISBN: " << ISBN << endl;
		cout << "bookName: " << bookName << endl;
		cout << "author: " << author << endl;
	}
private:
	int id;
	int numInLib;
	int count;
	char* ISBN[16];
	char* bookName[15];
	char* author[15];//类的属性 
};

int main()
{
	Book x[2], y[2];
	int a, b, c;
	char d[16], e[15], f[15];
	for (int i = 0;i<2;i++)
	{
		cout << "请依次输入第" << i + 1 << "本书的信息\n";
		cout << "id:";
	    cin >> a;
		cout << "numInLib:";
		cin >> b;
		cout << "count:";
		cin >> c;
		cout << "ISBN:";
		cin >> d;
		cout << "bookName:";
		cin >> e;
		cout << "author：";
		cin >> f;
		x[i].Input(a, b, c, d, e, f);
	}
	ofstream outfile("book.dat", ios::binary);//文件写入操作 
	if (!outfile)
	{
		cerr << "open error!" << endl;
		abort();
	}
	for (int q = 0;q<2;q++)
		outfile.write((char*)&x[q], sizeof(x[q]));
	outfile.close();
	ifstream infile("book.dat", ios::binary);//文件读取操作
	if (!infile)
	{
		cerr << "open error!" << endl;
		abort();
	}
	for (int k = 0;k<2;k++)
		infile.read((char*)&y[k], sizeof(y[k]));
	infile.close();
	for (int j = 0;j<2;j++)
	{
		cout << "No." << j + 1 << "  ";
		y[j].Print();
	}
	return 0;
}
