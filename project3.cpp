#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

// Course struct
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function declarations
void loadCourses(const string& fileName, map<string, Course>& courseMap);
void displayAllCourses(const map<string, Course>& courseMap);
void displayCourseInformation(const map<string, Course>& courseMap, const string& courseNumber);
string toUpperCase(const string& str);
bool fileExists(const string& fileName);

int main() {
    map<string, Course> courseMap;
    int choice;
    const string defaultFileName = "CS 300 ABCU_Advising_Program_Inpu.csv";
    string fileName;

    do {
        // Display the menu
        cout << "\n--- Course Management Menu ---" << endl;
        cout << "1. Load Courses from File" << endl;
        cout << "2. Display All Courses" << endl;
        cout << "3. Display Course Information" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";

        // Validate user input to ensure it is numeric
        if (!(cin >> choice)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1: {
            if (fileExists(defaultFileName)) {
                loadCourses(defaultFileName, courseMap);
            }
            else {
                cout << "Default file \"" << defaultFileName << "\" not found. Please enter the file name: ";
                cin.ignore();
                getline(cin, fileName);
                if (fileExists(fileName)) {
                    loadCourses(fileName, courseMap);
                }
                else {
                    cout << "Error: File \"" << fileName << "\" does not exist. Please check the file name and try again." << endl;
                }
            }
            break;
        }
        case 2:
            displayAllCourses(courseMap);
            break;
        case 3: {
            string courseNumber;
            cout << "Enter course number: ";
            cin >> courseNumber;
            displayCourseInformation(courseMap, courseNumber);
            break;
        }
        case 9:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}

// Check if a file exists
bool fileExists(const string& fileName) {
    ifstream file(fileName);
    return file.is_open();
}

// load the file into the data struct
void loadCourses(const string& fileName, map<string, Course>& courseMap) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Unable to open file \"" << fileName << "\". Make sure the file exists and is accessible." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prerequisite;

        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;

        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        courseMap[toUpperCase(courseNumber)] = course;
    }

    cout << "Courses successfully loaded from \"" << fileName << "\"." << endl;
}

// print all courses
void displayAllCourses(const map<string, Course>& courseMap) {
    if (courseMap.empty()) {
        cout << "No courses available. Please load data first." << endl;
        return;
    }

    cout << "\n--- All Courses ---" << endl;
    for (const auto& pair : courseMap) {
        cout << pair.first << ": " << pair.second.courseTitle << endl;
    }
}

// print 1 courses info
void displayCourseInformation(const map<string, Course>& courseMap, const string& courseNumber) {
    if (courseMap.empty()) {
        cout << "No courses available. Please load data first." << endl;
        return;
    }

    string upperCourseNumber = toUpperCase(courseNumber); // make uppercase for easier checking if a user doesnt do upper case
    auto it = courseMap.find(upperCourseNumber);
    if (it == courseMap.end()) {
        cout << "Course not found." << endl;
        return;
    }

    const Course& course = it->second;
    cout << "\nCourse Number: " << course.courseNumber << endl;
    cout << "Course Title: " << course.courseTitle << endl;
    cout << "Prerequisites: ";

    if (course.prerequisites.empty()) {
        cout << "None" << endl;
    }
    else {
        for (const string& prereq : course.prerequisites) {
            cout << prereq << " ";
        }
        cout << endl;
    }
}
// based on the example output provided
string toUpperCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}
