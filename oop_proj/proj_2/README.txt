# Student Information Management System

이 프로그램은 학생 정보를 관리하는 간단한 콘솔 애플리케이션입니다. 사용자는 학생 정보를 추가하고, 검색하며, 정렬할 수 있습니다.

## 주요 기능

1. **Insertion (학생 정보 입력)**
   - 프로그램에 학생 정보를 추가합니다.
   - 학생의 이름, 학번, 생년, 학과, 전화번호를 입력할 수 있습니다.
   - 이름은 최대 15자 이내, 영어로만 구성되어야 합니다.             -> 그렇지 않을 시 에러 발생 시킴
   - 학번은 10자리여야 하며, 앞 4자리는 입학년도를 나타내야 합니다.  -> 그렇지 않을 시 에러 + 숫자만 받도록 검사
   - 생년은 4자리여야 합니다.                                      -> 그렇지 않을 시 에러 + 숫자만 받도록 검사
   - 학과는 최대 36자 이내의 문자열입니다.                          -> 사이즈 수정 가능
   - 전화번호는 최대 12자리 숫자로 입력됩니다.                      -> 그렇지 않을 시 에러 + 숫자만 받도록 검사

2. **Search (학생 정보 검색)**
   - 학생 정보를 이름, 학번, 입학년도, 학과로 검색할 수 있습니다.   -> 검색 조건(사이즈 등) 안맞을 시 에러 발생 시킴
   - 검색 결과를 표시합니다.
   - 모든 학생 정보를 나열하는 옵션도 있습니다.                    -> display 함수 호출

3. **Sorting Option (정렬 옵션)**
   - 학생 정보를 이름, 학번, 입학년도, 학과로 정렬할 수 있습니다.
   - 정렬 옵션을 선택하여 학생 정보를 정렬합니다.
   - 초기값은 이름순으로 나열하도록 설정합니다.

4. **Exit (프로그램 종료)**
   - 프로그램을 종료합니다.

## 사용법

프로그램 실행 후, 메뉴에서 원하는 작업을 선택하세요. 작업을 선택하면 해당 작업을 수행하는 서브메뉴가 나타납니다. 각 서브메뉴는 사용자 입력을 기다립니다. 

학생 정보를 추가하면 프로그램이 정보를 저장하고, 검색 및 정렬 작업에서 사용자가 필요한 정보를 얻을 수 있습니다. 

프로그램을 종료하려면 메인 화면에서 '4. Exit' 메뉴를 선택합니다.

***

# Student Information Management System

This program is a simple console application for managing student information. Users can add, search, and sort student records.

## Key Features

1. **Insertion (Adding Student Information)**
   - Allows users to add student information to the program.
   - Information includes the student's name, student ID, birth year, department, and telephone number.
   - Name should be within 15 characters and must consist of English letters only. If not, it will trigger an error.
   - Student ID must be 10 digits, with the first 4 digits representing the admission year. If not, it will trigger an error and ensure it's numeric.
   - Birth year should be a 4-digit number. If not, it will trigger an error and ensure it's numeric.
   - The department name can be up to 36 characters. You can adjust this size.
   - Telephone number can be up to 12 digits and must be numeric. If not, it will trigger an error.

2. **Search (Student Information Search)**
   - Allows users to search for student information by name, student ID, admission year, or department. It will check for size constraints and trigger errors if not met.
   - Displays search results.
   - Includes an option to list all student information. It will call the display function.

3. **Sorting Option (Change Sorting Criteria)**
   - Allows users to sort student information by name, student ID, admission year, or department.
   - Choose a sorting option to arrange the student records accordingly.
   - The initial sorting is by name.

4. **Exit (Program Termination)**
   - Exits the program.

## Usage

After running the program, select the desired operation from the menu. Once an operation is chosen, a submenu for that operation will appear, waiting for user input.

When you add student information, the program saves the information, which can then be retrieved in search and sort operations.

To exit the program, select '4. Exit' from the menu.
