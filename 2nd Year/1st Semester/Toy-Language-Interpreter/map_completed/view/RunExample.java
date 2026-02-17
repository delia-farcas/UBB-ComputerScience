package org.example.map_completed.view;
import org.example.map_completed.controller.Controller;
import org.example.map_completed.model.expression.DivisionByZero;
import org.example.map_completed.model.statement.Statement;

public class RunExample extends Command {
    private final Controller ctr;
    private final Statement stm;
    public RunExample(String key, String desc, Statement stm, Controller ctr){ super(key, desc); this.stm = stm; this.ctr = ctr;}
    @Override
    public void execute() {
        try {
            java.util.Map<String, org.example.map_completed.model.type.Type> typeEnv = new java.util.HashMap<>();
            stm.typecheck(typeEnv);
            ctr.addNewProgram(stm);
            ctr.executeAllSteps();

        } catch (RuntimeException e) {
            System.out.println("Interpreter error: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Unexpected error: " + e.getMessage());
        }
    }
}
