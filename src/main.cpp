#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

void runTests();
int romanToNum(const std::string& romanNumeral);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Invalid Command Line Input...\n";
        std::cerr << "Must have one additional input being `test` or a series of roman numerals as input\n";
        return 1;
    }

    // We need to convert `argv[1]` to a string to compare it to a string literal as `argv[1]` is a pointer to a `char`
    if (std::string(argv[1]) == "test") {
        runTests();
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        std::string romanNumeral = std::string(argv[i]);

        int intConversion;
        try {
            intConversion = romanToNum(romanNumeral);
        } catch(const std::exception& e) {
            std::cout << "Given roman numeral: `" << romanNumeral << "` " << e.what() << '\n';
            continue;
        }
        std::cout << "Conversion of Roman Numeral: " << romanNumeral << " -> " << intConversion << '\n';
    }
    return 0;
}

int romanToNum(const std::string& romanNumeral) {

    std::map<char, int> numeralToVal = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };

    // -------------------------- Input Validation ---------------------------- //
    // Check if all given characters are valid
    for (int i = 0; i < romanNumeral.size(); i++) {
        try {
            numeralToVal.at(romanNumeral.at(i));
        } catch(const std::out_of_range& e) {
            throw std::invalid_argument("has invalid characters");
        }
    }

    // Restrictive rule 2:
    for (int i = 0; i < romanNumeral.size(); i++) {
        char charToCheck = romanNumeral.at(i);
        int counter = 1;
        for (int j = i + 1; j < romanNumeral.size(); j++) {
            if (romanNumeral[j] == charToCheck) {
                counter += 1;
            }
            if (counter >= 4) {
                throw std::invalid_argument("is invalid by rule 2");
            }
        }
    }

    // Restrictive rule 3:
    // Vector to hold counts for letters V, L, and D respectively
    std::vector<int> counter(3, 0);
    for (int i = 0; i < romanNumeral.size(); i++) {
        if (romanNumeral.at(i) == 'V') counter[0] += 1;
        if (romanNumeral.at(i) == 'L') counter[1] += 1;
        if (romanNumeral.at(i) == 'D') counter[2] += 1;
    }
    for (const int& count : counter) {
        if (count >= 2) {
            throw std::invalid_argument("is invalid by rule 3");
        }
    }

    





    return 0;
}

void runTests() {
    std::cout << "This is some tests...\n";
}


