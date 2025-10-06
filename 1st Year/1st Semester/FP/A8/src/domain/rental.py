from datetime import datetime
from src.domain.validator_exception import ValidatorException
class Rental:
    def __init__(self, rental_id, book_id, client_id, rented_date, returned_date):
        self._id = rental_id
        self._book_id = book_id
        self._client_id = client_id
        self._rented_date = rented_date
        self._returned_date = returned_date

    def is_active(self):
        """
        Checks if the rental is currently active.
        A rental is considered active if its return date is in the future.
        """
        now = datetime.now().date()  # Get the current date
        return self._returned_date > now  # Compare dates

    
    @property
    def get_id(self):
        return self._id
        
    @property
    def get_book_id(self):
        return self._book_id
            
    @property
    def get_client_id(self):
        return self._client_id
        
    @property
    def get_rented_date(self):
        return self._rented_date
        
    @property
    def get_returned_date(self):
        return self._returned_date
        
    def __str__(self):
        return f'Rental ID: {self._id}, Book ID: {self._book_id}, Client ID: {self._client_id}, Rented Date: {self._rented_date}, Returned Date: {self._returned_date}'
    
    def __repr__(self):
        return self.__str__()
    
class ValidatorRental:

    def validate_rental(self, rental):
        _errors = []
        if not isinstance(rental, Rental):
            raise TypeError("This is not a rental")
        
        rental._rented_date = rental._rented_date.date() if isinstance(rental._rented_date, datetime) else rental._rented_date
        rental._returned_date = rental._returned_date.date() if isinstance(rental._returned_date, datetime) else rental._returned_date

        if (rental._returned_date - rental._rented_date).days < 1:
            _errors.append("Rental must be at least 1 day.")
        
        if _errors:
            raise ValidatorException(_errors)
    @staticmethod    
    def validate_date_format(date_string: str, date_format: str = "%Y-%m-%d"):
        """
        Validates that a date string matches the given format.
        :param date_string: The date string to validate.
        :param date_format: The expected format of the date (default: "%Y-%m-%d").
        :return: A datetime object if the date is valid.
        :raises ValueError: If the date string does not match the format.
        """
        try:
            # Attempt to parse the date
            return datetime.strptime(date_string, date_format)
        except ValueError:
            # Raise an error if the date format is invalid
            raise ValueError(f"Invalid date format for '{date_string}'. Expected format: {date_format}")
