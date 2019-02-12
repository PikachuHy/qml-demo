package com.mygdx.game.Screens;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.assets.loaders.resolvers.InternalFileHandleResolver;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.maps.MapLayer;
import com.badlogic.gdx.maps.MapLayers;
import com.badlogic.gdx.maps.tiled.TiledMap;
import com.badlogic.gdx.maps.tiled.TiledMapTileLayer;
import com.badlogic.gdx.maps.tiled.TmxMapLoader;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.mygdx.game.Entity.FiguresNet;
import com.mygdx.game.Entity.Figures;
import com.mygdx.game.Entity.FiguresAnimation;
import com.mygdx.game.Entity.FiguresProperty;
import com.mygdx.game.Net.Client;
import com.mygdx.game.OrthogonalTiledMapRenderer2;


import java.io.*;
import java.net.Socket;

/**
 * Created by LMdeLiangMi on 9/3/16.
 */

public class GameScreen extends DefaultScreen {
    FiguresProperty i=new FiguresProperty();

    public Socket socket;
    public OutputStream out;
    public InputStream in;
    public Client client;

    String tmx_path="../assets/map_data/dessert.tmx";
    String dessert_path="../assets/map_data/dessert.png";
    String people_path="../assets/people/men2.txt";

    private TiledMap map;
    private OrthographicCamera camera;
    private AssetManager assetManager= new AssetManager();
    private Texture image;
    private OrthogonalTiledMapRenderer2 render2;
    private SpriteBatch batch;

    //music
    private static long now = 1, start = System.currentTimeMillis(), interval = 100000;
    private static Music[] music = new Music[4];

    Texture small_map;
    Texture map_dot;
    Texture map_treasure;

    int peoplex=14 ;
    int peopley=9;
    int latx=peoplex*32;
    int laty=peopley*32;
    int desertx=0-(peoplex-13)*32+32;
    int deserty=0-32*(320-peopley-12)-32;



    Figures man;
    FiguresNet people2;
    int man2[]=new int[7];
    String msg[]=new String[7];
    Stage stage;



    static int[][] barriers;

    static int[][] treasure;

    int Pedometer=50;
    int run_dect=0;


    public GameScreen (Game game) {
        super(game);
    }

