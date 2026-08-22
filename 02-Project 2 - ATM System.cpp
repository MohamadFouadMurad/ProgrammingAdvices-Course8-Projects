#include <iostream>
#include <string>
#include <cctype>
#include "MyFunction.h"
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace myfunc;
const string ClientsFileName = "Client.txt";

struct sClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	int AccountBalance = 0;
};

enum enAtmMainMenueOption
{
	eQuickWithDraw = 1,
	eNormalWithDraw = 2,
	eDeposit = 3,
	eCheckBalance = 4,
	eLogout = 5
};


sClient CurrentClient;

void ShowATmMenueScreen();
void GoBackToAtmMainMenue();
void Login();

enAtmMainMenueOption ReadAtmMainMenueScreen()
{
	short Number = 0;

	do
	{
		cout << "Chooce What do You Want To Do? [1 to 5]?";
		cin >> Number;
	} while (Number < 1 || Number > 5);

	return enAtmMainMenueOption(Number);
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
		vString.push_back(S1);
	}

	return vString;
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

	vector <string> vClientData = SplitString(stLine, Seperator);

	sClient Client;

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stoi(vClientData[4]);

	return Client;

}

vector <sClient> LoadDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream Myfile;

	Myfile.open(FileName, ios::in);

	if (!Myfile.is_open())
	{
		cout << "Error: File Client.txt not found!\n";
	}

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

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "Please enter AccountNumber?";
	cin >> AccountNumber;
	return AccountNumber;
}

bool FindClientByAccountNumberAndPincode( sClient& Client, string AccountNumber,string PinCode)
{
	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);

	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccountNumber == AccountNumber && vClients[i].PinCode == PinCode)
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
		for (sClient& C : vClients)
		{
			string DataLine = ConvertRecordToLine(C, "#//#");
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
}

void ShowQuickWithdrawScreen()
{
	
	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);


	system("cls");

	int WithDrawOption = 0;
	int WithDrawAmount = 0;

	cout << "----------------------------------------" << endl;
	cout << "          Quick Withdraw Screen         " << endl;
	cout << "----------------------------------------" << endl;
	cout << "      [1] 20              [2] 50        " << endl;
	cout << "      [3] 100             [4] 200       " << endl;
	cout << "      [5] 400             [6] 600       " << endl;
	cout << "      [7] 800             [8] 1000      " << endl;
	cout << "      [9] Exit " << endl;
	cout << "----------------------------------------" << endl;
	cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
	cout << "Choose what to WithDraw from[1] to [8] ?";
	cin >> WithDrawOption;


	WithDrawAmount = (WithDrawOption == 1) ? 20 : (WithDrawOption == 2) ? 50 : (WithDrawOption == 3) ? 100 : (WithDrawOption == 4) ? 200 : (WithDrawOption == 5) ? 400 : (WithDrawOption == 6) ? 600 : (WithDrawOption == 7) ? 800 : (WithDrawOption == 8) ? 1000 : 0;

	if (WithDrawOption == 9)
	{
		system("cls");
		ShowATmMenueScreen();
		return;
	}


	char Answer = 'n';

	if (WithDrawAmount > CurrentClient.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press Anykey to continue...";
		system("pause>0");
		ShowQuickWithdrawScreen();
		return;
	}

	cout << "\nAre you sure you want perform this transaction? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (sClient & c : vClients)
		{
			if (c.AccountNumber == CurrentClient.AccountNumber)
			{
				c.AccountBalance -= WithDrawAmount;
				CurrentClient.AccountBalance = c.AccountBalance;
				break;
			}
		}

		cout << "\n\nDone Successfully, the New Balance is : " << CurrentClient.AccountBalance << endl;

		SaveClientsDataToFile(ClientsFileName, vClients);
	}
	 
}

