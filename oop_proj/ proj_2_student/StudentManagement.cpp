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
    char name[16];        // 이름: 최대 15자, 영어
    char studentID[11];   // 학번: 10자리, 앞 4자리 입학년도
    char birthYear[5];    // 생년: 4자리
    char department[36];  // 학과
    char tel[13];         // 번호: 최대 12자
};

vector<Student> students;

const char* fileName = "file1.txt"; // 학생 정보
int initialSortOption = 1; // 초기 정렬, 이름 순
int* sortOption = &initialSortOption;

// 오름차순
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

// 파일에서 학생 정보를 읽기
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
        // 파일이 존재하지 않는 경우, 파일을 생성
        ofstream createFile(fileName, ios::out | ios::binary);
        if (!createFile) {
            cout << "Error: Unable to create the file." << endl;
            exit(1);
        }
        createFile.close();
    }
}

// 학생 정보 파일에 저장
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

// 영어로만 구성되는지(이름)
bool isEnglish(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && !isspace(str[i])) {
            return false;
        }
    }
    return true;
}

// 숫자로만 구성되는지(이름,학부 외)
bool isNum(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && !isspace(str[i])) {
            return false;
        }
    }
    return true;
}

// 학생 정보 입력
void insertInfo(int* sortOption) {
    Student student;
    bool validInput = false;

    // 이름: 필수, 최대 15자, 영어
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

    // 학번: 필수, 10자리, 앞 4자리는 입학년도
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

    // 생년: 4자리
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

    // 학과
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

    // 번호: 최대 12자
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

    // 이전의 정렬 옵션으로 다시 정렬
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

// 학생 정보 검색 
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

// 학생 정보 정렬
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
    loadInfo(); // 파일에서 학생 정보 읽기

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
