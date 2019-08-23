#include "stdafx.h"
#include "BorrowHistoryFunc.h"
#include"showInfo.h"
#include"BorrowRecordFunc.h"
#include"RecordOperationService.h"
#include<string>
#include"DealFault.h"

using namespace std;


//(展示当前读者所有当前借书记录。
//显示当前借阅书籍，超期图书，罚款金额，
void QueryCurReaderBorRecordService(int readerId) {
	cout << endl;
	list<BorrowRecord> borowRecordList = getRecordsByReaderId(readerId);
	if (borowRecordList.size() == 0) {
		cout << endl << "您当前没有借书记录" << endl;
		list<Reader> reader = getReaderById(readerId);
		if (reader.begin()->fine>0)
			cout << "需缴欠款：" << reader.begin()->fine << endl;
		return;
	}
	cout << endl << "您的当前借阅信息如下所示：" << endl;
	//向读者本人不需要展示其基本信息
	showBorRecordInfo(borowRecordList, false);
	list<Reader> reader = getReaderById(readerId);
	if (reader.begin()->fine>0)
		cout << "需缴欠款：" << reader.begin()->fine << endl;
}



//(展示当前读者的所有借阅历史)
void QueryCurReaderBorHistoryService(int readerId)
{

	list<BorrowHistory> borrowHistoryList = getHistoryByReaderId(readerId, 1);
	if (borrowHistoryList.size() == 0) {
		cout << endl << "您当前没有借书历史记录" << endl;
		return;
	}
	cout << endl;
	cout << "您的借书历史如下所示：" << endl;
	showBorHistoryInfo(borrowHistoryList, false);
}

/*(一定要保证登录的读者只能删除自己的借阅历史。
当读者输入一个要删除的借阅历史的id后，要确认这条借阅历史是当前读者的，
才可以执行删除操作)*/
bool DeleteCurReadHistoryService(int id) {
	return deleteHistory(id);
}


