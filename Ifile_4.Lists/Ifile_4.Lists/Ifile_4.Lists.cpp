//Task: we have simple list. 1, 2 .. 8. Please get the list 1, 8, 2, 7, 6, 4, 5
#pragma warning(disable: 4018)
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <iomanip>


using namespace std;

typedef unsigned int uint;

struct Node
{
	Node *Next;
	int x;

};

class SimpleList
{
public:
	Node *Head;
	int size;
	//constructor
	SimpleList()
	{
		Head = NULL;
		size = 0;
	}
	//destructor
	~SimpleList()
	{
		Node *temp = Head;
		while (temp != 0)
		{
			temp = temp->Next;
			delete Head;
			Head = temp;
		}
		size = 0;
	}
	//add x to the list
	void Add(int x)
	{
		Node *temp = new Node;
		temp->x = x;
		temp->Next = Head;
		Head = temp;
		size++;
	}
	void initSimpleList(int length)
	{
		for (int i = length; i != 0; --i)
			Add(i);
	}

	//add to list N the same values
	void Add(int x, int N)
	{
		for (int i = 0; i < N; i++)
		{
			Node *temp = new Node;
			temp->x = x;
			temp->Next = Head;
			Head = temp;
			size++;
		}
	}

	//clearing of the list
	void Clear()
	{
		Node *temp = Head;
		while (temp != 0)
		{
			temp = temp->Next;
			delete Head;
			Head = temp;
		}
		size = 0;
	}

	//printing
	void showList()
	{
		cout << setw(16) << "Simple list: ";
		Node *temp = Head;
		while (temp != 0)
		{
			cout << temp->x << " ";
			temp = temp->Next;
		}
		cout << endl;
	}

	int &operator[](int N) //operator overloading[]     
	{
		Node *temp = Head;
		for (int i = 0; i < N; i++)
		{
			temp = temp->Next;
		}
		return temp->x;
	}

	void partsToVector(int N)
	{
		Node *temp = Head;
		//declaration of first temporary vector
		vector <int> tempVec;

		for (uint i = 0; i < N; i++)
		{
			tempVec.push_back(temp->x);
			temp = temp->Next;
		}

		for (uint i = 0; i < N / 2+1; i +=2)
		{
			auto it = tempVec.begin();       //VS gives the mistake: the itarator is not incrementable
			advance(it, i);
			tempVec.insert(++it, tempVec.back());
			tempVec.pop_back();
		}
		//clearing of the list
		Clear();
		//adding vector to the list
		for (uint i = tempVec.size() - 1; i > 0; --i)
		{
			Add(tempVec[i]);
		}
		Add(tempVec[0]);        //tempVec[0]-is last
		showList();           //printing of the list
	}

	int getSize()
	{
		return size;
	}

};
//these functions shows the work with standard library, 
void initStdList(list <int> &lst, int size)
{
	for (int i = 1; i <= size; ++i)
		lst.push_back(i);
}
void purposeAlgorithm(list <int> &lst)
{
	int len = lst.size();
	auto it = lst.begin();
	for (auto i = 0; i < len / 2; ++i)
	{
		lst.insert(++it, lst.back());
		lst.pop_back();
	}
}
void showStdList(list <int> &lst)
{
	cout << setw(16) << "Standard list: ";

	for (auto it = lst.begin(); it != lst.end(); ++it)
		cout << *it << " ";
	cout << endl;
}


int main()
{
	SimpleList L;       //LIFO we do not have Tail
	int size = 8;
	L.initSimpleList(size);
	

	int sizeL = L.getSize();

	L.showList();
	L.partsToVector(sizeL);

	
	list <int> lst; //this is the variant of the task for standard elements, but it is not very interesting))), 
	                //besides list is 2-directional one
	initStdList(lst, size); 
	purposeAlgorithm(lst);
	showStdList(lst);

	cin.ignore();
	cin.get();
	return 0;
}