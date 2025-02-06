# Problem Set 1 for STDISCM
**Link to Github Repository: **(Github)[https://github.com/yuuungch/stdiscm-pset1]

## Instructions to Run:
- Open with Visual Studio
- Run in Debug mode, can be with (F5) or without debugger (Ctrl + F5)

## Config File Contents:
| Variable |         Description |
|----------|--------------------:|
| X        | number of threads   |
| y        | prime numbers range |

## File Directory:
| File             | Description                                            |
|------------------|--------------------------------------------------------|
| A1               | immediate printing with divided search range           |
| A2               | deferred printing with divided search range            |
| B1               | immediate printing with divisibility testing           |
| B2               | deferred printing with divisibility testing            |
| config_reader    | config file reader                                     |
| prime_operations | prime number operations used for divided search range  |
| main             | main function                                          |

## Expected Results for each File:
| File | Result                                                                                      |
|------|---------------------------------------------------------------------------------------------|
| A1   | prime numbers will appear immediately and simultaneous with other threads                   |
| A2   | prime numbers will appear collectively and arranged ascendingly                             |
| B1   | prime numbers will appear immediately, ascendingly, and with the thread id last used        |
| B2   | prime numbers will appear collectively and arranged ascendingly                             |
