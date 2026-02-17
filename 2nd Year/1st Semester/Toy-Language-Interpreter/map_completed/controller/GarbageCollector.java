package org.example.map_completed.controller;

import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.type.RefType;
import org.example.map_completed.model.value.RefValue;
import org.example.map_completed.model.value.Value;

import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class GarbageCollector {
    private final Set<Integer> addresses =  new HashSet<>();

    public void collect(List<ProgramState> states) {
        for (var state: states) {
            var symTable = state.getSymbolTable();
            var heapTable = state.getHeap();

            Map<Integer, Value> heap = heapTable.getContent();
            Map<String, Value> symbolT = symTable.getContent();

            for (var variable : symbolT.entrySet()) {
                var varValue = variable.getValue();
                if (varValue instanceof RefValue) {
                    RefValue refValue = (RefValue) varValue;
                    int adr = refValue.getAddress();
                    if (adr != 0) {
                        addresses.add(adr);
                        var locType = refValue.getLocationType();
                        while (locType instanceof RefType) {
                            RefValue nextVal = (RefValue) heap.get(adr);
                            int nextAdr = nextVal.getAddress();
                            addresses.add(nextAdr);
                            locType = nextVal.getLocationType();
                        }
                    }
                }
            }
        }
        states.getFirst().getHeap().garbage(addresses);
    }
}