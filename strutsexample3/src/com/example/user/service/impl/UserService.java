package com.example.user.service.impl;

import java.sql.SQLException;

import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.example.db.User;
import com.example.db.UserRole;
import com.example.role.dao.IUserRoleDao;
import com.example.user.dao.IUserDao;
import com.example.user.service.IUserService;

@Service
@Transactional
public class UserService implements IUserService  {

	private IUserDao UserDao;
	private IUserRoleDao UserRoleDao;
	
	
	
	public IUserRoleDao getUserRoleDao() {
		return UserRoleDao;
	}
	

	public void setUserRoleDao(IUserRoleDao userRoleDao) {
		UserRoleDao = userRoleDao;
	}


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
	
	@Override 
	public boolean addUser(User user)
	{
		if(user.getUserId()==null||user.getUserName()==null||user.getPassword()==null)
			return false;
		if(user.getPirv()==null)
			user.setPirv(1);
		UserRole ur  = new UserRole();
		ur.setUserid(user.getUserId());
		//ur.setUser_role(1);		
		//UserRoleDao.insertUserRole(ur);
		UserRoleDao.persistUserRole(ur);
		user.getUserRole().add(ur);
		
		if(user.getStat()==null)
			user.setStat(1);
		
		int cnt = UserDao.getContbyUser(user.getUserId());
		if(cnt>0)
			return false;
		UserDao.insertUser(user);
		return true;
	}

}
