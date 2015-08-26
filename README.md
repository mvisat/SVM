Sister Virtual Machine
==================
# Introduction
SVM is a simple process virtual machine that allows you to run a program written in [Sister Assembly Language (SASM)](#sister-assembly-language) or run a KEI file (compiled SASM file)

# Architecture
* SVM has 16 registers (0 to 15) of 2 bytes each
* SVM has memory of 65536 bytes (0 to 65535)
* SVM only handles signed integer of 8-bit and 16-bit, but for memory address it uses unsigned integer of 16-bit
* SVM also has a program counter (PC) which always points to the next instruction

# Compilation
To build both interpreter and compiler, execute:
```
$ make
```
To build interpreter only, execute:
```
$ make svm
```
To build compiler only, execute:
```
$ make svmc
```

# Usage
## Interpreter
```
$ svm <sasm file>
$ svm -kei <kei file>
```
## Compiler
```
$ svmc <sasm file 1> <sasm file 2> <sasm file...>
```
# Sister Assembly Language
## Symbol
Symbol | Description
--- | ---
`$x` | x-th register, i.e. `$0` is 0-th register
`M[x]` | Memory at address x, i.e. `M[65535]` is memory at 65535
`.xyz` | Label to mark the next instruction. Label starts with "." character
`@func` | Library call name

## Command
Command Name | Syntax | Description
--- | --- | ---
No Operation | `nop` | Self-explanatory.
Start | `start` | Start of the program to run. A program must has exactly 1 start command.
Add | `add $t $r $s` | `$t = $r + $s`
Add Immediate | `addi $t $r C` | `$t = $r + C`. C is 16-bit integer.
Substract | `sub $t $r $s` | `$t = $r - $s`
Multiply | `mul $t $r $s` | `$t = $r * $s`
And | `and $t $r $s` | `$t = $r && $s`
Or | `or $t $r $s` | `$t = $r || $s`
Not | `not $t $r` | `$t = !$r`
Equal | `eq $t $r $s` | `$t = $r == $s`
Less Than | `lt $t $r $s` | `$t = $r < $s`
Greater Than | `gt $t $r $s` | `$t = $r > $s`
Load | `ld $t $r C` | `$t = M[$r+C:$r+C+1]`. C is integer of 16-bit. Takes 16-bit from `M[$r+C]` and `M[$r+C+1]` with little indian format.
Load Byte | `lb $t $r C` | `$t = M[$r+C]`. C is integer of 16-bit. Takes 8-bit from `M[$r+C]`.
Load Immediate | `ldi $t C` | `$t = C`. C is integer of 16-bit.
Store | `str $t $r C` | `M[$r+C:$r+C+1] = $t`. C is integer of 16-bit. Stored in little endian format.
Store Byte | `stb $t $r C` | `M[$r+C] = $t`. C is integer of 16-bit.
Jump If Zero | `jz $t .label` | `if ($t == 0) PC = .label`
Jump If Not Zero | `jnz $t .label` | `if ($t != 0) PC = .label`
Jump | `jmp .label` | `PC = .label`
Jump Register | `jr $t` | `PC = $t`
Jump And Link | `jal $t .label` | `$t = next(PC); PC = .label`
Library Call | `libc $t $r @func` | `func(out $t, $r)`
Halt | `halt` | Stops execution. A program must has at least 1 halt command.
Comment | `# comment` | Comment in source code, not executed.
Open Library | `lopen fname` | Open library named "fname".
Link | `link @func` | Link a function named "func" to library call. "func" is taken from the last opened library.

## Example
```
# simple test program
# read integer a & b, returns a + b

start
    libc $0 $0 @input
    libc $1 $1 @input

    add $2 $0 $1

    libc $2 $2 @output
halt
```
