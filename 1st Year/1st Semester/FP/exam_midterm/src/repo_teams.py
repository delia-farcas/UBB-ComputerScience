from team import Team

class TeamsMemoryRepo:
    def __init__(self):
        self._data ={}

    def add_team(self, team):
        if team._id in self._data:
            raise RepositoryException(f"Team with ID {team._id} already exists.")
        else:
            self._data[team._id] = team

    def get_all_teams(self):
        return list(self._data.values())
    


class TeamsTextRepo(TeamsMemoryRepo):
    def __init__(self):
        super().__init__()
        self._file_loaded = False

    def add_team(self, team):
        self.__load()
        super().add_team(team)
        self.__save()
    
    def get_all_teams(self):
        self.__load()
        return self._data

    def __load(self):
        if self._file_loaded:
            return
        self._file_loaded = True
        try:
            with open("teams.txt", "rt") as fin:
                line = fin.readline()
                line = line.strip()
                while len(line) > 0:
                    tokens = line.split(" ")
                    super().add_team(Team(int(tokens[0]), tokens[1]))
                    line = fin.readline()
                    line = line.strip()
        except FileNotFoundError:
            print("The file teams.txt was not found.")

    def __save(self):
        fout = open("teams.txt", "wt")
        for team in self._data.values():
            fout.write(str(team._id) + " " + team._name + '\n')
        fout.close()


class RepositoryException(Exception):
    pass
