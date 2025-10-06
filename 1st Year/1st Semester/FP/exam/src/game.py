from domain import BoardError
from random import choice

class Game:
    def __init__(self, board):
        self._board = board
        self._last_row = 0
        self._last_col = 0

    def human_moves(self, row, col, symbol):
        '''
        Verifies the positions and places them on the board
        :param: 
        row - the row of the table
        col - the column of the table
        symbol - the symbol which the human participates(-1 for X and 1 for O)
        :raises:
        BoardError if position isnt available
        '''
        if row > 5 or col > 5:
            raise BoardError("Invalid row/column")
        free = self._board.get_free_squares()
        if (row, col) not in free:
            raise BoardError("Position is already taken")
        self._board.human_placement(row, col, symbol)
        self._last_row = row
        self._last_col = col

    def computer_moves(self, symbol):
        """
        The computer chooses a position to place the piece
        :param:
        symbol - the symbol which the human participates(-1 for X and 1 for O)
        """
        free = self._board.get_free_squares()
        if (self._last_row - 1, self._last_col) in free:
             self._board.computer_placement(self._last_row-1, self._last_col, symbol)
        elif (self._last_row-1, self._last_col -1) in free:
             self._board.computer_placement(self._last_row-1, self._last_col-1, symbol)
        elif (self._last_row, self._last_col +1) in free:
             self._board.computer_placement(self._last_row, self._last_col + 1, symbol)
        elif (self._last_row + 1, self._last_col + 1) in free:
             self._board.computer_placement(self._last_row + 1, self._last_col + 1, symbol)
        else:
            row, col = choice(free)
            self._board.computer_placement(row, col, symbol)

    def is_won(self, symbol):
        """
        Verifies if the human won
        """
        return self._board.human_won(symbol)
    
    def is_lost(self):
        """
        Verifies if the computer won
        """
        return self._board.computer_won()
    
