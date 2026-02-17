package org.example.map_completed.model.type;

import org.example.map_completed.model.value.*;

public class BoolType implements Type {

    @Override
    public boolean equals(Object another) {
        return another instanceof BoolType;
    }

    @Override
    public String toString() {
        return "bool";
    }

    @Override
    public Value getDefaultValue() {
        return new BoolValue(false);
    }
}
