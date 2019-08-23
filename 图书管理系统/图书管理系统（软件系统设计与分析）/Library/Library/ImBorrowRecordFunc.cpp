#include"stdafx.h"
#include"BorrowRecordFunc.h"
#include<fstream>
#include"showInfo.h"
#include"BookOperationServlet.h"



/**
* 添加记录到借书表中
* 记录的id是自增的，需要将文件指针定为到末尾读取最后一条记录的id
* @param borrowRecord
* @return
*/
bool addRecord(BorrowRecord& borrowRecord) {
	fstream fs;
	fs.open("borrowRecord.bat", ios::out | ios::in | ios::binary);
	//以追加的形式打开一个已经存在的文件进行读写操作(文件指针在文件末尾)
	if (!fs) {
		cout << " Error in open file borrowRecord.bat. " << endl;
		return false;
	}
	
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(BorrowRecord))  newId = 1;//这是文件里一条记录也没有的情况
	else {//注意这里  sizeof(BorrowRecord) 是无符号数，不能直接对其加符号
		int recordLen = sizeof(BorrowRecord);
		fs.seekg(-recordLen, ios::end); //定位到最后一条记录的开始处

		char* buffer = new char[sizeof(BorrowRecord)];
		fs.read(buffer, sizeof(BorrowRecord));//读取最后一条记录

		BorrowRecord* lastRecord = (BorrowRecord*)buffer;//将读到的数据强制类型转换

		newId = (*lastRecord).id + 1;//得到要新增的记录的id并完成赋值
	}
	borrowRecord.id = newId;
	//然后再将文件指针定位到末尾，写一条新记录
	fs.seekg(0, ios::end);
	fs.write((char*)&borrowRecord, sizeof(BorrowRecord));

	//关闭文件读写流
	fs.close();
	return true;

}
/*调试成功*/
/**
* 删除记录（真删除的时候参数只有id号即可）
*本来想法是将被删除记录之后之后的每条记录的id都减1
*然后向前移动
*最后对文件进行截断即可
*可是后来发现windows中 c++没有截断文件函数
于是为了真删除就只能重写一个文件了
* @param borrowRecord
* @return
*/
bool deleteRecord(int id) {
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("borrowRecord.bat", ios::out | ios::binary | ios::in);
	//打开一个已存在的文件读,并让文件指针指向最后

	if (!fs) {
		cout << " Error in open file borrowRecord.bat. " << endl;
		return false;
	}
	int count = sizeof(BorrowRecord);
	/*首先要将计算被删除的记录所处位置*/
	streamoff pos = count * (id - 1);
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();
	if (pos < 0 || pos > len) {
		fs.close();
		return false; 
	}//如果要删除记录的id号无效，返回false


	/*否则将剩下的记录都写进list*/
	list<BorrowRecord> recordList;
	fs.seekg(0, ios::beg);

	char* buffer = new char[count];
	streamoff l = fs.tellg();
	/*注意这里未到达文件末尾的判断情况
	有一次调试发现 len不是文件中存放的真实字节数，而是比真实字节数要多
	而后来调试中没有出现这种情况。。见了鬼了*/
	/*这里的判断条件不能是 while(!fs.eof()) 因为当读完文件最后一个字节时,fs.eof()还是
	true，只有再准备读取字节的时候fs.eof()才会是false
	如果这里用了fs.eof()作为条件，就会导致记录多一条...C++这个函数设计的真是...*/
	while (l < len) {//当还未到达文件末尾时继续遍历
		if (fs.tellg() == pos) { 
			fs.seekg(count, ios::cur);
			l = fs.tellg();//!!!!!!!!!!!
			continue;
		}//跳过要删除的记录
		fs.read(buffer, count);//将一条的记录读进buffer
		BorrowRecord record = *((BorrowRecord*)buffer);
		if(fs.tellg() > pos){
			record.id--;//被删除记录之后的记录id号都需减1
		}
		recordList.push_back(record);//要按顺序每次都将记录添加到list的末尾
		l = fs.tellg();
	}

	delete [] buffer;//内存回收！！！
	fs.close();

	/*现在需要删除原来的文件(ios::out)
	新建一个文件，将list里的内容全部写入*/
	fs.open("borrowRecord.bat", ios::out | ios::binary);
	if (!fs) {
		cout << "Open file failure in borrowRecord.bat" << endl;
		return false;
	}

	if (!recordList.empty()) {
		for (list<BorrowRecord>::iterator it = recordList.begin(); it != recordList.end(); ++it) {
			fs.write((char*)&(*it), sizeof(BorrowRecord));//写一条记录
		}
	}

	fs.close();
	return true;
}




