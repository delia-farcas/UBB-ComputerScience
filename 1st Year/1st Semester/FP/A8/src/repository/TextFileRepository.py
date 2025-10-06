from src.domain.book import Book
from src.domain.client import Client
from src.domain.rental import Rental
from src.repository.MemoryRepository import InMemoryRepository, BookRepository, ClientRepository, RentalRepository
from datetime import datetime

class BookTextFileRepository(BookRepository):
    def __init__(self):
        super().__init__()  # calls constructor of base class
        self._file_loaded = False

    def add(self, element):
        self.__load()
        super().add(element)
        # if there was no exception, the line below is executed
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
        if self._file_loaded is True:
            return
        self._file_loaded = True
        try:
            fin = open("books.txt", "rt")
        except FileNotFoundError:
            return

        line = fin.readline()
        line = line.strip()
        while len(line) > 0:
            tokens = line.split(",")
            super().add(Book(int(tokens[0]), tokens[1], tokens[2]))
            line = fin.readline()
            line = line.strip()
        fin.close()

    def __save(self):
        fout = open("books.txt", "wt")
        for book in self._data.values():
            fout.write(str(book._id) + "," + book._title + "," + book._author + "\n")
        fout.close()


class ClientTextFileRepository(ClientRepository):
    def __init__(self):
        super().__init__()
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
        if self._file_loaded is True:
            return
        self._file_loaded = True
        try:
            fin = open("clients.txt", "rt")
        except FileNotFoundError:
            return

        line = fin.readline()
        line = line.strip()
        while len(line) > 0:
            tokens = line.split(",")
            super().add(Client(int(tokens[0]), tokens[1]))
            line = fin.readline()
            line = line.strip()
        fin.close()

    def __save(self):
        fout = open("clients.txt", "wt")
        for client in self._data.values():
            fout.write(str(client._id) + "," + client._name + "\n")
        fout.close()


class RentalTextFileRepository(RentalRepository):

    def __init__(self):
        super().__init__()
        self._file_loaded = False

    def add(self, element):
        self.__load()
        super().add(element)
        # if there was no exception, the line below is executed
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

    def find_active_rentals(self, book_id):
        self.__load()
        return super().find_active_rentals(book_id)
        
    def __load(self):
        if self._file_loaded is True:
            return
        self._file_loaded = True
        fin = open("rentals.txt", "rt")
        line = fin.readline()
        line = line.strip()
        while len(line) > 0:
            tokens = line.split(",")
            rental_id = int(tokens[0])
            book_id = int(tokens[1])
            client_id = int(tokens[2])
            rented_date = tokens[3]
            returned_date = tokens[4].strip()

            start_date = datetime.strptime(rented_date, "%Y-%m-%d")
            end_date = datetime.strptime(returned_date, "%Y-%m-%d")

            # NOTE we assume input file are correct :)
            #book = self.__book_repo.find(book_id)
            #client = self.__client_repo.find(client_id)
            super().add(Rental(rental_id, book_id, client_id, start_date, end_date))
            line = fin.readline()
        fin.close()

    def __save(self):
        fout = open("rentals.txt", "wt")
        for rental in self._data.values():
            fout.write(
                str(rental._id) + "," + str(rental._book_id) + "," + str(rental._client_id) + "," + rental._rented_date.strftime(
                    "%Y-%m-%d") + "," + rental._returned_date.strftime("%Y-%m-%d") + "\n")
        fout.close()