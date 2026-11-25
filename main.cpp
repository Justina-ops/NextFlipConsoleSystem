#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <ctime> // for decoration purpose

using namespace std;

#define SIZE 100 //global definition to determine the size of all the array in A2

// ============================================================
// ANSI Colour Codes (for decoration)
// ============================================================
// reset ANSI code setting
#define RESET       "\033[0m" 
// font style
#define BOLD        "\033[1m"
#define ITALIC      "\033[3m"
#define UNDERLINE   "\033[4m"
// font colour
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define MAGENTA     "\033[35m"
// font background colour
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"

string currentUser = "Sunny Ling Ling Ling"; //global definition with default value to determine the current user

// Define the FUNCTION PROTOTYPE for all the listed functions
int loadUserInfo(string userData[][4]);
void registerNewUser(string userData[][4], int& numUser);
int login(string userData[][4], int& numUser);
int loadFavInfo(string fav[][6], int& count);
void addFavList(string fav[][6], int& count);
void displayFavList(string fav[][6], int& count);
void deleteFavList(string fav[][6], int& count);
void loadPurchaseInfo(string merch[][3], double& credit, int& total_merch);
void addItem(string merch[][3], double& credit, int& total_merch);
void payment(string merch[][3], double& credit, int& total_merch);
void printReceipt(string merch[][3], double& credit, int& total_merch);

// ============================================================
// FUNCTION: validChar (input validation for char)
// ============================================================
char validChar(string prompt, string foundOptions, string colour) {

	char value;
	bool found;
	string input; // read input as string first to detect multi-character input like "AB"

	do {
		// display prompt with colour
		cout << colour << prompt << RESET;
		getline(cin, input); // read entire line including spaces

		// check if input is exactly one character
		if (input.length() != 1) {
			cout << RED << BOLD << "Invalid input. Please enter (" << foundOptions << ") only! o_o" << RESET << endl;
			found = false;
			continue; // skip to next iteration
		}

		value = toupper(input[0]); // // convert to uppercase for case-insensitive comparison

		// check if input matches any of the valid options
		found = false;
		for (int i = 0; i < foundOptions.length(); i++) {
			if (value == foundOptions[i]) {
				found = true; // valid input found
				break; // stop searching
			}
		}

		// display error if input is not in valid options
		if (!found)
			cout << RED << BOLD << "Invalid input. Please enter (" << foundOptions << ") only! o_o" << RESET << endl;

	} while (!found); // repeat until valid input

	return value;

}

// ============================================================
// FUNCTION: validInt (input validation for integer)
// ============================================================
int validInt(string prompt, int min, int max, string colour) {

	int value;
	string input; // read input as string first to detect mixed input like "2d"

	do {
		cout << colour << prompt << RESET;
		getline(cin, input); // read entire line including spaces

		// check if input is empty
		if (input.empty()) {
			cout << RED << BOLD << "Input cannot be empty. Please try again! o_o" << RESET << endl;
			value = min - 1;
			continue; // skip to next iteration
		}

		// check if all characters are digits
		bool isValid = true;
		for (int i = 0; i < input.length(); i++) {
			if (!isdigit(input[i])) {
				isValid = false; // non-digit character found
				break;
			}
		}

		// display error if input contains non-digit characters
		if (!isValid) {
			cout << RED << BOLD << "Invalid input. Please input only number! o_o" << RESET << endl;
			value = min - 1; // force loop to repeat
		}

		else {
			value = stoi(input); // safe to convert string to int after validation
			if (value < min || value > max) // check if input is within the valid range
				cout << RED << BOLD << "Please input a number between " << min << " and " << max << "! o_o" << RESET << endl;
		}

	} while (value < min || value > max);

	return value;

}

// ===============================================================
// FUNCTION: validDouble (input validation for double)
// =============================================================== 
double validDoubleMin(string prompt, double min, string colour) {

	double value;
	string input;// read input as string first to detect mixed input like "2d"

	do {
		cout << colour << prompt << RESET;
		getline(cin, input); // read entire line including spaces

		// check if input is empty
		if (input.empty()) {
			cout << RED << BOLD << "Input cannot be empty. Please try again! o_o" << RESET << endl;
			value = min - 1;
			continue; // skip to next iteration
		}

		// check if all characters are digits or decimal point
		bool isValid = true;
		int dotCount = 0;
		bool hasDigit = false;

		for (int i = 0; i < input.length(); i++) {
			if (input[i] == '.') {
				dotCount++;
				if (dotCount > 1) { // more than one decimal point is invalid
					isValid = false;
					break;
				}
			}

			else if (!isdigit(input[i])) {
				isValid = false; // non-digit character found
				break;
			}

			else
				hasDigit = true;  // valid digit found

		}

		// reject input if no digit was found (e.g. ".")
		if (!hasDigit) isValid = false;

		// display error if input contains non-digit or invalid decimal characters
		if (!isValid) {
			cout << RED << BOLD << "Invalid input. Please input only number! o_o" << RESET << endl;
			value = min - 1; // force loop to repeat
		}


		else {
			value = stod(input); // safe to convert string to double after validation
			if (value <= min) // check if input is greater than minimum
				cout << RED << BOLD << "Number must be greater than " << min << "! o_o" << RESET << endl;
		}

	} while (value <= min); // repeat until valid input

	return value;

}

