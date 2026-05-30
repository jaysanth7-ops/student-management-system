#include "StudentManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>

// ══════════════════════════════════════════════
//  Constructor / Destructor
// ══════════════════════════════════════════════
StudentManager::StudentManager(const std::string& dataFile)
    : m_dataFile(dataFile), m_nextId(1001)
{
    load();
}

StudentManager::~StudentManager() { save(); }

// ══════════════════════════════════════════════
//  CRUD
// ══════════════════════════════════════════════
int StudentManager::addStudent(const std::string& name,
                                int                age,
                                const std::string& email,
                                const std::string& course)
{
    int id = m_nextId++;
    m_students.emplace(id, Student(id, name, age, email, course));
    save();
    std::cout << "  [✓] Student added! ID: " << id << "\n";
    return id;
}

bool StudentManager::updateStudent(int id) {
    auto it = m_students.find(id);
    if (it == m_students.end()) {
        std::cout << "  [!] Student ID " << id << " not found.\n";
        return false;
    }
    Student& s = it->second;

    std::cout << "\n  What would you like to update?\n"
              << "  1. Name    (current: " << s.getName()   << ")\n"
              << "  2. Age     (current: " << s.getAge()    << ")\n"
              << "  3. Email   (current: " << s.getEmail()  << ")\n"
              << "  4. Course  (current: " << s.getCourse() << ")\n"
              << "  Choice: ";
    int ch; std::cin >> ch;
    std::cin.ignore();

    switch (ch) {
        case 1: {
            std::string v; std::cout << "  New name: ";
            std::getline(std::cin, v); s.setName(v); break;
        }
        case 2: {
            int v; std::cout << "  New age: ";
            std::cin >> v; std::cin.ignore(); s.setAge(v); break;
        }
        case 3: {
            std::string v; std::cout << "  New email: ";
            std::getline(std::cin, v); s.setEmail(v); break;
        }
        case 4: {
            std::string v; std::cout << "  New course: ";
            std::getline(std::cin, v); s.setCourse(v); break;
        }
        default:
            std::cout << "  [!] Invalid choice.\n"; return false;
    }
    save();
    std::cout << "  [✓] Student updated successfully.\n";
    return true;
}

bool StudentManager::deleteStudent(int id) {
    auto it = m_students.find(id);
    if (it == m_students.end()) {
        std::cout << "  [!] Student ID " << id << " not found.\n";
        return false;
    }
    std::cout << "  Are you sure you want to delete \""
              << it->second.getName() << "\"? (y/n): ";
    char c; std::cin >> c; std::cin.ignore();
    if (c != 'y' && c != 'Y') {
        std::cout << "  Cancelled.\n"; return false;
    }
    m_students.erase(it);
    save();
    std::cout << "  [✓] Student deleted.\n";
    return true;
}

bool StudentManager::addGrade(int id,
                               const std::string& subject,
                               double mark)
{
    auto it = m_students.find(id);
    if (it == m_students.end()) {
        std::cout << "  [!] Student ID " << id << " not found.\n";
        return false;
    }
    if (mark < 0 || mark > 100) {
        std::cout << "  [!] Mark must be between 0 and 100.\n";
        return false;
    }
    it->second.addGrade(subject, mark);
    save();
    std::cout << "  [✓] Grade added.\n";
    return true;
}

// ══════════════════════════════════════════════
//  Display
// ══════════════════════════════════════════════
void StudentManager::displayAll() const {
    if (m_students.empty()) {
        std::cout << "  No student records found.\n"; return;
    }
    std::cout << "\n"
              << "  ┌────────┬────────────────────────┬──────────────────────┬───────────────┐\n"
              << "  │ ID     │ Name                   │ Course               │ GPA           │\n"
              << "  ├────────┼────────────────────────┼──────────────────────┼───────────────┤\n";
    for (const auto& [id, s] : m_students)
        s.printSummary();
    std::cout << "  └────────┴────────────────────────┴──────────────────────┴───────────────┘\n\n";
}

void StudentManager::displayOne(int id) const {
    auto it = m_students.find(id);
    if (it == m_students.end()) {
        std::cout << "  [!] Student ID " << id << " not found.\n"; return;
    }
    it->second.printDetailed();
}

