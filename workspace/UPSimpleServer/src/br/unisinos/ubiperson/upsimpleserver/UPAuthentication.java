package br.unisinos.ubiperson.upsimpleserver;

import java.sql.*;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.HashMap;

public class UPAuthentication {
	
	Connection conn;
	public final int tokenValidity = 5;
	protected HashMap<Long, Token> tokens = new HashMap<Long, Token>();
	
	
	protected class Token {
		Calendar validUntil;
		long token;
		String user;
		
		public Token(String user)
		{
			this.user = user;
			this.validUntil = new GregorianCalendar();
			this.validUntil.add(GregorianCalendar.MINUTE, tokenValidity);
			this.token = (long)(Math.random() * Long.MAX_VALUE);
		}
	}

	
	public UPAuthentication() throws ClassNotFoundException, SQLException
	{
		/*
		Class.forName("org.sqlite.JDBC");
		conn = DriverManager.getConnection("jdbc:sqlite:ubiperson.db");
		Statement st = conn.createStatement();
		st.execute("create table if not exists users ( " + 
				   "    user string primary key, " +
				   "    password string )");
		*/
	}
	
	public void registerUser(String user, String password) throws Exception
	{
		PreparedStatement st = conn.prepareStatement(
				"INSERT INTO users ( user, password ) VALUES ( ?, ? )");
		st.setString(1, user);
		st.setString(2, password);
		st.execute();
	}
	
	public long authenticate(String user, String password)
	{
		try {
			PreparedStatement pst = conn.prepareStatement(
					"select count(*) c from users where user = ? and password = ?");
			pst.setString(1, user);
			pst.setString(2, password);
			ResultSet rs = pst.executeQuery();
			rs.next();
			if(rs.getInt("c") == 0)
				return 0;
			else
			{
				Token t = new Token(user);
				tokens.put(t.token, t);
				return t.token;
			}
		} catch (SQLException e) {
			e.printStackTrace();
			return 0;
		}
	}
	
}
