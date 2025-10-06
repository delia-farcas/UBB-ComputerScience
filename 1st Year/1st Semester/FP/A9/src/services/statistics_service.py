from src.repository.MemoryRepository import InMemoryRepository, BookRepository, RentalRepository, ClientRepository
from src.repository.TextFileRepository import RentalTextFileRepository, BookTextFileRepository, ClientTextFileRepository
from datetime import datetime, timedelta

class StatisticsService:
    def __init__(self, rental_repository = RentalRepository(), book_repository = BookRepository(), client_repository = ClientRepository()):
        """
        Initialize the StatisticsService.

        :param rental_repository: Repository of rentals.
        :param book_repository: Repository of books.
        :param client_repository: Repository of clients.
        """
        self._rental_repository = rental_repository
        self._book_repository = book_repository
        self._client_repository = client_repository

    def most_rented_books(self):
        """
        Get the list of books sorted in descending order of the number of times they were rented.

        :return: List of tuples (book, rental_count), sorted by rental_count.
        """
        rental_counts = {}
        for rental in self._rental_repository.list_all():
            book_id = rental._book_id
            rental_counts[book_id] = rental_counts.get(book_id, 0) + 1
        sorted_books = sorted(
            rental_counts.items(), key=lambda item: item[1], reverse=True
        )
        result = []
        for book_id, count in sorted_books:
            book = self._book_repository.find_by_id(book_id)
            result.append((book._title, count))
        for book in self._book_repository.list_all():
            if book._id not in rental_counts:
                 result.append((book._title, 0))
        return result

    
    def most_active_clients(self):
        """
        Get the list of clients sorted in descending order of the number of book rental days.

        :return: List of tuples (client, total_rental_days), sorted by total_rental_days.
        """
        rental_days = {}
        for rental in self._rental_repository.list_all():
            client_id = rental._client_id
            days_rented = (rental._returned_date - rental._rented_date).days
            rental_days[client_id] = rental_days.get(client_id, 0) + days_rented

        sorted_clients = sorted(
            rental_days.items(), key=lambda item: item[1], reverse=True
        )
        result = []
        for client_id, count in sorted_clients:
            client = self._client_repository.find_by_id(client_id)
            result.append((client._name, count))
        for client in self._client_repository.list_all():
            if client._id not in rental_days:
                result.append((client._name, 0))
        return result

    def most_rented_authors(self):
        """
        Get the list of authors sorted in descending order of the number of rentals their books have.

        :return: List of tuples (author, rental_count), sorted by rental_count.
        """
        author_rentals = {}
        for rental in self._rental_repository.list_all():
            book = self._book_repository.find_by_id(rental._book_id)
            author = book._author
            author_rentals[author] = author_rentals.get(author, 0) + 1

        sorted_authors = sorted(
            author_rentals.items(), key=lambda item: item[1], reverse=True
        )

        for book in self._book_repository.list_all():
            if book._author not in author_rentals:
                sorted_authors.append((book._author, 0))
        return sorted_authors

