package org.example.map_completed.model.value;

import org.example.map_completed.model.type.BoolType;
import org.example.map_completed.model.type.Type;

public record BoolValue(boolean value) implements Value {

    @Override
    public Type getType(){
        return new BoolType();
    }

    @Override
    public String toString(){
        return String.valueOf(value);
    }
}
