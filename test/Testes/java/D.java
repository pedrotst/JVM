class D {
    public static void main(String args[]){
	//Todas instruções de dconst, dstore e dload
	
	System.out.println("\n------dconst_0/dstore_1--------\n");
	double double_0 = 0;
	
	System.out.println("\n------dconst_1/dstore_2--------\n");
	double double_1 = 1;
	
	System.out.println("\n------dstore_3--------\n");
	double double_2 = 2;
	
	System.out.println("\n------dstore--------\n");
	double double_3 = 3;
	double double_4 = 4;
	double double_5 = 5;
	
	System.out.println("\n------dload_1--------\n");
	System.out.println(double_0);
	
	System.out.println("\n------dload_2--------\n");
	System.out.println(double_1);
	
	System.out.println("\n------dload_3--------\n");
	System.out.println(double_2);
	
	System.out.println("\n------dload--------\n");
	System.out.println(double_3);
	System.out.println(double_4);
	System.out.println(double_5);

	
	/**System.out.println("\n------dastore-------\n");
	double vet[] = {100,200,300,400,500};
	
	System.out.println("\n------daload-------\n");
	System.out.println(vet[3]);
	System.out.println(vet[4]);
	System.out.println(vet[0]);**/

    }
}