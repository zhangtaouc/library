#include "stdafx.h"
#include"Structs.h"
#include<string>
#include"BookFunc.h"
#include"showInfo.h"
#include <array>
#include <unordered_set>
#include"Operation.h"
#include"BorrowRecordFunc.h"
#include"BorrowHistoryFunc.h"
#include"DealFault.h"
#include<sstream>
#define MaxTypeAmount 10//每本书最多有10种类别
#define MaxAuthorAmount 10//每本书最多记录十个主要作者
#define MaxFine 20 //最大欠款金额，如果读者的欠款超过这个数目，就不能继续借书了
using namespace std;



//(readerId是当前登录的读者的id号，主函数会将这个id传给这个service)
/*借书的Service*/
void BorrowBookService(int readerId) {

	//先得到当前读者的所有在借书籍，判断是否有逾期书籍
	//如果有，禁止当前读者借书
	list<BorrowRecord> r = getRecordsByReaderId(readerId);
	for (list<BorrowRecord>::iterator it = r.begin(); it != r.end(); it++) {
		//逾期书籍的标志是，应还书时间小于当前时间
		if ((*it).rationalTime < time(NULL)) {//还有点问题
											  //如果这本书我是1.2日下午四点借的，理应归还时间是2.2下午四点之前，那我在2.2号三点的
											  //时候还是可以借书的。这样合理吗？是应该以每天0：00作为当天所有到期记录的理应归还时间
											  //还是按照前一种思路呢
			cout << endl <<"您还有逾期书籍未归还，不能借书!请归还书籍后继续借书。借书界面退出！" << endl;
			return;
		}
	}

	if (r.size() >= maxBorrowNum) {
		cout << endl << "您已经借了" << r.size() << "本书籍！达到借书上限！借书界面退出！" << endl;
		return;
	}
	r.clear();//释放存储空间

	//欠款达到某个数值也不能继续借书
	list<Reader> reader = getReaderById(readerId);
	list<Reader>::iterator it = reader.begin();
	if ((*it).fine > MaxFine) {
		cout << endl <<"您的欠款金额已超过20元！请缴纳欠款后继续借书!借书界面退出！" << endl;
		return;
	}



	 //接下来让读者输入要借的书籍类的id

	int id;
	list<Book> book;

	cout << endl << "您有下列选择：" << endl;
	string select;
	cout << endl << "1.开始借书" << endl;
	cout << "2.退出借书界面" << endl;
	cout << "请输入选项：";
	getline(cin, select);
	trimAllSpace(select);

	while (select != "1" && select != "2") {
		cout << "只能输入选项1或2！" << endl;

		cout << endl << "1.开始借书" << endl;
		cout << "2.退出借书界面" << endl;
		cout << "请输入选项：";
		getline(cin, select);
		trimAllSpace(select);
	}

	if (select == "2") return;

		cout << endl << "请输入您要借的书籍类的id:" << endl;
		id = GetIntFromCin();
		if (id <= 0) {
			cout << "您输入的书籍id号格式有误！" << endl;
			return;
		}

		book = getBookById(id);
		if (book.empty()) {//输入的书籍不存在，要求重新输入
			cout << endl << "您输入的书籍id不存在！" << endl;
			return;
		}
		else {//如果书籍存在，判断该书籍馆藏数量是否大于1
			  //不管是否可以借书，要想用户展示这个书籍信息
			cout << endl << "该书籍信息如下所示：" << endl;
			showBooksInfo(book);

			list<Book>::iterator b = book.begin();
			if ((*b).numberInLib <= 1) {
				cout << endl << "该书籍馆藏数量不足,您不可以借阅该书！" << endl;
				return;//让读者重新输入一个书籍id
			}
			else {//馆藏数量足够的情况下，让读者确认后再进行借书操作

				string bor;
				while (1) {
					cout << endl << "您确认要借阅这本书吗？是请输入1，否请输入0：" << endl;
					getline(cin, bor);
					trimAllSpace(bor);
					if (bor != "1" && bor != "0")
						cout << endl << "您只能输入1或0，请重新输入：" << endl;
					else break;
				}

				if (bor == "1") {
					//只有确认要借书，而且书籍可借，函数才会进行到这里
					//接下来要生成一条借书记录

					BorrowRecord record;
					time_t now = time(NULL);
					if (!setRecordBookId(record, id, now)) {
						cout << "借书记录生成有误！退出借书界面！" << endl;
						return;
					}

					record.readerId = readerId;
					record.startTime = now;
					record.rationalTime = now;
					increaseRationalTimeByConst(record);//设置合理归还时间为：当前时间 + MaxBorrowDay

					if (!addRecord(record)) {
						cout << endl << "借书记录生成有误！退出借书界面！" << endl;
						return;
					}
					//否则说明借书记录生成成功
					//接下来应该让相应图书数量减少1


					list<Book>::iterator b = book.begin();
					(*b).numberInLib--;
					if (!modifyBook(*b)) {
						//如果因为某种原因导致未能成功修改书籍的馆藏数量
						//那就应该删除之前生成的借书记录
						deleteRecord(record.id);
						cout << endl << "借书记录生成有误！退出借书界面！" << endl;
						return;
					}

					//否则图书的馆藏数量减少1成功修改了

					cout << endl << "借书成功！" << endl;
					cout << "您的该条借书记录如下所示：" << endl;
					showBorRecordInfo(getRecordById(record.id), false);
					return;
				}
				//读者确认要借书后，跳出用来进行书籍id输入的循环体,进行文件操作
				else
					return;//否则就返回

			}

		}

}


