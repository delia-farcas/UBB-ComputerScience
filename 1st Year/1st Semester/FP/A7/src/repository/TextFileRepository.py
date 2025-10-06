from typing import List
from src.repository.MemoryRepository import MemoryRepository
from src.domain.domain import Expense

class TextFileRepository(MemoryRepository):
    def __init__(self, filename: str):
        self.filename = filename
        self.expenses = self._load()

    def add(self, expense: Expense):
        self.expenses.append(expense)
        self.save()

    def get_all(self) -> List[Expense]:
        return self.expenses

    def save(self):
        with open(self.filename, 'w') as f:
            for expense in self.expenses:
                f.write(f"{expense.day},{expense.amount},{expense.expense_type}\n")

    def _load(self) -> List[Expense]:
        expenses = []
        try:
            with open(self.filename, 'r') as f:
                for line in f:
                    day, amount, expense_type = line.strip().split(',')
                    expenses.append(Expense(int(day), int(amount), expense_type))
        except FileNotFoundError:
            pass
        return expenses
    
