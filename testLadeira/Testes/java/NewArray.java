public class NewArray {


	public static void main(String args[]) {
		byte b[] = {0x00,0x01,0x02};
		char c[] = {'a','b','c','d'};
		short s[] = {1,2,3,4,5};
		int i[] = {6,7,8,9,10,11};
		long l[] = {1000000,200000,300000,4000000};
		float f[] = {1.23f,4.56f,7.89f};
		double d[] = {1.23,4.56,7.89,10.11};
		int vazio[] = new int[5];
		
		System.out.println("Byte");
		System.out.println(b[0]);
		System.out.println(b[1]);
		System.out.println(b[2]);
		
		System.out.println("\nChar");
		System.out.println(c[0]);
		System.out.println(c[1]);
		System.out.println(c[2]);
		System.out.println(c[3]);
		
		System.out.println("\nShort");
		System.out.println(s[0]);
		System.out.println(s[1]);
		System.out.println(s[2]);
		System.out.println(s[3]);
		System.out.println(s[4]);
		
		System.out.println("\nInt");
		System.out.println(i[0]);
		System.out.println(i[1]);
		System.out.println(i[2]);
		System.out.println(i[3]);
		System.out.println(i[4]);
		System.out.println(i[5]);
		
		System.out.println("\nLong");
		System.out.println(l[0]);
		System.out.println(l[1]);
		System.out.println(l[2]);
		System.out.println(l[3]);
		
		System.out.println("\nFloat");
		System.out.println(f[0]);
		System.out.println(f[1]);
		System.out.println(f[2]);
		
		System.out.println("\nDouble");
		System.out.println(d[0]);
		System.out.println(d[1]);
		System.out.println(d[2]);
		
		System.out.println("\nvazio");
		System.out.println(vazio[0]);
		System.out.println(vazio[1]);
		System.out.println(vazio[2]);
	}
	
	

}