// ===============================================================
// FUNCTION: validDouble (input validation for double with range)
// =============================================================== 
double validDouble(string prompt, double min, double max, string colour) {

	double value;
	string input; // read input as string first to detect mixed input like "2d"

	do {
		cout << colour << prompt << RESET;
		getline(cin, input); // read entire line including spaces

		// check if input is empty
		if (input.empty()) {
			cout << RED << BOLD << "Invalid input. Please input only number! o_o" << RESET << endl;
			value = min - 1;
			continue; // skip to next iteration
		}

		// check if all characters are digits or decimal point
		bool isValid = true;
		int dotCount = 0;
		bool hasDigit = false;

		for (int i = 0; i < input.length(); i++) {
			if (input[i] == '.') {
				dotCount++;
				if (dotCount > 1) { // more than one decimal point is invalid
					isValid = false;
					break;
				}
			}

			else if (!isdigit(input[i])) {
				isValid = false; // non-digit character found
				break;
			}

			else
				hasDigit = true;  // valid digit found
		}

		// reject input if no digit was found (e.g. ".")
		if (!hasDigit) isValid = false;

		// display error if input contains non-digit or invalid decimal characters
		if (!isValid) {
			cout << RED << BOLD << "Invalid input. Please input only number! o_o" << RESET << endl;
			value = min - 1; // force loop to repeat
		}

		else {
			value = stod(input); // safe to convert string to double after validation
			if (value < min || value > max) // check if input is within the valid range
				cout << RED << BOLD << "Please input a number between " << min << " and " << max << "! o_o" << RESET << endl;
		}

	} while (value < min || value > max); // repeat until valid input

	return value;

}

// ========================================================================================================
// FUNCTION: validCin (input validation for getline without empty or just space and remove redundant space)
// ========================================================================================================
string validCin(string prompt, string colour) {

	bool isValid = true;
	string message;

	do {
		int spaceNum = 0;
		isValid = true;

		cout << colour << prompt << RESET;
		getline(cin, message);


		// If the message is empty
		if (message.empty())
			isValid = false;
		else {
			// Check the input space number from last character
			for (int i = (int)message.length() - 1; i >= 0; i--) {
				if (message[i] == ' ')
					spaceNum++;
				else
					break;
			}
		}

		// Check the input has space only
		if (spaceNum == message.length())
			isValid = false;

		// Remove redundant space
		if (spaceNum > 0)
			message.erase(message.length() - spaceNum, spaceNum);

		if (!isValid)
			cout << RED << BOLD << "Input cannot be empty. Please try again! o_o" << RESET << endl;;

	} while (!isValid);

	return message;

}

