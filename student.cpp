
#include "student.h"
#include <iomanip>

// ─────────────────────────────────────────────
//  Student::display()
// ─────────────────────────────────────────────
void Student::display() const {
    std::cout << std::left
              << std::setw(8)  << rollNo
              << std::setw(20) << name
              << std::setw(15) << course
              << std::setw(6)  << year
              << std::setw(7)  << std::fixed << std::setprecision(2) << cgpa
              << std::setw(15) << phone
              << email
              << "\n";
}

// ─────────────────────────────────────────────
//  Student::isValid()
// ─────────────────────────────────────────────
bool Student::isValid() const {
    if (rollNo <= 0) return false;
    if (name[0] == '\0') return false;
    if (cgpa < 0.0f || cgpa > 10.0f) return false;
    if (year < 1 || year > 6) return false;
    return true;
}
