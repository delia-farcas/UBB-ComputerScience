package org.example.map_completed.model.statement;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.type.Type;

import java.util.Map;

public interface Statement {
    ProgramState execute(ProgramState state);
    Map<String, Type> typecheck(Map<String, Type> typeEnv);
}
