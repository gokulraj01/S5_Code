import java.sql.*;
import java.util.Scanner;

class Student{
	Connection con;
	void makeDB(){
		try{
			// Check if table exists, else create table
			Statement s;
			DatabaseMetaData met = this.con.getMetaData();
			ResultSet res = met.getTables(null, null, "student", null);
			if(res.next())
				System.out.println("Student table exists!!");
			else{
				s = this.con.createStatement();
				s.executeQuery("CREATE TABLE student(name VARCHAR(20) PRIMARY KEY, mark INT)");
				System.out.println("Student table created!!");
			}
		} catch(Exception e){}
	}
	
	void insertStudent(String name, int mark){
		try{	
			PreparedStatement s = this.con.prepareStatement("INSERT INTO student VALUES (?, ?)");
			s.setString(1, name);
			s.setInt(2, mark);
			s.executeUpdate();
		} catch (Exception e){}
	}
	
	void rankList(){
		try{
			// Test a statement
			Statement s = this.con.createStatement();
			ResultSet res = s.executeQuery("select * from student order by mark");
			
			int i = 1;
			System.out.println("Rank\tName\tMark");
			// Interpret Result
			while(res.next())
				System.out.printf("%d\t%s\t%d\n", i++, res.getString(1), res.getInt(2));
		} catch(Exception e){}
	}
	
	public static void main(String args[]){
		try{
			// Dynamically load JDBC Driver
			Class.forName("oracle.jdbc.driver.OracleDriver");
			
			Student std = new Student();
			
			// Establish connection
			std.con = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:ORCL", "cs1", "welcome");
			
			// Initialize Student Table
			std.makeDB();
			
			Scanner s = new Scanner(System.in);
			System.out.print("No: of students: ");
			int n = s.nextInt();
			for(int i=0; i<n; i++){
				System.out.println("Student "+(i+1));
				System.out.print("Name: ");
				s.next();
				String name = s.nextLine();
				System.out.print("Mark: ");
				int mark = s.nextInt();
				System.out.println(name + " " + mark);
				std.insertStudent(name, mark);
			}
			
			// Show rank list
			std.rankList();
			
			// Close connection
			std.con.close();
		}
		catch(Exception e){
			System.out.println("Exception");
			e.printStackTrace();
		}
	}
}