#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

struct Student {
    char name[16];        // �̸�: �ִ� 15��, ����
    char studentID[11];   // �й�: 10�ڸ�, �� 4�ڸ� ���г⵵
    char birthYear[5];    // ����: 4�ڸ�
    char department[36];  // �а�
    char tel[13];         // ��ȣ: �ִ� 12��
};

vector<Student> students;

const char* fileName = "file1.txt"; // �л� ����
int initialSortOption = 1; // �ʱ� ����, �̸� ��
int* sortOption = &initialSortOption;

// ��������
void sortByName() {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return strcmp(a.name, b.name) < 0;
        });
}

void sortByStudentID() {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return strcmp(a.studentID, b.studentID) < 0;
        });
}

void sortByAdmissionYear() {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        char yearA[5], yearB[5];
        strncpy_s(yearA, a.studentID, 4);
        strncpy_s(yearB, b.studentID, 4);
        yearA[4] = yearB[4] = '\0';

        return strcmp(yearA, yearB) < 0;
        });
}

void sortByDepartment() {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return strcmp(a.department, b.department) < 0;
        });
}

// ���Ͽ��� �л� ������ �б�
void loadInfo() {
    ifstream file(fileName, ios::in | ios::binary);

    if (file) {
        Student student;
        while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            students.push_back(student);
         }
        file.close();
        sortByName();
    }
    else {
        // ������ �������� �ʴ� ���, ������ ����
        ofstream createFile(fileName, ios::out | ios::binary);
        if (!createFile) {
            cout << "Error: Unable to create the file." << endl;
            exit(1);
        }
        createFile.close();
    }
}

// �л� ���� ���Ͽ� ����
void saveInfo() {
    ofstream file(fileName, ios::out | ios::binary);
    for (const Student& student : students) {
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    }
    file.close();
}

void displayInfo() {
    const int nameWidth = 16;
    const int studentIDWidth = 15;
    const int departmentWidth = 36;
    const int birthYearWidth = 10;
    const int telWidth = 15;

    cout << "\n\t\t\tName\t\tStudentID\t\tDept\t\t\tBirth Year\tTel" << endl;

    for (const Student& student : students) {
        cout << "\n\t\t\t" << setw(nameWidth) << left << student.name;
        cout << setw(studentIDWidth) << left << student.studentID;
        cout << setw(departmentWidth) << left << student.department;
        cout << setw(birthYearWidth) << left << student.birthYear;
        cout << setw(telWidth) << left << student.tel << endl;
    }
}

// ����θ� �����Ǵ���(�̸�)
bool isEnglish(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && !isspace(str[i])) {
            return false;
        }
    }
    return true;
}

// ���ڷθ� �����Ǵ���(�̸�,�к� ��)
bool isNum(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && !isspace(str[i])) {
            return false;
        }
    }
    return true;
}

