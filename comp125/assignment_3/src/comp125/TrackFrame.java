/**
 * 
 */
package comp125;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.HeadlessException;
import java.io.IOException;
import java.util.ArrayList;

import javax.swing.JFrame;

/**
 * @author Nigel Salamanes (43690599) <nigel.salamanes @ students.mq.edu.au>
 * @version 1.0
 * @since 2014-11-09
 */
public class TrackFrame extends JFrame {

	Track track;
	
	/**
	 * @throws HeadlessException
	 */
	public TrackFrame(Track t) throws HeadlessException {
		track = t;
	}

	/*
	 * The paint method is called whenever the window needs 
	 * to be redrawn, for example when it is resized. We just
	 * call the draw method on the track instance.
	 */
	public void paint(Graphics g) {
		
		track.draw(g, getWidth(), getHeight());
	}
	
	
	public static void main(String arg[]) throws IOException, GPSException{

		//Track  track = new Track("data/bobbin-head.csv");
		Track  track = new Track("data/sample.csv");
		
	    TrackFrame frame = new TrackFrame(track);

	    frame.setSize(500,500);

	    // Make the window show on the screen.
	    frame.setVisible(true);  
	    
	  }
}
