/*
******   Made by AMIT KUMAR YADAV  ******

Name      - Amit Kumar Yadav
Email     - amitkryadav7777@gmail.com
Github    - https://github.com/amitkryadav7777
LinkedIn  - https://linkedin.com/in/amitkryadav7777
Twitter/X - https://twitter.com/amitkryadav7777
Instagram - https://instagram.com/amitkryadav7777
Date      - 21 September 2024
*/

#include <iostream>
#include <conio.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <ctime>
#include <time.h>
#include <string>
#include <vector>
#include <thread>
#include <graphics.h>
using namespace std;

string category; // This global varialbe identify admin and normal user
int invalid = 0;
void title() // This will show the title on the top
{
    cout << "\t\t-----------------------------------------------\n";
    cout << "\t\t\t:: Bank Management System ::" << endl;
    cout << "\t\t-----------------------------------------------\n\n";
    return;
}

// This fun() will called after successful login...
void home(string declCategory, string accNum);
// This function will check the login credentials...
void authentication(string authCategory, string username, string password);
// When user want to see his/her details
void accDetails(string category, string accNum);
// When the admin/user choose for login
int login();
// To update the user details...
void updateAccount(string category, string optionData);
// To create new user account...
void addAccount(string category);
// To update the user detials...
void update(string accNum, int option);
// To deposit the amount in the account...
void depositAmount(string category, string depositAccNum);
// To withdraw the amount in the account...
void withdrawalAmount(string category, string withdrawalAccNum);
// To check the account balance...
void balanceInqiry(string category, string inquiryAccNum);
// To see the transactions statement...
void passStatement(string category, string statAccNum);
// To delete the user account...
void deleteAccount(string category, string deleteAccNum);
// Login for admin...
void adminLogin();
// Login for user...
void userLogin();

