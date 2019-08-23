#include"stdafx.h"
#include"TypeFunc.h"
#include<fstream>

/*新增一个书的类型*/
bool addType(Type& type) {
	fstream fs;
	fs.open("type.bat", ios::out | ios::in | ios::binary);
	//以追加的形式打开一个已经存在的文件进行读写操作(文件指针在文件末尾)
	if (!fs) {
		cout << " Error in open file type.bat. " << endl;
		return false;
	}
	//由于type的id是自增的，刚开始需要让文件指针指向最后一条记录
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(Type))  newId = 1;//这是文件里一条记录也没有的情况
	else {//注意这里  sizeof(Type) 是无符号数，不能直接对其加符号
		int typeLen = sizeof(Type);
		fs.seekg(-typeLen, ios::end); //定位到最后一条记录的开始处

		char* buffer = new char[sizeof(Type)];
		fs.read(buffer, sizeof(Type));//读取最后一条图书记录

		Type* lastType = (Type*)buffer;//将读到的数据强制类型转换

		newId = (*lastType).id + 1;//得到要新增的type的id并完成赋值
		delete[] buffer;
	}
	type.id = newId;
	//然后再将文件指针定位到末尾，写一条新书的记录
	fs.seekg(0, ios::end);
	fs.write((char*)&type, sizeof(Type));
	//关闭文件读写流
	fs.close();
	return true;
}

bool modifyType(Type& type) {
	//打开文件type.bat时保证文件内容不被删除
	fstream fs("type.bat", ios::out | ios::in | ios::ate | ios::binary);
	//判断打开文件type.bat是否成功，若无法打开则输出错误信息并返回false
	if (!fs) {
		cout << "Error: Can not open file 'type.bat'!" << endl;
		return false;
	}
	//通过id计算文件指针偏移量以读取指定内容
	long pos = sizeof(Type) * (type.id - 1);
	//判断查找的位置是否正确,若小于0或超出文件长度则输出错误信息并返回false
	if (pos < 0 || pos > fs.tellg()) {
		cout << "Error: Input type ID mistaken!" << endl;
		fs.close();
		return false;
	}
	//读取指定位置的内容
	Type* rType;
	char* buffer = new char[sizeof(Type)];
	fs.seekg(pos, ios::beg);
	fs.read(buffer, sizeof(Type));
	rType = (Type*)buffer;
	//比较文件内查找到的rType.id与所需要修改的type.id是否相同
	//相同则进行文件内容修改，不相同则输出错误信息并返回false
	if (rType->id == type.id) {
		fs.seekp(pos, ios::beg);
		fs.write((char *)&type, sizeof(Type));
		fs.close();
		delete[] buffer;
		return true;
		//cout << "Modify Type success!" << endl;
	}
	else {
		cout << "Error: Modify Type ID mismatch!" << endl;
		fs.close();
		delete[] buffer;
		return false;
	}
}

list<Type> getTypeById(int id) {
	list<Type> typelist;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("Type.bat", ios::out | ios::binary | ios::in | ios::ate);
	//打开一个已存在的文件读,并让文件指针指向最后

	if (!fs) {
		cout << " Error in open file Type.bat. " << endl;
		return typelist;
	}

	/*通过type的id号来计算文件指针偏移量
	如果计算得到的偏移量大于文件字节长度或者小于0，直接返回空list
	*/
	long pos = sizeof(Type) * (id - 1);
	if (pos < 0 || pos > fs.tellg()) { 
		fs.close();
		return typelist;
	}

	fs.seekg(pos, ios::beg);
	char* buffer = new char[sizeof(Type)];
	fs.read(buffer, sizeof(Type));//读出记录
	Type type = *((Type*)buffer);
	typelist.push_back(type);//将记录添加到list末尾

	fs.close();
	delete[] buffer;

	return typelist;

}

/*根据类别名找到相应的类别(模糊查询)*/
list<Type> getTypeByName(string name) {
	list<Type> Typelist;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("type.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		cout << " Error in open file type.bat " << endl;
		return Typelist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//获取文件长度
							   //定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Type)];//用来读取一条记录的缓冲区
	Type type;
	string s = "";//用来存放当前读出的记录的name字段
				  /*当文件还未结束时，继续遍历文件*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Type));//读出记录
		type = *((Type*)buffer);
		s = type.name;
		trimAllSpace(name);//将传入的字符串去掉所有空格

		if (s.find(name) != string::npos)
			Typelist.push_back(type);//匹配则加入list
	}
	fs.close();
	delete[] buffer;
	return Typelist;
}



/*返回所有类别组成的list*/
list<Type> getAllTypes() {
	list<Type> Typelist;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("type.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		cout << " Error in open file type.bat " << endl;
		return Typelist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//获取文件长度
							   //定位到文件开头

	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Type)];//用来读取一条记录的缓冲区
	

	while (fs.tellg() < len) {
		Type type;
		fs.read(buffer, sizeof(Type));//读出记录
		type = *((Type*)buffer);
		Typelist.push_back(type);//加入list
	}

	fs.close();
	delete[] buffer;
	return Typelist;
}


/*
int main() {
	Type t;
	setTypeName(t,"nihao");
	addType(t);
	list<Type> b = getTypeById(1);
	for (list<Type>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}

	
	b.clear();
	b = getTypeById(1);

	for (list<Type>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}


	b.clear();

	b = getTypeByName("ni");
	for (list<Type>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}
	int i;
	cin >> i;
	return 1;




}*/