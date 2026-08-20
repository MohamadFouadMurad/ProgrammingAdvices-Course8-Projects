#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;
const string ClientFileName = "Client.txt";

namespace myfunc
{

	int ReadNumber(string message)
	{
		int Number = 0;
		cout << message << " : ";
		cin >> Number;
		return Number;
	}

	int ReadFloatNumber(string message)
	{
		float Number = 0;
		cout << message << " : ";
		cin >> Number;
		return float(Number);
	}

	int ReadDoubeleNumber(string message)
	{
		double Number = 0;
		cout << message << " : ";
		cin >> Number;
		return double(Number);
	}

	string ReadFullName(string message)
	{
		cout << message;
		string FullName = "";
		getline(cin, FullName);
		return FullName;
	}

	string CheckPositiveOrNegativeOrZero(int number)
	{
		if (number > 0)
			return "positive";
		else if (number < 0)
			return "negative";
		else
			return "zero";
	}

	int ReadValidNumberOnly(string message)
	{
		int Number;
		cout << message << endl;
		cin >> Number;


		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid Number, Enter a valid one:" << endl;
			cin >> Number;
		}

		return Number;
	}

	void SetWidthInCenter(int Width, string message)
	{
		int Length = message.length();

		if (Length >= Width)
		{
			cout << message;
			return;
		}

		int leftSpaces = (Width - Length) / 2;
		int rightSpaces = Width - Length - leftSpaces;

		cout << string(leftSpaces, ' ');
		cout << message;
		cout << string(rightSpaces, ' ');
	}

}

namespace InPut
{
	int printMessageAndReadNumberFromTo(string message, int from, int to)
	{
		int num = 0;
		do
		{
			cout << message << "From" + to_string(from) + "To" + to_string(to) << endl;
			cin >> num;
		} while (num > to || num < from);

		return num;
	}

	int ReadPositiveNumber(string message)
	{
		int num;

		do
		{
			cout << message << endl;
			cin >> num;
		} while (num < 0);

		return num;
	}
}

namespace OutPut
{
	void FindNumberIndex(int arr[100], int arrLength, int target)
	{
		cout << "number you are looking for is: " << target << endl;

		for (int i = 0; i < arrLength; i++)
		{
			if (target == arr[i])
			{
				cout << "the number found at position : " << i << "\n";
				cout << "the number found it's order  : " << i + 1 << "\n";
				return;
			}
		}

		cout << "the number is not found :-(\n";
	}

	void PrintArray(int arr[], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			cout << arr[i] << "\t";
		}
	}

	void PrintStringArray(string arr[], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
			cout << "code [" << i + 1 << "] : " << arr[i] << endl;
	}

	string Taps(short NumberOfTaps)
	{
		string tap = "";

		for (int i = 1; i <= NumberOfTaps; i++)
		{
			tap += "\t";
		}

		return tap;
	}

}

namespace Helpers
{
	int RandomNumber(int from, int to)
	{
		int RandomNumber;
		return RandomNumber = rand() % (to - from + 1) + from;
	}

	void FillArrayWithRandomNumbers(int arr[], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = RandomNumber(1, 100);
	}

	void CopyReverseArray(int arr1[], int arr2[], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			arr2[i] = arr1[arrLength - 1 - i];
		}
	}

	string GenerateWord()
	{
		string word = "";
		word = char(RandomNumber(65, 90));
		word += char(RandomNumber(65, 90));
		word += char(RandomNumber(65, 90));
		word += char(RandomNumber(65, 90));
		return word;
	}

	string GenerateCode()
	{
		string Text = GenerateWord() + "-";
		Text += GenerateWord() + "-";
		Text += GenerateWord() + "-";
		Text += GenerateWord();
		return Text;
	}

	void FillStringArray(string arr[], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateCode();
	}

	bool IsInArray(int searchValue, int arr[], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			if (searchValue == arr[i])
				return true;
		}
		return false;
	}

	bool IsPrimeNumber(int num)
	{
		int M = round(num / 2);
		for (int i = 2; i <= M; i++)
		{
			if (num % i == 0)
				return false;
		}
		return true;
	}

	bool IsPalindrome(int arr[], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] != arr[arrLength - i - 1])
			{
				return false;
			}
		}
		return true;
	}

	bool IsEvenNumber(int number)
	{
		return (number % 2 == 0);
	}

	void ResetScreen()
	{
		system("cls");
		system("color 0F");
	}
}

namespace String
{

	string ReadString()
	{
		string S1;
		cout << "Please Enter Your String?\n";
		getline(cin >> ws, S1);
		return S1;
	}

