#pragma once
#include <vector>
#include <SDL.h>
#include <iostream>
// texture manager, this is a global singleton (only one is allowed at once and it can be accessed globally within the application)
// this class takes care of loading images into SDL_Textures and allows them to be queried by name, the concept here is that there is 
// no reason to load the same image more than once. So if you call LoadTexture() on a texture that is already loaded, it will return
// the one in memory and if none is loaded, will load the new one and return that instead.
// all textures are referenced by index value (an integer) -1 denotes a "null" texture
// makes extensive use of logging to let you know what has been loaded
// note: It can be useful to parse a whole directory (including subdirectories) of textures. That is what LoadAllTexturesFromDirectory function is for
// also note: Usually in industry this class would also deal with compressed and archived textures within a zip file, allowing you to override
// the loading by placing a local file version within a local directory at the same path as one in the zip file directory structure
// I'll leave that for you to think about.

// simple data structure used to associate a texture pointer with a path for that texture
struct TexInfo_t
{
	SDL_Texture* pTexture = NULL;
	std::string TexturePath = "";
	std::string TextureFileName = "";
	bool IsArchived = false;	// this would be useful to know if the texture was loaded from a zip file for instance
	// you might need to store the archive index or name/id here if you add archive loading
};

struct SpriteFrame
{
	std::string name;
	SDL_Rect srcRect;
	unsigned int textureindex;
	unsigned int ownersequence;
};

enum Sequence_Type
{
	Seq_Once = 0,
	Seq_Loop = 1,
	Seq_PingPong = 2,
};


struct SpriteSequence
{
	std::string name;
	int playbackrate;
	Sequence_Type sequencetype;
	std::vector<unsigned int>mFrameIndices;
};

/// Note this code relies on SDL2_Image, so you must SDL_Init before this can work properly, also call SetRenderer

class TextureManager
{
public:
	~TextureManager();

	static TextureManager* GetInstance(); // get the pointer to the global singleton instance, create it if it doesn't exist...

	// public member functions
	// NOTE: MUST CALL SET RENDERER BEFORE MOST OF THESE FUNCTIONS WILL WORK!!

	// load an individual texture, store the path used to access it
	int LoadTexture(std::string path);

	// load a specific sprite outputted by e.g. TexturePacker and read the texture + sprite frames
	void LoadSpriteFromJSONFile(std::string path);

	// sprite sequence handling functions
	void AutoParseFramesIntoSequences();
	unsigned int NumSequences();
	unsigned int AddSequence(std::string name, int defaultplaybackrate = 100);
	unsigned int AddFrameToSequence(unsigned int sequenceindex, unsigned int frameindex);
	const SpriteSequence* GetSequence(std::string sequenceName);
	unsigned int GetSpriteSequences(std::vector<SpriteSequence>& sequences, std::string spritename);

	const TexInfo_t* GetSprite(std::string sequenceName);

	// load all supported textures from a specific directory, optionally recurse into subdirectories
	int LoadAllTexturesFromDirectory(std::string path, bool IncludeSubdirectories = true);

	SDL_Texture* GetTextureFromIndex(unsigned int index);

	const SpriteFrame* GetFrame(unsigned int index);

	void SetRenderer(SDL_Renderer* pRenderer) { m_pRenderer = pRenderer; };

private:
	TextureManager();
	// private data.. 
	// textures
	std::vector<TexInfo_t> mTextures;
	// sequences of frames
	std::vector<SpriteSequence> mSequences;
	// individual frames of a sequence
	std::vector<SpriteFrame> mFrames;
	// the single instance of this class as static member
	static TextureManager* m_pInstance;
	// pointer to the renderer we are using
	SDL_Renderer* m_pRenderer = nullptr;
};