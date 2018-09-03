/*	Patrick Rawlings
	CSCI 3310 Section 1
	Fall 2011
	Program 3
	10/27/11
	
	Information: See DiskSim.java for details on programming assignment.
*/
// ****************************************************
// Reference-based implementation of ADT list using arrays.
// Due to the limitations with array of generics, the
// "data type" for the list items is fixed to be of type
// SectorUsage.  Any program using this class must specify
// <SectorUsage> as the value for the type parameter.
// ****************************************************
public class List<T> {
  // reference to linked list of items

  public static final int MAX_LIST = 20;
  public static final int NULL = -1;
  
  private SectorUsage item[] = new SectorUsage[MAX_LIST];  // data
  private int      next[] = new int[MAX_LIST];       // pointer to next item

  private int head;     // pointer to front of list
  private int free;     // pointer to front of free list
  private int numItems; // number of items in list

// Constructor must initialize used list to empty and free list to 
// all available nodes.
//******************************************************************************
 public List() {
   
	 int index;
    for (index = 0; index < MAX_LIST-1; index++)
      next[index] = index + 1;
    
    next[MAX_LIST-1] = NULL;

    numItems = 0;
    head = NULL;
    free = 0;
  
 }// end default constructor
//******************************************************************************
 public void removeAll() {   // reinitialize all nodes to free
    
	int index;
    for (index = 0; index < MAX_LIST-1; index++)
      next[index] = index + 1;
    
    next[MAX_LIST-1] = NULL;

    numItems = 0;
    head = NULL;
    free = 0;
  
 }// end removeAll
//******************************************************************************
//public boolean isEmpty() returns 0 if the linked list is empty.
public boolean isEmpty() { 
	
	return (numItems == 0);
  
}  // end isEmpty
//******************************************************************************
//public int size() retruns the size of a linked list.  
 public int size() { 
	
	return numItems;
 
 }// end size
//******************************************************************************
//private int find(int index) returns the item of the specified index in a linked
//list.  No error checking.
 private int find(int index) { 
	
	int currentrent = head;	
	for(int i = 1; i < index; i++){
	currentrent = next[currentrent];
	}//end for
	return currentrent;
															
 }// end find
//******************************************************************************
//public SectorUsage get(int index) returns a specific item in a linked list
//based upon the input of the index.  The function error checks if the index
//is out of bounds by returning a null.
 public SectorUsage get(int index) {		
		
	if(index >= 1 && index <= numItems){// Within specified range! :)
	int result = find(index);
	SectorUsage data = item[result];
	return data;
	}//end if
	else{// Outside specified range. :(
	return null;
	}//end else

 }// end get
//******************************************************************************
//public void add(int index, SectorUsage newItem) adds an item to a linked list
//based upon the input of the index and the newItem of type SectorUsage. The
//function error checks if the number of item exceeds the memory & if the
//index is out of bounds on add.
public void add(int index, SectorUsage newItem) {
	

  if(numItems >= MAX_LIST){// Exceeded max size! :(
  System.out.println("Error! Exceeded the max size of the list in add!");
  }//end if

  if(index >= 1 && index <= numItems+1){// Within specified range! :)
  int prev = find(index - 1);
  int cur = find(index);
  int i = free;
  free = next[free];


   if (index != 1){// Add new item on the list.
	next[i] = next[prev];//Make new point at prev's next.
	next[prev] = i;      //Make prev point at new item.
	}//end if
	else{ 			 // Add new item on the front of the list.
	next[i] = head; // Make the new item point to the first item.
	head = i;       // Make head point at the new item.
	}//end else
	
	item[i] = newItem;// Update newItem
	numItems++;
 
  }//end if
  else{//Outside of specified rage! :(
  System.out.println("Error! Index out of bounds on add!");
  }//end else

 }// end add
//******************************************************************************
//public void remove(int index) removes an item out of a linkedlist based upon 
//the input of index of the given item.  It handles adding items to the front
//middle and back of the list.  The function has error checking to determine
//if the item is in bounds.
 public void remove(int index) {  
 
  int prev = find(index - 1);
  int cur = find(index);
  if (index >= 1 && index <= numItems+1){// Within specified range! :)
    
	 if (index != 1){ // Remove item on list.
	 cur = next[prev];
	 next[prev] = next[next[prev]];	    
    }//end if
	 else {// Remove first item on list.
	 cur = head;			// Make cur point to head
	 head = next[head];	// Skip item to remove.
	}//end else
	 numItems--;
	 item[cur] = null;   // Set end to null
	 next[cur] = free;	// Set to free list
	 free = cur;			// Set to cur.

  }// end if
  else{//Outside of specified range! :(
  System.out.println("Error! Index out of bounds on remove!");
  }//end else

 }// end remove*/
//******************************************************************************
} // end List

