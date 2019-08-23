#pragma once

//(展示当前读者所有当前借书记录。
//显示当前借阅书籍，超期图书，罚款金额，
void QueryCurReaderBorRecordServlet(int readerId);


//(展示当前读者的所有借阅历史)
void QueryCurReaderBorHistoryServlet(int readerId);


/*(一定要保证登录的读者只能删除自己的借阅历史。
当读者输入一个要删除的借阅历史的id后，要确认这条借阅历史是当前读者的，
才可以执行删除操作)*/
void DeleteCurReaderHistoryServlet(int readerId);
