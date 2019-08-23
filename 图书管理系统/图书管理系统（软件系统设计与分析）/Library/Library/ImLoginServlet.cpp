#include "stdafx.h"
#include "LoginServlet.h"
#include"LoginService.h"

/**
*要向主函数中传递2个信息，一个是用户身份，一个是id号
因而我才用键值对的形式，第一个是String类型表示用户身份
第二个是int类型，表示用户id号，如果用户选择身份出现错误，
那么构造的map对象为空，选择正确的话，下一层需要判断id号是否
为0！！！不为0表示正确。
*判断map对象是否为空是调用empty()方法，空返回1。
*获取map中对象的键值对的方法是：构造一个map对象的迭代器iter，然后
令iter = 对象名.begin(),即获取Map对象的第一个元素（其实本来元素也就只有一个）
然后iter->first,iter->second，即可获取map中的键值。
*map对象插入元素的方式直接是：对象名[key] = value，如果属性值为key
的键值对存在，就修改它的value为value，否则就新增这个键值对。
*/
map<string, int> LoginServlet() {
	string identity;
	string choice;
	map<string, int> identityMap;
	cout << endl << "请选择您的身份" << endl;
	cout << endl << "1：管理员		2：读者" << endl;
	//cin >> identity;
	getline(cin, identity);
	while (identity != "1" && identity != "2") {
		//容错处理
		if (DealFault() == 1) {
			cout << endl << "请选择您的身份" << endl;
			cout << endl << "1：管理员		2：读者" << endl;
			//cin >> identity;
			getline(cin, identity);
		}
		else {
			return identityMap;
		}
	}
	if (identity == "1") {
		int adminId = AdminLoginService();
		if (adminId) {
			identityMap["Admin"] = adminId;
		}
	}
	else if (identity == "2") {
		int readerId = ReaderLoginService();
		if (readerId) {
			identityMap["Reader"] = readerId;
		}
	}

	return identityMap;
}




/**
*这是注册功能的servlt，通过向Service层面传递reader对象完成相应功能
Reader的id，fine，exist由系统生成，name，password，sex由用户输入
注册成功返回true并告知用户的id号，失败则返回false
*接收password与name数据用string类型，然后调用strcpy()方法转换成char类型
strcpy(array,str.c_str)，通过str.length()方法判断用户输入的长度是否符合要求
使用getline(cin,str)输入带有空格的字符串
*在这里直接使用setReaderName()方法就可以修改name属性，password也是一样。
*/
bool SignUpServlet() {
	Reader reader;
	string name;
	string nameTerm;
	string password;
	string passwordTerm;
	string x;//判断用户是否要重新输入或是退出注册
	string sex;
	int exist = 1;
	double fine = 0;
	reader.exist = exist;
	reader.fine = fine;

	cout << endl << "欢迎来到注册页面" << endl;
	while (1) {
		cout << endl << "请输入您的姓名(不得超过19个字符,不得没有字符，不得全为空格)：";
		getline(cin, name);//输入可以带空格的字符串
		nameTerm = name;
		trimAllSpace(nameTerm);
		if (nameTerm.length() == 0 || name.length()<1 || name.length() > 19) {
			cout << endl << "您输入的字符串不符合要求，请重新输入或退出注册" << endl;
			cout << endl << "1：重新输入		0：退出注册" << endl;
			//cin >> x;
			getline(cin, x);
			if (x == "1") {
			}
			else if (x == "0") {
				cout << endl << "注册失败" << endl;
				return false;
			}
			else {
				if (DealFault()) {

				}
				else {
					cout << endl << "注册失败" << endl;
					return false;
				}
			}

		}
		else {
			cout << endl << "您的姓名为：" << name << ",请确认是否正确" << endl;
			cout << endl << "1：正确   0：错误" << endl;
			getline(cin, x);
			if (x == "1") {
				setReaderName(reader, name);
				break;
			}
			else if (x == "0") {

			}
			else {
				if (DealFault()) {

				}
				else {
					cout << endl << "注册失败" << endl;
					return false;
				}
			}

		}
	}

	while (1) {
		cout << endl << "请输入您的密码(要求5-10个字符,不能含有空格，不能为汉字等全角字符)：";
		getline(cin, password);
		passwordTerm = password;
		trimAllSpace(passwordTerm);//除去空格

		if (IsDoubleChar(password) || (passwordTerm.length() != password.length()) || password.length()<5 || password.length()>10) {
			cout << endl << "您输入的字符串不符合要求，请重新输入或退出注册" << endl;
			cout << "1：重新输入		0：退出注册" << endl;
			//cin >> x;
			getline(cin, x);

			if (x == "1") {
			}
			else if (x == "0") {
				cout << "注册失败" << endl;
				return false;
			}
			else {
				if (DealFault()) {

				}
				else {
					cout << "注册失败" << endl;
					return false;
				}
			}

		}
		else {
			cout << endl << "您的密码为：" << password << ",请确认是否正确" << endl;
			cout << endl << "1：正确   0：错误" << endl;
			getline(cin, x);
			if (x == "1") {
				setReaderPw(reader, password);
				break;
			}
			else if (x == "0") {

			}
			else {
				if (DealFault()) {

				}
				else {
					cout << endl << "注册失败" << endl;
					return false;
				}
			}

		}
	}

	while (1) {
		cout << endl << "请输入您的性别（1：男性  0：女性）" << endl;
		getline(cin, sex);
		if (sex != "1" && sex != "0") {
			cout << endl << "您的输入不符合要求，请选择继续或者退出" << endl;
			cout << endl << "1：继续       0：退出" << endl;
			getline(cin, x);
			if (x == "1") {

			}
			else if (x == "0") {
				cout << endl << "注册失败" << endl;
				return false;
			}
			else {
				if (DealFault()) {

				}
				else {
					return false;
				}
			}
		}
		else {
			reader.sex = atoi(sex.c_str());
			break;
		}
	}

	reader.id = SignUpService(reader);

	if (reader.id) {
		cout << endl << "注册成功！您的id号是" << reader.id << endl;
		return true;
	}
	else {
		cout << endl << "注册失败" << endl;
		return false;
	}

}