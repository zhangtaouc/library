#pragma once
#include<list>
#include"Structs.h"



list<Reader> QueryReaderById(int id);
void QueryReaderByName(string name);
void QueryReaderBySex(int sex);
void QueryAllReader();

/*按条件查询符合相应条件的读者并展示给用户看*/
void QueryReaderService();


/*增加一类读者的service*/
void AddReaderService(list<Reader> readerList);

/*删除一类读者的service*/
void DeleteReaderService(int id);


//管理员修改任意一个读者信息
void AdminModifyReaderService();

//读者修改自己基本信息
void ReaderModifySelfService(int id);

//读者缴纳欠款
void PayTheFeesService(int readerId);