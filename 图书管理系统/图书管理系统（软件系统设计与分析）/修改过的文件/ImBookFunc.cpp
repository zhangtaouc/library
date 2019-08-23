#include"stdafx.h"
#include"BookFunc.h"
#include"Operation.h"
#include<fstream>
using namespace std;
/*把函数声明放在头文件里，这样有函数需要调用
BooksFunction函数中的其中一个时，只需要
把这个头文件include进来就可以啦*/


/*通过图书唯一的id号查询这本书的信息并返回
找不到就返回空list*/
list<Book> getBookById(int id) {
	list<Book> booklist;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app 
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("book.bat", ios::out | ios::binary|ios::in|ios::ate);
	//打开一个已存在的文件读,并让文件指针指向最后

	if (!fs) {
		//cout << "In function getBookById ..." << endl;
		cout << " Error in open file book.bat. " << endl;
		return booklist;
	}
	
	/*通过图书的id号来计算文件指针偏移量
	如果计算得到的偏移量大于文件字节长度或者小于0，直接返回空list
	*/
	long pos = sizeof(Book) * (id - 1);
	if (pos < 0 || pos > fs.tellg()) { 
		fs.close();
		return booklist;
	}

	fs.seekg(pos, ios::beg);
	char* buffer = new char[sizeof(Book)];
	fs.read(buffer, sizeof(Book));//读出记录-
	Book book = *((Book*)buffer);

	if(book.exist == 1)//！！！！！！！！！！！！！！！！只查找没有被删除的书籍
	booklist.push_back(book);//将记录添加到list末尾
	fs.close();
	delete[] buffer;
	return booklist;

}

