import pickle
from src.domain.book import Book
from src.domain.client import Client
from src.domain.rental import Rental
from src.repository.MemoryRepository import BookRepository, ClientRepository, RentalRepository
from datetime import datetime

class BookBinaryRepository(BookRepository):
    def __init__(self, file_path="books.bin"):
        super().__init__()
        self._file_path = file_path
        self._file_loaded = False

    def add(self, element):
        self.__load()
        super().add(element)
        self.__save()

    def remove(self, elem_id: int):
        self.__load()
        super().remove(elem_id)
        self.__save()

    def update(self, element):
        self.__load()
        super().update(element)
        self.__save()

    def find_by_id(self, entity_id):
        self.__load()
        return super().find_by_id(entity_id)
    
    def find_by_title(self, title):
        self.__load()
        return super().find_by_title(title)

    def find_by_author(self, author):
        self.__load()
        return super().find_by_author(author)

    def __iter__(self):
        self.__load()
        return super().__iter__()

    def __len__(self):
        self.__load()
        return super().__len__()

    def __getitem__(self, item):
        self.__load()
        return super().__getitem__()

    def __load(self):
        if self._file_loaded:
            return
        try:
            with open(self._file_path, "rb") as file:
                self._data = pickle.load(file)
        except (FileNotFoundError, EOFError):
            self._data = {}
        self._file_loaded = True

    def __save(self):
        with open(self._file_path, "wb") as file:
            pickle.dump(self._data, file)

class ClientBinaryRepository(ClientRepository):
    def __init__(self, file_path="clients.bin"):
        super().__init__()
        self._file_path = file_path
        self._file_loaded = False

    def add(self, element):
        self.__load()
        super().add(element)
        self.__save()

    def remove(self, elem_id: int):
        self.__load()
        super().remove(elem_id)
        self.__save()

    def update(self, element):
        self.__load()
        super().update(element)
        self.__save()

    def find_by_id(self, elem_id):
        self.__load()
        return super().find_by_id(elem_id)

    def find_by_name(self, name):
        self.__load()
        return super().find_by_name(name)

    def __iter__(self):
        self.__load()
        return super().__iter__()

    def __len__(self):
        self.__load()
        return super().__len__()

    def __getitem__(self, item):
        self.__load()
        return super().__getitem__()

    def __load(self):
        if self._file_loaded:
            return
        try:
            with open(self._file_path, "rb") as file:
                self._data = pickle.load(file)
        except (FileNotFoundError, EOFError):
            self._data = {}
        self._file_loaded = True

    def __save(self):
        with open(self._file_path, "wb") as file:
            pickle.dump(self._data, file)

class RentalBinaryRepository(RentalRepository):
    def __init__(self, file_path="rentals.bin"):
        super().__init__()
        self._file_path = file_path
        self._file_loaded = False

    def add(self, element):
        self.__load()
        super().add(element)
        self.__save()

    def remove(self, elem_id: int):
        self.__load()
        super().remove(elem_id)
        self.__save()

    def find_by_id(self, rental_id):
        self.__load()
        return super().find_by_id(rental_id)

    def find_by_book(self, book_id):
        self.__load()
        return super().find_by_book(book_id)

    def find_by_client(self, client_id):
        self.__load()
        return super().find_by_client(client_id)

    def find_active_rentals(self, book_id=None):
        self.__load()
        return super().find_active_rentals(book_id)

    def __load(self):
        if self._file_loaded:
            return
        try:
            with open(self._file_path, "rb") as file:
                self._data = pickle.load(file)
        except (FileNotFoundError, EOFError):
            self._data = {}
        self._file_loaded = True

    def __save(self):
        with open(self._file_path, "wb") as file:
            pickle.dump(self._data, file)