//先显示当前借阅，让读者输入借书记录的id进行还书，借书记录真删除一条，借阅历史生成一条，馆藏数量增加
void ReturnBookService(int readerId)
{
	int choose = 1;
	list<BorrowRecord> borRecordList = getRecordsByReaderId(readerId);
	list<BorrowRecord>::iterator i;
	string str2;
	while (choose)
	{

		cout << endl;
		cout << "输入0退出还书功能 输入1进行还书操作:" << endl;
		cout << "请输入您的选择" << endl;

		choose = GetIntFromCin();
		if (choose == -1)
		{
			cout << endl;
			cout << "您只能输入0或1，请重新输入" << endl;
			choose = 1;
			continue;
		}
		bool hasDeleted = false;
		int choose2 = 1;
		string bookOnlyId;
		char bookOId[17];
		int choice = 1;
		switch (choose)
		{
		case 0:return;
		case 1:
			if (0)//borRecordList.size() == 0
			{
				cout << endl;
				cout << endl << "您没有要还的书籍！" << endl;
				return;
			}

			//通过输入书籍的唯一id来还书
			cout << endl;
			cout << endl << "请输入要还书籍的唯一id号：";
			while (1)
			{
				choice = 1;
				getline(cin, bookOnlyId);
				if (bookOnlyId.size() != 12) {
					cout << endl << "您输入的id格式不符合，请重新输入:";
					continue;
				}
				strcpy_s(bookOId, bookOnlyId.c_str());
				for (int k = 0; k < 12; k++) {
					if (bookOId[k]<'0' || bookOId[k]>'9') {
						cout << endl << "您输入的id格式不符合，请重新输入:";
						choice = 0;
						continue;
					}
				}
				if (!choice)
					continue;
				break;
			}
			cout << endl << "请重新确认书籍的唯一id:" << bookOnlyId << endl;
			while (1) {
				cout << endl << "确认还书请输入1，否则请输入0：" << endl;
				choose2 = GetIntFromCin();
				if (choose2 != 0 && choose2 != 1)
				{
					cout << endl;
					cout << "您只能输入0或者1，请重新输入" << endl;
					continue;
				}
				break;
			}
			if (choose2 == 0) {
				cout << endl;
				cout << "您已成功取消还书操作" << endl;
				choose2 = 1;
				continue;
			}
			//如果不想还书，重新回到函数开头
			//否则继续下面的还书操作

			//还书的逻辑：查找到相应的借书记录后，删除这条借书记录
			//如果这本书是逾期归还，那么还需要对这个读者追加罚款
			//然后生成一条借书历史
			//并且还需要将这个书籍的馆藏数量加一
			cout << "bookOnlyId" << bookOnlyId << endl;
			for (i = borRecordList.begin(); i != borRecordList.end(); i++)
			{
				if (bookOnlyId._Equal(i->bookOnlyId))
				{
					time_t now = time(NULL);
					list<Reader> rList = getReaderById(i->readerId);
					list<Reader>::iterator j;
					if (now > i->rationalTime)
					{
						cout << endl;
						cout << endl << "该书已超期，您将有罚金！" << endl;
						j = rList.begin();
						j->fine += (now - i->rationalTime) / (24 * 3600);
					}

					//生成借书历史
					BorrowHistory b;
					b.bookId = i->bookId;
					b.readerId = i->readerId;
					b.borrowTime = i->startTime;
					b.returnTime = now;
					addHistory(b);

					//删除借阅记录
					deleteRecord(i->id);

					//增加书籍数量
					list<Book> book = getBookById(i->bookId);
					list<Book>::iterator bo = book.begin();
					(*bo).numberInLib++;
					modifyBook(*bo);

					hasDeleted = true;
					break;
				}
			}
			bookOnlyId.clear();
			if (!hasDeleted)
			{
				cout << endl;
				cout << endl << "借阅记录中没有对应ID的书籍！,操作失败" << endl;
			}
			else
				cout << endl << "还书成功！" << endl;

			break;

		default:cout << endl << "请正确输入选择！" << endl;
			break;
		}

	}

}

