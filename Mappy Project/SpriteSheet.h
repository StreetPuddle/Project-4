#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
using namespace std;
class Sprite
{
	friend int collided(int x, int y);
	friend bool endValue( int x, int y , int frameHeight, int frameWidth);
	friend int topCollision(int x, int y, int frameWidth, int frameHeight);
	friend int bottomCollision(int x, int y, int frameWidth, int frameHeight);
	friend int rightCollision(int x, int y, int frameWidth, int frameHeight);
	friend int leftCollision(int x, int y, int frameWidth, int frameHeight);
public:
	Sprite();
	~Sprite();
	void InitSprites(int width, int height);
	void UpdateSprites(int width, int height, int dir); //dir 1 = right, 0 = left, 2 = Standing Still
	void DrawSprites(int xoffset, int yoffset);
	float getX() {return x;}
	float getY() {return y;}
	void setX(int sX) { x = sX; }
	void setY(int sY) { y = sY; }
	void setAnimationDir(int x) { animationDirection = x; }
	void setRunningSpeed(int running) { runningSpeed = running; }
	int getWidth() {return frameWidth;}
	int getHeight() {return frameHeight;}
	bool CollisionEndBlock();

private:
	float x;
	float y;

	int directionalFrames[3];
	int index;
	int speed;
	int runningSpeed;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationRows;
	int animationDirection;

	ALLEGRO_BITMAP *image;
};