from src.domain.rental import Rental, ValidatorRental
from src.repository.TextFileRepository import RentalTextFileRepository
from src.repository.MemoryRepository import InMemoryRepository, RentalRepository, BookRepository, ClientRepository
from src.services.service_exception import ServiceException
from datetime import datetime, timedelta
from src.services.undo_service import FunctionCall, Operation, CascadedOperation, UndoService
from faker import Faker


class RentalService:
    def __init__(self, rental_repo = RentalRepository(), book_repo = BookRepository(), client_repo = ClientRepository(), undo_service = UndoService(), validator = ValidatorRental()):
        self._rental_repo = rental_repo
        self._book_repo = book_repo
        self._client_repo = client_repo
        self._validator_rental = validator
        self._faker = Faker() 
        self._undo_service = undo_service

    def add_rental(self, book_id: int, client_id: int, rented_date: str, returned_date: str):
        """
        Adds a rental to the repository. Checks if the book exists and is already rented before adding.
        """
        #Create an unique ID
        rental_id = self._faker.unique.random_int(min=1, max=1000)
        #Check if the book is in the library
        if self._book_repo.find_by_id(book_id) is None:
            raise ServiceException(f"The book with ID {book_id} does not exist.")
        #Check if the client exists
        if self._client_repo.find_by_id(client_id) is None:
            raise ServiceException(f"The client with ID {client_id} is not registered.")
        # Check if the book is already rented
        if self._rental_repo.find_active_rentals(book_id) is not None:
            raise ServiceException(f"The book with ID {book_id} is already rented.")
        try:
            self._validator_rental.validate_date_format(rented_date)
        except ValueError as ve:
            raise ServiceException(str(ve))
        try:
            self._validator_rental.validate_date_format(rented_date)
        except ValueError as ve:
            raise ServiceException(str(ve))
 
        # Convert rented and returned dates to datetime objects
        rented_date = datetime.strptime(rented_date, "%Y-%m-%d")
        returned_date = datetime.strptime(returned_date, "%Y-%m-%d")

        rental = Rental(rental_id, book_id, client_id, rented_date, returned_date)
        self._validator_rental.validate_rental(rental)
        self._rental_repo.add(rental)
        print(f"Rental with ID {rental_id} added successfully.")

        # Record the undo/redo operation
        undo = FunctionCall(self._rental_repo.remove, rental_id)
        redo = FunctionCall(self._rental_repo.add, rental)
        operation = Operation(undo, redo)
        self._undo_service.record(operation)

    def update_returned_date(self, rental_id: int):
        """
        Updates the returned date of a rental.
        """
        old_rental = self._rental_repo.find_by_id(rental_id)
        rental = self._rental_repo.find_by_id(rental_id)
        if rental is None:
            raise ServiceException(f"Rental with ID {rental_id} not found.")
        
        # Convert the new returned date to a datetime object
        returned_date = datetime.today()
        
        # Update the rental's returned date
        rental._returned_date = returned_date
        self._rental_repo.update(rental)
        print(f"Rental with ID {rental_id} updated successfully with the returned date of {returned_date}")

        # Record the undo/redo operation
        undo = FunctionCall(self._rental_repo.update, old_rental)
        redo = FunctionCall(self._book_repo.update, rental)
        operation = Operation(undo, redo)
        self._undo_service.record(operation)

    def remove_rental(self, rental_id: int):
        """
        Removes a rental from the repository.
        """
        rental = self._rental_repo.find_by_id(rental_id)
        if rental is None:
            raise ServiceException(f"Rental with ID {rental_id} not found.")
        
        self._rental_repo.remove(rental_id)
        print(f"Rental with ID {rental_id} removed successfully.")

        # Record the undo/redo operation
        undo = FunctionCall(self._rental_repo.add, rental)
        redo = FunctionCall(self._rental_repo.remove, rental_id)
        operation = Operation(undo, redo)
        self._undo_service.record(operation)

        
    def find_rental_by_book(self, book_id: int):
        """
        Finds an active rental by book ID.
        """
        rentals = self._rental_repo.find_by_book(book_id)
        if rentals is None:
            raise ServiceException(f"No active rentals found for book with ID {book_id}.")
        return rentals

    def find_rental_by_client(self, client_id: int):
        """
        Finds rentals by client ID.
        """
        rentals = self._rental_repo.find_by_client(client_id)
        if not rentals:
            raise ServiceException(f"No rentals found for client with ID {client_id}.")
        return rentals

    def list_rentals(self):
        """
        Lists all rentals in the repository.
        """
        return self._rental_repo.list_all()
    
    def generate_rentals(self, count=20):
        """
        Generates random rentals and adds them to the repository.
        :param count: The number of rentals to generate (default is 20).
        """

        for _ in range(count):
            # Generate random IDs for rental, book, and client
            rental_id = self._faker.unique.random_int(min=1, max=1000)

            book_id = self._faker.random_int(min=1, max=100)
            while self._book_repo.find_by_id(book_id) is None:
                book_id = self._faker.random_int(min=1, max=100)

            client_id = self._faker.random_int(min=1, max=100)
            while self._client_repo.find_by_id(client_id) is None:
                client_id = self._faker.random_int(min=1, max=100)

            # Generate a valid rented and returned date
            rented_date = self._faker.date_this_year()
            returned_date = rented_date + timedelta(days=self._faker.random_int(min=2, max=30))

            # Create the rental object
            rental = Rental(rental_id, book_id, client_id, rented_date, returned_date)

            # Add and validate the rental

            self._validator_rental.validate_rental(rental)
            self._rental_repo.add(rental)

                