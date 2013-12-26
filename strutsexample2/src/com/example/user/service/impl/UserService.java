package com.example.user.service.impl;

import java.sql.SQLException;

import com.example.db.User;
import com.example.user.dao.IUserDao;
import com.example.user.service.IUserService;

public class UserService implements IUserService  {

	private IUserDao UserDao;
	
	
	public IUserDao getUserDao() {
		return UserDao;
	}


	public void setUserDao(IUserDao userDao) {
		UserDao = userDao;
	}


	@Override
	public boolean login(String username, String pwd) {
		
		User user;
		
		user = UserDao.loadUser(username);
	
		if(user==null)
			return false;
		
		if(!user.getPassword().equals(pwd))
			return false;
		
		return true;
		
	}

}
