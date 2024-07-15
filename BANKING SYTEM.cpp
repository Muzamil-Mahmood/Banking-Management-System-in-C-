#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct Account {
    int accountNumber;
    string accountHolderName;
    double balance;
    Account* next;
};

class Bank {
private:
    Account* head;
    unordered_map<int, Account*> hashTable;

public:
    Bank() : head(nullptr) {}

    void addAccount(int accountNumber, const string& accountHolderName, double balance) {
        Account* newAccount = new Account{accountNumber, accountHolderName, balance, head};
        head = newAccount;
        hashTable[accountNumber] = newAccount;
        cout << "Account added: " << accountHolderName << " (" << accountNumber << ")" << endl;
    }

    void deleteAccount(int accountNumber) {
        Account* current = head;
        Account* previous = nullptr;

        while (current != nullptr && current->accountNumber != accountNumber) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Account not found!" << endl;
            return;
        }

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        hashTable.erase(accountNumber);
        delete current;
        cout << "Account deleted: " << accountNumber << endl;
    }

    Account* searchAccount(int accountNumber) {
        if (hashTable.find(accountNumber) != hashTable.end()) {
            return hashTable[accountNumber];
        } else {
            return nullptr;
        }
    }

    void displayAccounts() {
        Account* current = head;
        while (current != nullptr) {
            cout << "Account Number: " << current->accountNumber
                 << ", Account Holder: " << current->accountHolderName
                 << ", Balance: $" << current->balance << endl;
            current = current->next;
        }
    }
};

int main() {
    Bank bank;
    int choice, accno;
    string name;
    double balance;

    do {
        cout << "\nSelect Options";
        cout << "\n1 :: Create Account \n2 :: Check Balance \n3 :: Delete Account \n4 :: Display All Accounts \n5 :: Exit \nEnter Your Choice: " << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Your Account Number: " << endl;
                cin >> accno;
                cout << "Enter Your Name: " << endl;
                cin >> name;
                cout << "Enter Your Balance: " << endl;
                cin >> balance;
                bank.addAccount(accno, name, balance);
                cout << "\nCongratulations! Your account is created." << endl;
                break;
            case 2: {
                cout << "Enter Account Number: " << endl;
                cin >> accno;
                Account* account = bank.searchAccount(accno);
                if (account) {
                    cout << "\nAccount found: "
                         << "Account Name :"<<account->accountHolderName << " ,Account Number :" << account->accountNumber
                         << ", Balance: $" << account->balance << endl;
                } else {
                    cout << "\nAccount not found: " << accno << endl;
                }
                break;
            }
            case 3:
                cout << "Enter Account Number: " << endl;
                cin >> accno;
                bank.deleteAccount(accno);
                break;
            case 4:
                cout << "ALL ACCOUNTS" << endl;
                bank.displayAccounts();
                break;
            case 5:
                return 0;
            default:
                cout << "Enter Correct Option" << endl;
        }
    } while (choice != 5);

    return 0;
}
