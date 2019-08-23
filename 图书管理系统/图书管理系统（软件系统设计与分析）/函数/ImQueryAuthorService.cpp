#include "stdafx.h"
#include "QueryAuthorService.h"
#include <iostream>
#include <string>
using namespace std;

void QueryAuthorService()//查找作者servlet 
{
	int choose;
	choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "输入0返回主界面 输入1按照id查找作者 输入2按照作者名查询作者" << endl;
		cin >> choose;
		if (!cin)            //条件可改写为cin.fail() 
		{
			cout << endl;
			cout << "输入有错!请重新输入" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			choose = 1;
			continue;
		}
		switch (choose)
		{
			int choose2;
		case 0:return;
		case 1:
			choose2 = 1;
			while (choose2)
			{
				cout << endl;
				cout << "请输入作者id号 输入0返回作者操作主界面" << endl;
				cin >> choose2;
				if (!cin)            //条件可改写为cin.fail() 
				{
					cout << endl;
					cout << "输入有错!请重新输入" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					choose2 = 1;
					continue;
				}
				if (choose2 == 0)
				{
					break;
				}
				list<Author> authorList= getAuthorById(choose2);
				if(authorList.size()==0)
				{
					cout << "不存在该作者id" << endl;
				}
				else
					showAuthorInfo(authorList);
			}
			break;
		case 2:
			choose2 = 1;
			while (choose2)
			{
				string authorName;
				cout << endl;
				cout << "请输入作者姓名 输入0返回作者操作主界面" << endl;
				cin >> authorName;
				if (!cin) {
					cout << endl;
					cout << "输入有错!请重新输入" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					choose2 = 1;
					continue;
				}
				if (authorName=="0")
				{
					choose2 = 0;
					break;
				}
				list<Author> authorList = getAuthorByName(authorName);
				if (authorList.size()==0)
				{
					cout << endl;
					cout << "不存在该姓名的读者" << endl;
					continue;
				}
					showAuthorInfo(authorList);
			}
			break;
		default:
			cout << endl;
			cout << "请正确输入选项！" << endl;
			break;
		}
	}
}