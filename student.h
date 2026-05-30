#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

// ─────────────────────────────────────────────
//  Grade – stores one subject and its mark
// ─────────────────────────────────────────────
struct Grade {
    std::string subject;
    double      mark;      // 0 – 100

    std::string serialize()                    const;
    static Grade deserialize(const std::string& token);
};

// ─────────────────────────────────────────────
//  Student – core entity
// ─────────────────────────────────────────────
class Student {
public:
    Student();
    Student(int id,
            const std::string& name,
            int                age,
            const std::string& email,
            const std::string& course);

    // ── Getters ──────────────────────────────
    int         getId()      const;
    std::string getName()    const;
    int         getAge()     const;
    std::string getEmail()   const;
    std::string getCourse()  const;
    double      getGPA()     const;   // average of all grades
    std::vector<Grade> getGrades() const;

    // ── Setters (for update) ─────────────────
    void setName  (const std::string& name);
    void setAge   (int age);
    void setEmail (const std::string& email);
    void setCourse(const std::string& course);
    void addGrade (const std::string& subject, double mark);

    // ── Display ──────────────────────────────
    void printSummary()  const;
    void printDetailed() const;

    // ── Persistence ──────────────────────────
    std::string  serialize()                        const;
    static Student deserialize(const std::string& line);

private:
    int         m_id;
    std::string m_name;
    int         m_age;
    std::string m_email;
    std::string m_course;
    std::vector<Grade> m_grades;
};

#endif // STUDENT_H
