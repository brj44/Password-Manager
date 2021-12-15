#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unordered_map>



using namespace std;
struct accountInfo
{
    string userName;
    string password;
};

struct userIDInfo
{
    string userName;
    int userID;
};


int startPage()
{
    int userInput = -1;
        do
        {
            cout << "1. LogOn" << endl;
            cout << "2. Create an account" << endl;
            cout << "0. End program" << endl;

            while(!(cin >> userInput))
            {
                cout << "Error: input was not an integer value" << endl;
                cin.clear();
                cin.ignore(123,'\n');
            }

        }while(userInput < 0 && userInput > 2);
    return userInput;
}

unordered_map<string, userIDInfo> getLocalAccounts()
{
    string line;
    string line2;
    int i = 0;
    ifstream inFile;
    unordered_map<string,userIDInfo> accounts;
    userIDInfo userID;

    inFile.open("managerAccounts.txt");
    if (inFile.is_open())
    {
        while(getline(inFile, line))
        {
            getline(inFile, line2);
            userID.userName = line;
            userID.userID = i;
            accounts[line2] = userID;
            i += 1;
        }
    }
    else
    {
        cout << "no accounts exist please create an account" << endl << endl;;
    }
    inFile.close();
    return accounts;

}


unordered_map<string, string> localUserNameCheck()
{
    string line;
    string line2;
    ifstream inFile;
    unordered_map<string, string> accounts;

    inFile.open("managerAccounts.txt");
    if (inFile.is_open())
    {
        while(getline(inFile, line))
        {
            getline(inFile, line2);
            accounts[line] = line2;
        }
    }

    inFile.close();
    return accounts;

}

vector<unordered_map<string, vector<string>>> accountsCheck()
{
    string line;
    string line2;
    string line3;
    string line4;
    ifstream inFile;
    vector<string> userPassCombo;
    unordered_map<string, vector<string>> accounts;
    vector<unordered_map<string, vector<string>>> orderedAccounts;

    inFile.open("usersAccounts.txt");
    if (inFile.is_open())
    {
        while(getline(inFile, line))
        {
            getline(inFile, line2);
            getline(inFile, line3);
            getline(inFile, line4);
            userPassCombo.push_back(line2);
            userPassCombo.push_back(line3);
            accounts[line] = userPassCombo;
            userPassCombo.clear();
            if (line4 == "$")
            {
                orderedAccounts.push_back(accounts);
            }
        }
    }

    inFile.close();
    return orderedAccounts;

}




vector<vector<vector<string>>> containerToDisplay()
{
    string line;
    string line2;
    string line3;
    string line4;
    ifstream inFile;
    vector<string> userPassCombo;
    vector<vector<string>> accounts;
    vector<vector<vector<string>>> orderedAccounts;


    inFile.open("usersAccounts.txt");
    if (inFile.is_open())
    {
        while(getline(inFile, line))
        {
            getline(inFile, line2);
            getline(inFile, line3);
            getline(inFile, line4);
            userPassCombo.push_back(line2);
            userPassCombo.push_back(line3);
            accounts.push_back(userPassCombo);
            userPassCombo.clear();
            if (line4 == "$")
            {
                orderedAccounts.push_back(accounts);

                accounts.clear();
            }
        }
    }

    inFile.close();
    return orderedAccounts;

}






int logOn ()
{
    unordered_map<string, userIDInfo> accounts = getLocalAccounts();
    userIDInfo userInfo;
    string userName;
    char password[200];

    int accountID;

    if (accounts.empty() == true)
    {
        cout << "No accounts exist please create an account" << endl;
        return -1;
    }

    cout << "please enter your UserName" << endl;
    getline(cin >> std::ws, userName);

    cout << "please enter your password" << endl;
    cin >> password;


    if (accounts[password].userName != userName)
    {
        cout << "incorrect password or userName" << endl;
        cout << "please create an account or try again" << endl;
        accountID = -1;
        return accountID;
    }
    else
    {
        cout << "LogOn Succesful!" << endl << endl;
        accountID = accounts[password].userID;
        return accountID;
    }

}

void createAccount()
{
    unordered_map<string, string> accounts = localUserNameCheck();
    string userName;
    char passWord[200];
    bool userExists = false;
    ofstream outFile;
    outFile.open("managerAccounts.txt");
    do
    {
        cout << "Please Create Your userName" << endl;
        getline(cin >> std::ws, userName);

        if (accounts.count(userName) > 0)
        {
            userExists = true;
            cout << "This userName Already Exists" << endl;
        }
        else
        {
            userExists = false;
        }
    }while (userExists == true);
    cout << "Please Create Your Password" << endl;
    cin >> passWord;

    for(auto i: accounts)
    {
        outFile << i.first << endl;
        outFile << i.second << endl;
    }
    outFile << userName << endl;
    outFile << passWord << endl;
    cout << "Account Created!" << endl;
    outFile.close();

}

