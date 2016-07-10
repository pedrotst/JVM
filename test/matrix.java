class matrix{
	int a;

	public matrix(int a){
		this.a = a;
	}

	public static void main(String[] args){
		matrix[] m = {new matrix(4), new matrix(2)};

		System.out.println(m[0].a);
		System.out.println(m[1].a);

	}
}
