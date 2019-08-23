#pragma once
#include <list>
#include "Structs.h"


/**
* 根据唯一的Id查找读者
* 找不到返回一个空list
* @param id
* @return
*/
list<Reader> getReaderById(int id);

/**
* 根据性别查找读者
* @param sex sex取1代表男性，0代表女性
* 这和类定义里sex属性是一致的
* 找不到返回一个空list
* @return
*/
list<Reader> getReadersBySex(int sex);

/**
* 根据名字查找读者(模糊查询)
* @param name
* @return
*/
list<Reader> getReadersByName(string name);

/**
* 获得所有读者的信息
* @return
*/
list<Reader> getReaders();


/**
* /添加读者
* 这里也是只考虑向读者表中添加一条读者记录
* 检查读者信息的工作上一层来完成
* @param reader
* @return
*/
bool addReader(Reader& reader);

/**
* 更改读者信息
* @param reader
* @return
*/

bool modifyReader(Reader& reader);

/*删除一个读者(假删除，修改exist属性即可)
如果参数id不存在，函数返回false
否则，假删除成功后函数返回true
*/
bool deleteReader(int id);