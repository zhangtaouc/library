#include"stdafx.h"
#include"BorrowHistoryFunc.h"
#include<fstream>
/**
* 添加借阅记录
* 借阅记录的id是自增的
* @param borrowHistory
* @return
*/
bool addHistory(BorrowHistory& borrowHistory) {
	fstream fs;
	fs.open("borrowHistory.bat", ios::out | ios::in | ios::binary);
	//以追加的形式打开一个已经存在的文件进行读写操作(文件指针在文件末尾)
	if (!fs) {
		//cout << "In function addHistory ..." << endl;
		cout << " Error in open file  borrowHistory .bat. " << endl;
		return false;
	}
	//由于不同种类的书籍的id是自增的，刚开始需要让文件指针指向
	//最后一条记录，然后获得最后一类书的id,加1就得到新书的id
	fs.seekg(0, ios::end);
	int newId;
	streamoff len = fs.tellg();
	if (len < sizeof(BorrowHistory))  newId = 1;//这是文件里一条记录也没有的情况
	else {//注意这里  sizeof(BorrowHistory) 是无符号数，不能直接对其加符号
		int recordLen = sizeof(BorrowHistory);
		fs.seekg(-recordLen, ios::end); //定位到最后一条记录的开始处

		char* buffer = new char[sizeof(BorrowHistory)];
		fs.read(buffer, sizeof(BorrowHistory));//读取最后一条图书记录

		BorrowHistory* lastRecord = (BorrowHistory*)buffer;//将读到的数据强制类型转换

		newId = (*lastRecord).id + 1;//得到要新增的书的id并完成赋值
	}
	borrowHistory.id = newId;

	//然后再将文件指针定位到末尾，写一条新书的记录
	fs.seekg(0, ios::end);
	fs.write((char*)&borrowHistory, sizeof(BorrowHistory));
	//关闭文件读写流
	fs.close();
	return true;

}

/**
* 根据借阅记录id删除借阅记录（假删除）
* @param borrowHistoryId
* @return
* 如果id不存在，函数返回false
* 否则，假删除成功后返回true
*/
bool deleteHistory(int id) {
	/*先查找该id是否存在，如果不存在直接返回false*/
	list<BorrowHistory> bList = getHistoryById(id, 0);
	if (bList.empty()) return false;

	/*假如id存在，修改这条记录的exist属性，再写入原来的位置即可*/
	list<BorrowHistory>::iterator borrowHistory = bList.begin();
	if ((*borrowHistory).exist == 0) return true;

	(*borrowHistory).exist = 0;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("borrowHistory.bat", ios::out | ios::binary | ios::in | ios::ate);
	//打开一个已存在的文件读,并让文件指针指向最后

	if (!fs) {
		cout << " Error in open file borrowHistory.bat. " << endl;
		return false;
	}
	/*现在文件指针在文件末尾*/
	/*通过record的id号来计算文件指针偏移量*/
	long pos = sizeof(BorrowHistory) * ((*borrowHistory).id - 1);

	fs.seekg(pos, ios::beg);//定位到要修改的记录处
	fs.write((char*)&(*borrowHistory), sizeof(BorrowHistory));//修改记录

	fs.close();
	return true;
}


/**
* 通过读者id查询借阅记录
* 如果exist属性为1，则只查找未假删除的借阅历史（读者查阅）
* 否则，查找所有借阅历史（管理员查阅）
*/
list<BorrowHistory> getHistoryByReaderId(int readerId, int exist) {
	list<BorrowHistory> borrowHistoryList;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("borrowHistory.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		//cout << "In function getHistoryByReaderId ..." << endl;
		cout << " Error in open file borrowHistory.bat " << endl;
		return borrowHistoryList;
	}
	//把指针移到文件末尾以获取文件长度
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//获取文件长度
							   //定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowHistory)];//用来读取一条记录的缓冲区
	BorrowHistory borrowHistory;
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowHistory));//读出记录
		borrowHistory = *((BorrowHistory*)buffer);
		if (exist == 1) {
			if (borrowHistory.exist == 0) continue;
			//只查找未假删除的借阅历史时，如果当前书籍不存在，直接找下一条记录!!!!!!!!
		}//当exist为0时查找范围是全部借阅历史
		if (borrowHistory.readerId == readerId)
			borrowHistoryList.push_back(borrowHistory);//符合条件则加入列表
	}
	delete[](buffer);
	fs.close();
	return borrowHistoryList;

}

