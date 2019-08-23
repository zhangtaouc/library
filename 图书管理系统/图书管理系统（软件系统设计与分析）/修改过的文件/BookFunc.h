#pragma once
#include"Structs.h"
#include<list>
/*把函数声明放在头文件里，这样有函数需要调用
BooksFunction函数中的其中一个时，只需要
把这个头文件include进来就可以啦*/


/*通过图书唯一的id号查询这本书的信息并返回
查询的时候要注意exist 属性需要为1(该书未被删除)
找不到就返回空list*/
list<Book> getBookById(int id);

/**
* 根据ISBN码查询书籍
exist可以为1或0，如果为1，则只查找exist为1的书
如果为0，则查找所有书籍
这个函数比较特殊，是因为如果有一个人要添加一个新类的书，但是这类书
的ISBN已经存在于图书馆中，只是被假删除了。这时候需要得到被假删除的
这类书，然后修改其exist属性和数量即可，不需要再新增一条记录
* 找不到就返回空list
* @param ISBN
* @return
*/
list<Book> getBookByISBN(string ISBN,int exist);

/*通过类别号找到属于这个类别的所有图书并返回
查询的时候要注意exist 属性需要为1(该书未被删除)
如果没有找到则返回空list
*/
list<Book> getBooksByType(int typeId, int exist);

/*根据作者号找到这个作者写过的所有书
查询的时候要注意exist 属性需要为1(该书未被删除)
找不到就返回空list*/
list<Book> getBooksByAuthor(int authorId);

/*由出版社的名字找到其出版的图书
查询的时候要注意exist 属性需要为1(该书未被删除)
找不到就返回空list*/
list<Book> getBooksByPublisher(string publisher);

//这里用string 类型是为了不越界访问字符数组
//如果参数类型是char*,我们无法准确知道传进来的字符数组有多长

/*通过图书名查询图书 这里做的是模糊查询(查找子字符串)
查询的时候要注意exist 属性需要为1(该书未被删除)
找不到就返回空list*/
list<Book> getBooksByName(string name);


/**
* 更改书籍信息
* @param books
* @return
*/
bool modifyBook(Book& book);

/**
* 删除书籍信息（假删除）
* 这里假定id号书一定存在，对其进行删除(判断该书是否存在是上一层做的工作)
* @param books
* @return
*/
bool deleteBook(int id);

/**
* 添加新种类的书籍
* 该函数只负责将book(一本新书)加进图书馆
* 对这本书数据的检查工作在上一层完成
* (上一层需要检查要增加的这本书的ISBN是否已经存在记录里
* 还有这本书的各种信息格式是否正确
)
* @param book
* @return
*/
bool addBook(Book& book);

