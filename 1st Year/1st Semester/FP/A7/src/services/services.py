from typing import List
from src.domain.domain import Expense
from src.repository.BinaryRepository import MemoryRepository

class Services:
    def __init__(self, repository):
        self.repository = repository
        self.undo_stack = []

    def add_expense(self, day: int, amount: int, expense_type: str):
        expense = Expense(day, amount, expense_type)
        self.repository.add(expense)
        self.undo_stack.append(('add', expense))

    def get_all_expenses(self) -> List[Expense]:
        return self.repository.get_all()

    def filter_expenses(self, min_amount: int) -> List[Expense]:
        return [expense for expense in self.repository.get_all() if expense.amount > min_amount]

    def undo(self) -> bool:
        if not self.undo_stack:
            return False
        
        action, expense = self.undo_stack.pop()
        if action == 'add':
            self.repository.expenses.remove(expense)
        self.repository.save()
        return True

