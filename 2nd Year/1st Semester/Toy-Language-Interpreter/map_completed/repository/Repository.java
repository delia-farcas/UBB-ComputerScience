package org.example.map_completed.repository;

import org.example.map_completed.model.state.ProgramState;

import java.util.ArrayList;
import java.util.List;

public interface Repository {
    void addProgramState(ProgramState program);
    ArrayList<ProgramState> getPrgStates();
    void setPrgStates(List<ProgramState> prgStates);
    void logPrgStateExec(ProgramState prgState);
    String displayState();
}
