package com.example.db.intercep;

import java.util.Map;

import com.example.LoginAction;
import com.opensymphony.xwork2.Action;
import com.opensymphony.xwork2.ActionInvocation;
import com.opensymphony.xwork2.interceptor.AbstractInterceptor;

public class NameTransInterceptor extends AbstractInterceptor {

	@Override
	public String intercept(ActionInvocation invocation) throws Exception {
		
		Map map = invocation.getInvocationContext().getParameters();
		Object sex = map.get("user.sex");
	
		if(sex instanceof String[])
		{
			if(((String[])sex)[0].equals("Ů"))
			{
				map.put("user.sex", "F");
				invocation.getInvocationContext().setParameters(map);
			}
			
			else
			{
				map.put("user.sex", "M");
				invocation.getInvocationContext().setParameters(map);
			}
		}
		String result = null;
		result = invocation.invoke();
		
		
		
		return result;
	}

}
