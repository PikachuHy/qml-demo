package com.coderising.jvm.test;

public class Test {
    public void doStuff(Animal a){
        System.out.println("In the Animal version");
    }
    public void doStuff(Dog h){
        System.out.println("In the Dog version");
    }

    public static void main(String[] args) {
        Test test = new Test();
        Animal dog = new Dog();
        test.doStuff(dog);
    }
}
class Animal{

}
class Dog extends Animal{

}