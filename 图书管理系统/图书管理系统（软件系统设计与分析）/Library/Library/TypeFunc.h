

#include"Structs.h"
#include<list>

//对于书籍的类型，我们就默认一开始加进去的书籍类别在很长时间内都是正确的
//因此不用写删除类型的函数

/*

这是用来增添类别的代码
while (1) {
cout << "请输入一个类别名：" << endl;
string kind;
getline(cin, kind);
trimAllSpace(kind);

if (kind == "#") return 1;

Type t;
setTypeName(t, kind);

if (addType(t)) {
cout << "添加成功！" << endl;
}

*/

/*新增一个书的类型*/
bool addType(Type& type);

bool modifyType(Type& type);


list<Type> getTypeById(int id);

/*根据类别名找到相应的类别(模糊查询)*/
list<Type> getTypeByName(string name);

/*返回所有类别组成的list*/
list<Type> getAllTypes();


