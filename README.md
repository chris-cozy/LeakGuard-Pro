# **LeakGuard-Pro**

LeakGuard-Pro is a memory leak detection tool designed to help software developers identify and analyze memory leaks in their programs. It provides a mechanism to track memory allocations and deallocations during program execution, allowing you to identify potential memory leaks and their associated sizes.

## **Features**

- **Memory Leak Detection:** LeakGuard-Pro intercepts calls to memory allocation functions (**`malloc`**, **`calloc`**, **`realloc`**) and memory deallocation function (**`free`**) using a dynamic library. It tracks memory allocations and deallocations during program execution.
- **Automatic Leak Reporting:** After the target program completes its execution, LeakGuard-Pro analyzes the memory usage and identifies any memory leaks that occurred during the program's runtime. It calculates the total number of leaks and the cumulative size of memory leaks.
- **Intuitive Usage:** LeakGuard-Pro is designed to be easy to integrate into your development workflow. It uses a dynamic library to intercept memory-related function calls, making it non-intrusive and easy to apply to existing codebases.
- **Flexibility:** LeakGuard-Pro supports a variety of programming languages and platforms, as long as they use standard memory allocation functions. This allows you to use LeakGuard-Pro in a wide range of projects.

## **Getting Started**

### **Prerequisites**

- C Compiler (e.g., GCC, Clang)
- Linux or Unix-like environment

### **Installation**

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/LeakGuard-Pro.git
   cd LeakGuard-Pro
   ```

2. Build LeakGuard-Pro:

   ```bash
   make all
   ```

### **Usage**

1. Compile your target program with LeakGuard-Pro's dynamic library:

   ```bash
   gcc -o myprogram myprogram.c -L. -lmemory_shim -ldl
   ```

2. Run your program using the **`leakcount`** executable:

   ```bash
   ./leakcount ./myprogram [program_arguments]
   ```

3. After your program finishes execution, LeakGuard-Pro will report any memory leaks detected, including the number of leaks and the cumulative leak size.

### **Example**

```c
#include <stdio.h>
#include <stdlib.h>
int main() {
    void *memory_leak = malloc(1024);  // This allocation will cause a leak

    printf("Hello, LeakGuard-Pro!\n");

    return 0;
}
```

### **Cleaning Up**

To clean up compiled files, run:

```bash
make clean
```

## **Contributing**

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or a pull request.

## **License**

This project is licensed under the MIT License - see the **[LICENSE](https://opensource.org/license/mit/)** file for details.

## **Acknowledgments**

LeakGuard-Pro was inspired by the need for an easy-to-use memory leak detection tool for software developers. It aims to simplify the process of identifying memory leaks in various projects.

## **Contact**

For questions, suggestions, or support, please contact [cjsanders100@gmail.com](mailto:cjsanders100@gmail.com).
