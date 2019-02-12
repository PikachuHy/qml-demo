package com.mygdx.game.Entity;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.sun.xml.internal.ws.api.message.ExceptionHasMessage;
import com.sun.xml.internal.ws.policy.privateutil.PolicyUtils;

import java.io.File;
import java.util.Scanner;

/**
 * Created by zyc on 2016/9/1.
 */
public class Figures extends Actor {

    FiguresAnimation figuresAnimation; // 声明动画变量
    // FiguresProperty figuresProperty; // 声明属性变量

    // 此处是绘制动画相关
    // 无参构造函数
    public Figures(){
        // do something
    }

    // 有参构造函数
    public Figures(String str_roads) throws Exception {
        figuresAnimation = new FiguresAnimation(str_roads);
        // figuresProperty = new FiguresProperty();
    }

    // 重写Act方法
    @Override
    public void act(float delta){
        figuresAnimation.act(delta);
    }

    // 重写Draw方法
    @Override
    public void draw(Batch batch, float parentAlpha) {
        figuresAnimation.draw(batch, parentAlpha);
    }

}
