package org.example.map_completed.model.state;
import java.util.Map;

public interface FileTable<K, V> {
    void put(K key, V value);
    V get(K key);
    boolean isDefined(K key);
    void remove(K key);
    Map<K, V> getContent();
}
