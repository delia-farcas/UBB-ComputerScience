package org.example.map_completed.model.statement;

import org.example.map_completed.model.expression.Expression;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.type.Type;

import java.util.Map;

public record PrintStatement(Expression expression) implements Statement{

    @Override
    public ProgramState execute(ProgramState state){
        state.getOut().add(expression.evaluate(state.getSymbolTable(), state.getHeap()));
        return null;
    }

    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        expression.typecheck(typeEnv);
        return typeEnv;
    }
    @Override
    public String toString() {
        return "Print(" + expression.toString() + ")";
    }
}
