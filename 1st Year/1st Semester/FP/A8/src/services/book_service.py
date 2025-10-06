from src.domain.book import Book, ValidatorBook
from src.repository.TextFileRepository import BookTextFileRepository, RentalTextFileRepository
from src.repository.MemoryRepository import InMemoryRepository, BookRepository, RentalRepository
from src.services.service_exception import ServiceException
from src.services.rental_service import RentalService
from faker import Faker

class BookService:
    def __init__(self, book_repo = BookRepository(), rental_repo = RentalRepository(), validator = ValidatorBook()):
        self._book_repo = book_repo
        self._rental_repo = rental_repo
        self._book_validator = validator
        self._rental_service = RentalService(rental_repo)
        self._faker = Faker()

    def add_book(self, book_id: int, title: str, author: str):
        """
        Adds a new book to the repository.
        :param book_id: The unique ID of the book.
        :param title: The title of the book.
        :param author: The author of the book.
        :raises ValueError: If a book with the given ID already exists.
        """
        book = Book(book_id, title, author)
        self._book_validator.validate_book(book)
        self._book_repo.add(book)
        print("Book added succesfully!")
        

    def remove_book(self, book_id: int):
        """
        Removes a book from the repository.
        :param book_id: The ID of the book to remove.
        :raises ValueError: If the book does not exist.
        """
        if self._book_repo.find_by_id(book_id) is None:
            raise ServiceException(f"Book with ID {book_id} does not exist.")
        book = self._book_repo.find_by_id(book_id)
        self._book_repo.remove(book_id)
        print("Book removed succesfully!")

        #Remove the book"s rentals
        try:
            rentals = self._rental_repo.find_by_book(book_id)
            for rent in rentals:
                self._rental_repo.remove(rent.get_id)
        except ServiceException:
            pass
        except TypeError:
            pass
        return book
    
    def update_book(self, book_id: int, new_title: str, new_author: str):
        """
        Updates the details of an existing book.

        :param book_id: The ID of the book to update.
        :param new_title: The new title for the book.
        :param new_author: The new author for the book.
        :raises ValueError: If the book does not exist.
        """
        updated_book = Book(book_id, new_title, new_author)
        self._book_validator.validate_book(updated_book)
        self._book_repo.update(updated_book)
        print("Book updated succesfully!")

    def find_by_id(self, book_id: int):
        """
        Retrieves a book by its ID.

        :param book_id: The ID of the book to retrieve.
        :return: The book object with the given ID.
        :raises ServiceException: If the book does not exist.
        """
        book = self._book_repo.find_by_id(book_id)
        if book is None:
            raise ServiceException(f"Book with ID {book_id} does not exist.")
        return book
    
    def find_by_title(self, book_title):
        books = self._book_repo.find_by_title(book_title)
        if books is None:
            raise ServiceException(f"We do not have books with title {book_title}.")
        return books
    
    def find_by_author(self, book_author):
        books = self._book_repo.find_by_author(book_author)
        if books is None:
            raise ServiceException(f"We don't have books written by {book_author}")
        return books

    def list_books(self):
        """
        Lists all the books in the repository.

        :return: A list of all books.
        """
        return self._book_repo.list_all()
    
    def generate_books(self, count=20):
        """
        Generates random books and adds them to the repository.
        :param count: The number of books to generate (default is 20).
        """
        for _ in range(count):
            book_id = self._faker.unique.random_int(min=1, max=1000)
            title = self._faker.text(max_nb_chars=20).strip(".")  # Generate a random title
            author = self._faker.name()  # Generate a random author name
            book = Book(book_id, title, author)
            self._book_validator.validate_book(book)
            self._book_repo.add(book)

