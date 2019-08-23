#pragma once
#include"AuthorFunc.h"
#include"BookFunc.h"
#include"TypeFunc.h"
#include"ReaderFunc.h"
#define MaxAuthorNumPerBook 10
#define MaxTypeNumPerBook 10



//输出书籍信息
void showBooksInfo(list<Book> books);

//输出读者信息(不包括读者登录密码)
void showReaderInfo(list<Reader> readers);

//输出借阅历史
//注意：第二个参数表示是否要展示该条借阅历史的读者信息(包括读者id和读者姓名)
//当读者登录时，向他展示他自己的借阅历史不需要展示读者信息
//但是当管理员查询多个借阅历史的时候需要展示读者信息
void showBorHistoryInfo(list<BorrowHistory> his, bool showReaderInfo);


//输出借阅记录
//注意：第二个参数表示是否要展示该条借阅记录的读者信息(包括读者id和读者姓名)
//当读者登录时，向他展示他自己的借阅记录不需要展示读者信息
//但是当管理员查询多个借阅记录的时候需要展示读者信息
void showBorRecordInfo(list<BorrowRecord> records, bool showReaderInfo);

//输出作者信息
//如果showId为true，就展示作者Id(此时每条作者的记录信息会用换行符隔开)
//否则就只展示作者姓名(只展示作者姓名时，不需要将作者姓名一行行地分开，只用空格隔开即可，这个会用在展示一本书的多个作者上)
void showAuthorInfo(list<Author> aus, bool showId);




//输出类别信息
//如果showId为true，就展示类别Id(此时每条作者的记录信息会用换行符隔开)
//否则就只展示类别名(只展示作者姓名时，不需要将作者姓名一行行地分开，只用空格隔开即可，这个会用在展示一本书的多个类别上)
void showTypeInfo(list<Type> types, bool showId);