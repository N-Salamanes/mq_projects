package comp125;

import java.awt.Color;
import java.awt.Graphics;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * @author Nigel Salamanes (43690599) <nigel.salamanes @ students.mq.edu.au>
 * @version 1.0
 * @since 2014-11-06 
 */
public class Track {

	//internal variables
	private ArrayList<Waypoint> waypoints = new ArrayList<Waypoint>();
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
    	
    	while (scanner.hasNextLine()){
    		
    		String line = scanner.nextLine();
    		
    		//create a new waypoint with the current line read
    		Waypoint newWaypoint = new Waypoint(line);
    		
    		//add the way point into our arraylist
    		waypoints.add(newWaypoint);

    		trackSize++;
    	}
    	
    	//calculate distance and elevation
    	//minus 1 from the size() otherwise we will get out of bounds access
    	for (int i = 0; i < size() - 1; i++){
    		//if the elevation is greater in the next element in the arraylist
    		//we have positive change in elevation
    		if (waypoints.get(i + 1).getElevation() > waypoints.get(i).getElevation()){
    			elevation += Math.abs(waypoints.get(i + 1).getElevation() - waypoints.get(i).getElevation());
    		}
    		
    		//Lets also calculate the distance between waypoints
    		distance += waypoints.get(i).distanceTo(waypoints.get(i + 1));
    	}
    	
