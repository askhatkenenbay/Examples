package kz.epam.webproject;

import java.sql.*;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.Properties;
public class temp {
    public static void main(String[] args){
        String url = "jdbc:mysql://localhost:3306/webproject";
        Properties prop = new Properties();
        prop.put("user","root");
        prop.put("password","Askhat255899");
        prop.put("autoReconnect","true");
        prop.put("characterEncoding","UTF-8");
        prop.put("useUnicode","true");
        prop.put("useSSL","true");
        prop.put("useJDBCCompliantTimezoneShift","true");
        prop.put("useLegacyDatetimeCode","false");
        prop.put("serverTimezone","UTC");
        prop.put("serverSslCert","classpath:server.crt");
        try{
            DriverManager.registerDriver(new com.mysql.cj.jdbc.Driver());
            //Class.forName("com.mysql.cj.jdbc.Driver");
            Connection connection = DriverManager.getConnection(url,prop);
            //Connection connection = DriverManager.getConnection(url,"root","Askhat255899");
            Statement statement = connection.createStatement();

            String sql = "SELECT email FROM infcustomer";
            ResultSet resultSet = statement.executeQuery(sql);
            while(resultSet.next()){
                String str = resultSet.getString(1);
                System.out.println(str);
            }
            connection.close();
        }catch(SQLException e){
            System.out.println(e.getMessage());
        }

        System.out.println("Second phase");
        Connection connection = null;
        Statement statement = null;
        try{
            connection = DriverManager.getConnection(url,prop);
            connection.setAutoCommit(false);
             statement= connection.createStatement();
            statement.addBatch("INSERT INTO infcustomer VALUES('Tommy','tommy@gmail.com','tommy2019','F',NULL)");
            statement.addBatch("INSERT INTO infcustomer VALUES('Billy','billy@gmail.com','billy2019','T',NULL)");
            int[] updateCounts = statement.executeBatch();
            connection.commit();
            System.out.println(Arrays.toString(updateCounts));

        } catch (SQLException e) {
            try {
                connection.rollback();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }finally {
            try{
                if(statement !=null){
                    statement.close();
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
            try{
                if(connection !=null){
                    connection.setAutoCommit(true);
                    connection.close();
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
        System.out.println("I am here");
        try{
            Enumeration<Driver> drivers = DriverManager.getDrivers();
            while(drivers.hasMoreElements()){
                Driver driver = drivers.nextElement();
                DriverManager.deregisterDriver(driver);
            }
        }catch(Exception e){

        }
    }
}
