package org.example.map_completed.model.value;

import org.example.map_completed.model.type.StringType;
import org.example.map_completed.model.type.Type;

public record StringValue(String val) implements Value {
    public String getVal(){ return val; }
    @Override public Type getType(){ return new StringType(); }
    @Override public String toString(){ return val; }
    @Override public boolean equals(Object other){
        if (this == other) return true;
        if (!(other instanceof StringValue)) return false;
        return val.equals(((StringValue)other).val);
    }
}
