package com.mygdx.game.Entity;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;

import java.io.File;
import java.util.Scanner;

/**
 * Created by asus on 2016/9/3.
 * add by zyc 2016年9月3日21:09:04
 */
public class FiguresAnimation {

    public static float stateTime=10f; // 渲染时间
    private static final float FRAME_DURATION = 0.1f; // 动画播放时间设定

    public static int state = 0; // 暂时不知道干嘛的
    public static int stay = 0; // 静止不动
    public static int up = 1; // 向上
    public static int down = 2; // 向下
    public static int left = 3; // 向左
    public static int right = 4; // 向右
    public static int attack = 5; // 攻击

    private static final float STEP = 32; // 行走步长

    private Animation walkAnimation_Stay; // 静止状态的行走动画
    private Animation walkAnimation_Up; // 向上走的行走动画
    private Animation walkAnimation_Down; // 向下走的行走动画
    private Animation walkAnimation_Left; // 向左走的行走动画
    private Animation walkAnimation_Right; // 向右走的行走动画

    private TextureRegion[] walkFrames_Stay; // 声明行走静止状态关键帧
    private TextureRegion[] walkFrames_Up; // 声明向上行走关键帧
    private TextureRegion[] walkFrames_Down; // 声明向下行走关键帧
    private TextureRegion[] walkFrames_Left; // 声明向左行走关键帧
    private TextureRegion[] walkFrames_Right; // 声明向右行走关键帧

    private Animation attackAnimation_Up; // 向上的攻击动画
    private Animation attackAnimation_Down; // 向下的攻击动画
    private Animation attackAnimation_Left; // 向左的攻击动画
    private Animation attackAnimation_Right; // 向右的攻击动画

    private TextureRegion[] attackFrames_Up; // 声明向上攻击关键帧
    private TextureRegion[] attackFrames_Down; // 声明向下攻击关键帧
    private TextureRegion[] attackFrames_Left; // 声明向左攻击关键帧
    private TextureRegion[] attackFrames_Right; // 声明向右攻击关键帧

    private TextureRegion[] stayFrames_Up; // 声明静止向上状态关键帧
    private TextureRegion[] stayFrames_Down; // 声明静止向下状态关键帧
    private TextureRegion[] stayFrames_Left; // 声明静止向左状态关键帧
    private TextureRegion[] stayFrames_Right; // 声明静止向右状态关键帧

    private Animation stayAnimation_Up; // 声明静止向上动画
    private Animation stayAnimation_Down; // 声明静止向下动画
    private Animation stayAnimation_Left; // 声明静止向下动画
    private Animation stayAnimation_Right; // 声明静止向右动画

    private TextureRegion currentFrame; // 当前动画关键帧

    private float x = 600; // 出生点横坐标
    private float y = 9100; // 出生点纵坐标


    // 无参构造函数
    public FiguresAnimation() {
        // do something
    }

