//Algorithm: we find all prime-numbers from 1 to N with the help of sieve of Eratosthenes and place them to
//temporary vector. Then we verify all numbers in cycle on dividing by prime numbers. We remember the factors which give the result of % ==0 .

#include <iostream>
#include <vector>
#include <string>


using namespace std;

typedef unsigned int uint;

class PrimeFactors                       //class for prime numbers
{
private:
	int *A;                              //dynamic array
	long long int N;                     //dimension of the array
	vector <int> simpleNumbers;          //the vector with the prime numbers
	vector <vector<int>> primeFactors;   //the vector which included other vectors with the prime factors for each number
public:

	PrimeFactors()
	{
		N = 0;
		string tempStr;
		while (N == 0)
		{
			cout << "Enter the integer number: ";
			cin >> tempStr;
			N = atoi(tempStr.c_str());  //simple protection from letters in input
		}

		A = new int[N];
	}
	~PrimeFactors()
	{
		delete[]A;
		cout << "Destructor!" << endl;
	}


	void Eratosfen()
	{

		int j = 0;
		for (int i = 2; i < sqrt(double(N)); ++i)  //sieve of Eratosthenes, finding of the prime numbers, count from 2
		{
			for (j = i*i; j < N; j += i)
			{
				A[j] = false;
			}
		}
	}

	void initArray()
	{
		for (int i = 0; i < N; ++i)
		{
			A[i] = true;
		}
	}

	void InitVector()
	{
		for (int i = 1; i < N; ++i)          //sieve of Eratosthenes, finding of the prime numbers, count from 2, 1 - is prime number
		{
			if (A[i] == true)
			{
				simpleNumbers.push_back(i);  //all prime numbers from 1 to N we push_back in vector вставл€ю в вектор
			}
		}
	}

	void initPrimeFactors()
	{
		int temp = 0;
		int size = simpleNumbers.size();            //size vector with the prime numbers
		vector <int> *temp_ptr = new vector <int>;  //pointer for memory of first element of vector
		primeFactors.push_back(*temp_ptr);
		primeFactors[0].push_back(1);              //place 1-цу to the vector
		int k = 0;
		for (uint i = 1; i <= N; ++i)              //finding of prime factors of each number: divide all numbers on prime numbers finding with the help of sieve of Eratosthenes
		{
			temp = i;
			for (uint j = 1; j < size; ++j)        //count from 1, 0th was added above
			{
				if (temp % simpleNumbers[j] == 0 && temp != 1) //finding of prime factor, which gives the interger number in result
				{
					primeFactors[k].push_back(simpleNumbers[j]);
					temp /= simpleNumbers[j];   //dividing the original number on prime factors, while it != 1
					j = 0;
				}
				if (temp == 1)                 //if the number divided by itself it gives 1 in result, we create new element of vector
				{
					vector <int> *temp_ptr = new vector <int>; //declaration of the pointer
					primeFactors.push_back(*temp_ptr);
					k++;
					break;
				}
			}
		}
	}

	void showSimpleNumbers()
	{
		for (uint i = 0; i < simpleNumbers.size(); ++i)      //sieve of Eratosthenes, finding of the prime numbers, count from 2, 1 - is prime number
		{
			cout << simpleNumbers[i] << " ";
		}
		cout << endl;
	}
	void showPrimeFactors()
	{

		for (uint i = 0; i < primeFactors.size() - 1; ++i)
		{
			cout << i + 1 << " = ";
			for (auto j = primeFactors[i].begin(); j != primeFactors[i].end(); ++j)
			{
				cout << *j;
				if (primeFactors[i].size() > 1 && j != --primeFactors[i].end()) //if size > 1 and the element is non - penultimate
					cout << "*";
			}
			cout << endl;
		}
	}
	void callAllFunctions()
	{
		initArray();
		Eratosfen();
		InitVector();
		showSimpleNumbers();
		initPrimeFactors();

	}
};



int main()
{
	PrimeFactors A;

	A.callAllFunctions();
	A.showPrimeFactors();
	
	cin.ignore();
	cin.get();
	return 0;
}