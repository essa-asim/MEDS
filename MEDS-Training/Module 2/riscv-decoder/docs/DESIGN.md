# RISC-V RV32I Instruction Decoder

## Software Design Document

---

## 1. Overview

This project implements a software-based instruction decoder for the RISC-V RV32I Instruction Set Architecture (ISA). The decoder accepts a text file containing hexadecimal machine instructions, decodes each instruction according to the RV32I specification, and prints the corresponding assembly language representation.

The project follows a modular design approach by separating file handling, instruction decoding, and program control into independent modules. This improves readability, maintainability, and extensibility.

---

## 2. Software Architecture

The software is divided into three main modules:

```
                +-------------------+
                |   main.c          |
                | Program Control   |
                +---------+---------+
                          |
                          |
                          v
                +-------------------+
                |   memory.c        |
                | Hex File Loader   |
                +---------+---------+
                          |
                          |
                          v
                +-------------------+
                |   decoder.c       |
                | Instruction       |
                | Decoder           |
                +---------+---------+
                          |
                          |
                          v
                Console Output
```

Each module has a single responsibility, resulting in a clean and maintainable design.

---

## 3. Module Description

### 3.1 main.c

The main module controls the overall execution of the program.

Responsibilities include:

* Processing command-line arguments.
* Calling the memory module to load instructions.
* Invoking the decoder for each instruction.
* Printing formatted output.

The main module does not perform any decoding itself, ensuring a clear separation of responsibilities.

---

### 3.2 memory.c

The memory module is responsible for reading hexadecimal instructions from an input file.

Responsibilities include:

* Opening the input file.
* Reading each hexadecimal instruction.
* Converting hexadecimal strings into 32-bit unsigned integers.
* Storing instructions in memory.
* Returning the total number of instructions loaded.

This isolates all file-handling operations from the rest of the project.

---

### 3.3 decoder.c

The decoder module performs instruction decoding according to the RV32I ISA.

Its responsibilities include:

* Extracting instruction fields.
* Identifying instruction formats.
* Decoding instruction mnemonics.
* Formatting assembly language output.

The decoder is organized into separate helper functions for each instruction format, improving readability and simplifying future extensions.

---

## 4. Instruction Decoding

Each 32-bit instruction is divided into several fields.

```
31        25 24   20 19   15 14 12 11    7 6      0
+-----------+-------+-------+------+-------+--------+
|  funct7   |  rs2  |  rs1  |funct3|  rd   | opcode |
+-----------+-------+-------+------+-------+--------+
```

The decoder first extracts the common fields using bit manipulation macros.

Depending on the opcode, the instruction is classified as one of the following formats:

* R-Type
* I-Type
* S-Type
* B-Type
* U-Type
* J-Type

Each instruction format has its own immediate extraction method.

---

## 5. Supported Instructions

The decoder supports the complete RV32I base instruction set required by the assignment.

### R-Type

* add
* sub
* sll
* slt
* sltu
* xor
* srl
* sra
* or
* and

### I-Type

* addi
* slli
* slti
* sltiu
* xori
* srli
* srai
* ori
* andi

### Load Instructions

* lb
* lh
* lw
* lbu
* lhu

### Store Instructions

* sb
* sh
* sw

### Branch Instructions

* beq
* bne
* blt
* bge
* bltu
* bgeu

### Upper Immediate Instructions

* lui
* auipc

### Jump Instructions

* jal
* jalr

---

## 6. Data Flow

The execution flow of the program is shown below.

```
User
  |
  |
  v
Hex File (.hex)
  |
  |
  v
load_hex_file()
  |
  |
  v
Instruction Memory
  |
  |
  v
decode_instruction()
  |
  |
  v
instruction_to_string()
  |
  |
  v
Formatted Assembly Output
```

Each instruction passes through the same decoding pipeline until the entire input file has been processed.

---

## 7. Design Decisions

Several software engineering principles were followed during implementation.

* Modular programming using separate source and header files.
* Single responsibility for each module.
* Use of descriptive data structures for decoded instructions.
* Use of bit extraction macros to simplify field extraction.
* Consistent coding style throughout the project.
* Command-line interface for flexible execution.

These design decisions improve code readability and simplify future maintenance.

---

## 8. Project Directory Structure

```
riscv-decoder/
│
├── include/
│   ├── common.h
│   ├── decoder.h
│   └── memory.h
│
├── src/
│   ├── main.c
│   ├── memory.c
│   └── decoder.c
│
├── test/
│   └── all_instructions.hex
│
├── Makefile
├── README.md
└── DESIGN.md
```

---

## 9. Future Improvements

The current implementation focuses on decoding RV32I instructions. Future enhancements may include:

* Support for additional RISC-V extensions (M, A, F, D, C).
* Label generation for branch and jump targets.
* Binary input file support.
* Instruction statistics and profiling.
* Integration with a simple RISC-V simulator.

---

## 10. Conclusion

The project successfully implements a modular RV32I instruction decoder capable of translating hexadecimal machine instructions into human-readable assembly language. The modular architecture, clean separation of responsibilities, and extensible design make the software easy to understand, maintain, and expand.
