package com.mygdx.game.Net;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseController {

    static Connection connection;
    static boolean mark=false;

    DatabaseController() {
        try {
            Class.forName("com.mysql.jdbc.Driver");
        }
        catch (ClassNotFoundException e) {
            System.out.println( "Error" + e );
        }
        String url = "jdbc:mysql://localhost:3306/javagame";
        String user = "root";
        String password = "090702";
        try {
            connection = DriverManager.getConnection(url, user, password);
        }
        catch (SQLException e) {
            e.printStackTrace();
        }
        mark=true;
    }

    static public void closeDB() {
        try {
            connection.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    static public Connection getConnection() {
        if(mark)
            return connection;
        else
        {
            new DatabaseController();
            return getConnection();
        }
    }

}
