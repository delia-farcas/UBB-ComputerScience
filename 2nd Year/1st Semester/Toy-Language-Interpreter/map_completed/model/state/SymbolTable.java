package org.example.map_completed.model.state;

import java.util.Map;

public interface SymbolTable<K, V> {
    void put(K key, V value);
    V get(K key);
    boolean isDefined(K key);
    void remove(K key);
    SymbolTable<K, V> cloneTable();
    Map<K, V> getContent();
}
