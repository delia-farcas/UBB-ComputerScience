import unittest
import os
from datetime import datetime, timedelta

from src.domain.book import Book
from src.domain.client import Client
from src.domain.rental import Rental
from src.repository.repository_exception import RepositoryException
from src.repository.MemoryRepository import BookTextFileRepository, ClientTextFileRepository, RentalTextFileRepository


class TestBookTextFileRepository(unittest.TestCase):
    def setUp(self):
        # Create a temporary file for testing
        self.file_path = "test_books.txt"
        with open(self.file_path, "wt") as f:
            f.write("1,1984,George Orwell\n2,Brave New World,Aldous Huxley\n")

        self.repo = BookTextFileRepository()
        self.repo._BookTextFileRepository__load = lambda: None  # Override file load
        self.repo._BookTextFileRepository__save = lambda: None  # Override file save
        self.repo._file_loaded = True

        # Load data into repository manually
        self.repo.add(Book(1, "1984", "George Orwell"))
        self.repo.add(Book(2, "Brave New World", "Aldous Huxley"))

    def tearDown(self):
        if os.path.exists(self.file_path):
            os.remove(self.file_path)

    def test_find_by_id(self):
        self.assertEqual(self.repo.find_by_id(1)._title, "1984")
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


class TestClientTextFileRepository(unittest.TestCase):
    def setUp(self):
        # Create a temporary file for testing
        self.file_path = "test_clients.txt"
        with open(self.file_path, "wt") as f:
            f.write("1,John Doe\n2,Jane Smith\n")

        self.repo = ClientTextFileRepository()
        self.repo._ClientTextFileRepository__load = lambda: None
        self.repo._ClientTextFileRepository__save = lambda: None
        self.repo._file_loaded = True

        self.repo.add(Client(1, "John Doe"))
        self.repo.add(Client(2, "Jane Smith"))

    def tearDown(self):
        if os.path.exists(self.file_path):
            os.remove(self.file_path)

    def test_find_by_id(self):
        self.assertEqual(self.repo.find_by_id(1)._name, "John Doe")
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


class TestRentalTextFileRepository(unittest.TestCase):
    def setUp(self):
        # Create a temporary file for testing
        self.file_path = "test_rentals.txt"
        today = datetime.now().date()
        tomorrow = today + timedelta(days=1)

        with open(self.file_path, "wt") as f:
            f.write(f"1,101,201,{today},{tomorrow}\n")
            f.write(f"2,102,202,{today},{today}\n")

        self.repo = RentalTextFileRepository()
        self.repo._RentalTextFileRepository__load = lambda: None
        self.repo._RentalTextFileRepository__save = lambda: None
        self.repo._file_loaded = True

        self.repo.add(Rental(1, 101, 201, today, tomorrow))
        self.repo.add(Rental(2, 102, 202, today, today))

    def tearDown(self):
        if os.path.exists(self.file_path):
            os.remove(self.file_path)

    def test_find_by_id(self):
        self.assertEqual(self.repo.find_by_id(1)._book_id, 101)
        self.assertIsNone(self.repo.find_by_id(99))

    def test_add_rental(self):
        new_rental = Rental(3, 103, 203, datetime.now().date(), datetime.now().date() + timedelta(days=3))
        self.repo.add(new_rental)
        self.assertEqual(self.repo.find_by_id(3)._book_id, 103)

    def test_remove_rental(self):
        self.repo.remove(1)
        self.assertIsNone(self.repo.find_by_id(1))

    def test_find_active_rentals(self):
        today = datetime.now().date()
        active_rentals = self.repo.find_active_rentals(101)
        self.assertEqual(len(active_rentals), 1)

    def test_find_by_client(self):
        rentals = self.repo.find_by_client(201)
        self.assertEqual(len(rentals), 1)
        self.assertEqual(rentals[0]._id, 1)


if __name__ == "__main__":
    unittest.main()
