from src.repository.repository_exception import RepositoryException

class RepositoryIterator():
    def __init__(self, data):
        self.__data = data
        self.__pos = -1

    def __next__(self):
        self.__pos += 1
        if len(self.__data) == self.__pos:
            # we have run out of elements in the data structure
            raise StopIteration()

        return self.__data[self.__pos]
    
class InMemoryRepository:
    def __init__(self):
          self._data = {}
    
    def add(self, entity):
        if entity._id in self._data:
            raise RepositoryException(f"Entity with ID {entity._id} already exists.")
        self._data[entity._id] = entity

    def remove(self, entity_id):
        if entity_id not in self._data:
            raise RepositoryException(f"Entity with ID {entity_id} does not exist.")
        del self._data[entity_id]

    def update(self, entity):
        if entity._id not in self._data:
            raise RepositoryException(f"Entity with ID {entity._id} does not exist.")
        self._data[entity._id] = entity
    
    def list_all(self):
        return list(self._data.values())
    
    def __iter__(self):
        return RepositoryIterator(list(self._data.values()))

    def __len__(self):
        return len(self._data)

    def __getitem__(self, item):
        if item not in self._data:
            return None
        return self._data[item]


class BookRepository(InMemoryRepository):
    
    def find_by_id(self, entity_id):
        if entity_id is not None:
            if entity_id not in self._data:
                return None
            return self._data[entity_id]
        
    def find_by_title(self, title):
        matches = []
        for book in self._data.values():  
            if title.lower() in book.get_title.lower():
                matches.append(book)
        if matches:
            return matches
        else:
            return None
            
    def find_by_author(self, author):
        matches = []
        for book in self._data.values():
            if author.lower() in book.get_author.lower():
                matches.append(book)
        if matches:
            return matches
        else:
            return None

class ClientRepository(InMemoryRepository):

    def find_by_id(self, entity_id):
        if entity_id is not None:
         if entity_id in self._data:
            return self._data[entity_id]
         return None
        
    def find_by_name(self, name):
        matches = []
        for client in self._data.values():  
            if name.lower() in client.get_name.lower():
                matches.append(client)
        if matches:
                return matches
        else:
                return None

class RentalRepository(InMemoryRepository,):

    def __init__(self):
        super().__init__()
       
    def find_by_id(self, entity_id):
        if entity_id in self._data:  
              return self._data[entity_id]
        return None
    def find_by_book(self, book_id):
        matches = []
        for rental in self._data.values():  
             if book_id == rental._book_id:
                matches.append(rental)
        if matches:
            return matches
        else:
            return None

    def find_by_client(self,client_id):
        matches = []
        for rental in self._data.values():  
            if client_id == rental._client_id:
                matches.append(rental)
        if matches:
            return matches
        else:
            return None
        
    def find_active_rentals(self, book_id = None):
        """
        Find all rentals that are currently active (not yet returned).
        Active rentals have a `returned_date` bigger than the date of today
        """
        matches = []
        for rental in self._data.values():
            if rental.is_active() and rental.get_book_id == book_id:
                matches.append(rental)
        if matches:
          return matches
        else:
          return None
        


        