/**
* 通过读者id查询借书表信息
* @return
*/
list<BorrowRecord> getRecordsByReaderId(int readerId) {
	list<BorrowRecord> borrowRecordList;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("borrowRecord.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		cout << " Error in open file borrowRecord.bat " << endl;
		return borrowRecordList;
	}
	//把指针移到文件末尾以获取文件长度
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//获取文件长度
	//定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowRecord)];//用来读取一条记录的缓冲区
	BorrowRecord borrowRecord;
	int rId; //用来缓存获取的BookId
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowRecord));//读出记录
		borrowRecord = *((BorrowRecord*)buffer);
		rId = borrowRecord.readerId;
		if (rId == readerId)
			borrowRecordList.push_back(borrowRecord);//匹配则加入list
	}
	delete[](buffer);
	fs.close();
	return borrowRecordList;
}

/**
* 根据书籍id查询借书表信息
* @return
*/
list<BorrowRecord> getRecordByBookId(int bookId) {
	list<BorrowRecord> borrowRecordList;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("borrowRecord.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		cout << " Error in open file borrowRecord.bat " << endl;
		return borrowRecordList;
	}
	//把指针移到文件末尾以获取文件长度
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//获取文件长度
						  //定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowRecord)];//用来读取一条记录的缓冲区
	BorrowRecord borrowRecord;
	int bId; //用来缓存获取的BookId
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowRecord));//读出记录
		borrowRecord = *((BorrowRecord*)buffer);
		bId = borrowRecord.bookId;
		if (bId  == bookId)
			borrowRecordList.push_back(borrowRecord);//匹配则加入list
	}
	delete[](buffer);
	fs.close();
	return	borrowRecordList;
}


//从第几条记录起查询多少条图书记录并返回
//amount = -1代表返回从start开始的所有图书记录
list<BorrowRecord> getRecords(int start, int amount) {
	list<BorrowRecord> BorrowRecordlist;
	if (amount <= 0 && amount != -1) return BorrowRecordlist;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("borrowRecord.bat", ios::out | ios::binary | ios::in | ios::ate);
	//打开一个已存在的文件读,并让文件指针指向最后

	if (!fs) {
		//cout << "In function getBorrowRecordById ..." << endl;
		cout << " Error in open file BorrowRecord.bat. " << endl;
		return BorrowRecordlist;
	}

	/*通过图书的id号来计算文件指针偏移量
	如果计算得到的偏移量大于文件字节长度或者小于0，直接返回空list
	*/
	long pos = sizeof(BorrowRecord) * (start - 1);
	if (pos < 0 || pos > fs.tellg()) {
		fs.close();
		return BorrowRecordlist;
	}
	fs.seekg(0, ios::end);
	streamoff fileLen = fs.tellg();
	streamoff endPos;

	if (amount == -1) endPos = fileLen;
	else endPos = pos + sizeof(BorrowRecord) *  amount;
	endPos = (endPos > fileLen) ? fileLen : endPos;

	fs.seekg(pos, ios::beg);
	char* buffer = new char[sizeof(BorrowRecord)];

	while (fs.tellg() < endPos) {
		fs.read(buffer, sizeof(BorrowRecord));//读出记录-
		BorrowRecord borrowRecord = *((BorrowRecord*)buffer);

			BorrowRecordlist.push_back(borrowRecord);//将记录添加到list末尾
	}
	fs.close();
	delete[] buffer;
	return BorrowRecordlist;
}
/**
* 更改借书表中的借书记录
* 完成续借功能的时候会用到
* @param borrowRecord
* @return
*/
bool modifyRecord(BorrowRecord& borrowRecord) {
	//打开文件borrowRecord.bat时保证文件内容不被删除
	fstream fs("borrowRecord.bat", ios::out | ios::in | ios::ate | ios::binary);
	//判断打开文件borrowRecord.bat是否成功，若无法打开则输出错误信息并返回false
	if (!fs) {
		cout << "Error: Can not open file 'borrowRecord.bat'!" << endl;
		fs.close();
		return false;
	}
	//通过id计算文件指针偏移量以读取指定内容
	long pos = sizeof(BorrowRecord) * (borrowRecord.id - 1);
	//判断查找的位置是否正确,若小于0或超出文件长度则输出错误信息并返回false
	if (pos < 0 || pos > fs.tellg()) {
		cout << "Error: Input BorrowRecord ID mistaken!" << endl;
		fs.close();
		return false;
	}
	//读取指定位置的内容
	BorrowRecord* rBorrowRecord;
	char* buffer = new char[sizeof(BorrowRecord)];
	fs.seekg(pos, ios::beg);
	fs.read(buffer, sizeof(BorrowRecord));
	rBorrowRecord = (BorrowRecord*)buffer;
	//比较文件内查找到的rBorrowRecord.id与所需要修改的borrowRecord.id是否相同，相同则进行文件内容修改，不相同则输出错误信息并返回false
	if (rBorrowRecord->id == borrowRecord.id) {
		fs.seekp(pos, ios::beg);
		fs.write((char *)&borrowRecord, sizeof(BorrowRecord));
		//cout << "Modify BorrowRecord success!" << endl;
		fs.close();
		delete[] buffer;
		return true;
	}
	else {
		cout << "Error: Modify BorrowRecord ID mismatch!" << endl;
		fs.close();
		delete[] buffer;
		return false;
	}
	
}



