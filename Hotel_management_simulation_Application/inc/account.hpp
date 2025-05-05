#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include "Std_Types.hpp"
class Account
{
private: 
    string username; // Username of the account
    string password; // Password of the account

public:
    Account();
    Account(const string &username,const string &password);
    
    string getUsername() const; // Returns the username of the account
    string getPassword() const; // Returns the password of the account

    void setUsername(const string &username); // Sets the username of the account
    void setPassword(const string &password); // Sets the password of the account

    static bool verifyManager(const string &password);
    static bool verifyEmployee(const string &password); // Verifies if the password is correct for an employee account
    static bool verifyAdmin(const string &password); // Verifies if the password is correct for an admin account
    static bool accountExists(const vector<Account>& accountList, const string& username);

    static bool registerAccount(vector<Account>& accountList,const string &username, const string &password); // Registers a new account with the given username and password
    
    static bool login(const vector<Account>& accountList,const string &username, const string &password); // Logs in to the account with the given username and password
    // static void showlistAccounts(); // Displays the list of accounts
    static bool VerifyManagerAccount(const string& password);
    static void showlistAccounts();
};
extern vector<Account> accountList; //biến toàn cục lưu trữ danh sách tài khoản nhân viên và quản lý sử dụng ở nhiều file
#define SUCCESS 1 // Success code for functions
#define FAILURE 0 // Failure code for functions
#endif // ACCOUNT_HPP