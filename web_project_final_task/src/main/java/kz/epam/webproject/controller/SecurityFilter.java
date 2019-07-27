package kz.epam.webproject.controller;

import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.annotation.WebInitParam;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebFilter(urlPatterns = { "/jsp/*" }, initParams = { @WebInitParam(name="INDEX_PATH",value = "/index.jsp")})
public class SecurityFilter implements Filter{
    private String indexPath;

    public void init(FilterConfig filterConfig) throws ServletException {
        indexPath = filterConfig.getInitParameter("INDEX_PATH");
    }


    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        HttpServletResponse httpResponce = (HttpServletResponse) servletResponse;
        HttpServletRequest httpRequest = (HttpServletRequest) servletRequest;
        httpResponce.sendRedirect(httpRequest.getContextPath() + indexPath);
        filterChain.doFilter(servletRequest,servletResponse);
    }


    public void destroy() {

    }
}
