package org.example.map_completed.view;

import org.example.map_completed.controller.Controller;
import org.example.map_completed.model.expression.*;
import org.example.map_completed.repository.ArrayListRepository;
import org.example.map_completed.model.statement.*;
import org.example.map_completed.model.type.*;
import org.example.map_completed.model.value.*;
import org.example.map_completed.repository.Repository;

import java.util.Scanner;

public class Interpreter {
    static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("Enter log file path: ");
        String logFilePath = input.nextLine();

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
                                new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                                new CompoundStatement(
                                        new HeapAllocation("a", new ValueExpression(new IntValue(22))),
                                        new CompoundStatement(
                                                new ForkStatement(
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





        TextMenu textMenu = new TextMenu();
        textMenu.addCommand(new ExitCommand("0", "Exit"));
        textMenu.addCommand(new RunExample(
                "1",
                "int v; v=2;Print(v);",
                ex1,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "2",
                "int a;int b; a=2+3*5;b=a+1;Print(b)",
                ex2,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "3",
                "bool a; int v; a=true;(If a Then v=2 Else v=3);Print(v)",
                ex3,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "4",
                "int a; a = 5 / 0; Print(a);",
                ex4,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "5",
                "bool flag; flag = 42; Print(flag);",
                ex5,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "6",
                "string str; int varc; str = \"test.in\"; openRFile(str); readFile(str, varc); print(varc); readFile(str, varc); print(varc); closeRFile(str);",
                ex6,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "7",
                "int a; int b; a = 2+3*5; b = a+1; if (b>10) print(b);",
                ex7,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "8",
                "Ref int v1; new(v1,10); Ref int v2; new(v2,20); Ref Ref int a; new(a,v1); print(rH(a)); print(rH(v1)); print(rH(v2));",
                ex8,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "9",
                "Ref int v; new(v,20); Ref Ref int a; new(a,v); new(v,30); print(rH(rH(a)));",
                ex9,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "10",
                "int v; v = 4; while (v > 0) {print(v); v = v - 1;} print(v);",
                ex10,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "11",
                "int a; int v; a=1;(If a Then v=0 Else v=1);Print(v)",
                ex11,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.addCommand(new RunExample(
                "12",
                "int v; Ref int a; v=10; new(a,22); fork(wH(a,30); v=32; print(v); print(rH(a))); print(v); print(rH(a));",
                ex12,
                new Controller(new ArrayListRepository(logFilePath))
        ));

        textMenu.show();
    }

}