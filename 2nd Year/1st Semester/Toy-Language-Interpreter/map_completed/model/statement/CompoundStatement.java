package org.example.map_completed.model.statement;

import org.example.map_completed.model.state.ExecutionStack;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.type.Type;

import java.util.Map;

public record CompoundStatement(Statement first, Statement second) implements Statement{

    @Override
    public ProgramState execute(ProgramState state){
        ExecutionStack<Statement> stack = state.getExecutionStack();
        stack.push(this.second);
        stack.push(this.first);
        return null;
    }

    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        return second.typecheck(first.typecheck(typeEnv));
    }

    @Override
    public String toString() {
        return first.toString() + "; " + second.toString();
    }
}
