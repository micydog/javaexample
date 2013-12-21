package com.example.db;

import java.util.HashSet;
import java.util.Set;

public class User {
	
	private String userId;
	private String userName;
	private String password;
	private Integer pirv;
	private Integer stat;
	private String sex;
	private String email;
	private Set<UserRole> userRole = new HashSet<UserRole>();;
	
	
	public Set<UserRole> getUserRole() {
		return userRole;
	}
	public void setUserRole(Set<UserRole> userRole) {
		this.userRole = userRole;
	}
	
	public String getUserId() {
		return userId;
	}
	public void setUserId(String userId) {
		this.userId = userId;
	}
	public String getUserName() {
		return userName;
	}
	public void setUserName(String userName) {
		this.userName = userName;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public Integer getPirv() {
		return pirv;
	}
	public void setPirv(Integer pirv) {
		this.pirv = pirv;
	}
	public Integer getStat() {
		return stat;
	}
	public void setStat(Integer stat) {
		this.stat = stat;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	
	

}
