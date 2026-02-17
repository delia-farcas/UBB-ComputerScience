package org.example.map_completed.model.state;

import org.example.map_completed.model.value.Value;

import java.util.List;

public interface Out<T> {
    void add(T value);
    List<T> getList();
}
