from texttable import Texttable

class BoardError(Exception):
    pass


class Board():
    def __init__(self):
        self._values = [0] *36
        self._move_count = 0  

    def get_free_squares(self):
        free = []
        for i in range(36):
            if self._values[i] == 0:
                free.append((i//6, i%6))
        return free
    
    def human_placement(self, row, col, symbol):
        '''
        Places the human chosen position on the board
        :param: 
        row - the row of the table
        col - the column of the table
        symbol - the symbol which the human participates(-1 for X and 1 for O)
        '''
        self._values[6*row + col] = symbol 

    def computer_placement(self, row, col, symbol):
        '''
        Places the computer chosen position on the board
        :param: 
        row - the row of the table
        col - the column of the table
        symbol - the symbol which the human participates(-1 for X and 1 for O)
        '''
        self._values[6*row + col] = -1 * symbol

    def human_won(self, symbol):
        """
        Verifies if the human won
        """
        for r in (0, 6, 12, 18, 24, 30):
            row = self._values[r:r+6]
            if symbol not in row and 0 not in row:
                return True
        for c in range(0, 6):
            col = []
            for row in (6, 12, 18, 24, 30):
                col.append(self._values[row+c])
            if symbol not in col and 0 not in col:
                return True
        diag_1 = []
        for r in range (0, 36, 7):
            diag_1.append(self._values[r])
            if symbol not in diag_1 and 0 not in diag_1:
                return True
        diag_2 = []
        for r in range(5, 31, 5):
            diag_2.append(self._values[r])
            if symbol not in diag_2 and 0 not in diag_2:
                return True

    def computer_won(self):
        """
        Verifies if the human won
        """
        if 0 not in self._values:
            return True
        return False

    def __str__(self):
        table = Texttable()
        display_row = []
        for row in (0, 6, 12, 18, 24, 30):
            display_row = self._values[row:row+6]
            for i in range(6):
                if(display_row[i] == 0):
                    display_row[i] = ' '
                elif display_row[i] == 1:
                    display_row[i] = 'O'
                elif display_row[i] == -1:
                    display_row[i] = 'X'
            table.add_row(display_row)
        return table.draw()
    

