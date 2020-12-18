package comp125;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

/**
 * @author Nigel Salamanes (43690599) <nigel.salamanes @ students.mq.edu.au>
 * @version 1.0
 * @since 2014-11-06 
 */
public class TrackLog { 
    
	//internal variables
	private ArrayList<Track> tracks = new ArrayList<Track>();
    private int ntracks;
    
    /**
     * Default constructor to make an empty TrackLog.
     */
    public TrackLog(){
    	ntracks = 0;
    }
    
    /**
     * Constructor to make a TrackLog from a directory of .csv files.
     * @param directory directory as string of the .csv files.
     * @throws IOException if there is a problem reading the files.
     */
    public TrackLog(String directory) throws IOException  {
        super(); 

        ntracks = 0;
        
        File path = new File(directory);
        File[] fullList = path.listFiles();

        /*
         * for each file in the directory, if the name ends with csv
         * we try to read it into a Track object and store that in
         * our tracks array
         */
        for(int i=0; i<fullList.length; i++) {
            if (fullList[i].toString().endsWith("csv")) {
            	try {
	                Track tr = new Track(fullList[i].toString());
	                add(tr);
            	} catch (GPSException e) {
            		// badly formed track file, just ignore
            	}
            }
        }

    }

    /**
     * Retrieves the amount of tracks.
     * @return the number of tracks.
     */
    public int size() {
    	return ntracks;
    }
    
    /**
     * Adds a track to our list of tracks.
     * @param tr the track being added.
     */
    public void add(Track tr) {
    	tracks.add(tr);
    	ntracks++;
    }

    /**
     * Retrieves the track at the specified index.
     * @param index the index of the track.
     * @return the track.
     */
    public Track get(int index) {
    	if (index < size()){
    		return tracks.get(index);
    	}
    	
    	//if its out of bounds
    	return null;
    }

    /**
     * Outputs the summary of all the tracks stored.  Output results will be
     * in the current order stored in the list.
     * @return summary of all tracks.
     */
    public String toString() {
    	String output = "";
    	
    	for (int i = 0; i < size(); i++){
    		output += tracks.get(i).toString() + "\n";
    	}
    	
    	return output;
    }
    
    /**
     * Sorts the stored tracks in order of ascending distance.
     */
    public void sortDistance() {
    	//ascending order
    	//i being the first element, smallest
        for (int i = 0; i < size(); i++){
        	//j is checking for every element after i and swapping it with i if its smaller
        	for (int j = i + 1; j < size(); j++){
        		if (tracks.get(j).getDistance() < tracks.get(i).getDistance()){
        			Track tempTrack = tracks.get(i);
        			tracks.set(i, tracks.get(j));
        			tracks.set(j, tempTrack);
        		}
        	}
        }
    }
    

    public void sortTimestamp() {
    	//ascending order
    	//i being the first element, smallest
        for (int i = 0; i < ntracks; i++){
        	//j is checking for every element after i and swapping it with i if its smaller
        	for (int j = i + 1; j < ntracks; j++){
        		if (tracks.get(j).getTimestamp().compareTo(tracks.get(i).getTimestamp()) < 0){
        			Track tempTrack = tracks.get(i);
        			tracks.set(i, tracks.get(j));
        			tracks.set(j, tempTrack);
        		}
        	}
        }
    }
    
    public static void main(String args[]) {
        
    }
    
}