    	scanner.close();
    }
    
	/**
	 * Default constructor to make an empty Track.
	 */
    public Track() {
    	//set the filename to blank since we dont have an input filename
    	myFilename = "";
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
    	waypoints.add(wp);
    	trackSize++;
    	
    	//we need to reset these because we need to re-calculate distance and elevation
    	distance = 0;
    	elevation = 0;

    	//calculate distance and elevation
    	//minus 1 from the size() otherwise we will get out of bounds access
    	for (int i = 0; i < size() - 1; i++){
    		//if the elevation is greater in the next element in the arraylist
    		//we have positive change in elevation
    		if (waypoints.get(i + 1).getElevation() > waypoints.get(i).getElevation()){
    			elevation += Math.abs(waypoints.get(i + 1).getElevation() - waypoints.get(i).getElevation());
    		}
    		
    		//Lets also calculate the distance between waypoints
    		distance += waypoints.get(i).distanceTo(waypoints.get(i + 1));
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
     * Will return empty if the track is empty.
     * @return the timestamp.
     */
    public String getTimestamp() {
    	/*
    	 * If the track is not empty we will return the timestamp in the first waypoint.
    	 * We can hardcore the element as 0.
    	 * Otherwise we will return an empty string.
    	 */
    	
    	try{
    		return waypoints.get(0).getTimestamp();
    	}
    	catch(Exception e){
    		return "";
    	}
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
    		if (wp.distanceTo(waypoints.get(i)) < wp.distanceTo(waypoints.get(closestIndex))){
    			closestIndex = i;
    		}
    	}
    	
    	return waypoints.get(closestIndex);
    }

    /**
     * Function which draws the current track to the window using java graphics.
     * @param g the Graphics class
     * @param width Width of the display window
     * @param height Height of the display window
     */
	public void draw(Graphics g, int width, int height) {

		//some variables to help with coordinate calculations
		final int border = 100;
		int iwidth = width - 2 * border;
		int iheight = height - 2 * border;
		int ileft = border;
		int ibottom = height - border;
		
		//draw a white rectangle
		g.setColor(Color.white);
		g.fillRect(border, border, iwidth, iheight);
		
		//draw a black border
		g.setColor(Color.black);
		g.drawRect(border, border, iwidth, iheight);
					
		//get our min/max values for long/lat.
		double minLon = waypoints.get(0).getLongitude(),
			   maxLon = waypoints.get(0).getLongitude();
		double minLat = waypoints.get(0).getLatitude(),
			   maxLat = waypoints.get(0).getLatitude();
				
		for (int i = 1; i < size(); i++){
			if (waypoints.get(i).getLongitude() < minLon){
				minLon = waypoints.get(i).getLongitude();
			}
			if (waypoints.get(i).getLongitude() > maxLon){
				maxLon = waypoints.get(i).getLongitude();
			}
			if (waypoints.get(i).getLatitude() < minLat){
				minLat = waypoints.get(i).getLatitude();
			}
			if (waypoints.get(i).getLatitude() > maxLat){
				maxLat = waypoints.get(i).getLatitude();
			}
		}
		
		g.setColor(Color.red);
		
		//Draw the lines between the waypoints
		for (int i = 0; i < size() - 1; i++){
			double lon1 = ileft + scale(waypoints.get(i).getLongitude(), minLon, maxLon, 0, iwidth);
			double lat1 = ibottom - scale(waypoints.get(i).getLatitude(), minLat, maxLat, 0, iheight);
			
			double lon2 = ileft + scale(waypoints.get(i + 1).getLongitude(), minLon, maxLon, 0, iwidth);
			double lat2 = ibottom - scale(waypoints.get(i + 1).getLatitude(), minLat, maxLat, 0, iheight);
			
			g.drawLine((int)lon1, (int)lat1, (int)lon2, (int)lat2);
		}
		
		
		//Display the track file name, distance and elevation gain
		g.drawString(getFilename(), (width/2)-40, border-10);
		g.drawString("Distance: " + (int)Math.round(getDistance()) + "km", ileft, ibottom + 20);
		g.drawString("Elevation Gain: " + (int)Math.round(getElevationGain()) + "m", ileft, ibottom + 40);
	}

	/**
	 * Function to scale a value to fit a certain range.
	 * @param valueIn Value being scaled.
	 * @param baseMin Minimum value possible of valueIn.
	 * @param baseMax Maximum value possible of valueIn.
	 * @param limitMin Minimum scaled/range value.
	 * @param limitMax Maximum scaled/range value.
	 * @return The scaled value.
	 */
    public static double scale(final double valueIn, final double baseMin, final double baseMax, final double limitMin, final double limitMax) {
        return ((limitMax - limitMin) * (valueIn - baseMin) / (baseMax - baseMin)) + limitMin;
    }
    
    /**
     * Find all of the climbs over a certain length in this track.
     * <p>To find climbs we go through all the waypoints in the track
     * and find which ones have continuous elevation which meet the
     * minimum length. If the requirement is satisfied we add the
     * climb track to our list of climbs.</p>
     * <p>To calculate if there is elevation between waypoints we check the
     * next iterated waypoint (i + 1) to see if the elevation is either
     * equal to or greater than.  If this is true then there is elevation.
     * Once de-elevation occurs or there are no more waypoints in the track,
     * a check to see the minimum length has been satisfied.  If this is satisfied,
     * then we have a climb track.</p>
     * 
     * @param minlength minimum length in km for any climb
     * @return an ArrayList of Track objects each representing one climb
     */
    public ArrayList<Track> findClimbs(double minlength){
    	
    	//List of climbs which we will return
    	ArrayList<Track> climbs = new ArrayList<Track>();
    	
    	//The climb which will be added to the list of climbs
    	//once completed
    	Track climb = new Track();

    	//distance of the climb
    	double distance = 0;
    	
    	//Lets go through the whole track and find climbs
    	for (int i = 0; i < size() - 1; i++){
    		//Create Waypoint variables for easier access
    		Waypoint wp1 = waypoints.get(i);
    		Waypoint wp2 = waypoints.get(i + 1);
    		
    		if (wp2.getElevation() >= wp1.getElevation()){
    			//We are climbing! (for now)
    			distance += wp1.distanceTo(wp2);

    			//add the waypoints to our climb
    			climb.add(wp1);
    			climb.add(wp2);
    		}
    		else{
    			//Lost elevation, no climb!
    			if (distance >= minlength){
    				//we have a climb reaching minimum requirements
    				//add it to our list of climbs
    				climbs.add(climb);
    			}
    			
				//Reset everything
				climb = new Track();
    			distance = 0;
    		}
    	}

    	//If the track ends on a climb and the minimum specifications are met
		//add it!
		if (distance >= minlength){
			climbs.add(climb);
		}
    	
    	return climbs;
    }
    
    /**
     * Calculate a distance metric between this track and another
     * track. The metric should be zero for identical tracks,
     * small for tracks that are very similar (eg. that overlap a lot)
     * and larger for more distinct tracks.
     * <p>The distance metric is not symmetrical.  Therefore
     * a to b is NOT equal to b to a. With what the formula works with,
     * each point in set A finds its closest point in set B. When doing
     * it the other way around, set B could have a point much further away than
     * any point in set A.  Thus this formula is asymmetric and not
     * symmetrical. </p>
     * <p>In regards to the distance metric between tracks, all points in 
     * track A might be close to track B however not all points in track B
     * are close to track A.</p>
     * @param other the other track to compare with
     * @return a similarity measure
     */
    public double distance(Track other){
    	
    	ArrayList<Double> distances = new ArrayList<Double>();
    	
    	//going through all of waypoints in track A
    	for (int i = 0; i < size(); i++){
    		Waypoint wp_A = waypoints.get(i);
    		
    		//Keep track of the distance
    		double wpDistance = wp_A.distanceTo(other.waypoints.get(0));
    		
    		//going through all of waypoints in track B
    		for (int j = 1; j < other.size(); j++){
    			Waypoint wp_B = other.waypoints.get(j);
    			
    			//keep track of the shortest distance between
    			//A to all of B
    			if (wp_A.distanceTo(wp_B) < wpDistance){
    				wpDistance = wp_A.distanceTo(wp_B);
    			}
    		}
    		
    		//Once we have found the shortest distance of this
    		//A to all of B, add it to our list
    		distances.add(wpDistance);
    	}
    	
    	//Calculate the furthest distance from the shortest distances
    	double largest = 0;
    	for (int i = 0; i < distances.size(); i++){
    		if (distances.get(i) > largest){
    			largest = distances.get(i);
    		}
    	}
    	
    	return largest;
    }
}