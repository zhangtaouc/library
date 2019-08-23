

#include"stdafx.h"
//借阅记录和借阅历史管理
#include<iostream>
#include"BorrowHistoryFunc.h"
#include"BookFunc.h"
#include "ReaderFunc.h"
#include"showInfo.h"
#include <list>
#include "Structs.h"
#include "BorrowRecordFunc.h"
#include"DealFault.h"

using namespace std;


void QueryBorrowHistoryService() {

	list<BorrowHistory> borrowHistoryList;

	int bookId;
	int readerId;
	int choice;

	for (;;) {
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "请输入选择读者id查询还是书的id查询" << endl;
		cout << endl;
		cout << "1.查询读者借阅历史" << endl;
		cout << "2.查询某类书的借阅历史" << endl;
		cout << "3.查询所有借阅历史" << endl;
		while (1)
		{
			cout << endl;
			cout << "请输入查询方式：";
			//cin >> choice;
			/*在这里把自己写的int型输入的语句注释掉，
			并且让这个数据choose直接等于函数的返回值，
			如果输入数据不符合要求就返回-1，否则返回输入的数*/

			choice = GetIntFromCin();
			break;
		}
		while (choice != 2 && choice != 1 && choice != 3) {
			while (1)
			{
				cout << endl;
				cout << "您只能输入1或2或3，请重新输入:";
				choice = GetIntFromCin();
				break;
			}
		}

		if (choice == 1) {
			while (1)
			{
				cout << endl;
				cout << "请输入读者的id：";
				readerId = GetIntFromCin();
				if (readerId < 0) {
					cout << endl;
					cout << "输入的数据格式错误！" << endl;
					continue;
				}
				break;
			}

			if (getReaderById(readerId).empty()) {
				cout << endl;
				cout << "无对应该ID的读者" << endl;
				return;
			}
			borrowHistoryList = getHistoryByReaderId(readerId, 1);
			if (borrowHistoryList.empty()) {
				cout << endl;
				cout << "查询借阅历史为空" << endl;
				return;
			}
			showBorHistoryInfo(borrowHistoryList, 1);
		}
		else if(choice == 2){
			while (1)
			{
				cout << endl;
				cout << "请输入书的id：";
				bookId = GetIntFromCin();
				if (bookId < 0) {
					cout << endl;
					cout << "输入的数据格式错误！" << endl;
					continue;
				}
				break;
			}
			if (getBookById(bookId).empty()) {
				cout << endl;
				cout << "无对应该ID的书" << endl;
				return;
			}
			borrowHistoryList = getHistoryByBooksId(bookId, 1);
			if (borrowHistoryList.empty()) {
				cout << endl;
				cout << "查询借阅历史为空" << endl;
				return;
			}
			showBorHistoryInfo(borrowHistoryList, 1);
		}
		else {
			list<BorrowHistory> his = getAllHistory(0);
			showBorHistoryInfo(his, true);
		}
		return;
	}
}



void QueryRecord() {

	int select;
	while (1) {
		cout << "您想要查看所有记录还是按照分页查看记录?" << endl;
		cout << "1.查看所有记录" << endl;
		cout << "2.按照分页查看记录" << endl;
		cout << "请输入选项：";
		select = GetIntFromCin();
		switch (select)
		{
		case 1:break;
		case 2:break;
		default:
			cout << "只能输入1或2！" << endl;
			continue;
		}
		break;
	}

	int i = 1;
	int start = 1;
	list<BorrowRecord> Recordlist;
	switch (select)
	{
	case 1:
		Recordlist = getRecords(1);
		showBorRecordInfo(Recordlist,true);
		break;
	case 2:
		while (1) {
			Recordlist.clear();
			Recordlist = getRecords(start, 5);//每页展示5本书
			if (Recordlist.empty()) {
				cout << "已经到达记录末尾页！" << endl;
				break;
			}

			cout << endl << endl << "第" << i << "页记录信息如下所示：" << endl;
			showBorRecordInfo(Recordlist,true);
			start = start + 5;
			i++;
			while (1) {
				cout << endl << "您是否还要查看更多记录？是请输入1，否请输入0" << endl;

				cout << "请输入选项：";
				select = GetIntFromCin();
				switch (select)
				{
				case 1:break;
				case 2:break;
				default:
					cout << "只能输入1或2！" << endl;
					continue;
				}
				break;
			}
			switch (select)
			{
			case 1:continue;//继续展示信息
			case 2:break;
			}
			break;
		}
		break;
	}

}


