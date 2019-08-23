#include"stdafx.h"
#include"BookOperationService.h"
#include<string>
#include"Operation.h"
#include"QueryBookService.h"
#include"RecordOperationService.h"
#include"DealFault.h"
using namespace std;

//(readerId是当前登录的读者的id号，主函数会将这个id传给这个service)
void BorrowBookServlet(int readerId) {
	while (1) {
		
		cout << endl << "欢迎来到借阅书籍界面！" << endl << endl;

		int select = 2;
		cout << "您可以选择：" << endl;
		cout << "1.在您知道要借书籍的id的情况下，您可以直接输入一个书籍id以借阅书籍。" << endl;
		cout << "2.您可以先进入查询书籍界面，查询您要借阅的书籍信息。" << endl;
		cout << "3.退出借阅书籍界面。" << endl;
		select = GetIntFromCin();

		//选择不同功能
		switch (select) {
			case 2 :
			QueryBookService();
			case 1:	
			BorrowBookService(readerId); break;
			case 3:break;
			default:
				cout << "输入的选项有误！" << endl;
				continue;
		}

		//退出界面确认
		while (1) {
			cout << endl << "您确认退出借书界面吗？如果是请输入1，否则请输入0:" << endl;
			select = GetIntFromCin();

			switch (select) {
			case 1: return;//收入1则退出界面
			case 0:break;
			default:
				cout << "只能输入0或1！" << endl;
				continue;
			}
			break;//如果输入1会跳到这里，下次继续进入借书界面
		}

	}
}


//先显示当前借阅，让读者输入借书记录的id进行还书，借书记录真删除一条，借阅历史生成一条，馆藏数量增加
void ReturnBookServlet(int readerId)
{
	QueryCurReaderBorRecordService(readerId);
	ReturnBookService(readerId);
}


/*续借的Servlet*/
void RenewBookServlet(int readerId) {
	while (1) {
		////展示当前读者所有当前借书记录。
		//显示当前借阅书籍，超期图书，罚款金额，
		QueryCurReaderBorRecordService(readerId);

		RenewBookService(readerId);

		string select;
		while (1) {
			cout << endl << "您还想续借书籍吗？如果是请输入1，否则请输入0以退出:" << endl;
			getline(cin, select);
			trimAllSpace(select);
			if (select == "1" || select == "0")
				break;
			else
				cout << "只能输入0或1，请重新输入！" << endl;
		}
		if (select == "0") return;
	}

}


