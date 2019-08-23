#include"stdafx.h"
#include"AdminFunc.h"
#include<fstream>
/**
* 更改管理员信息
* @param admin
* @return 若修改成功返回true，否则返回false，然后调用这个函数的函数继续进行其他处理
*/
bool modifyAdmin(Admin& admin) {
	//打开文件admin.bat时保证文件内容不被删除
	fstream fs("admin.bat", ios::out | ios::in | ios::ate | ios::binary);
	//判断打开文件admin.bat是否成功，若无法打开则输出错误信息并返回false
	if (!fs) {
		cout << "Error: Can not open file 'admin.bat'!" << endl;
		fs.close();
		return false;
	}
	//通过id计算文件指针偏移量以读取指定内容
	long pos = sizeof(Admin) * (admin.id - 1);
	//判断查找的位置是否正确,若小于0或超出文件长度则输出错误信息并返回false
	if (pos < 0 || pos > fs.tellg()) {
		cout << "Error: Input Admin ID mistaken!" << endl;
		fs.close();
		return false;
	}
	//读取指定位置的内容
	Admin* rAdmin;
	char* buffer = new char[sizeof(Admin)];
	fs.seekg(pos, ios::beg);
	fs.read(buffer, sizeof(Admin));
	rAdmin = (Admin*)buffer;
	//比较文件内查找到的rAdmin.id与所需要修改的admin.id是否相同，相同则进行文件内容修改，不相同则输出错误信息并返回false
	if (rAdmin->id == admin.id) {
		fs.seekp(pos, ios::beg);
		fs.write((char *)&admin, sizeof(Admin));
		//cout << "Modify Admin success!" << endl;
		delete[] buffer;
		fs.close();
		return true;
	}
	else {
		cout << "Error: Modify Admin ID mismatch!" << endl;
		delete[] buffer;
		fs.close();
		return false;
	}
}


/*由id号查找管理员信息
管理员登录会用到这个函数
|查找不到会返回一个空列表
*/
list<Admin> getAdminById(int id) {
	list<Admin> adminList;//建立list表
	fstream fs;
	fs.open("admin.bat", ios::out | ios::in | ios::binary | ios::ate);//打开文件，其中in代表输入，out代表输出，ate表示让文件指针指向最后
	if (!fs)//如果文件不存在，输出error
	{
		cout << "open file admin.bat error" << endl;
	}
	else
	{
		long pos = sizeof(Admin)*(id - 1);//通过id号计算指针偏移量
		if (pos<0 || pos>fs.tellg()) {
			cout << "id error" << endl;//如果偏移量小于零或者大于文件长度，输出error,返回空list
		}
		else
		{
			fs.seekg(pos, ios::beg);//指针跳转到文件头
			char * buffer = new char[sizeof(Admin)];//定义adamin长度的buffer变量
			fs.read(buffer, sizeof(Admin));//读文件
			Admin adminById = *((Admin*)buffer);//将buffer强制转换为admin类型，并赋值给adminById
			if (adminById.exist == 1)//如果未被删除，将记录添加到List末尾
			{
				adminList.push_back(adminById);
			}
			delete[] buffer;
		}
	}
	fs.close();
	return adminList;
}

/*删除一个管理员（假删除，修改exist属性即可)
若参数id不存在，函数返回false
否则假删除成功后，返回true
*/
bool deleteAdmin(int id) {
	list<Admin> adminList = getAdminById(id);
	if (adminList.empty()) return false;
	list<Admin>::iterator it = adminList.begin();

	if ((*it).exist == 0) return true;
	(*it).exist = 0;
	return modifyAdmin(*it);
}

/*新增一个管理员(用于首次新建一个管理员账号
管理员账号只有一个就够了)*/
bool addAdmin(Admin& admin) {
	fstream fs;
	fs.open("admin.bat", ios::out | ios::in | ios::binary);
	//以追加的形式打开一个已经存在的文件进行读写操作(文件指针在文件末尾)
	if (!fs) {
		cout << " Error in open file admin.bat. " << endl;
		return false;
	}
	//由于管理员的id是自增的，刚开始需要让文件指针指向
	//最后一条记录，然后获得最后一类书的id,加1就得到新书的id
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(Admin))  newId = 1;//这是文件里一条记录也没有的情况
	else {//注意这里  sizeof(Admin) 是无符号数，不能直接对其加符号
		int adminLen = sizeof(Admin);
		fs.seekg(-adminLen, ios::end); //定位到最后一条记录的开始处

		char* buffer = new char[sizeof(Admin)];
		fs.read(buffer, sizeof(Admin));//读取最后一条图书记录

		Admin* lastAdmin = (Admin*)buffer;//将读到的数据强制类型转换

		newId = (*lastAdmin).id + 1;//得到要新增的书的id并完成赋值
		delete[] buffer;
	}
	admin.id = newId;
	//然后再将文件指针定位到末尾，写一条新书的记录
	fs.seekg(0, ios::end);
	fs.write((char*)&admin, sizeof(Admin));
	//关闭文件读写流
	fs.close();

	return true;

}


/*
using namespace std;

int main()

{
Admin a;
a.exist = 1;
setAdminPd(a,"123");
addAdmin(a);
cout << a.password << endl;
list<Admin> l = getAdminById(1);
for (list<Admin>::iterator it = l.begin(); it != l.end(); ++it) {
cout << (*it).id <<" " << (*it).password << endl;
}

int i;
cin >> i;



return 0;
}*/
