from player_repo import PlayersMemoryRepository
from repo_teams import TeamsTextRepo, RepositoryException

class PlayerService:
    def __init__(self):
        self._repo = PlayersMemoryRepository()
        self._team_repo = TeamsTextRepo()

    def create_players(self):
        self._repo.generate_players()

    def add_player_team(self, team):
        teams = self._team_repo.get_all_teams()
        print(teams)
        if team not in teams:
            raise RepositoryException("Team inexistent")
        self._repo.add_player_to_team(team)
    
    