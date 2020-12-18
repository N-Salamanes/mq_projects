package comp125;

import static org.junit.Assert.assertTrue;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

/**
 * @author Nigel Salamanes (43690599) <nigel.salamanes @ students.mq.edu.au>
 * @version 1.0
 * @since 2014-10-14 
 */
public class Track {

	//internal variables
	//create our track which holds a max of 1000 waypoints
	private Waypoint[] waypoints = new Waypoint[1000];
	private String myFilename;
	private int trackSize = 0;
	private double distance = 0;
	private double elevation = 0;
	
	/**
	 * Constructor to make a Track from an input file.
	 * @param filename the filename of the track.
	 * @throws IOException if there is a problem reading a file.
	 * @throws GPSException if there is a problem with the file format.
	 */
    public Track(String filename) throws IOException, GPSException {
    	
    	//save the filename in our internal variable
    	myFilename = filename;
    	
    	//Lets read the file being passed in
    	Scanner scanner = new Scanner(new FileReader(filename));
    	
    	while (scanner.hasNextLine() && trackSize < 1000){
    		
    		String line = scanner.nextLine();
    		
    		///create a new waypoint with the current line read
    		Waypoint newWaypoint = new Waypoint(line);
    		
    		//add the way point into our list
    		waypoints[size()] = newWaypoint;
    		
    		trackSize++;
    	}
    	
    	//calculate distance and elevation
    	//we minus 1 from the size() otherwise we will get out of bounds access
    	for (int i = 0; i < size() - 1; i++){
    		//if the elevation is greater in the next element in the array
    		//we have positive change in elevation
    		if (waypoints[i + 1].getElevation() > waypoints[i].getElevation()){
    			elevation += Math.abs(waypoints[i + 1].getElevation() - waypoints[i].getElevation()); 
    		}
    		
    		//Lets also calculate the distance between waypoints
    		distance += waypoints[i].distanceTo(waypoints[i + 1]);
    	}
    }
    
    /**
     * Retrieves the size of the track.
     * @return the track size.
     */
    public int size() { 
    	return trackSize;
    }
    
    /**
     * Adds a waypoint to the track
     * @param wp the waypoint being added
     */
    public void add(Waypoint wp) {
    	waypoints[size()] = wp;
    	trackSize++;
    	
    	distance = 0;
    	elevation = 0;
    	
    	//calculate distance and elevation
    	//we minus 1 from the size() otherwise we will get out of bounds access
    	for (int i = 0; i < size() - 1; i++){
    		//if the elevation is greater in the next element in the array
    		//we have positive change in elevation
    		if (waypoints[i + 1].getElevation() > waypoints[i].getElevation()){
    			elevation += Math.abs(waypoints[i + 1].getElevation() - waypoints[i].getElevation()); 
    		}
    		
    		//Lets also calculate the distance between waypoints
    		distance += waypoints[i].distanceTo(waypoints[i + 1]);
    	}
    }
    
    /**
     * Retrieves the filename
     * @return the filename
     */
    public String getFilename() {
    	return myFilename;
    }
    
    /**
     * Retrieves the timestamp.
     * The timestamp returned will be the timestamp of the first waypoint in the track.
     * @return the timestamp.
     */
    public String getTimestamp() {
    	/*since we are returning the first timestamp as the first waypoint
    	 * in the track, we can hard code the timestamp position
    	*/ 
    	return waypoints[0].getTimestamp();
    }
    
    /**
     * Retreives the distance of the track.
     * @return the distance.
     */
    public double getDistance() {
    	return distance;
    }

    /**
     * Retrieves the elevation of the track.
     * Elevation is calculated from any positive change between waypoints.
     * @return the elevation.
     */
    public double getElevationGain() {
    	return elevation;
    }
    
    /**
     * Returns a string representation of the track.
     * Contains all summary statistics for the track.
     * @return summary of the track.
     */
    public String toString() {
    	return (getFilename() + ", "+ 
    			getDistance() + ", " +
    			getElevationGain() + ", " +
    			getTimestamp());
    }
    
    /**
     * Calculates the closest waypoint to the given waypoint.
     * @param wp the waypoint given.
     * @return the closest waypoint in the track.
     */
    public Waypoint closestTo(Waypoint wp) {
    	//set our closest waypoint to the first waypoint
    	int closestIndex = 0;
    	
    	//then lets go through all the waypoints and calculate the distance
    	for (int i = 1; i < size(); i++){
    		if (wp.distanceTo(waypoints[i]) < wp.distanceTo(waypoints[closestIndex])){
    			closestIndex = i;
    		}
    	}
    	
    	return waypoints[closestIndex];
    }
}


