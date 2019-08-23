#pragma once

#include"Structs.h"
#include<list>
void QueryBookById(list<Book> &bookList);

void QueryBookByName(list<Book> &bookList);

void QueryBookByISBN(list<Book> &bookList);

void QueryBookByAuthor(list<Book> &bookList);

void QueryBookByType(list<Book> &bookList);

void QueryBookByPublisher(list<Book> &bookList);

/*调用上面几个函数完成查书功能*/
void QueryBookService();