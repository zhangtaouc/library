#include "stdafx.h"
#include "QueryBooksByAuthorService.h"
#include "string"
#include "showInfo.h"

void QueryBooksByAuthorService()
{
	 int choose;
	 choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "输入0返回主界面 输入1根据作者id查询书籍" << endl;
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
				cin >> authorId;
				if (!cin)            //条件可改写为cin.fail() 
				{
					cout << endl;
					cout << "输入有错!请重新输入" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					authorId = 1;
					continue;
				}
				if(authorId == 0)
				{
					break;
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
