#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
import ui
from functions import create_list_expenses


def start():
    list = []
    history = []
    create_list_expenses(list, history)
    menu = ui.create_menu()
    while True:
       try:
          ui.principal_menu()
          command = input ("->")
          if command in menu:
              menu[command](list, history)
              print("Solved!")
          else:
              print("Invalid command")
       except ValueError as ve:
        print(ve)
        

    
start()