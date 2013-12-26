package com.example;

import com.example.db.User;
import com.example.user.service.IUserService;

public class LoginAction {
	
	private String username;
	private String password;
	private IUserService userService ;
	private User user;	
	
	
	
	public User getUser() {
		return user;
	}
	public void setUser(User user) {
		this.user = user;
	}
	public IUserService getUserService() {
		return userService;
	}
	public void setUserService(IUserService userService) {
		this.userService = userService;
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
		
		if(userService.login(username, password))
			return "success";
		else
			return "error";
		
		
	}
	
	public String addUser()
	{
		if(userService.addUser(user))
			return "success";
		else
			return "error";
	}

}