/*续借的Service*/
void RenewBookService(int readerId) {

	//先得到当前读者的所有在借书籍，判断是否有逾期书籍
	//如果有，禁止当前读者续借书籍
	list<BorrowRecord> r = getRecordsByReaderId(readerId);
	for (list<BorrowRecord>::iterator it = r.begin(); it != r.end(); it++) {
		//逾期书籍的标志是，应还书时间小于当前时间
		if ((*it).rationalTime < time(NULL)) {
			cout << endl << "您还有逾期书籍未归还，不能续借书籍!续借界面退出！" << endl;
			return;
		}
	}
	//欠款达到某个数值也不能继续借书
	list<Reader> reader = getReaderById(readerId);
	list<Reader>::iterator it = reader.begin();
	if ((*it).fine > MaxFine) {
		cout << endl << "您的欠款金额已超过20元！请缴纳欠款后继续借书!续借界面退出！" << endl;
		return;
	}



	r.clear();//释放存储空间

	while (1) {
		cout << endl << "请输入您要续借的借书记录id(您也可以输入0以退出续借界面)：" << endl;
		int id;
		cin >> id;
		if (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "您输入的id格式有误！请重新输入！" << endl;
			continue;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');//读取输入id后的换行符

		if (id == 0) return;

		//根据用户输入的借书记录查得一条借书记录
		list<BorrowRecord> record = getRecordById(id);
		if (record.empty()) {
			cout << endl << "请输入正确的借书记录id!" << endl;
			continue;
		}

		//需要检查要修改的借书记录是否是当前读者的
		list<BorrowRecord>::iterator it = record.begin();
		if ((*it).readerId != readerId) {
			cout << endl << "请输入正确的借书记录id!" << endl;
			continue;
		}

		int recordId = (*it).id;

		cout << endl << "您的借书信息如下：" << endl;
		showBorRecordInfo(record, false);

		string select;
		while (1) {
			cout << endl << "您确认要续借吗？确认请输入1，否则请输入0：" << endl;
			getline(cin, select);
			if (select == "1" || select == "0")
				break;
			else
				cout << endl << "您只能输入0或1，请重新输入！" << endl;
		}

		if (select == "0") continue;//输入0，则让用户重新输入一条借书记录id

									//否则应该判断该条借书记录是否还可以续借，如果可以的话续借成功
		if (!increaseRationalTimeByConst(*it)) {
			cout << endl << "您已经达到最大续借次数，不能再续借这本书了！" << endl;
			continue;
		}

		if (!modifyRecord(*it)) {
			cout << endl << "续借失败！" << endl;
			return;
		}
		else {
			cout << endl << "续借成功！" << endl;
			cout << endl << "您的该条借阅信息如下所示：" << endl;
			list<BorrowRecord> re = getRecordById(recordId);
			showBorRecordInfo(re, false);
			return;
		}

	}

}