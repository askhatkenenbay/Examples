package kz.epam.webproject.command.impl;

import kz.epam.webproject.command.Command;

import javax.servlet.http.HttpServletRequest;

public class RegisterCommand implements Command {
    private boolean firstUser = true;
    @Override
    public String execute(HttpServletRequest request) {
        if(firstUser){

        }
        String page = "/jsp/register.jsp";
        return page;
    }
}
