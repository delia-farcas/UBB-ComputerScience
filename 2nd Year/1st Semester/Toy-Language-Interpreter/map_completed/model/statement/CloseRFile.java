package org.example.map_completed.model.statement;

import org.example.map_completed.model.expression.Expression;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.state.FileTable;
import org.example.map_completed.model.type.StringType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.StringValue;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Map;

public record CloseRFile(Expression expr) implements Statement {

    @Override
    public ProgramState execute(ProgramState state) {
        SymbolTable<String, org.example.map_completed.model.value.Value> sym = state.getSymbolTable();
        var v = expr.evaluate(sym, state.getHeap());
        if (!(v instanceof StringValue sv))
            throw new RuntimeException("Expression not string");

        FileTable<StringValue, BufferedReader> ft = state.getFileTable();
        if (!ft.isDefined(sv))
            throw new RuntimeException("File not opened: " + sv.getVal());

        BufferedReader br = ft.get(sv);
        try {
            br.close();
            ft.remove(sv);
        } catch (IOException e) {
            throw new RuntimeException("Error closing file");
        }
        return null;
    }

    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        Type t = expr.typecheck(typeEnv);
        if (!t.equals(new StringType()))
            throw new RuntimeException("CloseRFile: expression is not string");
        return typeEnv;
    }

    @Override
    public String toString() {
        return "closeRFile(" + expr.toString() + ")";
    }
}
