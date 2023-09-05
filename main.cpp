#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>

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

// Пирамидальная сортировка по полю 'a'
void heapifyByFieldA(record2 arr[], int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && strcmp(arr[l].a, arr[largest].a) > 0)
		largest = l;

	if (r < n && strcmp(arr[r].a, arr[largest].a) > 0)
		largest = r;

	if (largest != i)
	{
		swapRecords(arr[i], arr[largest]);
		heapifyByFieldA(arr, n, largest);
	}
}

void heapSortByFieldA(record2 arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapifyByFieldA(arr, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swapRecords(arr[0], arr[i]);
		heapifyByFieldA(arr, i, 0);
	}
}

// Пирамидальная сортировка по полю 'b' (от большего к меньшему)
void heapifyByFieldB(record2 arr[], int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && arr[l].b > arr[largest].b)
		largest = l;

	if (r < n && arr[r].b > arr[largest].b)
		largest = r;

	if (largest != i)
	{
		swapRecords(arr[i], arr[largest]);
		heapifyByFieldB(arr, n, largest);
	}
}

void heapSortByFieldB(record2 arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapifyByFieldB(arr, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swapRecords(arr[0], arr[i]);
		heapifyByFieldB(arr, i, 0);
	}
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

	cout << "Choose sorting field (name or sum) name/sum: ";
	cin >> word;

	if (word == "name")
	{
		heapSortByFieldA(mas2, 4000); // Сортировка по полю 'a'
	}
	else if (word == "sum")
	{
		heapSortByFieldB(mas2, 4000); // Сортировка по полю 'b'
	}
	else
	{
		cerr << "Invalid sorting field." << endl;
		return 1;
	}

	cout << "Show list of users? (Y/N)" << endl;
	cin >> word;

	if (word == "y")
	{

		while (counter < 4000)
		{

			if (word == "y" || word == "d")
			{
				counter += 20;
				maxPage += 20;
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
				cout << "End: r" << endl;
				cin >> word;
			}
			else if (word == "a")
			{
				counter -= 20;
				maxPage -= 20;

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
				cout << "End: r" << endl;
				cin >> word;
			}
			else
			{
				exit(0);
				return 0;
			}
		}
	}

	return 0;
}
