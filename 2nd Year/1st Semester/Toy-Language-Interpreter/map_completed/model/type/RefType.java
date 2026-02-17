package org.example.map_completed.model.type;

import org.example.map_completed.model.value.RefValue;
import org.example.map_completed.model.value.Value;

public class RefType implements Type{
    Type inner;
    public RefType(Type inner) {
        this.inner = inner;
    }
    public Type getInner() {
        return inner;
    }

    @Override
    public String toString(){
        return "RefType";
    }

    @Override
    public boolean equals(Object another){
        if (another instanceof RefType otherRef)
            return inner.equals(otherRef.getInner());
        else
            return false;
    }

    @Override
    public Value getDefaultValue(){
        return new RefValue(0, inner);
    }
}
