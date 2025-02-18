# HamOS

HamOS is a Operating system that allows users to navigate and run programs.
The application features a user-friendly interface.

## New Features

- Added `wait()` , `printMulti{}` and string varibles (`AA == Hello`)
- Bug fixes
## Commands

HamOS supports the following commands in `.Ham` files:

- `VarName == Value`: Creates an integer variable with the given name and value. Variable names can only be a single letter (e.g., `A == 10`).
- `printVar(VarName)`: Prints the value of the specified variable (e.g., `printVar(A)`).
- `printStr("string")`: Prints the specified string to the console (e.g., `printStr("Hello, HamOS!")`).
- `Func([funcname]) {}`: Defines a function with the given name. (Note: Function implementation is a placeholder in this example and can be customized).
- `Run [funcname]`: Runs the specified function.
- `?Math [number/var] [+/-] [number/var] == [Var]`: Performs a mathematical operation (addition or subtraction) and stores the result in the specified variable.
- `if ([Var/number] == [Var/number]) {}`: Conditional statement to execute code if the condition is true.
- `else {}`: Conditional statement to execute code if the `if` condition is false.
- `kill()`: Terminates the program.
- `checkKey([keyboardKey]) {}`: Checks if the specified key is pressed (Note: Implementation is a placeholder and can be customized).
- `loop([times]) {}`: Loops the code inside the block a specified number of times.
- `loopInf {}`: Loops the code inside the block infinitely.
- `wait()`: Waits for the amount of time(seconds) in the parenthesis

## Installation

You can download the latest versions here:

Legacy Edition:

[![HamOS Lagacy Edition](https://img.shields.io/badge/Download-HamOSLE%20Executable-brightgreen)](https://HamGroup.github.io/HamOS/HamOSLE.zip)

Developer's Package:

[![HamOS Lagacy Edition](https://img.shields.io/badge/Download-HamOSLE%20Executable-brightgreen)](https://HamGroup.github.io/HamOS/HamOSDE.exe)

## Example `.Ham` File

```Ham
A == 10
printVar(A)
printStr("Hello, HamOS!")
```
