import java.util.TreeSet;


public class Taxman {
	
	// member attributes
	private int upperLimit;
	private TreeSet<Integer> numbers;
	private int playerScore = 0;
	private int taxmanScore = 0;
		
	/**
	 * The only constructor for Taxman class.
	 * This will set the upper limit and fill the TreeSet.
	 * 
	 * @param n an integer which will be used to set the upper limit
	 */
	public Taxman(int n) {
		//Set the upper limit
		upperLimit = n;
		
		//Init our TreeSet
		numbers = new TreeSet<Integer>();
		
		//Fill our TreeSet
		for (int i = 1; i <= n; i++){
			numbers.add(i);
		}
	}
	
	/**
	 * Returns the upper limit.
	 * @return the integer upperLimit
	 */
	public int getUpperLimit() {
		return upperLimit;
	}
	
	/**
	 * Returns the players score.
	 * @return the integer playerScore
	 */
	public int getPlayerScore() {
		return playerScore;
	}
	
	/**
	 * Returns the taxmans score.
	 * @return the integer taxmanScore
	 */
	public int getTaxmanScore() {
		return taxmanScore;
	}
	
	/**
	 * Creates a deep copy of 'numbers' and returns the newly created set.
	 * @return TreeSet<Integer> availableNumbers
	 */
	public TreeSet<Integer> getAvailableNumbers() {
		//Create a deep copy of numbers
		TreeSet<Integer> availableNumbers = new TreeSet<Integer>();
		availableNumbers.addAll(numbers);
		
		return availableNumbers;
	}
	
	/**
	 * Checks to see whether 'a' has any divisors in the remaining numbers (excluding 'a').
	 * @param a an integer which the player has chosen
	 * @return true/false if 'a' has any remaining divisors
	 */
	public boolean hasDivisorsOf(int a) {
				
		//Go through the available numbers
		for (int i : getAvailableNumbers()){
			//if i is greater than half of our upper limit,
			//there will be no more divisors to check
			if (i > (getUpperLimit() / 2)){
				break;
			}
			
			//Can't have a number divide by itself
			if (a != i){
				//Check if there are any divisors available
				if (a % i == 0){
					//there is at least 1 divisor
					return true;
				}
			}
		}
		
		//No available divisors
		return false;
	}
	
	/**
	 * Condition which controls whether the game is over.
	 * @return true/false, true if game is over/false if not
	 */
	public boolean gameOver() {
		//Go through each remaining number and see if it has a divisor
		for (int i : getAvailableNumbers()){
			for (int j : getAvailableNumbers()){
				if ((i < j) || (j > getUpperLimit() / 2)){
					break;
				}
				if (i != j){
					if (i % j == 0){
						//we have a divisible number
						return false;
					}
				}
			}
		}
		
		//no remaining divisible numbers, game over
		return true;
	}
	
	/**
	 * Remove all the divisors of 'a' in 'numbers' (excluding 'a').
	 * Returns a TreeSet of all the removed numbers
	 * @param a integer number the player has chosen
	 * @return TreeSet<Integer>
	 */
	private TreeSet<Integer> removeDivisorsOf(int a) {
		//Set of removed integers
		TreeSet<Integer> removedNumbers = new TreeSet<Integer>();
		
		for (int i : getAvailableNumbers()){
			//if i is greater than half of our upper limit,
			//there will be no more divisors to check
			if (i > (getUpperLimit() / 2)){
				return removedNumbers;
			}
			
			//We can't remove the given number
			if (a != i){
				//If we have found a divisor, remove it and put it in our temp set
				if (a % i == 0){
					removedNumbers.add(i);
					numbers.remove(i);
				}
			}
		}
		
		return removedNumbers;
	}

	/**
	 * The player chooses the number 'a' from the set.
	 * The taxman will take all divisible numbers of 'a'.
	 * Player and Taxman score will update where necessary.
	 * If the game is over, the taxman will take all remaining numbers.
	 * @param a integer number the player has chosen
	 * @return true/false, true if valid/false if invalid choice
	 */
	public boolean choose(int a) {
		//Valid choice
		if (numbers.contains(a)){
			if (hasDivisorsOf(a) == true){
				//Remove divisors
				TreeSet<Integer> divisors = removeDivisorsOf(a);
				
				//add them to the taxman score
				for (int i : divisors){
					taxmanScore += i;
				}
				
				System.out.println("Taxman collects: " + divisors.toString());
				
				//Remove chosen number
				numbers.remove(a);
				
				//Add chosen number to player score
				playerScore += a;
				
				//Check if its gameover with remaining numbers
				if (gameOver() && (numbers.isEmpty() == false)){
					System.out.println("No remaining numbers have divisors, Taxman collects remaining numbers");
					for (int i : numbers){
						taxmanScore += i;
					}
				}
				return true;
			}
		}
		
		//Not a valid choice
		return false;
	}
	
	/**
	 * A helper function for didsplaying the current game state.
	 */
	public void displayGameState() {
		System.out.print("Remaining nums: ");
		for (int i=0; i<=upperLimit; i++)
			if (numbers.contains(i))
				System.out.print(i + " ");
		
		System.out.println("\nPlayer: " + playerScore + "\n" + "Taxman: " + taxmanScore);
		if (gameOver()){
			System.out.println("Game Over!");
		}
	}
}
