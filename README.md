# Bank_emulator
Освiтнiй мiнi-проєкт для демонстрацiї навичків, здобутих підчас проходження навчальної практики. 
Система є емулятором банківської системи, та містить такі сутності як: сутності: рахунĸи, транзаĸції, депозити; 

## Можливостi
- Створення, видалення та пошук рахункiв i клiєнтiв через `AccountManager` та `ClientManager`.
- Операцiї з рахунками: поповнення, зняття, переказ, нарахування вiдсоткiв, списання комiсiї.
- Iсторiя транзакцiй у кожного рахунку.
- Спостерiгачi (`Observer`) для отримання повiдомлень про змiни балансу.
- Командний пiдхiд для операцiй (депозит/зняття) з можливiстю вiдмiни через `TransactionManager`.
- Збереження та вiдновлення даних у файли через `AccountSaver` i `ClientSaver`.


## Архiтектура
```
Aplication
├── AccountManager
├── BankService
├── ClientManager
├── DepositCommand/withDrawCommand
└── TransactionManager

Core
├── Account
├── Client
├── Transaction
├── Observer
├── InterestStrategy
├── NotificationService
└── ICommand

Infrastructure
├── AccountSaver
└── ClientSaver

Console
├──  AccountUI
├──  ClientUI
├── MainMenu
└── TransactionUI

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
- Номер рахунку не може бути порожнiм, початковий баланс не може бути вiд’ємним.
- Iм’я клiєнта не може бути порожнiм; `taxId` генерується на основi iменi.
- Операцiї поповнення/зняття приймають тiльки додатнi суми.
- Зняття та переказ неможливi, якщо сума бiльша за поточний баланс.
- Комiсiя списується тiльки якщо на рахунку достатньо коштiв.
- Вiдсотки нараховуються лише при заданiй стратегiї (`InterestStrategy`).
- Кожна успiшна операцiя додається в iсторiю транзакцiй i сповiщає пiдписникiв.



