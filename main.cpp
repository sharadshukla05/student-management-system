
/*
 * ╔══════════════════════════════════════════════════════════════╗
 * ║          STUDENT MANAGEMENT SYSTEM  —  C++ Project          ║
 * ║  Features : Add | Update | Delete | Search | Display | Sort ║
 * ║  Storage  : Binary file  (students.dat)                     ║
 * ╚══════════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstring>
#include <cstdlib>

#include "student.h"
#include "fileHandler.h"

// ─── Platform-aware clear screen ──────────────────────────────
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ─── Pause until Enter is pressed ─────────────────────────────
void pause() {
    std::cout << "\n  Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// ─── Decorative banner ────────────────────────────────────────
void printBanner() {
    clearScreen();
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════════════╗\n";
    std::cout << "  ║       STUDENT  MANAGEMENT  SYSTEM  v1.0          ║\n";
    std::cout << "  ║     Persistent Data Storage  |  C++ Project      ║\n";
    std::cout << "  ╚══════════════════════════════════════════════════╝\n";
    std::cout << "  Total Records: " << FileHandler::totalRecords() << "\n\n";
}

// ─── Main Menu ────────────────────────────────────────────────
void printMenu() {
    std::cout << "  ┌──────────────────────────────────┐\n";
    std::cout << "  │         MAIN  MENU               │\n";
    std::cout << "  ├──────────────────────────────────┤\n";
    std::cout << "  │  1. Add New Student               │\n";
    std::cout << "  │  2. Display All Students          │\n";
    std::cout << "  │  3. Search Student by Roll No.    │\n";
    std::cout << "  │  4. Update Student Record         │\n";
    std::cout << "  │  5. Delete Student Record         │\n";
    std::cout << "  │  6. Sort Students by CGPA         │\n";
    std::cout << "  │  7. Sort Students by Roll No.     │\n";
    std::cout << "  │  8. Count / Statistics            │\n";
    std::cout << "  │  0. Exit                          │\n";
    std::cout << "  └──────────────────────────────────┘\n";
    std::cout << "  Enter your choice: ";
}

// ─── Table Header ─────────────────────────────────────────────
void printTableHeader() {
    std::cout << "\n  " << std::string(85, '-') << "\n";
    std::cout << "  " << std::left
              << std::setw(8)  << "Roll"
              << std::setw(20) << "Name"
              << std::setw(15) << "Course"
              << std::setw(6)  << "Year"
              << std::setw(7)  << "CGPA"
              << std::setw(15) << "Phone"
              << "Email\n";
    std::cout << "  " << std::string(85, '-') << "\n";
}

// ─── Input helpers ────────────────────────────────────────────
void getStringInput(const char* prompt, char* buf, int maxLen) {
    std::cout << "  " << prompt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(buf, maxLen);
}

void getStringInputNoFlush(const char* prompt, char* buf, int maxLen) {
    std::cout << "  " << prompt;
    std::cin.getline(buf, maxLen);
}

int getIntInput(const char* prompt) {
    int val;
    while (true) {
        std::cout << "  " << prompt;
        if (std::cin >> val) return val;
        std::cout << "  [!] Invalid input — please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

float getFloatInput(const char* prompt, float lo, float hi) {
    float val;
    while (true) {
        std::cout << "  " << prompt;
        if (std::cin >> val && val >= lo && val <= hi) return val;
        std::cout << "  [!] Enter a value between " << lo << " and " << hi << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// ══════════════════════════════════════════════════════════════
//  FEATURE 1 — Add New Student
// ══════════════════════════════════════════════════════════════
void addStudent() {
    printBanner();
    std::cout << "  [ ADD NEW STUDENT ]\n\n";

    Student s;

    // Roll number — must be unique
    while (true) {
        s.rollNo = getIntInput("Roll Number     : ");
        if (s.rollNo <= 0) {
            std::cout << "  [!] Roll number must be positive.\n";
            continue;
        }
        if (FileHandler::rollExists(s.rollNo)) {
            std::cout << "  [!] Roll number " << s.rollNo << " already exists. Try another.\n";
            continue;
        }
        break;
    }

    getStringInput("Full Name       : ", s.name,   50);
    getStringInputNoFlush("Course          : ", s.course, 30);
    s.year  = getIntInput("Year (1-6)      : ");
    if (s.year < 1 || s.year > 6) s.year = 1;
    s.cgpa  = getFloatInput("CGPA (0-10)     : ", 0.0f, 10.0f);
    getStringInputNoFlush("Phone           : ", s.phone, 15);
    getStringInputNoFlush("Email           : ", s.email, 50);

    if (!s.isValid()) {
        std::cout << "\n  [!] Invalid data — record NOT saved.\n";
        pause();
        return;
    }

    if (FileHandler::appendRecord(s)) {
        std::cout << "\n  [✔] Student record added successfully!\n";
    } else {
        std::cout << "\n  [✘] Error saving record to file.\n";
    }
    pause();
}

// ══════════════════════════════════════════════════════════════
//  FEATURE 2 — Display All Students
// ══════════════════════════════════════════════════════════════
void displayAll() {
    printBanner();
    std::cout << "  [ ALL STUDENT RECORDS ]\n";

    auto students = FileHandler::loadAll();
    if (students.empty()) {
        std::cout << "\n  No records found.\n";
        pause();
        return;
    }

    printTableHeader();
    for (const auto& s : students) {
        std::cout << "  ";
        s.display();
    }
    std::cout << "  " << std::string(85, '-') << "\n";
    std::cout << "  Total: " << students.size() << " record(s)\n";
    pause();
}

// ══════════════════════════════════════════════════════════════
//  FEATURE 3 — Search Student by Roll Number
// ══════════════════════════════════════════════════════════════
void searchStudent() {
    printBanner();
    std::cout << "  [ SEARCH STUDENT ]\n\n";

    int roll = getIntInput("Enter Roll Number to search: ");
    auto students = FileHandler::loadAll();

    for (const auto& s : students) {
        if (s.rollNo == roll) {
            std::cout << "\n  [✔] Student Found:\n";
            printTableHeader();
            std::cout << "  ";
            s.display();
            std::cout << "  " << std::string(85, '-') << "\n";
            pause();
            return;
        }
    }
    std::cout << "\n  [✘] No student found with Roll No: " << roll << "\n";
    pause();
}

// ══════════════════════════════════════════════════════════════
//  FEATURE 4 — Update Student Record
// ══════════════════════════════════════════════════════════════
void updateStudent() {
    printBanner();
    std::cout << "  [ UPDATE STUDENT RECORD ]\n\n";

    int roll = getIntInput("Enter Roll Number to update: ");
    auto students = FileHandler::loadAll();
    bool found = false;

    for (auto& s : students) {
        if (s.rollNo == roll) {
            found = true;
            std::cout << "\n  Current details:\n";
            printTableHeader();
            std::cout << "  ";
            s.display();
            std::cout << "  " << std::string(85, '-') << "\n";
            std::cout << "\n  Enter new details (leave blank = keep current for text fields):\n\n";

            // Temporary buffers
            char tmpBuf[50];

            // Name
            std::cout << "  New Name   [" << s.name << "]: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.getline(tmpBuf, 50);
            if (tmpBuf[0] != '\0') std::strncpy(s.name, tmpBuf, 50);

            // Course
            std::cout << "  New Course [" << s.course << "]: ";
            std::cin.getline(tmpBuf, 30);
            if (tmpBuf[0] != '\0') std::strncpy(s.course, tmpBuf, 30);

            // Year
            std::cout << "  New Year   [" << s.year << "] (0=keep): ";
            int y; std::cin >> y;
            if (y >= 1 && y <= 6) s.year = y;

            // CGPA
            std::cout << "  New CGPA   [" << s.cgpa << "] (0=keep): ";
            float g; std::cin >> g;
            if (g > 0 && g <= 10.0f) s.cgpa = g;

            // Phone
            std::cout << "  New Phone  [" << s.phone << "]: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.getline(tmpBuf, 15);
            if (tmpBuf[0] != '\0') std::strncpy(s.phone, tmpBuf, 15);

            // Email
            std::cout << "  New Email  [" << s.email << "]: ";
            std::cin.getline(tmpBuf, 50);
            if (tmpBuf[0] != '\0') std::strncpy(s.email, tmpBuf, 50);

            break;
        }
    }

    if (!found) {
        std::cout << "\n  [✘] Roll No " << roll << " not found.\n";
        pause();
        return;
    }

    if (FileHandler::saveAll(students)) {
        std::cout << "\n  [✔] Record updated successfully!\n";
    } else {
        std::cout << "\n  [✘] Error writing to file.\n";
    }
    pause();
}

// ══════════════════════════════════════════════════════════════
//  FEATURE 5 — Delete Student Record
// ══════════════════════════════════════════════════════════════
void deleteStudent() {
    printBanner();
    std::cout << "  [ DELETE STUDENT RECORD ]\n\n";

    int roll = getIntInput("Enter Roll Number to delete: ");
    auto students = FileHandler::loadAll();

    auto it = std::remove_if(students.begin(), students.end(),
        [&](const Student& s) { return s.rollNo == roll; });

    if (it == students.end()) {
        std::cout << "\n  [✘] No student found with Roll No: " << roll << "\n";
        pause();
        return;
    }

    // Confirm deletion
    char confirm;
    std::cout << "\n  Are you sure you want to delete Roll No " << roll << "? (y/n): ";
    std::cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') {
        std::cout << "\n  Deletion cancelled.\n";
        pause();
        return;
    }

    students.erase(it, students.end());

    if (FileHandler::saveAll(students)) {
        std::cout << "\n  [✔] Student with Roll No " << roll << " deleted.\n";
    } else {
        std::cout << "\n  [✘] Error updating file.\n";
    }
    pause();
}

// ══════════════════════════════════════════════════════════════
//  FEATURE 6 — Sort by CGPA (descending)
// ══════════════════════════════════════════════════════════════
void sortByCGPA() {
    printBanner();
    std::cout << "  [ STUDENTS SORTED BY CGPA (High → Low) ]\n";

    auto students = FileHandler::loadAll();
    if (students.empty()) {
        std::cout << "\n  No records found.\n";
        pause();
        return;
    }

    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) { return a.cgpa > b.cgpa; });

    printTableHeader();
    int rank = 1;
    for (const auto& s : students) {
        std::cout << "  [" << std::setw(2) << rank++ << "] ";
        s.display();
    }
    std::cout << "  " << std::string(85, '-') << "\n";
    pause();
}

// ══════════════════════════════════════════════════════════════
//  FEATURE 7 — Sort by Roll Number (ascending)
// ══════════════════════════════════════════════════════════════
void sortByRoll() {
    printBanner();
    std::cout << "  [ STUDENTS SORTED BY ROLL NUMBER ]\n";

    auto students = FileHandler::loadAll();
    if (students.empty()) {
        std::cout << "\n  No records found.\n";
        pause();
        return;
    }

    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) { return a.rollNo < b.rollNo; });

    printTableHeader();
    for (const auto& s : students) {
        std::cout << "  ";
        s.display();
    }
    std::cout << "  " << std::string(85, '-') << "\n";
    pause();
}

// ══════════════════════════════════════════════════════════════
//  FEATURE 8 — Statistics
// ══════════════════════════════════════════════════════════════
void showStats() {
    printBanner();
    std::cout << "  [ STATISTICS ]\n\n";

    auto students = FileHandler::loadAll();
    if (students.empty()) {
        std::cout << "  No records found.\n";
        pause();
        return;
    }

    float sum = 0, highest = 0, lowest = 10.0f;
    Student topStudent{}, bottomStudent{};

    for (const auto& s : students) {
        sum += s.cgpa;
        if (s.cgpa > highest) { highest = s.cgpa; topStudent = s; }
        if (s.cgpa < lowest)  { lowest  = s.cgpa; bottomStudent = s; }
    }

    float avg = sum / students.size();

    std::cout << "  Total Students  : " << students.size() << "\n";
    std::cout << "  Average CGPA    : " << std::fixed << std::setprecision(2) << avg << "\n";
    std::cout << "  Highest CGPA    : " << highest
              << "  (" << topStudent.name << ", Roll " << topStudent.rollNo << ")\n";
    std::cout << "  Lowest  CGPA    : " << lowest
              << "  (" << bottomStudent.name << ", Roll " << bottomStudent.rollNo << ")\n";

    // Distribution
    int above8 = 0, between6 = 0, below6 = 0;
    for (const auto& s : students) {
        if      (s.cgpa >= 8.0f) above8++;
        else if (s.cgpa >= 6.0f) between6++;
        else                     below6++;
    }

    std::cout << "\n  CGPA Distribution:\n";
    std::cout << "    ≥ 8.0 (Distinction) : " << above8   << " student(s)\n";
    std::cout << "    6.0–7.9 (First Div) : " << between6 << " student(s)\n";
    std::cout << "    < 6.0  (Others)     : " << below6   << " student(s)\n";
    pause();
}

// ══════════════════════════════════════════════════════════════
//  MAIN
// ══════════════════════════════════════════════════════════════
int main() {
    int choice;

    do {
        printBanner();
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: addStudent();    break;
            case 2: displayAll();    break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: sortByCGPA();    break;
            case 7: sortByRoll();    break;
            case 8: showStats();     break;
            case 0:
                clearScreen();
                std::cout << "\n  Thank you for using Student Management System!\n";
                std::cout << "  Data saved to: " << DB_FILE << "\n\n";
                break;
            default:
                std::cout << "\n  [!] Invalid choice. Please try again.\n";
                pause();
        }

    } while (choice != 0);

    return 0;
}
