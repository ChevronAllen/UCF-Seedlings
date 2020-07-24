#include "sprite.hpp"
#include "../util.hpp"

namespace m3dCI {
    Sprite::Sprite() :
            m_posX(0),
            m_posY(0),
            m_centerX(0),
            m_centerY(0),
            m_opacity(255),
            m_index(0),
            m_scaleX(1.0f),
            m_scaleY(1.0f),
            m_rotation(0.f),
            m_blendStrength(0.f),
            m_spriteSheetPath(""),
            m_tintColor(m3d::Color(255, 255, 255, 255)) {
                updateTint();
                m_spriteSheet = nullptr;
            }

    Sprite::Sprite(const std::string& t_spriteSheet, int t_imageId) :
            m_posX(0),
            m_posY(0),
            m_centerX(0),
            m_centerY(0),
            m_opacity(255),
            m_scaleX(1.0f),
            m_scaleY(1.0f),
            m_rotation(0),
            m_blendStrength(0.f),
            m_tintColor(m3d::Color(255, 255, 255, 255)) {
                updateTint();
                setSpriteSheet(t_spriteSheet, t_imageId);
            }

	//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
	Sprite::~Sprite()
	{

	}

    void Sprite::setXPosition(int t_x) {
        m_posX = t_x;
        C2D_SpriteSetPos(&m_sprite, m_posX, m_posY);
    }

    int Sprite::getXPosition() {
        return m_posX;
    }

    void Sprite::setYPosition(int t_y) {
        m_posY = t_y;
        C2D_SpriteSetPos(&m_sprite, m_posX, m_posY);
    }

    int Sprite::getYPosition() {
        return m_posY;
    }

    void Sprite::setPosition(int t_x, int t_y) {
        m_posX = t_x;
        m_posY = t_y;
        C2D_SpriteSetPos(&m_sprite, m_posX, m_posY);
    }

    void Sprite::setPosition(m3d::Vector2f t_vector) {
        m_posX = static_cast<int>(t_vector.u);
        m_posY = static_cast<int>(t_vector.v);
        C2D_SpriteSetPos(&m_sprite, m_posX, m_posY);
    }

    void Sprite::moveX(int t_offset) {
        m_posX += t_offset;
        C2D_SpriteSetPos(&m_sprite, m_posX, m_posY);
    }

    void Sprite::moveY(int t_offset) {
        m_posY += t_offset;
        C2D_SpriteSetPos(&m_sprite, m_posX, m_posY);
    }

    void Sprite::move(int t_offsetX, int t_offsetY) {
        m_posX += t_offsetX;
        m_posY += t_offsetY;
        C2D_SpriteSetPos(&m_sprite, m_posX, m_posY);
    }

    void Sprite::move(m3d::Vector2f t_vector) {
        m_posX += static_cast<int>(t_vector.u);
        m_posY += static_cast<int>(t_vector.v);
        C2D_SpriteSetPos(&m_sprite, m_posX, m_posY);
    }

    void Sprite::setCenterX(int t_x) {
        m_centerX = t_x;
        C2D_SpriteSetCenterRaw(&m_sprite, m_centerX, m_centerY);
    }

    int Sprite::getCenterX() {
        return m_centerX;
    }

    void Sprite::setCenterY(int t_y) {
        m_centerY = t_y;
        C2D_SpriteSetCenterRaw(&m_sprite, m_centerX, m_centerY);
    }

    int Sprite::getCenterY() {
        return m_centerY;
    }

    void Sprite::setCenter(int t_x, int t_y) {
        m_centerX = t_x;
        m_centerY = t_y;
        C2D_SpriteSetCenterRaw(&m_sprite, m_centerX, m_centerY);
    }

    void Sprite::setCenter(m3d::Vector2f t_vector) {
        m_centerX = static_cast<int>(t_vector.u);
        m_centerY = static_cast<int>(t_vector.v);
        C2D_SpriteSetCenterRaw(&m_sprite, m_centerX, m_centerY);
    }

    void Sprite::setXScale(float t_scale) {
        m_scaleX = t_scale;
        C2D_SpriteSetScale(&m_sprite, m_scaleX, m_scaleY);
    }

    float Sprite::getXScale() {
        return m_scaleX;
    }

    void Sprite::setYScale(float t_scale) {
        m_scaleY = t_scale;
        C2D_SpriteSetScale(&m_sprite, m_scaleX, m_scaleY);
    }

    float Sprite::getYScale() {
        return m_scaleY;
    }

