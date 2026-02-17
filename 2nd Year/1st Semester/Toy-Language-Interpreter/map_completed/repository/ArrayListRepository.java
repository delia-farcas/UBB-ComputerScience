package org.example.map_completed.repository;
import org.example.map_completed.model.state.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class ArrayListRepository implements Repository {
    private final ArrayList<ProgramState> programStates = new ArrayList<>();
    private final String logFilePath;
    public ArrayListRepository(String logFilePath) {
        this.logFilePath = logFilePath;
    }
    @Override
    public void addProgramState(ProgramState state) {
        programStates.add(state);
    }

    @Override
    public ArrayList<ProgramState> getPrgStates() {
        return programStates;
    }

    @Override
    public void setPrgStates(List<ProgramState> prgStates) {
        this.programStates.clear();
        this.programStates.addAll(prgStates);
    }

    @Override
    public void logPrgStateExec(ProgramState prgState) throws RuntimeException {
        try (PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)))) {

            logFile.println("Id: " + prgState.getId());

            logFile.println("ExeStack:");
            logFile.println(prgState.getExecutionStack().toString());

            logFile.println("SymTable:");
            logFile.println(prgState.getSymbolTable().toString());

            logFile.println("Heap:");
            logFile.println(prgState.getHeap().toString());

            logFile.println("Out:");
            logFile.println(prgState.getOut().toString());

            logFile.println("FileTable:");
            logFile.println(prgState.getFileTable().toString());
        } catch (IOException e) {
            throw new RuntimeException("Could not write to log file: " + e.getMessage());
        }
    }

    public String displayState() {
        StringBuilder res = new StringBuilder();
        for (ProgramState programState : programStates) {
            res.append("Id: ").append(programState.getId()).append("\n");
            res.append("ExecutionStack: ").append(programState.getExecutionStack().toString()).append("\n");
            res.append("SymbolTable: ").append(programState.getSymbolTable().toString()).append("\n");
        }

        if (!programStates.isEmpty()) {
            ProgramState first = programStates.get(0);
            res.append("Out: ").append(first.getOut().toString()).append("\n");
            res.append("FileTable: ").append(first.getFileTable().toString()).append("\n");
            res.append("Heap: ").append(first.getHeap().toString()).append("\n");
        }

        return res.toString();
    }
}