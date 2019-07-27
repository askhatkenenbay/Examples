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
    <link rel="icon" type="image/ico" href="https://www.atlassian.design/server/images/iconography/Icon_branches_example_24_2x.png" />
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href='//fonts.googleapis.com/css?family=Open+Sans:700,600' rel='stylesheet' type='text/css'>
    <style>
        body{
            font-family: 'Open Sans', sans-serif;
            background:#3498db;
            margin: 0 auto 0 auto;
            width:100%;
            text-align:center;
            margin: 20px 0px 20px 0px;
        }
        p{
            font-size:12px;
            text-decoration: none;
            color:#ffffff;
        }
        h1{
            font-size:1.5em;
            color:#525252;
        }
        .box{
            background:white;
            width:300px;
            border-radius:6px;
            margin: 0 auto 0 auto;
            padding:0px 0px 70px 0px;
            border: #2980b9 4px solid;
        }
        .username{
            background:#ecf0f1;
            border: #ccc 1px solid;
            border-bottom: #ccc 2px solid;
            padding: 8px;
            width:250px;
            color:#AAAAAA;
            margin-top:10px;
            font-size:1em;
            border-radius:4px;
        }
        .button{
            background:#2ecc71;
            width:125px;
            padding-top:5px;
            padding-bottom:5px;
            color:white;
            border-radius:4px;
            border: #27ae60 1px solid;
            margin-top:20px;
            margin-bottom:20px;
            float:left;
            margin-left:88px;
            font-weight:800;
            font-size:0.8em;
        }
        .button:hover{
            background:#2CC06B;
        }
        .fpwd{
            color:#f1c40f;
            text-decoration: underline;
        }
        #absoluteCenteredDiv{
            position: absolute;
            top:0;
            bottom: 0;
            left: 0;
            right: 0;
            margin: auto;
            width:400px;
            height: 300px;
            text-align: center;
        }
    </style>
</head>
<body>
<div id="absoluteCenteredDiv">
    <form name="loginForm" method="POST" action="controller" id = "loginForm">
        <input type="hidden" name="command" value="login"/>
        <div class="box">
            <h1>Login Form</h1>
            <input class="username" name="login" type="text" placeholder="User Name">
            <input class="username" name="password" type="password" placeholder="Password" id = "password">
            <%--            <a href="#"><div class="button">Sign In</div></a>--%>
            ${errorLoginPassMessage}<br/>
            ${wrongAction}<br/>
            ${nullPage}<br/>
            <input onclick="checkPassword()" class = "button" value="Log in"/>
        </div>
    </form>
    <form name="registerForm" method="POST"  action="controller" id = "registerForm">
        <input type="hidden" name="register" value="register"/>
        <p>Not registered? <input class="fpwd" id="signup" type = "submit"><label for="signup">Create an account</label></p>
    </form>

</div>
</body>
<script>
    function checkPassword() {
        var pass = document.getElementById("password");
        if (pass.value.length > 4){
            document.getElementById("loginForm").submit();
        }
        else{
            document.getElementsByClassName("button")[0].style.backgroundColor = "#ff0000";
        }
    }
</script>
</html>
