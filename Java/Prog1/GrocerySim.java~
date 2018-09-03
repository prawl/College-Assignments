/*
	Patrick Rawlings
	CSCI 3310 Section 1
	Fall 2011
	Program 1
	9/15/11

	Description: GrocerySim.java is a program meant to simulate a grocery store
	checkout system.  This program uses a class called GroceryItem.java which	
	must be complied along with GrocerySim.(To compile: javac GrocerySim.java 
	GroceryItem.java).  The program takes in the files and calculates the 
	subtotal, tax and total for each customer based on the items purchased.


	I/O format: The program reads in the inventory for the grocery store from an
	text file named inventory.dat (No input cmd necessary just make sure that 
	this file is created and in the same directory as the .java files)
	and stores the items into a GroceryItem.
	See GroceryItem.java for the contents of the GroceryItem and the format for 
	the text file.  Next, the program takes in another text file named 
	purchases.dat in the format of (java GrocerySim.java < purchases.dat) this 
	file is simulating what customers are buying with 0  0 signifying the next
	customer and end of file (File must end with 0 0 to end properly.)  The 
	program will then output the item within the purchases.dat in a formatted
	output.
	
	Error Handling: 
	1) If <product number> is not the inventory file an error message will be 
	outputted and the item will be skipped.
	2) If a duplicate item exists an error message will be outputted and the
	 duplicate entry will be skipped.
	3)<times> not in the specified rage.  An error message will print to the 
	reciept and ignore the line. ****

	ASSUMPTIONS:We are assuming that the inventory list will not be larger than
	100 items (small store).
*/
//*****************************************************************************	

import java.io.*;
import java.util.*;


public class GrocerySim
{
public static final int MAXINVENTORY = 100; // maximum # of item in inventory.

public static void main (String[] args){
	
	Scanner keyboard;
	GroceryItem[] data;

try {
		keyboard = new Scanner(new File("inventory.dat"));
		data = new GroceryItem[MAXINVENTORY];
	 }//end try
	catch(Exception e)
	{
		System.out.println("Error! File not found!");	
		return;
	}//end catch

	int amount; 				// # of items the user purchases.
	int productID;				// ID number for the products on the inventory.dat.
	int customer = 1;			// How many customers were registered in output.
	int curItem = 0;			// Counter for GroceryItem data[].
	boolean dupError = false;// Error flag for a duplicate item in invy. 
	int index;					// Index for data[] in item search.
	double subTotal = 0;		
	double taxAmt = 0;		
	double grandTotal;		
	String stringSubTotal = "Subtotal"; // For formatted output.
	String stringTax = "Tax";				// For formatted output.
	String stringTotal = "Total";			// For formatted output.
	
	while (keyboard.hasNext())// Reads the content of the text file.
	{ 
		data[curItem] = new GroceryItem(); 
		data[curItem].readItem(keyboard);//Stores one item into data.
		curItem++;
	}//end while
	
	
		for(int i = 0; i < curItem; i++)
		{
			for(int i2 = i+1; i2 < curItem; i2++)
			{
//System.out.println("Debug: Comparing data[i] = " + i + " to data[i2] " + i2);
				if (data[i].getProductNum() == data[i2].getProductNum())
				{
//System.out.println("Debug:INSIDE Comparing data[i] = "+i+ " to data[i2] "+i2);
				 dupError = true;
				}//end if	
			}//end for
		}//end for
	
	if (dupError == true) // Duplicate items exist.
	{
	System.out.println("Error! Duplicate item(s) dectected in inventory"
				 + " file! The duplicate item(s) will be ignored.\n");
	GroceryItem.printInventory(data, curItem);
	System.out.println("");
	}//end if
	
//GroceryItem.printInventory(data, curItem);// Debug Prints out the inventory.
	Scanner kbd = new Scanner(System.in);// New scanner for user input.
	System.out.println("Customer " + customer);
	
	while (kbd.hasNextInt())
	{	
		productID = kbd.nextInt();	
		amount = kbd.nextInt();
//	System.out.println("Debug: Step 1: Starting to read line. productID = " 
//+ productID + " amount " + amount);	

//System.out.println("AMOUNT = " + amount);
	if((amount > 100) || (amount < 0) )
	{
	System.out.println("\n\nError! " + amount + " is not within the specified" +
	 " range (1-100)");
	}
	else
	{


		if(productID != 0 || amount != 0) // Not done
		{
			index = GroceryItem.itemSearch(data, curItem, productID);			
//	System.out.println("Debug:Step 2: Item is not 0, 0.  Keep going!  productID 
//= " + productID + " amount " + amount);			
			
			if(index == -1) // Not in the  inventory
			{
				System.out.printf("\n*** item %d not in inventory***", productID);	 
			}//end if
			else // Is in the inventory
			{	
//	System.out.println("Debug: Step 3: Item is in the inventory! 
//productID = " + productID + " amount " + amount);
				double itemTotal = data[index].getPrice() * amount;
				System.out.printf("\n%13s  %d  @ %.2f %6.2f %s",
				data[index].getDescription(),amount, data[index].getPrice(), 
				itemTotal,data[index].getTax());
				subTotal += itemTotal; // Calculate subtotal
//	System.out.println("Debug: Step 4: Start calculating tax! Doing good! 
// productID = " + productID + " amount 			" + amount);
				if (data[index].getTax() == 'N') // Tax is .08
				{
					taxAmt += itemTotal * .08;
//System.out.printf("Debug: taxAmt with a N or .08 is = %.2f\n",  taxAmt);
				}//end if		
				else
				{
					taxAmt +=  itemTotal * .02;
//System.out.printf("Debug: taxAmt with a F or .02 is = %.2f\n ", taxAmt);
				}//end else			
			}//end else
			
//System.out.println("Debug:Step 5: Finished with 1 item in the invy, moving on 
// productID = " + productID + " amount " + amount);
			
		}//end if
					
//System.out.println("Debug: Step 6: Entering in next productID and amount.  
//Should start over...  productID = " + productID + " amount " + amount);
	
		else
		{ 
		customer++;
		grandTotal = subTotal + taxAmt;
		System.out.printf("\n\n%13s  %16.2f\n", stringSubTotal, subTotal);			
		System.out.printf("%13s  %16.2f\n", stringTax, taxAmt);		
		System.out.printf("\n%13s  %16.2f\n", stringTotal, grandTotal);
		subTotal = taxAmt = grandTotal = 0;
			if(kbd.hasNext() == true) // Another customer exist.
			{
			System.out.println("Customer " + customer);			
			}//end if		
		}//end else	
	
	}//end else
	
}//end while
}// end main
}// end GrocerySim
//******************************************************************************
