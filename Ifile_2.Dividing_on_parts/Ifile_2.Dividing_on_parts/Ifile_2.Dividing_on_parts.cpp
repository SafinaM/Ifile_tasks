//We have vector with the dimension N. We need to divide it on M < N equal parts (the number of elements in each part is equal to each other).
//Parts should not  overlap and should cover all vector (exception - it is allowed intervals from vector begin to the first part begin and the from the last part end to vector end,
//but in this case the size of thes intervals should be minimum. The result are indexes of the  beginning and end of each part which should be shown on the screen or keept in the
//any structure.

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

typedef unsigned int uint;

int verifData()
{
	int N = 0;
	string tempStr;
	while (N == 0)
	{
		cout << "enter the integer number > 0: ";
		cin >> tempStr;
		N = atoi(tempStr.c_str());  //simple protection from the letters in input
	}
	return N;
}
void dividingOnParts(int M, int size)
{
	if (size > M + 1)
	{
		if (size % M == 0)                         //if the result of division of vector.size()/M is integer
		{
			int part = size / M;                   //the size of part
			for (int k = 0; k < M; ++k)
			{
				cout << "Part " << k + 1 << ": ";  //showing on the screen
				for (int i = k*part; i < (k + 1)*part; i += part - 1)
				{
					cout << i << " ";
				}
				cout << endl;
			}
		}
		else                               //if the result of division of vector.size()/M is NOT integer
		{
			int diff = size % M;           //Reminder from division vector.size()/M
			if (diff % 2 == 0)             //if the result of division of reminder on two is interger...
			{
				int i = 0;
				int part = (size - diff) / M;                 //size of part
				for (int k = 0; k < M; ++k)
				{
					cout << "Part " << k + 1 << ": ";         //showing on the screen
					for (i = k*part + diff / 2; i < (k + 1)*part + diff / 2;)
					{
						cout << i << " ";
						if (M < size / 2 || part != 1)  //if M < size/2  and dist from vector beginning to first part beginning and from the vector end to the last part end not equal 1			
						{
							i += part - 1;
						}
						else                //if M < size/2  and dist from vector beginning to first part beginning and from the vector end to the last part end are equal 1
						{
							cout << i << " ";
							break;
						}
					}
					cout << endl;
				}
			}
			else
			{
				diff += 1;                             // adding the 1 to diff for dividing on
				int divided = size - diff;

				while (divided % M != 0 && divided > 0)
				{
					diff += 2;                        //adding 2    
					divided = size - diff;
				}
				if (divided > 0)
				{
					int part = (size - diff) / M;
					for (int k = 0; k < M; ++k)
					{
						cout << "Part " << k + 1 << ": ";
						for (int i = k*part + diff / 2; i <= (k + 1)*part + diff / 2; i += part - 1)
						{
							cout << i << " ";
						}
						cout << endl;
					}
				}
				else
					cout << "The task with such numbers is not possible." << endl;
			}
		}
	}
	else
		cout << "The task with such numbers is not possible." << endl;
}

int main()
{
	cout << "N: ";
	int size = verifData();
	cout << " M < N: ";
	int M = verifData();

	vector <int> B(size, 0);
	dividingOnParts(M, size);  
	
	cin.ignore();
	cin.get();
	return 0;
}