// ==============
// MAIN FUNCTION
// ==============
int main() {

	// Define and initialise all the necessary variables
	int choice;
	int contRL = 2;
	char choose;
	string userData[SIZE][4];
	string fav[SIZE][6];
	int favCount = 0;
	int sel;
	int cont1 = 1;
	int cont = 1;
	int cont2 = 1;
	int sel1;
	string merch[SIZE][3];
	double credit = 0;
	int total_merch = 0;

	// User Module to handle new registration and login
	do {
		system("cls");

		// Function call loadUserInfo to read the registered users' details from "userInfo.txt"
		//The function return number of registered user(s) in the record
		int numUser = loadUserInfo(userData);

		// LOGIN MENU: To ask whether user want to register or login
		cout << RED << BOLD; // NextFlip ASCII art banner
		cout << "  _   _  _______  __  _______  _____  _      _____  _____  \n";
		cout << " | \\ | ||  _____| \\ \\/ /_   _||  ___|| |    |_   _||  _  \\ \n";
		cout << " |  \\| || |__      \\  /  | |  | |__  | |      | |  | |_| | \n";
		cout << " | . ` ||  __|     /  \\  | |  |  __| | |      | |  |  ___/ \n";
		cout << " | |\\  || |____   / /\\ \\ | |  | |    | |____ _| |_ | |     \n";
		cout << " |_| \\_||______| /_/  \\_\\|_|  |_|    |______||_____||_|    \n";
		cout << RESET << endl;
		cout << BG_WHITE << BOLD << BLACK;
		cout << "+-------------------------------------------------------------+" << endl;
		cout << "|                    NEXTFLIP - LOGIN MENU                    |" << endl;
		cout << "+-------------------------------------------------------------+" << endl;
		cout << RESET << endl;
		cout << "1. Register New User" << endl;
		cout << "2. Login" << endl;
		cout << "3. Quit" << endl << endl;

		// validated input: only accept 1-3, rejects non-numbers
		choice = validInt("Choice: ", 1, 3, RED);

		if (choice == 1) {
			// Function call registerNewUser to register new user
			registerNewUser(userData, numUser);

			// validated input: only accept 1-2, rejects non-numbers
			contRL = validInt("Do you want to continue register/login? (1-yes, 2-no): ", 1, 2, WHITE);

			if (contRL == 2)
				return 0;
		}

		else if (choice == 2) {
			// Function call login by returning a value for the if...else statement to handle possible conditions:
			// a. if username and password are correct
			// b. if username is correct but password is not correct
			// c. if username is not correct but password is correct
			// d. if username and password are not correct
			// Prompt back to the "LOGIN MENU" if meet with condition b, c and d
			// Proceed to next stage (favourite or merchandise) if succefully login
			// NOTE: set the global variable "currentUser" to the username that successfully login 
			int loginSuccess = login(userData, numUser);

			if (loginSuccess == 0) {
				// validated input: only accept 1-2, rejects non-numbers
				contRL = validInt("Do you want to continue register/login? (1-yes, 2-no): ", 1, 2, WHITE);

				if (contRL == 2)
					return 0;
			}
			else if (loginSuccess == 1)
				break;
		}
		else
			return 0;

	} while (contRL == 1);

	do {
		system("cls");

		// indicate name if user able to login
		cout << WHITE << BG_CYAN << BOLD;
		cout << "Name: " << currentUser << RESET << endl;
		// NextFlip ASCII art banner
		cout << RED << BOLD;
		cout << "  _   _  _______  __  _______  _____  _      _____  _____  \n";
		cout << " | \\ | ||  _____| \\ \\/ /_   _||  ___|| |    |_   _||  _  \\ \n";
		cout << " |  \\| || |__      \\  /  | |  | |__  | |      | |  | |_| | \n";
		cout << " | . ` ||  __|     /  \\  | |  |  __| | |      | |  |  ___/ \n";
		cout << " | |\\  || |____   / /\\ \\ | |  | |    | |____ _| |_ | |     \n";
		cout << " |_| \\_||______| /_/  \\_\\|_|  |_|    |______||_____||_|    \n";
		cout << RESET << endl;
		// menu to handle favourite list or purchase merchandise
		cout << BG_RED << BOLD << WHITE;
		cout << "+-------------------------------------------------------------+" << endl;
		cout << "|                    NEXTFLIP - MAIN MENU                     |" << endl;
		cout << "+-------------------------------------------------------------+" << endl;
		cout << RESET;
		cout << BOLD << WHITE << "~~Welcome to NextFlip~~" << RESET << endl;
		cout << CYAN << "A. " << WHITE << "Favourite List" << endl;
		cout << CYAN << "B. " << WHITE << "Purchase Merchandise" << endl;
		cout << CYAN << "C. " << WHITE << "Exit" << endl;
		cout << RESET << endl;

		// validated input: only accept A or B or C, rejects non-char
		choose = validChar("Choice: ", "ABC", YELLOW);
		system("cls");

		// if user choose favourite list
		if (choose == 'A') {
			do {
				system("cls");
				// function call loadFavInfo to read favourite(s) from "XXX MDInfo.txt"
				int hasFav = loadFavInfo(fav, favCount);

				// NextFlip ASCII art banner
				cout << WHITE << BG_CYAN << BOLD;
				cout << "Name: " << currentUser << " " << RESET << endl;
				cout << RED << BOLD;
				cout << "  _   _  _______  __  _______  _____  _      _____  _____  \n";
				cout << " | \\ | ||  _____| \\ \\/ /_   _||  ___|| |    |_   _||  _  \\ \n";
				cout << " |  \\| || |__      \\  /  | |  | |__  | |      | |  | |_| | \n";
				cout << " | . ` ||  __|     /  \\  | |  |  __| | |      | |  |  ___/ \n";
				cout << " | |\\  || |____   / /\\ \\ | |  | |    | |____ _| |_ | |     \n";
				cout << " |_| \\_||______| /_/  \\_\\|_|  |_|    |______||_____||_|    \n";
				cout << RESET << endl;
				// menu for user to select display, add or delete favourite
				cout << BG_CYAN << BOLD << WHITE;
				cout << "+-------------------------------------------------------------+" << endl;
				cout << "|                  NEXTFLIP - FAVOURITE LIST                  |" << endl;
				cout << "+-------------------------------------------------------------+" << endl;
				cout << RESET;
				cout << CYAN << "1. " << WHITE << "Display Favourite List" << endl;
				cout << CYAN << "2. " << WHITE << "Add Favourite List" << endl;
				cout << CYAN << "3. " << WHITE << "Delete Favourite List" << endl;
				cout << CYAN << "4. " << WHITE << "Back" << endl;
				cout << RESET << endl;

				// validated input: only accept 1-4, rejects non-numbers
				sel = validInt("Select: ", 1, 4, YELLOW);
				system("cls");

				// if list is empty and user selects Display or Delete, show warning
				if ((sel == 1 || sel == 3) && hasFav == 0) {
					cout << RED << BOLD << " [!] There is no favourite in the list! o_o" << RESET << endl;
					system("PAUSE");
					continue;
				}

				if (sel == 1)
					displayFavList(fav, favCount); //Function call displayFavList to display all the favourite(s)
				else if (sel == 2)
					addFavList(fav, favCount);     //Function call addFavList to add favourite 
				else if (sel == 3)
					deleteFavList(fav, favCount);  //Function call deleteFavList to delete favourite
				else break; //Break the loop

			} while (cont1 == 1);
		}

		// if user choose purchase merchandise
		else if (choose == 'B') {
			system("cls");

			do {
				// function call loadPurchaseInfo to load merchandise details from "XXX PurInfo.txt"
				loadPurchaseInfo(merch, credit, total_merch);

				system("cls");

				// NextFlip ASCII art banner
				cout << RED << BOLD;
				cout << "  _   _  _______  __  _______  _____  _      _____  _____  \n";
				cout << " | \\ | ||  _____| \\ \\/ /_   _||  ___|| |    |_   _||  _  \\ \n";
				cout << " |  \\| || |__      \\  /  | |  | |__  | |      | |  | |_| | \n";
				cout << " | . ` ||  __|     /  \\  | |  |  __| | |      | |  |  ___/ \n";
				cout << " | |\\  || |____   / /\\ \\ | |  | |    | |____ _| |_ | |     \n";
				cout << " |_| \\_||______| /_/  \\_\\|_|  |_|    |______||_____||_|    \n";
				cout << RESET << endl;
				//Menu to choose add credit/merchandise or make payment
				cout << BG_BLUE << BOLD << WHITE;
				cout << "+-------------------------------------------------------------+" << endl;
				cout << "|               NEXTFLIP - PURCHASE MERCHANDISE               |" << endl;
				cout << "+-------------------------------------------------------------+" << endl;
				cout << RESET << endl;
				cout << "[1] Add Credit/Merchandise" << endl;
				cout << "[2] Make Payment" << endl;
				cout << "[3] Back" << endl << endl;

				// validated input: only accept 1-3, rejects non-numbers
				sel1 = validInt("Choice: ", 1, 3, YELLOW);

				// select the function according to the user input
				if (sel1 == 1)
					addItem(merch, credit, total_merch); // function call addItem to add credit or merchandise to the account
				else if (sel1 == 2)
					payment(merch, credit, total_merch); // function call payment to make payment for the merchandise
				else
					break; //Break the loop

			} while (cont2 == 1);
		}

		else return 0;

	} while (cont == 1);

	return 0;
}

// function loadUserInfo --> read all the registered users' details from "userInfo.txt" and store the data into the respective parameters
// userData is a two dimensional array with row and column ([][4]), 
// row is depends on the number of users, columns is to store name, email, username and password
// the function will return the total number of registered user in the file
// "userInfo.txt" is created if it doesn't exist yet 

