#pragma once

//(readerId是当前登录的读者的id号，主函数会将这个id传给这个service)
void BorrowBookServlet(int readerId);


//先显示当前借阅，让读者输入借书记录的id进行还书，借书记录真删除一条，借阅历史生成一条，馆藏数量增加
void ReturnBookServlet(int readerId);

/*续借的Servlet*/
void RenewBookServlet(int readerId);