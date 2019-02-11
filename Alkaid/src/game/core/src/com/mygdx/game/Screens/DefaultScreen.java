package com.mygdx.game.Screens;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Screen;

/**
 * Created by DMX on 2016/09/08.
 */
public abstract class DefaultScreen implements Screen{
    Game game;

    public DefaultScreen(Game game){this.game=game;}

    @Override
    public void resize (int width, int height) {
    }

    @Override
    public void show () {
    }

    @Override
    public void hide () {
    }

    @Override
    public void pause () {
    }

    @Override
    public void resume () {
    }

    @Override
    public void dispose () {
    }
}