void addAccount(string category) // To add new account
{
    system("cls");
    title();
    string name, dob, mobile, email, accNum, accType, password, amount, time, city = "";
    fstream fout;
    fstream out;
    // opens existing csv files or creates new files to store account holders' data and statements.
    fout.open("accounts.csv", ios::out | ios::app);
    out.open("statements.csv", ios::out | ios::app);
    cout << "\t\tCreating an account -- \n";
    cout << "\t\tAccount Holder Name : "; // Now taking input of users' details
    cin.ignore();
    getline(cin, name);
    cout << "\t\tDOB (dd/mm/yyyy)    : ";
    cin >> dob;
    cout << "\t\tMobile              : ";
    cin >> mobile;
    cout << "\t\tEmail               : ";
    cin >> email;
    cout << "\t\tAccount Number      : ";
    cin >> accNum;

    char delimiter = ','; // CHECK-START, Checking account number's availibility...
    std::string line;
    std::string item;
    std::ifstream file("login.csv");
    std::vector<std::string> row;
    while (std::getline(file, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (accNum == row[1])
        {
            cout << "\t\tThis account number already exists!\n"
                 << endl;
            delay(1000);
            file.close();
            addAccount(category);
            return;
        }
    } // CHECK-END

    cout << "\t\tAccount Type(S/C)   : ";
    cin >> accType;
    cout << "\t\tPassword            : ";
    cin >> password;
    cout << "\t\tAmount to Deposit   : ";
    cin >> amount;
    cout << "\t\tCity                : ";
    cin.ignore();
    getline(cin, city);
    // Inserting the data into accounts.csv file
    fout << name << ","
         << dob << ","
         << mobile << ","
         << email << ","
         << accNum << ","
         << accType << ","
         << password << ","
         << city
         << "\n";

    time_t t;
    struct tm *tm;
    char Date[30];
    std::time(&t);
    tm = localtime(&t);
    strftime(Date, sizeof Date, "%x %X", tm);
    time = Date;
    // Inserting the data into statements.csv file
    out << accNum << ","
        << "Cr" << ","
        << time << ","
        << amount << ","
        << amount
        << "\n";

    fstream outLogin;
    outLogin.open("login.csv", ios::out | ios::app);
    // Inserting the data into login.csv file for login
    outLogin << "user" << ","
             << accNum << ","
             << password
             << "\n";
    cout << "\t\tAccount successfully created." << endl;
    outLogin.close();
    fout.close();
    out.close();
    delay(1000);
    if (category == "user")
    {
        login();
        return;
    }
    home(category, accNum);
    return;
}


void accDetails(string category, string accNum)
{ // To see  user detials by user itself
    system("cls");
    title();
    fstream file;
    // opening an existing csv file to fetch account holders' details.
    file.open("accounts.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[4] == accNum) // Now printing data of user
            {
                cout << "\n\t\tAccount Details -\n"
                     << "\n\t\tName          : " << row[0] << "\n\t\tDOB(dd/mm/yy) : " << row[1] << "\n\t\tMobile        : " << row[2] << "\n\t\tEmail         : " << row[3] << "\n\t\tAccount No    : " << row[4] << "\n\t\tAccount Type  : " << row[5] << "\n\t\tCity          : " << row[7] << endl;
            }
        }
    }
    file.close();
    string back;
    cout << "\n\t\tPress any key to exit... ";
    cin >> back;
    home(category, accNum);
    return;
}
void update(string accNum, int option)
{ // To update user detail..
    fstream fout;
    // opens an existing csv file to fetch and store account holders' data.
    fout.open("accounts.csv", ios::in | ios::out);
    if (fout.fail())
    {
        cout << "\n\t\tError opening the file" << endl;
        delay(1000);
        home(category, accNum);
        return;
    }

    vector<string> lines;
    string line;
    char delimiter = ',';
    std::string item;
    std::vector<std::string> row;
    while (std::getline(fout, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (row[4] == accNum) // Checking accNum and taking new data for accNum...
        {
            line = "";
            string newData;
            switch (option)
            {
            case 1:
                cout << "\n\t\tEnter New Name : ";
                cin.ignore();
                getline(cin, newData);
                row[0] = newData;
                break;
            case 2:
                cout << "\n\t\tEnter New DOB : ";
                cin.ignore();
                getline(cin, newData);
                row[1] = newData;
                break;
            case 3:
                cout << "\n\t\tEnter New Mobile : ";
                cin >> newData;
                row[2] = newData;
                break;
            case 4:
                cout << "\n\t\tEnter New Email : ";
                cin >> newData;
                row[3] = newData;
                break;
            case 5:
                cout << "\n\t\tEnter New City : ";
                cin >> newData;
                row[7] = newData;
                break;
            case 6:
                cout << "\n\t\tEnter New Password : ";
                cin.ignore();
                getline(cin, newData);
                row[6] = newData;
                break;
            default:
                cout << "\n\t\tInvalid option";
                break;
            }
            for (int i = 0; i < row.size(); i++)
            {
                line.append(row[i]);
                if (i != row.size() - 1)
                {
                    line.push_back(',');
                }
            }
            lines.push_back(line);
        }
        else
        {
            lines.push_back(line);
        }
    }
    fout.close();
    fstream fin;
    fin.open("accounts.csv", ios::out); // Now inserting user's newd data in the database
    for (string l : lines)
    {
        fin << l << "\n";
    }
    fin.close();
    cout << "\n\t\tAccount successfully updated!";
    delay(1000);
    updateAccount(category, accNum);
    return;
}


// Shows user's data for updataion and then this updateAccount() called update()
void updateAccount(string category, string updateAccNum)
{
    system("cls");
    title();
    string accNum = updateAccNum;
    bool accPresent = false;

    fstream file;
    // opens an existing csv file to fetch account holders' data for updation.
    file.open("accounts.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[4] == accNum) // Showing details of accNum
            {
                accPresent = true;
                cout << "\n\t\tAccount No       : " << row[4] << "\n\t\tAccount Type     : " << row[5] << "\n"
                     << "\n\t\tUpdate Account details -\n"
                     << "\n\t\t1. Name          : " << row[0] << "\n\t\t2. DOB(dd/mm/yy) : " << row[1] << "\n\t\t3. Mobile        : " << row[2] << "\n\t\t4. Email         : " << row[3] << "\n\t\t5. City          : " << row[7];
                if (category == "user")
                {
                    cout << "\n\t\t6. Password      : " << row[6];
                }
            }
        }
    }
    file.close();
    if (!accPresent) // To check accNum exists or not
    {
        cout << "\n\n\t\tInvalid account number..." << endl;
        delay(1000);
    }
    else
    {
        int option;
        cout << "\n\n\t\tSelect an option to update that detatil or 0 to exit :  ";
        cin >> option;
        if (option == 0)
        {
            home(category, accNum);
            return;
        }
        update(accNum, option);
        updateAccount(category, accNum);
    }
    home(category, accNum);
    return;
}


