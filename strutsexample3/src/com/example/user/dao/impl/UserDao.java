package com.example.user.dao.impl;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

import org.hibernate.Criteria;
import org.hibernate.criterion.Restrictions;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.jdbc.core.RowMapper;

import com.example.db.BaseDao;
import com.example.db.User;
import com.example.user.dao.IUserDao;

public class UserDao extends BaseDao implements IUserDao {

	@Override
	public User loadUser(String userName)  {
		
		/*String sql = "select * from mydocuser where username=?";
		try{
			
			User user =this.getJdbcTemplate().queryForObject(sql, new Object[] { userName }, new RowMapper<User>() {
	
				@Override
				public User mapRow(ResultSet rs, int arg1) throws SQLException {
					User user = new User();
			
						user.setPassword(rs.getString("passwd"));
						user.setUserId(rs.getString("userid"));
						user.setUserName(rs.getString("username"));
						user.setPirv(rs.getInt("priv"));
						user.setStat(rs.getInt("stat"));
						user.setSex(rs.getString("sex"));
						user.setEmail(rs.getString("email"));				
					
					return user;
				}			
			});
			
			return user;
		}		
		catch(EmptyResultDataAccessException e)
		{
			e.printStackTrace();
			return null;
	    }*/
		//this.getSession().get(User.class, userName);
	    Criteria c=this.getSession().createCriteria(User.class);
		c.add(Restrictions.eq("userName",userName));//eq是等于，gt是大于，lt是小于,or是或		
		List<User> list=c.list();
		if(list==null||list.size()==0)
			return null;
		else
			return list.get(0);

		
	}
	
	@Override
	public int getContbyUser(String userId)
	{
		 Criteria c=this.getSession().createCriteria(User.class);
		 c.add(Restrictions.eq("userId",userId));//eq是等于，gt是大于，lt是小于,or是或		
		 List<User> list=c.list();
		 if(list==null) return 0;
		 
		 return list.size();
	}
	
	@Override
	public void insertUser(User user)
	{
		
		this.getSession().save(user);
	}
	
	

}
