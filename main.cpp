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

int compareRecords(record2 &a, record2 &b) {
    int cmp = strncmp(a.a, b.a, 30);
    if (cmp == 0) {
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


struct AVLNode {
    record2 data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

int getHeight(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int getBalanceFactor(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLNode* insert(AVLNode* root, record2 data) {
    if (root == nullptr) {
        AVLNode* newNode = new AVLNode;
        newNode->data = data;
        newNode->left = newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (compareRecords(data, root->data) < 0) {
        root->left = insert(root->left, data);
    } else if (compareRecords(data, root->data) > 0) {
        root->right = insert(root->right, data);
    } else {
        // Duplicate data, handle as needed
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalanceFactor(root);

    // Left Heavy
    if (balance > 1) {
        if (compareRecords(data, root->left->data) < 0) {
            return rotateRight(root);
        } else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    // Right Heavy
    if (balance < -1) {
        if (compareRecords(data, root->right->data) > 0) {
            return rotateLeft(root);
        } else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root;
}



struct TreeNode
{
    record2 data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* next; // Связанный список объектов с одинаковым ключом b
};

// Функция для вставки нового объекта в связанный список
TreeNode* insertIntoLinkedList(TreeNode* head, record2 data)
{
    TreeNode* newNode = new TreeNode;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->next = head;
    return newNode;
}

// Функция для вставки объекта в AVL-дерево
TreeNode* insertNode(TreeNode* node, record2 data)
{
    if (node == nullptr)
    {
        TreeNode* newNode = new TreeNode;
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->next = nullptr;
        return newNode;
    }

    if (data.b == node->data.b)
    {
        // Вставляем объект в связанный список текущего узла
        node->next = insertIntoLinkedList(node->next, data);
    }
    else if (data.b < node->data.b)
        node->left = insertNode(node->left, data);
    else
        node->right = insertNode(node->right, data);

    return node;
}

// Функция для обхода и вывода объектов в дереве


AVLNode* searchByFieldB(AVLNode* root, unsigned short int searchValue) {
    if (root != nullptr) {
        // Рекурсивный обход левого поддерева
        searchByFieldB(root->left, searchValue);

        // Если поле 'b' равно заданному значению, вывести информацию
        if (root->data.b == searchValue) {
            cout << "Name: " << root->data.a << endl;
            cout << "Key: " << root->data.b << endl;
            cout << "Dolg: " << root->data.c << endl;
            cout << "Date: " << root->data.d << endl;
            cout << "------------------------" << endl;
        }

        // Рекурсивный обход правого поддерева
        searchByFieldB(root->right, searchValue);
    }
}

AVLNode* buildAVLTreeFromQueue(queue<record2>& matchingRecords) {
    AVLNode* root = nullptr;

    while (!matchingRecords.empty()) {
        record2 record = matchingRecords.front();
        matchingRecords.pop();

        root = insert(root, record);
    }

    return root;
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
	AVLNode* avlTreeRoot = nullptr;


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
		if(avlTreeRoot != nullptr){
		cout << "o. Display tree" << endl;

		}
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

			queue<record2> copyOfMatchingRecords = matchingRecords; // Создаем копию очереди

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

			avlTreeRoot = buildAVLTreeFromQueue(copyOfMatchingRecords); // Строим AVL-дерево из копии

			cout << "Press m to go back...";
			cin >> word;

		

				// Вывод данных в AVL-дереве с учетом объектов с одинаковыми ключами
				// inOrderTraversal(root);
			
		}
		else if (word == "d")
		{
			break;
		}
		else if (word == "o"){
			cout << "Write price";
			cout << endl;

			cin >> word;
			cout << endl;
			cout << endl;
			AVLNode* result = searchByFieldB(avlTreeRoot, std::stoul(word));
			if (result != nullptr) {
    // Узел был найден, вы можете что-то сделать с данными в этом узле
				cout << "Name: " << result->data.a << endl;
				cout << "Dolg: " << result->data.b << endl;
				cout << "Date: " << result->data.c << endl;
				cout << "Lowyer: " << result->data.d << endl;
			} else {
				// Узел с указанным значением не был найден
				cout << "Node with value " << "5000" << " not found." << endl;
			}
				cout << "Press m to go back...";
			cin >> word;
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
