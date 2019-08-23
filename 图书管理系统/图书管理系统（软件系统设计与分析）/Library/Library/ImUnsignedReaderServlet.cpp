#include "stdafx.h"
#include "UnsignedReaderServlet.h"


void UnsignedReaderServlet() {
	string choice;
	cout << endl << "由于您未登录，因而只能使用查书功能" << endl;

	while (1) {
		QueryBookService();
		cout << endl << "是否需要继续查书" << endl;
		cout << endl << "1：继续   0：退出" << endl;
		getline(cin, choice);
		if (choice == "1") {

		}
		else if (choice == "0") {
			break;
		}
		else {
			if (DealFault()) {

			}
			else {
				break;
			}
		}
	}
	cout << endl << "已退出" << endl;
}