// ============================================================
// FUNCTION: loadUserInfo
// ============================================================
int loadUserInfo(string userData[][4]) {

	// i refers to rows and j refers to columns
	int i = 0, j = 0;
	string line;

	ifstream readFile;
	readFile.open("userInfo.txt");

	// Check the userInfo.txt is exist or not, if not then create one
	if (readFile.fail()) {

		ofstream newFile("userInfo.txt"); // If file doesn't exist → create empty file

		if (newFile.fail()) {
			cout << BG_RED << WHITE << BOLD << " [!] Unable to create file! o_o" << "userInfo.txt" << RESET << endl;
		}
		else {
			newFile.close();
		}
		return 0;
	}

	// Read the data 
	while (getline(readFile, line)) {

		userData[i][j] = line;

		j++;
		if (j == 4)
		{
			i++;
			j = 0;
		}
	}
	readFile.close();


	// Return number of number that already register 
	return i;
}

// function registerNewUser --> To register new user and save it to "userInfo.txt"
// numUser should be a reference parameter
// format of email is checked whether correct or not; E.g. @ must exists in the email
// password is at least 8 characters (1 symbol, 1 uppercase letter, 1 number)
// name, email or username is checked whether exist in the list. 
// E.g., "Sunny Ling Ling Ling" is already exist in the list, hence new user is not allowed to register using the same name.

// ============================================================
// FUNCTION: registerNewUser
// ============================================================
void registerNewUser(string userData[][4], int& numUser) {

	// Variables
	string name, username, email, password;
	int confRegister;

	// Check number of users is bigger than SIZE
	if (numUser >= SIZE) {
		cout << RED << BOLD << "The user register list is full! o_o" << RESET << endl;
		system("PAUSE");
		return;
	}

	// Name Input
	while (true)
	{
		bool repeatName = true;

		name = validCin("Name: ", WHITE);

		// Check has it repeat name
		for (int i = 0; i < numUser; i++) {
			if (name == userData[i][0]) {
				cout << RED << BOLD << "This name is already taken. Please key in another name." << RESET << endl;;
				repeatName = false;
			}
		}

		if (repeatName)
			break;
	}

	// Email Input
	while (true)
	{
		bool repeatEmail = true, validEmail = true, validSymbol = true, existSymbol1 = false, existSymbol2 = false;

		// l refres the position of '@', r refers the position of '.'
		int l = 0, r = 0;

		cout << "Email: ";
		cin >> email;
		cin.ignore();
		// Check the is valid or not  //E11
		for (int i = 0; i < email.length(); i++) {
			// Check has it other symbol (valid symbol: '@', '.')
			// Check has it uppercase
			if ((ispunct(email[i]) && !(email[i] == '@' || email[i] == '.')) || isupper(email[i]))
				validSymbol = false;

			if (email[i] == '@') {
				// Check it only has one '@'
				if (existSymbol1 == false) {
					l = i;
					existSymbol1 = true;
				}
				else
					validSymbol = false;
			}
			else if (email[i] == '.') {
				// Check it only has one '.'
				if (existSymbol2 == false) {
					r = i;
					existSymbol2 = true;
				}
				else
					validSymbol = false;
			}
		}
		// Check '@' is in front of 'n'
		if (l > r)
			validEmail = false;
		// Check '@' is not the first char of the email 
		if (email[0] == '@')
			validEmail = false;
		// Check '.' is not the last char of the email
		if (email[email.length() - 1] == '.')
			validEmail = false;


		// Check has it repeat email
		for (int i = 0; i < numUser; i++) {
			if (email == userData[i][1]) {
				cout << RED << BOLD << "This email is already taken. Please key in another email." << RESET << endl;;
				repeatEmail = false;
			}
		}

		if (repeatEmail && validEmail && validSymbol && existSymbol1 && existSymbol2)
			break;
		else
			cout << RED << BOLD << "Invalid email. Please key in again! " << RESET << endl;
	}

	// Username Input
	while (true)
	{
		bool repeatName = true, validUsername = true;

		// Input
		username = validCin("Username: ", WHITE);

		// Check has it repeat username
		for (int i = 0; i < numUser; i++) {
			if (username == userData[i][2]) {
				cout << RED << BOLD << "This username is already taken. Please key in another username." << RESET << endl;
				repeatName = false;
			}
		}

		if (repeatName && validUsername)
			break;
	}

	// Password Input
	while (true) {
		bool upper = 0, symbol = 0, number = 0;

		cout << "Password (At least 8 charaters (1 symbol, 1 uppercase letter, 1 number)): ";
		cin >> password;
		cin.ignore();

		if (password.length() < 8) {
			cout << RED << BOLD << "The length of password is less than 8. Please try again" << RESET << endl;
			continue;
		}

		for (int i = 0; i < password.length(); i++) {
			if (isupper(password[i]))
				upper = 1;
			else if (isdigit(password[i]))
				number = 1;
			else if (ispunct(password[i]))
				symbol = 1;
		}

		if (symbol && number && upper)
			break;
		else
			cout << RED << BOLD << "Not eligible password. Please try again" << RESET << endl;
	}

	// User confirm registration
	confRegister = validInt("Confirm registration (1-yes, 2-no): ", 1, 2, WHITE);

	// If comfirm the register
	if (confRegister == 1) {

		// Record the user sign in data;
		ofstream writeIn;
		writeIn.open("userInfo.txt", ios::app);

		// Check can it open usertxt or not
		if (writeIn.fail())
			cout << RED << BOLD << "Unable to open the userInfo.txt file! " << RESET << endl;
		else {
			// Write the data into the userInfo.txt
			writeIn << name << '\n';
			writeIn << email << '\n';
			writeIn << username << '\n';
			writeIn << password << '\n';

			writeIn.close();

			// Update userData 

			userData[numUser][0] = name;
			userData[numUser][1] = email;
			userData[numUser][2] = username;
			userData[numUser][3] = password;
			numUser++;
		}
	}
}

// function login --> For user to login with the registered username and password
// the function will return a value to indicate login success or login fail   

