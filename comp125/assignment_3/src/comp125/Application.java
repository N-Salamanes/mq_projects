package comp125;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * @author Nigel Salamanes (43690599) <nigel.salamanes @ students.mq.edu.au>
 * @version 1.0
 * @since 2014-11-08
 */
public class Application {
	
	//internal variables
	static TrackLog myTrackLog;
	static String directory = "";
	static int iSelect = 0;
	static ArrayList<Track> climbs = new ArrayList<Track>();
	static double climbAmount = 0;
	static double distanceThreshold = 0;
	static boolean valid = false;
	
	/**
	 * Our main method which finds climbs in a selected track and then
	 * finds similar/same climbs in other tracks via distance metric. The program will output the results found.
	 * <p>The program prompts the user to input information which is required.</p>
	 * <p>1. The directory where the track files are held.</p>
	 * <p>2. The track number in which to find the climbs as a comparator. The number corresponds
	 * to the position in the TrackLog</p>
	 * <p>3. The minimum amount of elevation required for a climb.</p>
	 * <p>4. The distance metric threshold to compare distances between two climbs. Lower values
	 * are closer to each other while higher values are further apart.</p>
	 * <p>This program assumes that the track files are contained in a folder of the root directory of
	 * this program.</p>
	 * @param args the input arguments when the program is launched.
	 */
	public static void main(String[] args){
		
		//create our keyboard scanner so we can get input from the user
		Scanner keyboard = new Scanner(System.in);
		
		while (!valid){
			try{
				System.out.println("Please enter in a directory:");
				
				//grabs the line entered in by the user
				directory = keyboard.nextLine();
				
				//Create a tracklog with the directory
				myTrackLog = new TrackLog(directory);
				
				//Prints out the list of available tracks
				for (int i = 0; i < myTrackLog.size(); i++){
					System.out.println(i + " : " + myTrackLog.get(i).getFilename());
				}
				
				System.out.println("Please enter number of track to select:");
				iSelect = keyboard.nextInt();
				
				System.out.println("Please enter the minimum amount of elevation gain in km for the tracks:");
				climbAmount = keyboard.nextDouble();
				
				System.out.println("Please enter in the distance metric threshold for finding similar climbs (5 works best): ");
				distanceThreshold = keyboard.nextDouble();
				
				System.out.println("Finding climbs...");
				climbs = myTrackLog.get(iSelect).findClimbs(climbAmount);
				
				valid = true;
			}
			catch (Exception e){
				System.out.println("Invalid input.");
			}
		}
		
		System.out.println("Found " + climbs.size() + " climb(s) matching " + climbAmount + " climb amount.");
		
		//if we actually have any climbs to use as a comparison
		if (climbs.size() != 0){
			System.out.println("Searching for the same climb(s) in other tracks.");
			for (int i = 0; i < myTrackLog.size(); i++){

				//if our iterated i is the same as our selected track, skip it
				//we dont want to be comparing it against itself
				if (i == iSelect){
					continue;
				}
				
				//Counts the amount of similar climbs in each track.
				int iCount = 0;
				
				ArrayList<Track> otherClimbs = myTrackLog.get(i).findClimbs(climbAmount);
				
				System.out.print(myTrackLog.get(i).getFilename());
				
				//go through each climb in our selected track
				for (int j = 0; j < climbs.size(); j++){
					//go through each climb in our currently iterated track
					for (int k = 0; k < otherClimbs.size(); k++){
						
						System.out.print(".");
						
						if (climbs.get(j).distance(otherClimbs.get(k)) < distanceThreshold){
							iCount++;
						}
					}
				}
				
				System.out.println("\nFound " + iCount + " similar climbs in track " + myTrackLog.get(i).getFilename());
			}
		}
		else{
			System.out.println("No climbs were found, exiting.");
		}
		
		System.out.println("Finished finding similar climbs, exiting.");
		//close the keyboard
		keyboard.close();
	}
	
}
