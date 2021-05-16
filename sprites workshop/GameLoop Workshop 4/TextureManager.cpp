//#include "stdafx.h"
#include "TextureManager.h"
#include "SDL_image.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <filesystem>

// the "Using" keyword tells the C++ compiler that we are using the nlohmann::json namespace so can just call it json
using nlohmann::json;

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	SDL_Log("Textures Unloading");
	for (TexInfo_t t: mTextures)
	{
		SDL_DestroyTexture(t.pTexture);
		t.pTexture = NULL;
	}
	



}

TextureManager* TextureManager::m_pInstance = nullptr;

TextureManager* TextureManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new TextureManager();
		SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Texture Manager Created %p", m_pInstance);
	}
	return m_pInstance;
}

int TextureManager::LoadTexture(std::string path)
{
	if (!m_pRenderer) return -1;
	TexInfo_t texinfo;
	texinfo.pTexture = IMG_LoadTexture(m_pRenderer, path.c_str());
	texinfo.TexturePath = path;
	texinfo.TextureFileName = path;
	mTextures.push_back(texinfo);
	return mTextures.size() - 1;
}

void TextureManager::LoadSpriteFromJSONFile(std::string path)
{
	std::ifstream infile(path);
	json j;
	infile >> j;

	std::string path_to_json_file = path.substr(0, path.find_last_of('/'));

	std::string imagefilename = j["meta"]["image"].get<std::string>();

	// attempt to load the sprite images via the texture manager if the meta of the json file contains the png image filename and the image is in the current
	// path directory
	SDL_Log(imagefilename.c_str());
	imagefilename = path_to_json_file + "/" + imagefilename;
	SDL_Log(imagefilename.c_str());
	// prepend the path to the image file
	int currenttextureindex = LoadTexture(imagefilename);

	for (auto& element : j["frames"])
	{
		SpriteFrame frame;
		frame.name = element["filename"];
		SDL_Rect rect;
		rect.x = element["frame"]["x"];
		rect.y = element["frame"]["y"];
		rect.w = element["frame"]["w"];
		rect.h = element["frame"]["h"];

		frame.srcRect = rect;
		frame.ownersequence = -1;
		frame.textureindex = currenttextureindex;
		mFrames.push_back(frame);
	}
	AutoParseFramesIntoSequences();

}
// a function that uses the sprite naming convention of TexturePacker to parse out sprite sequences frame by frame
// basically, it looks for the last "-" character and anything before it is used as the sequence name, anything after is a number
// so adventurer-run-001.png becomes adventurer-run sequence with a frame added to it
void TextureManager::AutoParseFramesIntoSequences()
{
	unsigned int currentSeqIndex = 1;
	unsigned int framenum = 0;

	// clear out sequences because we're going to redo them?
	mSequences.clear();

	for (SpriteFrame& frame : mFrames)
	{
		std::size_t found = frame.name.find_last_of('-');
		std::string seq = frame.name.substr(0, found);

		// add sequence will either add a new sequence, or return the index of a current sequence of the same name
		currentSeqIndex = AddSequence(seq);

		AddFrameToSequence(currentSeqIndex, framenum);
		framenum++;
	}

	// now verify we've parsed correctly.. print out all sequences and frames within them
	for (SpriteSequence& seq : mSequences)
	{
		
		std::cout << "Sequence Named: " << seq.name << " Contains: \n";
		for (unsigned int n : seq.mFrameIndices)
		{
			std::cout << "Frame: " << mFrames[n].name << " at index " << n << "\n";
		}
	}
}

// TODO: complete this and load all png's recursively from a given path (if include subdirectories is true)
int TextureManager::LoadAllTexturesFromDirectory(std::string path, bool IncludeSubdirectories)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Texture loading from directory called %p", m_pInstance);

	std::filesystem::directory_entry directory = std::filesystem::directory_entry(path);
	

	for (std::filesystem::directory_entry file : std::filesystem::directory_iterator(directory))
	{
		std::string filepath = file.path().string();
		if (file.is_directory() && IncludeSubdirectories)
		{
			
			LoadAllTexturesFromDirectory(filepath + '/', IncludeSubdirectories);
		}
		std::string extension = filepath.substr(filepath.find_last_of('.') + 1);

			if (extension == "png")
			{
				int textureIndex = LoadTexture(filepath);
				//loads texture and logging success and index
				if (textureIndex != -1) {
					SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "texture from png file %s loaded at Index %i", filepath.c_str() , textureIndex);
				}
		}
			if (extension == "json")
			{
				SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "JSON file attempted to load: %s", filepath.c_str());
				LoadSpriteFromJSONFile(filepath);
				
			}


		else if (file.is_regular_file())
		{
			//int textureIndex = LoadTexture(file.path().string());
			////loads texture and logging success and index
			//if ( textureIndex!= -1) {
			//	SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "texture from file %s loaded at Index %i",filepath.c_str() ,textureIndex);
			//}

				continue;

		}

		
	}
	

	return 0;

}

// given a texture index value, return the associated pointer to texture for it
SDL_Texture* TextureManager::GetTextureFromIndex(unsigned int index)
{
	if (index >= mTextures.size())
	{
		return nullptr;
	}
	return mTextures[index].pTexture;
}

// given an index for a sprite frame, return the SpriteFrame structure pointer
const SpriteFrame* TextureManager::GetFrame(unsigned int index)
{
	if (index >= mFrames.size())
	{
		return nullptr;
	}
	return &mFrames[index];
}



// adds a new sequence, returns the index of that sequence in the mSequences vector
unsigned int TextureManager::AddSequence(std::string name, int defaultplaybackrate)
{
	unsigned int index = 0;
	// iterate existing sequences, try and find one that already exists..
	for (SpriteSequence& s : mSequences)
	{
		if (s.name == name)
		{
			return index;
		}
		index++;
	}

	SpriteSequence seq;
	seq.name = name;
	seq.playbackrate = defaultplaybackrate;
	seq.sequencetype = Seq_Loop;
	mSequences.push_back(seq);
	return mSequences.size() - 1;
}

// adds a newly created frame into the specified sequence
unsigned int TextureManager::AddFrameToSequence(unsigned int sequenceindex, unsigned int frameindex)
{
	if (sequenceindex <= mSequences.size())
	{
		mSequences[sequenceindex].mFrameIndices.push_back(frameindex);
		return mSequences[sequenceindex].mFrameIndices.size() - 1;
	}
	return 0;
}
//Returns a spriteSequence pointer to a named sequence
const SpriteSequence* TextureManager::GetSequence(std::string sequenceName)
{
	//& for passing through reference!!!
	for (SpriteSequence &seq : mSequences)
	{
		if (seq.name == sequenceName)
		{
			SDL_Log("Sequence %s successfully assigned!!", sequenceName.c_str());
			return &seq;
		}
	}
	SDL_Log("Sequence %s Not found. Please check spelling.", sequenceName.c_str());
	return NULL;
}

// copies the sprite sequences with the appropriate sprite name as start into the std::vector of sprite sequences passed in by reference
unsigned int TextureManager::GetSpriteSequences(std::vector<SpriteSequence>& sequences, std::string spritename)
{
	unsigned int sequencescopied = 0;
	for (auto seq : mSequences)
	{
		if (seq.name.find(spritename) != std::string::npos)
		{
			sequences.push_back(seq);
			sequencescopied++;
		}
	}
	return sequencescopied;
}