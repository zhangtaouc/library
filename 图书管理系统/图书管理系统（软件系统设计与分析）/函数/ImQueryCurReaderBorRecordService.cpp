#include "stdafx.h"
#include "QueryCurReaderBorRecordService.h"
#include "BorrowHistoryFunc.h"
using namespace std;
void QueryCurReaderBorRecordService(int readerId) {
	cout << endl;
	list<BorrowRecord> borowRecordList = getRecordsByReaderId(readerId);
	showBorrowRecordInfo(borowRecordList);
	list<Reader> reader = getReaderById(readerId);
	cout << "Ðè½ÉÇ·¿î£º" << reader.begin()->fine << endl;
}