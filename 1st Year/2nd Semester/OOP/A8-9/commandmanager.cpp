#include "commandmanager.h"

void CommandManager::executeCommand(std::unique_ptr<Command> command) {
    try {
        command->execute();
        undoStack.push(std::move(command));

        // Clear redo stack when a new command is executed
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }
    catch (const std::exception& e) {
        // If command execution fails, don't add it to the stack
        throw;
    }
}

bool CommandManager::canUndo() const {
    return !undoStack.empty();
}

bool CommandManager::canRedo() const {
    return !redoStack.empty();
}

void CommandManager::undo() {
    if (canUndo()) {
        auto command = std::move(undoStack.top());
        undoStack.pop();

        try {
            command->undo();
            redoStack.push(std::move(command));
        }
        catch (const std::exception& e) {
            // If undo fails, put the command back
            undoStack.push(std::move(command));
            throw;
        }
    }
}

void CommandManager::redo() {
    if (canRedo()) {
        auto command = std::move(redoStack.top());
        redoStack.pop();

        try {
            command->execute();
            undoStack.push(std::move(command));
        }
        catch (const std::exception& e) {
            // If redo fails, put the command back
            redoStack.push(std::move(command));
            throw;
        }
    }
}

void CommandManager::clear() {
    while (!undoStack.empty()) {
        undoStack.pop();
    }
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}
