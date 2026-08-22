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
const string UserFileName = "Users.txt";

struct sClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	int AccountBalance = 0;
};

struct sUser
{
	string UserName = "";
	string Password = "";
	int Permissions = 0;
};

enum enMainMenueOptions
{
	eClientList = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClientInfo = 4,
	eFindClient = 5,
	eTransactions = 6,
	eManageUsers = 7,
	eLogout = 8
};

enum enManageUsersMenueOptions
{
	eListUsers = 1,
	eAddNewUser = 2,
	eDeleteUser = 3,
	eUpdateUser = 4,
	eFindUser = 5,
	eMainMenueUsers = 6
};

enum enUserPermissions
{
	eAll = -1,
	pListClients = 1,
	pAddNewClient = 2,
	pDeleteClient = 4,
	pUpdateClients = 8,
	pFindClient = 16,
	pTransactions = 32,
	pManageUsers = 64
};

enum enTransactionMenue
{
	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalance = 3,
	eMainMenue = 4
};

void ShowMainMenueScreen();
void GoBackToMainMenue();
void GoBackToTransactionMenueScreen();
void ShowMangaeUsersMenueScreen();
void GoBackToManageUsersMenueScreen();
bool CheckUserPermissions(enUserPermissions Permissions);
void ShowAccessDeniedMessage();
void Login();

enMainMenueOptions ReadMainMenueScreen()
{
	short Number = 0;

	do
	{
		cout << "Chooce What do You Want To Do? [1 to 8]?";
		cin >> Number;
	} while (Number < 1 || Number > 8);

	return enMainMenueOptions(Number);
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

void PrintClientRecord(sClient Client)
{
	cout << "The following is the extracted client record: " << endl << endl;

	cout << left << setw(15) << "Account Number" << ": " << Client.AccountNumber << endl;
	cout << left << setw(15) << "Pin Code" << ": " << Client.PinCode << endl;
	cout << left << setw(15) << "Name" << ": " << Client.Name << endl;
	cout << left << setw(15) << "Phone" << ": " << Client.Phone << endl;
	cout << left << setw(15) << "Account Balance" << ": " << Client.AccountBalance << endl;
}

void PrintClientRecordinOneLine(sClient Client)
{
	cout << "| ";
	SetWidthInCenter(15, Client.AccountNumber);
	cout << "| ";
	SetWidthInCenter(10, Client.PinCode);
	cout << "| ";
	SetWidthInCenter(40, Client.Name);
	cout << "| ";
	SetWidthInCenter(12, Client.Phone);
	cout << "| ";
	SetWidthInCenter(15, to_string(Client.AccountBalance));
}

void PrintAllClientData(vector <sClient> vClients)
{
	cout << "                                      Client list (" << vClients.size() << ") Client(s)." << endl;

	cout << "\n_______________________________________________________";
	cout << "_________________________________________________\n" << endl;
	cout << "| ";
	SetWidthInCenter(15, "AccountNumber");
	cout << "| ";
	SetWidthInCenter(10, "PinCode");
	cout << "| ";
	SetWidthInCenter(40, "ClientName");
	cout << "| ";
	SetWidthInCenter(12, "Phone");
	cout << "| ";
	SetWidthInCenter(15, "Balance");
	cout << "\n_______________________________________________________";
	cout << "_________________________________________________\n" << endl;

	for (sClient Client : vClients)
	{
		PrintClientRecordinOneLine(Client);
		cout << endl;
	}


	cout << "\n_______________________________________________________";
	cout << "_________________________________________________\n" << endl;
}

void ShowAllClientsScreen()
{

	if (!CheckUserPermissions(enUserPermissions::pListClients))
	{
		ShowAccessDeniedMessage();
		return;
	}
	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);

	PrintAllClientData(vClients);
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "Please enter AccountNumber?";
	cin >> AccountNumber;
	return AccountNumber;
}

bool FindClientByAccountNumber(vector <sClient> & vClients , sClient & Client,string AccountNumber)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccountNumber == AccountNumber)
		{
			Client = vClients[i];
			return true;
		}
	}

	return false;
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

void AddDateLineTofile(string FileName, string stDataLine)
{
	fstream Myfile;

	Myfile.open(FileName, ios::out | ios::app);

	if (Myfile.is_open())
	{
		Myfile << stDataLine << endl;

		Myfile.close();
	}

}

