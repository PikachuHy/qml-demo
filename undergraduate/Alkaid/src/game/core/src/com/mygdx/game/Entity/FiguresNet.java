package com.mygdx.game.Entity;

import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.mygdx.game.Entity.FiguresNetAnimation;
import com.mygdx.game.Entity.FiguresProperty;

/**
 * Created by asus on 2016/9/8.
 */
public class FiguresNet extends Actor {

    FiguresNetAnimation figuresNetAnimation;
    FiguresProperty figuresProperty;
    String[] information = new String[7];

    public FiguresNet(){
        // do something
    }

    public FiguresNet(String[] info) throws Exception {
        receiveInfo(info);
        String str_roads = "";
        switch (Integer.parseInt(info[0])) {
            case 1:
                str_roads = "../assets/people/men1.txt";
                break;
            case 2:
                str_roads = "../assets/people/men2.txt";
                break;
            case 3:
                str_roads = "../assets/people/men3.txt";
                break;
            case 4:
                str_roads = "../assets/people/women1.txt";
                break;
            case 5:
                str_roads = "../assets/people/women2.txt";
                break;
            case 6:
                str_roads = "../assets/people/women3.txt";
                break;
            default:
                System.out.print("读取失败");
                break;
        }
        figuresNetAnimation = new FiguresNetAnimation(str_roads);
        figuresProperty = new FiguresProperty();
        figuresProperty.setID(Integer.parseInt(info[0]));
        figuresProperty.setHp(Integer.parseInt(info[1]));
        figuresProperty.setAttack(Integer.parseInt(info[2]));
        figuresProperty.setDefence(Integer.parseInt(info[3]));
        figuresNetAnimation.setX(Float.parseFloat(info[4]));
        figuresNetAnimation.setY(Float.parseFloat(info[5]));
        figuresNetAnimation.setState(Integer.parseInt(info[6]));
    }

    @Override
    public void act(float delta){
        figuresNetAnimation.act(delta);
    }

    @Override
    public void draw(Batch batch, float parentAlpha) {
        figuresNetAnimation.draw(batch, parentAlpha);
    }

    public void receiveInfo(String[] info) {
        // 0是编号
        information[0] = info[0];
        // 1是hp
        information[1] = info[1];
        // 2是攻击
        information[2] = info[2];
        // 3是防御
        information[3] = info[3];
        // 4是横坐标
        information[4] = info[4];
        // 5是纵坐标
        information[5] = info[5];
        // 6是状态
        information[6] = info[6];
    }

    public void resetString(String[] info) {
        receiveInfo(info);
        figuresProperty.setID(Integer.parseInt(info[0]));
        figuresProperty.setHp(Integer.parseInt(info[1]));
        figuresProperty.setAttack(Integer.parseInt(info[2]));
        figuresProperty.setDefence(Integer.parseInt(info[3]));
        figuresNetAnimation.setX(Float.parseFloat(info[4]));
        figuresNetAnimation.setY(Float.parseFloat(info[5]));
        figuresNetAnimation.setState(Integer.parseInt(info[6]));
    }

    public int getState() {
        return figuresNetAnimation.getState();
    }

    public int getAttack() {
        return figuresNetAnimation.getAttack();
    }

    public int getUp() {
        return figuresNetAnimation.getUp();
    }

    public int getDown() {
        return figuresNetAnimation.getDown();
    }

    public int getLeft() {
        return figuresNetAnimation.getLeft();
    }

    public int getRight1() {
        return figuresNetAnimation.getRight();
    }

    public int getStay() {
        return figuresNetAnimation.getStay();
    }

    public float getStateTime(){
        return figuresNetAnimation.getStateTime();
    }
    public void setStateTime(float time){
        figuresNetAnimation.setStateTime(time);
    }
}
