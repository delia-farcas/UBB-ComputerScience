class Client:
    def __init__(self, client_id, name):
        self._id = client_id
        self._name = name

    @property
    def get_id(self):
        return self._id
    
    @property
    def get_name(self):
        return self._name
    
    def __str__(self):
        return f'Client ID: {self._id}, name: {self._name}'
    
    def __repr__(self):
        return str(self)
    
class ClientValidator:
    def validate_client(self, client):
        if not isinstance(client, Client):
            raise TypeError("This is not a client")
        _errors = []
        if client._id <= 0:
            _errors.append("Id should be a positive number")
        if len(client._name) == 0:
            _errors.append("Invalid name of the client")
        if _errors:
            raise ValueError(_errors)
        

