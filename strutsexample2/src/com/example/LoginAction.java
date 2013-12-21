package com.example;

import com.example.user.service.IUserService;

public class LoginAction {
	
	private String username;
	private String password;
	private IUserService userSevice ;
	
	
	
	public IUserService getUserSevice() {
		return userSevice;
	}
	public void setUserSevice(IUserService userSevice) {
		this.userSevice = userSevice;
	}
	
	public String getUsername()
	{
		return username;
	}
	public void setUsername(String username){
		
		this.username = username;
		
		
	}
	public String getPassword()
	{
		return password;
	}
	
	public void setPassword(String password)
	{
		this.password = password;
		
	}
	
	public String login() 
	{
		
		if(userSevice.login(username, password))
			return "success";
		else
			return "error";
		
		
	}

}