    public void drawi(){
        try {
            man = new Figures(people_path);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void show () {
        i.hp=5;
        i.ID=2;
        man2[0]=1;//0是编号
        man2[1]=5;// 1是hp
        man2[2]=1;// 2是攻击
        man2[3]=1;//3是防御
        man2[4]=19*32;//4是横坐标
        man2[5]=9*32;//5是纵坐标
        man2[6]=0;//6是状态

        try {

            socket = new Socket("127.0.0.1",8888);
            out = socket.getOutputStream();
            in = socket.getInputStream();
            client = new Client(socket,out,in);

        } catch (IOException e) {
            e.printStackTrace();
        }

        barriers=new int[320][320];
        treasure=new int[10][5];
        batch = new SpriteBatch();
        load();
        assetManager.update();
        System.out.println(assetManager.isLoaded(tmx_path));

        if(assetManager.isLoaded(tmx_path)) {
            map = assetManager.get(tmx_path);
        }
        if(assetManager.isLoaded(dessert_path)) {
            image = assetManager.get(dessert_path);
        }

        drawi();

        stage = new Stage();
        stage.addActor(man);
        //stage.addListener(man.getLeftListener());
        Gdx.input.setInputProcessor(stage);

        render2 = new OrthogonalTiledMapRenderer2(map);
        camera = new OrthographicCamera();
        camera.setToOrtho(false,960,640);
        camera.translate((peoplex - 14) * 32, 32 * (320 - peopley - 13) + 64);
        setMapArray();

        small_map=new Texture("../assets/small_map.png");
        map_dot=new Texture("../assets/dot.png");
        map_treasure=new Texture("../assets/treasure.png");
        drawothers();

        //music
        GameScreen.music[0] = Gdx.audio.newMusic(Gdx.files.internal("../assets/music/begin.mp3"));
        GameScreen.music[0].setLooping(true);
        GameScreen.music[0].play();
        GameScreen.music[1] = Gdx.audio.newMusic(Gdx.files.internal("../assets/music/mid1.mp3"));
        GameScreen.music[1].setLooping(true);
        GameScreen.music[2] = Gdx.audio.newMusic(Gdx.files.internal("../assets/music/mid2.mp3"));
        GameScreen.music[2].setLooping(true);
        GameScreen.music[3] = Gdx.audio.newMusic(Gdx.files.internal("../assets/music/end.mp3"));
        GameScreen.music[3].setLooping(true);
    }

    public void load(){
        assetManager.load(dessert_path,Texture.class);
        assetManager.setLoader(TiledMap.class,new TmxMapLoader(new InternalFileHandleResolver()));
        assetManager.load(tmx_path,TiledMap.class);
        assetManager.finishLoading();
    }

    public void unload(){

    }

    public void handleInput(){
        if(Pedometer>=8) {
            run_dect = 0;
            msg[6]=0+"";
            if(FiguresAnimation.state != FiguresAnimation.attack)FiguresAnimation.state = FiguresAnimation.stay;
            if (Gdx.input.isKeyPressed(Input.Keys.A)) {
                if(FiguresAnimation.state == FiguresAnimation.attack&&FiguresAnimation.stateTime<0.8f)return;
                if (peoplex>0&&ifcollision(1)) {
                    FiguresAnimation.state = FiguresAnimation.left;
                    camera.translate(-4, 0, 0);
                    desertx+=4;
                    for(int i=1;i<=treasure[0][0];i++)
                        treasure[i][3]+=4;
                    Pedometer=1;
                    peoplex--;
                    latx-=4;
                    run_dect = 1;
                }
            }
            else if (Gdx.input.isKeyPressed(Input.Keys.D)) {
                if(FiguresAnimation.state == FiguresAnimation.attack&&FiguresAnimation.stateTime<0.8f)return;
                if(peoplex<=315&&ifcollision(2)) {
                    FiguresAnimation.state = FiguresAnimation.right;
                    camera.translate(4, 0, 0);
                    desertx-=4;
                    for(int i=1;i<=treasure[0][0];i++)
                        treasure[i][3]-=4;
                    Pedometer=1;
                    peoplex++;
                    latx+=4;
                    System.out.println("trun to"+peoplex+","+peopley);
                    run_dect = 2;
                }
            }
            else if (Gdx.input.isKeyPressed(Input.Keys.S)) {
                if(FiguresAnimation.state == FiguresAnimation.attack&&FiguresAnimation.stateTime<0.8f)return;
                if (peopley<=315&&ifcollision(3)) {
                    FiguresAnimation.state = FiguresAnimation.down;
                    camera.translate(0, -4, 0);
                    deserty+=4;
                    for(int i=1;i<=treasure[0][0];i++)
                        treasure[i][4]+=4;
                    Pedometer=1;
                    peopley++;
                    laty+=4;
                    System.out.println("trun to"+peoplex+","+peopley);
                    run_dect = 3;
                }
            }
            else if (Gdx.input.isKeyPressed(Input.Keys.W)) {
                if(FiguresAnimation.state == FiguresAnimation.attack&&FiguresAnimation.stateTime<0.8f)return;
                if (peopley>=1&&ifcollision(4)){
                    FiguresAnimation.state = FiguresAnimation.up;
                    camera.translate(0, 4, 0);
                    deserty-=4;
                    for(int i=1;i<=treasure[0][0];i++)
                        treasure[i][4]-=4;
                    Pedometer=1;
                    peopley--;
                    laty-=4;
                    System.out.println("trun to"+peoplex+","+peopley);
                    run_dect = 4;
                }
            }
            else if (Gdx.input.isKeyPressed(Input.Keys.J)) {
                if(FiguresAnimation.state != FiguresAnimation.attack)FiguresAnimation.stateTime=0;
                FiguresAnimation.state = FiguresAnimation.attack;
                //printmap();
            }
        }
        else{
            if (run_dect==1) {
                camera.translate(-4, 0, 0);
                desertx+=4;
                latx-=4;
                for(int i=1;i<=treasure[0][0];i++)
                    treasure[i][3]+=4;
                Pedometer++;
            }
            else if (run_dect==2) {
                camera.translate(4, 0, 0);
                desertx-=4;
                latx+=4;
                for(int i=1;i<=treasure[0][0];i++)
                    treasure[i][3]-=4;
                Pedometer++;
            }
            else if (run_dect==3) {
                camera.translate(0, -4, 0);
                deserty+=4;
                laty+=4;
                for(int i=1;i<=treasure[0][0];i++)
                    treasure[i][4]+=4;
                Pedometer++;
            }
            else if (run_dect==4) {
                camera.translate(0, 4, 0);
                deserty-=4;
                laty-=4;
                for(int i=1;i<=treasure[0][0];i++)
                    treasure[i][4]-=4;
                Pedometer++;
            }

        }

    }

    public void drawothers(){
        msg[0]=man2[0]+"";
        msg[1]=man2[1]+"";
        msg[2]=man2[2]+"";
        msg[3]=man2[3]+"";
        msg[4]=384+(man2[4]-latx)+"";
        msg[5]=224-(man2[5]-laty)+"";
        msg[6]=man2[6]+"";
        try {
            people2=new FiguresNet(msg);
        } catch (Exception e) {
            e.printStackTrace();
        }
        stage.addActor(people2);
    }

    @Override
    public void render (float delta) {
        //music
        if(now==1&&System.currentTimeMillis()-start>=interval){
            GameScreen.music[0].stop();
            GameScreen.music[0].dispose();
            GameScreen.music[1].play();
            now=2;
        }
        else if(now==2&&System.currentTimeMillis()-start>=2*interval){
            GameScreen.music[1].stop();
            GameScreen.music[1].dispose();
            GameScreen.music[2].play();
            now=3;
        }
        else if(now==3&&System.currentTimeMillis()-start>=3*interval){
            GameScreen.music[2].stop();
            GameScreen.music[2].dispose();
            GameScreen.music[3].play();
            now=4;
        }
        else if(System.currentTimeMillis()-start>=4*interval){
            game.setScreen(new GameOverScreen(game));
        }
        //finish
        try {
            Thread.sleep(4);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Gdx.gl.glClearColor(1,1,1,1);
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
        Gdx.gl.glBlendFunc(GL20.GL_SRC_ALPHA, GL20.GL_ONE_MINUS_SRC_ALPHA);

        String msg=client.doRead(in);
        //System.out.println("recv:"+msg);
        String[] StrArray = msg.split("#");
        String[] info=new String[7];
        int k=0;
        if(Integer.parseInt(StrArray[k])==i.ID)k+=5;
        info[0]=StrArray[k++];//0是编号

        info[1]=StrArray[k++];// 1是hp
        info[2]="1";// 2是攻击
        info[3]="1";//3是防御
        info[4]=384+(Integer.parseInt(StrArray[k++])-latx)+"";//4是横坐标
        info[5]=224-(Integer.parseInt(StrArray[k++])-laty)+"";//5是纵坐标
        info[6]=StrArray[k++];//6是状态
        people2.resetString(info);



        handleInput();
        batch.begin();
        batch.draw(image,desertx,deserty);
        for(int i=1;i<=treasure[0][0];i++)
            if(treasure[i][0]==1)
                batch.draw(map_treasure,treasure[i][3], treasure[i][4]);

        batch.end();

        camera.update();
        render2.setView(camera);
        render2.render();
        Gdx.gl.glDisable(GL20.GL_BLEND);

        stage.act();
        stage.draw();

        batch.begin();
        batch.draw(small_map,960-164+1,-1);
        batch.draw(map_dot,960-164+1+2+(peoplex/2)-2,161-(peopley/2)-2);
        batch.end();

        msg="sx#";
        msg=msg+i.ID+"#"+i.hp+"#"+latx+"#"+laty+"#"+FiguresAnimation.state;
        client.doWrite(msg,out);
    }

    public void setMapArray()
    {
        MapLayers layers = map.getLayers();
        for(MapLayer layer:layers){
            if(layer.getName().equals("building") == true){
                if(layer instanceof TiledMapTileLayer){
                    TiledMapTileLayer tileLayer=(TiledMapTileLayer)layer;
                    for(int i=319;i>0;i--){
                        for(int j=0;j<319;j++){
                            TiledMapTileLayer.Cell cell=tileLayer.getCell(j,i);
                            if(cell!=null)barriers[319-i][j]=1;
                        }
                    }
                }
            }
        }
        for(int i=0;i<9;i++)for(int j=0;j<320;j++)barriers[i][j]=2;
        for(int i=312;i<=319;i++)for(int j=0;j<320;j++)barriers[i][j]=2;
        for(int i=0;i<320;i++)for(int j=0;j<14;j++)barriers[i][j]=2;
        for(int i=0;i<320;i++)for(int j=306;j<=319;j++)barriers[i][j]=2;

        treasure[0][0]=1;
        treasure[1][0]=1;treasure[1][1]=14;treasure[1][2]=20;
        treasure[1][3]=384+32+(treasure[1][1]-peoplex)*32+32;treasure[1][4]=224+128-(treasure[1][2]-peopley)*32-32;

        for(int i=1;i<=treasure[0][0];i++)
            if(treasure[i][0]==1)
                barriers[treasure[i][2]][treasure[i][1]]=3;
    }

    public boolean ifcollision(int dect){
        if(dect==1){
            if(barriers[peopley][peoplex-1]==0&&barriers[peopley+1][peoplex-1]==0&&barriers[peopley+2][peoplex-1]==0)return true;
        }
        else if(dect==2){
            if(barriers[peopley][peoplex+2]==0&&barriers[peopley+1][peoplex+2]==0&&barriers[peopley+2][peoplex+2]==0)return true;
        }
        else if(dect==3){
            if(barriers[peopley+3][peoplex]==0&&barriers[peopley+3][peoplex+1]==0)return true;
        }
        else if(dect==4){
            if(barriers[peopley-1][peoplex]==0&&barriers[peopley-1][peoplex+1]==0)return true;
        }
        return false;
    }

    @Override
    public void hide () {
        map.dispose();
        assetManager.dispose();
    }
}
