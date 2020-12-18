package comp125;

import java.util.Scanner;
/**
 * Template for class containing methods to help ensure the accuracy and
 * security of credit cards.
 * Author: Scott McCallum 2014.
 * 
 * Edited by Nigel Salamanes (43690599)
 * Assignment #1 COMP125
 * 
 * Purpose is to verify credit card numbers
 * Answers to second part are at the bottom of the file
 */

public class CardSecurity {
    
	// Test the methods.
	public static void main(String[] args) {
		
		//Init our scanner so we can grab input from the user
		Scanner keyboard = new Scanner(System.in);
		
		//This is the input string which is grabbed from the user
		String sInput = " ";
		
		//These are the keys which we will be feeding into the algorithms
		int k1 = 3;
		int k2 = 5;
		
		//This is where we grab a card number from the user. A valid card number must be produced 
		while(!isNumeric(sInput)){
			System.out.println("Please enter in a valid card number:");
			sInput = keyboard.nextLine();
		}
				
		System.out.println("Check digit for sInput is " + checkDigit(sInput) + ".");
		
		System.out.println("Encrypt for sInput is " + encrypt(sInput, k1, k2) + ".");
		
		System.out.println("Card sec code for sInput is " + cardSecCode(sInput, k1, k2) + ".");
		
		System.out.println("Decryption for encrypted sInput is " + decrypt(encrypt(sInput, k1, k2), k1, k2));	
		
		//Close our scanner so there is no memory leak
		keyboard.close();
	}
	
	/**
	 * Checks whether or not the given cardNum is a numeric string.
	 * It should return true if every character in the cardNum
	 * is a decimal digit, and false otherwise.
	 */
	public static boolean isNumeric(String cardNum) {
				
		//Goes through each character in our string and checks if it is a number
		//If the character is anything but a number it will return false
		for (int i = 0; i < cardNum.length(); i++){
			if(Character.isDigit((cardNum.charAt(i))) == false){
				return false;
			}
		}
		
		//If it hits here then our string must be numeric
		return true;
	}
	
	/**
	 * Computes and returns check digit for given cardNum.
	 * See Assign 1 description for precise specification.
	 */
	public static int checkDigit(String cardNum) {
		
		//Lets create a char[] so that we can modify individual elements in the string
		char[] chCardNum = cardNum.toCharArray();
			
		//Lets reverse the odd pairs. E.g: 1,3,5,etc
		//Increase by 4 so that we get every odd pair
		for (int i = 0; i < chCardNum.length; i += 4){
			
			//Firstly lets check if there is an element that exists 
			if (i + 1 < chCardNum.length ){

				//Then switch the current element and next element together
				char chTemp = chCardNum[i];
				chCardNum[i] = chCardNum[i + 1];
				chCardNum[i + 1] = chTemp;
			}
		}
		
		//Sum of the pairs added up
		int iSum = 0;
		
		//Go through our array again and add up all the digit pairs
		//+=2 so we go through each pair
		for (int i = 0; i < chCardNum.length; i+=2){
			
			//Lets work with the pairs so we get proper double digits if needed
			int iTempDigits = Character.getNumericValue(chCardNum[i]);
			
			//Lets see if the next element exists in the array
			if (i + 1 < chCardNum.length){
				//If it hits here then that must mean that its a double digit
				//Multiply by 10 first then and the single digit
				iTempDigits *= 10;
				iTempDigits += Character.getNumericValue(chCardNum[i + 1]);
			}
			
			//Add the pair/single digit to our sum
			iSum += iTempDigits;
		}
		
		//Return the check digit which is the total sum of the pairs modulo 10
		return iSum % 10;
	}
	
	/**
	 * Returns encryption of given cardNum using given keys k1, k2.
	 * See Assign 1 description for precise specification.
	 */
	public static String encrypt(String cardNum, int k1, int k2) {
		
		//Strings which hold the encrypted numbers and their hex equivalence
		String cryptogram = "";
	
		//Convert our string to char[] so we can manipulate it
		char[] chCharNum = cardNum.toCharArray();
		
		for (int i = 0; i < chCharNum.length; i++){
			//Lets work with one digit at a time getting the numerical value of it
			int iDigit = Character.getNumericValue(chCharNum[i]);
			
			iDigit *= k1;	//Multiply our digit by key 1
			iDigit += k2;	//Add k2 to our digit
			iDigit %= 10;	//Find the modulo of 10
			
			//Save our converted number in our char[]
			chCharNum[i] = Character.forDigit(iDigit, Character.MAX_RADIX);
		}
						
		//Convert our char[] back to a string and store it in cryptogram
		cryptogram = String.valueOf(chCharNum);
		
		//Returns the encrypted
		return cryptogram;
	}
	
