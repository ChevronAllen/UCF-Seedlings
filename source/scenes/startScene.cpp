#include "../gameManager.hpp"
#include "../sceneManager.hpp"
#include "../scene.hpp"
#include "../resources.h"

class startScene : public Scene
{
	private:
		//m3d::Sprite *wallpaper;
		//m3d::Texture *texture;
		m3d::Rectangle *wallpaper;
		m3d::Rectangle *bwallpaper;
		m3d::Color *colorRec;
		m3d::Color *colorText;
		m3d::Text *prompt;
		int x;
		int y;
	public:
		startScene()
		{
			x = 200;
			y = 150;
		}
		void initialize(){
			 //texture = ResourceManager::loadTexture("gfx/copy.png");
			 //texture = ResourceManager::getTexture("gfx/copy.png");
			 colorRec = new m3d::Color(150,150,150);
			 colorText = new m3d::Color(0,0,0);
			 bwallpaper = new m3d::Rectangle(0,0,320,240,*colorRec);
			 wallpaper = new m3d::Rectangle(0,0,400,240,*colorRec);
			 prompt = new m3d::Text("Press Start",*colorText);
			 prompt->setPosition(160,120);
			 //wallpaper = new m3d::Sprite();
		     //wallpaper->setTexture(*texture);
		     //wallpaper->setCenter(0,0);
		     //wallpaper->setScale(.5,.5);
		}
		void draw(){
			m3d::Screen * screen = GameManager::getScreen();

		    wallpaper->setPosition(0,0);
		    screen->drawTop(*wallpaper);
				screen->drawBottom(*bwallpaper);
				screen->drawBottom(*prompt);
		}
    void load(){};
    void unload(){};
    void update(){};
    void onEnter(){};
    void onExit(){};
};
