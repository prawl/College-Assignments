/* Patrick Rawlings
	CSCI 3310 
	Fall 2011

	Description:
*/

import java.io.*;
import java.util.*;

public class GroceryItem
{
	private int productNum;		// grocery item product number.
	public String description;	// name of grocery item.
	public double price;			// cost of grocery item.
	public char tax;			// F - for food items; N - non-food items.
	public int userProductNum;
	public int amount;	

	// accessor methods
	public int getProductNum() {return productNum;}
	public String getDescription() {return description;}
	public double getPrice() {return price;}
	public char getTax() {return tax;}

//*****************************************************************************

public void readItem (Scanner keyboard)
	{
	productNum = keyboard.nextInt();
	description = keyboard.next();
	price = keyboard.nextDouble();
	tax = keyboard.next().charAt(0);
	keyboard.nextLine();
	} 

//*****************************************************************************
public static void printInventory (GroceryItem [] input, int size)
	{
		for(int i = 0; i < size; i++){
			System.out.println(input[i].productNum +" "+ input[i].description +" "+ 			
			input[i].price +" "+ input[i].tax);
		}//end for
	}

//*****************************************************************************
public static int itemSearch (GroceryItem [] data, int size, int productID)
	{
		for(int index = 0; index < size; index++)
		{  	
			if(data[index].getProductNum() == productID)
			{
				return index;
			}//end if		
		}//end for
	return -1;
	}

//*****************************************************************************
} // end class GroceryItem
