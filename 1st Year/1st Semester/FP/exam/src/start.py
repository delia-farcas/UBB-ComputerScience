from ui import UI
from game import Game
from domain import Board, BoardError


def start():
    board = Board()    
    game = Game(board)
    ui = UI(game, board)
    ui.principal_menu()

start()