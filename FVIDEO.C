/* Copyright (c) 1992 by AT&T Bell Laboratories. */
/* Advanced C++ Programming Styles and Idioms */
/* James O. Coplien */
/* All rights reserved. */

#include <generic.h>
#include <iostream.h>
#include "curses.h"

#define LocalScope(function) struct name3(function,Local,Scope) {	\
void *parent; name3(function,Local,Scope)(void *p) { parent = p; } public
#define EndLocalScope } local(this)
#define EndOuterScope } local(0)
#define Parent(type,c) ((name3(type,Local,Scope)*)(c)->parent)

void main()
{
	LocalScope(BallGame):
		void DrawSides() {
			for(int i = 0; i < 66; i++) mvaddch(0, i, 'S');
			for(i = 0; i < 13; i++) {
				mvaddch(i, 0, 'S');
				mvaddch(i, 65, 'S');
			}
			leftWall = 0;
			rightWall = 65;
		}

		struct Ball {
			int yposition, xposition;
			int yspeed, xspeed;
			Ball() {
				yposition = 6;
				xposition = 33;
				yspeed = 1;
				xspeed = 1;
			}
		} ball;

		struct Bat {
			int yposition, position, length, xspeed;
			Bat() { position = 40;
				yposition = 11;
				length = 4;
				xspeed = 0;
			}
		} bat;

		void DrawBat() {
			for (int i = bat.position; i < bat.position + bat.length; i++) {
				mvaddch(bat.yposition, i, 'b');
			}
		}

		void EraseBat() {
			for (int i = bat.position; i < bat.position + bat.length; i++) {
				mvaddch(bat.yposition, i, ' ');
			}
		}

		short leftWall, rightWall;

		int score;
	
		void DrawWall() {
			for(int i = 0; i < 66; i++) {
				mvaddch(3, i, 'W');
				mvaddch(4, i, 'W');
				mvaddch(5, i, 'W');
			}
		}

		char ballIsInPlay() {
			return ball.xposition < rightWall &&
			  ball.xposition > leftWall &&
			  ball.yposition <= bat.yposition;
		}

		void PlayGame() {
			LocalScope(PlayGame):
				char key;	// from keyboard

				short ballsLeft;
				void PlayABall() {
					LocalScope(PlayABall):
						void CheckBallPosition() {
							PlayGameLocalScope *p = Parent(PlayGame, this);
							BallGameLocalScope *p2 = Parent(BallGame, p);
							int &y = p2->ball.yposition;
							int &x = p2->ball.xposition;
							if (x <= p2->leftWall+1 ||
								x >= p2->rightWall-1) {
								p2->ball.xspeed = -p2->ball.xspeed;
							}
							if (y <= 0) {
								p2->ball.yspeed = -p2->ball.yspeed;
							}
							char c = mvinch(y + p2->ball.yspeed,
								x + p2->ball.xspeed);
							switch (c) {
							case 'W':
								mvaddch(y + p2->ball.yspeed,
									x + p2->ball.xspeed,
									' ');
								p2->score++;
							case 'b':
								p2->ball.yspeed = -p2->ball.yspeed;
								p2->ball.xspeed = p2->bat.xspeed;
								break;
							}
						}

						void MoveBall() {
							PlayGameLocalScope *p = Parent(PlayGame, this);
							BallGameLocalScope *p2 = Parent(BallGame, p);
							mvaddch(p2->ball.yposition,
								p2->ball.xposition, ' ');
							p2->ball.xposition += p2->ball.xspeed;
							p2->ball.yposition += p2->ball.yspeed;
							mvaddch(p2->ball.yposition,
								p2->ball.xposition, 'O');
						}

						void MoveBat(char key) {
							LocalScope(MoveBat):
								void MoveLeft(Bat& bat) {
									PlayABallLocalScope *p = Parent(PlayABall, this);
									PlayGameLocalScope *p2 = Parent(PlayGame, p);
									Parent(BallGame, p2)->EraseBat();
									if (bat.position > Parent(BallGame, p2)->leftWall) {
										bat.position--;
									}
									Parent(BallGame, p2)->DrawBat();
								}

								void MoveRight(Bat& bat) {
									PlayABallLocalScope *p = Parent(PlayABall, this);
									PlayGameLocalScope *p2 = Parent(PlayGame, p);
									Parent(BallGame, p2)->EraseBat();
									if (bat.position < Parent(BallGame, p2)->rightWall - bat.length) {
										bat.position++;
									}
									Parent(BallGame, p2)->DrawBat();
								}
							EndLocalScope;

							PlayGameLocalScope *p = Parent(PlayGame, this);
							switch (key) {
							case 'l':
								local.MoveLeft(Parent(BallGame, p)->bat);
								Parent(BallGame, p)->bat.xspeed = -1;
								break;
							case 'r':
								local.MoveRight(Parent(BallGame, p)->bat);
								Parent(BallGame, p)->bat.xspeed = 1;
								break;
							default:
								break;
							}
						}
					EndLocalScope;

					while (Parent(BallGame, this)->ballIsInPlay()) {
						local.CheckBallPosition();	
						local.MoveBall();
						refresh();
						key = getch();
						local.MoveBat(key);
					}
				}
			EndLocalScope;

			local.ballsLeft = 4;
			while (local.ballsLeft > 0) {
				refresh();
				local.key = getch();
				local.PlayABall();
				--local.ballsLeft;
			}
		}

	EndOuterScope;

	int bestScore = 0;

	initscr();
	cbreak();
	noecho();

	local.DrawSides();
	local.DrawBat();

	for (;;) {
		local.score = 0;
		local.DrawWall();
		local.PlayGame();
		if (local.score > bestScore) {
			bestScore = local.score;
		}
		cout << "best score is " << bestScore << "\n";
	}
}
