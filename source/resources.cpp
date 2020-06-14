#include "resources.h"


ResourceManager* ResourceManager::_instance = NULL;
std::map<std::string, void*>* ResourceManager::_hashmap = NULL;
m3d::Texture* ResourceManager::_error = NULL;
std::vector<std::string> _preloadTextures = {};

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
    
}

void ResourceManager::initialize()
{
    //  If no instance exists, construct one
    if(_instance == NULL)
    {
        _instance = new ResourceManager();
    }

    //  set all fields and stores;
    if(_hashmap != NULL){
        //UnloadAll();
    }
    _instance->_hashmap = new std::map<std::string, void*>();   

    return;

}

ResourceManager* ResourceManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ResourceManager();
    }
    return _instance;
}

void* ResourceManager::readFile(std::string path)
{
    char* buffer;
    
    FILE* fp = fopen( path.c_str(), "rb");
    if(fp == NULL){
        Util::getInstance()->PrintLine("unable to access file '" + path + "'");
    }

   
    fseek(fp,0L, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    buffer = (char*)calloc(size, sizeof(char));
    fread(buffer,sizeof(char),size,fp);
    fclose(fp);


    return (void*)buffer;
}

void* ResourceManager::loadFile(std::string path)
{
    void* mem = NULL;
    try
    {
        mem = readFile(path);
    }
    catch(const std::exception& e)
    {
        Util::getInstance()->PrintLine( e.what() );
        mem = NULL;
    }

    (*_hashmap)[path] = mem;
    return mem;
}

m3d::Texture* ResourceManager::loadTexture(std::string path)
{
    m3d::Texture* texture = new Texture();
    std::string fullPath = ROMFS_PATH;
    fullPath = fullPath.append(path); 

    try
    {

        if( texture->loadFromFile(fullPath) == false)
        {
            Util::getInstance()->PrintLine("failed to load from file " + (fullPath));
            return NULL;
        }
    }
    catch(const std::exception& e)
    {
        Util::getInstance()->PrintLine(e.what());
        return NULL;
    }
    catch(const std::string& e)
    {
        Util::getInstance()->PrintLine(e);
        return NULL;
    }
    catch(const int& e)
    {
        Util::getInstance()->PrintLine("error code: " + e);
        return NULL;
    }

    (*_hashmap)[path] = texture;
    return texture;

}

void ResourceManager::loadTextureBatch(std::vector<std::string> arr)
{
    
    for(std::string path : arr)
    {
        loadTexture(path);
    }
}

//  TODO: test returns when key is not found
m3d::Texture* ResourceManager::getTexture(std::string path)
{
    m3d::Texture* tex;

    //std::string fullPath  = TEXTURE_PATH;
    //fullPath.append(id);

    tex = static_cast<m3d::Texture*>( (*_hashmap)[path] ); 
    
    return tex;
}

