package kz.epam.first.command.impl;

import kz.epam.first.command.Command;

import javax.servlet.http.HttpServletRequest;

public class LogoutCommand implements Command {

    public String execute(HttpServletRequest request) {
        String page = "/index.jsp";
        request.getSession().invalidate();
        return page;
    }
}