// �л� ���� �Է�
void insertInfo(int* sortOption) {
    Student student;
    bool validInput = false;

    // �̸�: �ʼ�, �ִ� 15��, ����
    do {
        cout << "\n\t\t\tName ? ";
        string input;
        getline(cin, input);

        if (input.empty() || input.length() > 15 || !isEnglish(input.c_str())) {
            cout << "\n\t\t\tError: Invalid Name. Name is a required field, up to 15 English letters." << endl;
        }
        else {
            strncpy_s(student.name, input.c_str(), sizeof(student.name));
            validInput = true;
        }
    } while (!validInput);

    validInput = false;

    // �й�: �ʼ�, 10�ڸ�, �� 4�ڸ��� ���г⵵
    do {
        cout << "\n\t\t\tStudent ID (10 digits) ? ";
        string input;
        getline(cin, input);
        if (input.length() == 10 && isNum(input.c_str())) {
            strncpy_s(student.studentID, input.c_str(), sizeof(student.studentID));
            bool alreadyExists = false;
            for (const Student& s : students) {
                if (strcmp(s.studentID, student.studentID) == 0) {
                    alreadyExists = true;
                    cout << "\n\t\t\tError: Already inserted." << endl;
                    break;
                }
            }
            if (!alreadyExists) {
                validInput = true;
            }
        }
        else {
            cout << "\n\t\t\tError: Invalid Student ID. Student ID must be a 10-digit number." << endl;
        }
    } while (!validInput);

    validInput = false;

    // ����: 4�ڸ�
    do {
        cout << "\n\t\t\tBirth Year (4 digits) ? ";
        string input;
        getline(cin, input);
        if (input.length() == 4 && isNum(input.c_str())) {
            strncpy_s(student.birthYear, input.c_str(), sizeof(student.birthYear));
            validInput = true;
        }
        else {
            cout << "\n\t\t\tError: Invalid Birth Year. Birth Year must be a 4-digit number." << endl;
        }
    } while (!validInput);

    validInput = false;

    // �а�
    do {
        cout << "\n\t\t\tDepartment ? ";
        string input;
        getline(cin, input);
        if (input.length() < sizeof(student.department)) {
            strncpy_s(student.department, input.c_str(), sizeof(student.department));
            validInput = true;
        }
        else {
            cout << "\n\t\t\tError: Department is too long." << endl;
        }
    } while (!validInput);

    validInput = false;

    // ��ȣ: �ִ� 12��
    do {
        cout << "\n\t\t\tTel ? ";
        string input;
        getline(cin, input);
        if (input.length() <= 12 && isNum(input.c_str())) {
            strncpy_s(student.tel, input.c_str(), sizeof(student.tel));
            validInput = true;
        }
        else {
            cout << "\n\t\t\tError: Invalid Tel. Please enter up to a 12-digit number." << endl;
        }
    } while (!validInput);

    students.push_back(student);

    // ������ ���� �ɼ����� �ٽ� ����
    switch (*sortOption) {
    case 1:
        sortByName();
        break;
    case 2:
        sortByStudentID();
        break;
    case 3:
        sortByAdmissionYear();
        break;
    case 4:
        sortByDepartment();
        break;
    }

    saveInfo();
    cout << "\n\t\t\t> Completely Inserted!" << endl;
}

