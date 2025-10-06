

class Expense:
    def __init__(self, day: int, amount: int, expense_type: str):
        self.day = day
        self.amount = amount
        self.expense_type = expense_type

    def __str__(self):
        return f"Day: {self.day}, Amount: {self.amount}, Type: {self.expense_type}"

