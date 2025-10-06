import pygame
from src.constants import PURPLE,CREAM, ROWS, COLS, SQUARE_SIZE, WHITE, BLACK
from src.piece import Piece

class Board:
    def __init__(self):
        self._board = []
        self._black_left = self._white_left = 12
        self._black_kings = self._white_kings = 0
        self.create_board()

    def draw_squares(self, win):
        win.fill(PURPLE)
        for row in range(ROWS):
            for col in range(row % 2, ROWS, 2):
                pygame.draw.rect(win, CREAM,(row * SQUARE_SIZE, col * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))

    def evaluate(self):
        return self._white_left - self._black_left + (self._white_kings * 0.5 - self._black_kings * 0.5)

    def get_all_pieces(self, color):
        pieces = []
        for row in self._board:
            for piece in row:
                if piece != 0 and piece._color == color:
                    pieces.append(piece)
        return pieces

    def move(self, piece, row, col):
        self._board[piece._row][piece._col], self._board[row][col] = self._board[row][col], self._board[piece._row][piece._col]
        piece.move(row, col)

        if row == ROWS - 1 or row == 0:
            piece.make_king()
            if piece._color == WHITE:
                self._white_kings += 1
            else:
                self._black_kings += 1

    def get_piece(self, row, col):
        return self._board[row][col]

    def create_board(self):
        for row in range(ROWS):
            self._board.append([])
            for col in range(COLS):
                if (row + col) % 2 == 1:
                    if row < 3:
                        self._board[row].append(Piece(row, col, WHITE))
                    elif row > 4:
                        self._board[row].append(Piece(row, col, BLACK))
                    else:
                        self._board[row].append(0)
                else:
                    self._board[row].append(0)
                    
    def draw(self, win):
        self.draw_squares(win)
        for row in range(ROWS):
            for col in range(COLS):
                piece = self._board[row][col]
                if piece != 0:
                    piece.draw(win)

    def remove(self, pieces):
        for piece in pieces:
            self._board[piece._row][piece._col] = 0
            if piece != 0:
                if piece._color == BLACK:
                    self._black_left -= 1
                else:
                    self._white_left -= 1

    def game_winner(self):
        if self._black_left <= 0:
            return WHITE
        elif self._white_left <= 0:
            return BLACK
        return None
          
    def get_valid_moves(self, piece):
        moves = {}
        left = piece._col - 1
        right = piece._col + 1
        row = piece._row

        if piece._color == BLACK or piece._king:
            moves.update(self._traverse_left(row - 1, max(row - 3, -1), -1, piece._color, left))
            moves.update(self._traverse_right(row - 1, max(row - 3, -1), -1, piece._color, right))
        if piece._color == WHITE or piece._king:
            moves.update(self._traverse_left(row + 1, min(row + 3, ROWS), 1, piece._color, left))
            moves.update(self._traverse_right(row + 1, min(row + 3, ROWS), 1, piece._color, right))
        
        return moves
    
    def _traverse_left(self, start, stop, step, color, left, skipped = []):
        moves = {}
        last = []
        for r in range (start, stop, step):
            if left < 0:
                break
            current = self._board[r][left]
            if current == 0:
                if skipped and not last:
                    break
                elif skipped:
                    moves[(r, left)] = last + skipped
                else:
                    moves[(r, left)] = last
                if last:
                    if step == -1: 
                        row = max(r - 3, 0)
                    else:
                        row = min(r + 3, ROWS)
                    moves.update(self._traverse_left(r+step, row, step, color, left - 1, skipped = last))
                    moves.update(self._traverse_right(r+step, row, step, color, left + 1, skipped = last))
                break
            elif current._color == color:
                break
            else:
                last = [current]


            left -= 1
        return moves


    def _traverse_right(self, start, stop, step, color, right, skipped = []):
        moves = {}
        last = []
        for r in range (start, stop, step):
            if right >= COLS:
                break

            current = self._board[r][right]
            if current == 0:
                if skipped and not last:
                    break
                elif skipped:
                    moves[(r, right)] = last + skipped
                else:
                    moves[(r, right)] = last
                if last:
                    if step == -1: 
                        row = max(r - 3, 0)
                    else:
                        row = min(r + 3, ROWS)
                    moves.update(self._traverse_left(r+step, row, step, color, right - 1, skipped = last))
                    moves.update(self._traverse_right(r+step, row, step, color, right + 1, skipped = last))
                break
            elif current._color == color:
                break
            else:
                last = [current]


            right += 1
        return moves

