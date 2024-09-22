#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Define a struct to store student data
struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
    std::string email;
};

int main() {
    // Vector to store student data
    std::vector<STUDENT_DATA> students;

    // Open the student data file
    std::ifstream file("StudentData.txt");

    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Failed to open the StudentData.txt file!" << std::endl;
        return -1;
    }

    // Read each line from the file
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string firstName, lastName;

        // Parse the comma-separated name pair
        if (std::getline(ss, firstName, ',') && std::getline(ss, lastName)) {
            // Create a student object and store it in the vector
            STUDENT_DATA student = { firstName, lastName, "" };
            students.push_back(student);
        }
    }

    // Close the file
    file.close();

#ifdef PRE_RELEASE
    // Pre-release mode: add email data
    std::ifstream emailFile("StudentData_Emails.txt");
    if (!emailFile.is_open()) {
        std::cerr << "Failed to open the StudentData_Emails.txt file!" << std::endl;
        return -1;
    }

    int index = 0;
    while (std::getline(emailFile, line)) {
        if (index < students.size()) {
            students[index].email = line; // Add email to corresponding student
        }
        ++index;
    }

    emailFile.close();

    std::cout << "PRE-RELEASE MODE: List of students with emails:" << std::endl;
    for (const auto& student : students) {
        std::cout << "Name: " << student.firstName << " " << student.lastName
            << ", Email: " << student.email << std::endl;
    }
#else
    // Standard mode: print student information without email
    std::cout << "STANDARD MODE: List of students:" << std::endl;
    for (const auto& student : students) {
        std::cout << "Name: " << student.firstName << " " << student.lastName << std::endl;
    }
#endif

    return 0;
}
