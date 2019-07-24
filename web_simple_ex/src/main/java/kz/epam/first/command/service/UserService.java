package kz.epam.first.command.service;

public class UserService {
    public boolean checkLogin(String login, String password){
        return login.equals(password);
    }
}
