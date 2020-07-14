#include "../modules/cameraModule.hpp"

CameraModule::CameraModule(std::function<void(m3dCI::Sprite*)> t_callback) : Module::Module()
{
    m_buffer = nullptr;
    m_callback = t_callback;
    //C2D_SpriteSheetLoadFromMem
}

CameraModule::~CameraModule()
{
    
    CAMU_StopCapture(PORT_BOTH);
	CAMU_Activate(SELECT_NONE);
}

void CameraModule::Before()
{
    Util::PrintLine("Initializing camera");
    m_camHandle = (unsigned int) camInit();
	Util::PrintLine("camInit:" + std::to_string(m_camHandle));
	Util::PrintLine("CAMU_SetSize: " + std::to_string((unsigned int) CAMU_SetSize(SELECT_OUT1, SIZE_CTR_TOP_LCD, CONTEXT_A)));
    

	Util::PrintLine("CAMU_SetOutputFormat:" + std::to_string((unsigned int) CAMU_SetOutputFormat(SELECT_OUT1, OUTPUT_RGB_565, CONTEXT_A) ) );
    

	// TODO: For some reason frame grabbing times out above 10fps. Figure out why this is.
	Util::PrintLine("CAMU_SetFrameRate: " + std::to_string((unsigned int) CAMU_SetFrameRate(SELECT_OUT1, FRAME_RATE_10) ) );

	Util::PrintLine("CAMU_SetNoiseFilter: " + std::to_string((unsigned int) CAMU_SetNoiseFilter(SELECT_OUT1, true)));
	Util::PrintLine("CAMU_SetAutoExposure: " + std::to_string((unsigned int) CAMU_SetAutoExposure(SELECT_OUT1, true)));
	Util::PrintLine("CAMU_SetAutoWhiteBalance: " + std::to_string((unsigned int) CAMU_SetAutoWhiteBalance(SELECT_OUT1, true)));

	// TODO: Figure out how to use the effects properly.
	//printf("CAMU_SetEffect: 0x%08X\n", (unsigned int) CAMU_SetEffect(SELECT_OUT1, EFFECT_SEPIA, CONTEXT_A));

	Util::PrintLine("CAMU_SetTrimming: " + std::to_string((unsigned int) CAMU_SetTrimming(PORT_CAM1, false)));
	//Util::PrintLine("CAMU_SetTrimming: " + std::to_string((unsigned int) CAMU_SetTrimming(PORT_CAM2, false)));

    Util::PrintLine("CAMU_GetMaxBytes: " + std::to_string((unsigned int) CAMU_GetMaxBytes(&m_bufferSize, SCREEN_WIDTH, SCREEN_HEIGHT)));
	Util::PrintLine("CAMU_SetTransferBytes: " + std::to_string((unsigned int) CAMU_SetTransferBytes(PORT_CAM1, m_bufferSize, SCREEN_WIDTH, SCREEN_HEIGHT)));

	Util::PrintLine("CAMU_Activate: " + std::to_string((unsigned int) CAMU_Activate(SELECT_OUT1)));

	//Handle camReceiveEvent = 0;
	//Handle camReceiveEvent2 = 0;

	Util::PrintLine("CAMU_ClearBuffer: " + std::to_string((unsigned int) CAMU_ClearBuffer(PORT_CAM1)));
	//Util::PrintLine("CAMU_SynchronizeVsyncTiming: " + std::to_string((unsigned int) CAMU_SynchronizeVsyncTiming(SELECT_OUT1, SELECT_OUT2)));

	Util::PrintLine("CAMU_StartCapture: " + std::to_string((unsigned int) CAMU_StartCapture(PORT_CAM1)));
	Util::PrintLine("CAMU_PlayShutterSound: " + std::to_string((unsigned int) CAMU_PlayShutterSound(SHUTTER_SOUND_TYPE_MOVIE)));

    m_buffer = static_cast<u8*>(calloc(m_bufferSize, sizeof(u8)));
}

void CameraModule::During()
{
    //Util::PrintLine("cameraModule: update");
    //Util::PrintLine("CAMU_ClearBuffer: " + std::to_string((unsigned int) CAMU_ClearBuffer(PORT_CAM1)));
    //Util::PrintLine("CAMU_SetReceiving: " + std::to_string( (unsigned int) CAMU_SetReceiving(&m_camReceiveEvent, m_buffer, PORT_CAM1, SCREEN_SIZE, (s16) m_bufferSize)));
    //CAMU_SetReceiving(&camReceiveEvent2, buf + SCREEN_SIZE, PORT_CAM2, SCREEN_SIZE, (s16) m_bufferSize);

    //Util::PrintLine("svcWaitSynchronization: " + std::to_string((unsigned int) svcWaitSynchronization(m_camReceiveEvent, 300000000ULL)));
    //svcWaitSynchronization(camReceiveEvent2, WAIT_TIMEOUT);

    if(m3d::buttons::buttonPressed(m3d::buttons::Y))
    {
        m_finished = true;
    }


}

void CameraModule::onDraw()
{
    if(m_buffer  != nullptr)
        writePictureToFramebufferRGB565(gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL), m_buffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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

