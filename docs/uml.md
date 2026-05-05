``` mermaid
classDiagram
%% Патерн Observer для сповіщень
class Observer {
    <<interface>>
    +update(String message)
}
class NotificationService {
    +update(String message)
}
Observer <|-- NotificationService

%% Патерн Strategy для нарахування відсотків
class InterestStrategy {
    <<interface>>
    +calculate(double balance) double
}
class SavingsInterest {
    +calculate(double balance) double
}
class FixedDepositInterest {
    +calculate(double balance) double
}
InterestStrategy <|-- SavingsInterest
InterestStrategy <|-- FixedDepositInterest

%% Патерн Command для операцій та відміни
class Command {
    <<interface>>
    +execute() bool
    +undo()
}
class DepositCommand {
    -Account account
    -double amount
    +execute()
    +undo()
}
class WithdrawCommand {
    -Account account
    -double amount
    +execute()
    +undo()
}
Command <|-- DepositCommand
Command <|-- WithdrawCommand

%% Основні сутності
class Client {
    +String name
    +String taxId
    +Account[] accounts
    +addAccount(Account acc)
}

class Account {
    +String accountNumber
    +double balance
    -InterestStrategy strategy
    -Observer[] observers
    -Transaction[] history
    +setInterestStrategy(InterestStrategy s)
    +applyInterest()
    +attach(Observer o)
    +notify(String msg)
}

class Transaction {
    +String id
    +double amount
    +DateTime timestamp
    +String type
}

%% Зв'язки
Client "1" *-- "many" Account : має масив
Account "1" *-- "many" Transaction : зберігає історію
Account o-- "1" InterestStrategy : використовує
Account o-- "many" Observer : сповіщає
DepositCommand --> Account : змінює баланс
WithdrawCommand --> Account : змінює баланс
```