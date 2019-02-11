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
import com.mygdx.game.Net.userLoginController;

import java.sql.SQLException;

/**
 * Created by Spica on 2016/9/9.
 */
public class GameOverScreen extends DefaultScreen{

    private SpriteBatch batch;
    private Texture img;



    public GameOverScreen (Game game) {
        super(game);
    }

    @Override
    public void show () {
        batch = new SpriteBatch();
        img = new Texture("gameover.png");

    }

    @Override
    public void render (float delta) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
        batch.begin();
        batch.draw(img,0,0);
        batch.end();

        if (Gdx.input.isKeyPressed(Input.Keys.ANY_KEY)) {
            game.setScreen(new MainMenu(game));
        }

    }

    @Override
    public void hide () {
        Gdx.app.debug("JavaGame", "GameOver");
    }
}
