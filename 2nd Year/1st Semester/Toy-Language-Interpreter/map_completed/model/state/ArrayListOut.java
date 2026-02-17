package org.example.map_completed.model.state;

import java.util.ArrayList;
import java.util.List;
import org.example.map_completed.model.value.Value;

public class ArrayListOut<T> implements Out<T> {
    private final List<T> list = new ArrayList<>();

    @Override
    public void add(T value) {
        list.add(value);
    }

    @Override
    public List<T> getList() {
        return list;
    }

    @Override
    public String toString() {
        return list.toString();
    }
}
