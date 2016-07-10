class matrix{
	public static void main(String[] args){
		float[][][] m = new float[2][2][3];
		short[] s = {2, 5};

		m[0][0][1] = 20;
		s[1] = 10;
		System.out.print(m[0][0][1] + s[1]);
		//System.out.println(s[1]);

	}
}
