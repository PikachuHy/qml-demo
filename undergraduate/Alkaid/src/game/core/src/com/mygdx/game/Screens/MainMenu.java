package com.mygdx.game.Screens;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.*;
import com.badlogic.gdx.scenes.scene2d.utils.TextureRegionDrawable;
import com.mygdx.game.Net.Client;
import com.mygdx.game.Net.userLoginController;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.sql.SQLException;

/**
 * Created by DMX on 2016/09/08.
 */
public class MainMenu extends DefaultScreen{
//    private SpriteBatch batch;
    private Texture img;

    private Skin skin;
    private Stage stage;
    private TextField textField_Usr;
    private TextField textField_PassWord;
    private Texture texture;
    private Image image;
    private SpriteBatch batch;
    private Image imageUsername;
    private Image imagePassword;

    private boolean result = false;

    final String BUTTON_LOGIN_PATH="../assets/skin/login.png";
    final String BUTTON_SIGN_IN_PATH="../assets/skin/register.png";

    private Button buttonLogin;
    private Button buttonSignIn;

    public MainMenu (Game game) {
        super(game);
    }

    @Override
    public void show () {

        batch=new SpriteBatch();
//        img=new Texture("../assets/treasure.png");

        //init
        buttonLogin=new ImageButton(new TextureRegionDrawable(new TextureRegion(new Texture(BUTTON_LOGIN_PATH))));
        buttonSignIn=new ImageButton(new TextureRegionDrawable(new TextureRegion(new Texture(BUTTON_SIGN_IN_PATH))));
        skin = new Skin(Gdx.files.internal("../assets/skin/test.json"));
        stage = new Stage();
        texture = new Texture("../assets/skin/logo3.png");
        image = new Image(texture);
        imageUsername=new Image(new Texture("../assets/skin/user.png"));
        imagePassword=new Image(new Texture("../assets/skin/password.png"));
        batch = new SpriteBatch();


        Gdx.input.setInputProcessor(stage);
        //user
        textField_Usr = new TextField("",skin);
        textField_Usr.setSize(267,43);
        textField_Usr.setPosition(180,280);
        //password
        textField_PassWord = new TextField("",skin,"default-pw");
        textField_PassWord.setSize(267,43);
        textField_PassWord.setPosition(180,220);
        textField_PassWord.setPasswordCharacter('*');
        textField_PassWord.setPasswordMode(true);

        //layout
        buttonLogin.setPosition(180,100);
        buttonSignIn.setPosition(330,100);
        imageUsername.setPosition(140,281);
        imagePassword.setPosition(140,221);

        textField_Usr.setTextFieldListener(new TextField.TextFieldListener() {
            @Override
            public void keyTyped(TextField textField, char c) {
            }
        });
        textField_PassWord.setTextFieldListener(new TextField.TextFieldListener() {
            @Override
            public void keyTyped(TextField textField, char c) {
            }
        });

        buttonLogin.addListener(new InputListener(){
            @Override
            public boolean touchDown(InputEvent event, float x, float y, int pointer, int button) {
//                game.setScreen(game.loginScreen);

                userLoginController userLoginAction = new userLoginController();

                try {
                    result = userLoginAction.Login(textField_Usr.getText(),textField_PassWord.getText());
                } catch (SQLException e1) {
                    e1.printStackTrace();
                }

                return true;
            }
        });

        stage.addActor(image);
        stage.addActor(textField_PassWord);
        stage.addActor(textField_Usr);
        stage.addActor(buttonLogin);
        stage.addActor(buttonSignIn);
        stage.addActor(imageUsername);
        stage.addActor(imagePassword);

    }

    @Override
    public void render (float delta) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
        batch.begin();
        stage.act();
        stage.draw();

//        batch.draw(img,0,0);
        batch.end();


        if (result)
        game.setScreen(new GameScreen(game));

    }

    @Override
    public void hide () {
        Gdx.app.debug("JavaGame", "dispose main menu");
    }
}
