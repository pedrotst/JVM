public class Animal{
    public int age;

    public Animal(){
      
    }
    public Animal(int age){
        this.age = age;
      // This constructor has one parameter, name.
      //System.out.println("Name chosen is :" + name );
   }

   public int getAge( ){
       //System.out.println("Puppy's age is :" + puppyAge );
       return age;
   }
   public void setAge(int age){
       //System.out.println("Puppy's age is :" + puppyAge );
       this.age = age;
   }
}
