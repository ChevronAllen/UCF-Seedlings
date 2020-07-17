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

void CameraModule::initialize()
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

void CameraModule::updateActions()
{
    //Util::PrintLine("cameraModule: update");
    //Util::PrintLine("CAMU_ClearBuffer: " + std::to_string((unsigned int) CAMU_ClearBuffer(PORT_CAM1)));
    //Util::PrintLine("CAMU_SetReceiving: " + std::to_string( (unsigned int) CAMU_SetReceiving(&m_camReceiveEvent, m_buffer, PORT_CAM1, SCREEN_SIZE, (s16) m_bufferSize)));
    //CAMU_SetReceiving(&camReceiveEvent2, buf + SCREEN_SIZE, PORT_CAM2, SCREEN_SIZE, (s16) m_bufferSize);

    //Util::PrintLine("svcWaitSynchronization: " + std::to_string((unsigned int) svcWaitSynchronization(m_camReceiveEvent, 300000000ULL)));
    //svcWaitSynchronization(camReceiveEvent2, WAIT_TIMEOUT);

    if(m3d::buttons::buttonPressed(m3d::buttons::Y))
    {
        //C2D_SpriteSheetLoadFromMem()
        Util::PrintLine("test camera");
        C3D_TexLoadImage(&m_tex,m_buffer,GPU_TEXFACE_2D,0);
        
        std::stringstream str;
        str << "tex: " << &m_tex << ", " << "w: " << m_tex.width << ", " << "h: " << m_tex.height << std::endl; 
        Util::PrintLine(str.str());
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

/*
bool CameraModule::loadPng(const void* t_fp, bool t_buffer = true) {
    m3dCI::Texture tex; 
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); 

    png_infop info = png_create_info_struct(png);

    if(setjmp(png_jmpbuf(png)))
    {
        png_destroy_read_struct(&png, &info, NULL);
        return false;
    }

    if (t_buffer) {
        png_set_read_fn(png, (png_voidp) t_fp,
                        [](png_structp ptr, png_bytep data, png_size_t len) {
                            unsigned int* addr = (unsigned int*) png_get_io_ptr(ptr);
                            memcpy(data, (void*) *addr, len);
                            *addr += len;
                        });
    } else {
        png_set_read_fn(png, (png_voidp) t_fp,
                        [](png_structp ptr, png_bytep data, png_size_t len) {
                            fread(data, 1, len, (FILE*) png_get_io_ptr(ptr));
                        });
    }

    png_read_info(png, info);
    
    tex.m_width = png_get_image_width(png, info);
    tex.m_height = png_get_image_height(png, info);

    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth  = png_get_bit_depth(png, info);

    // Read any color_type into 8bit depth, ABGR format.
    // See http://www.libpng.org/pub/png/libpng-manual.txt

    if(bit_depth == 16)
        png_set_strip_16(png);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    // if color_type doesn't have an alpha channel, fill it with 0xff.
    if(color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if(color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    // output ABGR
    png_set_bgr(png);
    png_set_swap_alpha(png);

    png_read_update_info(png, info);

    png_bytep* row_pointers = static_cast<png_byte**>(malloc(sizeof(png_bytep) * tex.m_height));
    for(int y = 0; y < tex.m_height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    png_read_image(png, row_pointers);

    if (!t_buffer) fclose((FILE*) t_fp);
    png_destroy_read_struct(&png, &info, NULL);

    //unloadImage(m_image);
    if (m_image.tex) C3D_TexDelete(m_image.tex);

    tex.m_texture = static_cast<C3D_Tex*>(malloc(sizeof(C3D_Tex)));
    tex.m_image.tex = tex.m_texture;
    tex.m_subtexture.width = tex.m_width;
    tex.m_subtexture.height = tex.m_height;
    tex.m_subtexture.left = 0.0f;
    tex.m_subtexture.top = 1.0f;
    tex.m_subtexture.right = tex.m_width / (float) m3dCI::Texture::getNextPow2(tex.m_width);
    tex.m_subtexture.bottom = 1.0 - (tex.m_height / (float) m3dCI::Texture::getNextPow2(tex.m_height));
    tex.m_image.subtex = &tex.m_subtexture;

    C3D_TexInit(tex.m_image.tex, m3dCI::Texture::getNextPow2(tex.m_width), m3dCI::Texture::getNextPow2(tex.m_height), GPU_RGBA8);

    memset(tex.m_image.tex->data, 0, tex.m_image.tex->size);

    for(int j = 0; j < tex.m_height; j++) {
        png_bytep row = row_pointers[j];
        for(int i = 0; i < tex.m_width; i++) {
            png_bytep px = &(row[i * 4]);
            u32 dst = ((((j >> 3) * (m3dCI::Texture::getNextPow2(tex.m_height) >> 3) + (i >> 3)) << 6) + ((i & 1) | ((j & 1) << 1) | ((i & 2) << 1) | ((j & 2) << 2) | ((i & 4) << 2) | ((j & 4) << 3))) * 4;

            memcpy(static_cast<char*>(tex.m_image.tex->data) + dst, px, sizeof(u32)); 
        }
    }

    // C3D_TexSetFilter(m_texture, GPU_LINEAR, GPU_LINEAR);
    C3D_TexSetWrap(tex.m_image.tex, GPU_CLAMP_TO_BORDER, GPU_CLAMP_TO_BORDER);
    tex.m_image.tex->border = 0xFFFFFFFF;

    return true;
}
*/

