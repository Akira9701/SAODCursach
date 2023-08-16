#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

struct record
{
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;
};

struct record1
{
	char a[30];
	short int b;
	char c[22];
	char d[10];
};

struct record2
{
	char a[30];
	unsigned short int b;
	char c[10];
	char d[22];
};

struct record3
{
	char a[32];
	char b[18];
	short int c;
	short int d;
	char e[10];
};

int main()
{
	FILE *fp;
	fp = fopen("file.dat", "rb");
	// record tt[4000] = {0};
	// record1 mas[4000] = {0};
	record2 mas2[4000] = {0};
	// record3 mas3[4000] = {0};
	int i = 0, sum = 0;
	int ch[10];
	i = fread((record2 *)mas2, sizeof(record2), 4000, fp);
	i = 0;
	while ((i++) < 4000)
	{
		// getchar();
		cout << mas2[i].a << " " << mas2[i].b << " " << mas2[i].c << " " << mas2[i].d << endl;
	}

	return 0;
}