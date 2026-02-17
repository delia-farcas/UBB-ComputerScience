package org.example.map_completed.model.state;
import java.util.Map;
import java.util.Set;

public interface Heap<K, V>{
    K allocate(V value);
    void put(K key, V value);
    V get(K key);
    boolean containsKey(K key);
    Map<K, V> getContent();
    void setContent(Map<K, V> newHeap);
    void garbage(Set<Integer> addresses);
    K getNextFreeKey();
}