    void Sprite::setScale(float t_xScale, float t_yScale) {
        m_scaleX = t_xScale;
        m_scaleY = t_yScale;
        C2D_SpriteSetScale(&m_sprite, m_scaleX, m_scaleY);
    }

    void Sprite::scaleX(float t_delta) {
        m_scaleX += t_delta;
        C2D_SpriteSetScale(&m_sprite, m_scaleX, m_scaleY);
    }

    void Sprite::scaleY(float t_delta) {
        m_scaleY += t_delta;
        C2D_SpriteSetScale(&m_sprite, m_scaleX, m_scaleY);
    }

    void Sprite::scale(float t_deltaX, float t_deltaY) {
        m_scaleX += t_deltaX;
        m_scaleY += t_deltaY;
        C2D_SpriteSetScale(&m_sprite, m_scaleX, m_scaleY);
    }

    void Sprite::setRotation(float t_rotation, bool t_radians) {
        m_rotation = t_radians ?
                        t_rotation * (180.0/3.141592653589793238463) :
                        t_rotation;
        C2D_SpriteSetRotationDegrees(&m_sprite, m_rotation);
    }

    void Sprite::rotate(float t_delta, bool t_radians) {
        m_rotation += t_radians ?
                        t_delta * (180.0/3.141592653589793238463) :
                        t_delta;
        C2D_SpriteSetRotationDegrees(&m_sprite, m_rotation);
    }

    void Sprite::setTint(m3d::Color t_color) {
        m_tintColor = t_color;
        updateTint();
    }

    m3d::Color Sprite::getTint() {
        return m_tintColor;
    }

    void Sprite::setBlend(float t_blend) {
        if (t_blend < 0.f) m_blendStrength = 0.f;
        else if (t_blend > 1.f) m_blendStrength = 1.f;
        else m_blendStrength = t_blend;

        updateTint();
    }

    float Sprite::getBlend() {
        return m_blendStrength;
    }

    void Sprite::setOpacity(unsigned int t_opacity) {
        m_opacity = t_opacity;
        updateTint();
    }

    float Sprite::getOpacity() {
        return m_opacity;
    }

    void Sprite::setSpriteSheet(const std::string& t_spriteSheet, int t_imageId) {
        m_spriteSheetPath = t_spriteSheet;
        m_index = t_imageId;
        m_spriteSheet = C2D_SpriteSheetLoad(m_spriteSheetPath.c_str());

        C2D_SpriteFromSheet(&m_sprite, m_spriteSheet, m_index);
    }

    void Sprite::setTexture(m3d::Texture& t_texture)
	{
		//This is the dumbest thing I have ever encoutered as a developer.
		// When loading the sprite, the position of the Sprite object resets to 0,0.
		//This implementation just resets the previous values. 
		int x = getXPosition();
		int y = getYPosition();
        C2D_SpriteFromImage(&m_sprite, t_texture.getImage());

		setPosition(x, y);
    }

    const std::string& Sprite::getSpriteSheet() {
        return m_spriteSheetPath;
    }

    void Sprite::draw(m3d::RenderContext t_context) {
        C2D_DrawSpriteTinted(&m_sprite, &m_imageTint);
    }

    // private methods
    void Sprite::updateTint() {
        C2D_Tint tint = {
            m3d::Color(m_tintColor.getRed(), m_tintColor.getGreen(), m_tintColor.getBlue(), m_opacity).getRgba8(),
            m_blendStrength
        };

        m_imageTint = { tint, tint, tint, tint };
    }

	m3d::BoundingBox m3dCI::Sprite::getBoundingBox()
	{
		int p_w = m_sprite.params.pos.w;
		int p_h = m_sprite.params.pos.h;

		return m3d::BoundingBox(m_posX, m_posY, p_w, p_h);
	}


    m3dCI::Sprite* m3dCI::Sprite::createFromSheet(C2D_SpriteSheet& t_sheet,int t_index)
    {
        Sprite* sprite = new Sprite();

        sprite->m_spriteSheet = t_sheet;
        sprite->m_index = t_index;
        C2D_SpriteFromSheet(&(sprite->m_sprite), sprite->m_spriteSheet, sprite->m_index);

        return sprite;
    }

	int m3dCI::Sprite::GetHeight()
	{
		return m_sprite.params.pos.h;
	}

	int m3dCI::Sprite::GetWidth()
	{
		return m_sprite.params.pos.w;
	}

} /* m3d */