void StudentManager::displayTopStudents(int n) const {
    if (m_students.empty()) {
        std::cout << "  No students found.\n"; return;
    }
    std::vector<const Student*> sorted;
    for (const auto& [id, s] : m_students)
        sorted.push_back(&s);
    std::sort(sorted.begin(), sorted.end(),
              [](const Student* a, const Student* b) {
                  return a->getGPA() > b->getGPA();
              });

    std::cout << "\n  🏆 TOP " << n << " STUDENTS:\n";
    int count = 0;
    for (const auto* s : sorted) {
        if (count++ >= n) break;
        s->printSummary();
    }
    std::cout << "\n";
}

// ══════════════════════════════════════════════
//  Search
// ══════════════════════════════════════════════
void StudentManager::searchByName(const std::string& keyword) const {
    bool found = false;
    std::string kw = keyword;
    std::transform(kw.begin(), kw.end(), kw.begin(), ::tolower);

    std::cout << "\n  Search results for \"" << keyword << "\":\n";
    for (const auto& [id, s] : m_students) {
        std::string name = s.getName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (name.find(kw) != std::string::npos) {
            s.printSummary(); found = true;
        }
    }
    if (!found) std::cout << "  No students found.\n";
    std::cout << "\n";
}

void StudentManager::searchByCourse(const std::string& course) const {
    bool found = false;
    std::string c = course;
    std::transform(c.begin(), c.end(), c.begin(), ::tolower);

    std::cout << "\n  Students in course \"" << course << "\":\n";
    for (const auto& [id, s] : m_students) {
        std::string sc = s.getCourse();
        std::transform(sc.begin(), sc.end(), sc.begin(), ::tolower);
        if (sc.find(c) != std::string::npos) {
            s.printSummary(); found = true;
        }
    }
    if (!found) std::cout << "  No students found.\n";
    std::cout << "\n";
}

// ══════════════════════════════════════════════
//  Statistics
// ══════════════════════════════════════════════
void StudentManager::showStatistics() const {
    if (m_students.empty()) {
        std::cout << "  No data available.\n"; return;
    }
    double total = 0, highest = 0, lowest = 100;
    std::string topName, lowName;

    for (const auto& [id, s] : m_students) {
        double gpa = s.getGPA();
        total += gpa;
        if (gpa > highest) { highest = gpa; topName = s.getName(); }
        if (gpa < lowest)  { lowest  = gpa; lowName = s.getName(); }
    }
    double avg = total / m_students.size();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n"
              << "  ╔══════════════════════════════════════╗\n"
              << "  ║         CLASS STATISTICS             ║\n"
              << "  ╠══════════════════════════════════════╣\n"
              << "  ║  Total Students : " << std::left << std::setw(18) << m_students.size() << " ║\n"
              << "  ║  Average GPA    : " << std::left << std::setw(18) << avg     << " ║\n"
              << "  ║  Highest GPA    : " << std::left << std::setw(18) << highest << " ║\n"
              << "  ║  Top Student    : " << std::left << std::setw(18) << topName << " ║\n"
              << "  ║  Lowest GPA     : " << std::left << std::setw(18) << lowest  << " ║\n"
              << "  ║  Needs Help     : " << std::left << std::setw(18) << lowName << " ║\n"
              << "  ╚══════════════════════════════════════╝\n\n";
}

// ══════════════════════════════════════════════
//  File I/O
// ══════════════════════════════════════════════
void StudentManager::save() const {
    std::ofstream file(m_dataFile);
    if (!file) {
        std::cerr << "  [!] Could not save to " << m_dataFile << "\n"; return;
    }
    file << m_nextId << "\n";
    for (const auto& [id, s] : m_students)
        file << s.serialize() << "\n";
}

void StudentManager::load() {
    std::ifstream file(m_dataFile);
    if (!file) return;

    std::string line;
    if (std::getline(file, line) && !line.empty())
        m_nextId = std::stoi(line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            Student s = Student::deserialize(line);
            m_students[s.getId()] = s;
        } catch (...) {
            std::cerr << "  [!] Skipping corrupt record.\n";
        }
    }
    std::cout << "  [✓] Loaded " << m_students.size() << " student record(s).\n";
}

int  StudentManager::getNextId() const { return m_nextId; }
bool StudentManager::exists(int id) const {
    return m_students.find(id) != m_students.end();
}
