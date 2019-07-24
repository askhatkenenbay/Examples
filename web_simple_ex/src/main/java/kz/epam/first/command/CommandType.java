package kz.epam.first.command;

import kz.epam.first.command.impl.LoginCommand;
import kz.epam.first.command.impl.LogoutCommand;

public enum CommandType {
    LOGIN(new LoginCommand()), LOGOUT(new LogoutCommand());

    CommandType(Command command) {
        this.command = command;
    }

    private Command command;

    public Command getCommand() {
        return command;
    }
}
