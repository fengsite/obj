    java.lang.*;
//单利模式

public class Singleton{
    private static Singleton instance;
    private Singleton(){ };
    public static Singleton get(){
        if(instance==null){
            instance=new Singleton();

        }
        return instance; 
            
    }
    
    //原型模式
    interface prototype {
        prototype clone();
    }

    class ConcretePrototype implements prototype{
        private String name;

        public ConcretePrototype (String name){
            this.name = name;

        }
        @Override
        public prototype clone (){
            return new ConcretePrototype(this.name);
        }
        @Override
        public String toString (){
            return new ConcretePrototype[name="+ name + "]";"
        }


    }
       
 
}