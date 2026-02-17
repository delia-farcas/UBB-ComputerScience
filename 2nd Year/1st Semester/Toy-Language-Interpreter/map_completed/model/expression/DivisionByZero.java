package org.example.map_completed.model.expression;

public class DivisionByZero extends ArithmeticException {
    public DivisionByZero() {
        super("Division by zero is not allowed.");
    }
}
