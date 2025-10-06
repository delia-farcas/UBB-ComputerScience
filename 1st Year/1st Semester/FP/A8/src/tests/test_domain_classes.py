import unittest
from src.domain.book import Book, ValidatorBook
from src.domain.validator_exception import ValidatorException
from src.domain.client import Client, ClientValidator
from datetime import datetime, timedelta
from src.domain.rental import Rental, ValidatorRental

class TestBookAndValidator(unittest.TestCase):
    def setUp(self):
        self.validator = ValidatorBook()

    def test_book_creation(self):
        book = Book(1, "1984", "George Orwell")
        self.assertEqual(book.get_id, 1)
        self.assertEqual(book.get_title, "1984")
        self.assertEqual(book.get_author, "George Orwell")

    def test_book_str_representation(self):
        book = Book(1, "1984", "George Orwell")
        self.assertEqual(str(book), "Book ID: 1, title: 1984, author: George Orwell")

    def test_validate_valid_book(self):
        book = Book(1, "1984", "George Orwell")
        try:
            self.validator.validate_book(book)  # Should not raise exceptions
        except Exception as e:
            self.fail(f"Validator raised an exception unexpectedly: {e}")

    def test_validate_invalid_book(self):
        invalid_book = Book(-1, "", "")
        with self.assertRaises(ValidatorException) as context:
            self.validator.validate_book(invalid_book)
        self.assertIn("Id should be a positive number", str(context.exception))
        self.assertIn("Title invalid", str(context.exception))
        self.assertIn("Book should have an author", str(context.exception))



class TestClientAndValidator(unittest.TestCase):
    def setUp(self):
        self.validator = ClientValidator()

    def test_client_creation(self):
        client = Client(1, "John Doe")
        self.assertEqual(client.get_id, 1)
        self.assertEqual(client.get_name, "John Doe")

    def test_client_str_representation(self):
        client = Client(1, "John Doe")
        self.assertEqual(str(client), "Client ID: 1, name: John Doe")

    def test_validate_valid_client(self):
        client = Client(1, "John Doe")
        try:
            self.validator.validate_client(client)  # Should not raise exceptions
        except Exception as e:
            self.fail(f"Validator raised an exception unexpectedly: {e}")

    def test_validate_invalid_client(self):
        invalid_client = Client(-1, "")
        with self.assertRaises(ValueError) as context:
            self.validator.validate_client(invalid_client)
        self.assertIn("Id should be a positive number", str(context.exception))
        self.assertIn("Invalid name of the client", str(context.exception))




class TestRentalAndValidator(unittest.TestCase):
    def setUp(self):
        self.validator = ValidatorRental()
        self.today = datetime.now().date()
        self.tomorrow = self.today + timedelta(days=1)

    def test_rental_creation(self):
        rental = Rental(1, 101, 201, self.today, self.tomorrow)
        self.assertEqual(rental.get_id, 1)
        self.assertEqual(rental.get_book_id, 101)
        self.assertEqual(rental.get_client_id, 201)
        self.assertEqual(rental.get_rented_date, self.today)
        self.assertEqual(rental.get_returned_date, self.tomorrow)

    def test_rental_str_representation(self):
        rental = Rental(1, 101, 201, self.today, self.tomorrow)
        expected_str = f"Rental ID: 1, Book ID: 101, Client ID: 201, Rented Date: {self.today}, Returned Date: {self.tomorrow}"
        self.assertEqual(str(rental), expected_str)

    def test_rental_is_active(self):
        active_rental = Rental(1, 101, 201, self.today, self.tomorrow)
        self.assertTrue(active_rental.is_active())
        inactive_rental = Rental(2, 101, 201, self.today, self.today)
        self.assertFalse(inactive_rental.is_active())

    def test_validate_valid_rental(self):
        rental = Rental(1, 101, 201, self.today, self.tomorrow)
        try:
            self.validator.validate_rental(rental)  # Should not raise exceptions
        except Exception as e:
            self.fail(f"Validator raised an exception unexpectedly: {e}")

    def test_validate_invalid_rental(self):
        invalid_rental = Rental(1, 101, 201, self.today, self.today)  # Same day
        with self.assertRaises(ValidatorException) as context:
            self.validator.validate_rental(invalid_rental)
        self.assertIn("Rental must be at least 1 day.", str(context.exception))

    def test_validate_date_format_valid(self):
        valid_date = "2024-06-01"
        result = ValidatorRental.validate_date_format(valid_date)
        self.assertEqual(result, datetime.strptime(valid_date, "%Y-%m-%d"))

    def test_validate_date_format_invalid(self):
        invalid_date = "01/06/2024"  # Wrong format
        with self.assertRaises(ValueError) as context:
            ValidatorRental.validate_date_format(invalid_date)
        self.assertIn("Invalid date format for '01/06/2024'. Expected format: %Y-%m-%d", str(context.exception))
