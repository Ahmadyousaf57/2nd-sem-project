#include <iostream>
  //---------------------------------------------//
 //----------for fileHandling Laibrary----------//
//---------------------------------------------//
#include <fstream>
#include <string>
  //-----------------------------------------------//
 //-for steric password and file Handling Laibaray//
//-----------------------------------------------//
#include <vector>
 //---------------------------------------------//
 //-----start Email condition laibrary----------//
//---------------------------------------------//
#include <regex>
  //---------------------------------------------//
 //------password steric form laibrary----------//
//---------------------------------------------//
#include <conio.h>
using namespace std;
   //----------------------------------------------//
  //---Abstract base class for User and Type of---// 
 //----inhertance class of Heirarchical----------//
//----------------------------------------------//
class User {
protected:
    string email;
    string pw;
public:
//-------------Parametrized Constructor--------------//
    User(string email, string pw) : email(email), pw(pw)  {}

 //-------------Virtual destructor--------------//
    virtual ~User() {}
 //-------------Abstarct class------------------//
    virtual void display() = 0;

 //-------------function get--------------------//
    string getId() const {
        return email;
    }

 //-------------function get--------------------//
    string getPW() const {
        return pw;
    }
};
  //---------------------------------------------//
 //-------------derived class for User----------//
//---------------------------------------------//
class LoginUser : public User {
public:
    LoginUser(string email, string pw) : User(email, pw) {}

    void display() override {
        cout << "Login User: " << email << endl;
    }
};
  //---------------------------------------------//
 //-------------derived class for User----------//
//---------------------------------------------//
class SignUpUser : public User {
public:
    SignUpUser(string email, string pw) : User(email, pw) {}

    void display() override {
        cout << "Sign Up User: " << email << endl;
    }
};
  //---------------------------------------------//
 //-----Encrypt password function part 2--------//
//---------------------------------------------//
char encryptCh(char ch, int shift) {
    if (isalpha(ch)) {
        char base = isupper(ch)? 'A' : 'a';
        return (ch - base + shift + 26) % 26 + base;
    }
    if (isdigit(ch)) {
        return (ch - '0' + shift + 10) % 10 + '0';
    }
    return ch;
}
  //--------------------------------------------//
 //-------Encrypt password function part 1------//
//---------------------------------------------//
string encrypt(const string& password, int shift) {
    string encrypted = "";
    for (size_t i = 0; i < password.length(); i++) {
        char ch = password[i];
        char encryptedChar = encryptCh(ch, shift);
        encrypted += encryptedChar;
    }
    return encrypted;
}
  //---------------------------------------------//
 //-----Decrypt password function part 2--------//
//---------------------------------------------//
char decryptCh(char ch, int shift) {
    if (isalpha(ch)) {
        char base = isupper(ch)? 'A' : 'a';
        return (ch - base - shift + 26) % 26 + base;
    }
    if (isdigit(ch)) {
        return (ch - '0' - shift + 10) % 10 + '0';
    }
    return ch;
}
  //---------------------------------------------//
 //------Decrypt password function part 1-------//
//---------------------------------------------//
string decrypt(const string& encrypted, int shift) {
    string decrypted = "";
    for (size_t i = 0; i < encrypted.length(); i++) {
        char ch = encrypted[i];
        char decryptedChar = decryptCh(ch, shift);
        decrypted += decryptedChar;
    }
    return decrypted;
}
  //---------------------------------------------//
 //-------------File handling class-------------//
//---------------------------------------------//
class FileHandler {
private:
    string filename;
public:

 //-------------Parametrized constructor of FileHandling--------------//
    FileHandler(string filename) : filename(filename) {}

 //-------------for data enter in FileHandling--------------//
    void writeUser(const User& user) {
 //-------------ofstream bulitin Class of Fstream--------------//
 //------------- ios::app for Mantain  previous data--------------//
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << user.getId() << "," << encrypt(user.getPW(), 3) << endl;
            file.close();
        } else {
            cout << "Unable to open file" << endl;
        }
    }
    vector<User*> readUsers() {
        vector<User*> users;
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t commaPos = line.find(',');
                string id = line.substr(0, commaPos);
                string encryptedPW = line.substr(commaPos + 1);
                string decryptedPW = decrypt(encryptedPW, 3);
                users.push_back(new LoginUser(id, decryptedPW));
            }
            file.close();
        } else {
            cout << "Unable to open file" << endl;
        }
        return users;
    }
};
  //---------------------------------------------//
 //-------------CHECK ERROR CLASS---------------//
//---------------------------------------------// 
class CheckError{
public:
 //------------- PASSWORD CHECK AND MATCH FUNCTION--------------//
void checkingpassword(string decryptedPassword,string password){
if(decryptedPassword==password){
 cout<<"You Are Successfull Login"<<endl;
}
else{
    cout<<"Your Password is Not Match"<<endl;
}
}
string matchpassword(string confirmpassword,string password){
if(!(confirmpassword==password)){
    cout<<"------------------------( Error )-----------------------------"<<endl;
    cout<<"Your Password is Not Match"<<endl;
    cout<<"--------------------------------------------------------------"<<endl;
    return password;
}
}
 //-------------EMAIL CHECK AND MATCH FUNCTION--------------//
void matchemail(string email,string confirmemail){
if(!(email==confirmemail)){
    cout<<"------------------------( Error )-----------------------------"<<endl;
    cout<<"Your Email And Confirm Email is Not Match"<<endl;
    cout<<"--------------------------------------------------------------"<<endl;
}
}
bool isValidEmail(const string& email) {
 //-------------Define the email pattern according to the general format--------------//
    const regex pattern(
        R"((\w+)(\.|\+)?(\w*)@(\w+)\.(\w+)(\.(\w+))?)"
    );
    return regex_match(email, pattern);
}
};
  //---------------------------------------------//
 //----------STERIC PASSWORD FORM Class---------//
