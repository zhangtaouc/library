

#include "stdafx.h"
#include"Structs.h"
#include"BookFunc.h"
#include"showInfo.h"
#include"Operation.h"
#include"BorrowRecordFunc.h"
#include <array>
#include<string>
#include <unordered_set>
#include"DealFault.h"
#include"QueryBookService.h"
#define MaxTypeAmount 10//每本书最多有10种类别
#define MaxAuthorAmount 10//每本书最多记录十个主要作者
using namespace std;





/*添加一本书籍的service*/
void AddBookService(){
	Book book;

	int out;//用于退出当前增加书籍功能
	//本来想的是在增添书籍的每一步之后都询问一下是否要退出增添书籍功能，但是
	//这样有些麻烦，因此只有在刚开始进入界面的时候会询问一下是否要退出(有可能是输入错误了)

	//每添加图书的某一项信息之后都会询问是否退出添加书籍功能
	while (1) {
		cout << "您可以进行如下操作：" << endl;
		cout << "1.开始添加图书" << endl;
		cout << "2.退出增添书籍界面" << endl;
		cout << "请输入选项1或2：";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "只能输入1或2！" << endl;
			continue;
		}
		break;//case 1的情况
	}

	//首先获取新增图书的ISBN编号
	string isbn;
	while (1) {
		cout << endl << "请输入新增图书的ISBN编号:" << endl;
		getline(cin, isbn);
		trimFLSpace(isbn);//去掉首尾空格

		//检查输入的ISBN编号是否满足ISBN校验方式
		bool  isISBN = IsISBN(isbn);

		//如果不满足ISBN格式要求，询问要重新输入ISBN编号还是退出增加书籍
		if (!isISBN) {
			cout << endl << "您输入的ISBN编号格式有误!" << endl;
			while (1) {
				cout << endl << "您想要继续输入ISBN编号吗？输入1以继续，输入0退出增添书籍界面:";
				out = GetIntFromCin();

				switch (out)
				{
				case 1:break;
				case 0:return;
				default:
					cout << endl << "只能输入1或0！" << endl;
					continue;
				}
				break;//case 1的情况
			}
			continue;
		}

		//如果满足校验方式，设置新增书籍的ISBN
		setBookISBN(book, isbn);

		//得到格式正确的ISBN编号后，让用户确认一下ISBN
		int select;
		cout << endl << "请您确认ISBN:" << isbn.data() << endl;
		while (1) {
			cout << endl;
			cout << "1.确认ISBN编号" << endl;
			cout << "2.重新输入ISBN编号" << endl;
			cout << endl << "请输入选项1或2：";
			select = GetIntFromCin();
			switch (select)
			{
			case 1:
			case 2:break;
			default:
				cout << endl << "只能输入1或2！" << endl;
				continue;
			}

			break;//1.确认当前的ISBN编号
				// 2.重新输入ISBN编号
		}
		switch (select)
		{
		case 1:break;//1.确认当前的ISBN编号，继续下面的函数
		case 2:continue;//2.重新输入ISBN编号
		}

		//得到格式正确的ISBN编号且确认后，要根据该编号查询该书籍是否存在
		//如果存在，分为两种情况：
		//1.书籍存在且被假删除了，应展示图书信息，让用户确认这个是否就是要增加的
		//书籍，如果是的话，就让用户输入新增数量，并修改书籍信息
		//2.书籍存在且未被删除，此时禁止增加该本书籍

		list<Book> b = getBookByISBN(isbn, 0);
		if (!b.empty()) {
			list<Book>::iterator it = b.begin();
			if ((*it).exist == 0) {//情况1
				cout << endl << "您要添加的书籍信息已经存在于馆中！如下所示:" << endl;
				showBooksInfo(b);

				while (1) {
					cout << endl << "这是您要添加的书籍信息吗？" << endl;
					cout << "1.是的" << endl;
					cout << "2.不是。(通过选择2您可以重新输入ISBN编号)" << endl;
					cout << "请输入选项1或2：" << endl;
					select = GetIntFromCin();

					int amount;
					switch (select) {
					case 1:
						cout << endl << "请输入该书籍的数目：" << endl;
						amount = GetIntFromCin();
						//输入的书籍数量不能小于等于0(或者是用户输入一个不是数字的字符串也会导致amount < 0)
						while (amount <= 0) {
							cout << "您输入的数据格式有误，请重新输入！" << endl;
							cout << endl << "请输入该书籍的数目：";
							amount = GetIntFromCin();
						}
						//输入新增数量，将原先假删除掉的书籍信息改写
						(*it).amount = amount;
						(*it).numberInLib = amount;
						(*it).exist = 1;
						modifyBook(*it);
						cout << "新增书籍成功!书籍信息如下所示：" << endl;
						showBooksInfo(getBookByISBN(isbn, 1));
						return;
					case 2:
						break;
					default:
						cout << endl << "只能输入1或2！" << endl;
						continue;
					}
					break;
				}
			}
			else {//如果该ISBN编号的书籍已经存在且该图书未被删除，则禁止增加该本书籍
				cout << endl << "该ISBN编号的书籍已存在！" << endl;
				continue;
			}
		}
		else break;//如果该ISBN不存在于图书馆中，允许添加书籍
	}


	//每添加图书的某一项信息之后都会询问是否退出添加书籍功能
	while (1) {
		cout << "您可以进行如下操作：" << endl;
		cout << endl;
		cout << "1.继续输入当前图书信息" << endl;
		cout << "2.退出增添书籍界面" << endl;
		cout << "请输入选项1或2：";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "只能输入1或2！" << endl;
			continue;
		}
		break;//case 1的情况
	}


	//接下来要求输入书名，应该保证书名不能是一行空格
	//书名中可以有空格,但是书名首尾不能有空格
	string name;
	while (1) {
		cout << endl << "请输入新增书籍的书名：" << endl;
		getline(cin, name);
		trimFLSpace(name);

		if (!setBookName(book, name)) {
			cout << endl <<"书名过长，请重新输入!" << endl;
			continue;
		}
		else {
			if (name == "") {//保证书名不能是一行空格
				cout << endl << "书名不能为空，请重新输入！" << endl;
			}
			else {
				
				//书名需要再次确认
				int select;
				cout << endl << "请您再次确认书名:" << "<<" <<  name.data()  << ">>"<< endl;
				while (1) {
					cout << endl;
					cout << "1.确认书名" << endl;
					cout << "2.重新输入书名" << endl;
					cout << endl << "请输入选项1或2：";
					select = GetIntFromCin();
					switch (select)
					{
					case 1:
					case 2:break;
					default:
						cout << endl << "只能输入1或2！" << endl;
						continue;
					}

					break;//1.确认
						  // 2.重新输入
				}
				switch (select)
				{
				case 1:break;//1.确认，继续下面的函数
				case 2:continue;//2.重新输入
				}
				break;//确认书名
			}
		}
	}

	//每添加图书的某一项信息之后都会询问是否退出添加书籍功能
	while (1) {
		cout << endl <<"您可以进行如下操作：" << endl;
		cout << "1.继续输入当前图书信息" << endl;
		cout << "2.退出增添书籍界面" << endl;
		cout << "请输入选项1或2：";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "只能输入1或2！" << endl;
			continue;
		}
		break;//case 1的情况
	}


	//接下来要求输入出版社名
	//应该保证出版社名不能是一行空格
	//出版社名中可以有空格，但是首尾的空格字符会被剪切掉
	string publisher;
	while (1) {

		cout << endl << "请输入新增书籍的出版社名：" << endl;
		getline(cin, publisher);
		trimFLSpace(publisher);

		if (!setBookPublisher(book, publisher)) {
			cout << endl << "出版社名过长，请重新输入!" << endl;
			continue;
		}
		else {
			if (publisher == "") {//保证书名不能是一行空格
				cout << endl << "出版社名不能为空，请重新输入！" << endl;
			}
			else {//重新确认一遍出版社名
				cout << endl << "请您再次确认出版社名:" << publisher.data() << endl;

				//书名需要再次确认
				int select;
				while (1) {
					cout << endl << "1.确认出版社名" << endl;
					cout << "2.重新输入出版社名" << endl;
					cout << endl << "请输入选项1或2：";
					select = GetIntFromCin();
					switch (select)
					{
					case 1:
					case 2:break;
					default:
						cout << endl << "只能输入1或2！" << endl;
						continue;
					}

					break;//1.确认
						  // 2.重新输入
				}
				switch (select)
				{
				case 1:break;//1.确认，继续下面的函数
				case 2:continue;//2.重新输入
				}
				break;//确认

			}
		}
	}

	//每添加图书的某一项信息之后都会询问是否退出添加书籍功能
	while (1) {
		cout << endl << "您可以进行如下操作：" << endl;
		cout << "1.继续输入当前图书信息" << endl;
		cout << "2.退出增添书籍界面" << endl;
		cout << "请输入选项1或2：";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "只能输入1或2！" << endl;
			continue;
		}
		break;//case 1的情况
	}

	//接下来让用户选择图书类别，类别可以为空
	//用一个set集合来存储用户输入的所有类别id，为了保证不输入重复的id
	unordered_set<int> typeIdSet;	

	//展示所有类别的信息，让用户输入该本书籍所属类别id,一本书籍最多可以有10个不同的类别
	//每次用户输入一个类别id(要保证输入的每个id都不同)，都会让用户重新确认一下类别的信息，如果正确的话就复制给types数组中的元素
	//等到用户输入完类别id后，展示所有该书所属的类别，再让用户确认一次，如果正确的话就完成types属性的添加

	list<Type> T = getAllTypes();
	cout << endl << "所有类别的信息如下所示：" << endl;
	showTypeInfo(T, true);
	list<Type> curType;//用来存储当前书籍所属的所有类别
	//用来存储类别最大id
	int maxTypeId = T.size();

	cout << endl << "您最多可以为一本书选择" << MaxTypeAmount << "个类别。" << endl;
	while (1) {
		if (typeIdSet.size() >= MaxTypeAmount) {
			cout << endl << "已经输入了" << MaxTypeAmount << "个类别，不能继续添加类别了!" << endl;
			break;
		}

		cout << endl << "请输入该本书籍所属类别的id号(您可以输入0来结束类别项的输入):";

		int id;
		id = GetIntFromCin();

		//首先要保证输入的id在类别所在id的范围内而且数据格式要正确
		if (id < 0 || id > maxTypeId)
		{
			cout << endl << "您输入的类别id有误！" << endl;
			continue;
		}

		if (id == 0) break;//输入0以结束类别输入

		//输入的类别id若有重复，不会被重复添加到集合中去
		//应该让用户确认一下该类别的信息，如果确认正确才将id添加到set中去
		 //如果用户输错了，取消当前类别id的输入
		list<Type> t = getTypeById(id);
		cout << endl << "请您确认类别信息:" << endl;
		showTypeInfo(t, true);

		int select;
		while (1) {
			cout << endl << "1.确认类别" << endl;
			cout << "2.重新输入一个类别" << endl;
			cout << endl << "请输入选项1或2：";
			select = GetIntFromCin();
			switch (select)
			{
			case 1:
			case 2:break;
			default:
				cout << endl << "只能输入1或2！" << endl;
				continue;
			}
			break;//1.确认
				  // 2.重新输入
		}
		switch (select)
		{
		case 1:break;//1.确认，继续下面的函数
		case 2:continue;//2.重新输入
		}
		//确认类别号
		//输入1代表确认这个类别id
	
		pair<unordered_set<int>::iterator,bool> p = typeIdSet.insert(id);
		if (p.second) {
			list<Type>::iterator it = t.begin();
			curType.push_back(*it);
		}
	}

	T.clear();//释放空间
			  //得到了这些类别id后，应该对book的types属性赋值了
	int types[MaxTypeAmount];

	int i = 0;
	for (int id : typeIdSet)
		types[i++] = id;
	
	setBookTypes(book, types, typeIdSet.size());
	typeIdSet.clear();//释放空间
					  //每添加图书的某一项信息之后都会询问是否退出添加书籍功能
	
	while (1) {
		cout << endl << "您可以进行如下操作：" << endl;
		cout << "1.继续输入当前图书信息" << endl;
		cout << "2.退出增添书籍界面" << endl;
		cout << "请输入选项1或2：";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "只能输入1或2！" << endl;
			continue;
		}
		break;//case 1的情况
	}


					  //接下来让用户输入该书的作者
					  //这里是有缺陷的。因为对于名字相同的作者，这里会认为他们是同一个人。
					  //让用户输入若干个作者名，用集合来存储这些作者姓名，保证每个元素值的唯一性
					  //对于相同的作者姓名，没有必要对用户提醒
					  //默认每个作者姓名都不同，作者姓名中若有空格会被自动裁剪掉
					  //一本书的读者信息不能为空，至少需要有一个读者
					  //作者名中可以含有空格，但是名字首尾的空格会被剪切
	unordered_set<string> authorNames;

	cout << endl << "请输入该本书籍的主要作者。一本书最多可以有" << MaxAuthorAmount << "个作者。" << endl;

	while (1) {

		if (authorNames.size() == MaxAuthorAmount)
		{
			cout << endl << "您已经输入了" << MaxAuthorAmount << "个主要作者，不能继续输入作者了!进入下一步！" << endl;
			break;
		}

		cout << endl << "请输入一个作者姓名,或者您可以输入0来结束所有作者姓名的输入:" << endl;
		cout << endl;
		string aName;
		getline(cin, aName);
		trimFLSpace(aName);//裁剪空格字符

		//if (aName == "2") return;

		if (aName == "0") {
			if (authorNames.size() == 0) {//
				cout << endl << "您至少需要输入一个作者信息!" << endl;
				continue;
			}
			else //用户想要结束作者姓名的输入时
				  //是否有误，如果有误，应该将Set集合置空，重新输入作者姓名集合
				break;//退出作者姓名输入，进行作者表的增添
		}

		
		Author a;
		//先保证作者名不能全是空格，且不可以过长

		if (aName == "" || !setAuthorName(a, aName)) {
			//如果aName全为空格字符或者为空或者过长(超过读者姓名最长字符个数)
			//提示重新输入一个作者姓名
			cout << "读者姓名过长或为空，格式错误!" << endl;
			continue;
		}

		//格式正确的话，确认一下作者姓名
		int select;
		cout << endl << "请确认作者姓名：" << aName.data() << endl;

		while (1) {
			cout << endl;
			cout << "1.确认作者" << endl;
			cout << "2.重新输入作者" << endl;
			cout << endl << "请输入选项1或2：";
			select = GetIntFromCin();
			switch (select)
			{
			case 1:
			case 2:break;
			default:
				cout << endl << "只能输入1或2！" << endl;
				continue;
			}

			break;//1.确认
				  // 2.重新输入
		}
		switch (select)
		{
		case 1:break;//1.确认，继续下面的函数
		case 2:continue;//2.重新输入
		}
		//若确认成功，则将这个作者姓名插入到集合中去
		authorNames.insert(aName);
	}

	//每添加图书的某一项信息之后都会询问是否退出添加书籍功能
	while (1) {
		cout << endl << "您可以进行如下操作：" << endl;
		cout << "1.继续输入当前图书信息" << endl;
		cout << "2.退出增添书籍界面" << endl;
		cout << "请输入选项1或2：";
		out = GetIntFromCin();

		switch (out)
		{
		case 1:break;
		case 2:return;
		default:
			cout << endl << "只能输入1或2！" << endl;
			continue;
		}
		break;//case 1的情况
	}

	//接下来让用户输入图书数量
	int amount;
	while (1) {
		cout << endl << "请输入该类书籍的数量：";
		amount = GetIntFromCin();

		if (amount <= 0) {
			cout << endl << "书籍数量输入格式有误！" << endl;
			continue;
		}
		else {

			int select;
			cout << endl << "请您再次确认书籍数量:" << amount << endl;

			while (1) {
				cout << endl;
				cout << "1.确认" << endl;
				cout << "2.取消。重新输入书籍数量" << endl;
				cout << endl << "请输入选项1或2：";
				select = GetIntFromCin();

				switch (select)
				{
				case 1:
				case 2:break;
				default:
					cout << endl <<"只能输入1或2！" << endl;
					continue;
				}
				break;//1.确认
					  // 2.重新输入
			}

			switch (select)
			{
			case 1:break;//1.确认，继续下面的函数
			case 2:continue;//2.重新输入
			}
			
			//完成书籍数量的赋值
			book.amount = amount;
			book.numberInLib = amount;
			break;
		}
	}

	cout << endl << "书籍信息已经输入完毕。当前输入的书籍信息如下所示：" << endl;
	cout << endl;
	cout << "ISBN编号：" << isbn.data() << endl;
	cout << "书名：" << name.data() << endl;
	cout << "出版社：" << publisher.data() << endl;
	cout << "类别：";
	showTypeInfo(curType, false);
	cout <<endl << "作者：";
	for (string s:authorNames) {
		cout << s.data() << "  ";
	}
	cout << endl << "数量：" << amount << endl;

	while (1) {
		cout << endl << "您是否确认要增添该本书籍？" << endl;
		cout << "1.确认增添该本书籍。" << endl;
		cout << "2.取消增添。退出增加书籍界面。" << endl;
		cout << "请输入选项1或2：";

		out = GetIntFromCin();
		int index = 0;
		int authorId[MaxAuthorAmount];
		switch (out) {
		case 1:
			book.exist = 1;
			//等到用户确认要添加该本书籍后才会添加作者
			//接下来进行作者的增添操作
			//如果已输入的作者姓名不存在于文件中才增加一条作者记录

			for (string s : authorNames) {
				list<Author> a = getAuthorByName(s, true);
				if (a.empty()) {//如果已输入的作者姓名不存在于文件中才增加一条作者记录
					Author au;
					setAuthorName(au, s);
					addAuthor(au);
					authorId[index++] = au.id;
				}
				else {
					list<Author>::iterator it = a.begin();
					authorId[index++] = (*it).id;
				}
			}

			//完成作者id数组的赋值
			setBookAuthors(book, authorId, authorNames.size());

			//添加书籍成功后展示书籍信息，退出函数
			if (addBook(book)) {
				list<Book> bookList = getBookById(book.id);
				cout << endl << "书籍添加成功！书籍信息如下所示：" << endl;
				showBooksInfo(bookList);
			}
			else {
				cout << "调用AddBook返回false,添加书籍失败！" << endl;
			}
		case 2: return;//输入2退出增添书籍界面
		default:
			cout << endl <<  "只能输入1或2！" << endl;
			continue;
		}
	
	}
}


