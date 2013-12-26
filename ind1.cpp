// Телефонная книга
// ind 1

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

class Number
{
public:
	string name;
	string number;
	Number(const Number &v):
		name(v.name),
			number(v.number){}
		Number() {}
	const Number &operator=(const Number &v)
	{
		name = v.name;
		number = v.number;
		return v;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<Number> telBook;
	
	cout << "Телефонная книга\n";
	cin.get();
	system("CLS");
	while(1)
	{
		fstream f("file.txt");
		int q;
		system("CLS");
		cout << "Меню\n";
		cout << "1. Просмотр всех\n";
		cout << "2. Поиск\n";
		cout << "3. Добавить\n";
		cout << "4. Выход\n";
		cin >> q;
		switch (q)
		{
		case 1:
			system("CLS");
			while (true)
			{
				Number t;
				f >> t.name;
				if (f.eof())
					break;
				f >> t.number;
				if (f.eof())
					break;
				telBook.push_back(t);
			}
			for (int i = 0; i < telBook.size(); ++i)
			{
				cout << telBook[i].name << " " << telBook[i].number << endl;
			}
			cin.get();
			cin.get();
			system("CLS");
			break;
		case 2:
			system("CLS");
			int w;
			cout << "1. По фамилии\n2. По номеру телефона\n";
			cin >> w;
			system("CLS");
			switch(w)
			{
			case 1:
				while(true)
				{
					cout << "Введите имя (или СТОП)\n";
					string name;
					cin >> name;
					if (name == "СТОП")
					{
						system("CLS");
						break;
					}
					for (int i = 0; i < telBook.size(); ++i)
					{
						if (telBook[i].name == name)
							cout << name << " " << telBook[i].number << endl;
					}
					cin.get();
					cin.get();
					system("CLS");
				}
				break;
			case 2:
				while(true)
				{
					cout << "Введите номер телефона(или СТОП)\n";
					string number;
					cin >> number;
					if (number == "СТОП")
					{
						system("CLS");
						break;
					}
					for (int i = 0; i < telBook.size(); ++i)
					{
						if (telBook[i].number == number)
							cout << telBook[i].name << " " << number << endl;
					};
					cin.get();
					cin.get();
					system("CLS");
				}
				break;
			}
			break;
		case 3:
			while(true)
			{
				system("CLS");
				ofstream fout("file.txt", ios_base::app);
				cout << "Введите фамилию (или СТОП)\n";
				string nam;
				cin >> nam;
				
				if (nam =="СТОП")
					break;
				system("CLS");
				cout << "Введите номер\n";
				string numb;
				cin >> numb;
				system("CLS");
				fout << "\n" << nam << " " << numb << "\n";
				fout.close();
				system("CLS");
				//break;
			}
			break;
		case 4:
			system("CLS");
			return 0;
		}
	}
	return 0;
}