	/**
	 * Computes and returns a card security code for given
	 * card number. See Assign 1 description for precise spec.
	 */
	public static String cardSecCode(String cardNum, int k1, int k2) {
		
		//String which holds the encrypted numbers to hex
		String cryptoHex = "";
				
		//String which holds our CSC
		String CSC = "";
		
		//Integer which counts how many numbers we have stored in our CSC (Max of 3)
		int iCount = 0;
		
		//Lets encrypt our card number
		String myEncString = encrypt(cardNum, k1, k2);
		
		//Convert our encrypted number to hex and store it in a string cryptoHex
		//Long is needed instead of int to hold larger numbers like the one in the example
		//Convert our encrypted string to a long, then convert that long into hex which is stored in a new string cryptoHex
		try {
			cryptoHex = Long.toHexString(Long.parseLong(myEncString));
		}
		catch (NumberFormatException nfe){
			
		}
		
		//Lets go through the encrypted string and find the first 3 digits and store it in CSC
		for (int i = 0; i < cryptoHex.length(); i++){
			if (iCount < 3){
				if (Character.isDigit(cryptoHex.charAt(i)) == true){
					CSC += cryptoHex.charAt(i);
					iCount++;
				}
			}
		}
		
		//Returns CSC
		return CSC;
	}

	/**
	* Returns the decryption of the given cryptogram using the given keys.
	* Precondition: it can be assumed that cryptogram is a valid numeric string,
	* k1 is a valid first encryption key,
	* k2 is a valid second encryption key.
	* Postcondition: the string returned is the decryption of cryptogram
	* using keys k1 and k2, according to the rule outlined
	* in the comments above.
	*/
	public static String decrypt(String cryptogram, int k1, int k2){
				
		//Convert our encrypted string to char[] so we can manipulate it
		char[] encCharArr = cryptogram.toCharArray();
		
		//Go through our whole array and find the decryption of each one
		for (int i = 0; i < encCharArr.length; i++){
			
			//Convert our char digit to an int
			int iEncDigit = Character.getNumericValue(encCharArr[i]);
			
			boolean bFound = false;
			
			//While we haven't found the decrypted digit
			while (bFound == false){
				
				//Check to see if it fits the decryption keys
				if (iEncDigit - k2 >= 0){
					if ((iEncDigit - k2) % k1 == 0){
						iEncDigit = (iEncDigit - k2) / k1;
						
						encCharArr[i] = Character.forDigit(iEncDigit, Character.MAX_RADIX);
						
						bFound = true;
					}
				}
				
				//Increase iEncDigit by 10 so we can test k1, k2 against this new value
				iEncDigit += 10;
			}
		}
		
		return String.valueOf(encCharArr);
	}
}
/**
 * 1. For which keys k1 and k2 having nonnegative integer values less than 10 could
	  we be assured that decryption of encrypted card numbers will always be possible?
	  Try to describe in words the properties of such keys. Provide a concise answer as
	  a comment in your submitted file.
 *
 *	A. For values of k1 and k2 that can be used in decryption, k1 set needs to be an odd number
 *	and not be a factor of 10.  All k2 values between 1 to 9 work in this k1 set.
 *	Therefore k1 = 1,3,7,9 and k2 = 1 to 9.
 *	The reason for the other values in k1 not being able to successfully decrypt the encrypted
 *	number is because of the encryption algorithm.  When using Modulo, you lose the whole number
 *	which is being divided. E.g: 23 % 10 = 3.  You can get the same modulo results E.g: 33 % 10 = 3.
 *	Because of this, odd numbers and non-factors of the modulo are in the set k1.
 *
 * 2. For such keys k1 and k2, how could we perform decryption? Provide a decryption
 * rule D(c) = · · ·, where c denotes the integer value of a digit character of
 * a cryptogram, and D(c) denotes the integer value of the decrypted character.
 * Your decryption rule must satisfy D(E(d)) = d for all integers d. (That is,
 * given integer d, decrypting the encryption of d results in d.) Provide a concise
 * answer as a comment in your submitted file.
 * 
 * A. D(c) = D(E(d))
 * D(c) = for [ (c - k2) % k1 = 0) and c - k2 >= 0, D(c) = (c - k2) / k1]
 * Since we lose a bit of information when we apply modulo to the result in encryption, there is no
 * 100% reverse modulo without conditions.  With this rule applied, we can iterate through the possible
 * reversed modulo results and test to see if it fits the encryption rule reversed.
 * As seen in the previous question, decryption keys work best with prime numbers and numbers which have
 * are not a common factor to the modulo.  This ensures that the same result can not be produced twice for
 * different numbers.
 * 
 * 	 
 * 
*/

