
#include "stdafx.h"
#include "QueryCurReaderBorHistoryService.h"
using namespace std;
void QueryCurReaderBorHistoryService(int readerId)
{
	cout << endl;
	list<BorrowHistory> borrowHistoryList = getHistoryByReaderId(readerId, 1);
	if(borrowHistoryList.size()==0)
	{
		cout << "当前用户没有在借的书籍" << endl;
	}
	else 
		showBorrowHistoryInfo(borrowHistoryList);
}