// ============================================================
// FUNCTION: login
// ============================================================
int login(string userData[][4], int& numUser) {

	string username, password;
	bool validUsername = false;
	int numLoginUser = -1;
	int loginSuccess = 0;

	cout << "Username: ";
	getline(cin, username);

	cout << "password: ";
	cin >> password;
	cin.ignore();

	// Check the username 
	for (int i = 0; i < numUser; i++) {
		if (username == userData[i][2]) {
			validUsername = true;
			numLoginUser = i;
		}
	}

	// Check the password 
	if (numLoginUser == -1)
		cout << RED << BOLD << "Username or Password not correct! " << RESET << endl;
	else if (password == userData[numLoginUser][3]) {
		currentUser = username;
		loginSuccess = 1;
	}
	else
		cout << "Username or Password not correct! " << endl;

	if (loginSuccess == 1) {
		cout << "Login successfully! " << endl;
		system("pause");
	}

	// Return value of login success
	return loginSuccess;
}

// function loadFavInfo --> read the favourites saved in "XXX MDInfo.txt"
// fav is two dimensional array with rows and columns ([][6])
// count is a reference parameter
// the function will check whether any favorites exist in the file (it can be empty) and return a value to indicate whether it is empty
// a new text file is created using ofstream for current login user if the text file does not exist
// a global variable named "currentUser" stores the username that successfully login
// if the text file exists, read the records into the respective parameters 

// ============================================================
// FUNCTION: loadFavInfo
// ============================================================
int loadFavInfo(string fav[][6], int& count) {
	count = 0;

	// Build personalised filename using currentUser global variable
	string filename = currentUser + " MDInfo.txt";

	ifstream inFile(filename);

	if (inFile.fail()) {
		ofstream newFile(filename); // If file doesn't exist → create empty file

		if (newFile.fail()) {
			cout << BG_RED << WHITE << BOLD << " [!] Unable to create file! o_o" << filename << RESET << endl;
		}
		else {
			newFile.close();

		}
		return 0;
	}

	// Read file line-by-line into 2D array
	while (count < SIZE && getline(inFile, fav[count][0])) { // catgory
		if (!getline(inFile, fav[count][1])) break;         // title
		if (!getline(inFile, fav[count][2])) break;        // year
		if (!getline(inFile, fav[count][3])) break;       // language
		if (!getline(inFile, fav[count][4])) break;      // description
		if (!getline(inFile, fav[count][5])) break;     // rating
		count++;
	}
	inFile.close();

	// Return 1 if favourites exist, 0 if file was empty
	if (count == 0)
		return 0;
	else
		return 1;

}

// function addFavList --> add favourite to the list
// count is a reference parameter
// the text file ("XXX MDInfo.txt") is updated after add favourite

// ============================================================
// FUNCTION: addFavList
// ============================================================
void addFavList(string fav[][6], int& count) {

	// Prevent writing beyond array boundary
	if (count >= SIZE) {
		cout << BG_RED << WHITE << BOLD << "[!] Favourite list is full! o_o" << RESET << endl;
		system("PAUSE");
		return;
	}

	cout << BG_MAGENTA << WHITE << BOLD;
	cout << "================================================================" << endl;
	cout << "              ADD NEW FAVOURITE DRAMA OR MOVIE                  " << endl;
	cout << "================================================================" << endl;
	cout << RESET;

	// ----- Category: only "Drama" or "Movie" accepted -----
	// Use while(true) + break to keep prompting until valid category is entered
	while (true) {
		string temp = validCin("Category: ", CYAN);

		// Convert to lowercase for flexible input
		// e.g. user can enter "DRAMA", "drama", "Drama" - all accepted
		string lower = temp;
		for (int i = 0; i < (int)lower.length(); i++)
			lower[i] = tolower(lower[i]);

		if (lower == "drama") {
			fav[count][0] = "Drama";
			break;
		}
		else if (lower == "movie") {
			fav[count][0] = "Movie";
			break;
		}
		else {
			cout << RED << BOLD << "[!] Invalid category! Please enter Drama or Movie only! o_o" << RESET << endl;
		}
	}

	// ----- Title: cannot be empty -----
	fav[count][1] = validCin("Title: ", CYAN);

	// ----- Year: must be a valid integer between 1800 and 2026 -----
	fav[count][2] = to_string(validInt("Year: ", 1800, 2026, CYAN));

	// ----- Language: cannot be empty -----
	fav[count][3] = validCin("Language: ", CYAN);

	// ----- Description: cannot be empty -----
	fav[count][4] = validCin("Description: ", CYAN);

	// ----- Rating: must be between 0.0 and 10.0, stored to 1 decimal -----
	double rating = validDouble("Rating: ", 0.0, 10.0, CYAN);
	rating = ((int)(rating * 10)) / 10.0;  // Truncate to 1 decimal place, e.g. 9.35 -> 9.3

	string r = to_string(rating);  // Convert to string and keep only 1 decimal place for file storage
	fav[count][5] = r.substr(0, r.find(".") + 2);  // e.g. "9.300000" -> "9.3"


	// ----- Confirm before saving -----
	cout << YELLOW << "--------------------------------------------------------" << endl;
	cout << BG_GREEN << WHITE << BOLD << endl;
	int confirm = validInt("Confirm add? (1-yes, 2-no): ", 1, 2, WHITE);

	if (confirm == 1) {

		// Overwrite the file with the full updated list
		string filename = currentUser + " MDInfo.txt";
		ofstream outFile(filename);

		if (outFile.fail()) {
			cout << RED << "[!] Unable to open file for writing! o_o" << RESET << endl;
			system("PAUSE");
			return;
		}

		count++; // Increment count only after file is successfully opened

		for (int i = 0; i < count; i++) {
			for (int j = 0; j < 6; j++)
				outFile << fav[i][j] << endl;
		}
		outFile.close();

		// Show success message and summary of added entry
		cout << BG_GREEN << WHITE << BOLD << "\nFavourite added successfully ^_^   " << RESET << endl;
		cout << CYAN << BOLD << "[INFO] Total favourites now: " << count << RESET << endl;
		cout << YELLOW << BOLD << "---------------------------------------------------------------" << endl;
		cout << CYAN << BOLD << "Category    : " << fav[count - 1][0] << RESET << endl;
		cout << CYAN << BOLD << "Title       : " << fav[count - 1][1] << RESET << endl;
		cout << CYAN << BOLD << "Year        : " << fav[count - 1][2] << RESET << endl;
		cout << CYAN << BOLD << "Language    : " << fav[count - 1][3] << RESET << endl;
		cout << CYAN << BOLD << "Description : " << fav[count - 1][4] << RESET << endl;
		cout << CYAN << BOLD << "Rating      : " << fav[count - 1][5] << RESET << endl;
		cout << CYAN << BOLD << "---------------------------------------------------------------" << RESET << endl;

	}
	else {
		cout << BG_RED << WHITE << "\nAdd cancelled. -_-" << RESET << endl;
	}
	system("PAUSE");
}

