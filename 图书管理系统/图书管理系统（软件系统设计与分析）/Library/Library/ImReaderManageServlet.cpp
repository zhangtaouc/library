#include"stdafx.h"
#include"Structs.h"
#include"ReaderManageService.h"
#include<list>
#include<iostream>
#include<string>
#include"ReaderFunc.h"
#include"ReaderManageService.h"
#include"DealFault.h"
using namespace std;



/*按条件查询符合相应条件的读者并展示给用户看*/
//按条件（id，姓名，性别，所有）查询读者，已被删除（假删除）的读者不会被检索到
void QueryReaderServlet() {
	QueryReaderService();
}


//增加读者（可以是一批，也可以是一个）
void AddReaderServlet() {
	while (1)
	{
		cout << endl << "您要创建一个读者吗？按1确定，其他键退出创建:" << endl;
		string key;//用于选择操作
		getline(cin, key);
		if (key == "1")//key为1的时候代表要创建读者
		{
			Reader tempReader;//临时储存一个读者结构体
			list<Reader> readerList;//每生成一个临时的读者结构体，就将其传进readerList中，传送结束后，调用AddReaderService


									//输入密码				
			while (1) {
				cout << endl << "请输入该读者的密码(密码最多可以有20个字符):" << endl;
				string tempPwd;//临时密码字符串
				getline(cin, tempPwd);

				trimAllSpace(tempPwd);

				if (tempPwd == "" || !setReaderPw(tempReader, tempPwd))
				{
					cout << endl << "读者密码长度非法，请重新输入!" << endl;
					continue;
				}

				string confirm;
				while (1) {
					cout << endl << "您输入的读者密码为：";
					cout << tempReader.password << endl;
					cout << endl << "请重新确认密码！正确请输入1，否则请输入0以重新输入密码!" << endl;
					getline(cin, confirm);
					if (confirm == "0" || confirm == "1")
						break;
					else {
						cout << "您只能输入0或1，请重新输入！" << endl;
					}
				}
				if (confirm == "1") break;
				else continue;//输入0可以重新输入密码！


			}

			//输入姓名
			while (1) {
				cout << endl << "请输入读者的姓名" << endl;
				string tempName;//临时的读者姓名
				getline(cin, tempName);

				if (!setReaderName(tempReader, tempName))
				{
					cout << endl << "读者姓名长度非法，请重新输入" << endl;
					continue;
				}


				string confirm;
				while (1) {
					cout << endl << "您输入的读者姓名为:" << tempReader.name << endl;
					cout << endl << "请重新确认读者姓名！正确请输入1，否则请输入0以重新输入读者姓名!" << endl;
					getline(cin, confirm);
					if (confirm == "0" || confirm == "1")
						break;
					else {
						cout << "您只能输入0或1，请重新输入！" << endl;
					}
				}

				if (confirm == "1") break;
				else continue;//输入0可以重新输入读者姓名！

			}



			//输入性别，该方法需改进
			while (1) {
				cout << endl << "请输入该读者的性别,1表示男性，0表示女性" << endl;
				int tempSex;//临时存储该读者的性别;
				tempSex = GetIntFromCin();
				while (tempSex != 0 && tempSex != 1)//性别必须为整形，不能输入除了一和零之外的值
				{
					cout << endl << "输入不合法！不能输入除了1和0之外的字符,请重新输入" << endl;
					tempSex = GetIntFromCin();
				}
				tempReader.sex = tempSex;
				string confirm;
				while (1) {

					cout << endl << "你输入的读者性别为：";
					if (tempReader.sex) cout << "男" << endl;
					else cout << "女" << endl;

					cout << endl << "请重新确认读者性别！正确请输入1，否则请输入0以重新输入读者性别!" << endl;
					getline(cin, confirm);
					if (confirm == "0" || confirm == "1")
						break;
					else {
						cout << endl << "您只能输入0或1，请重新输入！" << endl;
					}
				}
				if (confirm == "1") break;
				else
					continue;//输入0可以重新输入读者性别！

			}

			//将读者有效性以及欠款金额置为默认值
			tempReader.exist = 1;
			tempReader.fine = 0;

			//将该临时读者结构体放入list中，由于不确定list中存的是tempReader的指针还拷贝，所以
			//每生成一个tempReader就将其保存进结构体中并存入文件中
			readerList.push_back(tempReader);
			AddReaderService(readerList);

			//输出创建成功地提示信息
			cout << endl << "新读者已创建" << endl;
		}
		else//其他值代表退出创建
		{
			cout << endl << "创建读者模块已退出" << endl;
			return;
		}
	}

}



void DeleteReaderServlet() {
	while (1)
	{
		cout << endl << "您要删除一个读者吗？按1确定，其他键退出" << endl;
		string key;
		getline(cin, key);
		if (key == "1")//1代表继续删除操作
		{
			cout << endl << "您是否知晓要删除的读者的id？" << endl << "若您知道，请按1继续删除，否则请按其他键查找该用户的id" << endl;
			getline(cin, key);
			if (key == "1")//1代表继续删除操作
			{
				cout << endl << "请输入你要删除的读者的id" << endl;
				int tempId;//临时存放要删除的读者的id
				tempId = GetIntFromCin();
				while (tempId == -1)
				{
					cout << endl << "输入不合法！您只能输入数字！请重新输入！";
					tempId = GetIntFromCin();
				}
				DeleteReaderService(tempId);
			}
			else//其他键代表用户不清楚要删除的读者的id，需要先进行查找操作
			{
				QueryReaderService();//查找读者

									 //继续删除，与if中进行的操作相同
				cout << endl << "请输入你要删除的读者的id" << endl;
				int tempId;//临时存放要删除的读者的id
				tempId = GetIntFromCin();
				while (tempId == -1)
				{
					cout << endl << "输入不合法！您只能输入数字！请重新输入！";
					tempId = GetIntFromCin();
				}
				DeleteReaderService(tempId);
				//cout << endl << "id为" << tempId << "的读者已删除" << endl;
			}
		}
		else//其他按键退出该servlet
		{
			cout << endl << "删除读者程序已退出！" << endl;
			return;
		}
	}

}


//管理员修改读者信息功能界面
void AdminModifyReaderServlet() {

	for (;;) {
		cout << endl;
		cout << "您是否知晓所要修改的读者ID号？" << endl;
		for (;;) {
			cout << "知晓请输入1，否则请输入0进入读者查询操作：";
			int t = GetIntFromCin();

			if (t == 1)
				break;
			else if (t == 0) {
				QueryReaderService();
				break;
			}
			else
				cout << "您的输入有误，请重新输入" << endl;
		}

		AdminModifyReaderService();

		for (;;) {
			cout << "是否继续进行读者信息修改？继续请输入1，返回首页请输入0：";
			int t = GetIntFromCin();

			if (t == 1)
				break;
			else if (t == 0)
				return;
			else
				cout << "您的输入有误，请重新输入" << endl;
		}
	}
}

//读者修改自己基本信息界面
void ReaderModifySelfServlet(int id) {

	for (;;) {

		ReaderModifySelfService(id);

		for (;;) {
			cout << "是否继续进行您的信息修改？继续请输入1，返回首页请输入0：";
			int t = GetIntFromCin();

			if (t == 1)
				break;
			else if (t == 0)
				return;
			else
				cout << "您的输入有误，请重新输入" << endl;
		}
	}
}

//读者缴纳欠款
void PayTheFeesServlet(int readerId) {
	PayTheFeesService(readerId);
}




