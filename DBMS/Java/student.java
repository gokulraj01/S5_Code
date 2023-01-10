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
	
	void updateMark(String name, int mark){
		try{
			PreparedStatement s = this.con.prepareStatement("UPDATE student SET mark=? WHERE name=?");
			s.setInt(1, mark);
			s.setString(2, name);
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
		String name;
		int mark;
		try{
			// Dynamically load JDBC Driver
			Class.forName("oracle.jdbc.driver.OracleDriver");
			
			Student std = new Student();
			
			// Establish connection
			std.con = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:ORCL", "cs1", "welcome");
			
			// Initialize Student Table
			std.makeDB();
			
			Scanner s = new Scanner(System.in);
			while(true){
				System.out.println("Options\n[1] Add Student\t[2] Update Mark\n[3] Show Ranklist\t[4] Exit");
				int c = s.nextInt();
				switch(c){
					case 1:
						System.out.print("Name: ");
						s.next();
						name = s.nextLine();
						System.out.print("Mark: ");
						mark = s.nextInt();
						std.insertStudent(name, mark);
						break;
					case 2:
						System.out.print("Name: ");
						s.next();
						name = s.nextLine();
						System.out.print("New Mark: ");
						mark = s.nextInt();
						std.insertStudent(name, mark);
						break;
					case 3:
						std.rankList();
						break;
				}
				if(c == 4) break;
			}
			// Close connection
			s.close();
			std.con.close();
		}
		catch(Exception e){
			System.out.println("Exception");
			e.printStackTrace();
		}
	}
}