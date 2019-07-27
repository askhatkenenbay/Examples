package kz.epam.webproject.command.impl;

import kz.epam.webproject.command.Command;

import javax.servlet.http.HttpServletRequest;

public class LogoutCommand implements Command {

    public String execute(HttpServletRequest request) {
        String page = "/index.jsp";
        request.getSession().invalidate();
        return page;
    }
}