// �л� ���� �˻� 
void searchInfo() {
    int getSearch;
    bool validInput = false;
    cout << "\n\t\t\t- Search -\n\t\t\t1. Search by name\n\t\t\t2. Search by student ID (10 numbers)\n\t\t\t3. Search by admission year (4 numbers)\n\t\t\t4. Search by department name\n\t\t\t5. List All" << endl;

    do {
        cout << "\n\t\t\tPress a Number (1 to 5): ";
        string input;
        getline(cin, input);

        if (input.empty() || input.length() > 1 || !isdigit(input[0])) {
            cout << "\n\t\t\tError : Invalid input. Please enter a valid number between 1 and 5." << endl;
        }
        else {
            getSearch = input[0] - '0';
            if (getSearch >= 1 && getSearch <= 5) {
                validInput = true;
            }
            else {
                cout << "\n\t\t\tError : Invalid input. Please enter a number between 1 and 5." << endl;
            }
        }
    } while (!validInput);
    validInput = false;

    switch (getSearch) {
    case 1: {
        char searchName[16];
        cout << "\n\t\t\tName keyword ? ";
        cin.getline(searchName, sizeof(searchName));

        cout << "\n\t\t\tName\tStudent ID\tDepartment\tBirth Year\tTel" << endl;
        bool found = false;
        for (const Student& student : students) {
            if (strstr(student.name, searchName) != nullptr) {
                cout << "\n\t\t\t" << student.name << "\t" << student.studentID << "\t" << student.department << "\t" << student.birthYear << "\t" << student.tel << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "\n\t\t\t\t\t\tNo records found" << endl;
        }
        break;
    }
    case 2: {
        char searchID[11];
        cout << "\n\t\t\tStudent ID (10 digits) ? ";
        cin.getline(searchID, sizeof(searchID));

        cout << "\n\t\t\tName\tStudent ID\tDepartment\tBirth Year\tTel" << endl;
        bool found = false;
        for (const Student& student : students) {
            if (strcmp(student.studentID, searchID) == 0) {
                cout << "\n\t\t\t" << student.name << "\t" << student.studentID << "\t" << student.department << "\t" << student.birthYear << "\t" << student.tel << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "\n\t\t\t\t\t\tNo records found" << endl;
        }
        break;
    }

    case 3: {
        char searchYear[5];
        cout << "\n\t\t\tAdmission year (4 numbers) ? ";
        cin.getline(searchYear, sizeof(searchYear));

        cout << "\n\t\t\tName\tStudent ID\tDepartment\tBirth Year\tTel" << endl;
        bool found = false;
        for (const Student& student : students) {
            bool match = true;
            for (int i = 0; i < 4; ++i) {
                if (student.studentID[i] != searchYear[i]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "\n\t\t\t" << student.name << "\t" << student.studentID << "\t" << student.department << "\t" << student.birthYear << "\t" << student.tel << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "\n\t\t\t\t\t\tNo records found" << endl;
        }
        break;
    }

    case 4: {
        char searchDepartment[36];
        cout << "\n\t\t\tDepartment name keyword ? ";
        cin.getline(searchDepartment, sizeof(searchDepartment));

        cout << "\n\t\t\tName\tStudent ID\tDepartment\tBirth Year\tTel" << endl;
        bool found = false;
        for (const Student& student : students) {
            if (strstr(student.department, searchDepartment) != nullptr) {
                cout << "\n\t\t\t" << student.name << "\t" << student.studentID << "\t" << student.department << "\t" << student.birthYear << "\t" << student.tel << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "\n\t\t\t\t\t\tNo records found" << endl;
        }
        break;
    }
    case 5:
        displayInfo();
        break;

    default:
        cout << "\n\t\t\tError : Invalid input. Please enter a valid number between 1 and 5." << endl;
        break;
    }
}

// �л� ���� ����
void sortInfo() {
    int getSort = *sortOption;
    bool validInput = false;

    cout << "\n\t\t\t - Search - \n\t\t\t1. Sort by Name\n\t\t\t2. Sort by Student ID\n\t\t\t3. Sort by Admission Year\n\t\t\t4. Sort by Department name\n\t\t\t" << endl;

    do {
        cout << "\n\t\t\tPress a Number (1 to 4): ";
        string input;
        getline(cin, input);

        if (input.empty() || input.length() > 1 || !isdigit(input[0])) {
            cout << "\n\t\t\tError: Invalid input. Please enter a valid number between 1 and 4." << endl;
        }
        else {
            getSort = input[0] - '0';
            if (getSort >= 1 && getSort <= 4) {
                validInput = true;
            }
            else {
                cout << "\n\t\t\tError: Invalid input. Please enter a number between 1 and 4." << endl;
            }
        }
    } while (!validInput);
    validInput = false;

    switch (getSort) {
    case 1:
        sortByName();
        break;
    case 2:
        sortByStudentID();
        break;
    case 3:
        sortByAdmissionYear();
        break;
    case 4:
        sortByDepartment();
        break;
    }
    *sortOption = getSort;
    saveInfo();
    cout << "\n\t\t\t> Completely Sorted!" << endl;
}

int main() {
    loadInfo(); // ���Ͽ��� �л� ���� �б�

    int getNumber;
    bool validInput = false;

    do {
        cout << "\n\t\t\t\t     =================================================== \n";
        cout << "\t\t\t\t     |     STUDENT INFORMATION MANAGEMENT SYSTEM       |\n";
        cout << "\t\t\t\t     =================================================== \n";
        cout << "\n\t\t\t\t";
        cout << "\n\t\t\t1. Insertion\n\t\t\t2. Search\n\t\t\t3. Sorting Option\n\t\t\t4. Exit\n";
        cout << "\n\t\t\t";

        do {
            cout << "\n\t\t\tPress a Number (1 to 4): ";
            string input;
            getline(cin, input);

            if (input.empty() || input.length() > 1 || !isdigit(input[0])) {
                cout << "\n\t\t\tError : Invalid input. Please enter a valid number between 1 and 4." << endl;
            }
            else {
                getNumber = input[0] - '0';
                if (getNumber >= 1 && getNumber <= 4) {
                    validInput = true;
                }
                else {
                    cout << "\n\t\t\tError : Invalid input. Please enter a number between 1 and 4." << endl;
                }
            }
        } while (!validInput);
        validInput = false;

        switch (getNumber) {
        case 1:
            insertInfo(sortOption);
            break;
        case 2:
            searchInfo();
            break;
        case 3:
            sortInfo();
            break;
        case 4:
            cout << "\n\n\n";
            cout << "\t\t\t\t     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
            cout << "\t\t\t\t    {                      BYE BYE                      }\n";
            cout << "\t\t\t\t     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
            break;
        default:
            cout << "\n\t\t\tError : Invalid input. Please enter a number between 1 and 4." << endl;
            break;
        }
    } while (getNumber != 4);

    return 0;
}
