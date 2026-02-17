package org.example.map_completed.model.type;

import org.example.map_completed.model.value.*;

public class IntType implements Type {

    @Override
    public boolean equals(Object another) {
        return another instanceof IntType;
    }

    @Override
    public String toString() {
        return "int";
    }

    @Override
    public Value getDefaultValue() {
        return new IntValue(0);
    }
}