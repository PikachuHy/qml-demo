package com.mygdx.game.Entity;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.*;
import java.lang.Math;
/**
 * Created by Spica on 2016/9/7.
 */

//Waiting for working 20160907

public class FiguresProperty {

    public final static int BeginOfAll = 40;
    public int hp; // ����ֵ
    public int maxHp; // �������ֵ
    public int defence; // ����ֵ
    public int attack; // ����ֵ
    public String name;
    public int ID;

    public int strength, dexterity, intelligence, luck; // ����ֵ ����ֵ ����ֵ ����ֵ

    boolean attacked = false; // �Ƿ񱻹���
    boolean dead = false; // �Ƿ�����

    // �޲ι��캯��
    public FiguresProperty() {
            initialize();
        }

    // ��ʼ��������� һ��40�㣬δ��������
    public void initialize() {
        int mid=(int)(Math.random()*4153%20)+11,le=(int)(Math.random()*4153%(mid-1))+1,ri=(int)(Math.random()*4153%(40-1-mid))+mid+1;
        strength=le;
        dexterity=mid-strength;
        intelligence=ri-mid;
        luck=BeginOfAll-strength-dexterity-intelligence;

        hp = decideHp();
        maxHp = decideHp();
        attack = decideAttack();
        defence = decideDefence();
    }

        // ��������ֵ
        public int decideHp() {
//            int hpAbility = 0;
//            hpAbility += (1 + ((int)(intelligence / 2.0) + 1) * 0.01) *intelligence;
            return (int)Math.ceil((1 + intelligence * 0.01)*hp);
        }

        // ��������ֵ
        public int decideAttack() {
//            int attackAbility = 0;
//            attackAbility += (1 + ((int)(strength / 2.0) + 1) * 0.01) * strength;
            return (int)((1+Math.ceil(strength*0.01/2))*attack);
        }

        // ��������ֵ
        public int decideDefence() {
//            int defenceAbility = 0;
//            defenceAbility += (1 + ((int)(dexterity / 2.0) + 1) * 0.01) * dexterity;
            return (int)((1+Math.ceil(dexterity*0.01/4))*defence);
        }

        // ����ֵ�ı�
        public void changeHp(int changeOfHp) {
            hp += changeOfHp;
        }

        // �жϽ�ɫ�Ƿ����� ���������� ���򷵻ؼ�
        public boolean isDead() {
            return hp<=0;
        }

//        // ����Ϊ����Ѫ���õı���
//        private Texture textureFu, textureEp; // Full Empty
//        TextureRegion region;
//        private static int hpWidth = 356;
//        private int hpHeight = 28;
//        private static int hpWidthC = hpWidth ; // current
//        private static int hpNum = maxHp;
//        private static int hit = damage - defence;

    // HP 相关
//        public void draw(Batch batch, float parentAlpha) {
//            loadHpFrame();
//            // ��Ѫ������Ҫ��
//            batch.draw(textureEp, 0, 0, 344, 28);
//            // ���Ʋ�ɫ�� = ˲���Ѫ
//            region.setRegionWidth(hpWidth);
//            batch.draw(region, -1, 1, hpWidth, 28);
//            handleInput();
//
//        }
//
//        //  ����Ѫ����ͷ���ز�
//        public void loadHpFrame() {
//            // ��ͼ
//            textureFu = new Texture("hp_full.png");
//            textureEp = new Texture("hp_empty.png");
//            region = new TextureRegion(textureFu, 0, 0, hpWidth, hpHeight);
//        }
//
//        public void handleInput() {
//            // Ѫ������
//            if(hpWidth > hpWidthC && hpWidth > 0 && test) {
//                hpWidth -= Gdx.graphics.getDeltaTime() * 100;
//            }
//        }
//
//        public void textHp() {
//
//        }

        // ����setter, getter����
        public int getHp() {
            return hp;
        }
        public int getMaxHp() {
            return maxHp;
        }
        public int getDefence() {
            return defence;
        }
        public int getAttack() {
            return attack;
        }
        public String getName() {
            return name;
        }
        public int getStrength() {
            return strength;
        }
        public int getDexterity() {
            return dexterity;
        }
        public int getIntelligence() {
            return intelligence;
        }
        public int getLuck() {
            return luck;
        }
         public int getID() {
        return ID;
    }

        public void setHp(int hp) {
            this.hp = hp;
        }
        public void setDefence(int defence) {
            this.defence = defence;
        }
        public void setAttack(int attack) {
            this.attack = attack;
        }
        public void setName(String name) {
            this.name = name;
        }
        public void setStrength(int strength) {
            this.strength = strength;
        }
        public void setDexterity(int dexterity) {
            this.dexterity = dexterity;
        }
        public void setIntelligence(int intelligence) {
            this.intelligence = intelligence;
        }
        public void setLuck(int luck) {
            this.luck = luck;
        }
        public void setID(int ID) {
        this.ID = ID;
    }
}
