package com.example.user.dao;

import java.sql.SQLException;

import com.example.db.User;

public interface IUserDao {
	
	public User loadUser(String userName) ;
	

}
