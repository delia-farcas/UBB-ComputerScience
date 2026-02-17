package org.example.map_completed.model.expression;

import org.example.map_completed.model.state.Heap;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.Value;

import java.util.Map;

public record ValueExpression(Value value) implements Expression{
    @Override
    public Value evaluate(SymbolTable<String, Value> symbolTable, Heap<Integer, Value> heap){
        return value;
    }

    @Override
    public Type typecheck(Map<String, Type> typeEnv) {
        return value.getType();
    }

    @Override
    public String toString(){
        return value.toString();
    }
}