    // 有参构造函数 最新版 add by zyc 2016年9月3日11:35:44
    public FiguresAnimation(String str_roads, float x, float y) throws Exception{
        try {
            // 读取文件内容
            File file = new File(str_roads);
            Scanner input = new Scanner(file);
            String[] strings = new String[80];
            int i = 0;
            while (input.hasNext()) {
                strings[i] = input.next();
                i++;
            }
            // 状态
            String[] states_Up = new String[4];
            System.arraycopy(strings, 0, states_Up, 0, 4);
            String[] states_Down = new String[4];
            System.arraycopy(strings, 4, states_Down, 0, 4);
            String[] states_Left = new String[4];
            System.arraycopy(strings, 8, states_Left, 0, 4);
            String[] states_Right = new String[4];
            System.arraycopy(strings, 12, states_Right, 0, 4);

            // 行走
            String[] walk_Up = new String[8];
            System.arraycopy(strings, 16, walk_Up, 0, 8);
            String[] walk_Down = new String[8];
            System.arraycopy(strings, 24, walk_Down, 0, 8);
            String[] walk_Left = new String[8];
            System.arraycopy(strings, 32, walk_Left, 0, 8);
            String[] walk_Right = new String[8];
            System.arraycopy(strings, 40, walk_Right, 0, 8);

            // 攻击
            String[] attack_Up = new String[8];
            System.arraycopy(strings, 48, attack_Up, 0, 8);
            String[] attack_Down = new String[8];
            System.arraycopy(strings, 56, attack_Down, 0, 8);
            String[] attack_Left = new String[8];
            System.arraycopy(strings, 64, attack_Left, 0, 8);
            String[] attack_Right = new String[8];
            System.arraycopy(strings, 72, attack_Right, 0, 8);

            // 载入静止关键帧
            stayFrames_Up = new TextureRegion[4];
            stayFrames_Down = new TextureRegion[4];
            stayFrames_Left = new TextureRegion[4];
            stayFrames_Right = new TextureRegion[4];
            stayFrames_Up = loadFrame(states_Up);
            stayFrames_Down = loadFrame(states_Down);
            stayFrames_Left = loadFrame(states_Left);
            stayFrames_Right = loadFrame(states_Right);

            // 载入行走关键帧
            walkFrames_Up = new TextureRegion[8];
            walkFrames_Down = new TextureRegion[8];
            walkFrames_Left = new TextureRegion[8];
            walkFrames_Right = new TextureRegion[8];
            walkFrames_Up = loadFrame(walk_Up);
            walkFrames_Down = loadFrame(walk_Down);
            walkFrames_Left = loadFrame(walk_Left);
            walkFrames_Right = loadFrame(walk_Right);

            // 载入攻击关键帧
            attackFrames_Up = new TextureRegion[8];
            attackFrames_Down = new TextureRegion[8];
            attackFrames_Left = new TextureRegion[8];
            attackFrames_Right = new TextureRegion[8];
            attackFrames_Up = loadFrame(attack_Up);
            attackFrames_Down = loadFrame(attack_Down);
            attackFrames_Left = loadFrame(attack_Left);
            attackFrames_Right = loadFrame(attack_Right);

            walkFrames_Stay = new TextureRegion[1];
            walkFrames_Stay[0] = stayFrames_Down[0];

            setAnimation();

            input.close();

            this.x = x;
            this.y = y;

        } catch(Exception e){
            System.out.print("文件读取错误！");
        }
    }

    // 有参构造函数 最新版
    public FiguresAnimation(String str_roads) throws Exception{
        this(str_roads, 384, 224);
    }

    // 该函数用来读取图片 add by zyc 2016年9月3日11:01:15
    public TextureRegion loadTextureRegion(String str_roads) {
        TextureRegion textureRegion = new TextureRegion();
        //System.out.print(str_roads);
        Texture texture = new Texture(str_roads);
        textureRegion.setRegion(texture);
        return textureRegion;
    }

    // 该函数用来将图片载入成关键帧 add by zyc 2016年9月3日11:14:13
    public TextureRegion[] loadFrame(String... str_roads) {
        TextureRegion[] textureRegions = new TextureRegion[str_roads.length];
        for(int i = 0; i <str_roads.length; i++) {
            textureRegions[i] = loadTextureRegion(str_roads[i]);
        }
        return textureRegions;
    }

