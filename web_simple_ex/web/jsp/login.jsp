<%--
  Created by IntelliJ IDEA.
  User: Askhat
  Date: 23.07.2019
  Time: 17:22
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login</title>
</head>
<body>
<form name="loginForm" method="POST" action="controller">
    <input type="hidden" name="command" value="login"/>
    Login:<br/>
    <input type="text" name="login" value=""/>
    <br/>Password:<br/>
    <input type="password" name="password" value=""/><br/>
    ${errorLoginPassMessage}<br/>
    ${wrongAction}<br/>
    ${nullPage}<br/>
    <input type="submit" value="Log in"/>
</form>
</body>
</html>