	void LowerFirstLettFromEachWord(string Name)
	{
		cout << endl;

		int isFirstLetter = true;

		cout << "String After Conversion: " << endl;

		for (int i = 0; i < Name.length(); i++)
		{
			if (Name[i] != ' ' && isFirstLetter)
			{
				Name[i] = tolower(Name[i]);
			}

			isFirstLetter = (Name[i] == ' ' ? true : false);
		}

		cout << Name << endl;
	}

	void UpperFirstLettFromEachWord(string Name)
	{
		cout << endl;

		int isFirstLetter = true;

		cout << "String After Conversion: " << endl;

		for (int i = 0; i < Name.length(); i++)
		{
			if (Name[i] != ' ' && isFirstLetter)
			{
				Name[i] = toupper(Name[i]);
			}

			isFirstLetter = (Name[i] == ' ' ? true : false);
		}

		cout << Name << endl;
	}

	void LowerAllString(string Name)
	{
		for (int i = 0; i < Name.length(); i++)
		{
			if (Name[i] != ' ')
			{
				Name[i] = tolower(Name[i]);
			}
		}

		cout << Name << endl;
	}

	void UpperAllString(string Name)
	{

		for (int i = 0; i < Name.length(); i++)
		{
			if (Name[i] != ' ')
			{
				Name[i] = toupper(Name[i]);
			}
		}

		cout << Name << endl;
	}

	char InvertLetterCase(char Char1)
	{
		return isupper(Char1) ? tolower(Char1) : toupper(Char1);
	}

	int CountCapitalLetters(string S1)
	{

		int count = 0;

		for (int i = 0; i < S1.length(); i++)
		{
			if (isupper(S1[i]))
			{
				count++;
			}
		}

		return count;
	}

	int CountSmallLetters(string S1)
	{
		int count = 0;

		for (int i = 0; i < S1.length(); i++)
		{
			if (islower(S1[i]))
			{
				count++;
			}
		}

		return count;
	}

	vector <string> SplitString(string S1, string Delim)
	{
		vector <string> vString;

		short pos = 0;
		string sWord;

		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);

			if (sWord != "")
			{
				vString.push_back(sWord);
			}

			S1.erase(0, pos + Delim.length());
		}

		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}

		return vString;
	}

	string JoinString(vector <string>& vString, string delim)
	{
		string S1 = "";

		for (string& word : vString)
		{
			if (!S1.empty())
			{
				S1 += delim;
			}
			S1 += word;
		}

		return S1;
	}

	string RemovePunctuationsFromString(string S1)
	{
		string S2 = "";

		for (int i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}

		return S2;
	}

}

namespace Files
{
	struct sClient
	{
		string AccountNumber = "";
		string PinCode = "";
		string Name = "";
		string Phone = "";
		int AccountBalance = 0;
	};

	sClient ReadClintData()
	{
		sClient data;

		cout << "enter Account Number? ";
		getline(cin >> ws, data.AccountNumber);

		cout << "enter Pincode? ";
		getline(cin, data.PinCode);

		cout << "enter Name?";
		getline(cin, data.Name);

		cout << "enter phone?";
		getline(cin, data.Phone);

		cout << "enter Accountbalance?";
		cin >> data.AccountBalance;

		return data;
	}

	string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
	{
		string stClintRecord = "";

		stClintRecord += Client.AccountNumber + Seperator;
		stClintRecord += Client.PinCode + Seperator;
		stClintRecord += Client.Name + Seperator;
		stClintRecord += Client.Phone + Seperator;
		stClintRecord += to_string(Client.AccountBalance);

		return stClintRecord;
	}

	sClient ConvertLineToRecord(string stLine, string Seperator = "#//#")
	{

		vector <string> vClientData = String::SplitString(stLine, Seperator);

		sClient Client;

		Client.AccountNumber = vClientData[0];
		Client.PinCode = vClientData[1];
		Client.Name = vClientData[2];
		Client.Phone = vClientData[3];
		Client.AccountBalance = stoi(vClientData[4]);

		return Client;

	}

	void PrintClientRecord(sClient Client)
	{
		cout << "The following is the extracted client record: " << endl << endl;

		cout << left << setw(15) << "Account Number" << ": " << Client.AccountNumber << endl;
		cout << left << setw(15) << "Pin Code" << ": " << Client.PinCode << endl;
		cout << left << setw(15) << "Name" << ": " << Client.Name << endl;
		cout << left << setw(15) << "Phone" << ": " << Client.Phone << endl;
		cout << left << setw(15) << "Account Balance" << ": " << Client.AccountBalance << endl;
	}

	void AddDataLineToFile(string FileName, string stDataLine)
	{
		fstream MyFile;

		MyFile.open(FileName, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	void AddNewClinet()
	{
		sClient Client;

		Client = ReadClintData();

		AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client, "#//#"));
	}