/*删除一类书籍或者几本书籍的service*/
void DeleteBookService() {

	//要求输入删除书籍的id
	int bookId;
	
		//进入界面之后，让用户选择是否退出(有可能是选择错误才进入当前界面的)
		
		cout << endl << "请输入您要删除图书的id:" << endl;
		bookId = GetIntFromCin();
		if (bookId <= 0) {
			cout << endl << "您输入的图书id格式不正确！" << endl;
			return;//继续输入一个图书id
		}

		list<Book> book = getBookById(bookId);
		if (book.empty()) {
			cout << endl << "您输入的书籍id不存在！" << endl;
			return;
		}

		//如果书籍存在，就先将这本书的信息输出给用户
		cout << endl << "您要删除的书籍信息如下所示：" << endl;
		showBooksInfo(book);

		
		cout << "您可以进行如下操作：" << endl;
		cout << endl << "1.删除这类书籍.(这类书籍的信息会被清除)" << endl;
		cout << "2.减少该类书籍的数量." << endl;
		cout << "3.退出删除书籍界面." << endl;

		cout << endl << "请输入选项:";
		string select;
		while (1) {
			getline(cin, select);
			trimAllSpace(select);
			if (select == "1" || select == "2" || select == "3")
				break;
			else {
				cout << endl << "您只能输入1,2,3，请重新输入：" << endl;
				cout << endl << "请输入选项:";
			}
		}

		//接下来会有3个分支：1.删除这类书籍；2.减少该类书籍的数量；3.退出删除书籍界面

		list<Book>::iterator b = book.begin();
		if (select == "1") {//这是删除一类书籍的分支
			if ((*b).numberInLib != (*b).amount) {//如果要删除的书籍有在借的，禁止删除
				cout << endl << "该类书籍有在借情况！您不能删除！" << endl;
				return;//继续输入一个书籍id
			}
			else {//如果可以删除，就让用户再确认一下后再去修改图书信息
				string select2;
				while (1) {
					cout << endl << "您确认要删除该类书籍吗？确认请输入1，取消请输入0：" << endl;
					getline(cin, select2);
					trimAllSpace(select2);
					if (select2 == "1" || select2 == "0")
						break;
					else
						cout << endl << "您只能输入1或0，请重新输入：" << endl;
				}
				if (select2 == "0") return;//继续输入一个图书id
											
				//输入1代表确认删除书籍
				(*b).exist = 0;
				(*b).amount = 0;
				(*b).numberInLib = 0;
				if (modifyBook(*b)) {//如果修改成功，输出提示信息
					cout << endl << "书籍删除成功！" << endl;
					return;
				}
				else {//若由于某种原因修改失败，输出提示信息后退出删除书籍界面(用于调试)
					cout << endl << "书籍删除失败！" << endl;
					return;
				}

			}


		}
		else if (select == "2") {//2.减少该类书籍的数量

			int deleteNum;
			
			while (1) {
				//得到格式正确的书籍删除数量
				cout << endl << "请输入要减少的该类书籍的数量：" << endl;
				deleteNum = GetIntFromCin();

				if (deleteNum <= 0) {
					cout << endl << "您输入的数量格式无效！" << endl;
					continue;
				}
				else if (deleteNum >= (*b).numberInLib) {//要保证至少有一本保留本
					cout << endl << "您删除该类书籍的数量不能大于其馆藏数量!" << endl;
					continue;
				}
				else {
					//让用户确认一下删除书籍的数量
					string confirm;
					cout << endl << "您确认要删除" << deleteNum << "本该类书籍吗？" << endl;
					cout << "1.确认删除" << endl;
					cout << "2.取消删除" << endl;
					while (1) {
						cout << endl << "请输入您的选项：" << endl;
						getline(cin, confirm);
						trimAllSpace(confirm);
						if (confirm == "1" || confirm == "2")
							break;
						else
							cout << endl << "您只能输入1,2！" << endl;
					}
					if (confirm == "2") return;
					else {
						(*b).amount -= deleteNum;
						(*b).numberInLib -= deleteNum;
						if (modifyBook(*b)) {
							cout << "删除书籍成功！" << endl;
							return;
						}
						else {
							cout << "删除书籍失败！" << endl;
							return;
						}

					}

				}
			}
			
				
			}
		//当前输入的书籍id不是用户想要删除的书籍id时，应该继续下一次书籍id的输入
		else return;

	

}


