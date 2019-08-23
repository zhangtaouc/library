
#include"stdafx.h"
#include<list>
#include"Structs.h"
#include"ReaderFunc.h"
#include"showInfo.h"
#include<string>
#include"DealFault.h"



list<Reader> QueryReaderById(int id)
{
	list<Reader> readerList = getReaderById(id);
	if (readerList.empty())
	{
		cout << "NOT FOUND!";
		readerList.clear();
		return readerList;
	}
	//调用showInfo，该函数未添加
	showReaderInfo(readerList);
	return readerList;
}

//按照读者姓名查找读者，参数为string型的name，直接在函数内调用显示函数显示查询到的结果
void QueryReaderByName(string name)
{
	list<Reader> readerList = getReadersByName(name);
	if (readerList.empty())
	{
		cout << "NOT FOUND!";
		return;
	}
	//调用showInfo，该函数未添加
	showReaderInfo(readerList);
	return;
}

//按照读者性别查找读者，参数为int型的sex，直接在函数内调用显示函数显示查询到的结果
void QueryReaderBySex(int sex)
{
	list<Reader> readerList = getReadersBySex(sex);
	if (readerList.empty())
	{
		cout << "NOT FOUND!";
		return;
	}
	//调用showInfo，该函数未添加
	showReaderInfo(readerList);
	return;
}

//获取所有读者信息，无参数，直接在函数内调用显示函数显示查询到的结果
void QueryAllReader()
{
	list<Reader> readerList = getReaders();
	if (readerList.empty())
	{
		cout << "NOT FOUND!";
		return;
	}
	//调用showInfo，该函数未添加
	showReaderInfo(readerList);
	return;
}



/*按条件查询符合相应条件的读者并展示给用户看*/
//按条件（id，姓名，性别，所有）查询读者，已被删除（假删除）的读者不会被检索到
void QueryReaderService() {
	while (1)
	{
		string key;//代表查找的条件
		string name;
		cout << endl << "请输入您查找的条件" << endl << "1 id" << endl << "2 姓名" << endl << "3 性别" << endl << "4 显示所有读者信息" << endl << "其他为退出查询 " << endl;
		getline(cin, key);
		if (key == "1")//根据id查找读者
		{
			cout << endl << "请输入您要查找的读者的id" << endl;
			int id;//临时存储要查找的读者的id
			id = GetIntFromCin();

			while (id <= 0)//id必须输入int型且大于0，否则报错并要求重新输入
			{
				cout << endl << "输入有误，请重新输入！" << endl;
				id = GetIntFromCin();
			}
			QueryReaderById(id);
		}
		else if (key == "2")//根据姓名查找读者
		{
			cout << endl << "请输入您要查找的读者的姓名" << endl;
			string name;//临时存储要查找的读者的姓名
			getline(cin, name);
			QueryReaderByName(name);

		}
		else if (key == "3")//根据性别查找读者
		{
			cout << endl << "请输入该读者的性别,1表示男性，0表示女性" << endl;
			int tempSex;//临时存储该读者的性别;
			tempSex = GetIntFromCin();
			while (tempSex != 0 && tempSex != 1)//性别必须为整形，不能输入除了一和零之外的值
			{
				cout << endl << "输入不合法！不能输入除了1和0之外的字符,请重新输入" << endl;
				tempSex = GetIntFromCin();
			}
			QueryReaderBySex(tempSex);
		}
		else if (key == "4")//显示所有读者信息
		{
			QueryAllReader();
		}
		else
		{
			cout << endl << "查询已结束！" << endl;
			return
				;
		}
	}

}


/*增加一类读者的service*/
//增加读者，可以增加一批，参数为list<Reader>
void AddReaderService(list<Reader> readerList)
{
	if (readerList.empty())
	{
		cout << "empty rederList";
		return;
	}

	//bool status = true;//status为true表示添加过程中没有出错，为false表示出错
	for (list<Reader> ::iterator it = readerList.begin(); it != readerList.end(); it++)
	{
		if (!addReader(*it))
		{
			cout << "添加读者失败，读者id为" << it->id << endl;
		}
	}
	return;
}

//删除读者，一次只删除一个，参数为Reader.id
void DeleteReaderService(int id)
{
	Reader aReader;
	list<Reader> readerList = getReaderById(id);
	if (readerList.empty())
	{
		cout << endl << "查无此人哟~" << endl;
		return;
	}
	aReader = readerList.back();
	aReader.exist = 0;
	if (!modifyReader(aReader))
		cout << "删除读者失败" << endl;
	else
		cout << endl << "id为" << id << "的读者已删除" << endl;
	return;
}



bool ModifyReaderName(Reader &reader) {
	string name;

	cout << "请输入修改的姓名，输入0取消修改：";
	getline(cin, name);

	if (name == "0")
		return false;
	else
		copy(reader.name, name, sizeof(Reader::name));
	return true;
}

bool ModifyReaderPassword(Reader &reader) {


	string password;

	cout << "请输入修改的密码，请注意，密码只允许包含英文字符及数字，输入0取消修改：";
	getline(cin, password);

	if (password == "0")
		return false;
	else
		//读者密码容错

		copy(reader.password, password, sizeof(Reader::password));
	return true;
}

bool ModifyReaderSex(Reader &reader) {
	int sex;

	for (;;) {
		cout << "请输入修改的性别，0.女，1.男，2.取消修改：";
		sex = GetIntFromCin();

		if (sex == 2)
			return false;
		//性别只有两种
		else if (sex != 0 && sex != 1)
			cout << "您的输入有误，请重新输入" << endl;
		else {
			reader.sex = sex;
			break;
		}
	}
	return true;
}

