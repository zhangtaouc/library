#include"stdafx.h"

#include"showInfo.h"
#include"Operation.h"
#include<iomanip>
#define MaxAuthorNumPerBook 10
#define MaxTypeNumPerBook 10



//输出书籍信息
void showBooksInfo(list<Book> books) {
	if (books.empty())
		return;
	for (list<Book>::iterator it = books.begin(); it != books.end(); ++it) {
		cout << "Id:" << (*it).id << endl;
		cout << "ISBN: " << (*it).ISBN << endl;
		cout << "书籍名：" << (*it).name << endl;
		cout << "出版社：" << (*it).publisher << endl;
		cout << "作者：";
		list<Author> aus;

		for (int i = 0; i < MaxAuthorNumPerBook; i++) {
			int id = (*it).author[i];
			if (id == 0) break;
			else {
				list<Author> a = getAuthorById(id);
				if (!a.empty()) {
					list<Author>::iterator ait = a.begin();
					aus.push_back(*ait);
				}
			}
		}

		//展示当前图书的作者姓名组成的字符串
		showAuthorInfo(aus, false);

		cout << endl <<"图书所属类别：";
		list<Type> types;
		for (int i = 0; i < MaxTypeNumPerBook; i++) {
			int id = (*it).type[i];
			if (id == 0) break;
			else {
				list<Type> t = getTypeById(id);
				if (!t.empty()) {
					list<Type>::iterator t_it = t.begin();
					types.push_back(*t_it);
				}
			}
		}

		if (types.empty()) cout << "该图书不属于任何类别。" << endl;
		else showTypeInfo(types, false);
		cout << endl;

		cout << "总数量：" << (*it).amount << endl;
		cout << "馆藏数量：" << (*it).numberInLib << endl;
		cout << "**********************************************************" << endl;
	}
}

//输出读者信息(不包括读者登录密码)
void showReaderInfo(list<Reader> readers) {
	if (readers.empty())
		return;

	for (list<Reader>::iterator it = readers.begin(); it != readers.end(); it++) {
		cout << "读者Id:" << (*it).id << endl;
		cout << "姓名：" << (*it).name << endl;
		cout << "性别:";
		if ((*it).sex)
			cout << "男" << endl;
		else
			cout << "女" << endl;

		cout << fixed << showpoint;
		cout << setprecision(2);
		cout << " 欠款金额：" << (*it).fine << endl;
		cout << "**********************************************" << endl;
	}
}

//输出借阅历史
//注意：第二个参数表示是否要展示该条借阅历史的读者信息(包括读者id和读者姓名)
//当读者登录时，向他展示他自己的借阅历史不需要展示读者信息
//但是当管理员查询多个借阅历史的时候需要展示读者信息
void showBorHistoryInfo(list<BorrowHistory> his, bool showReaderInfo) {
	if (his.empty())
		return;

	for (list<BorrowHistory>::iterator it = his.begin(); it != his.end(); it++) {
		cout << "借阅历史Id:" << (*it).id << endl;
		list<Book> books = getBookById((*it).bookId);
		list<Book>::iterator book = books.begin();
		cout << "借阅书籍类id：" << (*it).bookId << endl;
		cout << "借阅图书名：" << (*book).name << endl;

		if (showReaderInfo) {
			list<Reader> readers = getReaderById((*it).readerId);
			list<Reader>::iterator reader = readers.begin();
			cout << "读者id :" << (*reader).id << endl;
			cout << "读者姓名：" << (*reader).name << endl;
		}

		cout << "借阅起始时间：" << getDateStr((*it).borrowTime).data() << endl;
		cout << "还书时间：" << getDateStr((*it).returnTime).data() << endl;
		cout << "**********************************************" << endl;
	}


}


//输出借阅记录
//注意：第二个参数表示是否要展示该条借阅记录的读者信息(包括读者id和读者姓名)
//当读者登录时，向他展示他自己的借阅记录不需要展示读者信息
//但是当管理员查询多个借阅记录的时候需要展示读者信息
void showBorRecordInfo(list<BorrowRecord> records, bool showReaderInfo) {
	if (records.empty())
		return;

	for (list<BorrowRecord>::iterator it = records.begin(); it != records.end(); it++) {
		cout << "借阅记录Id:" << (*it).id << endl;

		cout << "书籍Id:" << (*it).bookOnlyId << endl;
		list<Book> books = getBookById((*it).bookId);

		list<Book>::iterator book = books.begin();
		cout << "借阅图书名：" << (*book).name << endl;

		if (showReaderInfo) {
			list<Reader> readers = getReaderById((*it).readerId);
			list<Reader>::iterator reader = readers.begin();
			cout << "读者id :" << (*reader).id << endl;
			cout << "读者姓名：" << (*reader).name << endl;
		}

		cout << "借阅起始时间：" << getDateStr((*it).startTime).data() << endl;
		cout << "最迟还书时间：" << getDateStr((*it).rationalTime).data() << endl;
		cout << "**********************************************" << endl;
	}

}

//输出作者信息
//如果showId为true，就展示作者Id(此时每条作者的记录信息会用换行符隔开)
//否则就只展示作者姓名(只展示作者姓名时，不需要将作者姓名一行行地分开，只用空格隔开即可，这个会用在展示一本书的多个作者上)
void showAuthorInfo(list<Author> aus, bool showId) {
	if (aus.empty()) return;
	string  c;
	if (showId)  c = "\n";//每条作者的记录信息会用换行符隔开
	else c = "\t";//只展示作者姓名时，不需要将作者姓名一行行地分开，只用空格隔开即可
	for (list<Author>::iterator it = aus.begin(); it != aus.end(); it++) {
		if (showId)
			cout << "作者Id :" << (*it).id << c.data();
		cout << (*it).name << c.data();
		if (showId)
			cout << "*****************" << endl;
	}
	return;
}




//输出类别信息
//如果showId为true，就展示类别Id(此时每条作者的记录信息会用换行符隔开)
//否则就只展示类别名(只展示作者姓名时，不需要将作者姓名一行行地分开，只用空格隔开即可，这个会用在展示一本书的多个类别上)
void showTypeInfo(list<Type> types, bool showId) {
	if (types.empty()) return;
	string  c;
	if (showId)  c = "\n";//每个类别的记录信息会用换行符隔开
	else c = "\t";//只展示类别名时，不需要将其一行行地分开，只用空格隔开即可
	for (list<Type>::iterator it = types.begin(); it != types.end(); it++) {
		if (showId)
			cout << "类别Id :" << (*it).id << c.data();
		cout << (*it).name << c.data();
		if (showId)
			cout << "*****************" << endl;
	}
	return;

}












