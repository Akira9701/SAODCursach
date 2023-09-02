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

int main()
{
	int counter = 0;
	int maxPage = 20;
	std::string word;
	FILE *fp;
	fp = fopen("file.dat", "rb");
	record2 mas2[4000] = {0};
	int i = 0;
	i = fread((record2 *)mas2, sizeof(record2), 4000, fp);
	i = 0;
	heapSortByFieldA(mas2, 4000); // Сортировка по полю 'a'

	cout << "Show list of users? (Y/N)" << endl;
	cin >> word;
	if (word == "y")
	{
		for (int i = counter; i < maxPage; i++)
		{
			cout << i + 1 << " " << mas2[i].a << " " << mas2[i].b << " " << mas2[i].c << " " << mas2[i].d << endl;
		}
		counter += 20;
		maxPage += 20;
	}
	while (counter < 4000)
	{
		cout << "Continue? (Y/N)" << endl;
		cin >> word;
		if (word == "y")
		{
			for (int i = counter; i < maxPage; i++)
			{
				cout << i + 1 << " " << mas2[i].a << " " << mas2[i].b << " " << mas2[i].c << " " << mas2[i].d << endl;
			}
			counter += 20;
			maxPage += 20;
		}
		else
		{
			exit;
		}
	}

	return 0;
}