import java.io.*;
import java.util.*;

public class test {

private static int search(int a, int b, int n) {
int returnValue;

	int mid = (a+b)/2;
	System.out.printf("Enter: a = %2d, b = %2d, mid = %2d\n", a, b, mid);

	if((mid*mid <= n) && (n < (mid+1) * (mid+1))) {
	returnValue = mid;
	}
	else if (mid * mid > n){
	returnValue = search(a, mid-1, n);
	}
	else{
	returnValue = search(mid+1, b ,n);
	}
	System.out.printf("Leave: a = %2d, b = %2d, mid = %2d\n", a, b, mid);
	return returnValue;
}

public static void main (String[] args){
int n = 100;
System.out.printf("For n = %2d, the result is %d\n", n, search(1 , n, n));
}
}
