#pragma once

#include<time.h>
#define  maxBorrowDay 30//最大借书天数(每续借一次，最迟归还长度就增长maxBorrowDay天)
#define maxBorrowNum 10//最大借书数量
#define finePerday  1//逾期每天的罚款
#define maxRenewTime  3//最大续借图书次数
#include<iostream>
#include"Operation.h"
using namespace std;

typedef struct {
	int id;
	char password[22];//密码要求：5-10位！！！！！！！
	int exist;
}Admin;

/*设置admin的密码为pd*/
bool setAdminPd(Admin& admin,string pd);


/************************************************************************/

typedef struct {
	int id;
	char name[40];//一个字符是两个字节，所以这个数组最多可以存储20个字符的作者姓名
}Author;



/*给name字段设置值
如果name 长度过长，函数不进行设置，直接返回false
*/
bool setAuthorName(Author& author, string name);



/************************************************************************/
typedef struct {
	int id;
	char name[20];//一个字符是两个字节，所以这个数组最多可以存储10个字符的类别名
}Type;

bool setTypeName(Type& type,string name);

/************************************************************************/
typedef struct {
	int id;
	char name[40];//一个unicode字符编码是两个字节，因此书名最长可以有20个字符
	int author[10];//存储一本书的author的id号，用一个整型数组表示
				   //不够10个的后面补0 在按作者号查询作者信息时，遍历这个数组
				   //遇到有元素为0 就停止，然后去查询作者信息即可



	char publisher[40];//出版社名称
	int numberInLib;//馆藏数量
	int amount;//该类图书总量
	int type[10];//用来表述哪一类图书，该整型数组存储该图书所属类别的id组成的数组
				 //同样，不够10个类别的在后面补0 查询方法同作者id

	int exist;//该属性是为了做假删除用的
	char ISBN[14];//ISBN编号,多出来的一位是存储字符结束符的
}Book;


/*给name字段设置值
如果name 长度过长，函数不进行设置，直接返回false
*/
bool setBookName(Book& book,string name);

/*设置由作者id组成的整型数组，如果au过长，函数返回false
len 是au数组的长度 
例如int a[5]; 长度就是5*/
bool setBookAuthors(Book& book,int* au,unsigned len);

bool setBookPublisher(Book& book,string pub);

/*同author数组的复制
len 是参数type数组的长度*/
bool setBookTypes(Book& book,int* type, unsigned len);


bool setBookISBN(Book& book,string ISBN);




/************************************************************************/
typedef struct {
	int id;//读者id
	char name[40];//读者姓名  !!!!!
	char password[22];//密码5-10位有效！！！！！！！！！！
	int sex;//sex用0或1表示比较方便  1表示男性，0表示女性
	int exist;//用户是否有效 用1或0表示
	double fine;//欠款金额
}Reader;

/*给name字段设置值
如果name 长度过长，函数不进行设置，直接返回false
*/
bool setReaderName(Reader& reader,string name);

bool setReaderPw(Reader& reader,string pw);


/************************************************************************/

typedef struct {
	int id;
	char bookOnlyId[17];//这里的bookOnlyId是可以唯一标识一本书的id，
				//这个编号的前5位是书所属类别号，后面的12位是这本书被借时间
	int readerId;
	int bookId;
	time_t startTime;//借书起始时间
	time_t rationalTime;//图书最迟归还时间
						//续借次数可以通过借书起始时间和最迟归还时间来计算
						//续借前要判断续借次数不能大于最大续借次数

}BorrowRecord;


//record.rationalTime = time(NULL); 可以设置当前时间

/*返回一个时间字符串(格式：YYYY-MM-DD HH:MM   24小时制)
用于功能界面、主函数中的展示
*/
string getDateStr(time_t& time);

/*根据书所属类的bookKindId和某个时间(一般是当前时间)为被借走的这本书生成一个唯一的id
该函数会直接将这个唯一的id赋值给b的 bookOnlyId字段
并且会将bookKindId赋值给bookId字段
*/
bool setRecordBookId(BorrowRecord& b,int bookKindId,time_t& t);


/*将图书最迟归还时间后延 maxBorrowDay 天
但是如果通过判断，当前续借次数已经大于最大续借次数
则rationaltime不会变化，函数会返回false
(设置前要保证 startTime里和rationalTime里存放的是有效时间，否则会返回false)
续借可以调用这个函数
*/
bool increaseRationalTimeByConst(BorrowRecord& record);

/************************************************************************/


typedef struct {
	int id; //借阅历史记录id号
	int bookId; //借阅图书id号(这是这本书所属类的id号)
	int readerId;//读者id号

				 /*time_t是表示UTC时间的，也就是一个整数值
				 存储 从00:00 hours, Jan 1, 1970 UTC
				 到某一时间点经历的秒数

				 size_t型数据可以通过函数mktime转换成表示 年月日时分秒 的结构体类型tm
				 从而获取时间信息
				 */
	time_t borrowTime;//借阅起始时间,在文件中存储这个整数值就可以
	time_t returnTime;//图书归还时间，在文件中存储这个整数值就可以
	int exist;//这是用来做假删除的属性，取值为0或或1，0代表该条记录被删除，1代表该记录存在
}BorrowHistory;

/*注：用getDataStr函数就可以得到两个time_t变量的字符串表示*/
/*应用 generateBookId函数生成bookId*/
/*BorrowHistory结构体中没有数组类型，因此直接赋值都不会出现越界问题
不过在赋值之前需要检查数据
*/


