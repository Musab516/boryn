# 🔥 Boryn Programming Language

A custom-built, interpreted programming language written in C++ featuring natural syntax and dynamic typing.

![Language](https://img.shields.io/badge/Language-C++-blue.svg)
![Status](https://img.shields.io/badge/Status-Active-success.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

---

## 📖 Overview

**Boryn** is a dynamically-typed, interpreted programming language designed with readability and simplicity in mind. Built entirely from scratch in C++, Boryn features a complete lexer, parser, and tree-walking interpreter.

### Why Boryn?

Traditional programming languages can feel verbose and intimidating. Boryn uses natural keywords like `say` instead of `print` and `provide` instead of `input`, making code more conversational and intuitive.

---

## ✨ Features

- 🎯 **Dynamic Typing** — Automatic type inference (int, double, string)
- 📝 **Natural Syntax** — Readable keywords (`say`, `provide`, `when`)
- 🔢 **Arithmetic Operations** — Full support for `+`, `-`, `*`, `/`
- 🔤 **String Concatenation** — Seamless string operations
- ⚖️ **Comparison Operators** — `==`, `!=`, `>`, `<`, `>=`, `<=`
- 🔀 **Conditional Logic** — `when`/`not`/`end` blocks
- 💬 **User Input** — Interactive programs with `provide`
- 🚀 **Fast Execution** — Efficient C++ interpreter

---

## 🚀 Quick Start

### Prerequisites

- C++17 compiler (g++, clang++)
- Make (optional)

### Installation

```bash
# Clone the repository
git clone https://github.com/Musab516/boryn.git
cd boryn

# Compile the interpreter
g++ -std=c++17 main.cpp lexer.cpp parser.cpp interpreter.cpp -o boryn

# Run your first program
./boryn examples/hello.byn
```

---

## 📚 Language Syntax

### Hello World

```boryn
say "Hello, World!"
```

### Variables

```boryn
let name = "Boryn"
let version = 1.0
let year = 2024

say "Welcome to " + name + " v" + version
```

### User Input

```boryn
let name = provide "What's your name?"
say "Hello, " + name + "!"

let age = provide "How old are you?"
say "You are " + age + " years old."
```

### Arithmetic

```boryn
let a = 10
let b = 5

say a + b    // Output: 15
say a - b    // Output: 5
say a * b    // Output: 50
say a / b    // Output: 2
```

### Conditionals

```boryn
let age = provide "Enter your age:"

when age >= 18:
    say "You are an adult!"
not:
    say "You are a minor!"
end
```

### Comparisons

```boryn
let password = provide "Enter password:"

when password == "secret123":
    say "Access granted!"
not:
    say "Access denied!"
end
```

### Advanced Example: Simple Calculator

```boryn
say "=== Simple Calculator ==="

let num1 = provide "Enter first number:"
let num2 = provide "Enter second number:"

say "Sum: " + (num1 + num2)
say "Difference: " + (num1 - num2)
say "Product: " + (num1 * num2)
say "Quotient: " + (num1 / num2)
```

---

## 🏗️ Architecture

Boryn follows a classic interpreter design:

```
Source Code (.byn)
       ↓
   [LEXER]           → Tokenizes source into tokens
       ↓
   [PARSER]          → Builds Abstract Syntax Tree (AST)
       ↓
   [INTERPRETER]     → Executes AST nodes
       ↓
    Output
```

### Components

#### 1. **Lexer** (`lexer.cpp`)
- Scans source code character by character
- Produces stream of tokens (keywords, identifiers, operators, literals)
- Handles strings, numbers, and operators

#### 2. **Parser** (`parser.cpp`)
- Consumes tokens from lexer
- Builds Abstract Syntax Tree (AST)
- Validates syntax and structure
- Implements recursive descent parsing

#### 3. **Interpreter** (`interpreter.cpp`)
- Tree-walking interpreter
- Evaluates AST nodes recursively
- Manages variable storage
- Handles dynamic typing and type coercion

---

## 📂 Project Structure

```
boryn/
├── include/              # Header files
│   ├── lexer.hpp        # Token definitions
│   ├── parser.hpp       # AST node types
│   └── interpreter.hpp  # Interpreter interface
├── src/                  # Source files
│   ├── main.cpp         # Entry point
│   ├── lexer.cpp        # Tokenization logic
│   ├── parser.cpp       # Syntax analysis
│   └── interpreter.cpp  # Execution engine
├── examples/
│   ├── hello.byn        # Hello World
│   ├── calculator.byn   # Arithmetic demo
│   ├── age_check.byn    # Conditional logic
│   └── password.byn     # User interaction
├── README.md
├── Makefile             # Build automation
├── .gitignore
└── LICENSE
```

---

## 🎯 Language Reference

### Keywords

| Keyword | Description |
|---------|-------------|
| `let` | Declare a variable |
| `say` | Print to console |
| `provide` | Get user input |
| `when` | Start conditional block |
| `not` | Else block |
| `end` | End conditional block |

### Operators

| Operator | Description |
|----------|-------------|
| `+` | Addition / String concatenation |
| `-` | Subtraction |
| `*` | Multiplication |
| `/` | Division |
| `==` | Equal to |
| `!=` | Not equal to |
| `>` | Greater than |
| `<` | Less than |
| `>=` | Greater than or equal |
| `<=` | Less than or equal |

### Data Types

- **Integer** — Whole numbers (e.g., `42`)
- **Double** — Floating-point numbers (e.g., `3.14`)
- **String** — Text in quotes (e.g., `"Hello"`)

---

## 🛠️ Development

### Building from Source

```bash
# Debug build
g++ -std=c++17 -g main.cpp lexer.cpp parser.cpp interpreter.cpp -o boryn

# Optimized build
g++ -std=c++17 -O3 main.cpp lexer.cpp parser.cpp interpreter.cpp -o boryn
```

### Running Tests

```bash
# Run all example programs
for file in examples/*.byn; do
    echo "Running $file..."
    ./boryn "$file"
done
```

---

## 🔮 Future Enhancements

- [ ] **Functions** — Define reusable code blocks
- [ ] **Loops** — `repeat` and `while` constructs
- [ ] **Arrays/Lists** — Collection data types
- [ ] **File I/O** — Read/write files
- [ ] **Standard Library** — Built-in utility functions
- [ ] **Error Messages** — Better syntax error reporting
- [ ] **REPL Mode** — Interactive shell
- [ ] **Comments** — `//` single-line comments
- [ ] **Module System** — Import other `.byn` files

---

## 📝 Example Programs

### 1. Greeting Program (`examples/hello.byn`)

```boryn
let name = provide "What's your name?"
say "Nice to meet you, " + name + "!"
```

### 2. Age Checker (`examples/age_check.byn`)

```boryn
let age = provide "Enter your age:"

when age >= 18:
    say "You can vote!"
not:
    say "You're too young to vote."
end
```

### 3. Password Validator (`examples/password.byn`)

```boryn
let password = provide "Create a password:"
let confirm = provide "Confirm password:"

when password == confirm:
    say "Password set successfully!"
not:
    say "Passwords don't match!"
end
```

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author

**Musab Bin Majid**  
Computer Science Student @ IBA  
[GitHub](https://github.com/Musab516) | [LinkedIn](https://linkedin.com/in/musab-bin-majid-8714272b5)

---

## 🙏 Acknowledgments

Built as a learning project to understand:
- Lexical analysis and tokenization
- Recursive descent parsing
- Abstract Syntax Trees (AST)
- Interpreter design patterns
- C++ memory management with smart pointers

Inspired by languages like Python, Ruby, and Lua.

---

## 📊 Technical Details

- **Implementation Language:** C++17
- **Parsing Technique:** Recursive Descent
- **Memory Management:** Smart pointers (`shared_ptr`)
- **Type System:** Dynamic typing with runtime type inference
- **Execution Model:** Tree-walking interpreter

---

**⭐ If you find Boryn interesting, please star the repository!**
