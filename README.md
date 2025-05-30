# Roman Numeral Converter

---

## 🚀 Overview

A lightweight C++ command-line tool that converts between **Roman numerals and integers**, supporting values from **1 to 3999**.

Built in a day to stay sane during exams—because writing clean logic is more therapeutic than cramming. Also sparked by a book I’m reading that uses Roman numerals for chapters, so I built this to better understand how to read and interpret them.

## 📁 Project Structure

```plaintext
roman-numeral-converter
├── bin/
├── src/
│   └── main.cpp
├── Makefile
└── README.md
```

## 🛠️ Usage

Make sure you're in the project root: `roman-numeral-converter/`

### ✅ Build the program

```bash
make build
```

### 🔁 Convert Roman numerals and integers

```bash
make run XIV 2024 IX
```

You can mix multiple inputs (Roman numerals or integers). The program will:

- Convert each input in order
- Print the conversion result
- Handle invalid input gracefully

## 🧪 Run Tests

```bash
make run test
```

Test suite includes:

1. Roman numeral conversions from I to XX
2. Large numerals (e.g., MCMXCIV)
3. Integer-to-Roman for values 1–20
4. 1000 randomized round-trip conversions (int → Roman → int)


## ⚠️ Notes

- Only accepts **uppercase** Roman numerals (`XV`, not `xv`)
- Valid range: **1 to 3999**
- Invalid inputs return an error message; program continues


## 🧠 Why This Exists

A quick mental break from exams, and a chance to:

- Practice C++
- Reinforce Roman numeral logic
- Bootstrap simple test coverage using assertions


## Rules

These were the rules I used, taken from: [Roman Numerals - Chart, Rules | Roman Counting | Roman Letters](https://www.cuemath.com/numbers/roman-numerals/)

- **Rule 1**: When certain numerals are repeated, the number represented by them is their sum. For example, II = 1 + 1 = 2, or XX = 10 + 10 = 20, or, XXX = 10 + 10 + 10 = 30.

- **Rule 2**: It is to be noted that no Roman numerals can come together more than 3 times. For example, we cannot write 40 as XXXX

- **Rule 3**: The letters V, L, and D are not repeated.

- **Rule 4**: Only I, X, and C can be used as subtractive numerals. There can be 6 combinations when we subtract. These are IV = 5 - 1 = 4; IX = 10 - 1 = 9; XL = 50 - 10 = 40; XC = 100 - 10 = 90; CD = 500 - 100 = 400; and CM = 1000 - 100 = 900

- **Rule 5**: When a Roman numeral is placed after another Roman numeral of greater value, the result is the sum of the numerals. For example, VIII = 5 + 1 + 1 + 1 = 8, or, XV = 10 + 5 = 15,

- **Rule 6**: When a Roman numeral is placed before another Roman numeral of greater value, the result is the difference between the numerals. For example, IV = 5 - 1 = 4, or, XL = 50 - 10 = 40, or XC = 100 - 10 = 90

- **Rule 7**: When a Roman numeral of a smaller value is placed between two numerals of greater value, it is subtracted from the numeral on its right. For example, XIV = 10 + (5 - 1) = 14, or, XIX = 10 + (10 - 1) = 19

- **Rule 8**: To multiply a number by a factor of 1000 a bar is placed over it.

- **Rule 9**: Roman numerals do not follow any place value system.

- **Rule 10**: There is no Roman numeral for zero (0).

# Contributions

- [Roman Numerals - Chart, Rules | Roman Counting | Roman Letters](https://www.cuemath.com/numbers/roman-numerals/)
