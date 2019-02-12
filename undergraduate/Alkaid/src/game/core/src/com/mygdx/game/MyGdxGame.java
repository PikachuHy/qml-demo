package com.mygdx.game;

import com.badlogic.gdx.Game;
import com.mygdx.game.Screens.MainMenu;

public class MyGdxGame extends Game {

	@Override
	public void create () {
		setScreen(new MainMenu(this));
	}

}
