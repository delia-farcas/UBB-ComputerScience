package org.example.map_completed.controller;


import org.example.map_completed.model.state.*;
import org.example.map_completed.model.statement.Statement;
import org.example.map_completed.model.value.RefValue;
import org.example.map_completed.model.value.Value;
import org.example.map_completed.repository.Repository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;


public final class Controller {
    private final Repository repository;
    private ExecutorService executor;

    public Controller(Repository repository) {
        this.repository = repository;
        this.executor = Executors.newFixedThreadPool(2);
    }



    public void addNewProgram(Statement program) {
        var executionStack = new LinkedListExecutionStack<Statement>();
        executionStack.push(program);
        ProgramState newProgramState = new ProgramState(
                executionStack,
                new MapSymbolTable<>(),
                new ArrayListOut(),
                new MapFileTable<>(),
                new MapHeap<>()
        );
        repository.addProgramState(newProgramState);
    }
    
    public ArrayList<ProgramState> removeCompletedProgram(ArrayList<ProgramState> programStates) {
        return (ArrayList<ProgramState>) programStates.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public void oneStepForAllPrg(List<ProgramState> programStates) {

        programStates.forEach(repository::logPrgStateExec);

        List<Callable<ProgramState>> callList = programStates.stream()
                .map(prg -> (Callable<ProgramState>) prg::executeOneStep)
                .toList();

        try {
            List<ProgramState> newProgramStates =
                    executor.invokeAll(callList).stream()
                            .map(future -> {
                                try {
                                    return future.get();
                                } catch (ExecutionException e) {
                                    throw new RuntimeException(e.getCause());
                                } catch (InterruptedException e) {
                                    Thread.currentThread().interrupt();
                                    return null;
                                }
                            })
                            .filter(Objects::nonNull)
                            .collect(Collectors.toList());

            programStates.addAll(newProgramStates);
            repository.setPrgStates(programStates);

        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        programStates.forEach(repository::logPrgStateExec);
    }


    public void executeAllSteps() {
        executor = Executors.newFixedThreadPool(2);

        List<ProgramState> prgList =
                removeCompletedProgram((ArrayList<ProgramState>) repository.getPrgStates());

        while (!prgList.isEmpty()) {

            GarbageCollector gc = new GarbageCollector();
            gc.collect(prgList);

            oneStepForAllPrg(prgList);

            displayCurrentState();

            prgList =
                    removeCompletedProgram((ArrayList<ProgramState>) repository.getPrgStates());
        }

        executor.shutdownNow();

        System.out.println("--- Final Program State ---");
        displayCurrentState();
    }

    public void displayCurrentState() {
//        IO.println(repository.getCurrentState());
        IO.println(repository.displayState());
    }

    public Repository repository() {
        return repository;
    }

    public ExecutorService executor() {
        return executor;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (obj == null || obj.getClass() != this.getClass()) return false;
        var that = (Controller) obj;
        return Objects.equals(this.repository, that.repository) &&
                Objects.equals(this.executor, that.executor);
    }

    @Override
    public int hashCode() {
        return Objects.hash(repository, executor);
    }

    @Override
    public String toString() {
        return "Controller[" +
                "repository=" + repository + ", " +
                "executor=" + executor + ']';
    }


    List<Integer> getAddrFromSymTable(Collection<Value> values) {
        return values.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> ((RefValue)v).getAddress())
                .collect(Collectors.toList());
    }

}
