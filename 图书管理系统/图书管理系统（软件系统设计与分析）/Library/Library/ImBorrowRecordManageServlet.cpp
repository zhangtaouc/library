#include"stdafx.h"
#include<iostream>
#include<string>
#include"BorrowRecordManageService.h"
#include"QueryBookService.h"
#include"ReaderManageService.h"

using namespace std;

//借阅记录和借阅历史管理

void QueryBorrowHistoryServlet() {
	cout << endl << "欢迎来到查询借阅历史界面" << endl;
	cout << "您可以通过输入书籍id或者读者id查询相关借书历史记录。" << endl;

	string choice1;
	string choice2;

	cout << endl;
	cout << "**********************************************" << endl;
	cout << endl;
	cout << "请选择:" << endl;
	cout << endl;
	cout << "0.直接输入书籍id或者读者id查询相关借书历史记录" << endl;
	cout << "1.查询书籍信息" << endl;
	cout << "2.查询读者信息" << endl;
	cout << "3.查询所有借阅历史" << endl;
	cout << "4.退出" << endl;
	cout << endl;
	cout << "请输入选择：";

	while (1) {
		getline(cin, choice1);
		if (choice1 == "0") {
			break;
		}
		else if (choice1 == "1") {
			QueryBookService(); //查询书籍信息
		}
		else if (choice1 == "2") {
			QueryReaderService();//查询读者信息
		}
		else if (choice1 == "4")
			return;
		else if (choice1 == "3")
			QueryBorrowHistoryService();
		else {
			cout << endl;
			cout << "输入内容不合规则，请重新输入：";
			continue;
		}
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "0.直接输入书籍id或者读者id查询相关借书历史记录" << endl;
		cout << "1.查询书籍信息" << endl;
		cout << "2.查询读者信息" << endl;
		cout << "3.查询所有借阅历史" << endl;
		cout << "4.退出" << endl;
		cout << "请输入选择：";
	}

	for (int t = 1; t != 0;) {
		QueryBorrowHistoryService();//调用Service文件中的函数进行查询借阅历史
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "您要退出查询历史记录界面吗？" << endl;
		cout << endl;
		cout << "0.返回首页" << endl;
		cout << "1.继续查询" << endl;
		while (1) {
			cout << endl;
			cout << "请输入选项：";
			getline(cin, choice2);
			if (choice2 == "0") {
				t = 0;
				break;
			}
			else if (choice2 == "1") {
				t = 1;
				break;
			}
			else {
				cout << endl;
				cout << "输入内容不合规则!只能输入1或0.";
				continue;
			}
		}
	}
	return;
}

/*按读者id或图书id查看符合条件的借阅记录*/
void QueryBorrowRecordServlet() {
	cout << endl << "欢迎来到查询借阅记录界面" << endl;
	cout << "您可以通过输入书籍id或者读者id查询当前借阅记录。" << endl;

	string choice1;
	string choice2;

	cout << endl;
	cout << "**********************************************" << endl;
	cout << endl;
	cout << "请选择:" << endl;
	cout << endl;
	cout << "0.直接输入书籍id或者读者id询当前借阅记录" << endl;
	cout << "1.查询书籍信息" << endl;
	cout << "2.查询读者信息" << endl;
	cout << "3.查询所有借书记录" << endl;
	cout << "4.退出" << endl;
	cout << endl;
	cout << "请输入选择：";

	while (1) {
		getline(cin, choice1);
		if (choice1 == "0") {
			break;
		}
		else if (choice1 == "1") {
			QueryBookService(); //查询书籍信息
		}
		else if (choice1 == "2") {
			QueryReaderService();//查询读者信息
		}
		else if (choice1 == "3")
			QueryBorrowRecordService();
		else if (choice1 == "4")
			return;
		else {
			cout << endl;
			cout << "输入内容不合规则，请重新输入：";
			continue;
		}
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "0.直接输入书籍id或者读者id查询询当前借阅记录" << endl;
		cout << "1.查询书籍信息" << endl;
		cout << "2.查询读者信息" << endl;
		cout << "3.查询所有借书记录" << endl;

		cout << "4.退出" << endl;
		cout << "请输入选择：";
	}

	for (int t = 1; t != 0;) {
		QueryBorrowRecordService();//调用Service文件中的函数进行查询借阅历史
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "您要退出查询当前借阅记录吗？" << endl;
		cout << endl;
		cout << "0.返回首页" << endl;
		cout << "1.继续查询" << endl;
		while (1) {
			cout << endl;
			cout << "请输入选项：";
			getline(cin, choice2);
			if (choice2 == "0") {
				t = 0;
				break;
			}
			else if (choice2 == "1") {
				t = 1;
				break;
			}
			else {
				cout << endl;
				cout << "输入内容不合规则!只能输入1或0.";
				continue;
			}
		}
	}
	return;
}


