#pragma once
#include <list>
#include "Structs.h"

/**
* 添加借阅记录
* @param borrowHistory
* @return
*/
bool addHistory(BorrowHistory& borrowHistory);

/**
* 根据借阅记录id删除借阅记录（假删除）
* @param borrowHistoryId
* @return
* 如果id不存在，函数返回false
* 否则，假删除成功后返回true
*/

bool deleteHistory(int id);


/**
* 通过读者id查询借阅记录
*/
list<BorrowHistory> getHistoryByReaderId(int readerId, int exist);

/**
* 通过书籍id(这里的图书id是一类图书的共同id)查询借阅记录
* @return
*/
list<BorrowHistory> getHistoryByBooksId(int bookId, int exist);

/**
* 返回所有的借阅记录
* @return
*/
list<BorrowHistory> getAllHistory(int exist);

/*通过历史记录的id查找记录
exist为1 ，则查找的在未被删除的历史记录中查找
exist为0则在所有历史记录中查找*/
list<BorrowHistory> getHistoryById(int id, int exist);