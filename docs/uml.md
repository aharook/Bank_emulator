``` mermaid
classDiagram

    
    class Observer {
        <<interface>>
        +update(String message)
    }
    class NotificationService {
        +update(String message)
    }
    Observer <|-- NotificationService


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


    class TransactionType {
        <<enumeration>>
        DEPOSIT
        WITHDRAWAL
        TRANSFER
        INTEREST_PAYMENT
        FEE_DEDUCTION
    }

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
        +TransactionType type
    }
    class AccountSaver{
        +filePath_
        +cache
        +save(account)
        +getAll() const
        +findByNumber()
        +saveToFile()
        +loadFromFile()
    }
    
    Client "1" *-- "many" Account 
    Account "1" *-- "many" Transaction 
    Account o-- "1" InterestStrategy 
    Account o-- "many" Observer 
    Transaction --> TransactionType 
    DepositCommand --> Account
    WithdrawCommand --> Account 
    AccountSaver --> Account
```