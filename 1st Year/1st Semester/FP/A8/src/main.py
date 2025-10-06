from src.services.book_service import BookService
from src.services.client_service import ClientService
from src.services.rental_service import RentalService
from src.repository.MemoryRepository import BookRepository, ClientRepository, RentalRepository
from src.repository.BinaryRepository import BookBinaryRepository, ClientBinaryRepository, RentalBinaryRepository
from src.repository.TextFileRepository import BookTextFileRepository, ClientTextFileRepository, RentalTextFileRepository
from src.ui.ui import Ui

book_repo = BookTextFileRepository()
client_repo = ClientTextFileRepository()
rental_repo = RentalTextFileRepository()
rental_service = RentalService(rental_repo, book_repo, client_repo)
client_service = ClientService(client_repo, rental_repo)
book_service = BookService(book_repo, rental_repo)
book_service.generate_books()
client_service.generate_clients()
rental_service.generate_rentals()


ui = Ui(book_service, client_service, rental_service)

ui.principal_menu()