// function displayFavList --> display all the favourites store in the text file ("XXX MDInfo.txt")
// A message pop out when there is no favourite in the list

// ============================================================
// FUNCTION: displayFavList
// ============================================================
void displayFavList(string fav[][6], int& count) {

	cout << BG_MAGENTA << WHITE << BOLD;
	cout << "================================================================" << endl;
	cout << "                    DISPLAY FAVOURITE LIST                      " << endl;
	cout << "================================================================" << endl;
	cout << RESET;
	cout << endl;

	if (count == 0) {
		// No favourites found - notify user
		cout << BG_RED << WHITE << BOLD << "[!] There is no favourite in the list! o_o" << RESET << endl;
		system("PAUSE");
		return;
	}
	cout << CYAN << "[INFO] Total favourites: " << count << RESET << endl << endl;

	// Loop through all entries and display each one
	for (int i = 0; i < count; i++) {
		cout << YELLOW << BOLD << "-------------------------------------------------------------" << RESET << endl;
		cout << BOLD << i + 1 << ". " << RESET << endl;
		cout << BOLD << "Category   : " << fav[i][0] << RESET << endl;
		cout << BOLD << "Title      : " << fav[i][1] << RESET << endl;
		cout << BOLD << "Year       : " << fav[i][2] << RESET << endl;
		cout << BOLD << "Language   : " << fav[i][3] << RESET << endl;
		cout << BOLD << "Description: " << fav[i][4] << RESET << endl;
		cout << BOLD << "Rating     : " << fav[i][5] << RESET << endl;
		cout << endl;
	}
	cout << YELLOW << BOLD << "-------------------------------------------------------------" << RESET << endl;
	system("PAUSE");
}


// function deleteFavList --> delete selected favourite in the list 
// count is a reference parameter
// the text file ("XXX MDInfo.txt") is updated after delete favourite 

// ============================================================
// FUNCTION: deleteFavList
// ============================================================
void deleteFavList(string fav[][6], int& count) {

	cout << BG_MAGENTA << WHITE << BOLD;
	cout << "==============================================================" << endl;
	cout << "                   DELETE FAVOURITE LIST                      " << endl;
	cout << "==============================================================" << endl;
	cout << RESET;
	cout << endl;

	if (count == 0) {
		// No favourites to delete
		cout << BG_RED << WHITE << BOLD << "[!] There is no favourite in the list! o_o" << RESET << endl;
		system("PAUSE");
		return;
	}

	// Show only titles (not full details) for easier selection
	for (int i = 0; i < count; i++) {
		cout << YELLOW << i + 1 << ". " << fav[i][1] << RESET << endl;
	}

	// Validated input: only accepts 1 to count, rejects non-numbers
	int del = validInt("\nDelete: ", 1, count, YELLOW);

	// Validated input: only accepts 1 to 2, rejects non-numbers
	cout << BG_GREEN << WHITE << BOLD << endl;
	int confirm = validInt("Confirm delete? (1-yes, 2-no): ", 1, 2, WHITE);

	if (confirm == 1) {
		// Shift all entries after the deleted one up by one position
		// e.g. delete index 1: [0][1][2][3] -> [0][2][3]
		for (int i = del - 1; i < count - 1; i++) {
			for (int j = 0; j < 6; j++) {
				fav[i][j] = fav[i + 1][j]; // overwrite current with next entry
			}
		}
		count--; // Reduce count after deletion

		// Overwrite the file with the updated list
		string filename = currentUser + " MDInfo.txt";
		ofstream outFile(filename);

		if (outFile.fail()) {
			cout << RED << " [!] Unable to open file for writing! o_o" << RESET << endl;
			system("PAUSE");
			return;
		}

		for (int i = 0; i < count; i++) {
			for (int j = 0; j < 6; j++) {
				outFile << fav[i][j] << endl;
			}
		}
		outFile.close();

		cout << BG_GREEN << WHITE << "Favourite deleted successfully ^_^" << RESET << endl;
		cout << CYAN << "[INFO] Remaining favourites: " << count << RESET << endl;
	}
	else {
		cout << BG_RED << WHITE << "\nDelete cancelled -_-" << RESET << endl;
	}
	system("PAUSE");
}

// function loadPurchaseInfo --> read the credit and merchandises saved in "XXX PurInfo.txt"
// merch is two dimensional array with rows and columns ([][3])
// row is depends on the number of users and columns is to store name of merchandise, quantity and price (per piece)
// credit and total_merch are reference parameters
// a new text file is created using ofstream for current login user if the text file does not exist
// credit 0 is added into the text file (without the merchandise) if the text file is created for the first time
// a global variable named "currentUser" is defined before function prototype and stores the username that successfully login and can be used to create the new text file 
// the records are read if the text file exists and load into the respective parameters

// ============================================================
// FUNCTION: loadPurchaseInfo
// ============================================================
void loadPurchaseInfo(string merch[][3], double& credit, int& total_merch) {

	ifstream inFile(currentUser + " PurInfo.txt"); // try to open the purchase info file for current user

	// if file does not exist, create a new file with credit = 0
	if (inFile.fail()) {
		ofstream outFile(currentUser + " PurInfo.txt"); // create new file
		outFile << 0 << endl; // write initial credit as 0
		outFile.close();

		credit = 0;
		total_merch = 0;
	}

	// if file exists, read the records
	else {
		inFile >> credit; // read credit balance from first line
		inFile.ignore();

		total_merch = 0; // reset merchandise count before reading

		// temporary variables to hold each merchandise record
		string name;
		int qty;
		double price;

		// read each merchandise record until end of file, ensure not more than the array size
		while (total_merch < SIZE && getline(inFile, name)) {
			inFile >> qty;
			inFile >> price;
			inFile.ignore();

			// store merchandise details into 2D array
			merch[total_merch][0] = name; // column 0: name
			merch[total_merch][1] = to_string(qty); // column 1: quantity
			merch[total_merch][2] = to_string(price); // column 2: price

			total_merch++; // increment merchandise count
		}

		inFile.close();
	}

}

