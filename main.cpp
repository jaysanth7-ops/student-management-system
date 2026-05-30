#include "StudentManager.h"
#include <iostream>
#include <limits>
#include <string>

// ─────────────────────────────────────────────
//  Input helpers
// ─────────────────────────────────────────────
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readId(const std::string& prompt = "  Enter Student ID: ") {
    int id;
    std::cout << prompt;
    std::cin >> id;
    clearInput();
    return id;
}

// ─────────────────────────────────────────────
//  Banner
// ─────────────────────────────────────────────
void printBanner() {
    std::cout << R"(
  ╔═══════════════════════════════════════════════════╗
  ║      STUDENT MANAGEMENT SYSTEM  v1.0              ║
  ║      Manage · Track · Analyse                     ║
  ╚═══════════════════════════════════════════════════╝
)";
}

void printMenu() {
    std::cout << R"(
  ══════════════════ MAIN MENU ══════════════════
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
  ═══════════════════════════════════════════════
  Choice: )";
}

// ─────────────────────────────────────────────
//  Handlers
// ─────────────────────────────────────────────
void handleAdd(StudentManager& sm) {
    std::cout << "\n  ── Add New Student ──\n";
    std::string name, email, course;
    int age;

    std::cout << "  Full name  : "; std::getline(std::cin, name);
    std::cout << "  Age        : "; std::cin >> age; clearInput();
    std::cout << "  Email      : "; std::getline(std::cin, email);
    std::cout << "  Course     : "; std::getline(std::cin, course);

    sm.addStudent(name, age, email, course);
}

void handleUpdate(StudentManager& sm) {
    std::cout << "\n  ── Update Student ──\n";
    int id = readId();
    sm.updateStudent(id);
}

void handleDelete(StudentManager& sm) {
    std::cout << "\n  ── Delete Student ──\n";
    int id = readId();
    sm.deleteStudent(id);
}

void handleDisplayAll(StudentManager& sm) {
    sm.displayAll();
}

void handleDisplayOne(StudentManager& sm) {
    std::cout << "\n  ── Student Details ──\n";
    int id = readId();
    sm.displayOne(id);
}

void handleAddGrade(StudentManager& sm) {
    std::cout << "\n  ── Add / Update Grade ──\n";
    int id = readId();
    if (!sm.exists(id)) {
        std::cout << "  [!] Student not found.\n"; return;
    }
    std::string subject;
    double mark;
    std::cout << "  Subject : "; std::getline(std::cin, subject);
    std::cout << "  Mark (0-100): "; std::cin >> mark; clearInput();
    sm.addGrade(id, subject, mark);
}

void handleSearchName(StudentManager& sm) {
    std::cout << "\n  ── Search by Name ──\n";
    std::string kw;
    std::cout << "  Enter name keyword: ";
    std::getline(std::cin, kw);
    sm.searchByName(kw);
}

void handleSearchCourse(StudentManager& sm) {
    std::cout << "\n  ── Search by Course ──\n";
    std::string course;
    std::cout << "  Enter course name: ";
    std::getline(std::cin, course);
    sm.searchByCourse(course);
}

// ─────────────────────────────────────────────
//  Main
// ─────────────────────────────────────────────
int main() {
    printBanner();

    StudentManager sm("students.txt");

    int choice = -1;
    while (choice != 0) {
        printMenu();
        std::cin >> choice;
        clearInput();

        switch (choice) {
            case 1:  handleAdd(sm);          break;
            case 2:  handleUpdate(sm);       break;
            case 3:  handleDelete(sm);       break;
            case 4:  handleDisplayAll(sm);   break;
            case 5:  handleDisplayOne(sm);   break;
            case 6:  handleAddGrade(sm);     break;
            case 7:  handleSearchName(sm);   break;
            case 8:  handleSearchCourse(sm); break;
            case 9:  sm.displayTopStudents(); break;
            case 10: sm.showStatistics();    break;
            case 0:
                std::cout << "\n  [✓] Data saved. Goodbye!\n\n";
                break;
            default:
                std::cout << "  [!] Invalid option. Try again.\n";
        }
    }
    return 0;
}
