# Bank_emulator
Освiтнiй мiнi-проєкт для демонстрацiї навичків, здобутих підчас проходження навчальної практики. 
Система є емулятором банківської системи, та містить такі сутності як: сутності: рахунĸи, транзаĸції, депозити; 

## Можливостi


## Архiтектура
```
Aplication
├── 

Core
├── Account
├── Client
├── DepositCommand/withDrawCommand
├── Transaction
├── Observer
└── ICommand


Infrastructure
├── AccountSaver


Console
├── 
├── 
├── 
└── 
Entry Point
└── main.cpp
```

## Збирання та запуск
### Вимоги
- CMake 3.20+
- C++17 компiлятор
- GTest для тестiв

### Збирання
```bash
cmake -B build
cmake --build build
```

### Запуск програми
```bash
./build/Debug/Bank_emulator.exe
```

### Запуск тестiв
```bash
./build/Debug/Systemtests.exe
```

## Бiзнес-правила




## Документацiя

