
# 🎓 Student Management System — C++

A **console-based Student Management System** built in **C++** that efficiently manages student records using **binary file handling** and a clean **menu-driven interface**.

---

## 📋 Features

| Feature | Description |
|---|---|
| ➕ Add Student | Add a new student with roll no., name, course, year, CGPA, phone, email |
| 📋 Display All | View all students in a formatted table |
| 🔍 Search | Search any student by roll number |
| ✏️ Update | Modify existing student details |
| 🗑️ Delete | Remove a student record with confirmation |
| 📊 Sort by CGPA | View merit list (highest CGPA first) |
| 🔢 Sort by Roll No. | View records sorted by roll number |
| 📈 Statistics | Average CGPA, topper, distribution analysis |

---

## 🗂️ Project Structure

```
StudentManagementSystem/
├── main.cpp          # Entry point — menu-driven application
├── student.h         # Student struct definition
├── student.cpp       # Student method implementations
├── fileHandler.h     # File I/O declarations
├── fileHandler.cpp   # Binary file read/write logic
├── students.dat      # Auto-created persistent data file (binary)
└── README.md         # Project documentation
```

---

## 🛠️ How to Compile & Run

### Using g++ (MinGW / GCC)

```bash
# Compile
g++ main.cpp student.cpp fileHandler.cpp -o student_ms

# Run
./student_ms          # Linux/Mac
student_ms.exe        # Windows
```

### Using MSVC (Developer Command Prompt)

```bash
cl main.cpp student.cpp fileHandler.cpp /Fe:student_ms.exe
student_ms.exe
```

### Using Code::Blocks / Dev-C++
1. Create a new **C++ Project**.
2. Add all `.cpp` files to the project.
3. Build & Run (`F9`).

---

## 💾 Data Persistence

Records are stored in a **binary file** (`students.dat`) using fixed-size `struct` serialization:

- Binary format ensures fast sequential I/O.
- The file is automatically created on the first run.
- All write operations use `ofstream` with `std::ios::binary` mode.
- Updates re-write the entire file (load → modify → save).

---

## 📐 Data Fields

| Field | Type | Constraint |
|---|---|---|
| Roll Number | `int` | Unique, > 0 |
| Name | `char[50]` | Non-empty |
| Course | `char[30]` | — |
| Year | `int` | 1 – 6 |
| CGPA | `float` | 0.00 – 10.00 |
| Phone | `char[15]` | — |
| Email | `char[50]` | — |

---

## 🖥️ Menu Preview

```
╔══════════════════════════════════════════════════╗
║       STUDENT  MANAGEMENT  SYSTEM  v1.0          ║
║     Persistent Data Storage  |  C++ Project      ║
╚══════════════════════════════════════════════════╝
  Total Records: 3

┌──────────────────────────────────┐
│         MAIN  MENU               │
├──────────────────────────────────┤
│  1. Add New Student               │
│  2. Display All Students          │
│  3. Search Student by Roll No.    │
│  4. Update Student Record         │
│  5. Delete Student Record         │
│  6. Sort Students by CGPA         │
│  7. Sort Students by Roll No.     │
│  8. Count / Statistics            │
│  0. Exit                          │
└──────────────────────────────────┘
```

---

## 🔧 Technologies Used

- **Language** : C++ (C++11 or later)
- **Storage**  : Binary file I/O (`fstream`)
- **STL**      : `vector`, `algorithm` (sort, remove_if)
- **Platform** : Windows / Linux / macOS

---

## 👤 Author

**Sharad Shukla**  
B.Tech Student  
GitHub: [@yourusername](https://github.com/yourusername)

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
