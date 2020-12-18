import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.TreeSet;

/**
 * OptimalPlayer derived from Player.
 * This will find the sequence of numbers to choose to obtain the highest score for the player.
 * This will brute-force all possible valid combinations and record the best score with its sequence.
 * @author Nigel
 *
 */
public class OptimalPlayer implements Player {
	
	/**
	 * This function will return true if the selected number is a valid choice, else false.
	 * @param avail TreeSet<Integer> set of available numbers
	 * @param selected integer to check if its a valid choice
	 * @return true/false
	 */
	boolean validChoice(TreeSet<Integer> avail, int selected){
		for (int i : avail){
			//can't have it divide by itself
			if (selected != i){
				if (selected % i == 0){
					//we have found a divisor
					return true;
				}
			}
		}
		//No valid choices
		return false;
	}
	/**
	 * This function will return true if there ARE valid numbers left, else false
	 * @param avail TreeSet<Integer> set of available numbers
	 * @return true/false
	 */
	boolean remaining(TreeSet<Integer> avail){
		
		for (int i : avail){
			for (int j : avail){
				if (i == j){
					break;
				}
				
				if ((i > j) && (i % j == 0)){
					//we have found a valid choice
					return true;
				}
			}
		}
		
		
		
		//there are no remaining valid choices
		return false;
	}
	
	//Keep record of the best possible sequence
	List<Integer> bestChoice = new ArrayList<Integer>();
	int highScore = 0;
	
	//Condition so we find the optimal choice only once
	boolean findOptimal = false;
	
	@Override
	public int chooseNum(TreeSet<Integer> avail) {

		//This will find the numbers to choose for the highest player score
		//This will run once
		if (findOptimal == false){
			List<Integer> choices = new ArrayList<Integer>();
			solve(avail,0,0,choices);
		}
		
		//Get the next number in the sequence and remove it
		int currentChoice = bestChoice.get(0);
		bestChoice.remove(0);
		
		return currentChoice;
	}

	
	
	boolean solve(TreeSet<Integer> _avail, int _player, int _taxman, List<Integer> choices){
		
		//Check if there is any valid choices left
		if (!remaining(_avail)){
			//remove divisors and give taxman numbers
			Iterator<Integer> iter = _avail.iterator();
			
			while (iter.hasNext()){
				_taxman += iter.next();
				iter.remove();
			}
		}
		
		//if the available numbers are empty, the game is over
		//this will be one of many routes
		if (_avail.isEmpty()){
			if (_player > highScore){
				highScore = _player;
				bestChoice.clear();
				bestChoice.addAll(choices);
			}
			return true;
		}
		
		for (int i : _avail){
			//if we have a valid choice
			if (validChoice(_avail, i)){
				//Create copys so we can pass these through
				List<Integer> new_choices = new ArrayList<Integer>();
				new_choices.addAll(choices);
				new_choices.add(i);
				
				TreeSet<Integer> new_avail = new TreeSet<Integer>();
				new_avail.addAll(_avail);
				int new_player = _player;
				int new_taxman = _taxman;
				
				//Increase the players score
				new_player += i;
				
				//Remove the players number
				new_avail.remove(i);
				
				//remove divisors and give taxman numbers
				Iterator<Integer> iter = new_avail.iterator();
				
				while (iter.hasNext()){
					int iterNum = iter.next();
					
					if (i % iterNum == 0){
						new_taxman += iterNum;
						iter.remove();
					}
				}
				
				//Recurse deeper with the new status
				solve(new_avail, new_player, new_taxman, new_choices);
			}
		}
		
		return false;
	}
}