bool ModifyBookName(Book &book) {
	string name;

	cout << endl;
	cout << "请输入所要修改的书名，输入0取消修改：";
	getline(cin, name);

	if (name == "0")
		return false;
	else
		copy(book.name, name, sizeof(Book::name));
	return true;
}

bool ModifyBookISBN(Book &book) {
	string ISBN;

	for (;;) {
		cout << endl;
		cout << "请输入修改的ISBN号（9位或13位），输入0取消修改：";
		getline(cin, ISBN);

		if (ISBN == "0")
			return false;
		else
			if (IsISBN(ISBN)) {
				copy(book.ISBN, ISBN, sizeof(Book::ISBN));
				return true;
			}
			else
				cout << "您的输入格式有误，请重新输入" << endl;
	}
}

bool ModifyBookAuthor(Book &book) {

	cout << endl << "请输入修改后当前书籍的全部作者！" << endl;
	//接下来让用户输入该书的作者
	//这里是有缺陷的。因为对于名字相同的作者，这里会认为他们是同一个人。
	//让用户输入若干个作者名，用集合来存储这些作者姓名，保证每个元素值的唯一性
	//对于相同的作者姓名，没有必要对用户提醒
	//默认每个作者姓名都不同，作者姓名中若有空格会被自动裁剪掉
	//一本书的读者信息不能为空，至少需要有一个读者
	//作者名中可以含有空格，但是名字首尾的空格会被剪切
	unordered_set<string> authorNames;

	cout << endl << "请输入该本书籍的主要作者。一本书最多可以有" << MaxAuthorAmount << "个作者。" << endl;

	while (1) {

		if (authorNames.size() == MaxAuthorAmount)
		{
			cout << endl << "您已经输入了" << MaxAuthorAmount << "个主要作者，不能继续输入作者了!进入下一步！" << endl;
			break;
		}

		cout << endl << "请输入一个作者姓名,或者您可以输入0来结束所有作者姓名的输入:" << endl;
		cout << endl;
		string aName;
		getline(cin, aName);
		trimFLSpace(aName);//裁剪空格字符

						   //if (aName == "2") return;

		if (aName == "0") {
			if (authorNames.size() == 0) {//
				cout << endl << "您至少需要输入一个作者信息!" << endl;

				while (1) {
					cout << "您是否要退出修改当前图书作者功能？是请输入1，否请输入0: " << endl;
					int select;
					select = GetIntFromCin();
					switch (select) {
					case 1:return false;
					case 0:break;
					default:cout << endl << "只能输入0或1！" << endl;
						continue;
					}
					break;
				}
				continue;
			}
			else //用户想要结束作者姓名的输入时
				 //是否有误，如果有误，应该将Set集合置空，重新输入作者姓名集合
				break;//退出作者姓名输入，进行作者表的增添
		}


		Author a;
		//先保证作者名不能全是空格，且不可以过长

		if (aName == "" || !setAuthorName(a, aName)) {
			//如果aName全为空格字符或者为空或者过长(超过读者姓名最长字符个数)
			//提示重新输入一个作者姓名
			cout << "读者姓名过长或为空，格式错误!" << endl;
			continue;
		}

		//格式正确的话，确认一下作者姓名
		int select;
		cout << endl << "请确认作者姓名：" << aName.data() << endl;

		while (1) {
			cout << endl;
			cout << "1.确认作者" << endl;
			cout << "2.重新输入作者" << endl;
			cout << endl << "请输入选项1或2：";
			select = GetIntFromCin();
			switch (select)
			{
			case 1:
			case 2:break;
			default:
				cout << endl << "只能输入1或2！" << endl;
				continue;
			}

			break;//1.确认
				  // 2.重新输入
		}
		switch (select)
		{
		case 1:break;//1.确认，继续下面的函数
		case 2:continue;//2.重新输入
		}
		//若确认成功，则将这个作者姓名插入到集合中去
		authorNames.insert(aName);
	}

	int index = 0;
	int authorId[MaxAuthorAmount];

	for (string s : authorNames) {
		list<Author> a = getAuthorByName(s, true);
		if (a.empty()) {//如果已输入的作者姓名不存在于文件中才增加一条作者记录
			Author au;
			setAuthorName(au, s);
			addAuthor(au);
			authorId[index++] = au.id;
		}
		else {
			list<Author>::iterator it = a.begin();
			authorId[index++] = (*it).id;
		}
	}

	//完成作者id数组的赋值
	setBookAuthors(book, authorId, authorNames.size());
	return true;


	/*
	string authorName[10];
	string tempAuthorName[10];
	list<Author> authorList;

	//因为作者可以有多个，因此用数组存储作者id，先用temp存储，以实现取消修改
	cout << endl;
	cout << "请输入书籍作者的姓名，最多10个" << endl;
	cout << "输入0结束，输入-1重新输入,输入-2取消修改：" << endl;
	for (int i = 0; i < 10; i++) {
		for (;;) {
			cout << i + 1 << ".";
			getline(cin, authorName[i]);

			getAuthorByName(authorName[i], t)

			//取消修改直接退出函数，不对book的author进行任何修改
			if (authorName[i] == -2)
				return false;
			//之前的输入有误，可输入-1选择重新输入，使for重新循环
			else if (authorName[i] == -1) {
				i = -1;
				break;
			}
			else if (authorId[i] == 0) {
				//用户输入结束，将数组余下元素置0，并退出for循环
				for (int k = i; k < 10; k++)
					tempAuthorId[i] = 0;
				i = 10;
				break;
			}
			else {
				authorList = getAuthorById(authorId[i]);
				if (!authorList.empty()) {
					tempAuthorId[i] = authorId[i];
					break;
				}
				else
					//找不到作者，让用户重新输入
					cout << "不存在与输入ID相匹配的作者，请重新输入" << endl;
			}
		}
	}

	//修改完成，将temp赋给book的author
	for (int i = 0; i < 10; i++)
		book.author[i] = tempAuthorId[i];
	return true;
	*/
}