// function addItem --> add credit or add merchandise and saved to "XXX PurInfo.txt"
// a menu for user to choose whether to add credit or merchandise
// "XXX PurInfo.txt" is updated after add credit or add merchandise
// credit and total_merch are reference parameters
// credit value is displayed all the time on the screen when it is in add section
// all merchandise added is listed out when add merchandise

// ============================================================
// FUNCTION: addItem
// ============================================================
void addItem(string merch[][3], double& credit, int& total_merch) {

	int choice;
	int cont = 1;
	int conf;

	do {
		// display add item menu
		system("cls");
		cout << fixed << setprecision(2);
		cout << BG_GREEN << BLACK << ITALIC << "Current Credit: RM " << credit << RESET << endl;
		cout << "================================================" << endl;
		cout << BG_YELLOW << BOLD << WHITE;
		cout << "+----------------------------------------------+" << endl;
		cout << "|            NEXTFLIP - ADD ITEM MENU          |" << endl;
		cout << "+----------------------------------------------+" << endl;
		cout << RESET << endl;
		cout << "[1] Add Credit" << endl;
		cout << "[2] Add Merchandise" << endl;
		cout << "[3] Back" << endl << endl;

		// Validated input: only accepts 1 to 3, rejects non-numbers
		choice = validInt("Choice: ", 1, 3, YELLOW);

		system("cls");

		// add credit
		if (choice == 1) {
			double amount; // amount of credit to add

			// display current credit
			cout << fixed << setprecision(2);
			cout << BG_GREEN << BLACK << ITALIC << "Current Credit: RM " << credit << RESET << endl;
			cout << "================================================" << endl << endl;

			// get amount to add from user
			amount = validDoubleMin("Credit to add: RM ", 0, WHITE);

			// ask user to confirm
			cout << endl;
			cout << "================================================" << endl << endl;
			conf = validInt("Confirm? (1-yes, 2-no): ", 1, 2, YELLOW);

			if (conf == 1) {
				// update credit balance
				credit += amount;

				// save updated credit and existing merchandise to file
				ofstream outFile(currentUser + " PurInfo.txt");
				outFile << credit << endl;

				for (int i = 0; i < total_merch; i++) {
					outFile << merch[i][0] << endl;
					outFile << merch[i][1] << endl;
					outFile << fixed << setprecision(2) << stod(merch[i][2]) << endl;
				}

				outFile.close();

				cout << GREEN << BOLD << "Credit added successfully! ^_^" << RESET << endl;
				system("pause");
			}

			else {
				// user cancelled the action
				cout << RED << BOLD << "Cancelled~  o_o " << RESET << endl;
				system("pause");
			}
		}

		// add merchandise
		else if (choice == 2) {
			string name;
			int qty;
			double price;

			// display current credit
			cout << fixed << setprecision(2);
			cout << BG_GREEN << BLACK << ITALIC << "Current Credit: RM " << credit << RESET << endl;
			cout << "================================================" << endl << endl;

			// display existing merchandise list
			if (total_merch != 0) {
				for (int i = 0; i < total_merch; i++) {
					cout << BG_YELLOW << BLACK << "~Item " << i + 1 << "~" << RESET << endl;
					cout << "Name: " << merch[i][0] << endl;
					cout << "Quantity: " << merch[i][1] << endl;
					cout << fixed << setprecision(2);
					cout << "Price (per item): RM " << stod(merch[i][2]) << endl;
				}
			}

			// get new merchandise details from user
			cout << endl;
			cout << "================================================" << endl;
			cout << ITALIC << BOLD << BG_BLUE << "~Add Merchandise~" << RESET << endl << endl;

			name = validCin("Name: ", WHITE);
			qty = validInt("Quantity: ", 1, 9999, WHITE); // validated input: only accepts 1 to 9999, rejects non-numbers
			price = validDoubleMin("Price (per piece): RM ", 0, WHITE); // validated input: only accepts value greater than 0, rejects non-numbers

			// ask user to confirm
			cout << "================================================" << endl << endl;
			conf = validInt("Confirm? (1-yes, 2-no): ", 1, 2, YELLOW); // validated input: only accepts 1 to 2, rejects non-numbers

			if (conf == 1) {

				// check if total merch exceed array size
				if (total_merch >= SIZE) {
					cout << RED << BOLD << "Merchandise list is full! o_o" << RESET << endl;
					system("pause");
					return;
				}

				// add new merchandise to array
				merch[total_merch][0] = name;
				merch[total_merch][1] = to_string(qty);
				merch[total_merch][2] = to_string(price);

				total_merch++;

				// save updated merchandise list to file
				ofstream outFile(currentUser + " PurInfo.txt");
				outFile << credit << endl;

				for (int i = 0; i < total_merch; i++) {
					outFile << merch[i][0] << endl;
					outFile << merch[i][1] << endl;
					outFile << fixed << setprecision(2) << stod(merch[i][2]) << endl;
				}

				outFile.close();

				cout << GREEN << BOLD << "Merchandise added successfully! ^_^" << RESET << endl;
				system("pause");
			}

			else {
				// user cancelled the action
				cout << RED << "Cancelled~  o_o " << RESET << endl;
				system("pause");
			}
		}

		// back
		else
			cont = 0; // exit loop and return to main menu

	} while (cont == 1);

}

// function payment --> make payment for the merchandise
// available credit and also all the merchandise in the list are shown
// the total price of the merchandise (sum of all merchandise) is displayed
// if user confirm payment, it is checked whether user has sufficient credit to pay
// a message pop out to stop the payment if insufficient credit else proceed if sufficient credit
// a receipt is printed for the payment
// the deducted credit is updated in "XXX PurInfo.txt"
// Merchandise list in "XXX PurInfo.txt" is cleared if payment is successfully made
// a message pop out if there is no merchandise in the list
// credit and total_merch are reference parameters