/*
通过记录的id号查询得到记录信息*/
list<BorrowRecord> getRecordById(int id) {
	list<BorrowRecord> borrowRecordList;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("borrowRecord.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		cout << " Error in open file borrowRecord.bat " << endl;
		return borrowRecordList;
	}
	//把指针移到文件末尾以获取文件长度
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//获取文件长度
						  //定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(BorrowRecord)];//用来读取一条记录的缓冲区
	BorrowRecord borrowRecord;
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(BorrowRecord));//读出记录
		borrowRecord = *((BorrowRecord*)buffer);
		if (borrowRecord.id == id){
			borrowRecordList.push_back(borrowRecord);//匹配则加入list
			break;
		}
	}
	delete[](buffer);
	fs.close();
	return borrowRecordList;

}





//该函数的功能是：返回一个time_t型变量
//其表示的是time+day天的时间
//day是大于0时，将返回time之后的时间
//小于0将返回time之前的时间
//否则该函数将直接返回time
time_t addDayToTime(time_t time, int day) {
	if (day == 0) return time;
	else {
		//先将time_t型变量转换为tm结构体变量，将其日期加day天
		tm t;
		int err = localtime_s(&t, &time);
		if (err) return time; //如果转换出错，直接返回time
		t.tm_mday += day;

		//然后再将这个结构体转换成time_t变量并返回就可以了
		return mktime(&t);
	}

}


//下面是生成一条逾期记录的函数(用于测试),overDay是设置的逾期天数,这个数字要大于0
//如果小于0会取其绝对值
void addExtendRecord(int readerId, int bookId,int overdueDay) {

	//如果读者id和书籍id有任意一个不合法，该函数就直接返回
	list<Book> book = getBookById(bookId);
	if (book.empty()) {
		cout << "当前书籍不存在，无法生成逾期记录！函数退出！" << endl;
		return; }
	list<Book>::iterator it1 = book.begin();
	if ((*it1).numberInLib <= 1) {
		cout << "当前书籍库存量不足，不能生成逾期记录，函数退出!" << endl;
		return;
	}
	//如果当前书籍的数量小于1，不能借该本书

	//如果当前读者不存在，直接返回
	list<Reader> reader = getReaderById(readerId);
	if (reader.empty()) { 
		cout << "当前读者不存在，无法生成逾期记录！函数退出！" << endl;
		return; 
	}

	//如果当前作者借的书的个数大于最多借书个数就不能生成一条逾期记录
	list<BorrowRecord> r = getRecordsByReaderId(readerId);
	if (r.size() >= maxBorrowNum)
	{
		cout << "当前读者借的书籍数量达到了最大借书数量，不能继续生成逾期记录！函数退出！" << endl;
		return;
	}


	//就相当于先 生成一条逾期记录，再将相应书籍的馆藏数量减1

	BorrowRecord record;
	record.bookId = bookId;
	time_t now = time(NULL);

	int day = overdueDay >= 0 ? -overdueDay : overdueDay;

	time_t RationalTime = addDayToTime(now, day);
	time_t startTime = addDayToTime(RationalTime, -maxBorrowDay);
	record.startTime = startTime;
	record.rationalTime = RationalTime;
	setRecordBookId(record, bookId, startTime);
	record.readerId = readerId;

	addRecord(record);
	
	list<Book>::iterator it = book.begin();
	Book b = (*it);
	b.numberInLib--;

	modifyBook(b);

	cout << "逾期记录已成功生成！展示如下：" << endl;

	list<BorrowRecord> re = getRecordById(record.id);
	showBorRecordInfo(re,true);

	cout << "函数退出！" << endl;
	return;

}



/*
int main() {
	
	/*
	BorrowRecord br;
	br.readerId = 1;
	br.startTime = time(NULL);
	br.rationalTime = time(NULL);
	setRecordBookId(br, 1, br.startTime);
	addRecord(br);
	*/

	/*
	list<BorrowRecord> records;
	records = getRecordById(1);
	showBorRecordInfo(records,true);

	if (deleteRecord(1)) cout << "delete success!" << endl;
	
	list<BorrowRecord> record;
	record = getRecordById(1);
	showBorRecordInfo(record, true);
	*/
/*
	addExtendRecord(1, 2,21);

	int i;
	cin >> i;
	
	cout << endl;


	
	
	
	
	return 1;

}*/

/*
int main() {

	//BorrowBookServlet(1);
	
	
	while (1) {
		int i; 
		cout << "id:";
		cin >> i;

		list<BorrowRecord> records = getAllRecords();
		showBorRecordInfo(records, 1);

		cout << endl << "删除后：" << endl;
		deleteRecord(i);
		records.clear();
		records = getAllRecords();
		showBorRecordInfo(records, 1);

	}
	

	int i;
	cin >> i;
	return 1;
}*/