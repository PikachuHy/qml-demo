package com.mygdx.game.Net;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class userLoginController {

    public userLoginController(){};

    public boolean Login(String username,String password) throws SQLException{
        Statement sql = DatabaseController.getConnection().createStatement();
        ResultSet rs = sql.executeQuery("select * from admin where username='"
                + username + "'&&password='"
                + password+ "'");
        if (rs.next()) {
            System.out.print("success");
            return true;

        } else{
            System.out.print("fail");
            return false;
        }
    }
}
