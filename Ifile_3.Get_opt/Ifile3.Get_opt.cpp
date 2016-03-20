//Write simple analog of getopt.


//Testing variants:
//1) without help, succsess
//--my-boolean-option = true --my-option-name my-option-name --my-option-fval 0.7 --my-option-ival=11
//
//2) with help, returns 0
// --help
//--my-boolean-option true --help --my-option-name my-option-name --my-option-fval 0.7 --my-option-ival 11
//
//3) incorrect input
//--my-boolean-option sfd; --my-option-name = my-option-name --my-option-fval 0.7 --my-option-ival=11 --my-option-name tyu 
//
//4) mistake  --
//my-boolean-option sfd; --my-option-name my-option-name --my-option-fval =  0.7 --my-option-ival 11
//
//5) mistake, cannot to transform to float or to int
//--my-boolean-option --my-option-name = my-option-name --my-option-fval=0.7 --my-option-ival=map

//6) succsess
//--my-boolean-option false --my-option-name = my-option-name --my-option-fval=0.7 --my-option-ival 12

#pragma warning(disable:4244)
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>


using namespace std;
typedef unsigned int uint;

struct Data
{
	int iValue = 0;
	float fValue = 0.0;
	string name = "";
	bool flag = false;
	string help = "";
	
	void clear()
	{
		iValue = 0;
		fValue = 0.0;
		name = "";
		flag = false;
		help = "";
	}
	void printData(const Data &data, vector<vector<string>> &Rules)
	{
		cout << "Data:" << endl;
		cout << endl;
		for (uint i = 0; i < Rules.size()-1; ++i)
		{
			if (Rules[i][2] == "false")
				cout << setw(10) << Rules[i][0] << setw(25 - Rules[i][1].length() - 1) << "[" << Rules[i][1] << "]";
			if (Rules[i][2] == "true")
				cout << setw(10) << Rules[i][0] << setw(25) << Rules[i][1];
			if (i == 0)
				cout <<setw(15) << data.iValue;
			if (i == 1)
				cout << setw(15) << data.fValue;
			if (i == 2)
				cout << setw(15) << data.name;
			if (i == 3)
				cout << setw(15) << data.flag;
			cout << endl;
		}

	}

};

void bite_off(string &str, string &temp_str) //the parser for input string by " " or "=" or " = "
{ 
	while (str.find("=") != -1)
	{
		int k = str.find("=");
		str[k] = ' ';
	}
	while (str.find("  ") != -1)  //delete 2 or 3 spaces and spaces in the begin of the input string
	{
		int k = str.find("  ");
		str.erase(str.begin() + k);
	}
	int x = str.find(" ");
	if( x != -1)
	{
		temp_str.assign(str, 0, x);
		str.erase(0, x+1);
		cout << str << endl;
		cout << temp_str << endl;
	}
	else
	{
		temp_str.assign(str, 0, str.length());
		str.erase(0, str.length());
	}

	
}
void print(vector <vector<string>> Rules)
{
	cout << setw(10) << "TYPE" << setw(25) << "NAME" << setw(12) << "NECESSITY" << endl;
	cout << endl;
	for (uint i = 0; i < Rules.size(); ++i)
	{
			if (Rules[i][2] == "false")
				cout << setw(10) << Rules[i][0] << setw(25-Rules[i][1].length()-1) << "[" <<Rules[i][1] << "]" << setw(12) << Rules[i][2] << endl;
			if(Rules[i][2] == "true")
				cout << setw(10) << Rules[i][0] << setw(25) << Rules[i][1] << setw(12) << Rules[i][2] << endl;
			cout << endl;
	}
}
int getopt(string &str, vector <vector<string>> &Rules) //if in input string there are few parameters of one type, the function keeps the last one
{                                                             
	Data data;
	

    
	string temp_str;
	bite_off(str, temp_str);  //parser of the input_string by " " or " = " or "="
	
	uint i;
	do
	{
		int k = -1;
		bool already_bite_off = false;    //the flag shows the result of bite_off()
		for (i = 0; i < Rules.size(); ++i)
		{
			if (temp_str == Rules[i][1])
			{
				k = i;
				if (Rules[k][1] == "--help")
				{
					print(Rules);
					return 0;            //the function getopt return 0 in the help case
				}
				break;
			}
		}
		if (k != -1)
		{
			if (Rules[k][0] == "bool") //if the param bool is existing without of a value then the data.flag is changing on TRUE 
			{
				bite_off(str, temp_str);

				if (temp_str == "1" || temp_str == "true")
				{
					data.flag = true;

				}
				else if (temp_str == "0" || temp_str == "false")
				{
					data.flag = false;
				}
				else
				{
					data.flag = true;
					already_bite_off = true;
				}	
			}
			else if (Rules[k][0] == "int")
			{
				bite_off(str, temp_str);
				data.iValue = atoi(temp_str.c_str());
				if (data.iValue == 0)
				{
					cout << "Mistake, type 1: incorrect type of integer value: " << temp_str << endl; // mistake(2), case of incorrect value after command
					return -1;
				}
			}
			else if (Rules[k][0] == "float")
			{
				bite_off(str, temp_str);
				data.fValue = atof(temp_str.c_str());
				if (data.fValue == 0)
				{
					cout << "Mistake, type 1: incorrect type of float value: " << temp_str << endl; //the function mistake(1), case of incorrect value after command
					return -1;
				}
			}
			else if (Rules[k][0] == "string")
			{
				bite_off(str, temp_str);
				data.name = temp_str;
			}
		}
		else
		{
			string tempRules;
			for (uint j = 0; j < Rules.size(); ++j)
			{
				tempRules.assign(Rules[j][1], 2, Rules[j][1].length()); //init of temporaries values for incorrect commands, ival
				if (temp_str == tempRules)
				{
					cout << "Mistake, type 2: add \"--\" to your command: " << temp_str << endl; //the mistake(2), the case of incorrect input coomand without "--"
					return -1;
				}
			}
			cout << "Mistake, type 3: incorrect input:" << temp_str << endl; //the mistake(3), the case of incorrect input command  without "--"
			return -1;	
		}
		if(str.length() != 0 && !already_bite_off)
			bite_off(str, temp_str);  //parser of the input_string by " " or " = " or "="
	} while (str.length() != 0);
	data.printData(data, Rules);
	return 1;
}
void deleteStartAndEndSpaces(string &str)
{
	while (str[0] == ' ')
	{
		str.erase(str.begin());
	}
	while (str[str.length() - 1] == ' ')
	{
		str.erase(str.length() - 1);
	}
}


int main()
{
	//we can change the Rules for getopt verifying. In this case please do not forget to change testing examples.
	vector <vector<string>> Rules = { { "int",    "--my-option-ival",    "true"},  //input vector of possible values and types
	                                  { "float",  "--my-option-fval",    "true" },  //first row - type, second row - name, third row - required or not
						              { "string", "--my-option-name",    "false" },
									  { "bool",   "--my-boolean-option", "true" },
									  { "string", "--help",             "false" } };
	
	string str ="";     //input string
	cout << "Enter the string, please: " << endl;

	while(str.length() == 0)
		getline(cin, str);

	deleteStartAndEndSpaces(str);          //cleaning of the input_string from start and end spaces
	cout << "String: " << str << endl;

	int tumb = getopt(str, Rules);
	cout << "getopt returns: " << tumb << endl;
	
	cin.get();
	return 0;
}