void AddNewClient(vector <sClient> & vClient)
{
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();

	while (FindClientByAccountNumber(vClient,Client,AccountNumber))
	{
		cout << "Client With [" << AccountNumber << "] Already exists, Enter Another Account Number? ";
		cin >> AccountNumber;
	}

	Client = ChangeClientRecord(AccountNumber);
	vClient.push_back(Client);
	AddDateLineTofile(ClientsFileName, ConvertRecordToLine(Client));
}

void ShowAddNewClientScreen()
{

	if (!CheckUserPermissions(enUserPermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);


	system("cls");


	cout << "----------------------------------------" << endl;
	cout << "         Add New Clients Screen         " << endl;
	cout << "----------------------------------------" << endl;


	char AddMore = 'y';
	sClient Client;

	do
	{
		cout << "Adding New Client:\n\n";

		AddNewClient(vClients);

		cout << "\nClient Added successfully, do you want to add more client? Y/N?" << endl;
		cin >> AddMore;
		
	} while (toupper(AddMore) == 'Y');
}

void SaveClientsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (sClient & C : vClients)
		{
			string DataLine = ConvertRecordToLine(C, "#//#");
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
}

void DeleteClientFromFile(vector <sClient>& vClients)
{
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	char Sure = 'N';

	if (FindClientByAccountNumber(vClients,Client,AccountNumber))
	{
		PrintClientRecord(Client);

		cout << "Are you sure you want to delete this Client? Y/N?";
		cin >> Sure;

		if ('Y' == toupper(Sure))
		{
			for (int i = 0; i < vClients.size(); i++)
			{
				if (vClients[i].AccountNumber == AccountNumber)
				{
					vClients.erase(vClients.begin() + i);
					break;
				}
			}
			cout << "Client Deleted Successfully." << endl;

			SaveClientsDataToFile(ClientsFileName, vClients);
		}
	}
	else
	{
		cout << "Client With Account Number (" << AccountNumber << ") is NOT Found!" << endl;
	}
}

void ShowDeleteClientScreen()
{

	if (!CheckUserPermissions(enUserPermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);


	system("cls");


	cout << "----------------------------------------" << endl;
	cout << "         Delete Client Screen           " << endl;
	cout << "----------------------------------------" << endl;

	DeleteClientFromFile(vClients);
}

void ShowUpdateClientInfoScreen()
{
	if (!CheckUserPermissions(enUserPermissions::pUpdateClients))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);


	system("cls");

	cout << "----------------------------------------" << endl;
	cout << "       Update Client Info Screen        " << endl;
	cout << "----------------------------------------" << endl;


	sClient Client;
	char Answer = 'n';
	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(vClients,Client,AccountNumber))
	{
		PrintClientRecord(Client);

		cout << "Are you sure do you want to Update? Y/N?";
		cin >> Answer;

		if ('Y' == toupper(Answer))
		{
			for (sClient & C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					cout << endl;
					C = ChangeClientRecord(AccountNumber);
					cout << "\nClient Update Successfully." << endl;
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);
		}
	}
	else
	{
		cout << "Client With Account Number (" << AccountNumber << ") Not Found!" << endl;
	}
}

void ShowFindClientScreen()
{

	if (!CheckUserPermissions(enUserPermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);


	system("cls");

	cout << "----------------------------------------" << endl;
	cout << "           Find Client Screen           " << endl;
	cout << "----------------------------------------" << endl;

	sClient Client;
	char Answer = 'n';
	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(vClients, Client, AccountNumber))
	{
		PrintClientRecord(Client);
	}
	else
	{
		cout << "Client With Account Number (" << AccountNumber << ") is NOT Found!" << endl;
	}
}

enTransactionMenue ReadTransactionMenueScreen()
{
	short Number = 0;

	do
	{
		cout << "Chooce What do You Want To Do? [1 to 4]?";
		cin >> Number;
	} while (Number < 1 || Number > 4);

	return (enTransactionMenue)Number;
}

