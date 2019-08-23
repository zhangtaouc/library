// Library.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include <map>
#include "Structs.h"
#include <string>
#include"UnsignedReaderServlet.h"
#include"LoginServlet.h"
#include"BookOperationServlet.h"
#include"QueryBookServlet.h"
#include"BookManageServlet.h"
#include"BorrowRecordManageServlet.h"
#include"ReaderManageServlet.h"
#include"QueryBookServlet.h"
#include"BookOperationServlet.h"
#include"RecordOperationServlet.h"
#include"AuthorManageServlet.h"
#include"AdminFunc.h"
using namespace std;


int main()
{
	cout << endl;
	cout << "欢迎使用图书馆管理系统！" << endl;
	int choose1 = 1;
	//进入界面输出提示信息
	while (choose1) {
		cout << endl;
		cout << "0.退出系统" << endl;
		cout << "1.进行登录操作" << endl;
		cout << "2.进行新读者注册操作" << endl;
		cout << "3.游客操作" << endl;
		cout << "请输入您的选择： ";

		choose1 = GetIntFromCin();
		map<string, int> loginInfo;
		if (choose1 < 0)            
		{
			cout << endl;
			cout << "输入有错!请重新输入" << endl;
			choose1 = 1;
			continue;
		}
		switch (choose1)
		{
			cout << endl;
		//退出系统
		case 0:cout << endl <<  "感谢您的使用！"; return 0;
		//用户登录
		case 1:
			loginInfo = LoginServlet();
			if (loginInfo.size() == 0)
			{
				continue;
			}
			else
			{
				map<string, int>::iterator i;
				string userIdentity;
				cout << endl;
				cout << "您已登录成功！" << endl;
				int choose2 = 1;
				i = loginInfo.begin();
				//admin登录后的操作
				if (i->first == "Admin")
				{
					while (choose2)
					{
						cout << endl;
						cout << "0.退出登录" << endl;
						cout << "1.书籍管理操作" << endl;
						cout << "2.读者管理操作" << endl;
						cout << "3.借阅记录管理操作" << endl;
						cout << "4.借阅历史管理操作" << endl;
						cout << "5.作者管理操作" << endl;
						cout << "请输入您的选择：" << endl;
						choose2 = GetIntFromCin();
						if (choose2 < 0)            //条件可改写为cin.fail() 
						{
							cout << "输入有错!请重新输入" << endl;
							choose2 = 1;
							continue;
						}

						int choose3 = 1;
						switch (choose2)
						{
						//管理员退出登录
						case 0:break;
						//管理员进行图书管理
						case 1:
							while (choose3)
							{
								cout << endl;
								cout << "书籍操作：" << endl;
								cout << "0.返回主界面" << endl;
								cout << "1.书籍查询操作" << endl;
								cout << "2.书籍增加操作" << endl;
								cout << "3.书籍修改操作" << endl;
								cout << "4.书籍删除操作" << endl;
								cout << "请输入您的选择：" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)           
								{
									cout << endl;
									cout << "输入有错!请重新输入" << endl;
									choose3 = 1;
									continue;
								} 
								switch (choose3)
								{
									case 0:break;
									case 1:QueryBookServlet();break;
									case 2:AddBookServlet();break;
									case 3:ModifyBookServlet();break;
									case 4:DeleteBookServlet();break;
									default:cout <<endl<< "请正确输入选择信息！" << endl; break;
								}
								if (choose3 == 0)
									break;
							}
							break;
						//管理员进行读者管理
						case 2:
							while (choose3)
							{
								cout << endl;
								cout << "读者管理操作" << endl;
								cout << "0.返回主界面" << endl;
								cout << "1.读者查询操作" << endl;
								cout << "2.读者增加操作" << endl;
								cout << "3.读者修改操作" << endl;
								cout << "4.读者删除操作" << endl;//若读者有借书情况，不能被删除
								cout << "请输入您的选择：" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "输入有错!请重新输入" << endl;
									choose3 = 1;
									continue;
								}
								switch (choose3)
								{
									case 0:break;
									case 1:QueryReaderServlet();break;
									case 2:AddReaderServlet();break;
									case 3:AdminModifyReaderServlet();break;
									case 4:DeleteReaderServlet();break;
								default:cout << endl << "请正确输入选择信息！" << endl; break;;
								}
								if (choose3 == 0)
									break;
							}
							break;
						//管理员进行借阅记录管理
						case 3:
							while (choose3)
							{
								cout << endl;
								cout << "借阅记录管理操作" << endl;
								cout << "0.返回主界面" << endl;
								cout << "1.借阅记录查询操作" << endl;
								cout << "2.查询当前超期未还书籍借阅记录" << endl;
								cout << "请输入您的选择：" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "输入有错!请重新输入." << endl;
									choose3 = 1;
									continue;
								}
								switch (choose3)
								{
								case 0:break;
								//		借阅记录查询	
								case 1:QueryBorrowRecordServlet();break;
									//	查询当前超期未还书籍
								case 2:QueryExtendedBookServlet();break;
							
					
								default:cout << endl<< "请正确输入选择信息！" << endl; break;;
								}
								if (choose3 == 0)
									break;
							}
							break;
						//管理员进行借阅历史管理
						case 4:
							while (choose3)
							{
								cout << endl;
								cout << "借阅记录管理操作" << endl;
								cout << "0.返回主界面" << endl;
								cout << "1.借阅历史查询操作" << endl;
								//cout << "2.借阅历史删除操作" << endl;
								cout << "请输入您的选择：" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "输入有错!请重新输入." << endl;
									choose3 = 1;
									continue;
								}
								switch (choose3)
								{
								case 0:break;
								//		借阅历史查询操作
								case 1:QueryBorrowHistoryServlet(); break;
								//			借阅历史删除操作	
								
								//case 2:Delete;break;

								default:cout << endl<< "请正确输入选择信息！" << endl; break;
								}
								if (choose3 == 0)
									break;
							}
							break;
						//管理员进行作者管理
						case 5:
							while (choose3)
							{
								cout << endl;
								cout << "作者管理操作" << endl;
								cout << "0.返回主界面" << endl;
								cout << "1.查询作者" << endl;
								cout << "2.根据作者进行书籍查询操作" << endl;
								cout << "请输入您的选择：" << endl;
								
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "输入有错!请重新输入." << endl;
									choose3 = 1;
									continue;
								}

								switch (choose3)
								{
								case 0:break;
								case 1:QueryAuthorServlet();break;
								case 2:QueryBooksByAuthorServlet();break;

								default:cout << endl << "请正确输入选择信息！" << endl; break;
								}
								if (choose3 == 0)
									break;

							}
							break;
						//输入错误，进行容错
						default:cout << endl << "请正确输入信息！" << endl; continue;
						}
						if (choose2 == 0)
						{
							break;
						}
					}

				}
				

