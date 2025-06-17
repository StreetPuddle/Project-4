#include "SpriteSheet.h"

Sprite::Sprite()
{
	image=NULL;
}
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}
void Sprite::InitSprites(int width, int height)
{
	x = 80;
	y = 250;

	maxFrame = 9;
	curFrame = 0;
	index = 0;
	speed = 2;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 48;
	frameHeight = 70;
	animationColumns = 3;
	animationDirection = 1;

	image = al_load_bitmap("spriteSheet2.png");
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;
	

	if (dir == 1 || dir == 0) {//animate left or right

		if (dir == 1) {//left
			animationDirection = dir;
			speed = 2;
		}
		else {//right
			animationDirection = dir;
			speed = -2;
		}
		directionalFrames[0] = 6;//frames flip depending on direction
		directionalFrames[1] = 7;
		directionalFrames[2] = 8;
		x += speed;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			curFrame = directionalFrames[index];
			index++;
			if (index > 2) {
				index = 0;
			}
		}
	}
	else if (dir == 4) {//animate moving down
		animationDirection = dir;
		directionalFrames[0] = 0;
		directionalFrames[1] = 1;
		directionalFrames[2] = 2;
		y += speed;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			curFrame = directionalFrames[index];
			index++;
			if (index > 2) {
				index = 0;
			}
		}
	}
	else if (dir == 3) {//animate moving up
		animationDirection = dir;
		directionalFrames[0] = 3;
		directionalFrames[1] = 4;
		directionalFrames[2] = 5;
		y -= speed;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			curFrame = directionalFrames[index];
			index++;
			if (index > 2) {
				index = 0;
			}
		}
	}
	else {
		switch (animationDirection) {//standing still
		case 0: curFrame = 7; break;//face left
		case 1: curFrame = 7; break;//face right
		case 3: curFrame = 4; break;//face up
		case 4: curFrame = 1; break;//face down
		}
	}
	speed = 2;
	//check for collided with foreground tiles
	if (animationDirection==0)//left
	{ 
		if (leftCollision(x, y, frameWidth, frameHeight)) { //collision detection to the left
			x = oldx + 1;
			y = oldy;
		}
	}
	else if (animationDirection ==1)//right
	{ 
		if (rightCollision(x, y, frameWidth, frameHeight)) { //collision detection to the right
			x = oldx - 1;
			y = oldy;
		}
	}
	else if (animationDirection == 3) {//up
		if (topCollision(x, y, frameWidth, frameHeight)) {//collision detection to the up
			x = oldx;
			y = oldy + 1;
			//collided(x, y) || collided(x + frameWidth, +y) && collided(x + frameWidth / 2, y)
		}
	}
	else if (animationDirection == 4) {//down
		if (bottomCollision(x, y, frameWidth, frameHeight)) {//collision detection to the down
			x = oldx;
			y = oldy - 1;
		}
	}
}

bool Sprite::CollisionEndBlock()
{
	if (endValue(x + frameWidth/2, y + frameHeight + 5))
		return true;
	else
		return false;
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	if (animationDirection==1){//right
		al_draw_bitmap_region(image, fx, fy, frameWidth,frameHeight, x-xoffset, y-yoffset, ALLEGRO_FLIP_HORIZONTAL);
	}else if (animationDirection == 0 ){//left
		al_draw_bitmap_region(image, fx, fy, frameWidth,frameHeight, x-xoffset, y-yoffset, 0);
	}else if (animationDirection == 2 ){//still
		al_draw_bitmap_region(image,0,0,frameWidth,frameHeight,  x-xoffset, y-yoffset, 0);
	}
	else if (animationDirection == 3) {//up
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else if (animationDirection == 4) {//down
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
}