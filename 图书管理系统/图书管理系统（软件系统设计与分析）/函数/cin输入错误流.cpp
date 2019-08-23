int main()
{
	int a;
	while (1)
	{
		cout << "�����һ��������";
		cin >> a;
		if (!cin)            //�����ɸ�дΪcin.fail() 
		{
			cout << "�����д�!����������" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			cout << a;
			break;
		}
	}
	system("pause");
	return 1;
}

