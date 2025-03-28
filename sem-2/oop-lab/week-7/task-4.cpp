#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
protected:
    string name;
    string id;
    string address;
    string phoneNumber;
    string email;

public:
    Person(string n, string i, string addr = "", string phone = "", string mail = "")
        : name(n), id(i), address(addr), phoneNumber(phone), email(mail) {}

    // Getters
    string getName() const { return name; }
    string getId() const { return id; }
    string getAddress() const { return address; }
    string getPhoneNumber() const { return phoneNumber; }
    string getEmail() const { return email; }

    virtual void displayInfo() {
        cout << "Name: " << name << "\nID: " << id << "\n";
        if (!address.empty()) cout << "Address: " << address << "\n";
        if (!phoneNumber.empty()) cout << "Phone: " << phoneNumber << "\n";
        if (!email.empty()) cout << "Email: " << email << "\n";
    }

    virtual void updateInfo(string addr, string phone, string mail) {
        address = addr;
        phoneNumber = phone;
        email = mail;
    }
};

class Student : public Person {
private:
    vector<string> coursesEnrolled;
    double gpa;
    int enrollmentYear;

public:
    Student(string n, string i, double g, int year, string addr = "", string phone = "", string mail = "")
        : Person(n, i, addr, phone, mail), gpa(g), enrollmentYear(year) {}

    // Getters
    vector<string> getCoursesEnrolled() const { return coursesEnrolled; }
    double getGpa() const { return gpa; }
    int getEnrollmentYear() const { return enrollmentYear; }

    void enrollCourse(string course) {
        coursesEnrolled.push_back(course);
    }

    void displayInfo() override {
        Person::displayInfo();
        cout << "Role: Student\n";
        cout << "Enrollment Year: " << enrollmentYear << "\n";
        cout << "GPA: " << gpa << "\n";
        cout << "Courses Enrolled: ";
        for (const auto& course : coursesEnrolled) {
            cout << course << ", ";
        }
        cout << "\n";
    }
};

class Professor : public Person {
private:
    string department;
    vector<string> coursesTaught;
    double salary;

public:
    Professor(string n, string i, string dept, double sal, string addr = "", string phone = "", string mail = "")
        : Person(n, i, addr, phone, mail), department(dept), salary(sal) {}

    // Getters
    string getDepartment() const { return department; }
    vector<string> getCoursesTaught() const { return coursesTaught; }
    double getSalary() const { return salary; }

    void assignCourse(string course) {
        coursesTaught.push_back(course);
    }

    void displayInfo() override {
        Person::displayInfo();
        cout << "Role: Professor\n";
        cout << "Department: " << department << "\n";
        cout << "Salary: $" << salary << "\n";
        cout << "Courses Taught: ";
        for (const auto& course : coursesTaught) {
            cout << course << ", ";
        }
        cout << "\n";
    }
};

class Staff : public Person {
private:
    string department;
    string position;
    double salary;

public:
    Staff(string n, string i, string dept, string pos, double sal, string addr = "", string phone = "", string mail = "")
        : Person(n, i, addr, phone, mail), department(dept), position(pos), salary(sal) {}

    // Getters
    string getDepartment() const { return department; }
    string getPosition() const { return position; }
    double getSalary() const { return salary; }

    void displayInfo() override {
        Person::displayInfo();
        cout << "Role: Staff\n";
        cout << "Department: " << department << "\n";
        cout << "Position: " << position << "\n";
        cout << "Salary: $" << salary << "\n";
    }
};

class Course {
private:
    string courseId;
    string courseName;
    int credits;
    string instructor;
    string schedule;

public:
    Course(string id, string name, int cred, string instr = "", string sched = "")
        : courseId(id), courseName(name), credits(cred), instructor(instr), schedule(sched) {}

    // Getters
    string getCourseId() const { return courseId; }
    string getCourseName() const { return courseName; }
    int getCredits() const { return credits; }
    string getInstructor() const { return instructor; }
    string getSchedule() const { return schedule; }

    void registerStudent(Student& student) {
        student.enrollCourse(courseName);
        cout << student.getName() << " enrolled in " << courseName << endl;
    }

    void displayInfo() {
        cout << "Course ID: " << courseId << "\n";
        cout << "Course Name: " << courseName << "\n";
        cout << "Credits: " << credits << "\n";
        if (!instructor.empty()) cout << "Instructor: " << instructor << "\n";
        if (!schedule.empty()) cout << "Schedule: " << schedule << "\n";
    }
};

int main() {
    vector<Person*> people;
    
    Student* s = new Student("Alice", "S001", 3.8, 2022, "123 College St", "555-1234", "alice@uni.edu");
    Professor* p = new Professor("Dr. Smith", "P001", "Computer Science", 80000, "456 Faculty Ave", "555-5678", "smith@uni.edu");
    Staff* st = new Staff("Bob Johnson", "ST001", "Administration", "Registrar", 50000, "789 Admin Blvd", "555-9012", "bob@uni.edu");
    
    people.push_back(s);
    people.push_back(p);
    people.push_back(st);
    
    Course cs101("CS101", "Introduction to Programming", 4, "Dr. Smith", "Mon/Wed 10:00-11:30");
    
    for (auto person : people) {
        person->displayInfo();
        cout << "-----------------\n";
    }
    
    cs101.displayInfo();
    cs101.registerStudent(*s);
    
    // Demonstrate getter usage
    cout << "\nUsing getters:\n";
    cout << "Student name: " << s->getName() << endl;
    cout << "Professor department: " << p->getDepartment() << endl;
    cout << "Staff position: " << st->getPosition() << endl;
    cout << "Course name: " << cs101.getCourseName() << endl;
    
    // Clean up
    for (auto person : people) {
        delete person;
    }
    
    return 0;
}