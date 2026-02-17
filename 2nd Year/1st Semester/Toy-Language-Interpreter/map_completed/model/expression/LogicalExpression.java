package org.example.map_completed.model.expression;

import org.example.map_completed.model.state.Heap;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.type.BoolType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.BoolValue;
import org.example.map_completed.model.value.Value;

import java.util.Map;

public record LogicalExpression(Expression left, Expression right,  String operator) implements Expression {

    @Override
    public Value evaluate(SymbolTable<String, Value> symbolTable, Heap<Integer, Value> heap){
        Value leftValue = left.evaluate(symbolTable, heap);
        Value rightValue = right.evaluate(symbolTable, heap);
        if(!(leftValue instanceof BoolValue(boolean leftTerm))){
            throw new ArithmeticException("Left value is not a boolean value");
        }
        if(!(rightValue instanceof BoolValue(boolean rightTerm))){
            throw new ArithmeticException("Right value is not a boolean value");
        }

        return switch(operator){
            case "&&" -> new BoolValue(leftTerm && rightTerm);
            case "||" -> new BoolValue(leftTerm || rightTerm);
            default -> throw new ArithmeticException("Invalid operator");
        };
    }

    @Override
    public Type typecheck(Map<String, Type> typeEnv) {
        Type t1 = left.typecheck(typeEnv);
        Type t2 = right.typecheck(typeEnv);

        if (!t1.equals(new BoolType()))
            throw new RuntimeException("First operand is not boolean");
        if (!t2.equals(new BoolType()))
            throw new RuntimeException("Second operand is not boolean");

        return new BoolType();
    }
}