/*根据管理员输入的id号向管理员展示有哪些书，有哪些读者*/

void QueryExtendedBookServlet()
{
	cout << endl << "欢迎来到查询逾期借阅记录界面" << endl;
	cout << "您可以通过输入书籍id或者读者id查询逾期借阅记录。" << endl;

	string choice1;
	string choice2;

	cout << endl;
	cout << "**********************************************" << endl;
	cout << endl;
	cout << "请选择:" << endl;
	cout << endl;
	cout << "0.直接输入书籍id或者读者id查询逾期借阅记录" << endl;
	cout << "1.查询书籍信息" << endl;
	cout << "2.查询读者信息" << endl;
	cout << "3.退出" << endl;
	cout << endl;
	cout << "请输入选择：";

	while (1) {
		getline(cin, choice1);
		if (choice1 == "0") {
			break;
		}
		else if (choice1 == "1") {
			QueryBookService(); //查询书籍信息
		}
		else if (choice1 == "2") {
			QueryReaderService();//查询读者信息

		}
		else if (choice1 == "3")
			return;
		else {
			cout << endl;
			cout << "输入内容不合规则，请重新输入：";
			continue;
		}
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "0.直接输入书籍id或者读者id查询逾期借阅记录" << endl;
		cout << "1.查询书籍信息" << endl;
		cout << "2.查询读者信息" << endl;
		cout << "3.退出" << endl;
		cout << "请输入选择：";
	}

	for (int t = 1; t != 0;) {
		QueryExtendedBookService();//调用Service文件中的函数进行查询借阅历史
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "您要退出查询逾期借阅记录吗？" << endl;
		cout << endl;
		cout << "0.返回首页" << endl;
		cout << "1.继续查询" << endl;
		while (1) {
			cout << endl;
			cout << "请输入选项：";
			getline(cin, choice2);
			if (choice2 == "0") {
				t = 0;
				break;
			}
			else if (choice2 == "1") {
				t = 1;
				break;
			}
			else {
				cout << endl;
				cout << "输入内容不合规则!只能输入1或0.";
				continue;
			}
		}
	}
	return;
}


/*
管理员功能，能够删除借阅历史以及借阅记录
*/
void DeleteBorrowRecordServlet() {

	string choice1;
	string choice2;

	cout << endl;
	cout << "**********************************************" << endl;
	cout << endl;
	cout << "请选择是否查询书籍或是查询读者信息功能" << endl;
	cout << endl;
	cout << "输入1查询书籍信息" << endl;
	cout << "输入2查询读者信息" << endl;
	cout << "输入0继续" << endl;
	cout << endl;
	cout << "请输入选择：";
	while (1) {
		getline(cin, choice1);
		if (choice1 == "0") {
			break;
		}
		else if (choice1 == "1") {
			QueryBookService(); //查询书籍信息
		}
		else if (choice1 == "2") {
			QueryReaderService();//查询读者信息
		}
		else {
			cout << endl;
			cout << "输入内容不合规则，请重新输入：";
			continue;
		}
	}

	for (int t = 1; t != 0;) {
		DeleteBorrowRecordService();//调用Service文件中的函数进行查询借阅历史
		cout << endl;
		cout << "**********************************************" << endl;
		cout << endl;
		cout << "请选择继续删除操作或是退出此功能" << endl;
		cout << endl;
		cout << "输入1继续删除" << endl;
		cout << "输入0返回首页" << endl;
		while (1) {
			cout << endl;
			cout << "是否继续查询：";
			getline(cin, choice2);
			if (choice2 == "0") {
				t = 0;
				break;
			}
			else if (choice2 == "1") {
				t = 1;
				break;
			}
			else {
				cout << endl;
				cout << "输入内容不合规则，请重新输入：";
				continue;
			}
			cout << endl;
			cout << "**********************************************" << endl;
			cout << endl;
			cout << "输入1继续查询书籍信息" << endl;
			cout << "输入2继续查询读者信息" << endl;
			cout << "输入0继续" << endl;
			cout << "请输入选择：";
		}
	}
	return;
}