int introMenu()
{
    int userChoice;

    do
    {
        cout << "please choose an option" << endl;
        cout << "1. Add a New Password" << endl;
        cout << "2. Generate a New Random Password" << endl;
        cout << "3. Find a Password" << endl;
        cout << "4. View all Passwords" << endl;
        cout << "0. End program" << endl;

        cin >> userChoice;
        while(!(cin >> userChoice))
            {
                cout << "Error: input was not an integer value" << endl;
                cin.clear();
                cin.ignore(123,'\n');
            }

    } while(userChoice != 0 && userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 4);
    return userChoice;
}

void addANewPassword(int userID)
{
    vector<unordered_map<string, vector<string>>> orderedAccounts = accountsCheck();
    string application;
    string userName;
    char passWord[200];

    bool accountExists = false;
    ofstream outFile;
    outFile.open("usersAccounts.txt");

    do
    {
        cout << "Please State The Application Name" << endl;
        getline(cin >> std::ws, application);


        if (userID < orderedAccounts.size())
        {
           if (orderedAccounts[userID].count(application) > 0)
            {
                accountExists = true;
                cout << "This Account Already Exists" << endl;
            }
            else
            {
                accountExists = false;
            }
        }

    }while (accountExists == true);
    cout << "Please Input Your UserName" << endl;
    getline(cin >> std::ws, userName);

    cout << "Please Input Your Password" << endl;
    cin >> passWord;


    for(int i = 0; i < orderedAccounts.size(); i++)
    {
        for(auto x: orderedAccounts[i])
        {

            outFile << x.first << endl;
            outFile << x.second[0] << endl;
            outFile << x.second[1] << endl;
            outFile << "*" << endl;
        }
        if (i != userID)
        {
            outFile << "$" << endl;
        }
    }

    outFile << application << endl;
    outFile << userName << endl;
    outFile << passWord << endl;
    outFile << "$" << endl;
    cout << "Account Created!" << endl;
    outFile.close();

    return;
}

void passwordGenerator()
{
    int ranNum;
    int passwordLength;
    vector<char> genPass;
    srand (time(NULL));

    cout << "Please enter the desired password length" << endl;
    while(!(cin >> passwordLength))
            {
                cout << "Error: input was not an integer value" << endl;
                cin.clear();
                cin.ignore(123,'\n');
            }

    for (int i = 0; i < passwordLength; i++)
    {
        ranNum = rand()%89 + 33;
        genPass.push_back(static_cast<char>(ranNum));
    }
    cout << "Here is Your New Password Please Copy and Paste it." << endl;
    for (int i = 0; i < genPass.size(); i++)
    {
        cout << genPass[i];
    }
    cout << " " << endl << endl;
}

void findAPassword(int userId)
{
    vector<unordered_map<string, vector<string>>> orderedAccounts = accountsCheck();
    string application;
    string userName;
    char passWord[200];
    bool accountExists = false;

    do
    {
        cout << "Please State The Application Name" << endl;
        getline(cin >> ws, application);

        if (orderedAccounts[userId].count(application) > 0)
        {
            accountExists = true;
        }
        else
        {
            cout << "This Account Does Exist" << endl;
            accountExists = false;
        }
    }while (accountExists == false);
    cout << "Your UserName: " << orderedAccounts[userId][application][0] << endl;
    cout << "Your Password: " << orderedAccounts[userId][application][1] << endl << endl;

    return;
}

void displayAllPasswords(int userId)
{
    vector<unordered_map<string, vector<string>>> orderedAccounts = accountsCheck();


    if (orderedAccounts[userId].size() == 0)
    {
        cout << "No Accounts Exist Please Add an Account" << endl << endl;
        return;
    }
    cout << endl;
    for(auto x: orderedAccounts[userId])
    {
        cout << x.first << endl;
        cout << x.second[0] << endl;
        cout << x.second[1] << endl << endl;
    }


    return;
}

int main()
{

    int userChoice;
    int userID;
    do
    {
        userChoice = startPage();
        if (userChoice == 0)
        {
            return 0;
        }
        else if (userChoice == 1)
        {
          userID = logOn();
          if (userID < 0)
          {
              continue;
          }
          else
          {
              break;
          }
        }
        else if (userChoice == 2)
        {
            createAccount();
        }
    }while(userChoice >= 1 && userChoice <= 2);

    do
    {
        userChoice = introMenu();
        if (userChoice == 1)
        {
            addANewPassword(userID);
        }
        else if (userChoice == 2)
        {
            passwordGenerator();
        }
        else if (userChoice == 3)
        {
            findAPassword(userID);
        }
        else if (userChoice == 4)
        {
            displayAllPasswords(userID);
        }
    }while(userChoice != 0);





    return 0;
}
