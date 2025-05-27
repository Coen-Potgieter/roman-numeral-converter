#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <cassert>
#include <ranges>
#include <random>

int runTests();
int romanToNum(std::string romanNumeral);
std::string numToRoman(int inputInt);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Invalid Command Line Input...\n";
        std::cerr << "Must have one additional input being `test` or a series of roman numerals as input\n";
        return 1;
    }

    // We need to convert `argv[1]` to a string to compare it to a string literal as `argv[1]` is a pointer to a `char`
    if (std::string(argv[1]) == "test") {
        return runTests();
    }

    for (int i = 1; i < argc; i++) {
        bool isRoman = false;
        std::string romanNumeralInput;
        int inputInt;
        try {
            inputInt = std::stoi(argv[i]);
        } catch(const std::invalid_argument& e) {
            isRoman = true;
            romanNumeralInput = argv[i];
        }

        if (isRoman) {
            int intConversion;
            try {
                intConversion = romanToNum(romanNumeralInput);
            } catch(const std::invalid_argument& e) {
                std::cout << "Given roman numeral: `" << romanNumeralInput << "` " << e.what() << '\n';
                continue;
            }
            std::cout << "Conversion of Roman Numeral: " << romanNumeralInput << " -> " << intConversion << '\n';
        } else {
            std::string romanNumeralConversion;
            try {
                romanNumeralConversion = numToRoman(inputInt);
            } catch(const std::invalid_argument& e) {
                std::cout << "Given Numer: `" << inputInt << "` " << e.what() << '\n';
                continue;
            }
            std::cout << "Conversion of Number: " << inputInt << " -> " << romanNumeralConversion << '\n';
        }

    }
    return 0;
}

