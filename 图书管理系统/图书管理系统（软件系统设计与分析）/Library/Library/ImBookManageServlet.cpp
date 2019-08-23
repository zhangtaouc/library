#include"stdafx.h"
#include"BookManageService.h"
#include<string>
#include"Operation.h"
#include"TypeFunc.h"
#include"AuthorFunc.h"
#include"QueryBookService.h"
#include"BookFunc.h"
#include"DealFault.h"
using namespace std;

/*增加一类书籍的servlet*/

void AddBookServlet() {
	while (1) {

		cout << endl << "欢迎来到增添书籍界面！" << endl << endl;
		AddBookService();

		int select;
		while (1) {
			cout << endl << "您确认退出添加书籍界面吗？" << endl;
			cout << "确认请输入1,否则请输入0：";

			select = GetIntFromCin();

			switch (select) {
			case 1:return;
			case 0:break;
			default:
				cout << endl << "只能输入1或0！" << endl;
				continue;
			}

			break;//case 0会跳转到这里，然后继续下一次增添书籍界面
		}
		
	}
}

/*删除一类书籍的Servlet*/
void DeleteBookServlet() {
	while (1) {
		cout <<endl << "欢迎来到删除书籍界面！" << endl <<endl;
		cout << "您可以选择：" << endl;
		cout << "1.在您知道书籍的id的情况下，您可以直接输入一个书籍id以删除书籍。" << endl;
		cout << "2.您可以先进入查询书籍界面，查询您要删除书籍的id号。" << endl;
		cout << "3.退出删除书籍界面" << endl;
		string select;

		while (1) {
			cout << endl << "请输入选项：";
			getline(cin, select);
			trimAllSpace(select);
			if (select == "1" || select == "2" || select == "3")
				break;
			else
				cout << "只能输入1或2或3，请重新输入！" << endl;
		}

		
		if (select == "2")
			QueryBookService();
		if (select == "2" || select == "1") 
			DeleteBookService();

		while (1) {
			cout << endl << "您要确认退出删除书籍界面吗？如果是请输入1，否则请输入0:" << endl;
			getline(cin, select);
			trimAllSpace(select);
			if (select == "1" || select == "0")
				break;
			else
				cout << "只能输入0或1！" << endl;
		}
		if (select == "1") return;
		else continue;


	}

}



/*修改一类书籍信息*/
void ModifyBookServlet() {

	for (;;) {
		cout << "是否知晓所要修改书籍的ISBN号？" << endl;
		for (;;) {
			cout << "知晓请输入1，否则请输入0进入书籍查找操作：";
			int t = GetIntFromCin();
			//知晓ISBN
			if (t == 1)
				break;
			//不知晓ISBN
			else if (t == 0) {
				QueryBookService();
				break;
			}
			else
				cout << "您的输入有误，请重新输入" << endl;
		}

		ModifyBookService();

		for (;;) {
			cout << "是否继续进行书籍信息修改？继续请输入1，返回首页请输入0：";
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



