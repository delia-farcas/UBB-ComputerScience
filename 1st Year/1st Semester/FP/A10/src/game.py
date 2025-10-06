import pygame
from src.board import Board
from src.constants import BLACK, WHITE, BLUE, SQUARE_SIZE

class Game:
    def __init__(self, win):
        self._init()
        self._win = win

    def update(self):
        self._board.draw(self._win)
        self.draw_valid_moves(self._valid_moves)
        pygame.display.update()

    def _init(self):
        self._selected = None
        self._board = Board()
        self._turn = BLACK
        self._valid_moves = {}

    def winner(self):
        return self._board.game_winner()

    def reset(self):
        self._init()

    def select(self, row, col):
        if self._selected:
            result = self._move(row, col)
            if not result:
                self._selected = None
                self.select(row, col)
        
        piece = self._board.get_piece(row, col)
        if piece != 0 and piece._color == self._turn:
            self._selected = piece
            self._valid_moves = self._board.get_valid_moves(piece)
            return True
        return False

    def _move(self, row, col):
        piece = self._board.get_piece(row, col)
        if self._selected and piece == 0 and (row, col) in self._valid_moves:
            self._board.move(self._selected, row, col)
            skipped = self._valid_moves[(row, col)]
            if skipped:
                self._board.remove(skipped)
            self.change_turn()
        else:
            return False
        return True
    
    def draw_valid_moves(self, moves):
        for move in moves:
            row, col = move
            pygame.draw.circle(self._win, BLUE, (col * SQUARE_SIZE + SQUARE_SIZE//2, row * SQUARE_SIZE + SQUARE_SIZE//2), 15)
    
    def change_turn(self):
        self._valid_moves = {}
        if self._turn == BLACK:
            self._turn = WHITE
        else:
            self._turn = BLACK

    def get_board(self):
        return self._board

    def ai_move(self, board):
        self._board = board
        self.change_turn()

        



