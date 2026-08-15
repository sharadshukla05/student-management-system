
#include "fileHandler.h"
#include <fstream>
#include <algorithm>

// ─────────────────────────────────────────────
//  Load all student records from binary file
// ─────────────────────────────────────────────
std::vector<Student> FileHandler::loadAll() {
    std::vector<Student> students;
    std::ifstream fin(DB_FILE, std::ios::binary);
    if (!fin.is_open()) return students;

    Student s;
    while (fin.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        students.push_back(s);
    }
    fin.close();
    return students;
}

// ─────────────────────────────────────────────
//  Overwrite file with updated vector
// ─────────────────────────────────────────────
bool FileHandler::saveAll(const std::vector<Student>& students) {
    std::ofstream fout(DB_FILE, std::ios::binary | std::ios::trunc);
    if (!fout.is_open()) return false;

    for (const auto& s : students) {
        fout.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    }
    fout.close();
    return true;
}

// ─────────────────────────────────────────────
//  Append a single record to the binary file
// ─────────────────────────────────────────────
bool FileHandler::appendRecord(const Student& s) {
    std::ofstream fout(DB_FILE, std::ios::binary | std::ios::app);
    if (!fout.is_open()) return false;
    fout.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    fout.close();
    return true;
}

// ─────────────────────────────────────────────
//  Check if a roll number already exists
// ─────────────────────────────────────────────
bool FileHandler::rollExists(int rollNo) {
    auto students = loadAll();
    for (const auto& s : students) {
        if (s.rollNo == rollNo) return true;
    }
    return false;
}

// ─────────────────────────────────────────────
//  Return total number of student records
// ─────────────────────────────────────────────
int FileHandler::totalRecords() {
    return static_cast<int>(loadAll().size());
}
