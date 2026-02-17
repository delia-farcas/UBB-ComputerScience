package org.example.map_completed.model.state;

public interface ExecutionStack<T> {
    void push(T value);
    T pop();
    boolean isEmpty();
    java.util.List<T> getStackAsList();
}
