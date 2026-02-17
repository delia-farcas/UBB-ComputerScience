package org.example.map_completed.model.expression;

import org.example.map_completed.model.state.Heap;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.type.RefType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.IntValue;
import org.example.map_completed.model.value.RefValue;
import org.example.map_completed.model.value.Value;

import java.util.Map;

public record RHExpression(Expression exp) implements Expression{

    @Override
    public Value evaluate(SymbolTable<String, Value> symbolTable, Heap<Integer, Value> heap){
        Value leftValue = exp.evaluate(symbolTable, heap);
        if (!(leftValue instanceof RefValue refValue)) {
            throw new ArithmeticException("rH: expression is not a RefValue");
        }
        int address = refValue.getAddress();

        if (!heap.containsKey(address))
            throw new RuntimeException("rH: invalid heap address");

        return heap.get(address);
    }

    @Override
    public Type typecheck(Map<String, Type> typeEnv) {
        Type type = exp.typecheck(typeEnv);
        if (!(type instanceof RefType))
            throw new RuntimeException("RH argument is not RefType");
        return ((RefType) type).getInner();
    }

    @Override
    public String toString() {
        return "readHeap(" + exp.toString() + ")";
    }

}