int romanToNum(std::string romanNumeral) {
    const std::map<char, int> romanMapping = {
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
            romanMapping.at(romanNumeral.at(i));
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
            } else {
                break;
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

    // Catch Subtractions (by rule 4 there are only 6 legal subtractions, all of which is 2 characters)
    std::vector<std::string> subtractionSequences;
    for (int i = 1; i < romanNumeral.size(); i++) {
        int currVal = romanMapping.at(romanNumeral.at(i));
        int prevVal = romanMapping.at(romanNumeral.at(i-1));

        // If previous character is less than current character then we have condition for a subtraction
        if (currVal > prevVal) {
            std::string seq = std::string({romanNumeral.at(i-1), romanNumeral.at(i)});

            // Now catch prev letters as well
            for (int k = i - 2; k >= 0; k--) {
                if (romanMapping.at(romanNumeral.at(k)) < currVal) {
                    seq = std::string({romanNumeral.at(k)}) + seq;
                }
            }
            subtractionSequences.push_back(seq);
        }
    }

    const std::vector<std::string> validSubtractions = { "IV", "IX", "XL", "XC", "CD", "CM" };
    for (const std::string&  seq : subtractionSequences) {
        bool seqValid = false;
        for (int i = 0; i < validSubtractions.size(); i++) {
            if (seq == validSubtractions.at(i)) {
                seqValid = true;
                break;
            }
        }
        if (!seqValid) throw std::invalid_argument("is invalid by rule 4");
    }
    // -------------------------- Conversion ---------------------------- //
    // At this point we have our subtractions
    // We can remove subtraction sequences from original string, add them up, and add back the subtractions
    int outp = 0;
    for (const std::string& seq : subtractionSequences) {
        size_t subtractionIndex = romanNumeral.find(seq);
        if (subtractionIndex != std::string::npos) {
            romanNumeral.erase(subtractionIndex, 2);
            outp += romanMapping.at(seq.at(1)) - romanMapping.at(seq.at(0));
        }
    }

    for (const char& elem : romanNumeral) {
        outp += romanMapping.at(elem);
    }

    return outp;
}

std::string numToRoman(int inputInt) {
    // Input Validation
    if (inputInt <= 0) {
        throw std::invalid_argument("cannot be non-positve");
    }
    const std::map<int, std::string> romanMapping = {
        {1, "I"},
        {4, "IV"},
        {5, "V"},
        {9, "IX"},
        {10, "X"},
        {40, "XL"},
        {50, "L"},
        {90, "XC"},
        {100, "C"},
        {400, "CD"},
        {500, "D"},
        {900, "CM"},
        {1000, "M"},
    };

    std::string outp;
    for (const auto& [key, value] : std::views::reverse(romanMapping)) {
        while (inputInt >= key) {
            outp += value;
            inputInt -= key;
        }
    }
    return outp;
}


int runTests() {
    // -------------------------- Checking 1-20 -------------------------- //
    const std::map<std::string, int> oneToTwenty = {
        {"I", 1}, {"II", 2}, {"III", 3}, {"IV", 4}, {"V", 5}, {"VI", 6}, {"VII", 7}, {"VIII", 8}, {"IX", 9}, 
        {"X", 10}, {"XI", 11}, {"XII", 12}, {"XIII", 13}, {"XIV", 14}, {"XV", 15}, {"XVI", 16}, {"XVII", 17}, 
        {"XVIII", 18}, {"XIX", 19}, {"XX", 20}
    };

    std::cout << "Testing Roman Numerals from 1-20...\n";
    int intConversion;
    for (const auto& [key, value] : oneToTwenty) {
        try {
            intConversion = romanToNum(key);
            assert(intConversion == value);
            std::cout << "Correct conversion of Roman Numeral: " << key << " -> " << intConversion << '\n';
        } catch(const std::invalid_argument& e) {
            std::cerr << '`' << key << "` Caused an error of: " << e.what() << '\n';
            return 1;
        } 
    }


    // -------------------------- Checking Values in the thousands -------------------------- //
    const std::map<std::string, int> thousands = {
        {"MI", 1001}, {"MVI", 1006}, {"MLI", 1051}, {"MLXXI", 1071}, {"MLXXVI", 1076}, {"MCXXI", 1121}, {"MCXXVI", 1126},
        {"MCLXXI", 1171}, {"MCLXXVI", 1176}, {"MII", 1002}, {"MVII", 1007}, {"MLII", 1052}, {"MLXXII", 1072}, {"MLXXVII", 1077},
        {"MCXXII", 1122}, {"MCXXVII", 1127}, {"MCLXXII", 1172}, {"MCLXXVII", 1177}, {"MIII", 1003}, {"MVIII", 1008},
        {"MLIII", 1053}, {"MLXXIII", 1073}, {"MLXXVIII", 1078}, {"MCXXIII", 1123}, {"MCXXVIII", 1128}, {"MCLXXIII", 1173},
        {"MCLXXVIII", 1178}, {"MIV", 1004}, {"MIX", 1009}, {"MLIV", 1054}, {"MLXXIV", 1074}, {"MLXXIX", 1079}, {"MCXXIV", 1124},
        {"MCXXIX", 1129}, {"MCLXXIV", 1174}, {"MCLXXIX", 1179}, {"MV", 1005}, {"MX", 1010}, {"MLV", 1055}, {"MLXXV", 1075},
        {"MLXXX", 1080}, {"MCXXV", 1125}, {"MCXXX", 1130}, {"MCLXXV", 1175}, {"MCLXXX", 1180}
    };

    std::cout << "\nTesting Roman Numerals in the thousands...\n";
    for (const auto& [key, value] : thousands) {
        try {
            intConversion = romanToNum(key);
            assert(intConversion == value);
            std::cout << "Correct conversion of Roman Numeral: " << key << " -> " << intConversion << '\n';
        } catch(const std::invalid_argument& e) {
            std::cerr << '`' << key << "` Caused an error of: " << e.what() << '\n';
            return 1;
        } 
    }

    // -------------------------- Testing integer to Roman 1-20 -------------------------- //
    std::string romanNumeralConversion;
    for (const auto& [key, value] : std::views::reverse(oneToTwenty)) {
        try {
            romanNumeralConversion = numToRoman(value);
            assert(romanNumeralConversion == key);
            std::cout << "Correct conversion of number: " << value << " -> " << romanNumeralConversion << '\n';
        } catch(const std::invalid_argument& e) {
            std::cout << "Given Numer: `" << value << "` " << e.what() << '\n';
            return 1;
        }
    }


    // -------------------------- Convert 100 Random Numers to roman then back to decimal -------------------------- //
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> uniformIntDistr(1, 3000);
    int randomNum;
    for (int i  = 0; i < 1000; i++) {
        randomNum = uniformIntDistr(gen);
        std::cout << "Converting " << randomNum << "\t";
        try {
            romanNumeralConversion = numToRoman(randomNum);
        } catch(const std::invalid_argument& e) {
            std::cout << "Given Numer: `" << randomNum << "` " << e.what() << '\n';
            return 1;
        }
        try {
            intConversion = romanToNum(romanNumeralConversion);
        } catch(const std::invalid_argument& e) {
            std::cerr << '`' << romanNumeralConversion << "` Caused an error of: " << e.what() << '\n';
            return 1;
        } 
        assert(randomNum == intConversion);
        std::cout << "Correct converted the random number: " << randomNum << " to " << romanNumeralConversion <<
            " then back to: " << intConversion << '\n';
    }

    return 0;
}