	void AddClinet()
	{
		char AddMore = 'Y';
		sClient Client;

		do
		{
			system("cls");
			cout << "Adding New Client:\n\n";

			AddNewClinet();

			cout << "\nClient Added successfully, do you want to add more client? Y/N?" << endl;
			cin >> AddMore;
		} while (toupper(AddMore) == 'Y');
	}

	string ReadClientAccountNumber()
	{
		string AccountNumber = "";
		cout << "Please enter AccountNumber?";
		cin >> AccountNumber;
		return AccountNumber;
	}

	void PrintAllClientsData(vector <sClient> vClients)
	{
		cout << "\n" << OutPut::Taps(4) << "Clients List (" << vClients.size() << ") Client(s).";

		cout << "\n_______________________________________________________";
		cout << "_________________________________________________\n" << endl;
		cout << "| ";
		myfunc::SetWidthInCenter(15, "AccountNumber");
		cout << "| ";
		myfunc::SetWidthInCenter(10, "PinCode");
		cout << "| ";
		myfunc::SetWidthInCenter(40, "ClientName");
		cout << "| ";
		myfunc::SetWidthInCenter(12, "Phone");
		cout << "| ";
		myfunc::SetWidthInCenter(15, "Balance");
		cout << "\n_______________________________________________________";
		cout << "_________________________________________________\n" << endl;


		for (sClient Client : vClients)
		{
			PrintClientRecord(Client);
			cout << endl;
		}


		cout << "\n_______________________________________________________";
		cout << "_________________________________________________\n" << endl;
	}

	vector <sClient> LoadDataFromFiles(string FileName)
	{
		vector <sClient> vClients;
		fstream Myfile;
		Myfile.open(FileName, ios::in);
		if (Myfile.is_open())
		{
			string line;
			sClient Client;

			while (getline(Myfile, line))
			{
				Client = ConvertLineToRecord(line, "#//#");

				vClients.push_back(Client);
			}

			Myfile.close();
		}

		return vClients;
	}

	bool FindClientByAccountNumber(vector <sClient> vClients, sClient& Client, string AccountNumber)
	{
		for (int i = 0; i < vClients.size(); i++)
		{
			if (AccountNumber == vClients[i].AccountNumber)
			{
				Client = vClients[i];
				return true;
			}
		}

		return false;
	}

	void SaveClientsDataToFile(string FileName, vector <sClient> vClients)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::out);

		if (MyFile.is_open())
		{
			for (sClient C : vClients)
			{
				string DataLine = ConvertRecordToLine(C, "#//#");
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}

	void DeleteClientFromFile(vector <sClient>& vClient, string AccountNumber)
	{
		for (int i = 0; i < vClient.size(); i++)
		{
			if (vClient[i].AccountNumber == AccountNumber)
			{
				vClient.erase(vClient.begin() + i);
				break;
			}
		}

		SaveClientsDataToFile(ClientFileName, vClient);
	}

	void DeleteClientDataByAccountNumber(vector <sClient>& vClients, string AccountNumber)
	{
		sClient stClient;
		char Answer = 'n';

		if (FindClientByAccountNumber(vClients, stClient, AccountNumber))
		{
			PrintClientRecord(stClient);
			cout << "Are you sure do you want to delete? Y/N?";
			cin >> Answer;

			if ('Y' == toupper(Answer))
			{
				DeleteClientFromFile(vClients, AccountNumber);
				cout << "Delete successfully." << endl;
			}
		}
		else
		{
			cout << "Client With Account Number (" << AccountNumber << ") Not Found!" << endl;
		}
	}

	sClient ChangeClientRecord(string AccountNumber)
	{
		sClient Client;

		Client.AccountNumber = AccountNumber;

		cout << "enter Pincode? ";
		getline(cin >> ws, Client.PinCode);

		cout << "enter Name?";
		getline(cin, Client.Name);

		cout << "enter phone?";
		getline(cin, Client.Phone);

		cout << "enter Accountbalance?";
		cin >> Client.AccountBalance;

		return Client;
	}

	void UpdateClientDataByAccountNumber(vector <sClient>& vClients, string AccountNumber)
	{
		sClient stClient;
		char Answer = 'n';

		if (FindClientByAccountNumber(vClients, stClient, AccountNumber))
		{
			PrintClientRecord(stClient);
			cout << "Are you sure do you want to Update? Y/N?";
			cin >> Answer;

			if ('Y' == toupper(Answer))
			{
				for (sClient& C : vClients)
				{
					if (C.AccountNumber == AccountNumber)
					{
						cout << endl;
						C = ChangeClientRecord(AccountNumber);
						cout << "\nClient Update Successfully." << endl;
						break;
					}
				}

				SaveClientsDataToFile(ClientFileName, vClients);
			}
		}
		else
		{
			cout << "Client With Account Number (" << AccountNumber << ") Not Found!" << endl;
		}
	}


}