// ============================================================
// FUNCTION: payment
// ============================================================
void payment(string merch[][3], double& credit, int& total_merch) {

	system("cls");

	// display current credit balance
	cout << fixed << setprecision(2);
	cout << BG_GREEN << BLACK << ITALIC << "Current Credit: RM " << credit << RESET << endl;
	cout << "================================================" << endl << endl;

	// check if there are any merchandise to checkout
	if (total_merch != 0) {
		double total_price = 0;
		int conf;

		// display all merchandise details and calculate total price
		for (int i = 0; i < total_merch; i++) {
			int qty = stoi(merch[i][1]); // convert quantity from string to int
			double price = stod(merch[i][2]); // convert price from string to double

			// display individual item details
			cout << BG_YELLOW << BLACK << "~Item " << i + 1 << "~" << RESET << endl;
			cout << "Name: " << merch[i][0] << endl;
			cout << "Quantity: " << qty << endl;
			cout << fixed << setprecision(2);
			cout << "Price (per item): RM " << price << endl;

			total_price += qty * price; // accumulate total price
		}

		// display total price calculation
		cout << endl;
		cout << "================================================" << endl;
		cout << RED << BOLD << ITALIC << "Total price (ALL):" << RESET << endl;

		for (int i = 0; i < total_merch; i++) {
			int qty = stoi(merch[i][1]);
			double price = stod(merch[i][2]);

			// display each item's calculation
			cout << "(" << qty << " * RM " << price << ")";
			if (i != total_merch - 1)
				cout << " + "; // add plus sign between items
			else
				cout << fixed << setprecision(2) << " = " << "RM " << total_price << endl;
		}

		// ask user to confirm payment
		cout << "================================================" << endl << endl;
		conf = validInt("Confirm payment? (1-yes, 2-no): ", 1, 2, YELLOW); // validated input: only accepts 1 to 2, rejects non-numbers

		if (conf == 1) {
			// check if user has sufficient credit
			if (total_price > credit)
				cout << RED << BOLD << "Credit is insufficient! o_o" << RESET << endl;

			else {
				cout << GREEN << BOLD << "Complete payment! Please check the receipt for details! ^_^" << RESET << endl;

				// call print receipt function to print receipt to file
				printReceipt(merch, credit, total_merch);

				// calculate the credit left after payment
				credit -= total_price;
				// clear merchandise list after successful payment
				total_merch = 0;

				// save updated credit to file with empty merchandise list
				ofstream outFile(currentUser + " PurInfo.txt");
				outFile << fixed << setprecision(2) << credit << endl;
				outFile.close();
			}
		}

		else
			cout << RED << BOLD << "Cancelled~  o_o " << RESET << endl;
	}

	else // if no merchandise to checkout
		cout << RED << BOLD << "No items to be check out. Please add some merchandise before making payment! o_o" << RESET << endl;

	system("pause");

}

// function printReceipt --> print the receipt of purchase for the merchandise "XXX Receipt.txt"

// ============================================================
// FUNCTION: printReceipt
// ============================================================
void printReceipt(string merch[][3], double& credit, int& total_merch) {

	// get current date and time for decoration purpose
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);

	double total_price = 0;

	// open receipt file for writing (creates new file or overwrites existing)
	ofstream outFile(currentUser + " Receipt.txt");

	// print receipt header
	outFile << "====================================================================" << endl;
	outFile << "                       NEXTFLIP RECEIPT                            " << endl;
	outFile << "====================================================================" << endl;
	// print customer username and their available credit
	outFile << "Customer: " << currentUser << "     Available Credit: RM " << credit << endl;
	outFile << "====================================================================" << endl;
	// print receipt generated datetime (for decoration)
	outFile << "Date: "
		<< setw(2) << setfill('0') << localTime.tm_mday << "/"
		<< setw(2) << setfill('0') << localTime.tm_mon + 1 << "/"
		<< localTime.tm_year + 1900 << endl;
	outFile << "Time: "
		<< setw(2) << setfill('0') << localTime.tm_hour << ":"
		<< setw(2) << setfill('0') << localTime.tm_min << ":"
		<< setw(2) << setfill('0') << localTime.tm_sec << endl;
	outFile << setfill(' ');
	outFile << "--------------------------------------------------------------------" << endl;

	// print each merchandise details and calculate total price
	for (int i = 0; i < total_merch; i++) {

		int qty = stoi(merch[i][1]); // convert quantity from string to int
		double price = stod(merch[i][2]); // convert price from string to double

		// write individual item details to receipt
		outFile << "~Item " << i + 1 << "~" << endl;
		outFile << "Name: " << merch[i][0] << endl;
		outFile << "Quantity: " << qty << endl;
		outFile << fixed << setprecision(2);
		outFile << "Price (per item): RM " << price << endl;

		total_price += qty * price; // accumulate total price

	}

	// print total price of all items
	outFile << "--------------------------------------------------------------------" << endl;
	outFile << "Total price (ALL):" << endl;

	for (int i = 0; i < total_merch; i++) {

		int qty = stoi(merch[i][1]);
		double price = stod(merch[i][2]);

		outFile << "(" << qty << " * RM " << price << ")";

		if (i != total_merch - 1)
			outFile << " + ";
		else
			outFile << fixed << setprecision(2) << " = " << "RM " << total_price << endl;

	}

	// print remaining credit by subtracting available credit with total price of items purchased
	outFile << "====================================================================" << endl;
	outFile << fixed << setprecision(2);
	outFile << "Remain Credit: RM " << credit << " - RM " << total_price << " = RM " << credit - total_price << endl;
	//print thank you banner
	outFile << "====================================================================" << endl;
	outFile << "           Thank you for purchasing at NEXTFLIP! ^_^   " << endl;
	outFile << "====================================================================" << endl;

	outFile.close();
}