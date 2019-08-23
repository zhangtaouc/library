#include"stdafx.h"
#include"RecordOperationService.h"
#include"DealFault.h"
#include"BorrowHistoryFunc.h"
#include<string>

//(展示当前读者所有当前借书记录。
//显示当前借阅书籍，超期图书，罚款金额，
void QueryCurReaderBorRecordServlet(int readerId)
{
	QueryCurReaderBorRecordService(readerId);
}


//(展示当前读者的所有借阅历史)
void QueryCurReaderBorHistoryServlet(int readerId)
{
	QueryCurReaderBorHistoryService(readerId);
}


/*(一定要保证登录的读者只能删除自己的借阅历史。
当读者输入一个要删除的借阅历史的id后，要确认这条借阅历史是当前读者的，
才可以执行删除操作)*/

void DeleteCurReaderHistoryServlet(int readerId) {
	/**
	当用户需要删除借阅历史时，我们规定用户先让用户查看当前借阅历史
	然后输入要删除的借阅历史的id号进行删除
	我们需要向函数传递读者的id号
	exist为1表示存在记录
	成功删除返回true，否则返回false
	*/
	int HistoryId;
	string choice;
	string historyTerm;
	string historyTerm2;
	list<BorrowHistory> borrowHistory;
	list<BorrowHistory>::iterator it;

	while (1) {
		cout << endl << "您当前借阅历史信息为：" << endl;
		QueryCurReaderBorHistoryService(readerId);
		cout << endl << "请输入您要删除的借阅历史信息的id号:" << endl;
		//cin >> historyTerm;
		getline(cin, historyTerm);
		HistoryId = atoi(historyTerm.c_str());
		historyTerm2 = "" + to_string(HistoryId);

		borrowHistory = getHistoryById(HistoryId, 1);
		it = borrowHistory.begin();

		if (historyTerm == historyTerm2 && !borrowHistory.empty() && it->readerId == readerId) {
			if (DeleteCurReadHistoryService(HistoryId)) {
				cout << endl << "删除成功！" << endl;
				cout << "您现在的借阅记录为：" << endl;
				QueryCurReaderBorHistoryService(readerId);
				cout << endl << "请问是否继续执行删除操作" << endl << endl << "1：继续   0：退出" << endl;
				//cin >> choice;
				getline(cin, choice);
				if (choice == "1") {

				}
				else if (choice == "0") 
					return;
				else {
					cout << endl << "您输入的内容不符合要求" << endl;
					if (DealFault() == 1) {

					}
					else
						return;
				}
			}
			else {
				cout << endl << "删除失败" << endl;
				return;
			}
		}
		else {
			cout << endl << "输入id不合法\n" << endl;
			if (DealFault()) {
			}
			else
				return;
		}
	}


}
