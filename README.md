# NextFlip Console System

A C++ console application developed as a group assignment for UCCD1004 Programming Concepts and Practices at UTAR.

The application supports user accounts, personalised favourite lists, merchandise purchases and receipt generation. Records are stored in local text files.

## Main Features

- User registration and login
- Account data validation
- Add, display and delete favourite titles
- Account credit top-ups
- Merchandise selection and payment
- Receipt generation
- Text-file data storage

## Technologies

- C++
- File handling with fstream
- Two-dimensional arrays
- Functions and reference parameters
- Input validation
- Windows console output

## Contributors

| Team Member | Responsibilities |
| --- | --- |
| Chan Zhuo Qing | Registration, login and account information |
| Liew Jia Min | Adding, displaying and deleting favourites |
| Yew Kai Qian | Credit top-ups, merchandise purchases, payments and receipts |

## My Contribution

I developed the favourite list module, including:

- Loading the current user's saved favourites.
- Adding new titles and saving the updated list.
- Displaying favourite details.
- Deleting selected favourites and updating the text file.

## Project Files

| File | Purpose |
| --- | --- |
| `main.cpp` | Combined application source code |
| `userInfo.txt` | Demo account information |
| `Demo User MDInfo.txt` | Demo favourite list |
| `Demo User PurInfo.txt` | Demo credit and merchandise records |
| `.gitignore` | Excludes build outputs and generated receipts |

## How to Run

Use Windows with the Visual Studio C++ development tools installed.

1. Download or clone this repository.
2. Open the Visual Studio Developer Command Prompt.
3. Navigate to the folder containing `main.cpp`.
4. Compile the application:

```bat
cl /EHsc /std:c++20 /utf-8 main.cpp /Fe:nextflip.exe
```

5. Run it from the same folder:

```bat
nextflip.exe
```

The source uses Windows console commands and Microsoft's `localtime_s` function.

## Demo Account

- Username: `demo`
- Password: `DemoPass123!`

Choose Login from the main menu to use the demo account.

## Project Context

This is an educational group project using local text files for account and application data. The contributor table identifies each member's work.
