from src.domain.client import Client, ClientValidator
from src.repository.TextFileRepository import ClientTextFileRepository
from src.repository.MemoryRepository import InMemoryRepository, ClientRepository, RentalRepository
from src.services.service_exception import ServiceException
from faker import Faker

class ClientService:
    def __init__(self, repository = ClientRepository(), rental_repo = RentalRepository(), validator = ClientValidator()):
        self._client_repo = repository
        self._rental_repo = rental_repo
        self._client_validator = validator
        self._faker = Faker()

    def add_client(self, client_id: int, client_name: str):
        """
        Adds a new client to the repository.
        """
        if self._client_repo.find_by_id(client_id) is not None:
            raise ServiceException(f"A client with ID {client_id} already exists.")
        

        client = Client(client_id, client_name)
        self._client_validator.validate_client(client)
        self._client_repo.add(client)
        print("Client added successfully!")

    def remove_client(self, client_id: int):
        """
        Removes a client from the repository by their ID.
        """
        client = self._client_repo.find_by_id(client_id)
        if client is None:
            raise ServiceException(f"No client found with ID {client_id}.")
        
        self._client_repo.remove(client_id)
        print("Client removed successfully!")

        try:
            rentals = self._rental_repo.find_by_client(client_id)
            for rent in rentals:
                self._rental_repo.remove(rent.get_id)
        except ServiceException:
            pass
        except TypeError:
            pass
        return client

    def update_client(self, client_id: int, new_name: str):
        """
        Updates an existing client's name.
        """
        client = self._client_repo.find_by_id(client_id)
        if client is None:
            raise ServiceException(f"No client found with ID {client_id}.")
        
        updated_client = Client(client_id, new_name)
        self._client_validator.validate_client(updated_client)
        self._client_repo.update(updated_client)
        print("Client updated successfully!")
    def find_by_id(self, client_id: int):
        """
        Finds and returns a client by their ID.
        """
        client = self._client_repo.find_by_id(client_id)
        if client is None:
            raise ServiceException(F"Client with ID {client_id} does not exist!")
        return client
    
    def find_by_name(self, name: str):
        """
        Searches for clients whose names contain the given string (case-insensitive, partial match).
        """
        clients = self._client_repo.find_by_name(name)
        if clients is None:
            raise ServiceException(f"Client with name {name} is not registered.")
        return clients
        

    def list_clients(self):
        """
        Lists all clients in the repository.
        """
        return self._client_repo.list_all()
    
    def generate_clients(self, count=20):
        """
        Generates random clients and adds them to the repository.
        :param count: The number of clients to generate (default is 20).
        """
        for _ in range(count):
            client_id = self._faker.unique.random_int(min=1, max=1000)
            name = self._faker.name()  # Generate a random name
            client = Client(client_id, name)
            self._client_validator.validate_client(client)
            self._client_repo.add(client)

    


