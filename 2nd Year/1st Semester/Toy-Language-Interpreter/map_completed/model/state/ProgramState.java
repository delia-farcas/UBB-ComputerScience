package org.example.map_completed.model.state;

import org.example.map_completed.model.statement.Statement;
import org.example.map_completed.model.value.StringValue;
import org.example.map_completed.model.value.Value;

import java.io.BufferedReader;

public class ProgramState {
    private static int prevId = 1;
    private final int id;
    private final ExecutionStack<Statement> executionStack;
    private final SymbolTable<String, Value> symbolTable;
    private final Out<Value> out;
    private final FileTable<StringValue, BufferedReader> fileTable;
    private final Heap<Integer, Value> heap;

    public ProgramState(
            ExecutionStack<Statement> executionStack,
            SymbolTable<String, Value> symbolTable,
            Out<Value> out,
            FileTable<StringValue, BufferedReader> fileTable,
            Heap<Integer, Value> heap
    ) {
        this.executionStack = executionStack;
        this.symbolTable = symbolTable;
        this.out = out;
        this.fileTable = fileTable;
        this.heap = heap;
        this.id = prevId++;
    }

    public int getId(){return id;}
    public ExecutionStack<Statement> getExecutionStack() {
        return executionStack;
    }

    public SymbolTable<String, Value> getSymbolTable() {
        return symbolTable;
    }

    public Out<Value> getOut() {
        return out;
    }

    public FileTable<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }
    public Heap<Integer, Value> getHeap() { return heap; }

    public boolean isNotCompleted() {
        return ! executionStack.isEmpty();
    }

    public ProgramState executeOneStep() {
        if (executionStack.isEmpty()) {
            throw new RuntimeException("Stack is empty");
        }
        Statement statement = executionStack.pop();
        return statement.execute(this);
    }

    @Override
    public String toString() {
        return  "Id: " + id + "\n" +
                "ExecutionStack: " + executionStack + "\n" +
                "SymbolTable: " + symbolTable + "\n" +
                "Out: " + out + "\n" +
                "FileTable: " + fileTable + "\n" +
                "Heap: " + heap;
    }
}
