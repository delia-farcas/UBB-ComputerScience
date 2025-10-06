
from typing import List
import pickle
from src.domain.domain import Expense
from src.repository.MemoryRepository import MemoryRepository

class BinaryFileRepository(MemoryRepository):
    def __init__(self, filename: str):
        self.filename = filename
        self.expenses = self._load()

    def add(self, expense: Expense):
        self.expenses.append(expense)
        self.save()

    def get_all(self) -> List[Expense]:
        return self.expenses

    def save(self):
        with open(self.filename, 'wb') as f:
            pickle.dump(self.expenses, f)

    def _load(self) -> List[Expense]:
        try:
            with open(self.filename, 'rb') as f:
                return pickle.load(f)
        except FileNotFoundError:
            return []

