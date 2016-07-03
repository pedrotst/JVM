public class Puppy{

   private int puppyAge;

   public Puppy(int age){
       puppyAge = age;

      // This constructor has one parameter, name.
      //System.out.println("Name chosen is :" + name );
   }

   public void setAge( int age ){
       puppyAge = age;
   }

   public void incAge(int inc){
	puppyAge = puppyAge + 1;
   }

   public void mulAge(int mul){
	puppyAge = puppyAge * mul;
   }

   public int getAge( ){
       //System.out.println("Puppy's age is :" + puppyAge );
       return puppyAge;
   }

   public static void main(String []args){
      /* Object creation */
      Puppy myPuppy = new Puppy( 1);

      /* Call class method to set puppy's age */
      //myPuppy.setAge( 2 );

      /* Call another class method to get puppy's age */
      //myPuppy.getAge( );

      /* You can access instance variable as follows as well */
      System.out.println("Variable Value :" + myPuppy.puppyAge );
   }
}
