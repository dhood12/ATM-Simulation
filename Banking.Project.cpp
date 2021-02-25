#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

string username, password, unTyped, pwTyped, transferDecision, firstName, lastName;
int decision;
int transactionCounter = 3;
char transactionDecision;
char accountSelect;
bool isUsername, sClicked;
bool isPassword, cClicked;
bool isRob = false;
bool isLisa = false;
bool isMark = false;
bool isLeeAnn = false;
float moneyDeposited, moneyTransferred, moneyWithdrawn;
float savingsBalance;
float checkingsBalance;


struct Customer
{
  string firstName;
  string lastName;
  string username;
  string password;
  float savingsBalance;
  float checkingsBalance;
};

const int size = 4;
Customer customerArray[size];
ofstream outFile;

void whichAccount();
void Deposit();
void BalanceInquiry();
void Withdrawal();
void LogOut();
void TransferBalance();
void transactionOption();
void readInfo(ifstream& inFile);
void updateFile();
void updateValues();


int main(){
  isUsername = false;
  isPassword = false;
  int counter = 2;
  ifstream inFile;
  readInfo(inFile);
  whichAccount();
 
  
//This prompts the user to input his or hers username
  cout << endl;
  cout << "Hi " << firstName << " " << lastName << "!" << endl;
  cout << "We just need you to enter your credentials to make sure this is you. You currently have 3 attempts remaining." << endl;
  while(!isUsername)
  {   
    cout << "Please enter your username:" << endl;
    cin >> unTyped;

    if (unTyped != username)
    {
      cout << "Invalid username! You have " << counter << " attempts remaining."<< endl;
      counter--;
    }
    else
    {
      isUsername = true;
      counter = 2;
    }        
    if (counter <= -1)
    {
      cout << "Too many incorrect attempts. You have been locked out. Please consult your bank." << endl;
      cout << "Goodbye." << endl;
      return 0;
    }
  }
    
  
//This prompts the user to input his or hers password
  cout << endl;
  cout << "Great! Now we need your password. You currently have 3 attempts remaining." << endl;
  while(!isPassword)
  {
    cout << "Please enter your password: " << endl;
    cin >> pwTyped;

    if (pwTyped != password)
    {
      cout << "Invalid password! You have " << counter << " attempts remaining."<< endl;
      counter--;
    }
    else
    {
      isPassword = true;
      cout << "Access Granted" << endl;
    }
    if (counter <= -1)
    {
      cout << "Too many incorrect attempts. You have been locked out. Please consult your bank." << endl;
      cout << "Goodbye." << endl;
      return 0;
    }
  }
  
  while(transactionCounter >= 0)
  {

    while(cin)
    {
      cout << endl;
      cout << "What would you like to do today?" << endl;
      cout << "Press 1 for Balance Inquiry" << endl
        << "Press 2 for Withdrawal" << endl 
        << "Press 3 for Deposit" << endl
        << "Press 4 for Transfer Balance" << endl
        << "Press 5 to Log Out" << endl;
      cin >> decision;
      if (decision != (int)decision)
      {
        cout << "Invalid option. Please input an integer value that corresponds to the menu." << endl;
      }
      else
        break;
    }
    


    switch (decision)
    {
//Balance Inquiry
      case 1:
        BalanceInquiry();
        updateFile();
        transactionOption();
        break;
//Withdrawal
      case 2: 
        Withdrawal();
        updateValues();
        updateFile();
        transactionOption();
        break;
//Deposit
      case 3: 
        Deposit();
        updateValues();        
        updateFile();
        transactionOption();
        break;

//Transfer
      case 4:
        TransferBalance();
        updateValues();
        updateFile();
        transactionOption();
        break;
//Log Out
      case 5:
        LogOut();
        updateValues();
        updateFile();
        return 0;
        break;
      default: 
        cout << "Invalid option, try again." << endl;
    }
    if(transactionCounter == 0)
    {
      cout << "You are now logged out.\nGoodbye." << endl;
      break;
    }
  }
  return 0;  
}

//Function for BalanceInquiry
void BalanceInquiry()
{
  cout << "You currently have $" << savingsBalance << " in your savings account and $";
  cout << checkingsBalance << " in your checkings account." << endl;
}

