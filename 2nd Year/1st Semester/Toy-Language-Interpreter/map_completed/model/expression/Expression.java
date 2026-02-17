package org.example.map_completed.model.expression;
import org.example.map_completed.model.state.Heap;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.Value;
import org.example.map_completed.model.state.SymbolTable;

import java.util.Map;

public interface Expression {
    Value evaluate(SymbolTable<String, Value> symbolTable, Heap<Integer, Value> heap);
    Type typecheck(Map<String, Type> typeEnv);
}
