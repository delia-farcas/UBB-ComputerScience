from repo_teams import RepositoryException
from faker import Faker
from random import random
from player import Jucator

class PlayersMemoryRepository:
    def _init_(self):
          self._data = {}
    
    def add(self, entity):
        if entity._id in self._data:
            raise RepositoryException(f"Player with ID {entity._id} already exists.")
        self._data[entity._id] = entity

    def remove(self, entity_id):
        if entity_id not in self._data:
            raise RepositoryException(f"Player with ID {entity_id} does not exist.")
        del self._data[entity_id]

    def generate_players(self):
        fake = Faker()
        for i in range(1, 11):  # IDs start at 1
            name = fake.name()
            player = Jucator(id=i, name=name)
            self._data[id] = player
    
    def add_player_to_team(self, team):
        player = self._data[random.choice(self._data)]
        player.set_team(team)

    def _len_(self):
        return len(self._data)

    def _getitem_(self, item):
        if item not in self._data:
            return None
        return self._data[item]