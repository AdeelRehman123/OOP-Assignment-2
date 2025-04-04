#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HashGenerator {
public:
    static int generateHash(const string& input) {
        int hash = 5381;
        for (char c : input) {
            hash = (hash * 33) + c;
        }
        return hash;
    }
};

class User {
protected:
    string name;
    int id;
    vector<string> permissions;
    string email;
    int hashed_password;

public:
    User(int id, const string& name, const vector<string>& permissions, const string& email, const string& pass)
        : id(id), name(name), email(email), permissions(permissions) {
        hashed_password = HashGenerator::generateHash(pass);
    }

    bool authenticate(const string& inputPassword) {
        return this->hashed_password == HashGenerator::generateHash(inputPassword);
    }

    const string& getName() const { return name; }
    const vector<string>& getPermissions() const { return permissions; }

    virtual void displayInfo() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Permissions: ";
        for (const string& permission : permissions) {
            cout << permission << " ";
        }
        cout << endl;
    }
};

class Student : public User {
private:
    vector<int> assignments;

public:
    Student(int id, const string& name, const vector<string>& permissions, const string& email, const string& pass)
        : User(id, name, permissions, email, pass) {}

    void submitAssignment(int index) {
        if (index >= 0 && index < assignments.size()) {
            assignments[index] = 1;
        }
    }

    void assignAssignment(int index) {
        while (assignments.size() <= index) {
            assignments.push_back(0);
        }
    }

    void displayInfo() const override {
        User::displayInfo();
        cout << "Assignment Status: ";
        for (int status : assignments) {
            cout << status << " ";
        }
        cout << endl;
    }
};

class TA : public Student {
private:
    vector<Student> students;
    vector<string> projects;

public:
    TA(int id, const string& name, const vector<string>& permissions, const string& email, const string& pass)
        : Student(id, name, permissions, email, pass) {}

    void viewProjects() const {
        cout << "Projects: ";
        for (const string& project : projects) {
            cout << project << " ";
        }
        cout << endl;
    }

    void workOnNewProject(const string& project) {
        if (projects.size() < 2) {
            projects.push_back(project);
            cout << "Assigned new project: " << project << endl;
        } else {
            cout << "Can't exceed limit of 2 projects" << endl;
        }
    }

    void assignStudentToTA(const Student& student) {
        if (students.size() < 10) {
            students.push_back(student);
            cout << "Assigned student: " << student.getName() << endl;
        } else {
            cout << "Cannot assign more than 10 students to a TA" << endl;
        }
    }

    void displayInfo() const override {
        Student::displayInfo();
        cout << "Students assigned: ";
        for (const Student& student : students) {
            cout << student.getName() << " ";
        }
        cout << endl;
    }
};

class Professor : public User {
private:
    vector<TA> tas;
    vector<string> projects;

public:
    Professor(int id, const string& name, const vector<string>& permissions, const string& email, const string& pass)
        : User(id, name, permissions, email, pass) {}

    void assignProject(const string& project) {
        projects.push_back(project);
        cout << "Assigned new project: " << project << endl;
    }

    void assignTA(const TA& ta) {
        tas.push_back(ta);
        cout << "Assigned TA: " << ta.getName() << endl;
    }

    void workWithTAonProject(TA& ta, const string& project) {
        for (const auto& t : tas) {
            if (t.getName() == ta.getName()) {
                ta.workOnNewProject(project);
                return;
            }
        }
        cout << "TA not assigned." << endl;
    }

    void displayInfo() const override {
        User::displayInfo();
        cout << "Assigned TAs: ";
        for (const TA& ta : tas) {
            cout << ta.getName() << " ";
        }
        cout << endl;
    }
};

void authenticateAndPerformAction(User& user, const string& action) {
    if (action == "view lab") {
        bool hasPermission = false;
        for (const string& permission : user.getPermissions()) {
            if (permission == "view lab") {
                hasPermission = true;
                break;
            }
        }

        if (hasPermission) {
            cout << user.getName() << " is viewing the lab." << endl;
        } else {
            cout << user.getName() << " does not have permission to view the lab." << endl;
        }
    } else if (action == "submit assignment" && dynamic_cast<Student*>(&user)) {
        static_cast<Student&>(user).submitAssignment(0);
        cout << user.getName() << " submitted an assignment." << endl;
    } else if (action == "view projects" && dynamic_cast<TA*>(&user)) {
        static_cast<TA&>(user).viewProjects();
    } else {
        cout << "Action not permitted for this user." << endl;
    }
}

int main() {
    vector<string> studentPermissions = {"submit assignment"};
    vector<string> taPermissions = {"view projects", "manage_students"};
    vector<string> professorPermissions = {"assign projects", "full_lab_access"};

    Student student(1, "Danish", studentPermissions, "dan@ex.yyy", "password123");
    TA ta(2, "Ali", taPermissions, "ali@example.com", "password123");
    Professor professor(3, "Rafay", professorPermissions, "y27@ff.com", "admin123");

    professor.assignProject("Research Project 1");
    professor.assignTA(ta);

    student.assignAssignment(0);
    student.displayInfo();
    ta.displayInfo();
    professor.displayInfo();

    authenticateAndPerformAction(student, "submit assignment");
    authenticateAndPerformAction(ta, "view projects");
    authenticateAndPerformAction(professor, "assign projects");

    return 0;
}
