from src.domain.validator_exception import ValidatorException
from src.repository.repository_exception import RepositoryException
from src.services.service_exception import ServiceException
from src.services.undo_service import UndoRedoError
from src.repository.TextFileRepository import BookTextFileRepository, ClientTextFileRepository, RentalRepository

class Ui:
    def __init__(self, book_service, client_service, rental_service, statistiscs_service, undo_service):
        self.__client_service = client_service
        self.__book_service = book_service
        self.__rental_service = rental_service
        self.__statistics_service = statistiscs_service
        self.__undo_service = undo_service

    def principal_menu(self):
        print("Hello! Welcome to the coolest library in town!")
        while True:
            print('Choose an option:\n'
                '1. Manage books\n'
                '2. Manage clients\n'
                '3. Rent or return a book\n'
                '4. Search for book\n'
                '5. Search for client\n'
                '6. Undo last operation\n'
                '7. Redo last operation\n'
                '8. Show statistics\n'
                '9. Exit')
            command = input("Your option is:")
            if command == "1":
                self.manage_books()
            elif command == "2":
                self.manage_clients()
            elif command == "3":
                self.rent_or_return()
            elif command == "4":
                self.search_book()
            elif command == "5":
                self.search_client()
            elif command == "6":
                self.undo_last()
            elif command == "7":
                self.redo_last()
            elif command == "8":
                self.do_statistics()
            elif command == "9":
                return
            else:
                print("Invalid command")

    def manage_books(self):
        while True:
            print('Press 1 to add a book.\n'
                  'Press 2 to remove a book.\n'
                  'Press 3 to update a book. \n'
                  'Press 4 to list all books.\n'
                  'Press 5 to go back to main menu.\n')

            option = input('Your option is: ')

            if option == '1':
                self.book_option_1()

            elif option == '2':
                self.book_option_2()

            elif option == '3':
                self.book_option_3()

            elif option == '4':
                self.book_option_4()

            elif option == '5':
                break

            else:
                print('Invalid option!')

    def book_option_1(self):
        while True:
            book_id = input('Enter book ID: ')
            try:
                book_id = int(book_id)
                break
            except ValueError:
                print('ID must be a positive integer!')
        title = input('Enter book title: ')
        author = input('Enter book author: ')
        try:
            self.__book_service.add_book(book_id, title, author)
        except ValidatorException as ve:
            print(ve)
        except RepositoryException as re:
           print(re)

    def book_option_2(self):
        while True:
            book_id = input("Enter book id:")
            try:
                book_id = int(book_id)
                break
            except ValueError:
                print("ID must be a positive integer!")
        try:
            self.__book_service.remove_book(book_id)
        except RepositoryException as re:
            print(re)
        except ServiceException as se:
            print(se)

    def book_option_3(self):
        while True:
            book_id = input("Enter book id:")
            try:
                book_id = int(book_id)
                break
            except ValueError:
                print("ID must be a positive integer!")
        try:
            self.__book_service.find_by_id(book_id)
        except ServiceException as se:
            print(se)
        new_title = input("Enter new title:")
        new_author = input("Enter new author:")
        try:
            self.__book_service.update_book(book_id, new_title, new_author)
        except RepositoryException as re:
            print(re)

    def book_option_4(self):
        list = self.__book_service.list_books()
        for book in list:
            print(book)

    def manage_clients(self):
         while True:
            print('Press 1 to add a client.\n'
                  'Press 2 to remove a client.\n'
                  'Press 3 to update a client.\n'
                  'Press 4 to list all clients.\n'
                  'Press 5 to go back to main menu.\n')

            option = input('Your option: ')

            if option == '1':
                self.client_option_1()

            elif option == '2':
                self.client_option_2()

            elif option == '3':
                self.client_option_3()

            elif option == '4':
                self.client_option_4()

            elif option == '5':
                break

            else:
                print('Invalid command!')

    def client_option_1(self):
        while True:
             client_id = input('Enter client ID: ')
             try:
                 client_id = int(client_id)
                 break
             except ValueError:
                 print('ID must be an integer!')
        client_name = input('Enter client name: ')
        try:
            self.__client_service.add_client(client_id, client_name)
        except ValidatorException as ve:
            print(ve)
        except RepositoryException as re:
            print(re)

    def client_option_2(self):
        while True:
            client_id = input('Enter client ID: ')
            try:
                client_id = int(client_id)
                break
            except ValueError:
                print('Client ID must be an integer!')
        try:
            self.__client_service.remove_client(client_id)
        except RepositoryException as re:
            print(re)
        except ServiceException as se:
            print(se)

    def client_option_3(self):
        while True:
            client_id = input('Enter client id to update: ')
            try:
                client_id = int(client_id)
                break
            except ValueError:
                print('Client ID must be an integer!')
        client_name = input('Enter new client name: ')
        try:
            self.__client_service.update_client(client_id, client_name)
        except ValidatorException as ve:
            print(ve)
        except ServiceException as se:
            print(se)
        except RepositoryException as re:
            print(re)

    def client_option_4(self):
        list = self.__client_service.list_clients()
        for client in list:
            print(client)


    def rent_or_return(self):
        while True:
            print("Press 1 to rent a book")
            print("Press 2 to return a book")
            print("Press 3 to go back to main menu")
            command = input("Your option:")
            if command == "1":
                self.rent_book()
            elif command == "2":
                self.return_book()
            elif command == "3":
                break
            else:
                print("Invalid input")

    def rent_book(self):
        while True:
            book_id = input("Enter book ID:")
            try:
                book_id = int(book_id)
                break
            except ValueError:
                print("Book ID must be an integer.")
        while True:
            client_id = input("Enter client ID:")
            try:
                client_id = int(client_id)
                break
            except ValueError:
                print("Client ID must be an integer.")
        rented_date = input("Enter the date of the rent: YYYY-MM-DD")
        returned_date = input("Enter the due date:YYYY-MM-DD")
        try:
            self.__rental_service.add_rental(book_id, client_id, rented_date, returned_date)
        except ServiceException as re:
            print (re)

    def return_book(self):
        rental_id = input("Enter rental ID:")
        try:
            rental_id = int(rental_id)
        except ValueError:
            print("Rental ID must be an integer.")
        
        try:
            self.__rental_service.update_returned_date(rental_id)
        except ServiceException as re:
            print (re)

    def search_book(self):
        while True:
            print('Press 1 to search by id\n'
                'Press 2 to search by title\n'
                'Press 3 to search by author\n'
                'Press 4 to go back to main menu')
            command = input("Your option:")

            if command == "1":
                self.search_book_id()
            elif command == "2":
                self.search_book_title()
            elif command == "3":
                self.search_book_author()
            elif command == "4":
                break
            else:
                print("Invalid input.")

    def search_book_id(self):
        while True:
            id = input("Please introduce the ID of the book:")
            try:
                id = int(id)
                break
            except ValueError:
                print("ID must pe a positive integer")
        try:
            print(self.__book_service.find_by_id(id))
        except ServiceException as se:
            print(se)

    def search_book_title(self):
        title = input("Please introduce the name of the book:")
        try:
            books = self.__book_service.find_by_title(title)
            for book in books:
                print(book)
        except ServiceException as se:
            print(se)

    def search_book_author(self):
        author = input("Please introduce the name of the author:")
        try:
            books = self.__book_service.find_by_author(author)
            for book in books:
                print(book)
        except ServiceException as se:
            print(se)

    def search_client(self):
        while True:
            print('Press 1 to search by id\n'
                'Press 2 to search by name\n'
                'Press 3 to go back to main menu')
            command = input("Your option:")
            if command == "1":
                self.search_client_id()
            elif command == "2":
                self.search_client_name()
            elif command == "3":
                break
            else:
                print("Invalid input.")
                
    def search_client_id(self):
        while True:
            id = input("Please introduce the ID of the client:")
            try:
                id = int(id)
                break
            except ValueError:
                print("ID must pe a positive integer")
        try:
                print(self.__client_service.find_by_id(id))
        except ServiceException as se:
                print (se)

    def search_client_name(self):
        title = input("Please introduce the name of the client:")
        try:
            clients = self.__client_service.find_by_name(title)
            for client in clients:
                print(client)
        except ServiceException as se:
            print(se)

    def undo_last(self):
        try:
            self.__undo_service.undo()
            print("Last operation undone successfully!")
        except UndoRedoError as ue:
            print(ue)

    def redo_last(self):
        try:
         self.__undo_service.redo()
         print("Last operation redone successfully!!")
        except UndoRedoError as ue:
            print(ue)
        pass

    def do_statistics(self):
        while True:
            print('Press 1 to list most rented books\n'
                'Press 2 to list most active clients\n'
                'Press 3 to list most rented authors\n'
                'Press 4 to go back to main menu')
            command = input("Your option:")
            if command == "1":
                self.most_rented_books()
            elif command == "2":
                self.most_active_clients()
            elif command == "3":
                self.most_rented_authors()
            elif command == "4":
                break
            else:
                print("Invalid input.")

    def most_rented_books(self):
        sorted_books = self.__statistics_service.most_rented_books()
        for book, count in sorted_books:
            print(book + ", rented " + str(count) + " times")

    def most_active_clients(self):
        sorted_clients = self.__statistics_service.most_active_clients()
        for client, count in sorted_clients:
            print(client + ", with " + str(count) + " rental days")

    def most_rented_authors(self):
        sorted_authors = self.__statistics_service.most_rented_authors()
        for author, count in sorted_authors:
            print(author + ", with " + str(count) + " rents")





        