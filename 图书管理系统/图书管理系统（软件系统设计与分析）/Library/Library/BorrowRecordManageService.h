#pragma once
//借阅记录和借阅历史管理

/*按读者id或图书id查看符合条件的借阅历史*/
void QueryBorrowHistoryService();

/*按读者id或图书id查看符合条件的借阅记录*/
void QueryBorrowRecordService();

/*按读者id或图书id查看符合条件的超期借阅记录*/
void QueryExtendedBookService();

//删除借阅记录(只用于调试程序)
void DeleteBorrowRecordService();