bool ModifyBookType(Book &book) {

	cout << endl << "请输入修改后当前书籍的全部类别！" << endl;
	int typeId[10];
	int tempTypeId[10];
	list<Type> typeList;

	cout << endl;
	cout << "可修改的书籍种类如下：" << endl;
	showTypeInfo(getAllTypes(), true);

	//书籍种类同作者一样可有多个，因此操作相同
	cout << endl;
	cout << "请输入修改的书籍种类的ID号，最多10个" << endl;
	cout << "输入0结束，输入 - 1重新输入, 输入 - 2取消修改：" << endl;
	for (int i = 0; i < 10; i++) {
		for (;;) {
			cout << i + 1 << ".";
			typeId[i] = GetIntFromCin();

			if (typeId[i] == -2)
				return false;
			else if (typeId[i] == -1) {
				i = -1;
				break;
			}
			else if (typeId[i] == 0) {
				for (int k = i; k < 10; k++)
					tempTypeId[k] = 0;
				i = 10;
				break;
			}
			else {
				typeList = getTypeById(typeId[i]);
				if (!typeList.empty()) {
					tempTypeId[i] = typeId[i];
					break;
				}
				else
					cout << "不存在与输入ID相匹配的书籍种类，请重新输入" << endl;
			}
		}
	}

	for (int i = 0; i < 10; i++)
		book.type[i] = tempTypeId[i];
	return true;
}

