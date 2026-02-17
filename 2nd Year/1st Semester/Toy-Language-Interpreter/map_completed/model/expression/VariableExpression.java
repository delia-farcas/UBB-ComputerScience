package org.example.map_completed.model.expression;
import org.example.map_completed.model.state.Heap;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.Value;

import java.util.Map;

public record VariableExpression(String varName) implements Expression{

    @Override
    public Value evaluate(SymbolTable<String, Value> symbolTable, Heap<Integer, Value> heap) {
        if (!symbolTable.isDefined(varName)) {
            throw new RuntimeException("Variable " + varName + " not defined");

        }
        return (Value) symbolTable.get(varName);
    }

    @Override
    public Type typecheck(Map<String, Type> typeEnv) {
        if (!typeEnv.containsKey(varName))
            throw new RuntimeException("Variable not declared: " + varName);
        return typeEnv.get(varName);
    }

    @Override
    public String toString() {
        return varName;
    }
}
