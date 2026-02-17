package org.example.map_completed.model.statement;

import org.example.map_completed.model.expression.Expression;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.type.RefType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.RefValue;
import org.example.map_completed.model.value.Value;

import java.util.Map;

public record AssignmentStatement(String variableName, Expression expression) implements Statement {

    @Override
    public ProgramState execute(ProgramState state) {
        SymbolTable<String, Value> symTable = state.getSymbolTable();
        var heap = state.getHeap();

        if (!symTable.isDefined(variableName)) {
            throw new RuntimeException("Variable " + variableName + " not defined");
        }

        Value exprValue = expression.evaluate(symTable, heap);

        symTable.put(variableName, exprValue);

        return null;
    }

    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        if (!typeEnv.containsKey(variableName)) {
            throw new RuntimeException("Variable not declared: " + variableName);
        }
        Type varType = typeEnv.get(variableName);
        Type expType = expression.typecheck(typeEnv);

        if (!varType.equals(expType))
            throw new RuntimeException("Assignment type mismatch");

        return typeEnv;
    }

    @Override
    public String toString() {
        return variableName + " = " + expression.toString();
    }
}