//admin登录后的操作
			else
				{
//reader登录后的操作
					userIdentity = "Reader";
					int readerId = i->second;
					while (choose2)
					{
						cout << endl;
						cout << "0.退出登录" << endl;
						cout << "1.查询书籍" <<endl;
						cout << "2.查看当前借阅记录" << endl;
						cout << "3.查看或删除借阅历史" << endl;
						cout << "4.查看或修改个人信息操作" << endl;
						cout<<  "5.借书" << endl;
						cout << "6.还书" << endl;
						cout << "7.续借" << endl;
						cout << "8.缴纳欠款" << endl;
						cout << "请输入您的选择：" << endl;
						choose2 = GetIntFromCin();
						if (choose2 < 0)
						{
							cout << endl;
							cout << "输入有错!请重新输入." << endl;
							choose2 = 1;
							continue;
						}

						int choose3 = 1;
						switch (choose2)
						{
						//读者退出登录
						case 0:break;
						//读者查询书籍
						case 1:QueryBookServlet();break;
						//读者查看当前借阅记录
						case 2:QueryCurReaderBorRecordServlet(readerId);break;
						//读者查看或删除借阅历史
						case 3:
							while (choose3)
							{
								cout << endl;
								cout << "0.返回主界面 " << endl;
								cout << "1.借阅历史查询" << endl;
								cout << "2.借阅历史删除" << endl;
								cout << "请输入您的选择：" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "输入有错!请重新输入." << endl;
									choose3 = 1;
									continue;
								}
								switch (choose3)
								{
								case 0:break;
								case 1:QueryCurReaderBorHistoryServlet(readerId); break;
								case 2: DeleteCurReaderHistoryServlet(readerId); break;
								default:cout << endl; cout << "请正确输入信息！" << endl; continue;
								}
								if (choose2 == 0)
								{
									break;
								}
							}
							break;
						//查看或修改读者个人资料
						case 4:
							while (choose3)
							{
								cout << endl;
								cout << "0.返回主界面" << endl;
							//	cout << "1.个人信息查看" << endl;
								cout << "2.个人信息修改" << endl;
								cout << "请输入您的选择：" << endl;
								choose3 = GetIntFromCin();
								if (choose3 < 0)
								{
									cout << endl;
									cout << "输入有错!请重新输入." << endl;
									choose3 = 1;
									continue;
								}
								switch (choose3)
								{
								case 0:break;
								//case 1:个人信息查看；break;
								//个人信息修改
								case 2:	ReaderModifySelfServlet(readerId);break;
								default:cout << "请正确输入选项！" << endl; break;
								}
								if (choose3 == 0)
								{
									break;
								}

							}
							break;
						//借书
						case 5:BorrowBookServlet(readerId);break; 
						//还书
						case 6: ReturnBookServlet(readerId); break;
						//续借
						case 7:RenewBookServlet(readerId); break;
						//缴纳欠款
						case 8:  PayTheFeesServlet(readerId); break;//缴纳欠款
						default:cout << endl<< "请正确输入选择信息！" << endl; break;
						}
						if (choose2 == 0)
						{
							break;
						}
					}
				}

			}
			break;
		//读者注册
		case 2:SignUpServlet(); break;
		//游客操作
		case 3:UnsignedReaderServlet();break;
		default:cout << endl; cout << "请正确输入选项！"; continue;
		}


	}

	return 0;
}


