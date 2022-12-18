import java.util.*;
import java.sql.*;

class Student{
	static void makeDB(){
		
	}
	
	static void insertStudent(){
		
	}
	
	public static void main(String args[]){
		try{
			// Dynamically load JDBC Driver
			Class.forName("oracle.jdbc.driver.OracleDriver");
			
			// Establish connection
			Connection con = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:ORCL", "cs1", "welcome");
			
			// Test a statement
			Statement s = con.createStatement();
			ResultSet res = s.executeQuery("select * from employee");
			
			// Interpret Result
			while(res.next()){
				System.out.println("Tuple");
				System.out.printf("%d %s %d\n", res.getInt(1), res.getString(2), res.getInt(3));
			}
			// Close connection
			con.close();
		}
		catch(Exception e){
			System.out.println("Exception");
			e.printStackTrace();
		}
	}
}