package org.example.map_completed.model.state;

import java.util.HashMap;
import java.util.Map;

public class MapFileTable<K, V> implements FileTable<K, V> {
    private final Map<K, V> map = new HashMap<>();
    @Override
    public void put(K key, V value) { map.put(key, value); }
    @Override
    public V get(K key) { return map.get(key); }
    @Override
    public boolean isDefined(K key) { return map.containsKey(key); }
    @Override
    public void remove(K key) { map.remove(key); }
    @Override
    public Map<K, V> getContent() { return map; }
    @Override
    public String toString(){ return map.toString(); }
}
