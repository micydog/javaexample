package com.example.user.service;

import com.example.db.User;

public interface IUserService {
	
	public boolean login(String username, String pwd);

	boolean addUser(User user);

}
