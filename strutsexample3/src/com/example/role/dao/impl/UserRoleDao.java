package com.example.role.dao.impl;

import com.example.db.BaseDao;
import com.example.db.UserRole;
import com.example.role.dao.IUserRoleDao;

public class UserRoleDao extends BaseDao implements IUserRoleDao {
	
	@Override
	public void persistUserRole(UserRole userrole)
	{
		this.getSession().persist(userrole);
	}
	
	@Override
	public void insertUserRole(UserRole userrole)
	{
		
		this.getSession().save(userrole);
	}

}
