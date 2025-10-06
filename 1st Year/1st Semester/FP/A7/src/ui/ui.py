from src.services.services import Services

class UI:
    def __init__(self, services: Services):
        self.services = services

    def run(self):
        while True:
            print("1. Add expense")
            print("2. Display all expenses")
            print("3. Filter expenses")
            print("4. Undo last operation")
            print("5. Exit")
            
            choice = input("Enter your choice: ")
            
            if choice == '1':
                self._add_expense()
            elif choice == '2':
                self._display_expenses()
            elif choice == '3':
                self._filter_expenses()
            elif choice == '4':
                self._undo()
            elif choice == '5':
                break
            else:
                print("Invalid choice. Please try again.")

    def _add_expense(self):
        day = int(input("Enter day (1-30): "))
        amount = int(input("Enter amount: "))
        expense_type = input("Enter expense type: ")
        self.services.add_expense(day, amount, expense_type)
        print("Expense added successfully.")

    def _display_expenses(self):
        expenses = self.services.get_all_expenses()
        if not expenses:
            print("No expenses found.")
        else:
            for expense in expenses:
                print(expense)

    def _filter_expenses(self):
        min_amount = int(input("Enter minimum amount: "))
        filtered_expenses = self.services.filter_expenses(min_amount)
        if not filtered_expenses:
            print("No expenses found above the given amount.")
        else:
            for expense in filtered_expenses:
                print(expense)

    def _undo(self):
        if self.services.undo():
            print("Last operation undone successfully.")
        else:
            print("No operations to undo.")

