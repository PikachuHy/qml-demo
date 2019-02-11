package com.mygdx.game.Entity;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;

import java.io.File;
import java.util.Scanner;

/**
 * Created by asus on 2016/9/8.
 */
public class FiguresNetAnimation {

    public float stateTime=10f; // ��Ⱦʱ��
    private static final float FRAME_DURATION = 0.1f; // ��������ʱ���趨

    public int state = 0; // ��ʱ��֪�������
    public int stay = 0; // ��ֹ����
    public int up = 1; // ����
    public int down = 2; // ����
    public int left = 3; // ����
    public int right = 4; // ����
    public int attack = 5; // ����

    private static final float STEP = 32; // ���߲���

    private Animation walkAnimation_Stay; // ��ֹ״̬�����߶���
    private Animation walkAnimation_Up; // �����ߵ����߶���
    private Animation walkAnimation_Down; // �����ߵ����߶���
    private Animation walkAnimation_Left; // �����ߵ����߶���
    private Animation walkAnimation_Right; // �����ߵ����߶���

    private TextureRegion[] walkFrames_Stay; // �������߾�ֹ״̬�ؼ�֡
    private TextureRegion[] walkFrames_Up; // �����������߹ؼ�֡
    private TextureRegion[] walkFrames_Down; // �����������߹ؼ�֡
    private TextureRegion[] walkFrames_Left; // �����������߹ؼ�֡
    private TextureRegion[] walkFrames_Right; // �����������߹ؼ�֡

    private Animation attackAnimation_Up; // ���ϵĹ�������
    private Animation attackAnimation_Down; // ���µĹ�������
    private Animation attackAnimation_Left; // ����Ĺ�������
    private Animation attackAnimation_Right; // ���ҵĹ�������

    private TextureRegion[] attackFrames_Up; // �������Ϲ����ؼ�֡
    private TextureRegion[] attackFrames_Down; // �������¹����ؼ�֡
    private TextureRegion[] attackFrames_Left; // �������󹥻��ؼ�֡
    private TextureRegion[] attackFrames_Right; // �������ҹ����ؼ�֡

    private TextureRegion[] stayFrames_Up; // ������ֹ����״̬�ؼ�֡
    private TextureRegion[] stayFrames_Down; // ������ֹ����״̬�ؼ�֡
    private TextureRegion[] stayFrames_Left; // ������ֹ����״̬�ؼ�֡
    private TextureRegion[] stayFrames_Right; // ������ֹ����״̬�ؼ�֡

    private Animation stayAnimation_Up; // ������ֹ���϶���
    private Animation stayAnimation_Down; // ������ֹ���¶���
    private Animation stayAnimation_Left; // ������ֹ���¶���
    private Animation stayAnimation_Right; // ������ֹ���Ҷ���

    private TextureRegion currentFrame; // ��ǰ�����ؼ�֡

    private float x = 600; // �����������
    private float y = 9100; // ������������

    public FiguresNetAnimation() {
        // do something
    }

    // �вι��캯�� ���°� add by zyc 2016��9��3��11:35:44
    public FiguresNetAnimation(String str_roads, float x, float y) throws Exception{
        try {
            // ��ȡ�ļ�����
            File file = new File(str_roads);
            Scanner input = new Scanner(file);
            String[] strings = new String[80];
            int i = 0;
            while (input.hasNext()) {
                strings[i] = input.next();
                i++;
            }
            // ״̬
            String[] states_Up = new String[4];
            System.arraycopy(strings, 0, states_Up, 0, 4);
            String[] states_Down = new String[4];
            System.arraycopy(strings, 4, states_Down, 0, 4);
            String[] states_Left = new String[4];
            System.arraycopy(strings, 8, states_Left, 0, 4);
            String[] states_Right = new String[4];
            System.arraycopy(strings, 12, states_Right, 0, 4);

            // ����
            String[] walk_Up = new String[8];
            System.arraycopy(strings, 16, walk_Up, 0, 8);
            String[] walk_Down = new String[8];
            System.arraycopy(strings, 24, walk_Down, 0, 8);
            String[] walk_Left = new String[8];
            System.arraycopy(strings, 32, walk_Left, 0, 8);
            String[] walk_Right = new String[8];
            System.arraycopy(strings, 40, walk_Right, 0, 8);

            // ����
            String[] attack_Up = new String[8];
            System.arraycopy(strings, 48, attack_Up, 0, 8);
            String[] attack_Down = new String[8];
            System.arraycopy(strings, 56, attack_Down, 0, 8);
            String[] attack_Left = new String[8];
            System.arraycopy(strings, 64, attack_Left, 0, 8);
            String[] attack_Right = new String[8];
            System.arraycopy(strings, 72, attack_Right, 0, 8);

            // ���뾲ֹ�ؼ�֡
            stayFrames_Up = new TextureRegion[4];
            stayFrames_Down = new TextureRegion[4];
            stayFrames_Left = new TextureRegion[4];
            stayFrames_Right = new TextureRegion[4];
            stayFrames_Up = loadFrame(states_Up);
            stayFrames_Down = loadFrame(states_Down);
            stayFrames_Left = loadFrame(states_Left);
            stayFrames_Right = loadFrame(states_Right);

            // �������߹ؼ�֡
            walkFrames_Up = new TextureRegion[8];
            walkFrames_Down = new TextureRegion[8];
            walkFrames_Left = new TextureRegion[8];
            walkFrames_Right = new TextureRegion[8];
            walkFrames_Up = loadFrame(walk_Up);
            walkFrames_Down = loadFrame(walk_Down);
            walkFrames_Left = loadFrame(walk_Left);
            walkFrames_Right = loadFrame(walk_Right);

            // ���빥���ؼ�֡
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
            System.out.print("�ļ���ȡ����");
        }
    }

