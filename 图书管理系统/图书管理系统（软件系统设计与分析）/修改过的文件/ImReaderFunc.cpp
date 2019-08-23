#include"stdafx.h"
#include"ReaderFunc.h"
#include<fstream>

/**
* 根据唯一的Id查找读者
* 找不到返回一个空list
* @param id
* @return
*/
list<Reader> getReaderById(int id) {
	list<Reader> readerList;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("reader.bat", ios::out | ios::binary | ios::in | ios::ate);
	//打开一个已存在的文件读,并让文件指针指向最后

	if (!fs) {
		cout << "In function getReaderById ..." << endl;
		cout << " Error in open file reader.bat. " << endl;
		return readerList;
	}

	/*通过读者的id号来计算文件指针偏移量
	如果计算得到的偏移量大于文件字节长度或者小于0，直接返回空list
	*/
	long pos = sizeof(Reader) * (id - 1);
	if (pos < 0 || pos > fs.tellg()) {
		fs.close();
		return readerList; }

	fs.seekg(pos, ios::beg);
	char* buffer = new char[sizeof(Reader)];
	fs.read(buffer, sizeof(Reader));//读出记录
	Reader aReader = *((Reader*)buffer);

	if (aReader.exist == 1)//！！！！！！！！！！！！！！！！只查找没有被删除的读者
		readerList.push_back(aReader);//将记录添加到list末尾
	fs.close();
	delete[] buffer;
	return readerList;
}

