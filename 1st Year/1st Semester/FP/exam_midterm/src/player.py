from team import ValidatorException

class Jucator:
    def __init__(self, id, name):
        self._id = id
        self._name = name
        self._id_team = 0

    @property
    def get_id(self):
        return self._id
    
    @property
    def get_name(self):
        return self._name
    
    @property
    def get_id(self):
        return self._id_team
    
    def set_team(self, team):
        self._id_team = team
    
    def __str__(self):
        return f'Player ID: {self._id}, name: {self._name}, team: {self._id_team}'
    
    def __repr__(self):
        return str(self)
    

class ValidatorJucator:
    @staticmethod
    def validate_jucator(self, player):
        _errors = []
        if not isinstance(player, Jucator):
            _errors.append("This is not a player")
        if player._id <= 0:
            _errors.append("Id should be a positive number")
        if len(player._name) == 0:
            _errors.append("Name invalid")
        if _errors:
            raise ValidatorException(_errors)
        