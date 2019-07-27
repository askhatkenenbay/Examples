package kz.epam.webproject.command.impl;

import kz.epam.webproject.command.Command;

import javax.servlet.http.HttpServletRequest;

public class EmptyCommand implements Command {
    @Override
    public String execute(HttpServletRequest request) {
        String page = "/index.jsp";
        return page;
    }
}
