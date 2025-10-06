#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
from texttable import Texttable
import functions

def add_or_insert_expense(list, history):
    command_text = input("->")
    command_text = command_text.strip()
    command_text = command_text.split()
    validate_command(command_text)
    if(command_text[0] == "add"):
        validate_amount(command_text[1])
        functions.add_expense(list, history, command_text[1], command_text[2])
    elif(command_text[0] == "insert"):
        validate_day(command_text[1])
        validate_amount(command_text[1])
        functions.insert_expense(list, history, command_text[1], command_text[2], command_text[3])
    else:
        raise ValueError ("Invalid command")
    

def modify_expenses(list, history):
    command_text = input("->")
    command_text = command_text.strip()
    command_text = command_text.split()
    validate_command(command_text)
    categories = ["housekeeping", "food", "transport", "clothing", "internet", "others"]
    if command_text[1] in categories:
        functions.remove_expenses_type(list, history, command_text[1])
    elif len(command_text) == 2:
        validate_day(command_text[1])
        functions.remove_expenses_day(list, history, command_text[1])
    else:
        validate_day(command_text[1])
        validate_day(command_text[3])
        functions.remove_expenses_interval(list, history, command_text[1], command_text[3])


def display_expenses(list, history):  
    table = Texttable()
    table.header(["Day", "Amount (RON)", "Category"])
    command_text = input("->")
    command_text = command_text.strip()
    command_text = command_text.split()
    validate_command(command_text)
    to_display = []
    if len(command_text) == 1:
        to_display = functions.display(list)
    elif len(command_text) == 2:
        to_display = functions.display_category(list, command_text[1])
    else:
        validate_operator(command_text[3])
        validate_amount(command_text[3])
        to_display = functions.display_moft(list, command_text[1], command_text[2], command_text[3])

    for expense in to_display:
        table.add_row([functions.get_day(expense), functions.get_amount(expense), functions.get_type(expense)])
    print(table.draw())

def filter_expenses(list, history):
    command_text = input("->")
    command_text = command_text.strip()
    command_text = command_text.split()
    validate_command(command_text)
    if len(command_text) == 2:
        functions.filter_category(list, history, command_text[1])
    else:
        validate_operator(command_text[2])
        validate_amount(command_text[3])
        functions.filter_category_moft(list, history, command_text[1], command_text[2], command_text[3])

    
def undo(list, history):
    history.pop()
    list[:] = history[-1]

def test_undo():
    expense_list = [[1, 100, "food"], [2, 200, "transport"]]
    history = [
        [[1, 100, "food"]],
        [[1, 100, "food"], [2, 200, "transport"]],
    ]

    undo(expense_list, history)

    expected_list = [[1, 100, "food"]]
    expected_history = [[[1, 100, "food"]]]

    assert expense_list == expected_list, f"Test failed: {expense_list} != {expected_list}"
    assert history == expected_history, f"Test failed: {history} != {expected_history}"

test_undo()

def validate_command(command_text):
    """
    Validates if the command has the correct number of arguments.
    """
    if not isinstance(command_text, list):
        raise ValueError("Command must be a list of arguments.")

def validate_operator(operator):
    '''
    Validates an operator
    '''
    operators = ["<", ">", "="]
    if operator not in operators:
        raise ValueError("invalid command")

def validate_amount(amount):
    """
    Validates if the amount is a positive integer.
    """
    try:
        amount = int(amount)
        if amount <= 0:
            raise ValueError("Amount must be a positive integer.")
    except ValueError:
        raise ValueError("Amount must be a valid integer.")

def validate_day(day):
    """
    Validates if the day is a valid calendar day (1-31).
    """
    try:
        day = int(day)
        if day < 1 or day > 31:
            raise ValueError("Day must be between 1 and 31.")
    except ValueError:
        raise ValueError("Day must be a valid integer.")


def principal_menu():
    print("Please select an action")
    print("(A) Add a new expense")
    print("(B) Modify expenses")
    print("(C) Display expenses with different properties")
    print("(D) Filter expenses")
    print("(E) Undo")

def create_menu():
    menu = {
        "A" : add_or_insert_expense,
        "B" : modify_expenses,
        "C" : display_expenses,
        "D" : filter_expenses, 
        "E" : undo

    }
    return menu