package org.example.map_completed.model.statement;

import org.example.map_completed.model.expression.Expression;
import org.example.map_completed.model.type.BoolType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.Value;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.state.SymbolTable;
import org.example.map_completed.model.value.BoolValue;
import org.example.map_completed.model.value.Value;

import java.util.HashMap;
import java.util.Map;

public record WhileStatement(Expression condition, Statement body) implements Statement {

    @Override
    public ProgramState execute(ProgramState state) {
        SymbolTable<String, Value> symTable = state.getSymbolTable();
        Value condValue = condition.evaluate(symTable, state.getHeap());

        if (!(condValue instanceof BoolValue boolVal)) {
            throw new RuntimeException("Condition expression is not a boolean");
        }

        if (!condValue.equals(new BoolValue(false))) {
            state.getExecutionStack().push(this);
            state.getExecutionStack().push(body);
        }

        return null;
    }
    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        if (!condition.typecheck(typeEnv).equals(new BoolType()))
            throw new RuntimeException("WHILE condition not boolean");

        body.typecheck(new HashMap<>(typeEnv));
        return typeEnv;
    }

    @Override
    public String toString() {
        return "While(" + condition.toString() + ") {" + body.toString() + "}";
    }
}
