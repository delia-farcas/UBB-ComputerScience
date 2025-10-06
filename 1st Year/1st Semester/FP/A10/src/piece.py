from src.constants import BLACK, WHITE, GREY, SQUARE_SIZE, CROWN
import pygame

class Piece:
    PADDING = 15
    OUTLINE = 3

    def __init__(self, row, col, color):
        self._row = row
        self._col = col
        self._color = color
        self._king = False
        self._x = 0
        self._y = 0
        self.calc_pos()

    def calc_pos(self):
        self._x = SQUARE_SIZE * self._col + SQUARE_SIZE//2
        self._y = SQUARE_SIZE * self._row + SQUARE_SIZE//2

    def make_king(self):
        self._king = True

    def draw(self, win):
        radius = SQUARE_SIZE//2 - self.PADDING
        pygame.draw.circle(win, GREY, (self._x, self._y), radius + self.OUTLINE)
        pygame.draw.circle(win, self._color, (self._x, self._y), radius)
        if self._king:
            win.blit(CROWN, (self._x - CROWN.get_width()//2, self._y - CROWN.get_height()//2))
    
    def move(self, row, col):
        self._row = row
        self._col = col
        self.calc_pos()

    def __repr__(self):
        return str(self._color)


    

