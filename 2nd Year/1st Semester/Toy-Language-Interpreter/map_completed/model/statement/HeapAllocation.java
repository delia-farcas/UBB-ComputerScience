package org.example.map_completed.model.statement;

import org.example.map_completed.model.expression.Expression;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.type.RefType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.RefValue;
import org.example.map_completed.model.value.Value;

import java.util.Map;

public record HeapAllocation(String variableName, Expression expression) implements Statement {

    @Override
    public ProgramState execute(ProgramState state) {
        SymbolTable<String, Value> symTable = state.getSymbolTable();
        var heap = state.getHeap();

        if (!symTable.isDefined(variableName)) {
            throw new RuntimeException("Variable " + variableName + " not defined");
        }

        Value variableValue = symTable.get(variableName);

        if (!(variableValue instanceof RefValue varRef)) {
            throw new RuntimeException("Variable " + variableName + " is not a RefValue");
        }

        // Evaluate the expression
        Value exprValue = expression.evaluate(symTable, heap);

        // Only unwrap RefValue if the inner type is not a RefType
        if (exprValue instanceof RefValue ref && !(varRef.getLocationType() instanceof RefType)) {
            int address = ref.getAddress();
            if (address <= 0 || !heap.containsKey(address)) {
                throw new RuntimeException("Invalid heap reference: address " + address +
                        " is not a valid heap location");
            }
            exprValue = heap.get(address);
        }

        // Allocate the value on the heap
        int newAddress = heap.allocate(exprValue);

        // Update the variable to hold the new reference, using the existing variable's inner type
        symTable.put(variableName, new RefValue(newAddress, varRef.getLocationType()));

        return null;
    }
    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        Type varType = typeEnv.get(variableName);
        Type expType = expression.typecheck(typeEnv);

        if (!varType.equals(new RefType(expType)))
            throw new RuntimeException("NEW type mismatch");

        return typeEnv;
    }

    @Override
    public String toString() {
        return "new(" + variableName + ", " + expression.toString() + ")";
    }
}
