package org.example.map_completed.model.statement;

import org.example.map_completed.model.expression.Expression;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.RefValue;
import org.example.map_completed.model.value.Value;
import org.example.map_completed.model.type.RefType;
import org.example.map_completed.model.state.Heap;

import java.util.Map;

public class WHStatement implements Statement {
    private final String varName;
    private final Expression expression;

    public WHStatement(String varName, Expression expression) {
        this.varName = varName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        SymbolTable<String, Value> symTable = state.getSymbolTable();
        Heap<Integer, Value> heap = state.getHeap();

        if (!symTable.isDefined(varName)) {
            throw new RuntimeException("wH: variable " + varName + " is not defined");
        }

        Value varValue = symTable.get(varName);

        if (!(varValue instanceof RefValue refVal)) {
            throw new RuntimeException("wH: variable " + varName + " is not a RefValue");
        }

        int address = refVal.getAddress();

        if (!heap.containsKey(address)) {
            throw new RuntimeException("wH: address " + address + " not found in heap");
        }


        Value exprValue = expression.evaluate(symTable, heap);

        if (!exprValue.getType().equals(refVal.getLocationType())) {
            throw new RuntimeException("wH: type mismatch. Variable expects "
                    + refVal.getType() + " but expression is " + exprValue.getType());
        }

        heap.put(address, exprValue);

        return null;
    }

    @Override
    public String toString() {
        return "wH(" + varName + ", " + expression + ")";
    }

    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        Type varType = typeEnv.get(varName);
        if (!(varType instanceof RefType))
            throw new RuntimeException("Variable not RefType");

        Type inner = ((RefType) varType).getInner();
        Type expType = expression.typecheck(typeEnv);

        if (!inner.equals(expType))
            throw new RuntimeException("Heap write type mismatch");

        return typeEnv;
    }
}
