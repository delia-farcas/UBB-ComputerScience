#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
from random import choice, randint
from datetime import datetime

def create_expense(day, amount, type):
    return [day, amount, type]

def test_create_expense():
    day = 15
    amount = 300
    expense_type = "food"
    result = create_expense(day, amount, expense_type)
    expected = [15, 300, "food"]
    assert result == expected, f"Test failed: {result} != {expected}"

    day = 1
    amount = 0
    expense_type = "others"
    result = create_expense(day, amount, expense_type)
    expected = [1, 0, "others"]
    assert result == expected, f"Test failed: {result} != {expected}"

    day = 31
    amount = 10000
    expense_type = "luxury"
    result = create_expense(day, amount, expense_type)
    expected = [31, 10000, "luxury"]
    assert result == expected, f"Test failed: {result} != {expected}"

test_create_expense()


def get_day(expense):
    return expense[0]

def get_amount(expense):
    return expense[1]

def get_type(expense):
    return expense[2]  

def create_list_expenses(list, history):
    expenses_list = ["housekeeping", "food", "transport", "clothing", "internet", "others"]
    for i in range (10):
        day = randint(1, 31)
        amount = randint(10, 1000)
        type = choice(expenses_list)
        list.append(create_expense(day, amount, type)) 
    history.append(list.copy())

def add_expense(list, history, amount, type):
    now = datetime.now()
    expense = create_expense(now.day, amount, type)
    list.append(expense)
    history.append(list.copy())

def insert_expense(list, history, day, amount, type):
    expense = create_expense(day, amount, type)
    list.append(expense)
    history.append(list.copy())

def remove_expenses_day(list, history, day):
    i = 0
    while i < len(list):
        if get_day(list[i]) == day:
            list.pop(i)
        else:
            i += 1
    history.append(list.copy())
    
def remove_expenses_interval(list, history, day1, day2):
    i = 0
    while i < len(list):
        if int(get_day(list[i])) >= int(day1) and int(get_day(list[i])) <= int(day2):
            list.pop(i)
        else:
            i += 1
    history.append(list.copy())
    
def remove_expenses_type(list, history, expense_name):
    i = 0
    while i < len(list):
        if get_type(list[i]) == expense_name:
            list.pop(i)
        else:
            i += 1
    history.append(list.copy())

def display(list):
    return list

def display_category(list, type):
    to_display = []
    for i in list:
        if get_type(i) == type:
         to_display.append(i)
    return to_display

def display_moft(list, type, operator, value):
    to_display = []
    for i in list:
        if get_type(i) == type and condition(operator, get_amount(i), value) == True:
             to_display.append(i)
    return to_display


def filter_category(list, history, type):
    i = 0
    while i < len(list):
        if get_type(list[i]) != type:
         list.pop(i)
        else:
            i += 1
    history.append(list.copy())

def filter_category_moft(list, history, type, operator, value):
    i = 0
    while i < len(list):
        if get_type(list[i]) != type:
            list.pop(i)
        else:
            i += 1
    i = 0
    while i < len(list):
        if condition(operator, get_amount(list[i]), value) == False:
            list.pop(i)
        else:
            i += 1
    history.append(list.copy())

def condition(operator, value1, value2):
    value1 = int(value1)
    value2 = int(value2)
    if operator == "<":
        return value1 < value2
    elif operator == "=":
        return value1 == value2
    elif operator == ">":
        return value1 > value2

