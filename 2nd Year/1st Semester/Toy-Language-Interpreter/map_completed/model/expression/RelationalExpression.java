package org.example.map_completed.model.expression;

import org.example.map_completed.model.state.Heap;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.type.BoolType;
import org.example.map_completed.model.type.IntType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.Value;
import org.example.map_completed.model.value.IntValue;
import org.example.map_completed.model.value.BoolValue;

import java.util.Map;

public record RelationalExpression(Expression left, Expression right, String operator) implements Expression {

    @Override
    public Value evaluate(SymbolTable<String, Value> symbolTable, Heap<Integer, Value> heap) {
        Value leftValue = left.evaluate(symbolTable, heap);
        Value rightValue = right.evaluate(symbolTable, heap);

        /*
        if (!(leftValue instanceof IntValue(int leftTerm))) {
            throw new ArithmeticException("Left value is not an integer");
        }
        if (!(rightValue instanceof IntValue(int rightTerm))) {
            throw new ArithmeticException("Right value is not an integer");
        }
        */
        int leftTerm = ((IntValue) leftValue).value();
        int rightTerm = ((IntValue) rightValue).value();

        return switch (operator) {
            case "<"  -> new BoolValue(leftTerm < rightTerm);
            case "<=" -> new BoolValue(leftTerm <= rightTerm);
            case "==" -> new BoolValue(leftTerm == rightTerm);
            case "!=" -> new BoolValue(leftTerm != rightTerm);
            case ">"  -> new BoolValue(leftTerm > rightTerm);
            case ">=" -> new BoolValue(leftTerm >= rightTerm);
            default   -> throw new ArithmeticException("Invalid operator");
        };
    }

    @Override
    public Type typecheck(Map<String, Type> typeEnv) {
        Type t1 = left.typecheck(typeEnv);
        Type t2 = right.typecheck(typeEnv);

        if (!t1.equals(new IntType()) || !t2.equals(new IntType()))
            throw new RuntimeException("Relational operands must be int");

        return new BoolType();
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " " + operator + " " + right.toString() + ")";
    }
}