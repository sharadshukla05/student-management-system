
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "student.h"
#include <vector>
#include <string>

const std::string DB_FILE = "students.dat";

// ─────────────────────────────────────────────
//  File-based Persistence Layer
// ─────────────────────────────────────────────
class FileHandler {
public:
    // Load all records from file into a vector
    static std::vector<Student> loadAll();

    // Overwrite the file with the given vector
    static bool saveAll(const std::vector<Student>& students);

    // Append a single record to the file
    static bool appendRecord(const Student& s);

    // Check if roll number already exists
    static bool rollExists(int rollNo);

    // Return total count of records
    static int totalRecords();
};

#endif // FILE_HANDLER_H