bool ModifyBookPublisher(Book &book) {
	string publisher;

	cout << endl;
	cout << "请输入修改的出版社名称，输入0取消修改：";
	getline(cin, publisher);

	if (publisher == "0")
		return false;
	else
		copy(book.publisher, publisher, sizeof(Book::publisher));
	return true;
}

bool ModifyBookAmount(Book &book) {
	int amount;

	for (;;) {
		cout << endl;
		cout << "请输入修改的总量，输入-1取消修改:";
		amount = GetIntFromCin();

		if (amount == -1)
			return false;
		//修改的总量必须大于等于0
		else if (amount < 0)
			cout << "您的输入有误，请重新输入" << endl;
		else if (amount < book.numberInLib)
			cout << "输入的总量不可小于该书的馆存量，请重新输入" << endl;
		else {
			book.amount = amount;
			break;
		}
	}
	return true;
}

bool ModifyBookNumInLib(Book &book) {
	int numberInLib;

	for (;;) {
		cout << endl;
		cout << "请输入修改的馆存量，输入-1取消修改:";
		numberInLib = GetIntFromCin();

		if (numberInLib == -1)
			return false;
		//修改的馆存量大于等于0
		else if (numberInLib < 0)
			cout << "您的输入有误，请重新输入" << endl;
		else if (numberInLib > book.amount)
			cout << "输入的馆存量不可大于总量，请重新输入" << endl;
		else {
			book.numberInLib = numberInLib;
			break;
		}
	}
	return true;
}

