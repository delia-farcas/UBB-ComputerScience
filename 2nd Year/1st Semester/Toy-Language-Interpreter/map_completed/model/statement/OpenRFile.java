package org.example.map_completed.model.statement;

import org.example.map_completed.model.expression.Expression;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.state.FileTable;
import org.example.map_completed.model.type.StringType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.StringValue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Map;

public record OpenRFile(Expression expr) implements Statement {

    @Override
    public ProgramState execute(ProgramState state) {
        SymbolTable<String, org.example.map_completed.model.value.Value> sym = state.getSymbolTable();
        var v = expr.evaluate(sym, state.getHeap());

        if (!(v instanceof StringValue sv))
            throw new RuntimeException("Expression does not evaluate to string");

        FileTable<StringValue, BufferedReader> ft = state.getFileTable();
        if (ft.isDefined(sv))
            throw new RuntimeException("File already opened: " + sv);

        try {
            BufferedReader br = new BufferedReader(new FileReader(sv.getVal()));
            ft.put(sv, br);
        } catch (IOException e) {
            throw new RuntimeException("Could not open file: " + sv.getVal());
        }
        return null;
    }

    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        Type t = expr.typecheck(typeEnv);
        if (!t.equals(new StringType()))
            throw new RuntimeException("OpenRFile: expression is not string");
        return typeEnv;
    }

    @Override
    public String toString() {
        return "openRFile(" + expr.toString() + ")";
    }
}