    // 该函数用来初始化动画
    public void setAnimation() {
        // 行走类 annotate by zyc 2016年9月3日11:26:45
        walkAnimation_Stay = new Animation(FRAME_DURATION, walkFrames_Stay);
        walkAnimation_Up = new Animation(FRAME_DURATION, walkFrames_Up);
        walkAnimation_Down = new Animation(FRAME_DURATION, walkFrames_Down);
        walkAnimation_Left = new Animation(FRAME_DURATION, walkFrames_Left);
        walkAnimation_Right = new Animation(FRAME_DURATION, walkFrames_Right);

        // 攻击类 annotate by zyc 2016年9月3日11:27:34
        attackAnimation_Up = new Animation(FRAME_DURATION, attackFrames_Up);
        attackAnimation_Down = new Animation(FRAME_DURATION, attackFrames_Down);
        attackAnimation_Left = new Animation(FRAME_DURATION, attackFrames_Left);
        attackAnimation_Right = new Animation(FRAME_DURATION, attackFrames_Right);

        // 静止类 add by zyc 2016年9月3日15:06:24
        stayAnimation_Up = new Animation(FRAME_DURATION, stayFrames_Up);
        stayAnimation_Down = new Animation(FRAME_DURATION, stayFrames_Down);
        stayAnimation_Left = new Animation(FRAME_DURATION, stayFrames_Left);
        stayAnimation_Right = new Animation(FRAME_DURATION, stayFrames_Right);

        // attackAnimation_Up.setPlayMode(Animation.PlayMode.LOOP);
    }

    // 更新游戏逻辑
    public void logicUpdate() {
        if (state == right){
            //x += STEP;
        }else if (state == left){
            //x -= STEP;
        }else if (state == up){
            //y += STEP;
        }else if (state == down){
            //y -= STEP;
        }else if (state == attack){

        }else {
            // do something
        }
    }

    // 选择绘制动画 add by zyc 2016年9月3日15:19:22 dmx你要改的地方
    public void selectAnimation() {
        if(state == stay){
            // 根据朝向的不同设置播放静止动画
            if(walkFrames_Stay[0] == stayFrames_Up[0]) {
                currentFrame = stayAnimation_Up.getKeyFrame(stateTime, true);
            }
            else if(walkFrames_Stay[0] == stayFrames_Down[0]) {
                currentFrame = stayAnimation_Down.getKeyFrame(stateTime, true);
            }
            else if(walkFrames_Stay[0] == stayFrames_Left[0]) {
                currentFrame = stayAnimation_Left.getKeyFrame(stateTime, true);
            }
            else if(walkFrames_Stay[0] == stayFrames_Right[0]) {
                currentFrame = stayAnimation_Right.getKeyFrame(stateTime, true);
            }
            else{
                System.out.println("没有进行判断");
            }
        }
        else if (state == up){
            currentFrame = walkAnimation_Up.getKeyFrame(stateTime,true);
            walkFrames_Stay[0] = stayFrames_Up[0];
        }
        else if (state == down){
            currentFrame = walkAnimation_Down.getKeyFrame(stateTime,true);
            walkFrames_Stay[0] = stayFrames_Down[0];
        }
        else if (state == left){
            currentFrame = walkAnimation_Left.getKeyFrame(stateTime,true);
            walkFrames_Stay[0] = stayFrames_Left[0];
        }
        else if (state == right){
            currentFrame = walkAnimation_Right.getKeyFrame(stateTime,true);
            walkFrames_Stay[0] = stayFrames_Right[0];
        }
        else if (state == attack && stateTime <=0.8f){
            // 根据朝向的不同设置攻击
            if(walkFrames_Stay[0] == stayFrames_Up[0]) {
                currentFrame = attackAnimation_Up.getKeyFrame(stateTime, true);
            }
            else if(walkFrames_Stay[0] == stayFrames_Down[0]) {
                currentFrame = attackAnimation_Down.getKeyFrame(stateTime, true);
            }
            else if(walkFrames_Stay[0] == stayFrames_Left[0]) {
                currentFrame = attackAnimation_Left.getKeyFrame(stateTime, true);
            }
            else if(walkFrames_Stay[0] == stayFrames_Right[0]) {
                currentFrame = attackAnimation_Right.getKeyFrame(stateTime, true);
            }
        }
        else{
            state = stay;
            stateTime = 0;
        }
    }

    // act方法
    public void act(float delta){
        // 更新游戏逻辑
        logicUpdate();
        // 动画选择
        selectAnimation();
    }

    // draw方法
    public void draw(Batch batch, float parentAlpha) {
        // 游戏渲染时间
        stateTime += Gdx.graphics.getDeltaTime();
        // 动画绘制
        batch.draw(currentFrame, x, y);
    }
}
