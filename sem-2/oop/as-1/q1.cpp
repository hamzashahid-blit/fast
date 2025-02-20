#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward declarations
class Mentor;
class Sport;
class Skill;

// Skill class
class Skill {
private:
    int skillID;
    string skillName;
    string description;

public:
    Skill(int id, string name, string desc)
        : skillID(id), skillName(name), description(desc) {}

    void showSkillDetails() const {
        cout << "Skill ID: " << skillID << endl;
        cout << "Skill Name: " << skillName << endl;
        cout << "Description: " << description << endl;
    }

    void updateSkillDescription(string newDescription) {
        description = newDescription;
    }

    int getSkillID() { return skillID; }
};

// Sport class
class Sport {
private:
    int sportID;
    string name;
    string description;
    vector<Skill> requiredSkills;

public:
    Sport(int id, string n, string desc)
        : sportID(id), name(n), description(desc) {}

    void addSkill(const Skill& skill) {
        requiredSkills.push_back(skill);
    }

    void removeSkill(int skillID) {
        for (auto it = requiredSkills.begin(); it != requiredSkills.end(); ++it) {
            if (it->getSkillID() == skillID) {
                requiredSkills.erase(it);
                break;
            }
        }
    }

    void showSportDetails() const {
        cout << "Sport ID: " << sportID << endl;
        cout << "Sport Name: " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Required Skills: " << endl;
        for (const auto& skill : requiredSkills) {
            skill.showSkillDetails();
        }
    }

    int getSportID() const { return sportID; }

};

// Student class
class Student {
private:
    int studentID;
    string name;
    int age;
    vector<string> sportsInterests;
    Mentor* mentorAssigned;

public:
    Student(int id, string n, int a)
        : studentID(id), name(n), age(a), mentorAssigned(nullptr) {}

    void registerForMentorship(Mentor& mentor);

    void viewMentorDetails() const;

    void updateSportsInterest(const string& sport) {
        sportsInterests.push_back(sport);
    }

    int getStudentID() const { return studentID; }
    string getName() const { return name; }
};

// Mentor class
class Mentor {
private:
    int mentorID;
    string name;
    vector<string> sportsExpertise;
    int maxLearners;
    vector<Student*> assignedLearners;

public:
    Mentor(int id, string n, int max)
        : mentorID(id), name(n), maxLearners(max) {}

    void assignLearner(Student& student) {
        if (assignedLearners.size() < maxLearners) {
            assignedLearners.push_back(&student);
            cout << student.getName() << " has been assigned to mentor " << name << endl;
        } else {
            cout << "Mentor " << name << " has reached maximum capacity. Cannot assign " << student.getName() << endl;
        }
    }

    void removeLearner(Student& student) {
        for (auto it = assignedLearners.begin(); it != assignedLearners.end(); ++it) {
            if ((*it)->getStudentID() == student.getStudentID()) {
                assignedLearners.erase(it);
                cout << student.getName() << " has been removed from mentor " << name << endl;
                break;
            }
        }
    }

    void viewLearners() const {
        cout << "Mentor " << name << "'s assigned learners: " << endl;
        for (const auto& learner : assignedLearners) {
            cout << "- " << learner->getName() << endl;
        }
    }

    void provideGuidance() const {
        cout << "Mentor " << name << " is providing guidance to learners." << endl;
    }

    int getMentorID() const { return mentorID; }
    string getName() const { return name; }
};

// Student methods
void Student::registerForMentorship(Mentor& mentor) {
    mentor.assignLearner(*this);
    mentorAssigned = &mentor;
}

void Student::viewMentorDetails() const {
    if (mentorAssigned) {
        cout << "Mentor Details:" << endl;
        cout << "Mentor ID: " << mentorAssigned->getMentorID() << endl;
        cout << "Mentor Name: " << mentorAssigned->getName() << endl;
    } else {
        cout << "No mentor assigned." << endl;
    }
}

int main() {
    // Create some skills
    Skill dribbling(1, "Dribbling", "Ability to control the ball while moving");
    Skill shooting(2, "Shooting", "Ability to score goals");

    // Create a sport
    Sport football(1, "Football", "A team sport played with a ball");
    football.addSkill(dribbling);
    football.addSkill(shooting);

    // Create a mentor
    Mentor ali(101, "Ali", 3); // Ali can mentor up to 3 students

    // Create students
    Student saad(201, "Saad", 20);
    Student ahmed(202, "Ahmed", 21);
    Student sana(203, "Sana", 22);
    Student aliStudent(204, "Ali Student", 19);

    // Register students for mentorship
    saad.registerForMentorship(ali);
    ahmed.registerForMentorship(ali);
    sana.registerForMentorship(ali);
    aliStudent.registerForMentorship(ali); // This should fail as Ali's capacity is full

    // View mentor details
    saad.viewMentorDetails();

    // View assigned learners
    ali.viewLearners();

    // Remove a learner
    ali.removeLearner(saad);

    // View assigned learners again
    ali.viewLearners();

    // Provide guidance
    ali.provideGuidance();

    return 0;
}
