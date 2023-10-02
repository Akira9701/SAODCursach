#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include <regex>

using namespace std;

struct record2
{
	char a[30];
	unsigned short int b;
	char c[10];
	char d[22];
};

// Функция для обмена двух записей
void swapRecords(record2 &a, record2 &b)
{
	record2 temp = a;
	a = b;
	b = temp;
}

// Сравнение двух записей по сложному ключу
int compareRecords(record2 &a, record2 &b)
{
	// Сравнение по первым 3 символам поля 'a'
	int cmp = strncmp(a.a, b.a, 30);

	// Если первые 3 символа одинаковы, сравнение по полю 'b'
	if (cmp == 0)
	{
		if (a.b < b.b)
			return -1;
		else if (a.b > b.b)
			return 1;
		else
			return 0;
	}

	return cmp;
}

// Построение кучи по сложному ключу
void heapifyByComplexKey(record2 arr[], int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	// Используем функцию compareRecords для сравнения
	if (l < n && compareRecords(arr[l], arr[largest]) > 0)
		largest = l;

	if (r < n && compareRecords(arr[r], arr[largest]) > 0)
		largest = r;

	if (largest != i)
	{
		swapRecords(arr[i], arr[largest]);
		heapifyByComplexKey(arr, n, largest);
	}
}

// Сортировка кучей по сложному ключу
void heapSortByComplexKey(record2 arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapifyByComplexKey(arr, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swapRecords(arr[0], arr[i]);
		heapifyByComplexKey(arr, i, 0);
	}
}

bool isNumber(const std::string &str)
{
	// Регулярное выражение, которое соответствует целым числам (с или без знака)
	std::regex pattern("^[-+]?\\d+$");

	// Проверяем, соответствует ли строка регулярному выражению
	return std::regex_match(str, pattern);
}

int main()
{
	int counter = -20;
	int maxPage = 0;
	std::string word;
	FILE *fp;
	fp = fopen("file.dat", "rb");
	record2 mas2[4000] = {0};
	int i = 0;
	i = fread((record2 *)mas2, sizeof(record2), 4000, fp);
	i = 0;

	cout << "Show list of users? (Y/N)" << endl;
	cin >> word;

	if (word == "y")
	{
		cout << "Sort y/n ?" << endl;
		cin >> word;
		if (word == "y")
		{
			heapSortByComplexKey(mas2, 4000); // Сортировка по сложному ключу
		}

		while (counter < 4000)
		{

			if (word == "y" || word == "n" || word == "d")
			{
				counter += 20;
				maxPage += 20;
			}
			else if (word == "a")
			{
				counter -= 20;
				maxPage -= 20;
			}
			else if (isNumber(word))
			{

				counter = std::stoi(word) * 20;
				maxPage = 20 + std::stoi(word) * 20;
			}
			else
			{
				exit(0);
				return 0;
			}
			cout << "\033[2J\033[1;1H";

			cout << "Number"
				 << "\t"
				 << "Name"
				 << "\t\t\t\t"
				 << "Dolg"
				 << "\t"
				 << "Date"
				 << "\t\t"
				 << "Lowyer" << endl;
			for (int i = counter; i < maxPage; i++)
			{
				cout << i + 1 << "\t" << mas2[i].a << "\t" << mas2[i].b << "\t" << mas2[i].c << "\t" << mas2[i].d << endl;
			}

			cout << endl;
			cout << "Prev: a" << endl;
			cout << "Next: d" << endl;
			cout << "Any page: number" << endl;
			cout << "End: r" << endl;
			cin >> word;
		}
	}

	return 0;
}
