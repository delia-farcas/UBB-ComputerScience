from src.domain.validator_exception import ValidatorException

class Book:
    def __init__(self, book_id, title, author):
        self._id = book_id
        self._title = title
        self._author = author

    @property
    def get_id(self):
        return self._id
    
    @property
    def get_title(self):
        return self._title
    
    @property
    def get_author(self):
        return self._author
    
    def __str__(self):
        return f'Book ID: {self._id}, title: {self._title}, author: {self._author}'
    
    def __repr__(self):
        return str(self)
    
class ValidatorBook:

   def validate_book(self, book):
        _errors = []
        if not isinstance(book, Book):
            raise TypeError("This is not a book")
        if book._id <= 0:
            _errors.append("Id should be a positive number")
        if len(book._title) == 0:
            _errors.append("Title invalid")
        if len(book._author) == 0:
            _errors.append("Book should have an author")
        if _errors:
            raise ValidatorException(_errors)