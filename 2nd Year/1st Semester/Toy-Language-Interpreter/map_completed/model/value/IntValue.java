package org.example.map_completed.model.value;
import org.example.map_completed.model.type.IntType;
import org.example.map_completed.model.type.Type;

public record IntValue(int value) implements Value {
    @Override
    public Type getType() {
        return new IntType();
    }

    @Override
    public String toString(){
        return String.valueOf(value);
    }
}
