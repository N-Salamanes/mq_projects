
package comp125;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;
import java.math.*;

/**
 * @author Nigel Salamanes (43690599) <nigel.salamanes @ students.mq.edu.au>
 * @version 1.0
 * @since 2014-10-13 
 */
public class Waypoint {
   
    // The radius of the Earth in km
    final double R = 6373.0; 
    
    //Internal variables
    private double dLatitude;
    private double dLongitude;
    private double dElevation;
    private String sTimestamp;
    
    /**
     * Retrieves the latitude of the waypoint.
     * @return the latitude.
     */
    public double getLatitude() {
    	return dLatitude;
    }
    
    /**
     * Retrieves the longitude of the waypoint.
     * @return the longitude.
     */
    public double getLongitude() {
    	return dLongitude;
    }

    /**
     * Retrieves the elevation of the waypoint.
     * @return the elevation.
     */
    public double getElevation() {
    	return dElevation;
    }
    
    /**
     * Retrieves the timestamp of the waypoint.
     * @return the timestamp.
     */
    public String getTimestamp() {
    	return sTimestamp;
    }
    
    /**
     * Constructor to make a waypoint from an input string.
     * @param wstring waypoint information being passed as a string.
     * @throws GPSException if a waypoint is not valid.
     */
    public Waypoint(final String wstring) throws GPSException {
    	
    	//Split our passed string into separate elements we need
    	String[] newString = wstring.split(",");
    	
    	//Throw an exception if our new string does not have the right amount of elements
    	if (newString.length != 4){
    		throw new GPSException();
    	}
    	
    	//Try getting the split values and put them in their corresponding variables
    	try{
    		//Since the values should be in correct order we can hard code the element positions
    		sTimestamp = newString[0];
        	dLatitude = Double.parseDouble(newString[1]);
        	dLongitude = Double.parseDouble(newString[2]);
        	dElevation = Double.parseDouble(newString[3]);
    	}
    	catch (Exception e){
    		throw new GPSException();
    	}
    }

    /**
     * Calculates the distance between two waypoints using Haversine formula.
     * @param wp2 the second waypoint to be calculating the distance between.
     * @return the distance between two waypoints.
     */
    public double distanceTo(Waypoint wp2) {

    	//convert our latitude to radians
    	double lat1RAD = Math.toRadians(getLatitude());    	
    	double lat2RAD = Math.toRadians(wp2.getLatitude());
    	
    	//get the difference of longitude/latitude in radians
    	double dlon = Math.toRadians(wp2.getLongitude() - getLongitude());
    	double dlat = Math.toRadians(wp2.getLatitude() - getLatitude());    	
        	
    	//calculate a
    	double a = 
    			Math.pow((Math.sin(dlat/2)), 2) + 
    			Math.cos(lat1RAD) * 
    			Math.cos(lat2RAD) * 
    			Math.pow((Math.sin(dlon/2)), 2);
    	
    	//calculate c
    	double c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
    	
    	//calculate d, R = radius of earth
    	double d = R * c;
    	
    	//return our result
    	return d;
    }
}
