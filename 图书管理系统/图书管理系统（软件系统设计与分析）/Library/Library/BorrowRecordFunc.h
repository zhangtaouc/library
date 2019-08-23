#pragma once
#include <list>
#include "Structs.h"

/**
* 添加记录到借书表中
* @param borrowRecord
* @return
*/
bool addRecord(BorrowRecord& borrowRecord);

/**
* 删除记录（真删除的时候参数只有id号即可）
* @param borrowRecord
* @return
*/
bool deleteRecord(int id);

/**
* 通过读者id查询借书表信息
* @return
*/
list<BorrowRecord> getRecordsByReaderId(int readerId);

/**
* 根据书籍id查询借书表信息
* 这里的id是一类书共同的id
* @return
*/
list<BorrowRecord> getRecordByBookId(int bookId);



list<BorrowRecord> getRecords(int start, int amount = -1);

/**
* 更改借书表中的借书记录
* 完成续借功能的时候会用到
* @param borrowRecord
* @return
*/
bool modifyRecord(BorrowRecord& borrowRecord);

/*
通过记录的id号查询得到记录信息*/
list<BorrowRecord> getRecordById(int id);
