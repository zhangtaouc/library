
#include"stdafx.h"
#include<list>
#include"Structs.h"
#include"AuthorFunc.h"
#include"showInfo.h"
#include <iostream>
#include <string>
#include"DealFault.h"
using namespace std;

void QueryAuthorService() {

	int choose;
	choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "请输入：" << endl;
		cout << "0:返回主界面 " << endl;
		cout << "1:按照id查找作者" << endl;
		cout << "2:按照作者名查询作者" << endl;
		choose = GetIntFromCin();//输入choose
		switch (choose)
		{
			int choose2;
		case 0:
			return;
		case 1:
			choose2 = 1;
			while (choose2)
			{
				cout << endl;
				cout << "请输入作者id号(从1开始的整数） 输入0返回作者操作主界面" << endl;
				choose2 = GetIntFromCin();
				if (choose2 == -1) {
					cout << "输入不合要求" << endl;
					continue;
				}

				if (choose2 == 0)
				{
					break;
				}
				list<Author> authorList = getAuthorById(choose2);
				if (authorList.size() == 0)
				{
					cout << "不存在该作者id" << endl;
				}
				else
					showAuthorInfo(authorList, true);
			}
			break;
		case 2:
			choose2 = 1;
			while (choose2)
			{
				string authorName;
				string key;//用于选择是否退按作者名查找
				cout << endl << "您是否要退出查找？ 输入0返回作者操作主界面，其他键继续查找" << endl;
				getline(cin, key);
				if (key == "0")
					break;
				//输入作者名
				cout << endl << "请输入作者名" << endl;
				getline(cin, authorName);
				list<Author> authorList = getAuthorByName(authorName);
				if (authorList.size() == 0)
				{
					cout << endl;
					cout << "不存在该姓名的读者" << endl;
					continue;
				}
				showAuthorInfo(authorList, 1);
			}
			break;
		default:
			cout << endl;
			cout << "请正确输入选项！" << endl;
			break;
		}
	}

}


void QueryBooksByAuthorService()
{
	int choose;
	choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "请输入：" << endl;
		cout << "0返回主界面" << endl;
		cout << "1根据作者id查询书籍" << endl;
		choose = GetIntFromCin();
		switch (choose)
		{
		case 0:return;
		case 1:
			int authorId;
			authorId = 1;
			while (authorId)
			{
				cout << endl;
				cout << "请输入作者id 输入0返回作者查询操作主界面" << endl;
				authorId = GetIntFromCin();
				if (authorId == 0)
				{
					break;
				}
				if (authorId == -1) {
					cout << "输入不合要求" << endl;
					continue;
				}

				list<Book> bookList = getBooksByAuthor(authorId);
				if (bookList.size() == 0)
				{
					cout << endl;
					cout << "不存在该作者id！" << endl;
					continue;
				}
				showBooksInfo(bookList);
			}
			break;
		default:
			cout << endl;
			cout << "请正确输入选项！" << endl;
			continue;
		}
	}
}
