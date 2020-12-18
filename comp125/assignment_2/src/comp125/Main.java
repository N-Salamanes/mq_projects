package comp125;

import java.io.IOException;
import java.util.Scanner;

/**
 * @author Nigel Salamanes (43690599) <nigel.salamanes @ students.mq.edu.au>
 * @version 1.0
 * @since 2014-10-16 
 */
public class Main {
	
	//internal variables
	static TrackLog myTrackLog;
	static String directory = "";

	/**
	 * Function which validates the directory being entered by the user.
	 * This is a recursive function.
	 */
	static void UserInput(){
		//init our scanner
		Scanner keyboard = new Scanner(System.in);
		
		System.out.println("Please enter in a directory:");
		
		//grabs the line entered in by the user
		directory = keyboard.nextLine();
		
		try {
			//tests to see if the directory is valid
			myTrackLog = new TrackLog(directory);
		}
		catch (IOException e){
			
		}
		catch (NullPointerException e){
			//directory is not found, call our UserInput again so the user can enter in another directory
			//recursive function
			System.out.println("Error! Directory not found.");
			UserInput();
		}
	}
	
	/**
	 * Main method.  Program starts here.
	 * @param args arguments being passed when program starts.
	 */
	public static void main(String[] args){
		
		//grabs input from user, program will not continue unless a valid directory has been entered
		UserInput();
		System.out.println("'" + directory + "'" + " directory found!");
		
		//print out the details of the tracks sorted in both timestamp and distance
		System.out.println("\nSorting tracks by timestamp:");
		myTrackLog.sortTimestamp();
		System.out.println(myTrackLog.toString());
		
		System.out.println("Sorting tracks by distance:");
		myTrackLog.sortDistance();
		System.out.println(myTrackLog.toString());
	}
}
