package kz.epam.webproject.command;

import kz.epam.webproject.command.impl.EmptyCommand;

public class CommandFactory {
    public static Command defineCommand(String action){
        Command current = null;
        if(action == null || action.isBlank()){
            return new EmptyCommand();
        }

        try{
            CommandType currentType = CommandType.valueOf(action.toUpperCase());
            current = currentType.getCommand();
        }catch(IllegalArgumentException e){
            //
        }
        return current;
    }
}
