package kz.epam.webproject.command.service;

public class UserService {
    public boolean checkLogin(String login, String password){
        return login.equals(password);
    }
}