void ShowNormalWithDrawScreen()
{
	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);


	system("cls");

	cout << "----------------------------------------" << endl;
	cout << "         Normal WithDraw Screen         " << endl;
	cout << "----------------------------------------" << endl;

	int WithDrawAmount = 0;

	cout << "\nEnter an amount Multiple of 5`s ?";
	cin >> WithDrawAmount;

	while (WithDrawAmount % 5 != 0)
	{
		cout << "\nEnter an amount Multiple of 5`s ?";
		cin >> WithDrawAmount;
	}

	char Answer = 'n';


	if (WithDrawAmount > CurrentClient.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press Anykey to continue...";
		system("pause>0");
		ShowNormalWithDrawScreen();
		return;
	}


	cout << "\nAre you sure you want perform this transaction? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (sClient& c : vClients)
		{
			if (c.AccountNumber == CurrentClient.AccountNumber)
			{
				c.AccountBalance -= WithDrawAmount;
				CurrentClient.AccountBalance = c.AccountBalance;
				break;
			}
		}

		cout << "\n\nDone Successfully, the New Balance is : " << CurrentClient.AccountBalance << endl;

		SaveClientsDataToFile(ClientsFileName, vClients);
	}
}

void ShowDepositScreen()
{
	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);

	system("cls");

	cout << "----------------------------------------" << endl;
	cout << "            Deposit Screen              " << endl;
	cout << "----------------------------------------" << endl;

	int DepoistAmount = 0;
	char Answer = 'n';

	cout << endl;

	cout << "\npls enter deposit amount?";
	cin >> DepoistAmount;

	cout << "\nAre you sure you want perform this transaction? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (sClient & c : vClients)
		{
			if (c.AccountNumber == CurrentClient.AccountNumber)
			{
				c.AccountBalance += DepoistAmount;
				CurrentClient.AccountBalance = c.AccountBalance;
				break;
			}
		}

		cout << "\n\nDone Successfully, the New Balance is : " << CurrentClient.AccountBalance << endl;

		SaveClientsDataToFile(ClientsFileName, vClients);
	}

}

void ShowCheckBalanceScreen()
{
	cout << "----------------------------------------" << endl;
	cout << "          Check Balance Screen          " << endl;
	cout << "----------------------------------------" << endl;

	cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
}

void PerformAtmMainMenueScreen(enAtmMainMenueOption AtmMainMenueOption)
{
	switch (AtmMainMenueOption)
	{
	case enAtmMainMenueOption::eQuickWithDraw:
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToAtmMainMenue();
		break;

	case enAtmMainMenueOption::eNormalWithDraw:
		system("cls");
		ShowNormalWithDrawScreen();
		GoBackToAtmMainMenue();
		break;

	case enAtmMainMenueOption::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToAtmMainMenue();
		break;

	case enAtmMainMenueOption::eCheckBalance:
		system("cls");
		ShowCheckBalanceScreen();
		GoBackToAtmMainMenue();
		break;

	case enAtmMainMenueOption::eLogout:
		system("cls");
		Login();
		break;

	default:
		system("cls");
		Login();
		break;
	}
}

void ShowATmMenueScreen()
{
		cout << "===========================================================" << endl;
		cout << "                 ATM Main Menue Screen                     " << endl;
		cout << "===========================================================" << endl;
		cout << "            [1] Quick Withdraw.                            " << endl;
		cout << "            [2] Normal Withdraw.                           " << endl;
		cout << "            [3] Deposit.                                   " << endl;
		cout << "            [4] Check Balance.                             " << endl;
		cout << "            [5] Logout.                                    " << endl;
		cout << "===========================================================" << endl;

		PerformAtmMainMenueScreen(ReadAtmMainMenueScreen());
}

void GoBackToAtmMainMenue()
{
	cout << "\n\n Prees any key to go back to Atm main menue...";
	system("pause>0");
	system("cls");
	ShowATmMenueScreen();
}

void Login()
{
	system("cls");

	cout << "----------------------------------------" << endl;
	cout << "             Login Screen               " << endl;
	cout << "----------------------------------------" << endl;
	
	string AccountNumber,Pincode;
	bool Again = false;

	do
	{

		cout << "pls enter AccountNumber?";
		cin >> AccountNumber;
		cout << "pls enter Pincode?";
		cin >> Pincode;
		cout << endl;

		if (FindClientByAccountNumberAndPincode(CurrentClient,AccountNumber,Pincode))
		{
			Again = true;
		}
		else
		{
			system("cls");
			cout << "----------------------------------------" << endl;
			cout << "             Login Screen               " << endl;
			cout << "----------------------------------------" << endl;

			cout << "Invalid AccountNumber/Pincode" << endl;
		}

	} while (Again == false);

	system("cls");
	ShowATmMenueScreen();
}

int main()
{
	Login();

	return 0;
}