void ShowDepositScreen()
{
	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);

	system("cls");

	cout << "----------------------------------------" << endl;
	cout << "            Deposit Screen              " << endl;
	cout << "----------------------------------------" << endl;

	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	int DepoistAmount = 0;
	char Answer = 'n';

	while (!FindClientByAccountNumber(vClients, Client, AccountNumber))
	{
		cout << "Client With [" << AccountNumber << "]does not exist!" << endl << endl;
		AccountNumber = ReadClientAccountNumber();
		cout << endl;
	}

	cout << endl;

	PrintClientRecord(Client);

	cout << "\npls enter deposit amount?";
	cin >> DepoistAmount;

	cout << "\nAre you sure you want perform this transaction? Y/N?" << endl;
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (sClient& c : vClients)
		{
			if (c.AccountNumber == AccountNumber)
			{
				c.AccountBalance += DepoistAmount;
				Client.AccountBalance = c.AccountBalance;
				break;
			}
		}

		cout << "the New Balance is : " << Client.AccountBalance << endl;

		SaveClientsDataToFile(ClientsFileName, vClients);
	}

}

void ShowWithdrawScreen()
{
	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);


	system("cls");

	cout << "----------------------------------------" << endl;
	cout << "            Withdraw Screen             " << endl;
	cout << "----------------------------------------" << endl;

	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	int WithdrawAmount = 0;
	char Answer = 'n';

	while (!FindClientByAccountNumber(vClients, Client, AccountNumber))
	{
		cout << "Client With [" << AccountNumber << "]does not exist!" << endl << endl;
		AccountNumber = ReadClientAccountNumber();
		cout << endl;
	}

	cout << endl;

	PrintClientRecord(Client);

	cout << "Please enter Withdraw amount? ";
	cin >> WithdrawAmount;

	while (WithdrawAmount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> WithdrawAmount;
	}

	cout << "\nAre you sure you want perform this transaction? Y/N?" << endl;
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (sClient& c : vClients)
		{
			if (c.AccountNumber == AccountNumber)
			{
				c.AccountBalance -= WithdrawAmount;
				Client.AccountBalance = c.AccountBalance;
				break;
			}
		}

		cout << "the New Balance is : " << Client.AccountBalance << endl;

		SaveClientsDataToFile(ClientsFileName, vClients);
	}
}

void ShowTotalBalanceScreen()
{

	ShowAllClientsScreen();

	vector <sClient> vClients = LoadDataFromFile(ClientsFileName);
	int Balances = 0;

	for (sClient& C : vClients)
	{
		Balances += C.AccountBalance;
	}

	cout << "                                         Total Balances = " << Balances << endl;
}

void PerformTransactionMenueOption(enTransactionMenue TransactionMenueOption)
{
	switch (TransactionMenueOption)
	{
	case enTransactionMenue::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionMenueScreen();
		break;

	case enTransactionMenue::eWithdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionMenueScreen();
		break;

	case enTransactionMenue::eTotalBalance:
		system("cls");
		ShowTotalBalanceScreen();
		GoBackToTransactionMenueScreen();
		break;

	case enTransactionMenue::eMainMenue:
		system("cls");
		ShowMainMenueScreen();
		break;

	default:
		break;
	}
}

void ShowTransactinsMenueScreen()
{

	if (!CheckUserPermissions(enUserPermissions::pTransactions))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "===========================================================" << endl;
	cout << "                 Transactions Menue Screen                 " << endl;
	cout << "===========================================================" << endl;
	cout << "            [1] Deposit.                                   " << endl;
	cout << "            [2] WithDraw                                   " << endl;
	cout << "            [3] TotalBalance                               " << endl;
	cout << "            [4] Main Menue.                                " << endl;
	cout << "===========================================================" << endl;

	PerformTransactionMenueOption(ReadTransactionMenueScreen());
}

void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "          Program Ends :-)           \n";
	cout << "-----------------------------------\n";
}

void GoBackToMainMenue()
{
	cout << "\n\n Prees any key to go back to main menue...";
	system("pause>0");
	system("cls");
	ShowMainMenueScreen();
}

void GoBackToTransactionMenueScreen()
{
	cout << "\n\n Press any key to go back to Transactions Menue... ";
	system("pause>0");
	system("cls");
	ShowTransactinsMenueScreen();
}

// Users 

sUser CurrentUser;//global Varibale

string ConvertUsersRecordToLine(sUser User, string Seperator = "#//#")
{
	string stUSerRecord = "";

	stUSerRecord += User.UserName + Seperator;
	stUSerRecord += User.Password + Seperator;
	stUSerRecord += to_string(User.Permissions);

	return stUSerRecord;
}

sUser ConvertUsersLineToRecord(string stLine, string Seperator = "#//#")
{

	vector <string> vUserData = SplitString(stLine, Seperator);

	sUser User;

	User.UserName = vUserData[0];
	User.Password = vUserData[1];
	User.Permissions = stoi(vUserData[2]);

	return User;

}

