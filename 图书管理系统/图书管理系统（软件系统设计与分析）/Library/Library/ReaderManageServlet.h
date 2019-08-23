#pragma once

/*按条件查询符合相应条件的读者并展示给用户看*/
void QueryReaderServlet();


/*增加一类读者的service*/
void AddReaderServlet();

/*删除一类读者的Servlet*/
void DeleteReaderServlet();

//管理员修改读者信息功能界面
void AdminModifyReaderServlet();

//读者修改自己基本信息界面
void ReaderModifySelfServlet(int id);


//读者缴纳欠款
void PayTheFeesServlet(int readerId);