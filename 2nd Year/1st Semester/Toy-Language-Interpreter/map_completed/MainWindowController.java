package org.example.map_completed;

import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.input.MouseEvent;
import org.example.map_completed.controller.Controller;
import org.example.map_completed.controller.GarbageCollector;
import org.example.map_completed.model.state.ProgramState;
import org.example.map_completed.model.value.Value;

import java.util.*;
import java.util.stream.Collectors;

public class MainWindowController {

    @FXML
    private TextField numberOfPrgStatesTextField;
    @FXML
    private TableView<Map.Entry<Integer, Value>> heapTableView;
    @FXML
    private TableColumn<Map.Entry<Integer, Value>, Integer> addressColumn;
    @FXML
    private TableColumn<Map.Entry<Integer, Value>, String> valueColumn;

    @FXML
    private ListView<String> outputListView;
    @FXML
    private ListView<String> fileTableListView;
    @FXML
    private ListView<Integer> prgStateIdentifiersListView;

    @FXML
    private TableView<Map.Entry<String, Value>> symbolTableView;
    @FXML
    private TableColumn<Map.Entry<String, Value>, String> variableNameColumn;
    @FXML
    private TableColumn<Map.Entry<String, Value>, String> variableValueColumn;

    @FXML
    private ListView<String> executionStackListView;
    @FXML
    private Button runOneStepButton;

    private Controller controller;

    public void setController(Controller controller) {
        this.controller = controller;
        populateAll();
    }

    @FXML
    public void initialize() {
        addressColumn.setCellValueFactory(p ->
                new SimpleObjectProperty<>(p.getValue().getKey()));
        valueColumn.setCellValueFactory(p ->
                new SimpleStringProperty(p.getValue().getValue().toString()));

        variableNameColumn.setCellValueFactory(p ->
                new SimpleStringProperty(p.getValue().getKey()));
        variableValueColumn.setCellValueFactory(p ->
                new SimpleStringProperty(p.getValue().getValue().toString()));

        prgStateIdentifiersListView
                .getSelectionModel()
                .setSelectionMode(SelectionMode.SINGLE);
    }

    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    private void populateAll() {
        if (controller == null) return;

        List<ProgramState> prgList = controller.repository().getPrgStates();
        numberOfPrgStatesTextField.setText(String.valueOf(prgList.size()));

        if (prgList.isEmpty()) {
            clearUI();
            return;
        }

        ProgramState firstState = prgList.get(0);

        heapTableView.setItems(FXCollections.observableArrayList(
                firstState.getHeap().getContent().entrySet()
        ));
        heapTableView.refresh();
        outputListView.setItems(FXCollections.observableArrayList(
                firstState.getOut().getList().stream()
                        .map(Object::toString)
                        .collect(Collectors.toList())
        ));

        fileTableListView.setItems(FXCollections.observableArrayList(
                firstState.getFileTable().getContent().keySet().stream()
                        .map(Object::toString)
                        .collect(Collectors.toList())
        ));

        List<Integer> ids = prgList.stream()
                .map(ProgramState::getId)
                .collect(Collectors.toList());

        prgStateIdentifiersListView.setItems(
                FXCollections.observableArrayList(ids)
        );

        if (!ids.isEmpty() &&
                prgStateIdentifiersListView.getSelectionModel().getSelectedItem() == null) {
            prgStateIdentifiersListView.getSelectionModel().select(0);
        }

        populateSymTableAndExeStack();
    }

    private void clearUI() {
        heapTableView.getItems().clear();
        symbolTableView.getItems().clear();
        executionStackListView.getItems().clear();
        outputListView.getItems().clear();
        fileTableListView.getItems().clear();
        prgStateIdentifiersListView.getItems().clear();
    }

    @FXML
    void changeProgramState(MouseEvent event) {
        populateSymTableAndExeStack();
    }

    private void populateSymTableAndExeStack() {
        Integer selectedId = prgStateIdentifiersListView
                .getSelectionModel()
                .getSelectedItem();

        if (selectedId == null) return;

        ProgramState currentPrgState = controller.repository()
                .getPrgStates()
                .stream()
                .filter(state -> state.getId() == selectedId.intValue())
                .findFirst()
                .orElse(null);

        if (currentPrgState == null) return;

        List<Map.Entry<String, Value>> symTableEntries = new ArrayList<>(
                currentPrgState.getSymbolTable().getContent().entrySet()
        );

        symTableEntries.sort(Map.Entry.comparingByKey());

        symbolTableView.setItems(FXCollections.observableArrayList(symTableEntries));
        symbolTableView.refresh();

        List<String> stack = currentPrgState
                .getExecutionStack()
                .getStackAsList()
                .stream()
                .map(Object::toString)
                .collect(Collectors.toList());

        Collections.reverse(stack);
        executionStackListView.setItems(
                FXCollections.observableArrayList(stack)
        );
    }

    @FXML
    void runOneStep(ActionEvent event) {
        if (controller == null) {
            showAlert("Error", "No program selected.");
            return;
        }

        List<ProgramState> prgList = controller.repository().getPrgStates();

       prgList = controller.removeCompletedProgram(
              (ArrayList<ProgramState>) prgList
       );

        if (prgList.isEmpty()) {
            showAlert("Info", "Nothing left to execute.");
            controller.repository().setPrgStates(prgList);
            populateAll();
            return;
        }

        try {
            GarbageCollector gc = new GarbageCollector();
            gc.collect(prgList);

            controller.oneStepForAllPrg(prgList);

            controller.repository().setPrgStates(prgList);

        } catch (Exception e) {
            showAlert("Execution Error", e.getMessage());
            return;
        }

        populateAll();
    }
}