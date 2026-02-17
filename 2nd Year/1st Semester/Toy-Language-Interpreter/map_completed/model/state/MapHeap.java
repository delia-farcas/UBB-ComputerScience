package org.example.map_completed.model.state;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class MapHeap<K, V>  implements Heap<K, V> {
    private final Map<K, V> heap = new HashMap<>();
    private int nextFreeKey = 1;

    @Override
    public K allocate(V value) {
        K key = (K) (Integer) nextFreeKey;
        heap.put(key, value);
        nextFreeKey++;
        return key;
    }
    @Override
    public void put(K key, V value) {
        if (!heap.containsKey(key))
            throw new RuntimeException("Invalid heap key: " + key);
        heap.put(key, value);
    }

    @Override
    public V get(K key) {
        if (!heap.containsKey(key))
            throw new RuntimeException("Invalid heap key: " + key);
        return heap.get(key);
    }

    @Override
    public boolean containsKey(K key){
        return heap.containsKey(key);
    }

    @Override
    public Map<K, V> getContent() {
        return heap;
    }
    public void setContent(Map<K, V> newHeap) {
        heap.clear();
        heap.putAll(newHeap);
        // update nextFreeKey assuming K=Integer
        nextFreeKey = heap.keySet().stream()
                .mapToInt(k -> (Integer) k)
                .max()
                .orElse(0) + 1;
    }
    @Override
    public K getNextFreeKey() {
        return (K) (Integer) nextFreeKey;
    }

    @Override
    public String toString() {
        return heap.toString();
    }

    @Override
    public void garbage(Set<Integer> addresses) {
        Set<K> toBeRemoved = new HashSet<>(); // Folosește K aici, nu Integer

        for (var elem : heap.entrySet()) {
            // Facem cast la Integer pentru a putea verifica în setul de adrese
            if (!addresses.contains((Integer) elem.getKey())) {
                toBeRemoved.add(elem.getKey());
            }
        }

        for (K key : toBeRemoved) {
            heap.remove(key);
        }
    }
}
