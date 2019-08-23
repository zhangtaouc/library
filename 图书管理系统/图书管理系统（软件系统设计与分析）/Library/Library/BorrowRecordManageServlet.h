#pragma once
//借阅记录和借阅历史管理

/*根据管理员输入的id号向管理员展示有哪些书，有那些读者*/
void QueryBorrowHistoryServlet();

/*按读者id或图书id查看符合条件的借阅记录*/
void QueryBorrowRecordServlet();

/*
根据管理员输入的id号向管理员展示超期借阅记录*/
void QueryExtendedBookServlet();

//删除借阅记录或者借阅历史(只用于调试程序)
void DeleteBorrowRecordServlet();