bool ModifyReaderFine(Reader &reader) {
	double fine = -1;

	for (;;) {
		cout << "请输入修改的欠款金额，输入-1取消修改：";
		cin >> fine;
		//读者欠款容错

		if (fine == -1)
			return false;
		//欠款必须大于等于0
		else if (fine < 0)
			cout << "欠款金额必须大于0，您的输入有误，请重新输入" << endl;
		else {
			reader.fine = fine;
			break;
		}
	}
	return true;
}

//管理员修改任意一个读者信息
void AdminModifyReaderService() {
	//flag用于判断是否经过修改
	bool flag = false;
	int id;
	Reader reader;
	list<Reader> readerList;

	for (;;) {
		//通过id查找到读者
		cout << endl;
		cout << "请输入所查询读者的ID，输入0取消查询：";
		id = GetIntFromCin();

		if (id == 0)
			return;
		else
			readerList = QueryReaderById(id);
		if (readerList.empty())
			return;

		reader = readerList.back();
		readerList.pop_back();

		//实现修改多个属性
		for (int i = -1; i != 0;) {
			//选择修改的选项
			cout << endl;
			cout << "请选择需要修改的信息,若确认修改请输入0：" << endl;
			cout << "0.确认当前修改" << endl;
			cout << "-1.取消修改" << endl;
			cout << "1.姓名" << endl;
			cout << "2.密码" << endl;
			cout << "3.性别" << endl;
			cout << "4.欠款金额" << endl;
			i = GetIntFromCin();

			//实现功能的选择
			switch (i) {
			case 1:
				flag = ModifyReaderName(reader);
				break;
			case 2:
				flag = ModifyReaderPassword(reader);
				break;
			case 3:
				flag = ModifyReaderSex(reader);
				break;
			case 4:
				flag = ModifyReaderFine(reader);
				break;
			case 0:
				break;
			case -1:
				return;
			default:
				cout << "您的输入有误，请重新输入" << endl;
			}
		}

		if (flag) {
			flag = false;
			cout << "确认修改？确认请输入1，取消请输入0：";
			int t = GetIntFromCin();

			if (t == 1) {
				//调用函数修改读者信息
				if (modifyReader(reader)) {
					cout << "修改读者信息成功！" << endl;
					//输出完成修改的读者的信息
					readerList.clear();
					readerList.push_back(reader);
					showReaderInfo(readerList);
					return;
				}
				else
					cout << "修改读者信息失败！" << endl;
			}
			else if (t == 0)
				cout << "修改取消！" << endl;
			else
				cout << "您的输入有误，请重新输入" << endl;
		}
	}
}

//读者修改自己基本信息
void ReaderModifySelfService(int id) {
	//flag用于判断是否经过修改
	bool flag = false;
	Reader reader;
	list<Reader> readerList;

	for (;;) {
		readerList = QueryReaderById(id);

		reader = readerList.back();
		readerList.pop_back();

		//实现修改多个属性
		for (int i = -1; i != 0;) {
			//选择修改的选项
			cout << endl;
			cout << "请选择需要修改的信息,若确认修改请输入0：" << endl;
			cout << "0.确认当前修改" << endl;
			cout << "-1.取消修改" << endl;
			cout << "1.姓名" << endl;
			cout << "2.密码" << endl;
			cout << "3.性别" << endl;
			i = GetIntFromCin();

			string oriPwd;
			int okay = 1;
			int times = 5;//每次输入密码最多可以输五次
			//实现功能的选择
			switch (i) {
			case 1:
				flag = ModifyReaderName(reader);
				break;
			case 2:
				while (1) {
					if (times < 0) {
						cout << "您已经输入密码错误5次了！不能继续输入！" << endl;
						break;
					}
					cout << "请输入您原来的密码：";
					getline(cin, oriPwd);
					for (int j = 0; j < oriPwd.length() && j < sizeof(reader.password); j++) {
						if (oriPwd[j] != reader.password[j]) {
							okay = 0;
							break;
						}
					}
					if (okay) {
						flag = ModifyReaderPassword(reader);
						break;
					}
					else {
						cout << endl << "您输入的密码有误！" << endl;
						times--;
					}
				}
				break;
			case 3:
				flag = ModifyReaderSex(reader);
				break;
			case 0:
				break;
			case -1:
				return;
			default:
				cout << "您的输入有误，请重新输入" << endl;
			}
		}

		if (flag) {
			flag = false;
			cout << "确认修改？确认请输入1，取消请输入0：";
			int t = GetIntFromCin();

			if (t == 1) {
				//调用函数修改读者信息
				if (modifyReader(reader)) {
					cout << "您的信息修改成功！" << endl;
					//输出完成修改的读者的信息
					readerList.clear();
					readerList.push_back(reader);
					showReaderInfo(readerList);
					return;
				}
				else
					cout << "您的信息修改失败！请重试" << endl;
			}
			else if (t == 0)
				cout << "修改取消！" << endl;
			else
				cout << "您的输入有误，请重新输入" << endl;
		}
	}
}



//读者缴纳欠款
void PayTheFeesService(int readerId) {

	list<Reader> reader = getReaderById(readerId);
	list<Reader>::iterator it = reader.begin();
	cout << "您的欠款为:" << ((*it).fine) << endl;

	if ((*it).fine == 0) {
		cout << "您无需缴纳欠款！" << endl;
	}
	else {

		int select;
		while (1) {
			cout << endl << "1.缴纳所有欠款" << endl;
			cout << "2.退出当前界面" << endl;
			cout << "请输入选项：";
			select = GetIntFromCin();
			switch (select)
			{
			case 1:
				((*it).fine = 0);
				modifyReader(*it);
				cout << endl << "您的欠款缴纳成功！当前欠款为0！" << endl;
				break;
			case 2:return;
			default:
				cout << endl << "只能输入1或2！" << endl;
				continue;
			}

		}

	}

}

