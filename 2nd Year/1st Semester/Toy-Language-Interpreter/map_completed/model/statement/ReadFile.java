package org.example.map_completed.model.statement;

import org.example.map_completed.model.expression.Expression;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.state.FileTable;
import org.example.map_completed.model.type.IntType;
import org.example.map_completed.model.type.StringType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.StringValue;
import org.example.map_completed.model.value.IntValue;
import org.example.map_completed.model.value.Value;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Map;

public record ReadFile(Expression expr, String varName) implements Statement {

    @Override
    public ProgramState execute(ProgramState state) {
        SymbolTable<String, Value> sym = state.getSymbolTable();
        if (!sym.isDefined(varName))
            throw new RuntimeException("Variable not defined: " + varName);

        var varVal = sym.get(varName);
        if (!varVal.getType().equals(new IntType()))
            throw new RuntimeException("Variable is not integer");

        Value v = expr.evaluate(sym, state.getHeap());
        if (!(v instanceof StringValue sv))
            throw new RuntimeException("Expression not string");

        FileTable<StringValue, BufferedReader> ft = state.getFileTable();
        if (!ft.isDefined(sv))
            throw new RuntimeException("File not opened: " + sv.getVal());

        BufferedReader br = ft.get(sv);
        try {
            String line = br.readLine();
            int val = (line == null) ? 0 : Integer.parseInt(line);
            sym.put(varName, new IntValue(val));
        } catch (IOException e) {
            throw new RuntimeException("Error reading file");
        }
        return null;
    }

    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        Type expType = expr.typecheck(typeEnv);
        if (!expType.equals(new StringType()))
            throw new RuntimeException("ReadFile: expression is not string");

        if (!typeEnv.containsKey(varName))
            throw new RuntimeException("ReadFile: variable not declared: " + varName);

        if (!typeEnv.get(varName).equals(new IntType()))
            throw new RuntimeException("ReadFile: variable is not int");

        return typeEnv;
    }

    @Override
    public String toString() {
        return "readFile(" + expr.toString() + ", " + varName + ")";
    }
}
