from typing import List
from src.domain.domain import Expense

class MemoryRepository:
    def __init__(self):
        self.expenses = []

    def add(self, expense: Expense):
        self.expenses.append(expense)

    def get_all(self) -> List[Expense]:
        return self.expenses

    def save(self):
        pass  # No need to save for in-memory repository