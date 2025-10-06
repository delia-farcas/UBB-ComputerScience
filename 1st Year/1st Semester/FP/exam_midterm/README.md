Objective
Implement a console application for managing sports teams and players. The system should allow adding teams, assigning players to teams, and persisting data to files.

Requirements
1. Team Management
Create a Team class with:

Unique ID (positive integer)

Name (non-empty string)

Implement team validation with custom exceptions

Store teams in a text file (teams.txt)

Provide functionality to:

Add new teams

Display all teams

2. Player Management
Create a Player (Jucator) class with:

Unique ID (positive integer)

Name (non-empty string)

Team ID (default 0 - unassigned)

Generate 10 random players using the Faker library

Allow assigning players to existing teams

Store players in memory (dictionary-based repository)

3. Repository Pattern
Implement separate repositories for teams and players

Teams should support both memory and text file storage

Players should use in-memory storage

Handle duplicate IDs and invalid operations with custom exceptions

4. Service Layer
Create service classes to handle business logic

Separate team operations from player operations

Validate data before processing

5. User Interface
Console-based menu with options:

Add a new team

Display all teams

Assign a player to a team

Handle user input errors gracefully

6. Testing
Write unit tests for the service layer

Test team addition functionality

Test team retrieval functionality

Use mocking to isolate dependencies
