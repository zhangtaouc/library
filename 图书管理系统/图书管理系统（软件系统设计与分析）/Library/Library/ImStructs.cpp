#include"stdafx.h"
#include"Structs.h"
#include<sstream>
#include<string>


//Admin
/************************************************************************/
bool setAdminPd(Admin& admin,string pd) {
	return copy(admin.password, pd, sizeof(admin.password));
}


//Author

/************************************************************************/
bool setAuthorName(Author& author, string name) {
	return copy(author.name, name, sizeof(author.name));
}



//Type
/************************************************************************/

bool setTypeName(Type& type, string name) {
	return copy(type.name, name, sizeof(type.name));
}




//Book
/************************************************************************/
/*给name字段设置值
如果name 长度过长，函数不进行设置，直接返回false
*/
bool setBookName(Book& book, string name) {
	return copy(book.name, name, sizeof(book.name));
}

/*设置由作者id组成的整型数组，如果au过长，函数返回false
len 是au数组的长度*/
bool setBookAuthors(Book& book, int* au,unsigned len) {
	return copy(book.author, au, sizeof(book.author) / sizeof(int), len);
}

bool setBookPublisher(Book& book, string pub) {
	return copy(book.publisher, pub, sizeof(book.publisher));
}

/*同author数组的复制*/
bool setBookTypes(Book& book, int* type, unsigned len) {
	return copy(book.type, type, sizeof(book.type) / sizeof(int), len);
}



/*现在不去判断ISBN编码是否符合格式了，只要ISBN不超过13个字符就可以*/
bool setBookISBN(Book& book, string ISBN) {
	return copy(book.ISBN, ISBN, sizeof(book.ISBN));
}



//Reader
/************************************************************************/
bool setReaderName(Reader& reader, string name) {
	return copy(reader.name, name, sizeof(reader.name));
}

bool setReaderPw(Reader& reader, string pw) {
	return copy(reader.password, pw, sizeof(reader.password));
}


//BorrowRecord
/************************************************************************/
bool increaseRationalTimeByConst(BorrowRecord& record) {

	//double difftime(time_t end, time_t beginning); 返回两个日期之间的秒数
	double seconds = difftime(record.rationalTime, record.startTime);
	//计算两个日期之间的天数
	int day = seconds / (24 * 3600) + 1;

	//如果续借次数大于maxRenewTime (最大续借次数)，返回false
	if (day >= maxBorrowDay * maxRenewTime)
		return false;

	//否则将图书合理归还时间增加maxBorrowDay天
	tm time;
	int err = localtime_s(&time, &(record.rationalTime));
	if (err) return false; //如果转换出错，直接返回false
	time.tm_mday += maxBorrowDay;

	//然后再将该tm结构体转换成time_t类型即可

	record.rationalTime = mktime(&time);
	return true;
}

/*把一个 time_t 类型的时间转换成 YYYY-MM-DD HH:MM 格式的字符串
将一个字符串输出可以调用字符串的data函数
*/
string getDateStr(time_t& t) {
	/*经过发现，使用gtime_s(&tm,&time_t) 将time_t转换成tm得到的是0时区的时间
	而函数localtime得到的才是本地时间*/
	tm time;
	int err = localtime_s(&time, &t);
	if (err) return "";//如果转换出错，返回一个空字符串
					   //转换成功，则将结构体time中的信息拼接成一个字符串

					   /*size_t strftime (char* ptr, size_t maxsize, const char* format,
					   const struct tm* timeptr ); 该函数的作用是：将timeptr所指结构体中
					   时间的信息按照format格式字符串组织起来并复制到ptr地址处去
					   最多复制maxsize个字符，返回值代表复制到ptr中的字符个数
					   */
					   //%F	Short YYYY-MM-DD date, equivalent to %Y-%m-%d
					   //%R	24-hour HH:MM time, equivalent to %H:%M

	char str[30];
	int len = strftime(str, 30, "%F %R", &time);
	if (len == 0) return "";
	else return str;
}



/*根据书所属类的bookKindId和某个时间(一般是当前时间)为被借走的这本书生成一个唯一的id
(bookKindId在这里应该已经经过检测，是一类书的id了)
该函数会直接将这个唯一的id赋值给b的 bookOnlyId字段
并且会将bookKindId赋值给bookId字段
*/
bool setRecordBookId(BorrowRecord& b, int bookKindId, time_t& t) {
	string temp;
	stringstream ss;
	ss << bookKindId;
	ss >> temp;
	int n = temp.length();
	int j = 0;
	/*一本书的唯一编号前4位是其所属类的id*/
	for (int i = 0; i < 4; i++) {
		if (i < 4 - n) b.bookOnlyId[i] = '0';
		else b.bookOnlyId[i] = temp[j++];
	}
	/*后12位是时间t*/
	tm time;
	int err = localtime_s(&time, &t);
	if (err) false;
	/*依次是：年月日时分秒*/
	char temp2[13];
	int len = strftime(temp2,13, "%C%m%d%H%M%S", &time);
	if (len == 0) return false;
	for (int i = 4; i < 17; i++)
		b.bookOnlyId[i] = temp2[i];

	b.bookId = bookKindId;
	return true;

}


/*
int main() {
	
	

	BorrowRecord record;
	record.id = 1;
	record.bookId = 1;
	record.startTime = time(NULL);
	record.rationalTime = time(NULL);
	setRecordBookId(record, 1, record.startTime);
	cout << getDateStr(record.startTime).data()<<endl;
	cout << getDateStr(record.rationalTime).data() << endl;

	int j;
	cin >> j;
	return 1;

}*/
