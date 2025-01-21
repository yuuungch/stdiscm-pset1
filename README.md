# Problem Set 1 for STDISCM

## Instructions to Run:
- Open with Visual Studio
- Run in Debug mode, can be with (F5) or without debugger (Ctrl + F5)

## Config File Contents:
| Variable |         Description |
|----------|--------------------:|
| X        | number of threads   |
| y        | prime numbers range |

## File Directory:
| File             | Description                                  |
|------------------|----------------------------------------------|
| A1               | immediate printing with divided search range |
| A2               | deferred printing with divided search range  |
| B1               | immediate printing with linear search        |
| B2               | deferred printing with linear search         |
| config_reader    | config file reader                           |
| prime_operations | prime number operations used by the 4 files  |
| main             | main function                                |

## Expected Results for each File:
| File | Result                                                                                      |
|------|---------------------------------------------------------------------------------------------|
| A1   | prime numbers will appear immediately and in pseudo-randomized order (due to search range)  |
| A2   | prime numbers will appear collectively and in pseudo-randomized order (due to search range) |
| B1   | prime numbers will appear immediately and in an ordered manner                              |
| B2   | prime numbers will appear collectively and in an ordered manner                             |