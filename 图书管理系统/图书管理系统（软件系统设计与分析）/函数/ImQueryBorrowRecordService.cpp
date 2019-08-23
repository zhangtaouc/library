#include "stdafx.h"
#include "QueryBorrowRecordService.h"
#include "BookFunc.h"
#include "ReaderFunc.h"
void QueryBorrowRecordService()
{
	int choose;
	choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "输入0返回主界面 输入1根据书籍id查询借阅记录 输入2根据读者id查询借阅记录" << endl;
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
			int bookId;
			bookId = 1;
			while (bookId)
			{
				int bookId;
				cout << endl;
				cout << "请输入书籍id号 输入0返回借阅记录查询主界面" << endl;
				cin >> bookId;
				if (!cin)            //条件可改写为cin.fail() 
				{
					cout << endl;
					cout << "输入有错!请重新输入" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					bookId = 1;
					continue;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if(bookId ==0)
				{
					break;
				}
				list<Book> bookList = getBookById(bookId);
				if(bookList.size() == 0 )
				{
					cout << endl;
					cout << "不存在该书籍id!" << endl;
					continue;
				}
				list<BorrowRecord> borrowRecord = getRecordByBookId(bookId);
				if (borrowRecord.size() ==0)
				{
					cout << endl;
					cout << "该书籍当前没有被借阅" << endl;
					continue;
				}
				showBorrowRecordInfo(borrowRecord);
			}
			break;
		case 2:
			int readerId;
			readerId = 1;
			while (readerId)
			{
				cout << endl;
				cout << "请输入读者id号，输入0返回借阅记录查询主界面" << endl;
				cin >> readerId;
				if (!cin)            //条件可改写为cin.fail() 
				{
					cout << endl;
					cout << "输入有错!请重新输入" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					readerId = 1;
					continue;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if(readerId == 0)
				{
					break;
				}
				list<Reader> readerList = getReaderById(readerId);
				if(readerList.size() ==0)
				{
					cout << endl;
					cout << "不存在该读者！" << endl;
					continue;
				}
				list<BorrowRecord> borrowRecord = getRecordsByReaderId(readerId);
				if (borrowRecord.size() == 0)
				{
					cout << endl;
					cout << "该读者当前没有借阅书籍" << endl;
					continue;
				}
				showBorrowRecordInfo(borrowRecord);
			}
			break;
		default:
			cout << endl;
			cout << "请正确输入选项！" << endl;
			break;
		}
	}
}
