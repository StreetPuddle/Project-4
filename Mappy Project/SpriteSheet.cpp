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
	

	if (dir == 1 || dir == 0) { //right key

		if (dir == 1) {
			animationDirection = dir;
			speed = 2;
		}
		else {
			animationDirection = dir;
			speed = -2;
		}
		directionalFrames[0] = 6;
		directionalFrames[1] = 7;
		directionalFrames[2] = 8;
		x += speed;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			curFrame = directionalFrames[index];
			std::cout << "Index: " << index << endl;
			index++;
			if (index > 2) {
				index = 0;
			}
		}
	}
	else if (dir == 4) {
		animationDirection = dir;
		directionalFrames[0] = 0;
		directionalFrames[1] = 1;
		directionalFrames[2] = 2;
		y += speed;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			curFrame = directionalFrames[index];
			std::cout << "Index: " << index << endl;
			index++;
			if (index > 2) {
				index = 0;
			}
		}
	}
	else if (dir == 3) {
		animationDirection = dir;
		directionalFrames[0] = 3;
		directionalFrames[1] = 4;
		directionalFrames[2] = 5;
		y -= speed;
		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			curFrame = directionalFrames[index];
			std::cout << "Index: " << index << endl;
			index++;
			if (index > 2) {
				index = 0;
			}
		}
	}
	else {
		// Standing still
		index = 0; // Reset walk animation index
		frameCount = 0;

		switch (animationDirection) {
		case 0: curFrame = 7; break; // Standing Left
		case 1: curFrame = 7; break; // Standing Right (will be flipped in draw)
		case 2: curFrame = 4; break; // Standing Up
		case 3: curFrame = 1; break; // Standing Down
		}
	}
	speed = 2;
	//check for collided with foreground tiles
	if (animationDirection==0)
	{ 
		if (collided(x, y + frameHeight) || collided(x, y)) { //collision detection to the left
			x = oldx; 
			y= oldy;
		}

	}
	else if (animationDirection ==1)
	{ 
		if (collided(x + frameWidth, y + frameHeight) || collided(x + frameWidth, y)) { //collision detection to the right
			x = oldx; 
			y= oldy;
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
	}else if (animationDirection == 2 ){
		al_draw_bitmap_region(image,0,0,frameWidth,frameHeight,  x-xoffset, y-yoffset, 0);
	}
	else if (animationDirection == 3) {//up
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
	else if (animationDirection == 4) {//down
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
}
