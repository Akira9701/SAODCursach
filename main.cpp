#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include <regex>
#include <queue>

using namespace std;

struct record2
{
	char a[30];
	unsigned short int b;
	char c[10];
	char d[22];
};

void swapRecords(record2 &a, record2 &b)
{
	record2 temp = a;
	a = b;
	b = temp;
}

int compareRecords(record2 &a, record2 &b)
{
	int cmp = strncmp(a.a, b.a, 30);
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

void heapifyByComplexKey(record2 arr[], int index[], int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && compareRecords(arr[index[l]], arr[index[largest]]) > 0)
		largest = l;
	if (r < n && compareRecords(arr[index[r]], arr[index[largest]]) > 0)
		largest = r;
	if (largest != i)
	{
		swap(index[i], index[largest]);
		heapifyByComplexKey(arr, index, n, largest);
	}
}

void heapSortByComplexKey(record2 arr[], int index[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapifyByComplexKey(arr, index, n, i);
	for (int i = n - 1; i >= 0; i--)
	{
		swap(index[0], index[i]);
		heapifyByComplexKey(arr, index, i, 0);
	}
}

bool isNumber(const std::string &str)
{
	std::regex pattern("^[-+]?\\d+$");
	return std::regex_match(str, pattern);
}

void displayRecords(record2 arr[], int index[], int start, int end, int i)
{
	cout << "Number"
		 << "\t"
		 << "Name"
		 << "\t\t\t\t"
		 << "Dolg"
		 << "\t"
		 << "Date"
		 << "\t\t"
		 << "Lowyer" << endl;
	for (int j = start; j < end && j < i; j++)
	{
		int recordIndex = index[j];
		cout << j + 1 << "\t" << arr[recordIndex].a << "\t" << arr[recordIndex].b << "\t" << arr[recordIndex].c << "\t" << arr[recordIndex].d << endl;
	}
	cout << endl;
	cout << "Prev: p" << endl;
	cout << "Next: n" << endl;
	cout << "Any page: number" << endl;
	cout << "Search: s" << endl;
	cout << "Return to Menu: m" << endl;
}

int main()
{
	int counter = 0;
	int maxPage = 20;
	std::string word;
	bool sorted = false; // Flag to track if the list is sorted
	FILE *fp;
	fp = fopen("file.dat", "rb");
	record2 mas2[4000] = {0};
	int index[4000] = {0}; // Index array to maintain the order
	int i = 0;
	i = fread((record2 *)mas2, sizeof(record2), 4000, fp);
	fclose(fp);

	// Initialize the index array
	for (int j = 0; j < i; j++)
	{
		index[j] = j;
	}

	while (true)
	{
		cout << "Main Menu:" << endl;
		cout << "a. Show sorted list" << endl;
		cout << "b. Show unsorted list" << endl;
		cout << "c. Search by key" << endl;
		cout << "d. Exit" << endl;
		cin >> word;

		if (word == "a")
		{
			sorted = true;
		}
		else if (word == "b")
		{
			sorted = false;
		}
		else if (word == "c")
		{
			cout << "Enter a search key (3 characters) or 'q' to quit: ";
			cin >> word;
			if (word == "q" || word == "Q")
			{
				continue;
			}

			if (word.length() != 3)
			{
				cout << "Invalid search key length. It must be 3 characters." << endl;
				continue;
			}

			cout << "Matching Records:" << endl;
			queue<record2> matchingRecords;

			for (int j = 0; j < i; j++)
			{
				if (strncmp(mas2[index[j]].a, word.c_str(), 3) == 0)
				{
					matchingRecords.push(mas2[index[j]]);
				}
			}
			cout
				<< "Name"
				<< "\t\t\t\t"
				<< "Dolg"
				<< "\t"
				<< "Date"
				<< "\t\t"
				<< "Lowyer" << endl;
			while (!matchingRecords.empty())
			{
				record2 record = matchingRecords.front();
				matchingRecords.pop();

				cout << record.a << "\t" << record.b << "\t" << record.c << "\t" << record.d << endl;
			}
			cout << "Press m to go back...";
			cin >> word;
		}
		else if (word == "d")
		{
			break;
		}

		if (sorted)
		{
			heapSortByComplexKey(mas2, index, i);
		}

		while (counter < i)
		{
			if (word == "n")
			{
				counter += 20;
				maxPage += 20;
			}
			else if (word == "p")
			{
				counter -= 20;
				maxPage -= 20;
			}
			else if (isNumber(word))
			{
				counter = std::stoi(word) * 20;
				maxPage = 20 + std::stoi(word) * 20;
			}
			else if (word == "m" || word == "M")
			{
				break;
			}

			cout << "\033[2J\033[1;1H"; // Clears the console screen
			displayRecords(mas2, index, counter, maxPage, i);
			cin >> word;
		}
	}

	return 0;
}
