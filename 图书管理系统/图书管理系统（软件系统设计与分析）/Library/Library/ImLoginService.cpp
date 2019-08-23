

#include"stdafx.h"
#include"AdminFunc.h"
#include<list>
#include<string>
#include"DealFault.h"
#include"ReaderFunc.h"

/*这是用于注册和登陆的函数的头文件*/


/**
由管理员输入自己的id与password，调用getAdminById(id)方法找到这个id号
对应的一条记录，然后构造一个迭代器admin，因为只能有一个元素，所以直接
调用该方法的begin()方法就行，然后对比返回对象的password与用户输入的是
否一致，能符合的话就返回该用户的id号，否则返回0
*/
int AdminLoginService() {
	int id;
	list<Admin> adminList;
	string idTerm;//用于存储用户输入的id
	string idTerm2;//用于把id转换成字符串采用的临时变量
	string password;

	cout << endl << "请输入您的id号：";
	//cin >> id;
	getline(cin, idTerm);
	cout << endl << "请输入密码：";
	//cin >> password;
	getline(cin, password);

	id = atoi(idTerm.c_str());
	idTerm2 = "" + to_string(id);
	list<Admin> ::iterator admin;

	while (1) {
		adminList = getAdminById(id);
		admin = adminList.begin();
		if (idTerm == idTerm2 && !adminList.empty()) {
			if (admin->password == password) {
				cout << endl << "登录成功，欢迎" << admin->id << "使用本系统" << endl;
				return id;
				break;
			}
			else {
				cout << endl << "密码与id不符" << endl;
				if (DealFault() == 1) {
					cout << endl << "请输入您的id号：";
					//cin >> id;
					getline(cin, idTerm);
					cout << endl << "请输入密码：";
					//cin >> password;
					getline(cin, password);
					id = atoi(idTerm.c_str());
					idTerm2 = "" + to_string(id);
				}
				else {
					return 0;
				}

			}
		}
		else {
			cout << endl << "密码与id不符" << endl;
			if (DealFault() == 1) {
				cout << endl << "请输入您的id号：";
				//cin >> id;
				getline(cin, idTerm);
				cout << endl << "请输入密码：";
				//cin >> password;
				getline(cin, idTerm2);
				id = atoi(idTerm.c_str());
				idTerm2 = "" + to_string(id);
			}
			else {
				return 0;
			}
		}
	}

}


/***
由读者输入自己的id与password，调用getReaderById(id)方法找到这个id号
对应的一条记录，然后构造一个迭代器reader，因为只能有一个元素，所以直接
调用该方法的begin()方法就行，然后对比返回对象的password与用户输入的是
否一致，能符合的话就返回该用户的id号，否则返回0
***/
int ReaderLoginService() {
	int id;
	string idTerm;//用于用户输入错误id的容错处理
	string idTerm2;
	string password;
	list<Reader> readerList;

	cout << endl << "请输入您的id号：";
	//cin >> id;
	getline(cin, idTerm);
	cout << endl << "请输入密码：";
	//cin >> password;
	getline(cin, password);
	id = atoi(idTerm.c_str());
	idTerm2 = "" + to_string(id);

	while (1) {
		readerList = getReaderById(id);
		list<Reader> ::iterator reader = readerList.begin();
		if (idTerm == idTerm2 && !readerList.empty()) {
			if (reader->password == password) {
				cout << endl << "登录成功，欢迎" << reader->name << "使用本系统" << endl;
				return id;
				break;
			}
			else {
				cout << endl << "密码与id不符" << endl;
				if (DealFault() == 1) {
					cout << endl << "请输入您的id号：";
					//cin >> id;
					getline(cin, idTerm);
					cout << endl << "请输入密码：";
					//cin >> password;
					getline(cin, password);
					id = atoi(idTerm.c_str());
					idTerm2 = "" + to_string(id);
				}
				else {
					return 0;
				}

			}
		}
		else {
			cout << endl << "密码与id不符" << endl;
			if (DealFault() == 1) {
				cout << "请输入您的id号：";
				//cin >> id;
				getline(cin, idTerm);
				cout << "请输入密码：";
				//cin >> password;
				getline(cin, password);
				id = atoi(idTerm.c_str());
				idTerm2 = "" + to_string(id);
			}
			else {
				return 0;
			}
		}
	}
}


/**
调用addReader()方法，如果添加成功就返回他的id号，否则返回0
servelt层可以根据他返回的结果判断是否添加成功，以及获取添加的id号
*/
int SignUpService(Reader reader) {
	if (addReader(reader)) {
		return reader.id;
	}
	else {
		return 0;
	}
}