# MyInt (C++ Big Integer)

A custom integer class that stores digits in a dynamic array and supports
large-number arithmetic.

## Key Concepts
- Dynamic memory (`new[]/delete[]`)
- Deep copy (Rule of Three: destructor, copy constructor, assignment)
- Operator overloading: `+`, `*`, comparisons, `<<`, `>>`, `++`
- Input validation and trimming leading zeros

## Files
- `myint.h` — class definition
- `myint.cpp` — implementation
- `main.cpp` — demo usage

## Build & Run
```bash
g++ -std=c++17 main.cpp myint.cpp -o myint
./myint
