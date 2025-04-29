#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class User {
protected:
    string name, email, password, profilePhoto;
public:
    User(string n, string e, string p, string photo) : name(n), email(e), password(p), profilePhoto(photo) {}
    virtual void viewProfile() const {
        cout << "Name: " << name << "\nEmail: " << email << "\nProfile Photo: " << profilePhoto << "\n";
    }
    virtual void updateProfile() {
        cout << "Enter new name: "; cin >> name;
        cout << "Enter new profile photo: "; cin >> profilePhoto;
    }
    string getEmail() const { return email; }
    string getPassword() const { return password; }
};

class Job {
public:
    int id;
    string title, description, location, jobType, experience, position, requirement, role;
    int salary;

    Job(int i, string t, string desc, string l, string jt, string exp, string pos, string req, string r, int s)
        : id(i), title(t), description(desc), location(l), jobType(jt), experience(exp),
          position(pos), requirement(req), role(r), salary(s) {}

    void display() const {
        cout << "\nID: " << id
             << "\nTitle: " << title
             << "\nDescription: " << description
<< "\nLocation: " << location
             << "\nJob Type: " << jobType
             << "\nExperience: " << experience
             << "\nPosition: " << position
             << "\nRequirement: " << requirement
             << "\nRole: " << role
             << "\nSalary: " << salary << "\n";
    }
};

class Student : public User {
public:
    string skills, bio, resume;
    vector<int> appliedJobs;
    Student(string n, string e, string p, string photo) : User(n, e, p, photo) {}
    void viewProfile() const override {
        User::viewProfile();
        cout << "Skills: " << skills << "\nBio: " << bio << "\nResume: " << resume << "\n";
    }
    void updateProfile() override {
        User::updateProfile();
        cout << "Enter skills: "; cin.ignore(); getline(cin, skills);
        cout << "Enter bio: "; getline(cin, bio);
        cout << "Enter resume path: "; getline(cin, resume);
    }
    void searchJobs(const vector<Job>& jobs, const string& keyword) {
        for (const auto& job : jobs) {
            if (job.title.find(keyword) != string::npos || job.role.find(keyword) != string::npos) {
                job.display();
            }
        }
    }
    void filterJobs(const vector<Job>& jobs, const string& location, const string& role, int minSalary) {
        for (const auto& job : jobs) {
            if ((location.empty() || job.location == location) &&
                (role.empty() || job.role == role) &&
                (minSalary == 0 || job.salary >= minSalary)) {
                job.display();
                cout << "Apply to this job? (y/n): ";
                char ch; cin >> ch;
                if (ch == 'y') applyJob(job.id);
            }
        }
    }
    void applyJob(int jobId) {
        appliedJobs.push_back(jobId);
        cout << "Applied to job ID " << jobId << " successfully.\n";
    }
};

class Recruiter : public User {
public:
    vector<int> postedJobs;
    Recruiter(string n, string e, string p, string photo) : User(n, e, p, photo) {}

    void postJob(vector<Job>& jobs, int& jobIdCounter) {
        string title, description, location, jobType, experience, position, requirement, role;
        int salary;

        cin.ignore();
        cout << "Enter job title: "; getline(cin, title);
        cout << "Enter job description: "; getline(cin, description);
        cout << "Enter location: "; getline(cin, location);
        cout << "Enter job type (Full-time/Part-time/Internship): "; getline(cin, jobType);
        cout << "Enter required experience: "; getline(cin, experience);
        cout << "Enter position: "; getline(cin, position);
        cout << "Enter job requirement: "; getline(cin, requirement);
        cout << "Enter role: "; getline(cin, role);
        cout << "Enter salary: "; cin >> salary;

        jobs.emplace_back(jobIdCounter, title, description, location, jobType, experience, position, requirement, role, salary);
        postedJobs.push_back(jobIdCounter);
        cout << "Job posted with ID " << jobIdCounter << "\n";
        jobIdCounter++;
    }

