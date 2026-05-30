# 📚 Student Management System

A console-based Student Management System built with C++ that lets you add, update, delete, and display student records with grades and statistics. All data is saved automatically so nothing is lost when you close the app.

---

## 💻 What You Need Before Starting

- A computer (Windows, Mac, or Linux)
- G++ compiler installed

### How to install G++ on Windows:
1. Go to https://www.mingw-w64.org
2. Download and install MinGW
3. During install, select g++ as a component
4. Add MinGW to your system PATH
5. Open Command Prompt and type g++ --version to confirm it works

### How to install G++ on Mac:
1. Open Terminal
2. Type xcode-select --install and press Enter
3. Follow the on-screen instructions
4. Type g++ --version to confirm it works

### How to install G++ on Linux:
1. Open Terminal
2. Type sudo apt install g++ and press Enter
3. Type g++ --version to confirm it works

---

## 📥 Step 1 — Download This Project

1. Scroll to the top of this page
2. Click the green button that says Code
3. Click Download ZIP
4. Go to your Downloads folder
5. Right click the ZIP file and click Extract All or Extract Here
6. You will now have a folder called student-management-system

---

## 📂 Step 2 — Open the Project Folder

### On Windows:
1. Press the Windows key and type cmd
2. Click Command Prompt
3. Type this and press Enter:
   cd Downloads\student-management-system-main

### On Mac:
1. Press Command + Space and type Terminal
2. Press Enter to open it
3. Type this and press Enter:
   cd Downloads/student-management-system-main

### On Linux:
1. Open Terminal
2. Type this and press Enter:
   cd Downloads/student-management-system-main

---

## 🔨 Step 3 — Compile the Code

Type this command and press Enter:

g++ -std=c++17 -o student_app main.cpp Student.cpp StudentManager.cpp

Wait a few seconds. If you see no error messages, the compile was successful!

---

## ▶️ Step 4 — Run the App

### On Mac and Linux:
Type this and press Enter:
./student_app

### On Windows:
Type this and press Enter:
student_app.exe

You will see the main menu appear on screen.

---

## 📋 Step 5 — Using the App

When you run the app you will see this menu:

1.  Add New Student
2.  Update Student
3.  Delete Student
4.  Display All Students
5.  Display Student Details
6.  Add / Update Grade
7.  Search by Name
8.  Search by Course
9.  Top 5 Students
10. Class Statistics
0.  Exit

Type the number of what you want to do and press Enter.

---

## 👤 How to Add Your First Student

1. Type 1 and press Enter
2. Type the student full name and press Enter
3. Type the student age and press Enter
4. Type the student email and press Enter
5. Type the course name like Computer Science and press Enter
6. You will see a message saying Student added with an ID number
7. Write down that ID number — you will need it later!

Example:
Full name  : John Smith
Age        : 20
Email      : john@email.com
Course     : Computer Science
Result     : Student added! ID: 1001

---

## ✏️ How to Update a Student

1. Type 2 and press Enter
2. Enter the student ID number
3. You will see options to update Name, Age, Email, or Course
4. Type the number of what you want to change
5. Type the new value and press Enter
6. You will see Student updated successfully

---

## 🗑️ How to Delete a Student

1. Type 3 and press Enter
2. Enter the student ID number
3. The app will ask Are you sure? Type y and press Enter
4. The student record will be permanently deleted

---

## 📋 How to Display All Students

1. Type 4 and press Enter
2. A table will appear showing all students with their ID, name, course, and GPA

---

## 🔍 How to See One Student in Detail

1. Type 5 and press Enter
2. Enter the student ID number
3. A full record card will appear showing all their info and grades

---

## 🎓 How to Add a Grade

1. Type 6 and press Enter
2. Enter the student ID number
3. Type the subject name like Maths and press Enter
4. Type the mark between 0 and 100 and press Enter
5. The grade is saved and the GPA updates automatically

Note: If you add the same subject again it will update the existing mark.

---

## 🔎 How to Search for a Student

By Name:
1. Type 7 and press Enter
2. Type part of the name like Ali and press Enter
3. All students with that name will be shown

By Course:
1. Type 8 and press Enter
2. Type the course name like Mathematics and press Enter
3. All students in that course will be shown

---

## 🏆 How to See Top Students

1. Type 9 and press Enter
2. The top 5 students ranked by GPA will be displayed

---

## 📊 How to See Class Statistics

1. Type 10 and press Enter
2. You will see total students, average GPA, highest GPA, top student, lowest GPA, and which student needs help

---

## 💾 Where is My Data Saved?

All records are automatically saved to a file called students.txt in the same folder. Every time you add, update, or delete a student the file updates instantly. When you open the app again your data will still be there.

---

## 🚪 How to Exit

1. Type 0 and press Enter
2. The app closes and all data is saved

---

## 🔒 GPA and Grades Explained

Marks are out of 100. The app calculates GPA as the average of all subject marks and gives a letter grade:

90 to 100 = A+
80 to 89  = A
70 to 79  = B
60 to 69  = C
50 to 59  = D
Below 50  = F

---

## 👨‍💻 Built With

- C++ (C++17)
- Object Oriented Programming with classes
- File Handling for persistent storage
- Menu-driven console interface

---

## 🙋 Need Help?

Open an Issue on this GitHub page, describe your problem, and we will help you!