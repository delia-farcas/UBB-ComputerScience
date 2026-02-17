package org.example.map_completed.model.statement;

import org.example.map_completed.model.state.*;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.StringValue;
import org.example.map_completed.model.value.Value;

import java.io.BufferedReader;
import java.util.Map;

public record ForkStatement(Statement statement) implements Statement{

    @Override
    public ProgramState execute(ProgramState state) {
        ExecutionStack<Statement> newES =  new LinkedListExecutionStack<>();
        SymbolTable<String, Value> newST = state.getSymbolTable().cloneTable();
        Out<Value> newO = state.getOut();
        Heap<Integer, Value> newH = state.getHeap();
        FileTable<StringValue, BufferedReader> newFT = state.getFileTable();

        newES.push(statement);
        return new ProgramState(newES, newST, newO, newFT, newH);
    }

    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        // 1. Creăm o copie a mediului de tipuri actual (pentru a nu-l altera pe cel original)
        // Presupunând că folosești HashMap, putem face o copie simplă:
        Map<String, Type> copyEnv = new java.util.HashMap<>(typeEnv);

        // 2. Apelăm typecheck pe instrucțiunea din fork folosind copia
        statement.typecheck(copyEnv);

        // 3. Returnăm mediul original (fork-ul nu schimbă tipurile variabilelor din main)
        return typeEnv;
    }

    @Override
    public String toString() {
        return "fork(" + statement.toString() + ")";
    }

}
