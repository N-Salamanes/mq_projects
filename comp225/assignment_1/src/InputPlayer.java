import java.util.Scanner;
import java.util.TreeSet;


public class InputPlayer implements Player {

	@Override
	public int chooseNum(TreeSet<Integer> avail) {
		int choice = 0;
		boolean valid = false;
		
		Scanner in = new Scanner(System.in);
		
		while (valid == false){
			System.out.print("Which number do you choose?");
			
			if (in.hasNextInt() == true){
				choice = in.nextInt();
				valid = true;
			}
			else{
				in.next();
			}
		}
		
		return choice;
	}
}
