
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

// ─────────────────────────────────────────────
//  Student Record Structure
// ─────────────────────────────────────────────
struct Student {
    int    rollNo;
    char   name[50];
    char   course[30];
    int    year;
    float  cgpa;
    char   phone[15];
    char   email[50];

    // Display a formatted row
    void display() const;

    // Validate basic fields
    bool isValid() const;
};

#endif // STUDENT_H