    void updateJob(vector<Job>& jobs) {
        cout << "Your Posted Jobs:\n";
        for (int id : postedJobs) {
            for (auto& job : jobs) {
                if (job.id == id) {
                    job.display();
                    break;
                }
            }
        }

        int jobId;
        cout << "Enter Job ID to update: ";
        cin >> jobId;

        auto it = find(postedJobs.begin(), postedJobs.end(), jobId);
        if (it == postedJobs.end()) {
            cout << "You have not posted job ID " << jobId << ".\n";
            return;
        }

        for (auto& job : jobs) {
            if (job.id == jobId) {
                cin.ignore();
                cout << "Enter new title: "; getline(cin, job.title);
                cout << "Enter new description: "; getline(cin, job.description);
                cout << "Enter new location: "; getline(cin, job.location);
                cout << "Enter new job type: "; getline(cin, job.jobType);
                cout << "Enter new experience: "; getline(cin, job.experience);
                cout << "Enter new position: "; getline(cin, job.position);
                cout << "Enter new requirement: "; getline(cin, job.requirement);
                cout << "Enter new role: "; getline(cin, job.role);
                cout << "Enter new salary: "; cin >> job.salary;
                cout << "Job updated successfully.\n";
                return;
            }
        }
    }

    void reviewApplications(const vector<Student>& students) {
        for (const auto& s : students) {
            for (int jid : s.appliedJobs) {
                cout << s.getEmail() << " applied for job ID " << jid << ". Approve (a) or Reject (r)? ";
                char ch; cin >> ch;
                if (ch == 'a') cout << "Application approved.\n";
                else cout << "Application rejected.\n";
            }
        }
    }
};

class Company {
public:
    string name, location, description, website, logo;
    Company(string n, string l, string d, string w, string logo)
        : name(n), location(l), description(d), website(w), logo(logo) {}
    void display() const {
        cout << "Company: " << name << " | Location: " << location << "\n"
             << "Description: " << description << "\nWebsite: " << website
             << "\nLogo: " << logo << "\n";
    }
    void update() {
        cin.ignore();
        cout << "Enter new name: "; getline(cin, name);
        cout << "Enter new location: "; getline(cin, location);
        cout << "Enter new description: "; getline(cin, description);
        cout << "Enter new website: "; getline(cin, website);
        cout << "Enter new logo: "; getline(cin, logo);
    }
};

class Admin : public User {
public:
    Admin(string n, string e, string p, string photo) : User(n, e, p, photo) {}

    void createCompany(vector<Company>& companies) {
        string name, location, description, website, logo;
        cin.ignore();
        cout << "Enter company name: "; getline(cin, name);
        cout << "Enter location: "; getline(cin, location);
        cout << "Enter description: "; getline(cin, description);
        cout << "Enter website: "; getline(cin, website);
        cout << "Enter company logo path: "; getline(cin, logo);
        companies.emplace_back(name, location, description, website, logo);
        cout << "Company created successfully.\n";
    }

    void updateCompany(vector<Company>& companies) {
        for (int i = 0; i < companies.size(); ++i) {
            cout << i << ". "; companies[i].display();
        }
        int idx;
        cout << "Enter index of company to update: "; cin >> idx;
        if (idx >= 0 && idx < companies.size()) companies[idx].update();
        else cout << "Invalid index.\n";
    }

    void viewApplicationStats(const vector<Student>& students) {
        cout << "Application stats:\n";
        for (const auto& s : students) {
            cout << s.getEmail() << " applied to " << s.appliedJobs.size() << " job(s).\n";
        }
    }
};

bool login(const string& email, const string& password, const vector<Student>& students, Student*& sPtr) {
    for (auto& s : students) {
        if (s.getEmail() == email && s.getPassword() == password) {
            sPtr = const_cast<Student*>(&s);
            return true;
        }
    }
    return false;
}

bool login(const string& email, const string& password, const vector<Recruiter>& recruiters, Recruiter*& rPtr) {
    for (auto& r : recruiters) {
        if (r.getEmail() == email && r.getPassword() == password) {
            rPtr = const_cast<Recruiter*>(&r);
            return true;
        }
    }
    return false;
}

