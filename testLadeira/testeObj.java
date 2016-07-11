class testeObj{
	int numi=1;
	long numl=2;
	float numf=3.0F;
	double numd=4.0;
	byte numb=12;
	char c = 'a';
	short nums = 10;
	boolean b = true;
	objeto o;
	int array_i[] = {1, 2, 3};

	testeObj(){
		o = new objeto(1, 2);
		System.out.println("Numero inteiro");
		System.out.println(numi);
		System.out.println("Numero long");
		System.out.println(numl);
		System.out.println("Numero ponto flutuante");
		System.out.println(numf);
		System.out.println("Numero precisao dupla");
		System.out.println(numd);
		System.out.println("Byte");
		System.out.println(numb);
		System.out.println("Char");
		System.out.println(c);
		System.out.println("Short");
		System.out.println(nums);
		System.out.println("Boolean");
		System.out.println(b);
		System.out.println("int dentro do objeto o");
		System.out.println(o.get_a());
		System.out.println("Array 1, 2, 3 ?");
		System.out.println(array_i[1]);

	}
}