    // �вι��캯�� ���°�
    public FiguresNetAnimation(String str_roads) throws Exception{
        this(str_roads, 384, 224);
    }

    // �ú���������ȡͼƬ add by zyc 2016��9��3��11:01:15
    public TextureRegion loadTextureRegion(String str_roads) {
        TextureRegion textureRegion = new TextureRegion();
        //System.out.print(str_roads);
        Texture texture = new Texture(str_roads);
        textureRegion.setRegion(texture);
        return textureRegion;
    }

    // �ú���������ͼƬ����ɹؼ�֡ add by zyc 2016��9��3��11:14:13
    public TextureRegion[] loadFrame(String... str_roads) {
        TextureRegion[] textureRegions = new TextureRegion[str_roads.length];
        for(int i = 0; i <str_roads.length; i++) {
            textureRegions[i] = loadTextureRegion(str_roads[i]);
        }
        return textureRegions;
    }

    // �ú���������ʼ������
    public void setAnimation() {
        // ������ annotate by zyc 2016��9��3��11:26:45
        walkAnimation_Stay = new Animation(FRAME_DURATION, walkFrames_Stay);
        walkAnimation_Up = new Animation(FRAME_DURATION, walkFrames_Up);
        walkAnimation_Down = new Animation(FRAME_DURATION, walkFrames_Down);
        walkAnimation_Left = new Animation(FRAME_DURATION, walkFrames_Left);
        walkAnimation_Right = new Animation(FRAME_DURATION, walkFrames_Right);

        // ������ annotate by zyc 2016��9��3��11:27:34
        attackAnimation_Up = new Animation(FRAME_DURATION, attackFrames_Up);
        attackAnimation_Down = new Animation(FRAME_DURATION, attackFrames_Down);
        attackAnimation_Left = new Animation(FRAME_DURATION, attackFrames_Left);
        attackAnimation_Right = new Animation(FRAME_DURATION, attackFrames_Right);

        // ��ֹ�� add by zyc 2016��9��3��15:06:24
        stayAnimation_Up = new Animation(FRAME_DURATION, stayFrames_Up);
        stayAnimation_Down = new Animation(FRAME_DURATION, stayFrames_Down);
        stayAnimation_Left = new Animation(FRAME_DURATION, stayFrames_Left);
        stayAnimation_Right = new Animation(FRAME_DURATION, stayFrames_Right);

        // attackAnimation_Up.setPlayMode(Animation.PlayMode.LOOP);
    }

    // ������Ϸ�߼�
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

    // ѡ����ƶ��� add by zyc 2016��9��3��15:19:22 dmx��Ҫ�ĵĵط�
    public void selectAnimation() {
        if(state == stay){
            // ���ݳ���Ĳ�ͬ���ò��ž�ֹ����
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
                System.out.println("û�н����ж�");
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
            // ���ݳ���Ĳ�ͬ���ù���
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

    // act����
    public void act(float delta){
        // ������Ϸ�߼�
        logicUpdate();
        // ����ѡ��
        selectAnimation();
    }

    // draw����
    public void draw(Batch batch, float parentAlpha) {
        // ��Ϸ��Ⱦʱ��
        stateTime += Gdx.graphics.getDeltaTime();
        // ��������
        batch.draw(currentFrame, x, y);
    }

    // init����
//    public void init() {
//        figuresControl = new FiguresControl();
//    }
//
//    public FiguresControl getFiguresControl() {
//        return figuresControl;
//    }

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public void setState(int state) {
        this.state = state;
    }

    public int getState() {
        return state;
    }

    public int getStay() {
        return stay;
    }

    public int getUp() {
        return up;
    }

    public int getDown() {
        return down;
    }

    public int getLeft() {
        return left;
    }

    public int getRight() {
        return right;
    }

    public int getAttack() {
        return attack;
    }

    public float getStateTime() {
        return stateTime;
    }

    public void setStateTime(float stateTime) {
        this.stateTime = stateTime;
    }
}
