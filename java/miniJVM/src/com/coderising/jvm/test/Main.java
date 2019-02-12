package com.coderising.jvm.test;

public class Main {
    private int age = 20;
    public static int getResult(){
        return 1+1;
    }
    public static void main(String[] args) {
        System.out.println("Main");
        System.out.println(getResult());
//        new Main().isYouth();
    }
    public void isYouth() {
        if (this.age < 40) {
//            System.out.println("You're still young");
        } else {
//            System.out.println("You're old");
        }
    }
}
