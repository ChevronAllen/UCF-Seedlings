/**
 *  @file resources.h
 *  @brief Defines the ResourceManager class and any other structures to handle files and assets.
 *  
 */
#pragma once
#include <stdlib.h> 
#include <string.h> 
#include <iostream>
#include <fstream>
#include <exception>
#include <map>
#include <array>

#include <m3dia.hpp>

#include"m3diaLibCI/sprite.hpp"
#include "util.hpp"

#ifdef DEBUG
#define RESOURCE_DEBUG
#endif

#define ROMFS_PATH      "romfs:/"
#define TEXTURE_PATH    "romfs:/gfx/"
#define AUDIO_PATH      "romfs:/sfx/"
#define TEXTURE_EXT     {"png","jpg","bmp"}
#define SOUND_EXT       {"mp3", "wav"}


/** @class ResourceManager "resources.h"
 *  Static Resource Managment class.
 *  Load and unload resources from the ROM file system to memory. 
 *  Using this prevents multiple structures loading a single resource and consuming more memory than necessary
 * 
 *  @todo Audio and multiple filetypes
 */
class ResourceManager final
{
private:
    
    ResourceManager();
    ~ResourceManager();
    
    /**
     *  @brief Hash table of loaded assets
     *  stores pointers to memory indexed by a string.
     */
    static std::map<std::string, void*> _hashmap;

    /**
     *  @brief Default texture
     */
    static m3d::Texture * _error;
    
    static std::vector<std::string> _preloadTextures;

    /**
     *  @brief Read filenames from Spritesheet
     *  
     *  @param path file path relative to the assets folder
     *  @return list of asset file names relative to the spritesheet
     */
    static std::vector<std::string> readSpritesheet(std::string path);

public:
    
    

    /**
     *  @brief Initializes the Resource Manager
     *  This should be called early in the program to load default assets, singleton instance, and hash table
     */
    static void initialize();

    /**
     *  @brief Reads a File from the ROM file system, but does not load it into the resource manager
     *  @param path file path relative to the rom file system
     *  @returns pointer to the retrieved file data
     */
    static void* readFile(std::string path);

    /**
     *  @brief Loads a Texture Asset
     *  Loads a Texture asset from the ROM file system into the Resource Manager
     *  @param path file path relative to the rom file system
     *  @returns false if the texture couldnt be loaded
     */
    static m3d::Texture* loadTexture(std::string path);

    /**
     *  @brief  Loads a sprite sheet and generates sprites from its indexes. 
     *  sprites are stored by filename within the ResourceManager
     *  @param path path to the spritesheet relative to the asset folder (no extension)
     *  @returns array of loaded sprites
     */
    static std::vector<m3dCI::Sprite*> loadSpritesheet(std::string path);

    /**
     *  @brief Loads a Sound asset
     *  Loads a Sound asset from the ROM file system into the Resource Manager
     *  @param id unique identifier of the asset
     *  @param path file path relative to the rom file system
     *  @returns pointer to the loaded resource
     */
    static m3d::Sound* loadSound(std::string id, std::string path);

    /**
     *  Loads an asset from the ROM file system into the Resource Manager
     *  @param path file path relative to the rom file system
     *  @returns pointer to the loaded resource
     */
    static void* loadFile(std::string path);


    //static m3d::Sprite* loadSpritesheet(std::string,int);

    /**
     *  Unloads all assets from the Resource manager
     */
    static void UnloadAll();

    /**
     *  Unloads an asset from the Resource Manager
     *  @param path unique identifier of the asset
     */
    static void Unload(std::string path);

    
    static m3d::Texture* getTexture(std::string);

    /**
     *  @brief Attempts to retrieve a preloaded sprite
     *  @returns m3dCI::Sprite* to loaded sprite
     */
    static m3dCI::Sprite* getSprite(std::string);

};