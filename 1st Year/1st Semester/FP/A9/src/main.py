
from services.book_service import BookService
from services.client_service import ClientService
from services.rental_service import RentalService
from services.statistics_service import StatisticsService
from services.undo_service import UndoService
from repository.MemoryRepository import BookRepository, ClientRepository, RentalRepository
from repository.BinaryRepository import BookBinaryRepository, ClientBinaryRepository, RentalBinaryRepository
from repository.TextFileRepository import BookTextFileRepository, ClientTextFileRepository, RentalTextFileRepository
from ui.ui import Ui

book_repo = BookRepository()
client_repo = ClientRepository()
rental_repo = RentalRepository()
undo_service = UndoService()
rental_service = RentalService(rental_repo, book_repo, client_repo, undo_service)
client_service = ClientService(client_repo, rental_repo, undo_service)
book_service = BookService(book_repo, rental_repo, undo_service)
statistics_service = StatisticsService(rental_repo, book_repo, client_repo)
book_service.generate_books()
client_service.generate_clients()
rental_service.generate_rentals()


ui = Ui(book_service, client_service, rental_service, statistics_service, undo_service)

ui.principal_menu()
