#include<bangtal.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

SceneID scene0,scene1;
ObjectID mainch,mainch1,mainch_level1,mainch2,mainch_level2,mainch3,mainch_level3,
attack,attack1,attack_level1,attack2,attack_level2,attack3,attack_level3,
monster1,monster2,monster3,
boss,boss2,attackboss,deadboss,
castle,effect,endgame,
skill,skill1,skill2,skill3;
TimerID timer1;




int dx = 0; int dy = 0; int x = 400; int y = 300; int monster_x = 800; int monster_y = 400; int attackcount; int skillcount;







void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == mainch1) {
		enterScene(scene1); mainch = mainch1; attack = attack1; skill = skill1;
	}
	else if (object == mainch2) {
		enterScene(scene1);
		mainch = mainch2;
		attack = attack2;
		skill = skill2;

	}
	else if (object == mainch3) {
		enterScene(scene1);
		mainch = mainch3;
		attack = attack3;
		skill = skill3;


	}
	if (object == endgame) {
		endGame();

	}
	

}


#define ANIMATION_TIME		0.01f
#define ANIMATION_STEP		5

void ShowObject(ObjectID object, bool shown) {
	if (shown) showObject(object);
	else 
	{
		hideObject(object);

	}
	
}



void timerCallback(TimerID timer)
{
	
	x += dx; y += dy;
	locateObject(mainch, scene1, x, y);
	locateObject(attack, scene1, x, y);
	locateObject(effect, scene1, x + 200, y + 50);

	setTimer(timer, ANIMATION_TIME);
	startTimer(timer);
}

void keyboardCallback(KeyCode code, KeyState state)
{
	if (code == KeyCode::KEY_UP_ARROW) {			// UP
		dy += (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}
	else if (code == KeyCode::KEY_DOWN_ARROW) {		// DOWN
		dy -= (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
		
	}
	else if (code == KeyCode::KEY_RIGHT_ARROW) {		// RIGHT
		dx += (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}
	else if (code == KeyCode::KEY_LEFT_ARROW) {		// LEFT
		dx -= (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
		if (state == KeyState::KEY_PRESSED&&attackcount>150) {
			hideObject(boss2);
			ShowObject(attackboss, true);

		}
		else if (state != KeyState::KEY_PRESSED&&attackcount>150) {
			ShowObject(attackboss, false);
			ShowObject(boss2, true);

		}
		if (skillcount > 50) {
			hideObject(boss2);
			hideObject(attackboss);

		}
	}
	else if (code == KeyCode::KEY_A) {
			if (state==KeyState::KEY_PRESSED) {
			ShowObject(mainch,false);
			ShowObject(attack,true);
			attackcount++;
			if (attackcount > 60) {
				showMessage("Level up!!");

				hideObject(monster1);
				hideObject(monster2);
				hideObject(monster3);

				ShowObject(boss,true);

				if (mainch == mainch1) {
					mainch1 = mainch_level1;
					attack = attack_level1;
					hideObject(attack1);
				}
				else if (mainch == mainch2) {
					mainch1 = mainch_level2;
					attack = attack_level2;
					hideObject(attack2);
				}
				else if (mainch == mainch3) {
					mainch1 = mainch_level3;
					attack = attack_level3;
					hideObject(attack3);


				}
			}
			if (attackcount>150) {
				showMessage("Last Boss!!\n Skill Update!! Please Enter S to Use Skill!!");
				hideObject(boss);
				ShowObject(boss2, true);
				if (skillcount > 50) {
					hideObject(boss2);
					hideObject(attackboss);
					

				}
			}
			
			}
			else if (state != KeyState::KEY_PRESSED) {
				ShowObject(attack, false);
				ShowObject(mainch, true);
			}
			if (monster_x-25<x<monster_x and state == KeyState::KEY_PRESSED) {
				ShowObject(effect, true);

			}
			else if(state!=KeyState::KEY_PRESSED) {
				ShowObject(effect, false);

			}
				

	}
	if (code == KeyCode::KEY_S&&attackcount>150){

		
		if (state == KeyState::KEY_PRESSED) {
			skillcount++;

			ShowObject(mainch, false);
			ShowObject(attack, true);
			ShowObject(skill, true);
			locateObject(skill, scene1, x + 200, y);

		}
		else if (state != KeyState::KEY_PRESSED) {
			ShowObject(attack, false);
			ShowObject(mainch, true);
			ShowObject(skill, false);

		}
		if (skillcount > 50) {
			showMessage("Mission Completed!!");
			hideObject(boss2);
			hideObject(attackboss);
			ShowObject(deadboss,true);
			locateObject(deadboss, scene1, 800, 200);
			ShowObject(endgame, true);
			locateObject(endgame, scene1, 100, 600);

			
		}

	}
	



	
	

	

}



int main() {
	
	

	

	effect = createObject("effect.png");
	scaleObject(effect, 0.5);


	setTimerCallback(timerCallback);
	setMouseCallback(mouseCallback);
	setKeyboardCallback(keyboardCallback);

	scene0 = createScene("Select Your Champion! Press A = attack, Move Champion with keybord!", "select.png");

	mainch1 = createObject("mainch1.png");
	locateObject(mainch1, scene0, 300, 500);
	showObject(mainch1);

	mainch2 = createObject("mainch2.png");
	locateObject(mainch2, scene0, 500, 500);
	showObject(mainch2);

	mainch3 = createObject("mainch3.png");
	locateObject(mainch3, scene0, 700, 500);
	showObject(mainch3);

	mainch_level1 = createObject("mainch1-1.png");
	mainch_level2 = createObject("mainch2-1.png");
	mainch_level3 = createObject("mainch3-1.png");

	attack_level1 = createObject("attack1-1.png");
	attack_level2 = createObject("attack2-1.png");
	attack_level3 = createObject("attack3-1.png");

	

	attack1 = createObject("attack1.png");

	attack2 = createObject("attack2.png");

	attack3 = createObject("attack3.png");

	skill1 = createObject("skill1.png");
	scaleObject(skill1, 3);
	skill2 = createObject("skill2.png");
	skill3 = createObject("skill3.png");


	

	scene1 = createScene("Keep Your Castle From The Monster!!", "background3.png");

	

	
	

	castle = createObject("castle.png");
	locateObject(castle, scene1, 0, 260);
	showObject(castle);
	scaleObject(castle, 0.5);


	


	locateObject(mainch, scene1, x, y);
	ShowObject(mainch,true);
	
	locateObject(attack, scene1, x, y);

	monster1 = createObject("monster1.png");
	locateObject(monster1, scene1, monster_x, monster_y);
	showObject(monster1);
	scaleObject(monster1, 2);
	
	monster2 = createObject("monster2.png");
	locateObject(monster2, scene1, monster_x, monster_y+100);
	showObject(monster2);
	scaleObject(monster2, 2);

	monster3 = createObject("monster3.png");
	locateObject(monster3, scene1, monster_x, monster_y-100);
	showObject(monster3);
	scaleObject(monster3, 2);

	boss = createObject("boss.png");
	locateObject(boss, scene1, 800, 200);
	scaleObject(boss, 2);

	boss2 = createObject("boss3.png");
	locateObject(boss2, scene1, 800, 200);
	scaleObject(boss2, 3);

	attackboss = createObject("boss attack.png");
	locateObject(attackboss, scene1, 800, 200);
	scaleObject(attackboss, 2);

	deadboss = createObject("deadboss.png");
	scaleObject(deadboss, 3);

	endgame = createObject("endgame.png");







	TimerID timer = createTimer(ANIMATION_TIME);
	startTimer(timer);

	

	
	startGame(scene0);
	

}