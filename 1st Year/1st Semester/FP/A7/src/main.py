import random
from repository.MemoryRepository import MemoryRepository
from repository.BinaryRepository import  BinaryFileRepository
from repository.TextFileRepository import TextFileRepository
from services.services import Services
from ui.ui import UI


def generate_initial_expenses(services: Services):
    expense_types = ['Food', 'Transport', 'Utilities', 'Entertainment', 'Clothing']
    for _ in range(10):
        day = random.randint(1, 30)
        amount = random.randint(10, 1000)
        expense_type = random.choice(expense_types)
        services.add_expense(day, amount, expense_type)
    services.undo_stack.clear()  # Clear undo stack for initial expenses

if __name__ == "__main__":
    # Uncomment the repository you want to use
    repository = MemoryRepository()
    #repository = TextFileRepository("../expenses.txt")
    #repository = BinaryFileRepository("../expense.bin")
    
    #print("File Location:", repository.filename)
   
    services = Services(repository)
    generate_initial_expenses(services)
    
    
    ui = UI(services)
    ui.run()

