#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

// Function to split the input string by a given delimiter and convert to integer and return a vector of integers
vector<int> splitAndConvertToInt(const string& str, const string& delimiter) {
    vector<int> numbers;
    size_t pos = 0;
    size_t startPos = 0;
    
    while ((pos = str.find(delimiter, startPos)) != string::npos) {
        string token = str.substr(startPos, pos - startPos);
        numbers.push_back(stoi(token));
        startPos = pos + delimiter.length();
    }
    
    // Add the last number
    if (startPos < str.length()) {
        numbers.push_back(stoi(str.substr(startPos)));
    }

    return numbers;
}

// Main add function to handle the string calculator logic
int add(const string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    string delimiter = ",";
    string numString = numbers;

    // Check if there's a custom delimiter
    if (numbers.substr(0, 2) == "//") {
        size_t delimiterPos = numbers.find('\n');
        delimiter = numbers.substr(2, delimiterPos - 2);
        numString = numbers.substr(delimiterPos + 1);
    }

    // Replace new lines with the delimiter
    size_t pos = 0;
    while ((pos = numString.find('\n', pos)) != string::npos) {
        numString.replace(pos, 1, delimiter);
        pos += delimiter.length();
    }

    // Split the string based on the delimiter
    vector<int> intNumbers = splitAndConvertToInt(numString, delimiter);

    int sum = 0;
    vector<int> negativeNumbers;

    for (int num : intNumbers) {
        if (num < 0) {
            negativeNumbers.push_back(num);
        } else {
            sum += num;
        }
    }

    // Check if there are any negative numbers and throw an exception
    if (!negativeNumbers.empty()) {
        string errorMessage = "Negative numbers not allowed: ";
        for (int neg : negativeNumbers) {
            errorMessage += to_string(neg) + " ";
        }
        throw runtime_error(errorMessage);
    }

    return sum;
}

int main() {
    try {
        string s;
        cout<<"Enter the numbers separated by , :";
        cin>>s;
        cout<<"Sum: "<<add(s)<<endl;
        
    } catch (const exception& e) {
        // Catch and display any exceptions thrown by the add function
        cerr << e.what() << endl;
    }

    return 0;
}
