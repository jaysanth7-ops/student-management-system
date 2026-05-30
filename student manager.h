#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include <map>
#include <string>
#include <vector>

// ─────────────────────────────────────────────
//  StudentManager – handles all students + I/O
// ─────────────────────────────────────────────
class StudentManager {
public:
    explicit StudentManager(const std::string& dataFile = "students.txt");
    ~StudentManager();   // auto-saves on exit

    // ── CRUD ─────────────────────────────────
    int  addStudent   (const std::string& name,
                       int                age,
                       const std::string& email,
                       const std::string& course);
    bool updateStudent(int id);          // interactive update
    bool deleteStudent(int id);
    bool addGrade     (int id, const std::string& subject, double mark);

    // ── Display ──────────────────────────────
    void displayAll()        const;
    void displayOne(int id)  const;
    void displayTopStudents(int n = 5) const;

    // ── Search ───────────────────────────────
    void searchByName  (const std::string& keyword) const;
    void searchByCourse(const std::string& course)  const;

    // ── File I/O ─────────────────────────────
    void save() const;
    void load();

    // ── Stats ────────────────────────────────
    void showStatistics() const;

    int  getNextId() const;
    bool exists(int id) const;

private:
    std::map<int, Student> m_students;
    std::string            m_dataFile;
    int                    m_nextId;
};

#endif // STUDENTMANAGER_H
