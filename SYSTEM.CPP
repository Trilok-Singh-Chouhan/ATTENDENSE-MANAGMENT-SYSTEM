#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class AttendanceSystem {
private:
    const string studentFile = "students.txt";
    const string attendanceFile = "attendance.txt";

    bool fileExists(const string& filename) {
        ifstream file(filename);
        return file.good();
    }

public:
    
    void addStudent() {
        ofstream file(studentFile, ios::app);
        if (!file) {
            cout << "Error opening student file!\n";
            return;
        }

        int roll;
        string name;

        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);

        file << roll << " " << name << endl;
        file.close();

        cout << "Student added successfully!\n";
    }

    
    void markAttendance() {
    ifstream students(studentFile);
    ofstream attendance(attendanceFile, ios::app);

    if (!students || !attendance) {
        cout << "File error occurred!\n";
        return;
    }

    string date;
    cout << "Enter Date (DD-MM-YYY): ";
    cin >> date;
    cin.ignore(); 

    string line, name, status;
    int roll;
    char ch;

    cout << "\n--- Mark Attendance (Each Student) ---\n";

    while (getline(students, line)) {
        if (line.empty()) continue;

        
        int pos = line.find(' ');
        roll = stoi(line.substr(0, pos));
        name = line.substr(pos + 1);

        
        while (true) {
            cout << "Roll: " << roll
                 << "  Name: " << name
                 << "  (P/A): ";
            cin >> ch;

            if (ch == 'P' || ch == 'p') {
                status = "Present";
                break;
            }
            else if (ch == 'A' || ch == 'a') {
                status = "Absent";
                break;
            }
            else {
                cout << "Invalid input! Enter only P or A.\n";
            }
        }

        attendance << roll << " " << name << " "
                   << date << " " << status << endl;
    }

    students.close();
    attendance.close();

    cout << "\nAttendance marked for ALL students successfully!\n";
}


    
    void viewAttendance() {
    ifstream students(studentFile);
    ifstream attendance(attendanceFile);

    if (!students || !attendance) {
        cout << "Required files not found!\n";
        return;
    }

    cout << "\nID   Name                           Present(%)   Absent(%)\n";
    cout << "------------------------------------------------------------\n";

    string studentLine;

    while (getline(students, studentLine)) {
        if (studentLine.empty()) continue;

      
        int roll = 0, i = 0;
        while (i < studentLine.length() && studentLine[i] != ' ') {
            roll = roll * 10 + (studentLine[i] - '0');
            i++;
        }

        string name = studentLine.substr(i + 1);

        int present = 0, absent = 0;

        attendance.clear();
        attendance.seekg(0, ios::beg);

        string attLine;
        while (getline(attendance, attLine)) {
            if (attLine.empty()) continue;

         
            int aRoll = 0, j = 0;
            while (j < attLine.length() && attLine[j] != ' ') {
                aRoll = aRoll * 10 + (attLine[j] - '0');
                j++;
            }

            if (aRoll != roll) continue;

          
            int lastSpace = attLine.find_last_of(' ');
            if (lastSpace == string::npos) continue;

            string status = attLine.substr(lastSpace + 1);

            if (status == "Present")
                present++;
            else if (status == "Absent")
                absent++;
        }

        int total = present + absent;
        double pPct = 0.0, aPct = 0.0;

        if (total > 0) {
            pPct = (present * 100.0) / total;
            aPct = (absent * 100.0) / total;
        }

      
        pPct = (int)(pPct * 100 + 0.5) / 100.0;
        aPct = (int)(aPct * 100 + 0.5) / 100.0;

      
        cout << roll << "  ";

        cout << name;
        for (int s = name.length(); s < 14; s++)
            cout << " ";

        cout << "              ";

        if (pPct < 10) cout << " ";
        cout << pPct << "        ";

        if (aPct < 10) cout << " ";
        cout << aPct << endl;
    }

    students.close();
    attendance.close();
}

    
    void run() {
        int choice;

        do {
            cout << "\n<--------Attendance Management System-------->\n";
            cout << "1. Add Student\n";
            cout << "2. Mark Attendance\n";
            cout << "3. View Attendance\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addStudent();
                    
                    break;
                case 2:
                    markAttendance();
                    break;
                case 3:
                    viewAttendance();
                    break;
                case 4:
                    cout << "Exiting program...\n";
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 4);
    }
};


int main() {
    AttendanceSystem system;
    system.run();
    return 0;
}