void QueryBorrowRecordService() {
	int choose;
	choose = 1;
	while (choose)
	{
		cout << endl;
		cout << "请输入：" << endl;
		cout << "0:返回主界面" << endl;
		cout << "1:根据书籍id查询借阅记录" << endl;
		cout << "2:根据读者id查询借阅记录" << endl;
		cout << "3.查询所有借阅记录" << endl;
		choose = GetIntFromCin();
		switch (choose)
		{
		case 0:
			return;
		case 1:
			int bookId;
			bookId = 1;
			while (bookId)
			{
				int bookId;
				cout << endl;
				cout << "请输入书籍id号 输入0返回借阅记录查询主界面" << endl;
				bookId = GetIntFromCin();
				if (bookId == 0)
				{
					break;
				}
				if (bookId == -1) {
					cout << "输入不合要求" << endl;
					continue;
				}

				list<Book> bookList = getBookById(bookId);
				if (bookList.size() == 0)
				{
					cout << endl;
					cout << "不存在该书籍id!" << endl;
					continue;
				}
				list<BorrowRecord> borrowRecord = getRecordByBookId(bookId);
				if (borrowRecord.size() == 0)
				{
					cout << endl;
					cout << "该书籍当前没有被借阅" << endl;
					continue;
				}
				showBorRecordInfo(borrowRecord, true);
			}
			break;
		case 2:
			int readerId;
			readerId = 1;
			while (readerId)
			{
				cout << endl;
				cout << "请输入读者id号，输入0返回借阅记录查询主界面" << endl;
				readerId = GetIntFromCin();
				if (readerId == 0)
				{
					break;
				}
				if (readerId == -1) {
					cout << "输入不合要求" << endl;
					continue;
				}

				list<Reader> readerList = getReaderById(readerId);
				if (readerList.size() == 0)
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
				showBorRecordInfo(borrowRecord, true);
			}
			break;
		case 3:
			QueryRecord();
			break;
		default:
			cout << endl;
			cout << "请正确输入选项！" << endl;
			break;
		}
	}

}

void QueryExtendedBookService() {

	list<BorrowRecord> recordList;//根据读者id或者书的id查询出的列表
	list<BorrowRecord> extendedRecordList;//逾期记录的列表
	int bookId;
	int readerId;
	int choice;

	for (;;) {
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "请选择读者id查询还是书的id查询" << endl;
		cout << endl;
		cout << "1.查询读者借阅历史" << endl;
		cout << "2.查询某类书的借阅历史" << endl;
		while (1)
		{
			cout << endl;
			cout << "请输入查询方式：";
			choice = GetIntFromCin();
			break;
		}

		//判断输入的是否为0或1
		while (choice != 2 && choice != 1)
		{
			while (1)
			{
				cout << endl;
				cout << "您只能输入1或2，请重新输入:";
				choice = GetIntFromCin();
				break;
			}
		}

		time_t now = time(NULL);//用来比较是否逾期

								//根据读者id查询
		if (choice == 1) {
			while (1)
			{
				cout << endl;
				cout << "请输入读者的id：";
				readerId = GetIntFromCin();
				if (readerId < 0) {
					cout << endl;
					cout << "输入的书籍格式错误！" << endl;
					continue;
				}
				break;
			}

			if (getReaderById(readerId).empty()) {
				cout << endl;
				cout << "无对应该ID的读者" << endl;
				return;
			}
			recordList = getRecordsByReaderId(readerId);
			if (recordList.empty()) {
				cout << endl;
				cout << "记录为空" << endl;
				return;
			}
			for (list<BorrowRecord>::iterator it = recordList.begin(); it != recordList.end(); it++) {
				if ((*it).rationalTime < now) {
					extendedRecordList.push_back(*it);
				}
			}
			if (extendedRecordList.empty()) {
				cout << endl;
				cout << "查询的超期借阅记录为空" << endl;
				return;
			}
			showBorRecordInfo(extendedRecordList, true);
		}

		else {
			while (1)
			{
				cout << endl;
				cout << "请输入书的id：";
				bookId = GetIntFromCin();
				if (bookId < 0) {
					cout << endl;
					cout << "输入数据格式错误！" << endl;
					continue;
				}
				break;
			}

			if (getBookById(bookId).empty()) {
				cout << endl;
				cout << "无对应该ID的书" << endl;
				return;
			}
			recordList = getRecordByBookId(bookId);
			if (recordList.empty())
			{
				cout << endl;
				cout << "记录为空" << endl;
				return;
			}
			for (list<BorrowRecord>::iterator it = recordList.begin(); it != recordList.end(); it++) {
				if ((*it).rationalTime < now) {
					extendedRecordList.push_back(*it);
				}
			}
			if (extendedRecordList.empty()) {
				cout << endl;
				cout << "查询的超期借阅记录为空！" << endl;
				return;
			}
			showBorRecordInfo(extendedRecordList, true);
		}
		return;
	}
}