void depositAmount(string category, string depositAccNum) // To deposit Amount
{
    system("cls");
    title();

    string time, amount, balance;
    string accNum = depositAccNum;
    bool accPresent = false;

    char delimiter = ',';
    std::string line;
    std::string item;
    std::ifstream file("login.csv");
    std::vector<std::string> row;
    while (std::getline(file, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (accNum == row[1])
        {
            accPresent = true;
            cout << "\n\t\tEnter amount to deposit : ";
            cin >> amount; // Taking amount from user to deposit
            long int finalBalance;

            string trans = "Cr";
            fstream file;
            // opening statements.csv file to update statements.
            file.open("statements.csv", ios::out | ios::app | ios::in);
            while (file.eof() == 0)
            {
                char delimiter = ',';
                std::string line;
                std::string item;
                std::vector<std::string> row;
                while (std::getline(file, line))
                {
                    row.clear();
                    std::stringstream string_stream(line);
                    while (std::getline(string_stream, item, delimiter))
                    {
                        row.push_back(item);
                    }
                    if (row[0] == accNum)
                    {
                        balance = row[4]; // Fetching previous balance
                    }
                }
            }
            file.close();
            fstream file1; // Opening statements.csv file to store statement
            file1.open("statements.csv", ios::out | ios::app);

            time_t t;
            struct tm *tm;
            char Date[30];
            std::time(&t);
            tm = localtime(&t);
            strftime(Date, sizeof Date, "%x %X", tm);
            time = Date;

            finalBalance = stoi(balance) + stoi(amount); // Updaing balance
            file1 << accNum << ","                       // Storing data
                  << trans << ","
                  << time << ","
                  << amount << ","
                  << finalBalance
                  << "\n";
            file1.close();
            cout << "\n\t\tAmount deposited.";
            delay(1000);
        }
    }
    if (!accPresent)
    {
        cout << "\n\n\t\tInvalid account number..." << endl;
        delay(1000);
    }
    home(category, accNum);
    return;
}


void withdrawalAmount(string category, string withdrawalAccNum) // To withdraw amount
{
    system("cls");
    title();

    string accNum, time, amount, balance;
    accNum = withdrawalAccNum;
    bool accPresent = false;

    char delimiter = ',';
    std::string line;
    std::string item;
    std::ifstream file("login.csv");
    std::vector<std::string> row;
    while (std::getline(file, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (accNum == row[1])
        {
            accPresent = true;
            cout << "\n\t\tEnter amount to withdrawal : ";
            cin >> amount;
            long int finalBalance;

            string trans = "Dr";
            fstream file;
            // opening statements.csv file to withdraw money and to update statements.
            file.open("statements.csv", ios::out | ios::app | ios::in);
            while (file.eof() == 0)
            {
                char delimiter = ',';
                std::string line;
                std::string item;
                std::vector<std::string> row;
                while (std::getline(file, line))
                {
                    row.clear();
                    std::stringstream string_stream(line);
                    while (std::getline(string_stream, item, delimiter))
                    {
                        row.push_back(item);
                    }
                    if (row[0] == accNum)
                    {
                        balance = row[4]; // Fetching previous balance
                    }
                }
            }
            file.close();
            fstream file1;
            file1.open("statements.csv", ios::out | ios::app);

            time_t t;
            struct tm *tm;
            char Date[30];
            std::time(&t);
            tm = localtime(&t);
            strftime(Date, sizeof Date, "%x %X", tm);

            time = Date;
            finalBalance = stoi(balance) - stoi(amount); // Updating balance
            if (finalBalance < 0)
            {
                cout << "\n\n\t\tNot enough balance to withdrawal...";
            }
            else
            {
                file1 << accNum << "," // Storing data
                      << trans << ","
                      << time << ","
                      << amount << ","
                      << finalBalance
                      << "\n";
                file1.close();
                cout << "\n\t\tAmount withdrawaled.";
            }
            delay(1000);
            home(category, accNum);
            return;
        }
    }
    file.close();

    if (!accPresent)
    {
        cout << "\n\n\t\tInvalid account number..." << endl;
        delay(1000);
    }
    home(category, accNum);
    return;
}


void balanceInqiry(string category, string inquiryAccNum) // To check  acouont balance
{
    system("cls");
    title();
    string accNum, balance;
    accNum = inquiryAccNum;
    cout << "\t\tAccount number : " << accNum << "\n";
    bool accPresent = false;
    long int finalBalance;
    fstream file;
    // opening statements.csv file to fetch balance of accNum.
    file.open("statements.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {

            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[0] == accNum)
            {
                accPresent = true;
                balance = row[4]; // Fetching balance
            }
        }
    }
    file.close();
    if (accPresent)
    {
        cout << "\n\n\t\tBalance is : " << balance << endl; // Displaying balance
        string back;
        cout << "\n\t\tPress any key to exit... ";
        cin >> back;
    }
    else
    {
        cout << "\n\n\t\tInvalid account number..." << endl;
        delay(1000);
    }
    home(category, accNum);
    return;
}


