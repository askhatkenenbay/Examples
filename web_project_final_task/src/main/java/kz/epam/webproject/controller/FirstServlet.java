package kz.epam.webproject.controller;

import kz.epam.webproject.command.Command;
import kz.epam.webproject.command.CommandFactory;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(urlPatterns = "/controller")
public class FirstServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try{
            if(request.getParameter("command").equals("login")){
                processRequest(request,response);
            }
        }catch (Exception e){

        }
        try{
            if(request.getParameter("register").equals("register")){
                registerUser(request,response);
            }
        }catch (Exception e){

        }
        try{
            if(request.getParameter("shop").equals("shop")){
                shop(request,response);
            }
        }catch (Exception e){

        }
        /*response.setContentType("text/html");
        request.setCharacterEncoding("UTF-8");
        response.setCharacterEncoding("UTF-8");
       // response.getWriter().print("This is "+this.getClass().getName()+", using this POST method");
        String input = request.getParameter("input1");
        input = input.toUpperCase();
        request.setAttribute("result",input);
        Item item = new Item(77);
        request.setAttribute("item1",item);
        request.getRequestDispatcher("/jsp/main.jsp").forward(request,response);*/
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request,response);
       // response.setContentType("text/html");
      //  response.getWriter().print("This is "+this.getClass().getName()+", using this GET method");
    }

    private void processRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        String page = null;
        Command command = CommandFactory.defineCommand(request.getParameter("command"));
        page = command.execute(request);
        if(page != null){
            RequestDispatcher dispatcher = getServletContext().getRequestDispatcher(page);
            dispatcher.forward(request,response);
        }else{
            page = "index.jsp";
            request.getSession().setAttribute("nullPage","message nullpage");
            response.sendRedirect(request.getContextPath() + page);
        }
    }

    private void registerUser(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String page = null;
        Command command = CommandFactory.defineCommand(request.getParameter("register"));
        page = command.execute(request);
        if(page != null){
            RequestDispatcher dispatcher = getServletContext().getRequestDispatcher(page);
            dispatcher.forward(request,response);
        }else{
            page = "index.jsp";
            request.getSession().setAttribute("nullPage","message nullpage");
            response.sendRedirect(request.getContextPath() + page);
        }
    }

    private void shop(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        String page = "/jsp/shop.jsp";
        RequestDispatcher dispatcher = getServletContext().getRequestDispatcher(page);
        dispatcher.forward(request,response);
    }
}