//---------------------------------------------// 
class stericPassword{
    public:
    void SetStdinEcho(bool enable) {
#ifdef _WIN32
#endif
}
string getPassword() {
    string password;
    char ch;
    SetStdinEcho(false);
#ifdef _WIN32
    while (true) {
        ch = _getch();
        if (ch == '\r') { // Enter key is pressed
            cout << endl;
            break;
        } else if (ch == '\b') { // Backspace key is pressed
            if (!password.empty()) {
                cout << "\b \b"; // Move back, print space, move back again
                password;
            }
        } else {
            password.push_back(ch);
            cout << '*'; // Print asterisk
        }
    }
#endif
    SetStdinEcho(true);
    return password;
}
};
  //----------------------------------------------//
 //------------- SHOW PRODUCT CLASS--------------//
//----------------------------------------------// 
class product{
    public:
    void View(){
            cout<<"----------------------+ (Grocery Product) +------------------+"<<endl;
            cout<<"----------------------+-------------------+------------------+"<<endl;
            cout<<"|     Product Name    |       Quantity    |      Price       |"<<endl;
            cout<<"----------------------+-------------------+------------------+"<<endl;
            cout<<"|       Cake          |        45         |      5.0$        |"<<endl;
            cout<<"----------------------+-------------------+------------------+"<<endl;
            cout<<"|       Biscuts       |        20         |      12.0$       |"<<endl;
            cout<<"----------------------+-------------------+------------------+"<<endl;
            cout<<"|       Milk          |        30         |      30.0$       |"<<endl;
            cout<<"----------------------+-------------------+------------------+"<<endl;
            cout<<"|       Egg           |        10         |      24.0$       |"<<endl;
            cout<<"----------------------+-------------------+------------------+"<<endl;
    }
};
  //---------------------------------------------//
 //--------------Main Part start----------------//
//---------------------------------------------// 
int main() {

 //-------------Create object of  CLASS--------------//
    string Email,CEmail, PW,CPW,Name;
    CheckError CE;
    product p;

 //-------------Add shift=3 for password encrypted and decrypted--------------//
    int shift = 3;
    bool exit = false;

 //-------------create object of FilHandler class--------------//
//  E:\Study\2nd semester\oop lab\Project
    FileHandler fileHandler("E:\\study\\2nd semester\\oop lab\\project\\data.txt");

 //-------------Chose Selection--------------//
    while (!exit) {
        cout << "1. SignUp." << endl;
        cout << "2. LogIn." << endl;
        cout << "0. Exit." << endl;
        cout << "Enter Your Choice: ";
        int val;
        cin >> val;


 //-------------Signup--------------//
        if (val == 1) {
            cout<<"------------------------WELLCOME TO SIGNUP PAGE------------------------------------- "<<endl;
            cout << "Enter Name for SignUp: ";
            cin >> Name;
            cout << "Enter Email for SignUp: ";
            cin >> Email;
            if (!CE.isValidEmail(Email)) {
                cout<<"------------------------( Error )-----------------------------"<<endl;
                cout << "Your email address is inCorrect." <<endl;
                cout<<"--------------------------------------------------------------"<<endl;
            }
            cout << "Enter Confirm_Email for SignUp: ";
            cin >> CEmail;
            if (!CE.isValidEmail(CEmail)) {
                cout<<"------------------------( Error )-----------------------------"<<endl;
                cout << "Your email address is inCorrect." <<endl;
                cout<<"--------------------------------------------------------------"<<endl;
            }
            CE.matchemail(Email,CEmail);
            cout << "Enter Your Password For SignUp: ";
            stericPassword SP;
            PW=SP.getPassword();
            cout << "Enter Your Confirm_Password For SignUp: ";
            CPW=SP.getPassword();
            CE.matchpassword(CPW,PW);
            SignUpUser user(Email, PW);
//------------------start file Handling-------------// 
            fileHandler.writeUser(user);
            cout << "SignUp Successful" << endl;
        } 


 //-------------Login=1--------------//
        else if (val == 2) {
            cout<<"------------------------WELLCOME TO LOGIN PAGE------------------------------------- "<<endl;
            cout << "Enter Email for LogIn: ";
            cin >> Email;
            cout << "Enter Your Password For LogIn: ";
            cin >> PW;
            vector<User*> users = fileHandler.readUsers();
            bool found = false;
            for (User*user : users) {
                if (user->getId() == Email) {
                    if (user->getPW() == PW) {
                        cout << "Welcome!" << endl;
                        p.View();
                    } else {
                        cout<<"------------------------( Error )-----------------------------"<<endl;
                        cout << "Incorrect Password" << endl;
                        cout<<"--------------------------------------------------------------"<<endl;
                    }
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout<<"------------------------( Error )-----------------------------"<<endl;
                cout << "User Id not found, try again" << endl;
                cout<<"--------------------------------------------------------------"<<endl;
            }
            for (User* user : users) {
                delete user;
            }
        } 


 //-------------Exit=0--------------//
        else if (val == 0) {
            exit = true;
            cout << "Bye!" << endl;
        } else {
                cout<<"------------------------( Error )-----------------------------"<<endl;
                cout << "Invalid Input" << endl;
                cout<<"--------------------------------------------------------------"<<endl;
        }
    }
    return 0;
}