from team import Team, ValidateTeam

class Service:
    def __init__(self, repo):
        self._repo = repo
        self._validator = ValidateTeam()
        

    def add_team(self, id, name):
        team = Team(id, name)
        self._repo.add_team(team)

    def print_all_teams(self):
        teams = self._repo.get_all_teams()
        return teams