package org.example.map_completed.model.value;

import org.example.map_completed.model.type.RefType;
import org.example.map_completed.model.type.Type;

public class RefValue implements Value {
    private final int address;       // Address in the heap
    private final Type locationType; // Type of the value stored at that address

    // Constructor
    public RefValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    // Get the heap address
    public int getAddress() {
        return address;
    }

    // Get the type of the value stored at this address
    public Type getLocationType() {
        return locationType;
    }

    // Returns the RefType corresponding to this reference
    @Override
    public Type getType() {
        return new RefType(locationType);
    }

    @Override
    public String toString() {
        return "Ref(" + address + ", " + locationType + ")";
    }

    @Override
    public boolean equals(Object other) {
        if (other instanceof RefValue ref) {
            return this.address == ref.getAddress() &&
                    this.locationType.equals(ref.getLocationType());
        }
        return false;
    }
}