/**
* 通过书籍id(这里的参数bookId是一类图书的共同id)查询借阅记录
*
* 如果exist属性为1，则只查找未假删除的借阅历史（读者查阅）
* 是0，查找所有借阅历史（管理员查阅）
* @return
*/
list<BorrowHistory> getHistoryByBooksId(int bookId, int exist) {
	list<BorrowHistory> borrowHistoryList;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("borrowHistory.bat", ios::binary | ios::in | ios::app);
	//打开一个已存在的文件读
	//把指针移到文件末尾以获取文件长度
	if (!fs) {
		//cout << "In function getHistoryByBookId ..." << endl;
		cout << " Error in open file borrowHistory.bat " << endl;
		return borrowHistoryList;
	}

	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//获取文件长度
							   //定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowHistory)];//用来读取一条记录的缓冲区
	BorrowHistory borrowHistory;
	int bId; //用来缓存获取的BookId
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowHistory));//读出记录
		borrowHistory = *((BorrowHistory*)buffer);
		if (exist == 1) {
			if (borrowHistory.exist == 0) continue;
			//只查找未假删除的借阅历史时，如果当前记录被假删除了，直接找下一条记录!!!!!!!!
		}
		//exist为0时，查询所有借阅历史

		//由于每个图书的唯一编号是：
		//前五位是其类别id，后2位是第几本书，因此这里通过对bookId整除100就可以
		//得到这本书所属书类的id

		bId = borrowHistory.bookId;
		if (bId == bookId)
			borrowHistoryList.push_back(borrowHistory);//匹配则加入list

	}
	delete[](buffer);
	fs.close();
	return borrowHistoryList;
}

/**
* 返回所有的借阅记录
* 如果exist属性为1，则只查找未假删除的借阅历史（读者查阅）
* 为0，查找所有借阅历史（管理员查阅）
* @return
*/
list<BorrowHistory> getAllHistory(int exist) {
	list<BorrowHistory> borrowHistoryList;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("borrowHistory.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		cout << " Error in open file borrowHistory.bat " << endl;
		return borrowHistoryList;
	}
	//把指针移到文件末尾以获取文件长度
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//获取文件长度
							   //定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowHistory)];//用来读取一条记录的缓冲区
	BorrowHistory borrowHistory;
	/*当文件还未结束时，继续遍历文件*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowHistory));//读出记录
		borrowHistory = *((BorrowHistory*)buffer);
		if (exist == 1) {
			if (borrowHistory.exist == 0) continue;
			//只查找未假删除的借阅历史时，如果当前记录被假删除了，直接找下一条记录!!!!!!!!
		}
		//exist为0时，查询所有借阅历史
		borrowHistoryList.push_back(borrowHistory);
	}
	delete[](buffer);
	fs.close();
	return borrowHistoryList;
}




/*通过历史记录的id查找记录
exist为1 ，则查找的在未被删除的历史记录中查找
exist为0则在所有历史记录中查找*/
list<BorrowHistory> getHistoryById(int id, int exist) {
	list<BorrowHistory> borrowHistoryList;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("borrowHistory.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		cout << " Error in open file borrowHistory.bat " << endl;
		return borrowHistoryList;
	}
	//把指针移到文件末尾以获取文件长度
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//获取文件长度
							   //定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowHistory)];//用来读取一条记录的缓冲区
	BorrowHistory borrowHistory;
	/*当文件还未结束时，继续遍历文件*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowHistory));//读出记录
		borrowHistory = *((BorrowHistory*)buffer);
		if (exist == 1) {
			if (borrowHistory.exist == 0) continue;
			//只查找未假删除的借阅历史时，如果当前记录被假删除了，直接找下一条记录!!!!!!!!
		}
		//exist为0时，查询所有借阅历史
		if (borrowHistory.id == id) {
			borrowHistoryList.push_back(borrowHistory);
			break;
		}
	}
	delete[](buffer);
	fs.close();
	return borrowHistoryList;
}

/*
int main() {
BorrowHistory h;
h.id = 1;
h.bookId = 3;
h.borrowTime = time(NULL);
h.exist = 0;
h.returnTime = time(NULL);

addHistory(h);

list<BorrowHistory> l;
l = getHistoryByBooksId(3,0);

l.clear();
l = getHistoryByBooksId(3,1);

l.clear();
l = getHistoryById(1,0);


deleteHistory(h);
l.clear();
l = getHistoryById(1, 1);
return 1;





}*/