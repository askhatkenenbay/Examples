package kz.epam.first.command.impl;

import kz.epam.first.command.Command;

import javax.servlet.http.HttpServletRequest;

public class EmptyCommand implements Command {
    @Override
    public String execute(HttpServletRequest request) {
        String page = "/index.jsp";
        return page;
    }
}
