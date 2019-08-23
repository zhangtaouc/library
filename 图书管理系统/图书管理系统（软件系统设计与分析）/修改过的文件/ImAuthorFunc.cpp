#include"stdafx.h"
#include"AuthorFunc.h"
#include<fstream>

/*通过作者id获得作者信息
但是在作者表中，相邻两条记录的id号不一定连续
(详情见deleteAuthor)
因此不能通过计算偏移量的方法定位一个作者
如果该id的作者不存在则返回一个空list*/
list<Author> getAuthorById(int id) {
	list<Author> authorList;//建立list表
	fstream fs;
	fs.open("author.bat", ios::out | ios::in | ios::binary | ios::ate);//打开文件，其中in代表输入，out代表输出，ate表示让文件指针指向最后
	if (!fs)//如果文件不存在，输出error
	{
		cout << "open file author.bat error" << endl;
	}
	else
	{
			fs.seekg(0, ios::end);//指针跳转到文件尾
			streamoff len = fs.tellg();//获取文件字节长度
			fs.seekg(0, ios::beg);
			char * buffer = new char[sizeof(Author)];//定义author长度的buffer
			while (fs.tellg() <len) {
				fs.read(buffer, sizeof(Author));//读文件
				if (((Author*)buffer)->id == id) {//找到id所在位置
					Author authorById = *((Author*)buffer);//将buffer强制转换为author类型，并赋值给authorbyid
					authorList.push_back(authorById);//将记录添加到List末尾
					break;
				}
			}
			delete[] buffer;
	}
	fs.close();
	return authorList;


}

/*通过作者姓名查找作者信息
如果不存在姓名为name的作者返回一个空list
这里的查询为模糊查询
*/
list<Author> getAuthorByName(string name) {
	list<Author> authorList;//建立list表
	fstream fs;
	string s = "";//定义字符串用于存放姓名
	fs.open("author.bat", ios::binary | ios::in);//以读的方式打开文件
	if (!fs)//如果文件不存在，输出error
	{
		cout << "open file author.bat error" << endl;
	}
	else
	{
		fs.seekg(0, ios::end);
		streamoff len = fs.tellg();//获取文件长度
		fs.seekg(0, ios::beg);//指针指向文件头
		char*buffer = new char[sizeof(Author)];//定义author长度的buffer变量
		Author a;
		while (fs.tellg() < len)//当文件没结束时，遍历文件
		{
			fs.read(buffer, sizeof(Author));//读文件
			a = *((Author*)buffer);//强制转换
			s = a.name;
			if (s.find(name) != string::npos)//进行模糊查询
			{
				authorList.push_back(a);
			}
		}
		delete[] buffer;
	}
	fs.close();
	return authorList;
}


/*增加一条作者记录（用于增加的图书的读者从未在
读者表里出现过时）*/
bool addAuthor(Author& author) {
	fstream fs;
	fs.open("author.bat", ios::out | ios::in | ios::binary);
	//以追加的形式打开一个已经存在的文件进行读写操作(文件指针在文件末尾)
	if (!fs) {
		cout << " Error in open file author.bat. " << endl;
		return false;
	}
	//由于作者的id是自增的，刚开始需要让文件指针指向最后一条记录
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(Author))  newId = 1;//这是文件里一条记录也没有的情况
	else {//注意这里  sizeof(Author) 是无符号数，不能直接对其加符号
		int authorLen = sizeof(Author);
		fs.seekg(-authorLen, ios::end); //定位到最后一条记录的开始处

		char* buffer = new char[sizeof(Author)];
		fs.read(buffer, sizeof(Author));//读取最后一条图书记录

		Author* lastAuthor = (Author*)buffer;//将读到的数据强制类型转换

		newId = (*lastAuthor).id + 1;//得到要新增的书的id并完成赋值

		delete[] buffer;
	}
	author.id = newId;
	//然后再将文件指针定位到末尾，写一条新书的记录
	fs.seekg(0, ios::end);
	fs.write((char*)&author, sizeof(Author));
	//关闭文件读写流
	fs.close();
	return true;
}

/*注意，由于这里的删除过程中值删除无效作者
其他作者的id不变，相邻记录的id号可能不是连续的自然数
因此不能通过id直接定位作者，必须要遍历作者表一条一条查找*/
bool deleteAuthor(int id) {
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("author.bat", ios::out | ios::binary | ios::in);
	
	if (!fs) {
		cout << " Error in open file author.bat. " << endl;
		return false;
	}
	int count = sizeof(Author);//计算一条记录的字节数
	
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//记录文件总字节数

	/*list用来存储删除后的所有作者组成的集合*/
	list<Author> authorList;
	fs.seekg(0, ios::beg);

	char* buffer = new char[count];

	while (fs.tellg() < len) {//当还未到达文件末尾时继续遍历
		fs.read(buffer, count);//将一条的记录读进buffer
		if (((Author*)buffer)->id == id) continue;//如果是要删除的作者，就不加入list
		authorList.push_back(*(Author*)buffer);//要按顺序每次都将记录添加到list的末尾
	}

	delete[] buffer;//内存回收！！！
	fs.close();
	/*现在需要删除原来的文件(ios::out)
	新建一个文件，将list里的内容全部写入*/
	fs.open("author.bat", ios::out | ios::binary);
	if (!fs) {
		cout << "Open file failure in author.bat" << endl;
		return false;
	}

	for (list<Author>::iterator it = authorList.begin(); it != authorList.end(); ++it) {
		fs.write((char*)&(*it), sizeof(Author));//写一条记录
	}
	fs.close();
	return true;

}
/*
int main() {
	Author a;
	setAuthorName(a, "你好");
	addAuthor(a);
	setAuthorName(a, "nishishie");
	addAuthor(a);
	setAuthorName(a, "asshasuni");
	addAuthor(a);
	list<Author> b = getAuthorById(1);
	for (list<Author>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}
	
	deleteAuthor(1);
	
	b.clear();
	b = getAuthorById(1);

	if (b.empty()) cout << "已经删除" << endl;
	b.clear();
	b = getAuthorById(2);
	for (list<Author>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}
	
	
	b.clear();

	b = getAuthorByName("ni");
	for (list<Author>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).name << endl;
	}
	int i;
	cin >> i;
	return 1;



}*/