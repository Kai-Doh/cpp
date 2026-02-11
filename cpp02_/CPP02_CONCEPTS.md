# CPP Module 02 - Detailed Concepts Guide

## Module Overview
**Topics:** Ad-hoc Polymorphism, Operator Overloading, and the Orthodox Canonical Form

This module introduces three fundamental C++ concepts that form the backbone of object-oriented programming in C++.

---

## Table of Contents
1. [Orthodox Canonical Form (OCF)](#1-orthodox-canonical-form-ocf)
2. [Fixed-Point Numbers](#2-fixed-point-numbers)
3. [Operator Overloading](#3-operator-overloading)
4. [Ad-hoc Polymorphism](#4-ad-hoc-polymorphism)
5. [Exercise Breakdown with Code Analysis](#5-exercise-breakdown-with-code-analysis)
6. [Common Evaluation Questions & Answers](#6-common-evaluation-questions--answers)

---

## 1. Orthodox Canonical Form (OCF)

### What is it?
The Orthodox Canonical Form is a set of four special member functions that every class should implement to ensure proper resource management and copying behavior.

### The Four Required Functions

```cpp
class Fixed {
public:
    Fixed();                              // 1. Default Constructor
    Fixed(const Fixed& other);            // 2. Copy Constructor
    Fixed& operator=(const Fixed& other); // 3. Copy Assignment Operator
    ~Fixed();                             // 4. Destructor
};
```

### Why is OCF Important?

1. **Rule of Three**: If you define any one of destructor, copy constructor, or copy assignment operator, you should define all three
2. **Resource Management**: Prevents memory leaks and double-free errors
3. **Deep Copy vs Shallow Copy**: Ensures proper copying of dynamically allocated resources

### Implementation Analysis (from your code)

```cpp
// 1. DEFAULT CONSTRUCTOR - Initializes object to a known state
Fixed::Fixed() : _value(0) {
    std::cout << "Default constructor called" << std::endl;
}
```
**Why:** Uses initializer list (`: _value(0)`) which is more efficient than assignment in the body.

```cpp
// 2. COPY CONSTRUCTOR - Creates a new object as a copy of existing one
Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;
    *this = other;  // Reuses assignment operator
}
```
**Why:** `const Fixed&` prevents modification and avoids unnecessary copying. The reference (`&`) prevents infinite recursion.

```cpp
// 3. COPY ASSIGNMENT OPERATOR - Assigns values from one existing object to another
Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)          // Self-assignment check
        _value = other.getRawBits();
    return *this;                // Return reference for chaining (a = b = c)
}
```
**Why:**
- Self-assignment check (`this != &other`) prevents bugs when doing `a = a`
- Returns `*this` to allow chaining: `a = b = c`

```cpp
// 4. DESTRUCTOR - Cleans up resources when object is destroyed
Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}
```
**Why:** Virtual in base classes, ensures proper cleanup of derived classes.

---

## 2. Fixed-Point Numbers

### What are Fixed-Point Numbers?

Fixed-point numbers are a way to represent fractional numbers using integers. They offer:
- **Better precision** than floating-point for certain ranges
- **Faster computation** on systems without FPU
- **Deterministic behavior** (no floating-point rounding issues)

### How They Work

A fixed-point number splits an integer into two parts:
```
[Integer Part | Fractional Part]
    24 bits   |    8 bits       (for your implementation)
```

With 8 fractional bits:
- The **scaling factor** is `2^8 = 256`
- Smallest representable value (epsilon): `1/256 = 0.00390625`

### Conversion Formulas

```cpp
// Integer to Fixed-Point: Multiply by 2^fractionalBits (left shift)
_value = n << _fractionalBits;  // n * 256

// Float to Fixed-Point: Multiply by 2^fractionalBits, then round
_value = roundf(n * (1 << _fractionalBits));  // n * 256, rounded

// Fixed-Point to Integer: Divide by 2^fractionalBits (right shift)
return _value >> _fractionalBits;  // _value / 256

// Fixed-Point to Float: Divide by 2^fractionalBits
return (float)_value / (1 << _fractionalBits);  // _value / 256.0
```

### Visual Example

```
Number: 42.5

Step 1: Convert to fixed-point (8 fractional bits)
        42.5 * 256 = 10880

Step 2: In binary
        10880 = 0010101010000000
                |-------|-------|
                  42    |  128
               integer  | 0.5 * 256

Step 3: Convert back to float
        10880 / 256 = 42.5
```

### Your Implementation Analysis

```cpp
// Integer constructor
Fixed::Fixed(const int n) : _value(n << _fractionalBits) {
    // n << 8 means n * 256
    // Example: 10 becomes 2560 in raw value
}

// Float constructor
Fixed::Fixed(const float n) : _value(roundf(n * (1 << _fractionalBits))) {
    // n * 256, then rounded to nearest integer
    // Example: 42.42 * 256 = 10859.52 -> 10860
}

// Convert back to float
float Fixed::toFloat(void) const {
    return (float)_value / (1 << _fractionalBits);
    // Example: 10860 / 256 = 42.421875
}

// Convert back to integer (truncates fractional part)
int Fixed::toInt(void) const {
    return _value >> _fractionalBits;
    // Example: 10860 >> 8 = 42 (fractional part lost)
}
```

---

## 3. Operator Overloading

### What is Operator Overloading?
Operator overloading allows you to define custom behavior for operators (`+`, `-`, `*`, `<`, `==`, etc.) when used with your class.

### Types of Operators in Your Implementation

#### Comparison Operators (Return bool)

```cpp
bool Fixed::operator>(const Fixed& other) const {
    return _value > other._value;
}

bool Fixed::operator<(const Fixed& other) const {
    return _value < other._value;
}

bool Fixed::operator>=(const Fixed& other) const {
    return _value >= other._value;
}

bool Fixed::operator<=(const Fixed& other) const {
    return _value <= other._value;
}

bool Fixed::operator==(const Fixed& other) const {
    return _value == other._value;
}

bool Fixed::operator!=(const Fixed& other) const {
    return _value != other._value;
}
```
**Why `const`:** These don't modify the object, so mark them `const`.

#### Arithmetic Operators (Return new Fixed)

```cpp
// Addition: Simply add raw values
Fixed Fixed::operator+(const Fixed& other) const {
    Fixed result;
    result.setRawBits(_value + other._value);
    return result;
}

// Subtraction: Simply subtract raw values
Fixed Fixed::operator-(const Fixed& other) const {
    Fixed result;
    result.setRawBits(_value - other._value);
    return result;
}

// Multiplication: Requires adjustment for double-scaling
Fixed Fixed::operator*(const Fixed& other) const {
    Fixed result;
    // After multiplication, we have 16 fractional bits (8+8)
    // Right shift by 8 to get back to 8 fractional bits
    result.setRawBits((_value * other._value) >> _fractionalBits);
    return result;
}

// Division: Requires pre-scaling to maintain precision
Fixed Fixed::operator/(const Fixed& other) const {
    Fixed result;
    // Left shift dividend first to maintain precision
    // Then divide by raw value of divisor
    result.setRawBits((_value << _fractionalBits) / other._value);
    return result;
}
```

**Why multiplication needs `>> _fractionalBits`:**
```
a = 2.5 (raw: 640)
b = 2.0 (raw: 512)
a * b in real = 5.0

Without adjustment: 640 * 512 = 327680
This is 5.0 * 256 * 256 = 327680 (16 fractional bits!)

With adjustment: 327680 >> 8 = 1280 = 5.0 * 256 (correct!)
```

#### Increment/Decrement Operators

```cpp
// Pre-increment: ++a (increment, then return)
Fixed& Fixed::operator++() {
    _value++;  // Increment by smallest epsilon (1/256)
    return *this;
}

// Post-increment: a++ (save old value, increment, return old)
Fixed Fixed::operator++(int) {  // 'int' is a dummy parameter to distinguish from pre
    Fixed temp(*this);  // Save current state
    _value++;           // Increment
    return temp;        // Return old state
}

// Pre-decrement: --a
Fixed& Fixed::operator--() {
    _value--;
    return *this;
}

// Post-decrement: a--
Fixed Fixed::operator--(int) {
    Fixed temp(*this);
    _value--;
    return temp;
}
```

**Key Difference:**
- Pre-increment returns `Fixed&` (reference) - more efficient, no copy
- Post-increment returns `Fixed` (value) - must return old value, so needs copy

#### Stream Insertion Operator (<<)

```cpp
// Non-member function (friend-like access)
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;  // Return stream for chaining: cout << a << b
}
```
**Why non-member:** The left operand is `ostream`, not `Fixed`.

#### Static Member Functions (min/max)

```cpp
// For non-const references
Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b;
}

// For const references (overloaded version)
const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;
}

// Usage:
Fixed a(5), b(10);
Fixed::min(a, b);  // Calls non-const version

const Fixed c(5), d(10);
Fixed::min(c, d);  // Calls const version
```

---

## 4. Ad-hoc Polymorphism

### What is it?
Ad-hoc polymorphism means "different implementations of the same interface based on types." In C++, this is achieved through:

1. **Function Overloading**: Same function name, different parameters
2. **Operator Overloading**: Same operator, different behavior for different types

### Examples in Your Code

```cpp
// Function Overloading - Multiple constructors
Fixed();              // Default
Fixed(const int n);   // From int
Fixed(const float n); // From float

// The compiler chooses the right one based on argument type:
Fixed a;         // Calls Fixed()
Fixed b(42);     // Calls Fixed(const int n)
Fixed c(42.42f); // Calls Fixed(const float n)
```

```cpp
// Static function overloading
static Fixed& min(Fixed& a, Fixed& b);             // Non-const version
static const Fixed& min(const Fixed& a, const Fixed& b); // Const version

// Compiler chooses based on constness of arguments
```

---

## 5. Exercise Breakdown with Code Analysis

### Exercise 00: Basic OCF

**Goal:** Create a class with Orthodox Canonical Form

**Key Files:**
- `Fixed.hpp`: Class declaration with OCF
- `Fixed.cpp`: Implementation

**Critical Code:**
```cpp
class Fixed {
private:
    int                 _value;           // Raw fixed-point value
    static const int    _fractionalBits = 8; // Always 8 bits for fraction

public:
    Fixed();                              // Default constructor
    Fixed(const Fixed& other);            // Copy constructor
    Fixed& operator=(const Fixed& other); // Assignment operator
    ~Fixed();                             // Destructor

    int  getRawBits(void) const;          // Getter
    void setRawBits(int const raw);       // Setter
};
```

### Exercise 01: Constructors and Conversions

**Goal:** Add int/float constructors and conversion methods

**New Additions:**
```cpp
Fixed(const int n);     // Convert int to fixed-point
Fixed(const float n);   // Convert float to fixed-point
float toFloat() const;  // Convert to float
int toInt() const;      // Convert to int
```

**Stream operator:**
```cpp
std::ostream& operator<<(std::ostream& out, const Fixed& fixed);
```

### Exercise 02: Full Operator Overloading

**Goal:** Implement all comparison, arithmetic, and increment operators

**Operators Added:**
- Comparison: `>`, `<`, `>=`, `<=`, `==`, `!=`
- Arithmetic: `+`, `-`, `*`, `/`
- Increment/Decrement: `++a`, `a++`, `--a`, `a--`
- Static: `min()`, `max()` (both const and non-const versions)

---

## 6. Common Evaluation Questions & Answers

### Q1: Why use `const Fixed&` instead of `Fixed` for parameters?
**A:** Passing by const reference avoids copying the entire object. The `const` ensures we can't accidentally modify the original.

### Q2: Why return `Fixed&` in assignment operator?
**A:** To enable chaining like `a = b = c`. The expression is evaluated right-to-left: `a = (b = c)`.

### Q3: Why check `if (this != &other)` in assignment?
**A:** Self-assignment protection. Without it, `a = a` could cause issues if we delete resources before copying.

### Q4: Why is `_fractionalBits` static const?
**A:**
- `static`: Same value shared by all instances (saves memory)
- `const`: Cannot be changed after initialization

### Q5: Why use bitwise shifts instead of multiplication/division?
**A:** Bitwise shifts (`<<`, `>>`) are faster than multiplication/division. `n << 8` equals `n * 256`.

### Q6: How does multiplication work with fixed-point?
**A:**
```
(a * 2^8) * (b * 2^8) = a * b * 2^16
We need a * b * 2^8, so divide by 2^8 (right shift by 8)
```

### Q7: Why two versions of min/max?
**A:** To handle both const and non-const arguments. C++ will choose the appropriate version based on the constness of the arguments.

### Q8: What's the difference between pre and post increment?
**A:**
- Pre (`++a`): Increment first, then return the new value
- Post (`a++`): Return old value, then increment
- Pre is more efficient (no temporary object needed)

### Q9: Why is the stream operator a non-member function?
**A:** Because the left operand is `std::ostream&`, not `Fixed`. If it were a member, we'd have to call it as `fixed.operator<<(cout)`, which is backwards.

### Q10: What happens with division by zero?
**A:** The program may crash, which is acceptable according to the subject. You could add a check, but it's not required.

---

## Memory Layout Visualization

```
Fixed object in memory:
+-------------------+
|    _value (4B)    |  <-- int storing the fixed-point representation
+-------------------+

Static member (shared by all instances):
+-------------------+
| _fractionalBits=8 |  <-- const int, stored once for the class
+-------------------+

Example: Fixed f(42.5f);
_value = 42.5 * 256 = 10880 = 0x2A80

Binary: 00000000 00000000 00101010 10000000
                          |--42--| |-.5*256|
                          integer  fraction
```

---

## Quick Reference Card

| Concept | Syntax | Purpose |
|---------|--------|---------|
| Default Constructor | `Fixed()` | Initialize to default state |
| Copy Constructor | `Fixed(const Fixed&)` | Create copy of existing object |
| Assignment Operator | `Fixed& operator=(const Fixed&)` | Copy values to existing object |
| Destructor | `~Fixed()` | Clean up resources |
| Int to Fixed | `n << 8` | Multiply by 256 |
| Float to Fixed | `roundf(n * 256)` | Multiply and round |
| Fixed to Int | `value >> 8` | Divide by 256 (truncate) |
| Fixed to Float | `value / 256.0f` | Divide by 256.0 |
| Pre-increment | `Fixed& operator++()` | `++a` returns reference |
| Post-increment | `Fixed operator++(int)` | `a++` returns copy |
