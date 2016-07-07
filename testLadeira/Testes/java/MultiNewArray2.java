public class MultiNewArray2 {


	public static void main(String args[]) {
		char c[][][] = new char[3][3][3];
		
		c[0][0][0] = 'a';
		c[0][2][2] = 'b';
		c[2][2][1] = 'c';
		c[4][3][3] = 'c';
		
		System.out.println(c[0][0][0]);
		System.out.println(c[0][2][2]);
		System.out.println(c[2][2][1]);
		System.out.println(c[0][3][2]);
	}
	
	

}