void passStatement(string category, string statAccNum) // To see transactions statement
{
    system("cls");
    title();
    string accNum, balance;
    accNum = statAccNum;
    cout << "\t\tAccount number : " << accNum << "\n";
    bool accPresent = false;
    long int finalBalance;
    fstream file;
    // opening statements.csv file to fetch statements for accNum.
    file.open("statements.csv", ios::out | ios::app | ios::in);
    cout << "\n\t\tPassbook Statement - " << endl;
    cout << "\n\t\tA/C No\tCr./Dr.\tDate & Time\t\tAmount\tBalance" << endl;
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[0] == accNum) // Displaying statement
            {
                accPresent = true;
                cout << "\t\t" << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl;
            }
        }
    }
    file.close();
    if (!accPresent)
    {
        cout << "\n\n\t\tInvalid account number..." << endl;
        delay(1000);
    }
    else
    {
        string back;
        cout << "\n\t\tPress any key to exit... ";
        cin >> back;
    }
    home(category, accNum);
    return;
}


void deleteAccount(string category, string deleteAccNum) // To delete a user account
{
    system("cls");
    title();
    fstream fout;
    fstream flogin;
    // opening accounts.csv file to fetch account holders' details and to delete it.
    fout.open("accounts.csv", ios::in | ios::out);
    flogin.open("login.csv", ios::in | ios::out);
    if (fout.fail() || flogin.fail())
    {
        cout << "\n\t\tError opening the file" << endl;
        delay(1000);
        home(category, deleteAccNum);
        return;
    }
    bool accPresent = false;
    string accNum = deleteAccNum;
    vector<string> lines;
    string line;
    char delimiter = ',';
    std::string item;
    std::vector<std::string> row;
    // We will store all the data of accounts.csv and login.csv file into 2 different vectors except deleting a/c(accNum) and then we clear all data of accounts.csv and login.csv file and then vectors' data will again store in accounts.csv and login.csv file
    while (std::getline(fout, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (row[4] == accNum)
        {
            accPresent = true;
            continue;
        }
        lines.push_back(line); // Storing data in vector from accouonts.csv except accNum's details
    }
    fout.close();
    if (!accPresent)
    {
        cout << "\n\t\tAccount doesn't exist.\n";
    }
    else
    {
        fstream fin;
        fin.open("accounts.csv", ios::out);
        for (string l : lines) // Now storing vector's data into accounts.csv file
        {
            fin << l << "\n";
        }
        fin.close();
    }

    line = "";
    lines = {};
    item = "";
    row.clear();
    accPresent = false;
    while (std::getline(flogin, line))
    {

        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (row[1] == accNum)
        {
            accPresent = true;
            continue;
        }
        lines.push_back(line);
    }
    flogin.close();
    if (!accPresent)
    {
        cout << "\n\t\tAccount doesn't exist.\n";
    }
    else
    {
        fstream fLin;
        fLin.open("login.csv", ios::out);
        for (string l : lines) // Now storing data into login.csv file
        {
            fLin << l << "\n";
        }
        fLin.close();
        cout << "\n\t\tAccount successfully deleted!";
    }
    // }

    delay(1000);
    if (category == "user")
    {
        login();
        return;
    }
    home(category, accNum);
    return;
}


void adminLogin()
{ // This will called when we choose admin
    system("cls");
    title();
    string username, password;
    category = "admin";
    cout << "\t\tEnter username : ";
    cin >> username;
    cout << "\t\tEnter password : ";
    cin >> password;
    authentication(category, username, password);
    return;
}


void userLogin()
{ // This will called when we choose user
    system("cls");
    title();
    string username, password;
    category = "user";
    int userType;
    cout << "\t\t1. Create New Account\n";
    cout << "\t\t2. Log in";
    cout << "\n\t\tChoose one of above option : ";
    cin >> userType;
    if (userType == 1)
    {
        addAccount(category);
        return;
    }
    if (userType == 2)
    {
        cout << "\n\t\tEnter Account Number : ";
        cin >> username;
        cout << "\t\tEnter Password : ";
        cin >> password;
        authentication(category, username, password); // Calling authentication() for authentication of input credentials
    }
    return;
}


void authentication(string authCategory, string username, string password)
{ // To verify login credentials
    char delimiter = ',';
    std::string line;
    std::string item;
    std::ifstream file("login.csv");
    std::vector<std::string> row;
    while (std::getline(file, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if ((username == row[1]) && (password == row[2]))
        {
            cout << "\t\tYou have successfully logged in!\n"
                 << endl;
            delay(1000);
            file.close();
            home(authCategory, username);
            file.close();
            return;
        }
    }
    cout << "\n\t\tInvalid credentials.\n"
         << endl;
    file.close();
    delay(1000);
    system("cls");
    title();
    login();
    file.close();
    return;
}


int login() // To select type of login either Admin or User
{
    system("cls");
    title();
    int type;
    cout << "\t\tPlease choose your category -\n\n";
    cout << "\t\t1. Bank Manager\n";
    cout << "\t\t2. Account Holder\n\n";
    cout << "\t\tType your category : ";
    cin >> type;

    if (type == 1)
    {
        adminLogin();
    }
    if (type == 2)
    {
        userLogin();
    }
    return 0;
}


void home(string homeCategory, string accNum) // This will be executed after login
{
    int option = 0;
    system("cls");
    title();
    if (homeCategory == "admin")
    {
        cout << "\t\t1. Add New Account\n";
    }
    else
    {
        cout << "\t\t1. Account Details\n";
    }
    cout << "\t\t2. Update Account\n";
    cout << "\t\t3. Deposit Amount\n";
    cout << "\t\t4. Withdrawal Amount\n";
    cout << "\t\t5. Balance Inquiry\n";
    cout << "\t\t6. Passbook Statement\n";
    cout << "\t\t7. Delete Account\n";
    cout << "\t\t8. Logout & Exit\n";
    cout << "\t\tEnter your choice : ";
    cin >> option;
    string optionData;
    switch (option)
    {
    case 1:
        if (homeCategory == "admin")
        {
            addAccount(homeCategory);
        }
        else
        {
            accDetails(homeCategory, accNum);
        }
        break;
    case 2:
        if (homeCategory == "admin")
        { // If user will be admin then this block
            cout << "\n\t\tEnter account number to update detail..: ";
            cin >> optionData;
            updateAccount(homeCategory, optionData);
        }
        else
        { // If user will be normal user then this block
            updateAccount(homeCategory, accNum);
        }
        break;
    case 3:
        if (homeCategory == "admin")
        {
            cout << "\n\t\tEnter account number to deposit amount.. : ";
            cin >> optionData;
            depositAmount(homeCategory, optionData);
        }
        else
        {
            depositAmount(homeCategory, accNum);
        }
        break;
    case 4:
        // If there is admin then we required accNum to perform opertaion o an user's account
        if (homeCategory == "admin")
        {
            cout << "\n\t\tEnter account number to withdrawal amount.. : ";
            cin >> optionData;
            withdrawalAmount(homeCategory, optionData);
        }
        else
        {
            // If there is user then the accNum will be already fetched at login time
            withdrawalAmount(homeCategory, accNum);
        }
        break;
    case 5:
        if (homeCategory == "admin")
        {
            cout << "\n\t\tEnter account number to check balance... : ";
            cin >> optionData;
            balanceInqiry(homeCategory, optionData);
        }
        else
        {
            balanceInqiry(homeCategory, accNum);
        }
        break;
    case 6:
        if (homeCategory == "admin")
        {
            cout << "\n\t\tEnter account number to see Passbook statement : ";
            cin >> optionData;
            passStatement(homeCategory, optionData);
        }
        else
        {
            passStatement(homeCategory, accNum);
        }
        break;
    case 7:
        if (homeCategory == "admin")
        {
            cout << "\n\t\tEnter account number to delete account : ";
            cin >> optionData;
            deleteAccount(homeCategory, optionData);
        }
        else
        {
            deleteAccount(homeCategory, accNum);
        }
        break;
    case 8:
        cout << "\n\t\tThank You...";
        return;
    }
    return;
}


int main()
{
    int session = 0;
    fstream flogin;
    flogin.open("login.csv", ios::out | ios::app); // Creating CSV file for authentication
    flogin.close();
    title();
    category = "";
    session = login();
    return 0;
}