vector <sUser> LoadDataUsersFromFile(string FileName)
{
	vector <sUser> vUsers;
	fstream Myfile;

	Myfile.open(FileName, ios::in);

	if (Myfile.is_open())
	{
		string line;
		sUser User;

		while (getline(Myfile, line))
		{
			User = ConvertUsersLineToRecord(line, "#//#");

			vUsers.push_back(User);
		}

		Myfile.close();
	}

	return vUsers;
}

void SaveUsersDataToFile(string FileName, vector <sUser> & vUsers)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (sUser& User: vUsers)
		{
			string DataLine = ConvertUsersRecordToLine(User, "#//#");
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
}

enUserPermissions ReadPermissionsToSet()
{
	char Answer = 'Y';

	cout << "\nDo You want to give full accsess? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		return enUserPermissions::eAll;
	}

	int Permissions = 0;

	cout << "\nShow Client List? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		Permissions |= enUserPermissions::pListClients;
	}

	cout << "\nAdd New Client? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		Permissions |= enUserPermissions::pAddNewClient;
	}

	cout << "\nDelete Client? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		Permissions |= enUserPermissions::pDeleteClient;
	}

	cout << "\nUpdate Client? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		Permissions |= enUserPermissions::pUpdateClients;
	}

	cout << "\nFind Client? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		Permissions |= enUserPermissions::pFindClient;
	}


	cout << "\nTransaction? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		Permissions |= enUserPermissions::pTransactions;
	}

	cout << "\nManage Users? Y/N?";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		Permissions |= enUserPermissions::pManageUsers;
	}

	return enUserPermissions(Permissions);
}

void PrintUserRecord(sUser User)
{
	cout << "The following is the extracted User record: " << endl << endl;

	cout << left << setw(15) << "User Name" << ": " << User.UserName << endl;
	cout << left << setw(15) << "Password" << ": " << User.Password << endl;
	cout << left << setw(15) << "Permissions" << ": " << User.Permissions << endl;
}

void PrintUsersRecordinOneLine(sUser User)
{
	cout << "| ";
	SetWidthInCenter(15, User.UserName);
	cout << "| ";
	SetWidthInCenter(15, User.Password);
	cout << "| ";
	SetWidthInCenter(15, to_string(User.Permissions));
}

void PrintAllUsersData(vector <sUser> & vUsers)
{
	cout << "\t\t\t\tUsers list (" << vUsers.size() << ") Users(s)." << endl;

	cout << "\n_______________________________________________________";
	cout << "_________________________________________________\n" << endl;
	cout << "| ";
	SetWidthInCenter(15, "User Name");
	cout << "| ";
	SetWidthInCenter(15, "Password");
	cout << "| ";
	SetWidthInCenter(15, "Permissions");
	cout << "\n_______________________________________________________";
	cout << "_________________________________________________\n" << endl;

	if (vUsers.size() == 0)
	{
		cout << "\t\t\t\tNo Users Available In the system!" << endl;
	}
	else
	{
		for (sUser User : vUsers)
		{
			PrintUsersRecordinOneLine(User);
			cout << endl;
		}
	}


	cout << "\n_______________________________________________________";
	cout << "_________________________________________________\n" << endl;
}

void ShowAllUsersScreen()
{
	vector <sUser> vUsers = LoadDataUsersFromFile(UserFileName);

	PrintAllUsersData(vUsers);
}

string ReadUserName()
{
	string UserName = "";
	cout << "Please enter User Name?";
	cin >> UserName;
	return UserName;
}

bool FindUserByUserName(vector <sUser>& vUsers, sUser& User, string UserName)
{
	for (int i = 0; i < vUsers.size(); i++)
	{
		if (vUsers[i].UserName == UserName)
		{
			User = vUsers[i];
			return true;
		}
	}

	return false;
}

sUser ChangeUserRecord(string UserName)
{
	sUser User;

	User.UserName = UserName;

	cout << "enter Password? ";
	getline(cin >> ws, User.Password);

	User.Permissions = ReadPermissionsToSet();

	return User;
}

void AddNewUser(vector <sUser>& vUser)
{
	sUser User;
	string UserName = ReadUserName();

	while (FindUserByUserName(vUser, User, UserName))
	{
		cout << "\nUser With [" << UserName << "] Already exists, Enter Another User Name? ";
		cin >> UserName;
	}

	User = ChangeUserRecord(UserName);
	vUser.push_back(User);
	AddDateLineTofile(UserFileName, ConvertUsersRecordToLine(User));
}

