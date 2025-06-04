#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
#include <fstream>
using namespace std;

const string Filename = "Record.txt";
const string UsersFile = "Users.txt";

enum enChoise { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transaction = 6, Manage = 7 };
enum enPermisson { Display = 1, P_Add = 2, P_Delete = 4, P_Update = 8, P_Find = 16, P_Trancaction = 32, P_Manage = 64 };
enum enUser { ShowUser = 1, UserAdd = 2, UserDelete = 3, UserUpdate = 4, UserFind = 5 };
enum enTchoise { Deposit = 1, Withdraw = 2, TotalBalance = 3 };


struct stClints
{
	string AccountNumber;
	string Name;
	string PinCode;
	string Phone;
	double Balance = 0.0;
	bool MarkForDelete = false;
};
struct stUsers
{
	string UserName;
	string Password;
	int Permission = 0;
	bool MarkToDelete = false;
};

stUsers CurrentUser;

struct Permissons
{
	short ListUsers = 1;
	short AddNewUse = 2;
	short DeleteUser = 4;
	short UpdateUser = 8;
	short FindUser = 16;
	short Transaction = 32;
	short ManageUsers = 64;
};
string ConvertRecordToString(stClints Clint, string Sprater = "#//#")
{
	string R = "";
	R += Clint.AccountNumber + Sprater;
	R += Clint.Name + Sprater;
	R += Clint.PinCode + Sprater;
	R += Clint.Phone + Sprater;
	R += to_string(Clint.Balance);
	return R;
}
vector <string> ConvertStringToVector(string line, string delm)
{
	vector<string> vClint;
	short pos = 0;
	string sWord; // define a string variable  

	// use find() function to get the position of the delimiters  
	while ((pos = line.find(delm)) != std::string::npos)
	{
		sWord = line.substr(0, pos); // store the word   
		if (sWord != "")
		{
			vClint.push_back(sWord);
		}

		line.erase(0, pos + delm.length());  /* erase() until positon and move to next word. */
	}

	if (line != "")
	{
		vClint.push_back(line); // it adds last word of the string.
	}

	return vClint;
}
stClints ConvertVectorToRecord(string line, string Sperator = "#//#")
{
	vector <string> vClint;
	stClints Clint;
	vClint = ConvertStringToVector(line, Sperator);
	Clint.AccountNumber = vClint[0];
	Clint.Name = vClint[1];
	Clint.PinCode = vClint[2];
	Clint.Phone = vClint[3];
	Clint.Balance = stod(vClint[4]);

	return Clint;
}
vector<stClints> ConvertRecordInFileVector(string Filename)
{
	vector<stClints> vClint;
	fstream ClintsRecord;
	ClintsRecord.open(Filename, ios::in);
	if (ClintsRecord.is_open())
	{
		string line;
		stClints Clint;
		while (getline(ClintsRecord, line))
		{
			Clint = ConvertVectorToRecord(line);
			vClint.push_back(Clint);

		}
		ClintsRecord.close();
	}
	return vClint;
}
void SaveRecordToFile(string Filename, string line)
{

	fstream ClintsRecord;
	ClintsRecord.open(Filename, ios::out | ios::app);
	if (ClintsRecord.is_open())
	{
		ClintsRecord << line << endl;
		ClintsRecord.close();
	}
}
void SaveVectorToFile(string Filename, vector <stClints>& vClint)
{
	fstream ClintsRecord;
	ClintsRecord.open(Filename, ios::out);
	if (ClintsRecord.is_open())
	{
		string line;
		for (stClints& C : vClint)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				line = ConvertRecordToString(C);
				ClintsRecord << line << endl;
			}
		}
		ClintsRecord.close();
	}
}
bool CheckIfAccountExist(string AccountToCheck, string Filename)
{
	vector <stClints> vClients;
	fstream MyFile;
	MyFile.open(Filename, ios::in);//read Mode

	if (MyFile.is_open())
	{
		string Line;
		stClints Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertVectorToRecord(Line);
			if (Client.AccountNumber == AccountToCheck)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}

		MyFile.close();

	}
	return false;
}
void PrintClintInfo(stClints Clint)
{
	system("cls");

	cout << "________________________________________________________________________________________________\n\n";
	cout << "| " << setw(12) << left << "Account Number";
	cout << "| " << setw(9) << left << "Pin Code";
	cout << "| " << setw(40) << left << "Clint Name";
	cout << "| " << setw(12) << left << "Phone Number";
	cout << "| " << setw(10) << left << "Balance";
	cout << "\n________________________________________________________________________________________________\n\n";

	cout << "| " << setw(14) << left << Clint.AccountNumber;
	cout << "| " << setw(9) << left << Clint.PinCode;
	cout << "| " << setw(40) << left << Clint.Name;
	cout << "| " << setw(12) << left << Clint.Phone;
	cout << "| " << setw(10) << left << Clint.Balance;
	cout << "\n________________________________________________________________________________________________\n\n";
}
void PrintClint(stClints Clint)
{

	cout << "| " << setw(14) << left << Clint.AccountNumber;
	cout << "| " << setw(9) << left << Clint.PinCode;
	cout << "| " << setw(40) << left << Clint.Name;
	cout << "| " << setw(12) << left << Clint.Phone;
	cout << "| " << setw(10) << left << Clint.Balance;
}
bool HasAPermissonse(short Per, stUsers& User);
void PrintMainMenueScreen()
{
	system("cls");

	cout << "\n\n===========================================\n";
	cout << setw(9) << "" << "[1] Show Clint List\n";
	cout << setw(9) << "" << "[2] Add New Clint\n";
	cout << setw(9) << "" << "[3] Delete Clint\n";
	cout << setw(9) << "" << "[4] Update Clint Info\n";
	cout << setw(9) << "" << "[5] Find Clint\n";
	cout << setw(9) << "" << "[6] Transactions\n";
	cout << setw(9) << "" << "[7] Manage Users\n";
	cout << setw(9) << "" << "[8] Logout\n";
	cout << "===========================================\n\n";
}
void PrintAddNewClintScreen()
{
	system("cls");

	cout << "------------------------------------------\n";
	cout << setw(10) << "" << "Add New Clint\n";
	cout << "------------------------------------------\n";
}
void PrintAddNewUserScreen()
{
	system("cls");

	cout << "------------------------------------------\n";
	cout << setw(10) << "" << "Add New User\n";
	cout << "------------------------------------------\n";
}
void PrintUpdateClintScreen()
{
	system("cls");

	cout << "------------------------------------------\n";
	cout << setw(10) << "" << "Update Clint\n";
	cout << "------------------------------------------\n";
}
void PrintUpdateUserScreen()
{
	system("cls");

	cout << "------------------------------------------\n";
	cout << setw(10) << "" << "Update User\n";
	cout << "------------------------------------------\n";
}
void PrintAccountScreen()
{
	system("cls");

	cout << "------------------------------------------\n";
	cout << setw(10) << "" << "Find Account\n";
	cout << "------------------------------------------\n";
}
void PrintDeleteAccountScreen()
{
	system("cls");

	cout << "------------------------------------------\n";
	cout << setw(10) << "" << "Delete Account\n";
	cout << "------------------------------------------\n";
}
void PrintDeleteUserScreen()
{
	system("cls");

	cout << "------------------------------------------\n";
	cout << setw(10) << "" << "Delete User\n";
	cout << "------------------------------------------\n";
}
void PrintProgramEndScreen()
{
	system("cls");

	cout << "----------------------------------\n";
	cout << setw(10) << "" << "Log in :)\n";
	cout << "----------------------------------\n";

}
void PrintLoginScreen()
{
	system("cls");

	cout << "----------------------------------\n";
	cout << setw(10) << "" << "Login Screen\n";
	cout << "----------------------------------\n";

}
void PrintPermissionDeniedScreen()
{
	system("cls");

	cout << "------------------------------------\n";
	cout << "Permission Denied,\nYou Dont Have Permission To Do this,\nPlease Contact Your Admin.\n";
	cout << "------------------------------------\n";

}
void PrintTransactionsMenueScreen()
{
	system("cls");

	cout << "\n\n===========================================\n";
	cout << "            Transactions Menue Screen            ";
	cout << "\n===========================================\n";
	cout << setw(9) << "" << "[1] Deposit\n";
	cout << setw(9) << "" << "[2] Withdraw\n";
	cout << setw(9) << "" << "[3] Total Balance\n";
	cout << setw(9) << "" << "[4] Main Menue\n";
	cout << "===========================================\n\n";
}
void PrintManageUsersScreen()
{
	system("cls");

	cout << "\n\n===========================================\n";
	cout << "            Manage Users Menue Screen            ";
	cout << "\n===========================================\n";
	cout << setw(9) << "" << "[1] List Users\n";
	cout << setw(9) << "" << "[2] Add New User\n";
	cout << setw(9) << "" << "[3] Delete User\n";
	cout << setw(9) << "" << "[4] Update User\n";
	cout << setw(9) << "" << "[5] Find User\n";
	cout << setw(9) << "" << "[6] Main Menue\n";
	cout << "===========================================\n\n";
}
void PrintDepositScreen()
{
	system("cls");

	cout << "------------------------------------------\n";
	cout << setw(10) << "" << "Deposit Screen\n";
	cout << "------------------------------------------\n";
}
void PrintWithdrawScreen()
{
	system("cls");

	cout << "------------------------------------------\n";
	cout << setw(10) << "" << "Withdraw Screen\n";
	cout << "------------------------------------------\n";
}
void PrintTotalBalance()
{
	system("cls");

	vector <stClints> vClint;
	vClint = ConvertRecordInFileVector(Filename);
	double Count = 0;
	cout << "\n\n" << setw(40) << " " << "Balance Of (" <<vClint.size()<< ") Clint(s)\n\n";
	cout << "________________________________________________________________________________________________\n\n";
	cout << "| " << setw(12) << left << "Account Number";
	cout << "| " << setw(40) << left << "Clint Name";
	cout << "| " << setw(10) << left << "Balance";
	cout << "\n________________________________________________________________________________________________\n\n";


	for (stClints& C : vClint)
	{
		cout << "| " << setw(14) << left << C.AccountNumber;
		cout << "| " << setw(40) << left << C.Name;
		cout << "| " << setw(10) << left << C.Balance;
		cout << endl;
		Count += C.Balance;
	}

	cout << "\n________________________________________________________________________________________________\n";
	cout << setw(40) << " " << "Total Balance = " << Count << endl;

}
void MainMenue();
void TransactionsMenue();
void ManageUsersMenue();
void GoBackToMainMenue()
{
	cout << "Press Any Key to go back ";
	system("pause>0");
	MainMenue();

}
void GoBackToManegeMenue()
{
	cout << "Press Any Key to go back ";
	system("pause>0");
	ManageUsersMenue();

}
void GoBackToTransactions()
{
	cout << "Press Any Key to go back ";
	system("pause>0");
	TransactionsMenue();

}
short ReadMainMenueOption()
{
	short C;
	cout << "What you want to do [1 to 8] :";
	cin >> C;
	return C;
}
void PrintClintList()
{
	if (!HasAPermissonse(enPermisson::Display, CurrentUser))
	{
		PrintPermissionDeniedScreen();
		GoBackToMainMenue();
	}
	system("cls");
	vector <stClints> vClint;
	vClint = ConvertRecordInFileVector(Filename);

	cout << "\n\n" << setw(40) << " " << "Clint List (" <<vClint.size()<< ") Clint(s)\n\n";
	cout << "________________________________________________________________________________________________\n\n";
	cout << "| " << setw(12) << left << "Account Number";
	cout << "|" << setw(10) << left << "Pin Code";
	cout << "| " << setw(40) << left << "Clint Name";
	cout << "| " << setw(12) << left << "Phone Number";
	cout << "| " << setw(10) << left << "Balance";
	cout << "\n________________________________________________________________________________________________\n\n";

	for (stClints C : vClint)
	{
		PrintClint(C);
		cout << endl;
	}

	cout << "\n________________________________________________________________________________________________\n\n";
}
void AddNewClint()
{
	if (!HasAPermissonse(enPermisson::P_Add, CurrentUser))
	{
		PrintPermissionDeniedScreen();
		GoBackToMainMenue();
	}

	PrintAddNewClintScreen();

	char Answer = 'y';
	stClints Clint;
	do
	{
		do
		{
			cout << "Enter Account Number :\n";
			getline(cin >> ws, Clint.AccountNumber);
			if (CheckIfAccountExist(Clint.AccountNumber, Filename))
				cout << "The Account Exsist :(\n";
		} while (CheckIfAccountExist(Clint.AccountNumber, Filename));
		cout << "Enter Account Name :\n";
		getline(cin, Clint.Name);
		cout << "Enter Pin Code :\n";
		getline(cin, Clint.PinCode);
		cout << "Enter Phone Number :\n";
		getline(cin, Clint.Phone);
		cout << "Enter Balance :\n";
		cin >> Clint.Balance;

		SaveRecordToFile(Filename, ConvertRecordToString(Clint));
		cout << "The Clint Added successfully :)\n";
		cout << "\nDo you want gto Add anouther clint ? y/n\n";
		cin >> Answer;
	} while (Answer == 'y' || Answer == 'Y');
}
string AccountToSearch()
{
	string AccountToSearch;
	cout << "Enter Account Number :\n";
	getline(cin >> ws, AccountToSearch);
	return AccountToSearch;
}
bool SearchForAccount(string AccountToSearch, vector <stClints>& vClint, stClints& Clint)
{
	for (stClints& C : vClint)
	{
		if (AccountToSearch == C.AccountNumber)
		{
			Clint = C;
			return true;
		}
	}
	return false;
}
void FindClint()
{
	if (!HasAPermissonse(enPermisson::P_Find, CurrentUser))
	{
		PrintPermissionDeniedScreen();
		GoBackToMainMenue();
	}

	PrintUpdateClintScreen();

	vector <stClints> vClint;
	vClint = ConvertRecordInFileVector(Filename);
	stClints Clint;
	if (SearchForAccount(AccountToSearch(), vClint, Clint))
	{
		PrintClintInfo(Clint);
	}
	else
		cout << "Account not exsist :(\n";
}
stClints ChangeRecored(string AccountToUpdate, vector <stClints>& vClint)
{
	stClints Clint;
	Clint.AccountNumber = AccountToUpdate;
	cout << "Enter Account Name :\n";
	getline(cin >> ws, Clint.Name);
	cout << "Enter Pin Code :\n";
	getline(cin, Clint.PinCode);
	cout << "Enter Phone Number :\n";
	getline(cin, Clint.Phone);
	cout << "Enter Balance :\n";
	cin >> Clint.Balance;
	return Clint;
}
bool MarkAccountToDelete(string AccountTosearch, vector <stClints>& vClint)
{
	for (stClints& C : vClint)
	{
		if (AccountTosearch == C.AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
void DeleteAccount()
{
	if (!HasAPermissonse(enPermisson::P_Delete, CurrentUser))
	{
		PrintPermissionDeniedScreen();
		GoBackToMainMenue();
	}

	PrintDeleteAccountScreen();

	string accountToSearch = AccountToSearch();
	vector <stClints> vClint;
	vClint = ConvertRecordInFileVector(Filename);
	stClints Clint;
	char Answer;
	if (SearchForAccount(accountToSearch, vClint, Clint))
	{
		PrintClintInfo(Clint);
		cout << "\n\nAre you sure you want to delete the Account? y/n\n";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkAccountToDelete(accountToSearch, vClint);
			SaveVectorToFile(Filename, vClint);
			vClint = ConvertRecordInFileVector(Filename);
			cout << "The Account has deleted successfully :)\n";
		}
	}
	else
		cout << "Account not exsist :(\n";

}
void UpdateAccount()
{
	if (!HasAPermissonse(enPermisson::P_Update, CurrentUser))
	{
		PrintPermissionDeniedScreen();
		GoBackToMainMenue();
	}

	PrintUpdateClintScreen();

	string AccountToUpdate = AccountToSearch();
	vector <stClints> vClint;
	vClint = ConvertRecordInFileVector(Filename);
	stClints Clint;
	char Answer;
	if (SearchForAccount(AccountToUpdate, vClint, Clint))
	{
		PrintClintInfo(Clint);
		cout << "\n\nAre you sure you want to Update the Account? y/n\n";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClints& C : vClint)
			{
				if (C.AccountNumber == AccountToUpdate)
				{
					C = ChangeRecored(AccountToUpdate, vClint);
				}
			}
			SaveVectorToFile(Filename, vClint);
			cout << "The Account has Updated successfully :)\n";
		}
	}
	else
		cout << "Account not exsist :(\n";

}
void DepositToAccount()
{

	PrintDeleteAccountScreen();
	string AccountToDeposit = AccountToSearch();
	vector <stClints> vClint;
	vClint = ConvertRecordInFileVector(Filename);

	stClints Clint;
	char Answer;
	if (SearchForAccount(AccountToDeposit, vClint, Clint))
	{
		double DAmount = 0;
		PrintClintInfo(Clint);
		cout << "\n\nEnter the Amount you want to deposit : ";
		cin >> DAmount;
		cout << "\n\nAre you sure you want to Deposit to this Account? y/n\n";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClints& C : vClint)
			{
				if (C.AccountNumber == AccountToDeposit)
				{
					C.Balance += DAmount;
				}
			}
			SaveVectorToFile(Filename, vClint);
			cout << "The Account has been Deposit successfully :)\n";
		}
	}
	else
		cout << "Account not exsist :(\n";

}
void WithdrawFromAccount()
{

	PrintWithdrawScreen();
	string AccountToWithdraw = AccountToSearch();
	vector <stClints> vClint;
	vClint = ConvertRecordInFileVector(Filename);

	stClints Clint;
	char Answer;
	if (SearchForAccount(AccountToWithdraw, vClint, Clint))
	{
		double WAmount = 0;
		PrintClintInfo(Clint);
		do
		{
			cout << "Enter the Amount you want to Withdraw : \n";
			cin >> WAmount;
			if (WAmount > Clint.Balance)
				cout << "\nAmount Exceeds the balance , you cant withdraw up to : " << Clint.Balance << endl;
		} while (WAmount > Clint.Balance);

		cout << "\n\nAre you sure you want to withdraw from this Account? y/n\n";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClints& C : vClint)
			{
				if (C.AccountNumber == AccountToWithdraw)
				{
					C.Balance -= WAmount;
				}
			}
			SaveVectorToFile(Filename, vClint);
			vClint = ConvertRecordInFileVector(Filename);
			cout << "The withdraw has been done successfully :)\n";
		}
	}
	else
		cout << "Account not exsist :(\n";

}
stUsers ConvertVectorToUsers(string line, string Sperator = "#//#")
{
	vector <string> vUser;
	stUsers User;
	vUser = ConvertStringToVector(line, Sperator);
	User.UserName = vUser[0];
	User.Password = vUser[1];
	User.Permission = stoi(vUser[2]);

	return User;
}
vector<stUsers> ConvertUsersInFileVector(string Filename)
{
	vector<stUsers> vUser;
	fstream ClintsRecord;
	ClintsRecord.open(Filename, ios::in);
	if (ClintsRecord.is_open())
	{
		string line;
		stUsers User;
		while (getline(ClintsRecord, line))
		{
			User = ConvertVectorToUsers(line);
			vUser.push_back(User);

		}
		ClintsRecord.close();
	}
	return vUser;
}
bool CheckIfUsersExist(string UserToCheck, string Filename)
{
	vector <stUsers> vUser;
	fstream MyFile;
	MyFile.open(Filename, ios::in);//read Mode

	if (MyFile.is_open())
	{
		string Line;
		stUsers User;

		while (getline(MyFile, Line))
		{
			User = ConvertVectorToUsers(Line);
			if (User.UserName == UserToCheck)
			{
				MyFile.close();
				return true;
			}
			vUser.push_back(User);
		}

		MyFile.close();

	}
	return false;
}
string ConvertUsersToString(stUsers User, string Sprater = "#//#")
{
	string R = "";
	R += User.UserName + Sprater;
	R += User.Password + Sprater;
	R += to_string(User.Permission);
	return R;
}
void SaveVectorToFile(string Filename, vector <stUsers>& vUser)
{
	fstream UsersRecord;
	UsersRecord.open(Filename, ios::out);
	if (UsersRecord.is_open())
	{
		string line;
		for (stUsers& U : vUser)
		{
			if (U.MarkToDelete == false)
			{
				//we only write records that are not marked for delete.
				line = ConvertUsersToString(U);
				UsersRecord << line << endl;
			}
		}
		UsersRecord.close();
	}
}
void SaveUserToFile(string Filename, string line)
{

	fstream UserInfo;
	UserInfo.open(Filename, ios::out | ios::app);
	if (UserInfo.is_open())
	{
		UserInfo << line << endl;
		UserInfo.close();
	}
}
void PrintUsersList()
{
	system("cls");

	vector <stUsers> vUser;
	vUser = ConvertUsersInFileVector(UsersFile);

	cout << "\n\n" << setw(40) << " " << "User List (" << vUser.size() << ") User(s)\n\n";
	cout << "________________________________________________________________________________________________\n\n";
	cout << "| " << setw(12) << left << "User Name";
	cout << "| " << setw(40) << left << "Password";
	cout << "| " << setw(10) << left << "Permissions";
	cout << "\n________________________________________________________________________________________________\n\n";


	for (stUsers& C : vUser)
	{
		cout << "| " << setw(14) << left << C.UserName;
		cout << "| " << setw(40) << left << C.Password;
		cout << "| " << setw(10) << left << C.Permission;
		cout << endl;

	}

	cout << "\n________________________________________________________________________________________________\n";
}
void PrintUserList(stUsers User)
{
	system("cls");

	cout << "________________________________________________________________________________________________\n\n";
	cout << "| " << setw(12) << left << "User Name";
	cout << "| " << setw(40) << left << "Password";
	cout << "| " << setw(10) << left << "Permissions";
	cout << "\n________________________________________________________________________________________________\n\n";

		cout << "| " << setw(14) << left << User.UserName;
		cout << "| " << setw(40) << left << User.Password;
		cout << "| " << setw(10) << left << User.Permission;

	cout << "\n________________________________________________________________________________________________\n";
}
void PrintFindUserScreen()
{
	system("cls");

	cout << "------------------------------------------\n";
	cout << setw(10) << "" << "Find User\n";
	cout << "------------------------------------------\n";
}
stUsers SetPermissns(stUsers& User)
{
	char answer = 'y';
	cout << "Do you want to give full access ? y/n ? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		User.Permission = 127;
		return User;
	}
	cout << "\nDo you want to give access to :\n";
	cout << "\nShow Clint list  ? y/n ? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		User.Permission += 1;

	}
	cout << "\nAdd Clint ? y/n ? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		User.Permission += 2;
	}
	cout << "\nDelete Clint ? y/n ? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		User.Permission += 4;
	}
	cout << "\nUpdate Clint ? y/n ? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		User.Permission += 8;
	}
	cout << "\nFind Clints ? y/n ? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		User.Permission += 16;
	}
	cout << "\nTransaction ? y/n ? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		User.Permission += 32;
	}
	cout << "\nManage Users ? y/n ? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		User.Permission += 64;
	}
	return User;
}
bool HasAPermissonse(short Per, stUsers& User)
{
	if ((User.Permission & Per) == Per)
	{
		return true;
	}
	if ((User.Permission & Per) == Per)
	{
		return true;
	}
	if ((User.Permission & Per) == Per)
	{
		return true;
	}
	if ((User.Permission & Per) == Per)
	{
		return true;
	}
	if ((User.Permission & Per) == Per)
	{
		return true;
	}
	if ((User.Permission & Per) == Per)
	{
		return true;
	}
	if ((User.Permission & Per) == Per)
	{
		return true;
	}
	else
		return false;
}
stUsers ChangeUser(string UserToUpdate, vector <stUsers>& vUser)
{
	stUsers User;
	User.UserName = UserToUpdate;
	cout << "Enter Password :\n";
	getline(cin >> ws, User.Password);
	SetPermissns(User);
	return User;
}
stUsers ReadUserInfo()
{
	stUsers User;
	cout << "Enter User Name :\n";
	getline(cin >> ws, User.UserName);
	cout << "Enter User Password :\n";
	getline(cin >> ws, User.Password);
	return User;
}
void AddUser()
{
	PrintAddNewUserScreen();

	vector <stUsers> vUser;
	vUser = ConvertUsersInFileVector(UsersFile);

	char Answer = 'y';
	stUsers User;
	do
	{
		do
		{
			cout << "Enter User :\n";
			getline(cin >> ws, User.UserName);
			if (CheckIfUsersExist(User.UserName, UsersFile))
				cout << "The User Exsist :(\n";
		} while (CheckIfUsersExist(User.UserName, UsersFile));
		cout << "Enter Password :\n";
		getline(cin >> ws, User.Password);
		User.Permission = SetPermissns(User).Permission;
		SaveUserToFile(UsersFile, ConvertUsersToString(User));
		cout << "The User Added successfully :)\n";
		cout << "\nDo you want to Add anouther User ? y/n\n";
		cin >> Answer;
	} while (Answer == 'y' || Answer == 'Y');
}
bool FindUserByUserNameAndPassword(string UserName, string Password, stUsers& User)
{
	vector <stUsers> vUser;
	vUser = ConvertUsersInFileVector(UsersFile);
	for (stUsers& U : vUser)
	{
		if (UserName == U.UserName && Password == U.Password)
		{
			User = U;
			return true;
		}

	}
	return false;
}
bool LoginIfo(string UserName, string Password)
{
	if (FindUserByUserNameAndPassword(UserName, Password, CurrentUser))
	{
		return true;
	}
	return false;
}
bool SearchForUser(string UserToSearch, vector <stUsers>& vUser, stUsers& User)
{
	for (stUsers& U : vUser)
	{
		if (UserToSearch == U.UserName)
		{
			User = U;
			return true;
		}
	}
	return false;
}
string UserToSearch()
{
	string UserToSearch;
	cout << "Enter User Name:\n";
	getline(cin >> ws, UserToSearch);
	return UserToSearch;
}
void UpdateUser()
{
	PrintUpdateUserScreen();
	string UserToUpdate = UserToSearch();
	vector <stUsers> vUser;
	vUser = ConvertUsersInFileVector(UsersFile);

	stUsers User;
	char Answer;
	if (SearchForUser(UserToUpdate, vUser, User))
	{
		PrintUserList(User);
		cout << "\n\nAre you sure you want to Update the User? y/n\n";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (stUsers& U : vUser)
			{
				if (U.UserName == UserToUpdate)
				{
					U = ChangeUser(UserToUpdate, vUser);
				}
			}
			SaveVectorToFile(UsersFile, vUser);
			cout << "The User has Updated successfully :)\n";
		}
	}
	else
		cout << "User not exsist :(\n";

}
bool MarkUserToDelete(string UserTosearch, vector <stUsers>& vUser)
{
	for (stUsers& U : vUser)
	{
		if (UserTosearch == U.UserName)
		{
			U.MarkToDelete = true;
			return true;
		}
	}
	return false;
}
void DeleteUser()
{
	PrintDeleteUserScreen();
	string UsertoFound = UserToSearch();
	vector <stUsers> vUser;
	vUser = ConvertUsersInFileVector(UsersFile);

	stUsers User;
	char Answer;
	if (SearchForUser(UsertoFound, vUser, User))
	{
		PrintUsersList();
		cout << "\n\nAre you sure you want to delete the Account? y/n\n";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkUserToDelete(UsertoFound, vUser);
			SaveVectorToFile(UsersFile, vUser);
			vUser = ConvertUsersInFileVector(UsersFile);
			cout << "The Account has deleted successfully :)\n";
		}
	}
	else
		cout << "User not exsist :(\n";

}
void FindUser()
{
	PrintFindUserScreen();

	vector <stUsers> vUser;
	vUser = ConvertUsersInFileVector(UsersFile);


	stUsers User;
	if (SearchForUser(UserToSearch(), vUser, User))
	{
		PrintUserList(User);
	}
	else
		cout << "User not exsist :(\n";
}
short ReadTransactionsOption()
{
	short C;
	PrintTransactionsMenueScreen();
	cout << "What you want to do [1 to 4] :";
	cin >> C;
	return C;
}
short ReadManageUsersOption()
{
	short C;
	cout << "What you want to do [1 to 6] :";
	cin >> C;
	return C;
}
void Login();
void MainMenue();
void ManageUsers(enUser Choise)
{
	switch (Choise)
	{
	case enUser::ShowUser:
		PrintUsersList();
		GoBackToManegeMenue();
		break;

	case enUser::UserAdd:
		AddUser();
		GoBackToManegeMenue();
		break;

	case enUser::UserDelete:
		DeleteUser();
		GoBackToManegeMenue();
		break;

	case enUser::UserUpdate:
		UpdateUser();
		GoBackToManegeMenue();
		break;

	case enUser::UserFind:
		FindUser();
		GoBackToManegeMenue();
		break;

	default:
		MainMenue();
		break;
	}
}
void ManageUsersMenue()
{
	if (!HasAPermissonse(enPermisson::P_Manage, CurrentUser))
	{
		PrintPermissionDeniedScreen();
		GoBackToMainMenue();
	}

	PrintManageUsersScreen();
	ManageUsers(enUser(ReadManageUsersOption()));
}
void Transactions(enTchoise Tchoise)
{
	switch (Tchoise)
	{
	case enTchoise::Deposit:
		DepositToAccount();
		GoBackToTransactions();

	case enTchoise::Withdraw:
		WithdrawFromAccount();
		GoBackToTransactions();

	case enTchoise::TotalBalance:
		PrintTotalBalance();
		GoBackToTransactions();

	default:
		MainMenue();

		break;
	}
}
void TransactionsMenue()
{
	if (!HasAPermissonse(enPermisson::P_Trancaction, CurrentUser))
	{
		PrintPermissionDeniedScreen();
		GoBackToMainMenue();
	}

	PrintTransactionsMenueScreen();

	Transactions(enTchoise(ReadTransactionsOption()));
}
void Bank(enChoise Choise)
{
	switch (Choise)
	{
	case enChoise::Show:
		PrintClintList();
		GoBackToMainMenue();
		break;

	case enChoise::Add:
		AddNewClint();
		GoBackToMainMenue();
		break;

	case enChoise::Delete:
		DeleteAccount();
		GoBackToMainMenue();
		break;

	case enChoise::Update:
		UpdateAccount();
		GoBackToMainMenue();
		break;

	case enChoise::Find:
		PrintAccountScreen();
		FindClint();
		GoBackToMainMenue();
		break;

	case enChoise::Transaction:
		TransactionsMenue();
		GoBackToMainMenue();
		break;

	case enChoise::Manage:
		ManageUsersMenue();
		GoBackToMainMenue();
		break;

	default:
		Login();
		break;
	}
}
void MainMenue()
{
	PrintMainMenueScreen();
	Bank(enChoise(ReadMainMenueOption()));
}
void Login()
{
	bool LoginFail = false;
	do
	{
		PrintLoginScreen();
		stUsers User;
		if (LoginFail)
		{
			cout << "Invalied Name and password\n";
		}
		else
			User = ReadUserInfo();
		LoginFail = !LoginIfo(User.UserName, User.Password);
	} while (LoginFail);
	MainMenue();
}
int main()
{

	Login();

	system("pause>0");
	return 0;
}
