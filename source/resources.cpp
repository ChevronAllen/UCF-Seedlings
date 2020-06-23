#include "resources.h"


//ResourceManager* ResourceManager::_instance = NULL;
std::map<std::string, void*> ResourceManager::_hashmap = {};
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
    //getInstance();
    _hashmap.clear();

    return;
}

/*
ResourceManager* ResourceManager::getInstance()
{
    if(_instance == NULL)
    {
        _instance = new ResourceManager();
    }
    return _instance;
}
*/

void* ResourceManager::readFile(std::string path)
{
    char* buffer = NULL;
    FILE* fp = fopen( path.c_str(), "rb");

    if(fp == NULL){
        Util::getInstance()->PrintLine("unable to access file '" + path + "'");
    }

   
    fseek(fp,0L, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    buffer = (char*)calloc(size+1, sizeof(char));
    fread(buffer,sizeof(char),size,fp);
    /*
    */
    fclose(fp);

    return (void*)buffer;
}

void* ResourceManager::loadFile(std::string path)
{
    void* mem = NULL;
    std::string fullpath = ROMFS_PATH;
    fullpath.append(path);

    try
    {
        mem = readFile(fullpath);
    }
    catch(const std::exception& e)
    {
        Util::getInstance()->PrintLine( e.what() );
        mem = NULL;
    }

    _hashmap[path] = mem;
    return mem;
}

m3d::Texture* ResourceManager::loadTexture(std::string path)
{
    m3d::Texture* texture = new Texture();
    std::string fullPath = ROMFS_PATH;
    fullPath = fullPath.append(path); 

    /*
    texture->loadFromFile(fullPath);


    

    //try
    //{

        if( texture->loadFromFile(fullPath) == false)
        {
            Util::getInstance()->PrintLine("failed to load from file " + (fullPath));
            return NULL;
        }
    //}
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
    */
    _hashmap[path] = texture;
    return texture;

}

std::vector<std::string> ResourceManager::readSpritesheet(std::string path)
{
    std::vector<std::string> ret;
    std::ifstream fs (path);
    Util::PrintLine(path);
    if(fs.is_open())
    {   
        std::string line;
        while(std::getline(fs,line))
        {
            if(line.size() > 3)
            {
                int start = line.find_first_not_of(" \n\t\f\r\v");
                int end = line.find_last_not_of(" \n\t\f\r\v");
                
                ret.push_back(line.substr(start, end-start+1) );
            }
        }
    }
     


    return ret;
}

std::vector<m3dCI::Sprite*> ResourceManager::loadSpritesheet(std::string path)
{
    std::string fullPath = ROMFS_PATH;
    std::string defPath , sheetPath;
    std::vector<std::string> spriteNames; 
    std::vector<m3dCI::Sprite*> ret;

    fullPath = defPath = sheetPath = fullPath.append(path);
    defPath = defPath.append(".t3s");
    sheetPath = sheetPath.append(".t3x");
    
    C2D_SpriteSheet sheet = C2D_SpriteSheetLoad(sheetPath.c_str());
    
    std::vector<std::string> names = readSpritesheet(defPath);
    Util::PrintLine( std::to_string(names.size()) );

    _hashmap[sheetPath] = &sheet;

    for (unsigned int i = 1; i < names.size(); i++)
    {
        Util::PrintLine(names[i]);
        _hashmap[names[i]] = m3dCI::Sprite::createFromSheet(sheet,i-1);
        ret.push_back( static_cast<m3dCI::Sprite*>( _hashmap[names[i]]) );
/*
*/
    }
    return ret;
}


//  TODO: test returns when key is not found
m3d::Texture* ResourceManager::getTexture(std::string path)
{
    m3d::Texture* tex;

    //std::string fullPath  = TEXTURE_PATH;
    //fullPath.append(id);

    tex = static_cast<m3d::Texture*>( _hashmap[path] ); 
    
    return tex;
}

m3dCI::Sprite* ResourceManager::getSprite(std::string path)
{
    m3dCI::Sprite* tex;

    //std::string fullPath  = TEXTURE_PATH;
    //fullPath.append(id);

    tex = static_cast<m3dCI::Sprite*>( _hashmap[path] ); 
    
    return tex;
}

