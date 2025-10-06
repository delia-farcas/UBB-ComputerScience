import unittest
from datetime import datetime, timedelta

from src.domain.book import Book
from src.domain.client import Client
from src.domain.rental import Rental
from src.repository.repository_exception import RepositoryException
from src.repository.MemoryRepository import InMemoryRepository, BookRepository, ClientRepository, RentalRepository


class TestInMemoryRepository(unittest.TestCase):
    def setUp(self):
        self.repo = InMemoryRepository()
        self.book1 = Book(1, "1984", "George Orwell")
        self.book2 = Book(2, "Brave New World", "Aldous Huxley")

    def test_add_entity(self):
        self.repo.add(self.book1)
        self.assertEqual(len(self.repo), 1)
        self.assertIn(self.book1, self.repo.list_all())

    def test_add_existing_entity_raises_exception(self):
        self.repo.add(self.book1)
        with self.assertRaises(RepositoryException):
            self.repo.add(self.book1)

    def test_remove_entity(self):
        self.repo.add(self.book1)
        self.repo.remove(1)
        self.assertEqual(len(self.repo), 0)

    def test_remove_nonexistent_entity_raises_exception(self):
        with self.assertRaises(RepositoryException):
            self.repo.remove(1)

    def test_update_entity(self):
        self.repo.add(self.book1)
        updated_book = Book(1, "Animal Farm", "George Orwell")
        self.repo.update(updated_book)
        self.assertEqual(self.repo[1].get_title, "Animal Farm")

    def test_update_nonexistent_entity_raises_exception(self):
        with self.assertRaises(RepositoryException):
            self.repo.update(self.book1)

    def test_list_all(self):
        self.repo.add(self.book1)
        self.repo.add(self.book2)
        self.assertEqual(self.repo.list_all(), [self.book1, self.book2])

    def test_repository_iterator(self):
        self.repo.add(self.book1)
        self.repo.add(self.book2)
        items = [book for book in self.repo]
        self.assertEqual(items, [self.book1, self.book2])


class TestBookRepository(unittest.TestCase):
    def setUp(self):
        self.repo = BookRepository()
        self.book1 = Book(1, "1984", "George Orwell")
        self.book2 = Book(2, "Brave New World", "Aldous Huxley")
        self.repo.add(self.book1)
        self.repo.add(self.book2)

    def test_find_by_id(self):
        self.assertEqual(self.repo.find_by_id(1), self.book1)
        self.assertIsNone(self.repo.find_by_id(99))

    def test_find_by_title(self):
        self.assertEqual(self.repo.find_by_title("1984"), [self.book1])
        self.assertIsNone(self.repo.find_by_title("Nonexistent Title"))

    def test_find_by_author(self):
        self.assertEqual(self.repo.find_by_author("George Orwell"), [self.book1])
        self.assertIsNone(self.repo.find_by_author("Unknown Author"))


class TestClientRepository(unittest.TestCase):
    def setUp(self):
        self.repo = ClientRepository()
        self.client1 = Client(1, "John Doe")
        self.client2 = Client(2, "Jane Smith")
        self.repo.add(self.client1)
        self.repo.add(self.client2)

    def test_find_by_id(self):
        self.assertEqual(self.repo.find_by_id(1), self.client1)
        self.assertIsNone(self.repo.find_by_id(99))

    def test_find_by_name(self):
        self.assertEqual(self.repo.find_by_name("John"), [self.client1])
        self.assertIsNone(self.repo.find_by_name("Unknown Name"))


class TestRentalRepository(unittest.TestCase):
    def setUp(self):
        self.repo = RentalRepository()
        self.today = datetime.now().date()
        self.tomorrow = self.today + timedelta(days=1)
        self.rental1 = Rental(1, 101, 201, self.today, self.tomorrow)
        self.rental2 = Rental(2, 102, 202, self.today, self.today)  # Returned immediately
        self.repo.add(self.rental1)
        self.repo.add(self.rental2)

    def test_find_by_id(self):
        self.assertEqual(self.repo.find_by_id(1), self.rental1)
        self.assertIsNone(self.repo.find_by_id(99))

    def test_find_by_book(self):
        self.assertEqual(self.repo.find_by_book(101), [self.rental1])
        self.assertIsNone(self.repo.find_by_book(999))

    def test_find_by_client(self):
        self.assertEqual(self.repo.find_by_client(201), [self.rental1])
        self.assertIsNone(self.repo.find_by_client(999))

    def test_find_active_rentals(self):
        active_rentals = self.repo.find_active_rentals(101)
        self.assertEqual(active_rentals, [self.rental1])

        inactive_rentals = self.repo.find_active_rentals(102)
        self.assertIsNone(inactive_rentals)

    def test_find_active_rentals_without_book_id(self):
        active_rentals = self.repo.find_active_rentals()
        self.assertEqual(active_rentals, [self.rental1])

    def test_add_rental(self):
        new_rental = Rental(3, 103, 203, self.today, self.tomorrow)
        self.repo.add(new_rental)
        self.assertEqual(len(self.repo), 3)

    def test_remove_rental(self):
        self.repo.remove(1)
        self.assertEqual(len(self.repo), 1)


if __name__ == "__main__":
    unittest.main()
