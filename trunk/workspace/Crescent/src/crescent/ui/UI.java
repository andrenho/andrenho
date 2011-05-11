package crescent.ui;

import crescent.Nation;

public interface UI {

	void initialize();

	GameOptions getGameOptions();

	void playRound(Nation n);

}
