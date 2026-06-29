# RISC-V RV32I Instruction Decoder

## Overview

This project implements a modular instruction decoder for the RISC-V RV32I instruction set architecture. The decoder reads hexadecimal machine instructions from a text file, decodes each instruction, and prints its corresponding assembly language representation.

The project was developed as part of the Computer Architecture Grand Assignment.

---

## Features

- Supports the RV32I base instruction set
- Modular software design
- Command-line interface
- Decodes:
  - R-Type instructions
  - I-Type arithmetic instructions
  - Load instructions
  - Store instructions
  - Branch instructions
  - LUI
  - AUIPC
  - JAL
  - JALR

---

## Project Structure

```
riscv-decoder
│
├── include/
│   ├── common.h
│   ├── decoder.h
│   └── memory.h
│
├── src/
│   ├── decoder.c
│   ├── memory.c
│   └── main.c
│
├── test/
│   └── all_instructions.hex
│
├── Makefile
└── README.md
```

---

## Build

```bash
make
```

---

## Run

```bash
./bin/riscv-decoder test/all_instructions.hex
```

---

## Example Output

```
Address      Machine Code   Assembly
--------------------------------------------
0x00000000   003100B3       add x1, x2, x3
0x00000004   40310133       sub x2, x2, x3
```

---

## Supported Instruction Types

|  Type  | Supported |
|--------|-----------|
| R-Type |     ✓     |
| I-Type |     ✓     |
| Load   |     ✓     |
| Store  |     ✓     |
| Branch |     ✓     |
| LUI    |     ✓     |
| AUIPC  |     ✓     |
| JAL    |     ✓     |
| JALR   |     ✓     |