#include "stdafx.h"
#include"Structs.h"
#include<list>
#include<string>
#include"BookFunc.h"
#include"AuthorFunc.h"
#include"TypeFunc.h"
#include"DealFault.h"
#include"showInfo.h"


void QueryBookById(list<Book> &bookList) {
	int id;

	for (;;) {
		cout << endl;
		cout << "请输入所查询书籍的ID，输入0取消查询：";
		id = GetIntFromCin();

		if (id == 0) {
			bookList.clear();
			return;
		}
		else {
			bookList = getBookById(id);
			if (bookList.empty())
				cout << "抱歉，查询不到相关书籍,请重新输入" << endl;
			else
				break;
		}
	}
}

void QueryBookByName(list<Book> &bookList) {
	string name;

	for (;;) {
		cout << endl;
		cout << "请输入所查询书籍的名称，输入0取消查询：";
		getline(cin, name);

		if (name == "0") {
			bookList.clear();
			return;
		}
		else {
			bookList = getBooksByName(name);
			if (bookList.empty())
				cout << "抱歉，查询不到相关书籍,请重新输入" << endl;
			else
				break;
		}
	}
}

void QueryBookByISBN(list<Book> &bookList) {
	string ISBN;

	for (;;) {
		cout << endl;
		cout << "请输入所查询书籍的ISBN号(9位或13位)，输入0取消查询：";
		getline(cin, ISBN);

		if (ISBN == "0") {
			bookList.clear();
			return;
		}
		else if (!IsISBN(ISBN))
			cout << "您的输入格式有误，请重新输入" << endl;
		else {
			bookList = getBookByISBN(ISBN, 1);
			if (bookList.empty())
				cout << "抱歉，查询不到相关书籍,请重新输入" << endl;
			else
				break;
		}
	}
}

void QueryBookByAuthor(list<Book> &bookList) {
	string authorName;
	Author author;
	list<Book> tempBookList;
	list<Author> authorList;

	for (;;) {
		cout << endl;
		cout << "请输入所查询书籍的作者的名字，输入0取消查询：";
		getline(cin, authorName);

		if (authorName == "0") {
			bookList.clear();
			return;
		}
		else {
			authorList = getAuthorByName(authorName);
			while (!authorList.empty()) {
				author = authorList.back();
				authorList.pop_back();
				//用tempBookList暂存查找到的作者
				tempBookList = getBooksByAuthor(author.id);
				//合并两个list的信息
				bookList.splice(bookList.end(), tempBookList);
			}
			if (bookList.empty())
				cout << "抱歉，查询不到相关书籍,请重新输入" << endl;
			else
				break;
		}
	}
}

void QueryBookByType(list<Book> &bookList) {
	int typeId;

	for (;;) {
		cout << endl;
		cout << "可查询的书籍种类如下：" << endl;
		showTypeInfo(getAllTypes(), true);

		cout << "请输入所查询书籍的种类的ID，输入0取消查询：";
		typeId = GetIntFromCin();

		if (typeId == 0) {
			bookList.clear();
			return;
		}
		else {
			bookList = getBooksByType(typeId, 1);
			if (bookList.empty())
				cout << "抱歉，查询不到相关书籍,请重新输入" << endl;
			else
				break;
		}
	}
}

void QueryBookByPublisher(list<Book> &bookList) {
	string publisher;

	for (;;) {
		cout << endl;
		cout << "请输入所查询书籍的出版社，输入0取消查询：";
		getline(cin, publisher);

		if (publisher == "0") {
			bookList.clear();
			return;
		}
		else {
			bookList = getBooksByPublisher(publisher);
			if (bookList.empty())
				cout << "抱歉，查询不到相关书籍,请重新输入" << endl;
			else
				break;
		}
	}
}


void QueryAllBook() {

	int select;
	while (1) {
		cout << "您想要查看所有书籍还是按照分页查看书籍?" << endl;
		cout << "1.查看所有书籍" << endl;
		cout << "2.按照分页查看书籍" << endl;
		cout << "请输入选项：";
		select = GetIntFromCin();
		switch (select)
		{
		case 1:break;
		case 2:break;
		default:
			cout << "只能输入1或2！" << endl;
			continue;
		}
		break;
	}

	int i = 1;
	int start = 1;
	list<Book> booklist;
	switch (select)
	{
	case 1:
		booklist = getBooks(1);
		showBooksInfo(booklist);
		break;
	case 2:
		while (1) {
			booklist.clear();
			booklist = getBooks(start, 5);//每页展示5本书
			if (booklist.empty()) {
				cout << "已经到达书籍末尾页！" << endl;
				break;
			}

			cout << endl << endl <<  "第" << i <<"页书籍信息如下所示：" << endl;
			showBooksInfo(booklist);
			start = start + 5;
			i++;
			while (1) {
				cout << endl << "您是否还要查看更多书籍？是请输入1，否请输入0" << endl;

				cout << "请输入选项：";
				select = GetIntFromCin();
				switch (select)
				{
				case 1:break;
				case 2:break;
				default:
					cout << "只能输入1或2！" << endl;
					continue;
				}
				break;
			}
			switch (select)
			{
			case 1:continue;//继续展示书籍信息
			case 2:break;
			}
			break;
		}
		break;
	}
	
}


//按条件（id，ISBN，书名，作者，类别，出版社）查询书
void QueryBookService() {
	list<Book> bookList;
	list<Author> authorList;
	list<Type> typeList;

	//实现多次查询
	for (int i = 0;;) {
		//选择查询的选项
		cout << endl;
		cout << "查询书籍操作" << endl;
		cout << "1.按书籍ID号查找书籍" << endl;
		cout << "2.按书籍名称查找书籍" << endl;
		cout << "3.按书籍ISBN号查找书籍" << endl;
		cout << "4.按作者查找书籍" << endl;
		cout << "5.按种类查找书籍" << endl;
		cout << "6.按出版社查找书籍" << endl;
		cout << "7.显示所有书籍" << endl;
		cout << "0.取消并返回首页" << endl;
		cout << "请选择查询的方式：" << endl;
		i = GetIntFromCin();

		//实现功能的选择
		switch (i) {
		case 1:
			QueryBookById(bookList);
			break;
		case 2:
			QueryBookByName(bookList);
			break;
		case 3:
			QueryBookByISBN(bookList);
			break;
		case 4:
			QueryBookByAuthor(bookList);
			break;
		case 5:
			QueryBookByType(bookList);
			break;
		case 6:
			QueryBookByPublisher(bookList);
			break;
		case 7:
			QueryAllBook();
			break;
		case 0:
			return;
		default:
			cout << "您的输入有误，请重新输入" << endl;
		}

		if (!bookList.empty()) {
			cout << endl;
			cout << "您查询的书籍信息如下：" << endl;
			showBooksInfo(bookList);
		}

		for (;;) {
			cout << endl;
			cout << "继续查询？查询请输入1，退出请输入0：";
			int t = GetIntFromCin();
			if (t == 1)
				break;
			else if (t == 0)
				return;
			else
				cout << "您的输入有误，请重新输入" << endl;
		}

		//清空list
		bookList.clear();
	}
}