//Function for Withdrawal
void Withdrawal()
{
      BalanceInquiry();
      cout << "Which account would you like to withdraw from? Press c for checkings, and s for savings." << endl;
      cin >> accountSelect;
      while (cin) 
      {
        if(accountSelect == 's') 
        {      
          cout << "Please input the amount of dollars you would like to withdraw";
          cout << " from your savings account today. " << endl;
          cin >> moneyWithdrawn;
          if(moneyWithdrawn == (int)moneyWithdrawn && moneyWithdrawn >= 0 && moneyWithdrawn <= savingsBalance)
          {
            savingsBalance = savingsBalance - moneyWithdrawn;
            break;
          }
          else
          {
            cout << "Invalid input. Must be a positive integer, and must not exceed balance." << endl;
          }
        }
        else if (accountSelect == 'c')
        {
          cout << "Please input the amount of dollars you would like to withdraw";
          cout << " from your checkings account today. " << endl;
          cin >> moneyWithdrawn;
          if(moneyWithdrawn == (int)moneyWithdrawn && moneyWithdrawn >= 0 && moneyWithdrawn <= checkingsBalance)
          {
            checkingsBalance = checkingsBalance - moneyWithdrawn;
            break;
          }
          else 
          {
            cout << "Invalid Input. Must be a positive integer, and must not exceed balance." << endl;
          }
        }
        else //Outputs error message if user presses something other than 'c' or 's'
        {
          cout << "Invalid option" << endl;
          cout << "Which account would you like to deposit into today? Press c for checkings";
          cout << endl;
          cout << " and s for savings. " << endl;
          cin >> accountSelect;
        }
      }
          //Gives a detailed description of the transaction
      if (accountSelect == 'c')
      {
        cout << "You have withdrawn: $" << moneyWithdrawn << " from your checkings account.";
        cout << "\nYou now have: $" << checkingsBalance << " in your checkings account." << endl;  
      }
      else if (accountSelect == 's')
      {
        cout << "You have withdrawn: $" << moneyWithdrawn << " from your savings account.";
        cout << "\nYou now have: $" << savingsBalance << " in your savings account." << endl;
      }
}

//Function for Deposit
void Deposit()
{
  BalanceInquiry();
  cout << "Which account would you like to deposit into today? Press c for checkings";
      cout << " and s for savings. " << endl;
      cin >> accountSelect; 
//Checks which account the user has selected and
//Prompts the user to input how much money they would like to deposit
      while (cin) 
      {
        if(accountSelect == 's') 
        {
          cout << "Please insert the amount of dollars you would like to deposit";
          cout << " into your savings account today. " << endl;
          cin >> moneyDeposited;
          if(moneyDeposited == (int)moneyDeposited && moneyDeposited >= 0)
          {
            savingsBalance = savingsBalance + moneyDeposited;
            
            customerArray[0].savingsBalance = savingsBalance;
            break;
          }
          else
          {
            cout << "Invalid input. Must be a positive integer." << endl;
          }
        }
        else if (accountSelect == 'c')
        {
          cout << "Please insert the amount of dollars you would like to deposit";
          cout << " into your checkings account today. " << endl;
          cin >> moneyDeposited;
          if(moneyDeposited == (int)moneyDeposited && moneyDeposited >= 0)
          {
            checkingsBalance = checkingsBalance + moneyDeposited;
            break;
          }
          else 
          {
            cout << "Invalid Input. Must be a positive integer." << endl;
          }
        }
        else //Outputs error message if user presses something other than 'c' or 's'
        {
          cout << "Invalid option" << endl;
          cout << "Which account would you like to deposit into today? Press c for checkings";
          cout << endl;
          cout << " and s for savings. " << endl;
          cin >> accountSelect;
        }
      }
          //Gives a detailed description of the transaction
      if (accountSelect == 'c')
      {
        cout << "You have deposited: $" << moneyDeposited << " into your checkings account.";
        cout << "\nYou now have: $" << checkingsBalance << " in your checkings account." << endl;  
      }
      else if (accountSelect == 's')
      {
        cout << "You have deposited: $" << moneyDeposited << " into your savings account.";
        cout << "\nYou now have: $" << savingsBalance << " in your savings account." << endl;
      }
}

//Function to transfer the balance from one account to another
void TransferBalance()
{
  BalanceInquiry();
  cout << "Which accounts would you like to transfer money into and from? If checkings to savings, press cs, if savings to checkings, press sc" << endl;
      cin >> transferDecision;
      while (cin)
      {
        if (transferDecision == "cs")
        {
          cout << "How much money would you like to transfer from your checkings into your savings?" << endl;
          cin >> moneyTransferred;
          if (moneyTransferred == (int)moneyTransferred && moneyTransferred >= 0 && moneyTransferred <= checkingsBalance)
          {
            checkingsBalance = checkingsBalance - moneyTransferred;
            savingsBalance = savingsBalance + moneyTransferred;
            break;
          }
          else
          {
            cout << "Invalid Input. Must be a positive integer, and must not exceed account balance." << endl;
          }          
        }
        else if (transferDecision == "sc")
        {
          cout << "How much money would you like to transfer from your savings into your checkings?" << endl;
          cin >> moneyTransferred;
          if (moneyTransferred == (int)moneyTransferred && moneyTransferred >= 0 && moneyTransferred <= savingsBalance)
          {
            savingsBalance = savingsBalance - moneyTransferred;
            checkingsBalance = checkingsBalance + moneyTransferred;
            break;
          }
          else
          {
            cout << "Invalid Input. Must be a positive integer, and must not exceed account balance." << endl;
          }
        }
          else //Outputs error message if user presses something other than 'cs' or 'sc'
        {
          cout << "Invalid option" << endl;
          cout << "Which accounts would you like to transfer money into and from? If checkings to savings, press cs, if savings to checkings, press sc" << endl;
          cin >> transferDecision;
        }
      }
      
          //Gives a detailed description of the transaction
      if (transferDecision == "cs")
      {
        cout << "You have transferred: $" << moneyTransferred << " from your checkings account into your savings." << endl;
        cout << "\nYou now have: $" << savingsBalance << " in your savings account " << 
          "and $" << checkingsBalance << " in your checkings account." << endl;           
      }
      else if (transferDecision == "sc")
      {
        cout << "You have transferred: $" << moneyTransferred << " from your savings account into your checkings.";
        cout << "\nYou now have: $" << checkingsBalance << " in your checkings account. " <<
          "and $" << savingsBalance << " in your savings account." << endl;
      }
}