void ShowAddNewUserScreen()
{
	vector <sUser> vUsers = LoadDataUsersFromFile(UserFileName);


	system("cls");


	cout << "----------------------------------------" << endl;
	cout << "         Add New Users Screen         " << endl;
	cout << "----------------------------------------" << endl;


	char AddMore = 'y';
	sUser User;

	do
	{
		cout << "Adding New User:\n\n";

		AddNewUser(vUsers);

		cout << "\nUser Added successfully, do you want to add more User? Y/N?";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

void DeleteUserFromFile(vector <sUser>& vUsers)
{
	sUser User;
	string UserName = ReadUserName();
	char Sure = 'N';

	if (UserName == "Admin")
	{
		cout << "\nYou Cannot Delete This user";
	}
	else
	{
		if (FindUserByUserName(vUsers, User, UserName))
		{
			PrintUserRecord(User);

			cout << "Are you sure you want to delete this User? Y/N?";
			cin >> Sure;

			if ('Y' == toupper(Sure))
			{
				for (int i = 0; i < vUsers.size(); i++)
				{
					if (vUsers[i].UserName == UserName)
					{
						vUsers.erase(vUsers.begin() + i);
						break;
					}
				}
				cout << "User Deleted Successfully." << endl;

				SaveUsersDataToFile(UserFileName, vUsers);
			}
		}
		else
		{
			cout << "User With User Name (" << UserName << ") is NOT Found!" << endl;
		}
	}
}

void ShowDeleteUserScreen()
{
	vector <sUser> vUsers = LoadDataUsersFromFile(UserFileName);


	system("cls");


	cout << "----------------------------------------" << endl;
	cout << "         Delete Users Screen            " << endl;
	cout << "----------------------------------------" << endl;

	DeleteUserFromFile(vUsers);
}

void ShowUpdateUserInfoScreen()
{
	vector <sUser> vUsers = LoadDataUsersFromFile(UserFileName);


	system("cls");

	cout << "----------------------------------------" << endl;
	cout << "       Update User Info Screen        " << endl;
	cout << "----------------------------------------" << endl;


	sUser User;
	char Answer = 'n';
	string UserName = ReadUserName();

	if (FindUserByUserName(vUsers,User, UserName))
	{
		PrintUserRecord(User);

		cout << "Are you sure do you want to Update? Y/N?";
		cin >> Answer;

		if ('Y' == toupper(Answer))
		{
			for (sUser & User : vUsers)
			{
				if (User.UserName == UserName)
				{
					cout << endl;
					User = ChangeUserRecord(UserName);
					cout << "\nUser Update Successfully." << endl;
					break;
				}
			}

			SaveUsersDataToFile(UserFileName, vUsers);
		}
	}
	else
	{
		cout << "User With Account Number (" << UserName << ") Not Found!" << endl;
	}
}

void ShowFindUserScreen()
{
	vector <sUser> vUsers = LoadDataUsersFromFile(UserFileName);


	system("cls");

	cout << "----------------------------------------" << endl;
	cout << "           Find User Screen           " << endl;
	cout << "----------------------------------------" << endl;

	sUser User;
	char Answer = 'n';
	string UserName = ReadUserName();

	if (FindUserByUserName(vUsers, User, UserName))
	{
		PrintUserRecord(User);
	}
	else
	{
		cout << "User With Account Number (" << UserName << ") is NOT Found!" << endl;
	}
}

void PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eClientList:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eUpdateClientInfo:
		system("cls");
		ShowUpdateClientInfoScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eTransactions:
		system("cls");
		ShowTransactinsMenueScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eManageUsers:
		system("cls");
		ShowMangaeUsersMenueScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eLogout:
		Login();
		break;

	default:
		break;

	}
}

void ShowMainMenueScreen()
{
	cout << "===========================================================" << endl;
	cout << "                       Main Menue Screen                   " << endl;
	cout << "===========================================================" << endl;
	cout << "            [1] Show Client List.                          " << endl;
	cout << "            [2] Add New Client.                            " << endl;
	cout << "            [3] Delete Client.                             " << endl;
	cout << "            [4] Update Client Info.                        " << endl;
	cout << "            [5] Find Client.                               " << endl;
	cout << "            [6] Transactions.                              " << endl;
	cout << "            [7] Manage Users.                              " << endl;
	cout << "            [8] Logout.                                      " << endl;
	cout << "===========================================================" << endl;

	PerformMainMenueOption(ReadMainMenueScreen());

}