bool login(const string& email, const string& password, const vector<Admin>& admins, Admin*& aPtr) {
    for (auto& a : admins) {
        if (a.getEmail() == email && a.getPassword() == password) {
            aPtr = const_cast<Admin*>(&a);
            return true;
        }
    }
    return false;
}

int main() {
    vector<Student> students;
    vector<Recruiter> recruiters;
    vector<Admin> admins;
    vector<Job> jobs;
    vector<Company> companies;
    int jobIdCounter = 1;

    while (true) {
        cout << "\n--- Job Portal ---\n1. Signup\n2. Login\n3. Exit\nChoose: ";
        int choice; cin >> choice;

        if (choice == 1) {
            string name, email, pass, role, photo;
            cout << "Name: "; cin >> name;
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;
            cout << "Role (student/recruiter/admin): "; cin >> role;
            cout << "Profile photo: "; cin >> photo;

            if (role == "student") {
                students.emplace_back(name, email, pass, photo);
                cout << "Student signed up.\n";
            } else if (role == "recruiter") {
                recruiters.emplace_back(name, email, pass, photo);
                cout << "Recruiter signed up.\n";
            } else if (role == "admin") {
                admins.emplace_back(name, email, pass, photo);
                Admin* admin = &admins.back();
                cout << "Admin signed up and logged in.\n";
                while (true) {
                    cout << "\nAdmin Menu:\n1. Create Company\n2. Update Company\n3. View Application Stats\n4. Logout\nChoose: ";
                    int c; cin >> c;
                    if (c == 1) admin->createCompany(companies);
                    else if (c == 2) admin->updateCompany(companies);
                    else if (c == 3) admin->viewApplicationStats(students);
                    else break;
                }
            }

        } else if (choice == 2) {
            string email, pass;
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;

            Student* s = nullptr;
            Recruiter* r = nullptr;
            Admin* a = nullptr;

            if (login(email, pass, students, s)) {
                while (true) {
                    cout << "\nStudent Menu:\n1. View Profile\n2. Update Profile\n3. Search Jobs\n4. Filter Jobs\n5. Apply for Job\n6. Logout\nChoose: ";
                    int c; cin >> c;
                    if (c == 1) s->viewProfile();
                    else if (c == 2) s->updateProfile();
                    else if (c == 3) {
                        string kw; cout << "Keyword: "; cin >> kw;
                        s->searchJobs(jobs, kw);
                    } else if (c == 4) {
                        string loc, role; int sal;
                        cout << "Location: "; cin >> loc;
                        cout << "Role: "; cin >> role;
                        cout << "Min Salary: "; cin >> sal;
                        s->filterJobs(jobs, loc, role, sal);
                    } else if (c == 5) {
                        int jid; cout << "Job ID: "; cin >> jid;
                        s->applyJob(jid);
                    } else break;
                }

            } else if (login(email, pass, recruiters, r)) {
                while (true) {
                    cout << "\nRecruiter Menu:\n1. Post Job\n2. Review Applications\n3. Update Job\n4. Logout\nChoose: ";
                    int c; cin >> c;
                    if (c == 1) r->postJob(jobs, jobIdCounter);
                    else if (c == 2) r->reviewApplications(students);
                    else if (c == 3) r->updateJob(jobs);
                    else break;
                }

            } else if (login(email, pass, admins, a)) {
                while (true) {
                    cout << "\nAdmin Menu:\n1. Create Company\n2. Update Company\n3. View Application Stats\n4. Logout\nChoose: ";
                    int c; cin >> c;
                    if (c == 1) a->createCompany(companies);
                    else if (c == 2) a->updateCompany(companies);
                    else if (c == 3) a->viewApplicationStats(students);
                    else break;
                }
            } else {
                cout << "Invalid login.\n";
            }

        } else break;
    }
    return 0;
}
