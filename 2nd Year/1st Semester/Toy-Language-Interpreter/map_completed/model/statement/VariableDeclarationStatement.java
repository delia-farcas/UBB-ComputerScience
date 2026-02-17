
package org.example.map_completed.model.statement;

import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.Value;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.state.SymbolTable;

import java.util.Map;

public record VariableDeclarationStatement(Type type, String variableName) implements Statement {

    @Override
    public ProgramState execute(ProgramState state){
        SymbolTable<String, Value> symbolTable = state.getSymbolTable();
        symbolTable.put(variableName, type.getDefaultValue());
        return null;
    }
    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        typeEnv.put(variableName, type);
        return typeEnv;
    }

    @Override
    public String toString() {
        return type.toString() + " " + variableName;
    }

}
