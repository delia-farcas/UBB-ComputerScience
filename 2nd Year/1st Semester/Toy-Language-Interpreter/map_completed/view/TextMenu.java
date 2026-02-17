package org.example.map_completed.view;
import java.util.*;

public class TextMenu {
    private final Map<String, Command> commands;
    Scanner scanner=new Scanner(System.in);
    public TextMenu(){ commands=new HashMap<>(); }
    public void addCommand(Command c){ commands.put(c.getKey(),c); }
    private void printMenu(){
        commands.values().stream()
                .sorted(Comparator.comparingInt(com -> Integer.parseInt(com.getKey())))
                .forEach(com -> {
                    String line = String.format("%4s : %s", com.getKey(), com.getDescription());
                    System.out.println(line);
                });
    }
    public void show(){
        try {
            while (true) {
                printMenu();
                System.out.print("Input the option: ");
                String key = scanner.nextLine();
                Command com = commands.get(key);
                if (com == null) {
                    System.out.println("Invalid Option");
                    continue;
                }
                com.execute();
            }
        } finally {
            scanner.close();  // closes the Scanner when done
        }
    }
}