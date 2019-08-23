#pragma once
#include"stdafx.h"
#include<iostream>
#include <string>
#include <map>
#include "DealFault.h"
using namespace std;
/**
登录界面
*/
map<string, int> LoginServlet();


/*读者注册，若注册成功返回读者id号，否则返回0*/
bool SignUpServlet();