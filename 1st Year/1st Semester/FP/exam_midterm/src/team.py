class Team:
    def __init__(self, id, name):
        self._id = id
        self._name = name

    @property
    def get_id(self):
        return
    
    def get_name(self):
        return self._name
    
    def __str__(self):
        return f'Team ID: {self._id}, team name: {self._name}'
    
    def __repr__(self):
        return str(self)
    
class ValidateTeam:

    def validate_team(self, team):
        _errors = []
        if not isinstance(team, Team):
            _errors.append("This is not a team")
        if team._id is not int:
            _errors.append("This is not a team")
        if team._id <= 0:
            _errors.append("Id should be a positive number")
        if len(team._name) == 0:
            _errors.append("Name invalid")
        if _errors:
            raise ValidatorException(_errors)

class ValidatorException(Exception):
    pass