package org.example.map_completed.model.expression;

import org.example.map_completed.model.state.Heap;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.type.IntType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.IntValue;
import org.example.map_completed.model.value.Value;

import java.util.Map;

public record ArithmeticExpression(
        Expression left, Expression right, char operator)
        implements Expression {

    @Override
    public Value evaluate(SymbolTable<String, Value> symbolTable, Heap<Integer, Value> heap) {
        Value leftValue = left.evaluate(symbolTable, heap);
        Value rightValue = right.evaluate(symbolTable, heap);
        if (!(leftValue instanceof IntValue(int leftTerm))) {
            throw new ArithmeticException("Not an integer");
        }
        if (!(rightValue instanceof IntValue(int rightTerm))) {
            throw new ArithmeticException("Not an integer");
        }

        return switch (operator) {
            case '+' -> new IntValue(leftTerm + rightTerm);
            case '-' -> new IntValue(leftTerm - rightTerm);
            case '*' -> new IntValue(leftTerm * rightTerm);
            case '/' -> divide(leftTerm, rightTerm);
            default -> throw new ArithmeticException("Unknown operator");
        };
    }

    private static IntValue divide(int leftTerm, int rightTerm) {
        if (rightTerm == 0)
            throw new DivisionByZero();
        return new IntValue(leftTerm / rightTerm);
    }

    @Override
    public Type typecheck(Map<String, Type> typeEnv) {
        Type t1 = left.typecheck(typeEnv);
        Type t2 = right.typecheck(typeEnv);

        if (!t1.equals(new IntType()))
            throw new RuntimeException("First operand is not int");
        if (!t2.equals(new IntType()))
            throw new RuntimeException("Second operand is not int");

        return new IntType();
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " " + operator + " " + right.toString() + ")";
    }

}
