#include "stdafx.h"
#include "ReturnBookService.h"
#include <string.h>
using namespace std;
void ReturnBookService(int readerId)
{
	int choose =1;
	list<BorrowRecord> borRecordList = getRecordsByReaderId(readerId);
	list<BorrowRecord>::iterator i;
	while (choose)
	{
		
		cout << endl;
		cout << "输入0退出还书功能 输入1进行还书操作" << endl;
		cout << "请输入您的选择" << endl;
		int bookId;
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
		case 0:break;
		case 1:
			if (borRecordList.size() == 0)
			{
				cout << endl;
				cout << "您没有要还的书籍！" << endl;
				return;
			}
			cout << endl;
			cout << "请输入要还书籍的id号：";
			cin >> bookId;
			if (!cin)            //条件可改写为cin.fail() 
			{
				cout << endl;
				cout << "输入有错!请重新输入" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			for (i = borRecordList.begin(); i != borRecordList.end(); i++)
			{
				if (bookId == i->bookId)
				{
					time_t now = time(NULL);
					list<Reader> rList = getReaderById(i->readerId);
					list<Reader>::iterator j;
					if (now > i->rationalTime)
					{
						cout << endl;
						cout << "该书已超期" << endl;
						j = rList.begin();
						j->fine += (now - i->rationalTime) / (24 * 3600);
					}
					BorrowHistory b;
					b.bookId = i->bookId;
					b.readerId = i->readerId;
					b.borrowTime = i->startTime;
					b.returnTime = now;
					addHistory(b);
					deleteRecord(i->id);
					break;
				}
			}
			if (i == borRecordList.end())
			{
				cout << endl;
				cout << "借阅记录中没有对应ID的书籍！,操作失败" << endl;
			}
			break;
		default:cout << endl << "请正确输入选择！" << endl;break;
		}
	

	}
	
}