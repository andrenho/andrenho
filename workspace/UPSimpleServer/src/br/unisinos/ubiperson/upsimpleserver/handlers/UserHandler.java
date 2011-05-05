package br.unisinos.ubiperson.upsimpleserver.handlers;

import java.io.IOException;
import java.io.InputStream;

import br.unisinos.ubiperson.command.UserXMLCommand;
import br.unisinos.ubiperson.upsimpleserver.UPAuthentication;

import com.sun.net.httpserver.HttpExchange;

public class UserHandler extends BasicHandler {
	
	protected UPAuthentication auth;
	
	public UserHandler(UPAuthentication auth)
	{
		this.auth = auth;
	}

	@Override
	public void handle(HttpExchange t) throws IOException {
		String method = t.getRequestMethod();

		if(method.equals("POST"))
		{
			InputStream is = t.getRequestBody();
			try {
				UserXMLCommand user = UserXMLCommand.parse(is);
				auth.registerUser(user.name, user.password);
				sendReply(t, 200, "Success");
			} catch (Exception e) {
				e.printStackTrace();
				sendReply(t, 400, e.getMessage());
			}
		}
		else
			sendReply(t, 405, "Method " + method + " not allowed.");
	}

}