void ModifyBookService() {
	//flag用于判断是否经过修改
	bool flag = false;
	Book book;
	list<Book> bookList;
	list<Author> authorList;
	list<Type> typeList;

	for (;;) {
		//通过ISBN查找到需要修改的书籍
		QueryBookByISBN(bookList);
		//若返回值为空，则退出该函数
		if (bookList.empty())
			return;
		else
			//输出查找到的书籍的信息，以让用户看到需要修改的信息
			showBooksInfo(bookList);

		book = bookList.back();
		bookList.pop_back();

		//实现修改多个属性
		for (int i = -1; i != 0;) {
			//选择修改的选项
			cout << endl;
			cout << "请选择需要修改的信息，确认修改请输入0：" << endl;
			cout << "0.确认当前修改" << endl;
			cout << "-1.取消修改" << endl;
			cout << "1.书名" << endl;
			cout << "2.ISBN" << endl;
			cout << "3.作者" << endl;
			cout << "4.种类" << endl;
			cout << "5.出版社" << endl;
			cout << "6.总量" << endl;
			cout << "7.馆存量" << endl;
			i = GetIntFromCin();

			//实现功能的选择
			switch (i) {
			case 1:
				flag = ModifyBookName(book);
				break;
			case 2:
				flag = ModifyBookISBN(book);
				break;
			case 3:
				flag = ModifyBookAuthor(book);
				break;
			case 4:
				flag = ModifyBookType(book);
				break;
			case 5:
				flag = ModifyBookPublisher(book);
				break;
			case 6:
				flag = ModifyBookAmount(book);
				break;
			case 7:
				flag = ModifyBookNumInLib(book);
				break;
			case 0:
				break;
			case -1:
				return;
			default:
				cout << "您的输入有误，请重新输入" << endl;
			}
		}

		//若进行过修改，则调用修改函数
		if (flag) {
			flag = false;
			cout << "确认修改？确认请输入1，取消请输入0：";
			int t = GetIntFromCin();

			if (t == 1) {
				//调用函数修改书籍信息
				if (modifyBook(book)) {
					cout << "书籍信息修改成功！" << endl;
					bookList.clear();
					bookList.push_back(book);
					//输出查找到的书籍的信息
					showBooksInfo(bookList);
					return;
				}
				else
					cout << "书籍信息修改失败！" << endl;
			}
			else if (t == 0)
				cout << "修改取消！" << endl;
			else
				cout << "您的输入有误，请重新输入" << endl;
		}
	}
}


