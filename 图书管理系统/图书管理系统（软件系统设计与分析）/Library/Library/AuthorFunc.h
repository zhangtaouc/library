#pragma once
#include"Structs.h"
#include<list>

/*通过作者id获得作者信息
如果该id的作者不存在则返回一个空list*/
/*由于作者可能被删除(只有在管理员改变一本图书的作者，而且这个作者又没有写过别的书
的时候)，因此文件中作者的id号是不连续的，需要一条一条遍历，不能直接通过id计算文件指针的位置*/
list<Author> getAuthorById(int id);

/*通过作者姓名查找作者信息
如果不存在姓名为name的作者返回一个空list
fuzzyFind为true时，这里的查询为模糊查询
否则必须与姓名全部匹配
*/
list<Author> getAuthorByName(string name,bool fuzzyFind = true);


/*增加一条作者记录（用于增加的图书的读者从未在
读者表里出现过时）*/
bool addAuthor(Author& author);


/*这里是根据读者id真删除一个读者
删除之前需要做很多检验工作
该函数还会把被删除读者后面的读者记录都向前
移动，这些作者的id号都不会发生变化
这是因为这些作者id号还被写在图书表里
不能够随意变化
*/
bool deleteAuthor(int authorId);



