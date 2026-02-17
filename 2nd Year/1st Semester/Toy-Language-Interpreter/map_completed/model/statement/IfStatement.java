package org.example.map_completed.model.statement;

import org.example.map_completed.model.expression.Expression;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.type.BoolType;
import org.example.map_completed.model.type.Type;
import org.example.map_completed.model.value.BoolValue;
import org.example.map_completed.model.value.Value;

import java.util.HashMap;
import java.util.Map;

public record IfStatement (Expression condition, Statement thenStatement, Statement elseStatement) implements Statement {

    @Override
    public ProgramState execute(ProgramState state) {
        Value conditionValue = condition.evaluate(state.getSymbolTable(), state.getHeap());
        if(!conditionValue.getType().equals(new BoolType())){
            throw new RuntimeException("Condition is not a bool.");
        }
        BoolValue booleanValue = (BoolValue) conditionValue;
        Statement chosenStatement = booleanValue.value() ? thenStatement : elseStatement;
        state.getExecutionStack().push(chosenStatement);
        return null;
    }

    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        if (!condition.typecheck(typeEnv).equals(new BoolType()))
            throw new RuntimeException("IF condition not boolean");

        thenStatement.typecheck(new HashMap<>(typeEnv));
        elseStatement.typecheck(new HashMap<>(typeEnv));
        return typeEnv;
    }

    @Override
    public String toString() {
        return "If(" + condition.toString() + ") Then {" + thenStatement.toString() + "} Else {" + elseStatement.toString() + "}";
    }
}
