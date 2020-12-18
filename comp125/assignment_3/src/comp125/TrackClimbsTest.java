package comp125;

import static org.junit.Assert.*;

import java.io.IOException; 
import java.util.ArrayList;

import org.junit.Test;

public class TrackClimbsTest {

 
    
    @Test
    public void test_track_climbs() throws IOException, GPSException {
         
        Track bobbin = new Track("data/bobbin-head2.csv"); 

        // find climbs over 3km
        ArrayList<Track> climbs = bobbin.findClimbs(4.0);
        
        
        // check that there are three climbs in the result
        assertEquals(3, climbs.size());
        
        
        //My tests
        Track tr1 = new Track("data/homebush.csv");
        
        ArrayList<Track> myClimbs = tr1.findClimbs(2);
        
        assertEquals(3, myClimbs.size());
        
        tr1 = new Track("data/offroad.csv");
        
        double distance = 2;
        
        myClimbs = tr1.findClimbs(distance);
        
        assertEquals(5, myClimbs.size());
        
        //Making sure that the distance in each climb meets the requirement
        for (int i = 0; i < myClimbs.size(); i++){
        	assertEquals(true, myClimbs.get(i).getDistance() >= distance);
        }
    }
    
    
    
}
