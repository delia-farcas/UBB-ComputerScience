from repo_teams import TeamsMemoryRepo, RepositoryException, TeamsTextRepo
from service import Service
from team import ValidatorException
from player_service import PlayerService

class UI:
    def __init__(self, service):
        self._team_service = service
        self._player_service = PlayerService()

    def principal_menu(self):
        print("Welcome!!")
        while True:
            print("1. Add team\n"
                "2. Print all teams\n"
                "3.Add player to team")
            command = input("->")
            if command == "1":
                team = input("Insert id and name:")
                team = team.split(" ")
                try:
                    self._team_service.add_team(int(team[0]), team[1])
                except ValidatorException as ve:
                    print(ve)
                except RepositoryException as re:
                    print(re)
            elif command == "2":
                teams = self._team_service.print_all_teams()
                for team in teams:
                    print(team)
            elif command == "3":
                team = input("Choose team:")
                try:
                    self._player_service.add_player_team(int(team))
                except RepositoryException as re:
                    print(re)
        

teams_repo = TeamsTextRepo()
teams_srv = Service(teams_repo)
ui = UI(teams_srv)
ui.principal_menu()