//Function for logging out
void LogOut()
{
   cout << "You have logged out." << endl;
   cout << "Have a wonderful day!" << endl;
}

//Function for making another transaction
void transactionOption()
{
  cout << "Would you like to make another transaction?" << endl;
  cout << "Press y for yes, or n for no." << endl;
  cin >> transactionDecision;
  if (transactionDecision == 'Y' || transactionDecision == 'y')
  {
     transactionCounter--;
     cout << "You have " << transactionCounter << " more transaction(s) left." << endl;
  } 
  else 
  {
     transactionCounter = -1;
     LogOut();
  }
}

//Function for determining whose account is being logged into
void whichAccount()
{
  do
  {
    cout << "Hello! Welcome to the Airline Bank!" << endl;
    cout << "Please enter your first and last name: " << endl;
    cin >> firstName >> lastName;
    if (firstName == customerArray[0].firstName && lastName == customerArray[0].lastName)
    {
      isRob = true;
      username = customerArray[0].username;
      password = customerArray[0].password;
      savingsBalance = customerArray[0].savingsBalance;
      checkingsBalance = customerArray[0].checkingsBalance;
      break;
    }
    else if (firstName == customerArray[1].firstName && lastName == customerArray[1].lastName) 
    {
      isLisa = true;
      username = customerArray[1].username;
      password = customerArray[1].password;
      savingsBalance = customerArray[1].savingsBalance;
      checkingsBalance = customerArray[1].checkingsBalance;
      break;
    }
    else if (firstName == customerArray[2].firstName && lastName == customerArray[2].lastName) 
    {
      isMark = true;
      username = customerArray[2].username;
      password = customerArray[2].password;
      savingsBalance = customerArray[2].savingsBalance;
      checkingsBalance = customerArray[2].checkingsBalance;
      break;
    }
    else if (firstName == customerArray[3].firstName && lastName == customerArray[3].lastName) 
    {
      isLeeAnn = true;
      username = customerArray[3].username;
      password = customerArray[3].password;
      savingsBalance = customerArray[3].savingsBalance;
      checkingsBalance = customerArray[3].checkingsBalance;
      break;
    }
    else
    {
      cout << "Error: This name is not in our system. Please try again." << endl;
    }
  }
  while(cin);
}

//This function reads the information from the "accounts.dat" file into the customerArray of structures
void readInfo(ifstream& inFile)
{
  inFile.open("accounts.dat");
  for (int i = 0; i < size; i++)
  {
    inFile >> customerArray[i].firstName
           >> customerArray[i].lastName
           >> customerArray[i].username
           >> customerArray[i].password
           >> customerArray[i].savingsBalance
           >> customerArray[i].checkingsBalance;
  }
  inFile.close();
}


//This function updates the value of the array to be updated into the "accounts.dat" file
void updateValues()
{
  if(isRob == true)
  {
    customerArray[0].savingsBalance = savingsBalance;
    customerArray[0].checkingsBalance = checkingsBalance;
  }
  else if(isLisa == true)
  {
    customerArray[1].savingsBalance = savingsBalance;
    customerArray[1].checkingsBalance = checkingsBalance;
  }
  else if(isMark == true)
  {
    customerArray[2].savingsBalance = savingsBalance;
    customerArray[2].checkingsBalance = checkingsBalance;
  }
  else if(isLeeAnn == true)
  {
    customerArray[3].savingsBalance = savingsBalance;
    customerArray[3].checkingsBalance = checkingsBalance;
  }
}

//This function updates the "accounts.dat" file
void updateFile()
{
  outFile.open("accounts.dat");
  for (int i = 0; i < size; i++)
  {
    outFile << customerArray[i].firstName << " "
           << customerArray[i].lastName << " "
           << customerArray[i].username << " "
           << customerArray[i].password << " "
           << customerArray[i].savingsBalance << " "
           << customerArray[i].checkingsBalance;
    outFile << endl;
  }
  outFile.close();
}