// 删除借阅记录(只用于调试程序, 主函数里不进行调用)
void DeleteBorrowRecordService() {

	int historyId;
	int recordId;
	int choice1;
	for (;;) {
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "请输入选择删除借阅历史还是删除借阅记录" << endl;
		cout << endl;
		cout << "1.删除借阅历史" << endl;
		cout << "2.删除借阅记录" << endl;
		while (1)
		{
			cout << endl;
			cout << "请输入选择：";
			choice1 = GetIntFromCin();
			break;
		}
		while (choice1 != 2 && choice1 != 1) {
			while (1)
			{
				cout << endl;
				cout << "您只能输入1或2！请重新输入：";
				choice1 = GetIntFromCin();
				break;
			}
		}

		if (choice1 == 1) {
			while (1)
			{
				cout << endl;
				cout << "请输入借阅历史id：";
				historyId = GetIntFromCin();
				if (historyId <0) {
					cout << endl;
					cout << "输入数据格式有误！" << endl;
					continue;
				}
				else
				{
					list<BorrowHistory> history = getHistoryById(historyId, 1);
					if (history.empty())
					{
						cout << endl;
						cout << "该借阅历史为空，请选择重新输入或是返回" << endl;
						cout << endl;
						cout << "输入1重新输入" << endl;
						cout << "输入0返回" << endl;
						int choice2;
						while (1) {

							cout << endl;
							cout << "请输入选择：";
							choice2 = GetIntFromCin();
							break;
						}

						while (choice2 != 0 && choice2 != 1) {
							while (1)
							{
								cout << endl;
								choice2 = GetIntFromCin();
								break;
							}
						}
						if (choice2 == 1) {

						}
						else {
							return;
						}
					}
					else {
						list<BorrowHistory>::iterator h = history.begin();
						deleteHistory((*h).id);
						cout << endl;
						cout << "借阅历史已删除！" << endl;
						return;
					}
				}
			}
		}



		else {
			while (1)
			{
				cout << endl;
				cout << "请输入借阅记录id：";
				recordId = GetIntFromCin();
				if (recordId < 0) {
					cout << endl;
					cout << "输入数据格式有误！" << endl;
					continue;
				}
				else
				{
					list<BorrowRecord> record = getRecordById(recordId);
					if (record.empty())
					{
						cout << endl;
						cout << "该借阅历史为空，请选择重新输入或是返回" << endl;
						cout << endl;
						cout << "输入1重新输入" << endl;
						cout << "输入0返回" << endl;
						int choice2;
						while (1)
						{
							cout << endl;
							cout << "请输入选择：";
							choice2 = GetIntFromCin();
							break;
						}
						while (choice2 != 0 && choice2 != 1) {
							while (1)
							{
								cout << endl;
								cout << "您只能输入0或1，请重新输入:";
								choice2 = GetIntFromCin();
								break;
							}
						}
						if (choice2 == 1) {

						}
						else {
							return;
						}
					}
					else {
						deleteRecord(recordId);
						cout << endl;
						cout << "借阅记录已删除！" << endl;
						list<Book> returnbook = getBookById((*record.begin()).bookId);
						((*returnbook.begin())).numberInLib++;
						modifyBook(*returnbook.begin());

						return;
					}
				}
			}
		}
	}
}


