<%@ page language="java" import="java.util.*" pageEncoding="gb2312"%>


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>    
    
    <title>My JSP 'index.jsp' starting page</title>
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
  </head>
  
  <body>
    This is my JSP page. 
     <br>
     <form action="login.action" method="post">
<table align="center">
<caption><h3>用户登陆</h3></caption>
<tr>

<td>用户名<input type="text" name="username"/></td>
</tr>
<tr>

<td>密&nbsp;&nbsp;码<input type="text" name="password"/></td>
</tr>
<tr align="center">
<td colspan="2"><input type="submit" value="登陆"/><input
type="reset" value="重填" /></td>
</tr>
</table>
</form>
  </body>
</html>