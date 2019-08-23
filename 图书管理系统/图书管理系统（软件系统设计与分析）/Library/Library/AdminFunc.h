#pragma once
/*把函数声明放在头文件里，这样有函数需要调用
AdminFunction函数中的其中一个时，只需要
把这个头文件include进来就可以啦*/
#include<list>
#include<iostream>
#include "Structs.h"
/**
* 更改管理员信息
* @param admin
* @return 若修改成功返回true，否则返回false，然后调用这个函数
的函数继续进行其他处理
*/
bool modifyAdmin(Admin& admin);


/*由id号查找管理员信息
管理员登录会用到这个函数
|查找不到会返回一个空列表
*/
list<Admin> getAdminById(int id);

/*删除一个管理员（假删除，修改exist属性即可)
如果参数id不存在，函数返回false
否则，假删除成功后函数返回true
*/
bool deleteAdmin(int id);


/*新增一个管理员(用于首次新建一个管理员账号
管理员账号只有一个就够了)
新增一条记录之后，形参admin对象的id值会被赋值为其在文件中的id*/
bool addAdmin(Admin& admin);
