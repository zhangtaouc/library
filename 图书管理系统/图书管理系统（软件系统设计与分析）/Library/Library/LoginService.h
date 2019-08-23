#pragma once
#include"stdafx.h"
#include "Structs.h"
#include "ReaderFunc.h"
#include <iostream>
#include <string>
#include "DealFault.h"
using namespace std;/*这是用于注册和登陆的函数的头文件*/

/*管理员登录，若登陆成功返回管理员id号，否则返回0*/
int AdminLoginService();

/***
读者登录函数
***/
int ReaderLoginService();


/**
新增一个读者
*/
int SignUpService(Reader reader);