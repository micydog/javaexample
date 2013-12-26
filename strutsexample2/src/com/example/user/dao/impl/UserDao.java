package com.example.user.dao.impl;

import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.jdbc.core.RowMapper;

import com.example.db.BaseDao;
import com.example.db.User;
import com.example.user.dao.IUserDao;

public class UserDao extends BaseDao implements IUserDao {

	@Override
	public User loadUser(String userName)  {
		
		String sql = "select * from mydocuser where username=?";
		try{
			
			User user =this.getJdbcTemplate().queryForObject(sql, new Object[] { userName }, new RowMapper<User>() {
	
				@Override
				public User mapRow(ResultSet rs, int arg1) throws SQLException {
					User user = new User();
			
						user.setPassword(rs.getString("passwd"));
						user.setUserId(rs.getString("userid"));
						user.setUserName(rs.getString("username"));
						user.setPirv(rs.getString("priv"));
						user.setStat(rs.getString("stat"));
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
	    }
		
	}
	
	

}