/**
* 根据性别查找读者
* @param sex sex取1代表男性，0代表女性
* 这和类定义里sex属性是一致的
* 找不到返回一个空list
* @return
*/
list<Reader> getReadersBySex(int sex) {
	list<Reader> readerList;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("reader.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		//cout << "In function getReaderBySex ..." << endl;
		cout << " Error in open file reader.bat " << endl;
		return readerList;
	}

	//获取文件长度
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();
	fs.seekg(0, ios::beg);

	char* buffer = new char[sizeof(Reader)];//用来读取一条记录的缓冲区
	Reader aReader;
	int tempSex;//用来存放当前读出的记录的sex字段

				/*当文件还未结束时，继续遍历文件*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Reader));//读出记录
		aReader = *((Reader*)buffer);
		if (aReader.exist == 0) continue;//如果当前读者不存在，直接找下一条记录!!!!!!!!
		tempSex = aReader.sex;

		if (tempSex == sex)//看不懂
			readerList.push_back(aReader);//匹配则加入list
	}
	fs.close();
	delete[] buffer;
	return readerList;
}

/**
* 根据名字查找读者(模糊查询)
* @param name
* @return
*/
list<Reader> getReadersByName(string name) {
	list<Reader> readerList;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("reader.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		//cout << "In function getReaderByName ..." << endl;
		cout << " Error in open file reader.bat " << endl;
		return readerList;
	}

	//获取文件长度
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();
	fs.seekg(0, ios::beg);

	char* buffer = new char[sizeof(Reader)];//用来读取一条记录的缓冲区
	Reader aReader;
	string s = "";//用来存放当前读出的记录的name字段
				  /*当文件还未结束时，继续遍历文件*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Reader));//读出记录
		aReader = *((Reader*)buffer);
		if (aReader.exist == 0) continue;//如果当前书读者不存在，直接找下一条记录!!!!!!!!
		s = aReader.name;
		//trimAllSpace(name);//将传入的字符串去掉所有空格

		if (s.find(name) != string::npos)//看不懂
			readerList.push_back(aReader);//匹配则加入list
	}
	fs.close();
	delete[] buffer;
	return readerList;
}

/**
* 获得所有读者的信息
* @return
*/
list<Reader> getReaders() {
	//读入所有读者记录
	list<Reader> readerList;
	char* buffer = new char[sizeof(Reader)];//buffer作为缓冲指针
	ifstream infile("reader.bat", ios::binary);
	if (!infile)
	{
		//cout << "In function getReaders ..." << endl;
		cout << " Error in open file Reader.bat. " << endl;
		return readerList;
	}

	//获取文件长度
	infile.seekg(0, ios::end);
	streamoff len = infile.tellg();
	infile.seekg(0, ios::beg);

	Reader aReader;
	while (infile.tellg() < len)
	{
		infile.read(buffer, sizeof(Reader));
		aReader = *((Reader*)buffer);
		//Reader aReader = *((Reader*)buffer);
		if (aReader.exist == 1)
			readerList.push_back(aReader);
	}
	infile.close();
	delete[] buffer;
	return readerList;
	/*测试用，测试结果成功
	for (it = readerList.begin(); it != readerList.end(); it++)
	{
	cout << it->name << endl;
	}
	*/
}


/**
* /添加读者
* 这里也是只考虑向读者表中添加一条读者记录
* 检查读者信息的工作上一层来完成
* 调用完这个函数后，参数reader的id会被置为其在文件中的id号
* @param reader
* @return
*/
bool addReader(Reader& reader) {
	fstream fs;
	fs.open("reader.bat", ios::out | ios::in | ios::binary);
	//以追加的形式打开一个已经存在的文件进行读写操作(文件指针在文件末尾)
	if (!fs) {
		cout << " Error in open file reader.bat. " << endl;
		return false;
	}
	//由于读者的id是自增的，刚开始需要让文件指针指向最后一条记录
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(Reader))  newId = 1;//这是文件里一条记录也没有的情况
	else {//注意这里  sizeof(Reader) 是无符号数，不能直接对其加符号
		int readerLen = sizeof(Reader);
		fs.seekg(-readerLen, ios::end); //定位到最后一条记录的开始处

		char* buffer = new char[sizeof(Reader)];
		fs.read(buffer, sizeof(Reader));//读取最后一条图书记录

		Reader* lastReader = (Reader*)buffer;//将读到的数据强制类型转换

		newId = (*lastReader).id + 1;//得到要新增的书的id并完成赋值
		delete[] buffer;
	}
	reader.id = newId;
	//然后再将文件指针定位到末尾，写一条新书的记录
	fs.seekg(0, ios::end);
	fs.write((char*)&reader, sizeof(Reader));
	//关闭文件读写流
	fs.close();
	return true;

}

/**
* 更改读者信息
* @param reader
* @return
*/

bool modifyReader(Reader& reader) {
	//打开文件reader.bat时保证文件内容不被删除
	fstream fs("reader.bat", ios::out | ios::in | ios::ate | ios::binary);
	//判断打开文件reader.bat是否成功，若无法打开则输出错误信息并返回false
	if (!fs) {
		cout << "Error: Can not open file 'reader.bat'!" << endl;
		fs.close();
		return false;
	}
	//通过id计算文件指针偏移量以读取指定内容
	long pos = sizeof(Reader) * (reader.id - 1);
	//判断查找的位置是否正确,若小于0或超出文件长度则输出错误信息并返回false
	if (pos < 0 || pos > fs.tellg()) {
		cout << "Error: Input Reader ID mistaken!" << endl;
		fs.close();
		return false;
	}
	//读取指定位置的内容
	Reader* rReader;
	char* buffer = new char[sizeof(Reader)];
	fs.seekg(pos, ios::beg);
	fs.read(buffer, sizeof(Reader));
	rReader = (Reader*)buffer;
	//比较文件内查找到的rReader.id与所需要修改的reader.id是否相同，相同则进行文件内容修改，不相同则输出错误信息并返回false
	if (rReader->id == reader.id) {
		fs.seekp(pos, ios::beg);
		fs.write((char *)&reader, sizeof(Reader));
		//cout << "Modify Reader success!" << endl;
		fs.close();
		delete[] buffer;
		return true;
	}
	else {
		cout << "Error: Modify Reader ID mismatch!" << endl;
		fs.close();
		delete[] buffer;
		return false;
	}
	
}

/*删除一个读者(假删除，修改exist属性即可)
如果参数id不存在，函数返回false
否则，假删除成功后函数返回true
*/
bool deleteReader(int id) {
	list<Reader> readerList = getReaderById(id);
	if (readerList.empty()) return false;
	list<Reader>::iterator it = readerList.begin();

	if ((*it).exist == 0) return true;
	(*it).exist = 0;
	return modifyReader(*it);
}