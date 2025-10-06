import unittest
from unittest.mock import MagicMock
from service import Service
from team import Team

class TestService(unittest.TestCase):
    def setUp(self):
        self.mock_repo = MagicMock()
        self.service = Service(self.mock_repo)

    def test_add_team(self):
        team_id = 1
        team_name = "Team A"
        team = Team(team_id, team_name)
        
        self.service.add_team(team_id, team_name)

        self.mock_repo.add_team.assert_called_once_with(team)

    def test_print_all_teams(self):
        expected_teams = [Team(1, "Team A"), Team(2, "Team B")]
        self.mock_repo.get_all_teams.return_value = expected_teams

        result = self.service.print_all_teams()

       
if __name__ == "__main__":
    unittest.main()