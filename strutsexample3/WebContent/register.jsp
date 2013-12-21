<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@page import="org.apache.struts2.ServletActionContext"%> 
<%@taglib prefix="s" uri="/struts-tags"%>
<%@ page import="com.opensymphony.xwork2.util.ValueStack" %>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <!--<script type="text/javascript" src="js1/reg.js"></script> -->
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<title> 用户注册 </title>
	
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

  </head>
  
  <body>
    <div align="center">
  <table width="648" height="41" border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="images/top.jpg">&nbsp;</td>
    </tr>
  </table>
  <form  method="post" action="adduser.action"><!--   onSubmit="return Mycheck()">-->
  <table width="648" border="0" cellpadding="0" cellspacing="0">
    <%ValueStack vs=(ValueStack)request.getAttribute("struts.valueStack");%>
    <tr bgcolor="#FFFFFF">
      <td width="129" height="25"><div align="right">用&nbsp;户&nbsp;名：</div></td>
      <td width="419">&nbsp;&nbsp;<input name="user.userId" type="text" size="30"
     <%if(request.getParameter("user.userId")!=null){%> value="<%=request.getParameter("user.userId")%>" <%}%>>
	  *
    </tr>
    <tr bgcolor="#FFFFFF">
      <td height="25"><div align="right">密&nbsp;&nbsp;&nbsp;&nbsp;码：</div></td>
      <td>&nbsp;&nbsp;<input name="password1" type="password" size="30">
        *（由6-20位内的字母和数字组成）</td>
    </tr>
    <tr bgcolor="#FFFFFF">
      <td height="25"><div align="right">确认密码：</div></td>
      <td>&nbsp;&nbsp;<input name="user.password" type="password" size="30">
        *</td>
    </tr>
    <tr bgcolor="#FFFFFF">
      <td height="25"><div align="right">真实姓名：</div></td>
      <td>&nbsp;&nbsp;<input name="user.userName" type="text" size="30"      
      <%if(request.getParameter("user.userName")!=null){%> value="<%=request.getParameter("user.userName")%>"<%}%>>
        *</td>
    </tr>
   
    <tr bgcolor="#FFFFFF">
      <td height="25"><div align="right">性&nbsp;&nbsp;&nbsp;&nbsp;别：</div></td>
      <td>&nbsp;&nbsp;
        <input type="radio" value="男"  name="user.sex" checked="checked">
        男
        <input type="radio" name="user.sex" value="女" <%if (vs!=null&&vs.findString("user.sex").equals("女")){ %> checked="checked" <%}%>>
        女 </td>
    </tr>
	  <tr bgcolor="#FFFFFF">
      <td height="25"><div align="right">Email：&nbsp;&nbsp;</div></td>
      <td>&nbsp;&nbsp;<input name="user.email" type="text" size="30"
      <%if(request.getParameter("user.email")!=null){%> value="<%=request.getParameter("user.email")%>" <%}%>>
        *</td>
    </tr>

	  <tr bgcolor="#FFFFFF">
      <td height="25" colspan="2"><div align="center"><font color="FF9000">注：如果您在30天内没有登录该网站，您的信息将会被删除。</font></div></td>
      </tr>
	 <tr bgcolor="#FFFFFF">
       <td height="25">&nbsp;</td>
       <td>&nbsp;&nbsp;<input type="submit" name="Submit2" value="注册">&nbsp;&nbsp;
     &nbsp;&nbsp;   <input type="reset" name="Submit" value="重置">        </td>
    </tr>
  
	
    </table>
    </form>
   <%if(request.getParameter("success")!=null){%>	  
        <div align="center"><%=request.getAttribute("user.pirv")%></div>

	<%}%>

</div>
  </body>
</html>