/**
* 根据ISBN码查询书籍
* exist属性为1时只在未被删除的书中查找
* 为0时在所有的书中查找
* 找不到就返回空list
* @param ISBN
* @return
*/
list<Book> getBookByISBN(string ISBN,int exist) {
	list<Book> booklist;
	//if (!isISBN(ISBN)) return booklist;//如果ISBN格式不正确，直接返回空list
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("book.bat", ios::out | ios::binary | ios::in);
	//打开一个已存在的文件读,并让文件指针指向最后

	if (!fs) {
		//cout << "In function getBookByISDN ..." << endl;
		cout << " Error in open file book.bat " << endl;
		return booklist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//获取文件长度
	fs.seekg(0, ios::beg);
	string isbn = "";
	char* buffer = new char[sizeof(Book)];//用来读取一条记录的缓冲区
	Book book;
	/*当没有查找到相应的ISBN且文件还未结束时，继续遍历文件*/
	while (fs.tellg() < len && isbn != ISBN) {
		fs.read(buffer, sizeof(Book));//读出记录
		book = *((Book*)buffer);
		isbn = book.ISBN;
	}
	if (isbn == ISBN) {
		if (exist == 1) {//只查找未被删除的书籍
			if (book.exist == 0) return booklist;//若查到的书籍已经被删除，返回空list!!!!!!!!!
		}
		booklist.push_back(book);//找到就将记录添加到list末尾
	}
	fs.close();
	delete[] buffer;
	return booklist;

}

/*通过类别号找到属于这个类别的所有图书并返回
* 注意查找得到的书的exist属性都需要为1
如果没有找到则返回空list
*/
list<Book> getBooksByType(int typeId,int exist) {
	list<Book> booklist;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("book.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		//cout << "In function getBookByType ..." << endl;
		cout << " Error in open file book.bat " << endl;
		return booklist;
	}
	//把指针移到文件末尾以获取文件长度
	fs.seekg(0, ios::end);
	streamoff len = fs.tellg();//获取文件长度
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Book)];//用来读取一条记录的缓冲区
	Book book;
	/*当文件还未结束时，继续遍历文件*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Book));//读出记录
		book = *((Book*)buffer);
		if (book.exist != exist) continue;//如果当前书籍不存在，直接找下一条记录!!!!!!!
		for (int i = 0; i < (sizeof(book.type) / sizeof(int)); i++) {
			if (book.type[i] == typeId) {
				booklist.push_back(book);
				break;//若当前书籍属于这一类，就把它加入booklist，然后读下一行记录
			}
		}
	}
	//删除指针，返回内存
	delete[](buffer);
	fs.close();
	return booklist;
}

/*根据作者号找到这个作者写过的所有书
找不到就返回空list*/
list<Book> getBooksByAuthor(int authorId) {
	list<Book> booklist;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("book.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		//cout << "In function getBookByAuthor ..." << endl;
		cout << " Error in open file book.bat " << endl;
		return booklist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//获取文件长度
	//定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Book)];//用来读取一条记录的缓冲区
	Book book;
	/*当文件还未结束时，继续遍历文件*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Book));//读出记录
		book = *((Book*)buffer);
		if (book.exist == 0) continue;//如果当前书籍不存在，直接找下一条记录!!!!!!!!
		for (int i = 0; i < (sizeof(book.author) / sizeof(int)); i++) {
			if (book.author[i] == authorId) {
					booklist.push_back(book);
				break;//若当前书籍属于这一类，就把它加入booklist，然后读下一行记录
			}
		}
	}
	fs.close();
	delete[] buffer;
	return booklist;
}

/*由出版社的名字找到其出版的图书
按出版社名字查找也是模糊查询
找不到就返回空list*/
list<Book> getBooksByPublisher(string publisher) {
	list<Book> booklist;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("book.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		//cout << "In function getBookByPublisher ..." << endl;
		cout << " Error in open file book.bat " << endl;
		return booklist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//获取文件长度
	//定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Book)];//用来读取一条记录的缓冲区
	Book book;
	string s = "";//用来存放当前读出的记录的publisher字段
	/*当文件还未结束时，继续遍历文件*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Book));//读出记录
		book = *((Book*)buffer);
		if (book.exist == 0) continue;//如果当前书籍不存在，直接找下一条记录!!!!!!!!
		s = book.publisher;
		trimAllSpace(publisher);//将传入的字符串去掉所有空格

		if (s.find(publisher) != string::npos)
			booklist.push_back(book);//匹配则加入list
	}
	fs.close();
	delete[] buffer;
	return booklist;

}

//这里用string 类型是为了不越界访问字符数组
//如果参数类型是char*,我们无法准确知道传进来的字符数组有多长

/*通过图书名查询图书 这里做的是模糊查询(查找子字符串)
输入的参数name可以有空格
找不到就返回空list*/
list<Book> getBooksByName(string name) {
	list<Book> booklist;
	fstream fs;
	/*一定要注意读文件时打开已有文件的方式 : ios::in 或 ios::app
	如果没有这两个方式，已存在的文件会被删除，然后新建一个同名文件
	*/
	fs.open("book.bat", ios::binary | ios::in);
	//打开一个已存在的文件读

	if (!fs) {
		cout << " Error in open file book.bat " << endl;
		return booklist;
	}

	fs.seekg(0, ios::end);
	streampos len = fs.tellg();//获取文件长度
							//定位到文件开头
	fs.seekg(0, ios::beg);
	char* buffer = new char[sizeof(Book)];//用来读取一条记录的缓冲区
	Book book;
	string s = "";//用来存放当前读出的记录的name字段
				  /*当文件还未结束时，继续遍历文件*/
	while (fs.tellg() < len) {
		fs.read(buffer, sizeof(Book));//读出记录
		book = *((Book*)buffer);
		if (book.exist == 0) continue;//如果当前书籍不存在，直接找下一条记录!!!!!!!!
		s = book.name;
		trimAllSpace(name);//将传入的字符串去掉所有空格

		if (s.find(name) != string::npos)
			booklist.push_back(book);//匹配则加入list
	}
	fs.close();
	delete[] buffer;
	return booklist;

}


/**
* 更改书籍信息
* 参数是已经修改过的书籍的信息
* 该函数通过书籍的id号计算出记录所在位置
* 然后修改书籍信息
* @param books
* @return
*/
bool modifyBook(Book& book) {
	//打开文件book.bat时保证文件内容不被删除
	fstream fs("book.bat", ios::out | ios::in | ios::ate | ios::binary);
	//判断打开文件book.bat是否成功，若无法打开则输出错误信息并返回false
	if (!fs) {
		cout << "Error: Can not open file 'book.bat'!" << endl;
		fs.close();
		return false;
	}
	//通过id计算文件指针偏移量以读取指定内容
	long pos = sizeof(Book) * (book.id - 1);
	//判断查找的位置是否正确,若小于0或超出文件长度则输出错误信息并返回false
	if (pos < 0 || pos > fs.tellg()) {
		cout << "Error: Input Book ID mistaken!" << endl;
		fs.close();
		return false;
	}
	//读取指定位置的内容
	Book* rBook;
	char* buffer = new char[sizeof(Book)];
	fs.seekg(pos, ios::beg);
	fs.read(buffer, sizeof(Book));
	rBook = (Book*)buffer;
	//比较文件内查找到的rBook.id与所需要修改的Book.id是否相同，相同则进行文件内容修改，不相同则输出错误信息并返回false
	if (rBook->id == book.id) {
		fs.seekp(pos, ios::beg);
		fs.write((char *)&book, sizeof(Book));
		fs.close();
		delete[] buffer;
		return true;
		//cout << "Modify Book success!" << endl;
	}
	else {
		cout << "Error: Modify Book ID mismatch!" << endl;
		fs.close();
		delete[] buffer;
		return false;
	}
	
}

/*删除一个书籍（假删除，修改exist属性即可)
若参数id不存在，函数返回false
否则假删除成功后，返回true
*/
bool deleteBook(int id) {
	list<Book> bookList = getBookById(id);
	if (bookList.empty()) return false;
	list<Book>::iterator it = bookList.begin();

	if ((*it).exist == 0) return true;
	(*it).exist = 0;
	return modifyBook(*it);
}

/**
* 添加新种类的书籍
* 该函数只负责将一类新的book(一本新书)加进图书馆！！
* 对这本书数据的检查工作在上一层完成
* (上一层需要检查要增加的这本书的ISBN是否已经存在记录里
* 如果要添加的书籍的ISBN已经存在，就让管理员输入要添加的数目
* 然后调用modify函数修改馆藏数量和总数量)
* 还要检查这本书的各种信息格式是否正确
* @param book
* @return
*/
bool addBook(Book& book) {
	fstream fs;
	fs.open("book.bat", ios::out |ios::in| ios::binary);
	//以追加的形式打开一个已经存在的文件进行读写操作(文件指针在文件末尾)
	if (!fs) {
		cout << " Error in open file book.bat. " << endl;
		return false;
	}
	//由于不同种类的书籍的id是自增的，刚开始需要让文件指针指向
	//最后一条记录，然后获得最后一类书的id,加1就得到新书的id
	fs.seekg(0, ios::end);
	int newId;
	streampos len = fs.tellg();
	if (len < sizeof(Book))  newId = 1;//这是文件里一条记录也没有的情况
	else {//注意这里  sizeof(Book) 是无符号数，不能直接对其加符号
		int bookLen = sizeof(Book);
		fs.seekg(-bookLen, ios::end); //定位到最后一条记录的开始处

		char* buffer = new char[sizeof(Book)];
		fs.read(buffer, sizeof(Book));//读取最后一条图书记录

		Book* lastBook = (Book*)buffer;//将读到的数据强制类型转换

		newId = (*lastBook).id + 1;//得到要新增的书的id并完成赋值
		delete[] buffer;
	}
	book.id = newId;
	//然后再将文件指针定位到末尾，写一条新书的记录
	fs.seekg(0, ios::end);
	fs.write((char*)&book, sizeof(book));
	//关闭文件读写流
	fs.close();
	return true;
}

/*
int main() {
	
	Book book;
	
	book.amount = 4;
	book.exist = 1;
	book.numberInLib = 4;
	setBookISBN(book, "9787302227984");
	setBookName(book,"c++程序设计");
	setBookPublisher(book, "清华大学出版社");
	int a[4] = { 1,2,3,4 };
	setBookAuthors(book, a, 4);
	setBookTypes(book, a, 4);

	cout << book.ISBN << endl;
	cout << book.name << endl;
	cout << book.author[0] << endl;
	
	//if (addBook(book)) {
		
	list<Book> booklist = getBookById(1);
		for (list<Book>::iterator it = booklist.begin(); it != booklist.end(); ++it) {
			cout << (*it).id << endl;
			cout << (*it).ISBN << endl;
			cout << (*it).name << endl;
			cout << (*it).author[0] << endl;
		}

		booklist.clear();
		booklist = getBookByISBN("9787302227984",1);
		for (list<Book>::iterator it = booklist.begin(); it != booklist.end(); ++it) {
			cout << (*it).id << endl;
			cout << (*it).ISBN << endl;
			cout << (*it).name << endl;
			cout << (*it).author[0] << endl;
			book = *it;
		}
		book.exist = 0;
		modifyBook(book);

		booklist.clear();
		booklist = getBookByISBN("9787302227984", 1);
		for (list<Book>::iterator it = booklist.begin(); it != booklist.end(); ++it) {
			cout << (*it).id << endl;
			cout << (*it).ISBN << endl;
			cout << (*it).name << endl;
			cout << (*it).author[0] << endl;
			book = *it;
		}

		
	//}
	
	
	list<Book> booklist = getBookById(1);
	for (list<Book>::iterator it = booklist.begin(); it != booklist.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).ISBN << endl;
		cout << (*it).name << endl;
		cout << (*it).author[0] << endl;
		book = *it;
	}
	
	setBookName(book, "测试");
	modifyBook(book);
	list<Book> b = getBookById(1);
	for (list<Book>::iterator it = b.begin(); it != b.end(); ++it) {
		cout << "***********************" << endl;
		cout << (*it).id << endl;
		cout << (*it).ISBN << endl;
		cout << (*it).name << endl;
		cout << (*it).author[0] << endl;
	}
	int i;
	std::cin >> i;
	return 0;
}*/
