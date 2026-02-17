package org.example.map_completed.model.statement;

import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.type.Type;

import java.util.Map;

public class NoOpStatement implements Statement{

    @Override
    public ProgramState execute(ProgramState state){
        return null;
    }
    @Override
    public Map<String, Type> typecheck(Map<String, Type> typeEnv) {
        return typeEnv;
    }
}
