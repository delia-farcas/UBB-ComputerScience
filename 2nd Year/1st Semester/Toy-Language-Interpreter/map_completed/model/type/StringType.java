package org.example.map_completed.model.type;

import org.example.map_completed.model.value.*;

public class StringType implements Type {

    @Override
    public boolean equals(Object another) {
        return another instanceof StringType;
    }

    @Override
    public String toString() {
        return "string";
    }

    @Override
    public Value getDefaultValue() {
        return new StringValue("");
    }
}
