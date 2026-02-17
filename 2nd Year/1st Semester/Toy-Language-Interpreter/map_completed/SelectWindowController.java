package org.example.map_completed;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
import org.example.map_completed.MainWindowController;
import org.example.map_completed.controller.Controller;
import org.example.map_completed.model.expression.*;
import org.example.map_completed.model.statement.*;
import org.example.map_completed.model.type.BoolType;
import org.example.map_completed.model.type.IntType;
import org.example.map_completed.model.type.RefType;
import org.example.map_completed.model.type.StringType;
import org.example.map_completed.model.value.BoolValue;
import org.example.map_completed.model.value.IntValue;
import org.example.map_completed.model.value.StringValue;
import org.example.map_completed.repository.ArrayListRepository;
import org.example.map_completed.repository.Repository;

public class SelectWindowController {
    @FXML private ListView<Statement> programsListView;

    @FXML
    public void initialize() {
        // int v; v=2; Print(v);
        Statement ex1 = new CompoundStatement(
                new VariableDeclarationStatement(new IntType(), "v"),
                new CompoundStatement(
                        new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))
                )
        );

        // int a; int b; a=2+3*5; b=a+1; Print(b)
        Statement ex2 =
                new CompoundStatement(
                        new VariableDeclarationStatement(new IntType(), "a"),
                        new CompoundStatement(
                                new VariableDeclarationStatement(new IntType(), "b"),
                                new CompoundStatement(
                                        new AssignmentStatement(
                                                "a",
                                                new ArithmeticExpression(
                                                        new ValueExpression(new IntValue(2)),
                                                        new ArithmeticExpression(
                                                                new ValueExpression(new IntValue(3)),
                                                                new ValueExpression(new IntValue(5)),
                                                                '*'
                                                        ),
                                                        '+'
                                                )
                                        ),
                                        new CompoundStatement(
                                                new AssignmentStatement(
                                                        "b",
                                                        new ArithmeticExpression(
                                                                new VariableExpression("a"),
                                                                new ValueExpression(new IntValue(1)),
                                                                '+'
                                                        )
                                                ),
                                                new PrintStatement(new VariableExpression("b"))
                                        )
                                )
                        )
                );

        // bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)
        Statement ex3 =
                new CompoundStatement(
                        new VariableDeclarationStatement(new BoolType(), "a"),
                        new CompoundStatement(
                                new VariableDeclarationStatement(new IntType(), "v"),
                                new CompoundStatement(
                                        new AssignmentStatement(
                                                "a",
                                                new ValueExpression(new BoolValue(true))
                                        ),
                                        new CompoundStatement(
                                                new IfStatement(
                                                        new VariableExpression("a"),
                                                        new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                                                        new AssignmentStatement("v", new ValueExpression(new IntValue(3)))
                                                ),
                                                new PrintStatement(new VariableExpression("v"))
                                        )
                                )
                        )
                );

        // int a; a = 5 / 0; Print(a); ERROR
        Statement ex4 =
                new CompoundStatement(
                        new VariableDeclarationStatement(new IntType(), "a"),
                        new CompoundStatement(
                                new AssignmentStatement(
                                        "a",
                                        new ArithmeticExpression(
                                                new ValueExpression(new IntValue(5)),
                                                new ValueExpression(new IntValue(0)),
                                                '/'
                                        )
                                ),
                                new PrintStatement(new VariableExpression("a"))
                        )
                );

        // bool flag; flag = 42; Print(flag); ERROR
        Statement ex5 =
                new CompoundStatement(
                        new VariableDeclarationStatement(new BoolType(), "flag"),
                        new CompoundStatement(
                                new AssignmentStatement(
                                        "flag",
                                        new ValueExpression(new IntValue(42))
                                ),
                                new PrintStatement(new VariableExpression("flag"))
                        )
                );

        // string str; int varc; str = "test.in"; openRFile(str); readFile(str,varc); print(varc); ...
        Statement ex6 =
                new CompoundStatement(
                        new VariableDeclarationStatement(new StringType(), "str"),
                        new CompoundStatement(
                                new AssignmentStatement("str", new ValueExpression(new StringValue("test.in"))),
                                new CompoundStatement(
                                        new OpenRFile(new VariableExpression("str")),
                                        new CompoundStatement(
                                                new VariableDeclarationStatement(new IntType(), "varc"),
                                                new CompoundStatement(
                                                        new ReadFile(new VariableExpression("str"), "varc"),
                                                        new CompoundStatement(
                                                                new PrintStatement(new VariableExpression("varc")),
                                                                new CompoundStatement(
                                                                        new ReadFile(new VariableExpression("str"), "varc"),
                                                                        new CompoundStatement(
                                                                                new PrintStatement(new VariableExpression("varc")),
                                                                                new CloseRFile(new VariableExpression("str"))
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                );

        Statement ex7 =
                new CompoundStatement(
                        new VariableDeclarationStatement(new IntType(), "a"),
                        new CompoundStatement(
                                new VariableDeclarationStatement(new IntType(), "b"),
                                new CompoundStatement(
                                        new AssignmentStatement(
                                                "a",
                                                new ArithmeticExpression(
                                                        new ValueExpression(new IntValue(2)),
                                                        new ArithmeticExpression(
                                                                new ValueExpression(new IntValue(3)),
                                                                new ValueExpression(new IntValue(5)),
                                                                '*'
                                                        ),
                                                        '+'
                                                )
                                        ),
                                        new CompoundStatement(
                                                new AssignmentStatement(
                                                        "b",
                                                        new ArithmeticExpression(
                                                                new VariableExpression("a"),
                                                                new ValueExpression(new IntValue(1)),
                                                                '+'
                                                        )
                                                ),
                                                new IfStatement(
                                                        new RelationalExpression(
                                                                new VariableExpression("b"),
                                                                new ValueExpression(new IntValue(10)),
                                                                ">"
                                                        ),
                                                        new PrintStatement(new VariableExpression("b")),
                                                        new PrintStatement(new ValueExpression(new IntValue(0)))
                                                )
                                        )
                                )
                        )
                );

        Statement ex8 =
                new CompoundStatement(
                        new VariableDeclarationStatement(new RefType(new IntType()), "v1"),
                        new CompoundStatement(
                                new HeapAllocation("v1", new ValueExpression(new IntValue(10))),
                                new CompoundStatement(
                                        new VariableDeclarationStatement(new RefType(new IntType()), "v2"),
                                        new CompoundStatement(
                                                new HeapAllocation("v2", new ValueExpression(new IntValue(20))),
                                                new CompoundStatement(
                                                        new VariableDeclarationStatement(new RefType(new RefType(new IntType())), "a"),
                                                        new CompoundStatement(
                                                                new HeapAllocation("a", new VariableExpression("v1")),
                                                                new CompoundStatement(
                                                                        new PrintStatement(new RHExpression(new VariableExpression("a"))),
                                                                        new CompoundStatement(
                                                                                new PrintStatement(new RHExpression(new VariableExpression("v1"))),
                                                                                new PrintStatement(new RHExpression(new VariableExpression("v2")))
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                );



        Statement ex9 =
                new CompoundStatement(
                        new VariableDeclarationStatement(new RefType(new IntType()), "v"),
                        new CompoundStatement(
                                new HeapAllocation("v", new ValueExpression(new IntValue(20))),  // new(v,20)
                                new CompoundStatement(
                                        new VariableDeclarationStatement(new RefType(new RefType(new IntType())), "a"),
                                        new CompoundStatement(
                                                new HeapAllocation("a", new VariableExpression("v")),      // new(a,v)
                                                new CompoundStatement(
                                                        // "Remove" v logically by shadowing it in a new scope with a dummy int variable
                                                        new VariableDeclarationStatement(new IntType(), "v"),
                                                        new PrintStatement(
                                                                new RHExpression(new RHExpression(new VariableExpression("a")))
                                                        )
                                                )
                                        )
                                )
                        )
                );



        Statement ex10 =
                new CompoundStatement(
                        new VariableDeclarationStatement(new IntType(), "v"),
                        new CompoundStatement(
                                new AssignmentStatement("v", new ValueExpression(new IntValue(4))),
                                new CompoundStatement(
                                        new WhileStatement(
                                                new RelationalExpression(new VariableExpression("v"), new ValueExpression(new IntValue(0)), ">"),
                                                new CompoundStatement(
                                                        new PrintStatement(new VariableExpression("v")),
                                                        new AssignmentStatement("v",
                                                                new ArithmeticExpression(new VariableExpression("v"), new ValueExpression(new IntValue(1)), '-')
                                                        )
                                                )
                                        ),
                                        new PrintStatement(new VariableExpression("v"))
                                )
                        )
                );

        // int a; int v; a=1; (If a Then v=0 Else v=1); Print(v)
        Statement ex11 =
                new CompoundStatement(
                        new VariableDeclarationStatement(new IntType(), "a"),
                        new CompoundStatement(
                                new VariableDeclarationStatement(new IntType(), "v"),
                                new CompoundStatement(
                                        new AssignmentStatement(
                                                "a",
                                                new ValueExpression(new IntValue(1))
                                        ),
                                        new CompoundStatement(
                                                new IfStatement(
                                                        new VariableExpression("a"),
                                                        new AssignmentStatement("v", new ValueExpression(new IntValue(0))),
                                                        new AssignmentStatement("v", new ValueExpression(new IntValue(1)))
                                                ),
                                                new PrintStatement(new VariableExpression("v"))
                                        )
                                )
                        )
                );

        Statement ex12 = new CompoundStatement(
                new VariableDeclarationStatement(new IntType(), "v"),
                new CompoundStatement(
                        new VariableDeclarationStatement(new RefType(new IntType()), "a"),
                        new CompoundStatement(
                                new AssignmentStatement("v", new ValueExpression(new IntValue(10))), // 2. INITIALIZARE
                                new CompoundStatement(
                                        new HeapAllocation("a", new ValueExpression(new IntValue(22))),
                                        new CompoundStatement(
                                                new ForkStatement( // 3. FORK (Acum v=10 este deja în SymTable și va fi clonat)
                                                        new CompoundStatement(
                                                                new WHStatement("a", new ValueExpression(new IntValue(30))),
                                                                new CompoundStatement(
                                                                        new AssignmentStatement("v", new ValueExpression(new IntValue(32))),
                                                                        new CompoundStatement(
                                                                                new PrintStatement(new VariableExpression("v")),
                                                                                new PrintStatement(new RHExpression(new VariableExpression("a")))
                                                                        )
                                                                )
                                                        )
                                                ),
                                                new CompoundStatement(
                                                        new PrintStatement(new VariableExpression("v")),
                                                        new PrintStatement(new RHExpression(new VariableExpression("a")))
                                                )
                                        )
                                )
                        )
                )
        );

        programsListView.setItems(FXCollections.observableArrayList(ex1, ex2, ex3, ex4, ex5, ex6, ex7, ex8, ex9, ex10, ex11, ex12));
        programsListView.setCellFactory(lv -> new ListCell<>() {
            @Override
            protected void updateItem(Statement item, boolean empty) {
                super.updateItem(item, empty);
                if (empty || item == null) {
                    setText(null);
                } else {
                    setText(item.toString());
                }
            }
        });

    }

    @FXML
    private void handleSelectProgram() {
        Statement selected = programsListView.getSelectionModel().getSelectedItem();
        if (selected == null) {
            new Alert(Alert.AlertType.ERROR, "Please select a program!").show();
            return;
        }

        try {

            Repository repo = new ArrayListRepository("src/main/java/org/example/map_completed/logs/log.txt");
            Controller controller = new Controller(repo);
            controller.addNewProgram(selected);

            FXMLLoader loader = new FXMLLoader(getClass().getResource("/org/example/map_completed/main-window.fxml"));
            Scene scene = new Scene(loader.load());

            MainWindowController mainCtrl = loader.getController();
            mainCtrl.setController(controller);

            Stage stage = new Stage();
            stage.setTitle("Interpreter Dashboard");
            stage.setScene(scene);
            stage.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
