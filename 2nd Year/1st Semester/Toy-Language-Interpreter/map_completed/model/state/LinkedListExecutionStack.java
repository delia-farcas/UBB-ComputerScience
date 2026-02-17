package org.example.map_completed.model.state;

import java.util.LinkedList;

public class LinkedListExecutionStack<T> implements ExecutionStack<T> {
    private final LinkedList<T> stack = new LinkedList<>();

    @Override
    public void push(T value) {
        stack.push(value);
    }

    @Override
    public T pop() {
        return stack.pop();
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        for (int i = 0; i < stack.size(); i++) {
            sb.append(stack.get(i).toString());
            if (i < stack.size() - 1) {
                sb.append(" ; ");
            }
        }
        sb.append("]");
        return sb.toString();
    }

    @Override
    public java.util.List<T> getStackAsList() {
        return new java.util.ArrayList<>(stack);
    }
}
