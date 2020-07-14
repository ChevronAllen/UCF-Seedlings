#include "../modules/cameraModule.hpp"

CameraModule::CameraModule(std::function<void(m3dCI::Sprite*)> callback) : Module::Module()
{
    m_buffer = static_cast<u8*>(calloc(SCREEN_HEIGHT*SCREEN_WIDTH, sizeof(u8)));
    //C2D_SpriteSheetLoadFromMem
}

CameraModule::~CameraModule()
{

}

void CameraModule::Before()
{

}

void CameraModule::During()
{
    //Util::PrintLine("cameraModule: update");
    if(m3d::buttons::buttonPressed(m3d::buttons::Y))
    {
        m_finished = true;
    }
}

void CameraModule::writePictureToFramebufferRGB565(void *fb, void *img, u16 x, u16 y, u16 width, u16 height) {
	u8 *fb_8 = (u8*) fb;
	u16 *img_16 = (u16*) img;
	int i, j, draw_x, draw_y;
	for(j = 0; j < height; j++) {
		for(i = 0; i < width; i++) {
			draw_y = y + height - j;
			draw_x = x + i;
			u32 v = (draw_y + draw_x * height) * 3;
			u16 data = img_16[j * width + i];
			uint8_t b = ((data >> 11) & 0x1F) << 3;
			uint8_t g = ((data >> 5) & 0x3F) << 2;
			uint8_t r = (data & 0x1F) << 3;
			fb_8[v] = r;
			fb_8[v+1] = g;
			fb_8[v+2] = b;
		}
	}
}

void CameraModule::onDraw()
{
    writePictureToFramebufferRGB565(gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL), m_buffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}