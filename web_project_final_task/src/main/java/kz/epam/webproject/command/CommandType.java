package kz.epam.webproject.command;

import kz.epam.webproject.command.impl.LoginCommand;
import kz.epam.webproject.command.impl.LogoutCommand;
import kz.epam.webproject.command.impl.RegisterCommand;

public enum CommandType {
    LOGIN(new LoginCommand()), LOGOUT(new LogoutCommand()), REGISTER(new RegisterCommand());

    CommandType(Command command) {
        this.command = command;
    }

    private Command command;

    public Command getCommand() {
        return command;
    }
}
