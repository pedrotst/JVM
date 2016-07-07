class Instrucoes_109_141 {
    public static void main(String args[]){
	int int_a = 100;
	int int_b = -20434;
	int int_c = -320;
	
	long long_a = 1000000;
	long long_b = -2000;
	long long_c = -32012321;
	
	float float_a = 3.45f;
	float float_b = -5.73f;
	float float_c = -64242.56f;
	
	double double_a=3.45054;
	double double_b=-100.542;
	double double_c=-41342242242.777;
	
	//ldiv
	System.out.println("\n------ldiv--------\n");
	System.out.println(long_a/10);
	System.out.println(long_b/30);
	System.out.println(long_b/-30);
	System.out.println(long_c/long_a);
	
	//fdiv
	System.out.println("\n------fdiv--------\n");
	System.out.println(float_a/-1);
	System.out.println(float_a/3);
	System.out.println(float_b/-2);
	System.out.println(float_b/-float_b);
	System.out.println(float_c/-float_b);
	
	//ddiv
	System.out.println("\n------ddiv--------\n");
	System.out.println(double_a/-1);
	System.out.println(double_a/3);
	System.out.println(double_b/-2);
	System.out.println(double_b/-double_b);
	System.out.println(double_c/-double_a);
	
	//irem
	System.out.println("\n------irem--------\n");
	System.out.println(int_a%1);
	System.out.println(int_a%17);
	System.out.println(int_b%-2);
	System.out.println(int_b%int_b);
	System.out.println(int_c%int_a);
	
	//lrem
	System.out.println("\n------lrem--------\n");
	System.out.println(long_a%100002212);
	System.out.println(long_a%10903927);
	System.out.println(long_b%-200000);
	System.out.println(long_b%long_b);
	System.out.println(long_c%777777777);
	
	//frem
	System.out.println("\n------frem--------\n");
	System.out.println(float_a%153.23);
	System.out.println(float_a%17);
	System.out.println(float_b%-2.432);
	System.out.println(float_b%float_b);
	System.out.println(float_c%3503);
	
	//drem
	System.out.println("\n------drem--------\n");
	System.out.println(double_a%153.23);
	System.out.println(double_a%17);
	System.out.println(double_b%-2.432);
	System.out.println(double_b%double_b);
	System.out.println(double_c%76787);
	
	//ineg
	System.out.println("\n------ineg--------\n");
	System.out.println(-int_a);
	System.out.println(-int_b);
	System.out.println(-int_c);
	
	//lneg
	System.out.println("\n------lneg--------\n");
	System.out.println(-long_a);
	System.out.println(-long_b);
	System.out.println(-long_c);
	
	//fneg
	System.out.println("\n------fneg--------\n");
	System.out.println(-float_a);
	System.out.println(-float_b);
	System.out.println(-float_c);
	
	//dneg
	System.out.println("\n------dneg--------\n");
	System.out.println(-double_a);
	System.out.println(-double_b);
	System.out.println(-double_c);
	
	//ishl
	System.out.println("\n------ishl--------\n");
	System.out.println(int_a<<4);
	System.out.println(int_b<<8);
	System.out.println(int_b<<5);
	System.out.println(int_c<<int_a);
	
	//lshl
	System.out.println("\n------lshl--------\n");
	System.out.println(long_a<<4);
	System.out.println(long_b<<8);
	System.out.println(long_b<<3);
	System.out.println(long_c<<7);
	
	
	 //ishr
	System.out.println("\n------ishr--------\n");
	System.out.println(int_a>>4);
	System.out.println(int_b>>8);
	System.out.println(int_b>>5);
	System.out.println(int_c>>3);
	
	//lshr
	System.out.println("\n------lshr--------\n");
	System.out.println(long_a>>4);
	System.out.println(long_b>>8);
	System.out.println(long_b>>3);
	System.out.println(long_b>>9);
	
	
	//iushr
	System.out.println("\n------iushr--------\n");
	System.out.println(int_a>>>4);
	System.out.println(int_b>>>8);
	System.out.println(int_b>>>5);
	System.out.println(int_c>>>5);
	
	
	//lushr
	System.out.println("\n------lushr--------\n");
	System.out.println(long_a>>>4);
	System.out.println(long_b>>>8);
	System.out.println(long_b>>>3);
	System.out.println(long_c>>>2);
	
	
	//iand
	System.out.println("\n------iand--------\n");
	System.out.println(int_a&4);
	System.out.println(int_b&8);
	System.out.println(int_b&(-5));
	System.out.println(int_c&int_b);
	
	
	//land
	System.out.println("\n------land--------\n");
	System.out.println(long_a&4);
	System.out.println(long_b&8);
	System.out.println(long_b&3);
	System.out.println(long_b&long_a);
	System.out.println(long_b&long_a&long_c);
	
	//ior
	System.out.println("\n------ior--------\n");
	System.out.println(int_a|4);
	System.out.println(int_b|8);
	System.out.println(int_b|(-5));
	System.out.println(int_b|int_a);
	System.out.println(int_b|int_a|int_c);
	
	//lor
	System.out.println("\n------lor--------\n");
	System.out.println(long_a|4);
	System.out.println(long_b|8);
	System.out.println(long_b|3);
	System.out.println(long_b|long_a);
	System.out.println(long_b|long_a|long_c);
	
	//ixor
	System.out.println("\n------ixor--------\n");
	System.out.println(int_a^4);
	System.out.println(int_b^8);
	System.out.println(int_b^(-5));
	System.out.println(int_b^int_a);
	System.out.println(int_b^int_a^int_c);
	
	
	//lxor
	System.out.println("\n------lxor--------\n");
	System.out.println(long_a^4);
	System.out.println(long_b^8);
	System.out.println(long_b^3);
	System.out.println(long_b^long_a);
	System.out.println(long_b^long_a^long_c);
	
	
	//iinc
	System.out.println("\n------iinc--------\n");
	System.out.println(int_a+=4);
	System.out.println(int_b+=8);
	System.out.println(int_b+=(-5));
	System.out.println(int_a+=(-4));
	System.out.println(int_c+=278);
	
	
	//i2l
	System.out.println("\n------i2l--------\n");
	System.out.println(int_a&long_a);
	System.out.println(int_b&long_b);
	System.out.println(int_c&long_c);
	
	
	//i2f
	System.out.println("\n------i2f--------\n");
	System.out.println(int_a/float_a);
	System.out.println(int_b/float_b);
	System.out.println(int_c/float_c);
	
	
	//i2d
	System.out.println("\n------i2d--------\n");
	System.out.println(int_a/double_a);
	System.out.println(int_b/double_b);
	System.out.println(int_c/double_c);
	
	
	//l2i
	System.out.println("\n------l2i--------\n");
	System.out.println((int)long_a);
	System.out.println((int)long_b);
	System.out.println((int)long_c);
	
	
	//l2f
	System.out.println("\n------l2f--------\n");
	System.out.println((float)long_a);
	System.out.println((float)long_b);
	System.out.println((float)long_c);
	
	
	//l2d
	System.out.println("\n------l2d--------\n");
	System.out.println((double)long_a);
	System.out.println((double)long_b);
	System.out.println((double)long_c);
	
	
	//f2i
	System.out.println("\n------f2i--------\n");
	System.out.println((int)float_a);
	System.out.println((int)float_b);
	System.out.println((int)float_c);
	
	
	//f2l
	System.out.println("\n------f2l--------\n");
	System.out.println((long)float_a);
	System.out.println((long)float_b);
	System.out.println((long)float_c);
	
	
	//f2d
	System.out.println("\n------f2d--------\n");
	System.out.println(float_a/double_a);
	System.out.println(float_b/double_b);
	System.out.println(float_c/double_c);
	
    }
}