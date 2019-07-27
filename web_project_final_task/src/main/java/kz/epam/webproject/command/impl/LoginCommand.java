package kz.epam.webproject.command.impl;

import kz.epam.webproject.command.Command;
import kz.epam.webproject.command.service.UserService;

import javax.servlet.http.HttpServletRequest;

public class LoginCommand implements Command {
    private static final String PARAM_NAME_LOGIN = "login";
    private static final String PARAM_NAME_PASSWORD = "password";
    private UserService service = new UserService();
    @Override
    public String execute(HttpServletRequest request) {
        String page = null;
        String login = request.getParameter(PARAM_NAME_LOGIN);
        String pass = request.getParameter(PARAM_NAME_PASSWORD);
        if(service.checkLogin(login,pass)){
            request.setAttribute("user",login);
            page = "/jsp/main.jsp";
        }else{
            request.setAttribute("errorLoginPassMessage", "incorrect login or password");
            page = "/jsp/login.jsp";
        }
        return page;
    }
}
