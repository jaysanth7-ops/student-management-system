#include "Student.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>

// ══════════════════════════════════════════════
//  Grade helpers
// ══════════════════════════════════════════════
std::string Grade::serialize() const {
    // subject~mark
    std::ostringstream oss;
    oss << subject << "~" << std::fixed << std::setprecision(2) << mark;
    return oss.str();
}

Grade Grade::deserialize(const std::string& token) {
    Grade g;
    auto pos = token.find('~');
    g.subject = token.substr(0, pos);
    g.mark    = std::stod(token.substr(pos + 1));
    return g;
}

// ══════════════════════════════════════════════
//  Constructors
// ══════════════════════════════════════════════
Student::Student() : m_id(0), m_age(0) {}

Student::Student(int id,
                 const std::string& name,
                 int                age,
                 const std::string& email,
                 const std::string& course)
    : m_id(id), m_name(name), m_age(age),
      m_email(email), m_course(course) {}

// ══════════════════════════════════════════════
//  Getters
// ══════════════════════════════════════════════
int         Student::getId()     const { return m_id; }
std::string Student::getName()   const { return m_name; }
int         Student::getAge()    const { return m_age; }
std::string Student::getEmail()  const { return m_email; }
std::string Student::getCourse() const { return m_course; }
std::vector<Grade> Student::getGrades() const { return m_grades; }

double Student::getGPA() const {
    if (m_grades.empty()) return 0.0;
    double sum = 0;
    for (const auto& g : m_grades) sum += g.mark;
    return sum / m_grades.size();
}

// ══════════════════════════════════════════════
//  Setters
// ══════════════════════════════════════════════
void Student::setName  (const std::string& n) { m_name   = n; }
void Student::setAge   (int a)                { m_age    = a; }
void Student::setEmail (const std::string& e) { m_email  = e; }
void Student::setCourse(const std::string& c) { m_course = c; }

void Student::addGrade(const std::string& subject, double mark) {
    // Update if subject already exists
    for (auto& g : m_grades) {
        if (g.subject == subject) { g.mark = mark; return; }
    }
    m_grades.push_back({subject, mark});
}

// ══════════════════════════════════════════════
//  Display
// ══════════════════════════════════════════════
std::string letterGrade(double gpa) {
    if (gpa >= 90) return "A+";
    if (gpa >= 80) return "A";
    if (gpa >= 70) return "B";
    if (gpa >= 60) return "C";
    if (gpa >= 50) return "D";
    return "F";
}

void Student::printSummary() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  │ " << std::left  << std::setw(6)  << m_id
              << " │ " << std::left  << std::setw(22) << m_name
              << " │ " << std::left  << std::setw(20) << m_course
              << " │ " << std::right << std::setw(6)  << getGPA()
              << " (" << letterGrade(getGPA()) << ")"
              << " │\n";
}

void Student::printDetailed() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n"
              << "  ╔══════════════════════════════════════════════╗\n"
              << "  ║           STUDENT RECORD                     ║\n"
              << "  ╠══════════════════════════════════════════════╣\n"
              << "  ║  ID      : " << std::left << std::setw(34) << m_id      << " ║\n"
              << "  ║  Name    : " << std::left << std::setw(34) << m_name    << " ║\n"
              << "  ║  Age     : " << std::left << std::setw(34) << m_age     << " ║\n"
              << "  ║  Email   : " << std::left << std::setw(34) << m_email   << " ║\n"
              << "  ║  Course  : " << std::left << std::setw(34) << m_course  << " ║\n"
              << "  ║  GPA     : " << std::left << std::setw(28) << getGPA()
              << " (" << letterGrade(getGPA()) << ")   ║\n"
              << "  ╠══════════════════════════════════════════════╣\n"
              << "  ║  Subject                    Mark             ║\n"
              << "  ╠══════════════════════════════════════════════╣\n";
    if (m_grades.empty()) {
        std::cout << "  ║  No grades recorded.                         ║\n";
    } else {
        for (const auto& g : m_grades) {
            std::cout << "  ║  " << std::left  << std::setw(28) << g.subject
                      << std::right << std::setw(6) << g.mark << "           ║\n";
        }
    }
    std::cout << "  ╚══════════════════════════════════════════════╝\n\n";
}

// ══════════════════════════════════════════════
//  Persistence
//  FORMAT: id|name|age|email|course|subj~mark,subj~mark,...
// ══════════════════════════════════════════════
std::string Student::serialize() const {
    std::ostringstream oss;
    oss << m_id    << "|"
        << m_name  << "|"
        << m_age   << "|"
        << m_email << "|"
        << m_course << "|";
    for (size_t i = 0; i < m_grades.size(); ++i) {
        if (i > 0) oss << ",";
        oss << m_grades[i].serialize();
    }
    return oss.str();
}

Student Student::deserialize(const std::string& line) {
    Student s;
    std::istringstream iss(line);
    std::string token;

    std::getline(iss, token,    '|'); s.m_id     = std::stoi(token);
    std::getline(iss, s.m_name, '|');
    std::getline(iss, token,    '|'); s.m_age    = std::stoi(token);
    std::getline(iss, s.m_email,  '|');
    std::getline(iss, s.m_course, '|');

    std::string gradeBlock;
    std::getline(iss, gradeBlock);
    if (!gradeBlock.empty()) {
        std::istringstream gs(gradeBlock);
        std::string gt;
        while (std::getline(gs, gt, ',')) {
            if (!gt.empty())
                s.m_grades.push_back(Grade::deserialize(gt));
        }
    }
    return s;
}