enManageUsersMenueOptions ReadManageUsersScreen()
{
	int Number = 0;;

	do
	{
		cout << "Choose What do you want to do? [1 to 6]?";
		cin >> Number;
	} while (Number < 1 || Number > 6);

	return enManageUsersMenueOptions(Number);
}

void PerformMangeUsersMenueScreen(enManageUsersMenueOptions ManageUsersMenueOption)
{
	switch (ManageUsersMenueOption)
	{
		case enManageUsersMenueOptions::eListUsers:
		system("cls");
		ShowAllUsersScreen();
		GoBackToManageUsersMenueScreen();
		break;

	case  enManageUsersMenueOptions::eAddNewUser:
		system("cls");
		ShowAddNewUserScreen();
		GoBackToManageUsersMenueScreen();
		break;

	case  enManageUsersMenueOptions::eDeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUsersMenueScreen();
		break;

	case  enManageUsersMenueOptions::eUpdateUser:
		system("cls");
		ShowUpdateUserInfoScreen();
		GoBackToManageUsersMenueScreen();
		break;

	case  enManageUsersMenueOptions::eFindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackToManageUsersMenueScreen();
		break;

	case enManageUsersMenueOptions::eMainMenueUsers:
		system("cls");
		ShowMainMenueScreen();
		break;

	default:
		system("cls");
		ShowMainMenueScreen();
	}
}

void ShowMangaeUsersMenueScreen()
{

	if (!CheckUserPermissions(enUserPermissions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "===========================================================" << endl;
	cout << "                  Manage Users Menue Screen                " << endl;
	cout << "===========================================================" << endl;
	cout << "            [1] List Users.                                " << endl;
	cout << "            [2] Add New User.                              " << endl;
	cout << "            [3] Delete User.                               " << endl;
	cout << "            [4] Update User.                               " << endl;
	cout << "            [5] Find User.                               " << endl;
	cout << "            [6] Main Menue.                                    " << endl;
	cout << "===========================================================" << endl;

	PerformMangeUsersMenueScreen(ReadManageUsersScreen());
}

void GoBackToManageUsersMenueScreen()
{
	cout << "\n\n Press any key to go back to Manage Users Menue... ";
	system("pause>0");
	system("cls");
	ShowMangaeUsersMenueScreen();
}

bool FindUserByUserNameAndPassword(sUser& User, string UserName ,string Password)
{
	vector <sUser> vUsers = LoadDataUsersFromFile(UserFileName);

	for (int i = 0; i < vUsers.size(); i++)
	{
		if (vUsers[i].UserName == UserName && vUsers[i].Password == Password)
		{
			User = vUsers[i];
			return true;
		}
	}

	return false;
}

bool CheckUserPermissions(enUserPermissions Permissions)
{
	if (CurrentUser.Permissions == enUserPermissions::eAll)
	{
		return true;
	}
	else if (Permissions == (CurrentUser.Permissions & Permissions))
	{
		return true;
	}

	return false;
}

void ShowAccessDeniedMessage()
{
	cout << "-----------------------------------" << endl;
	cout << "Access Denied, " << endl;
	cout << "You dont Have Permission To Do this," << endl;
	cout << "Please Conact Your Admin." << endl;
	cout << "-----------------------------------" << endl;
}

void Login()
{
	system("cls");

	cout << "----------------------------------------" << endl;
	cout << "             Login Screen               " << endl;
	cout << "----------------------------------------" << endl;



	string Password, UserName;
	bool Again = false;

	do
	{

		cout << "pls enter UserName?";
		cin >> UserName;
		cout << "pls enter Password?";
		cin >> Password;
		cout << endl;

		if (FindUserByUserNameAndPassword(CurrentUser, UserName, Password))
		{
			Again = true;
		}
		else
		{
			system("cls");
			cout << "----------------------------------------" << endl;
			cout << "             Login Screen               " << endl;
			cout << "----------------------------------------" << endl;

			cout << "Invalid UserName/Password" << endl;
		}

	} while (Again == false);

	system("cls");
	ShowMainMenueScreen();
}

int main()
{
	Login();
    return 0;
}