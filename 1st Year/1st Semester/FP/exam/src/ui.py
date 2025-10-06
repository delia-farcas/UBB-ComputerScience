
from game import Game
from domain import Board, BoardError

class UI:
    def __init__(self, game, board):
        self._game = game
        self._board = board
        self._symbol = 0
        pass
    
    def choose_symbol(self):
        while True:
            print("Please choose your symbol(X or 0)")
            symbol = input("->")
            if(symbol == 'X'):
                self._symbol = -1
                break
            elif(symbol == 'O'):
                self._symbol = 1
                break
            else:
                print("Invalid! Choose between X and O")

    def human_turn(self):
        while True:
            try:
                row = int(input("Choose row:"))
            except ValueError:
                print("Row should be an integer")
                continue
            try:
                col = int(input("Choose col:"))
            except ValueError:
                print("Col should be an integer")
                continue
            try:
                self._game.human_moves(row, col, self._symbol)
                print(self._board)
                break
            except BoardError as be:
                print(be)

    def computer_turn(self):
        self._game.computer_moves(self._symbol)
        print(self._board)

    def principal_menu(self):
        print("Welcome to order and chaos!!")
        self.choose_symbol()
        print("This is the table")
        print(self._board)
        while True:
            self.human_turn()
            self.computer_turn()
            if self._game.is_won(self._symbol):
                print("Congrats! You won!")
                break
            if self._game.is_lost():
                print("You lost hahaha!!")
                break
