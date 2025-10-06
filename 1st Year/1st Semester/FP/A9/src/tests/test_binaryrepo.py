import unittest
import os
import pickle
from datetime import datetime, timedelta

from src.domain.book import Book
from src.domain.client import Client
from src.domain.rental import Rental
from src.repository.MemoryRepository import BookBinaryRepository, ClientBinaryRepository, RentalBinaryRepository
from src.repository.repository_exception import RepositoryException


class TestBookBinaryRepository(unittest.TestCase):
    def setUp(self):
        self.file_path = "test_books.bin"
        # Prepopulate file with test data
        with open(self.file_path, "wb") as file:
            data = {
                1: Book(1, "1984", "George Orwell"),
                2: Book(2, "Brave New World", "Aldous Huxley"),
            }
            pickle.dump(data, file)
        self.repo = BookBinaryRepository(self.file_path)

    def tearDown(self):
        if os.path.exists(self.file_path):
            os.remove(self.file_path)

    def test_find_by_id(self):
        book = self.repo.find_by_id(1)
        self.assertEqual(book._title, "1984")
        self.assertIsNone(self.repo.find_by_id(99))

    def test_add_book(self):
        new_book = Book(3, "Fahrenheit 451", "Ray Bradbury")
        self.repo.add(new_book)
        self.assertEqual(self.repo.find_by_id(3)._title, "Fahrenheit 451")

    def test_add_existing_book_raises_exception(self):
        with self.assertRaises(RepositoryException):
            self.repo.add(Book(1, "Duplicate Book", "Unknown"))

    def test_remove_book(self):
        self.repo.remove(1)
        self.assertIsNone(self.repo.find_by_id(1))

    def test_update_book(self):
        updated_book = Book(1, "Animal Farm", "George Orwell")
        self.repo.update(updated_book)
        self.assertEqual(self.repo.find_by_id(1)._title, "Animal Farm")


class TestClientBinaryRepository(unittest.TestCase):
    def setUp(self):
        self.file_path = "test_clients.bin"
        # Prepopulate file with test data
        with open(self.file_path, "wb") as file:
            data = {
                1: Client(1, "John Doe"),
                2: Client(2, "Jane Smith"),
            }
            pickle.dump(data, file)
        self.repo = ClientBinaryRepository(self.file_path)

    def tearDown(self):
        if os.path.exists(self.file_path):
            os.remove(self.file_path)

    def test_find_by_id(self):
        client = self.repo.find_by_id(1)
        self.assertEqual(client._name, "John Doe")
        self.assertIsNone(self.repo.find_by_id(99))

    def test_add_client(self):
        new_client = Client(3, "Alice Brown")
        self.repo.add(new_client)
        self.assertEqual(self.repo.find_by_id(3)._name, "Alice Brown")

    def test_remove_client(self):
        self.repo.remove(1)
        self.assertIsNone(self.repo.find_by_id(1))

    def test_update_client(self):
        updated_client = Client(1, "Johnny Doe")
        self.repo.update(updated_client)
        self.assertEqual(self.repo.find_by_id(1)._name, "Johnny Doe")


class TestRentalBinaryRepository(unittest.TestCase):
    def setUp(self):
        self.file_path = "test_rentals.bin"
        today = datetime.now().date()
        tomorrow = today + timedelta(days=1)

        # Prepopulate file with test data
        with open(self.file_path, "wb") as file:
            data = {
                1: Rental(1, 101, 201, today, tomorrow),
                2: Rental(2, 102, 202, today, today),
            }
            pickle.dump(data, file)
        self.repo = RentalBinaryRepository(self.file_path)

    def tearDown(self):
        if os.path.exists(self.file_path):
            os.remove(self.file_path)

    def test_find_by_id(self):
        rental = self.repo.find_by_id(1)
        self.assertEqual(rental._book_id, 101)
        self.assertIsNone(self.repo.find_by_id(99))

    def test_add_rental(self):
        today = datetime.now().date()
        new_rental = Rental(3, 103, 203, today, today + timedelta(days=2))
        self.repo.add(new_rental)
        self.assertEqual(self.repo.find_by_id(3)._book_id, 103)

    def test_remove_rental(self):
        self.repo.remove(1)
        self.assertIsNone(self.repo.find_by_id(1))

    def test_find_by_client(self):
        rentals = self.repo.find_by_client(201)
        self.assertEqual(len(rentals), 1)
        self.assertEqual(rentals[0]._id, 1)

    def test_find_active_rentals(self):
        today = datetime.now().date()
        active_rentals = self.repo.find_active_rentals()
        self.assertEqual(len(active_rentals), 1)
        self.assertEqual(active_rentals[0]._id, 1)


if __name__ == "__main__":
    unittest.main()
