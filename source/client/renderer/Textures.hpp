/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp
	
	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#pragma once
#include <map>

#include "client/options/Options.hpp"
#include "client/app/AppPlatform.hpp"
#include "DynamicTexture.hpp"
#include "texture/TextureAtlas.hpp"
#include "common/utility/HashMap.hpp"

#define C_TEX_TERRAIN     "terrain.png"
#define C_TEX_ITEMS       "gui/items.png"
#define C_TEX_GUI_BLOCKS  "gui/gui_blocks.png"
#define C_TEX_TOUCHGUI    "gui/touchgui.png"

#define C_TEX_SPRITESHEET "gui/spritesheet.png"
#define C_TEX_SPRITESHEET_WIDTH  (128)
#define C_TEX_SPRITESHEET_HEIGHT (128)

class DynamicTexture; // in case we are being included from DynamicTexture. We don't store complete references to that

class Textures
{
protected:
	typedef HashMap<std::string, TextureData*> TextureMap;
	typedef HashMap<std::string, TextureAtlas*> TextureAtlasMap;

public:
	TextureData* loadTexture(const std::string& name, bool bRequired);
	TextureData* loadAndBindTexture(const std::string& name, bool isRequired = true, unsigned int textureUnit = 0);
	TextureData* getTextureData(const std::string& name, bool isRequired);
	TextureData* uploadTexture(const std::string& name, TextureData& t);
	TextureAtlas* getTextureAtlas(const std::string& name);
	void unloadAll();
	void clear();
	void tick();
	void addDynamicTexture(DynamicTexture* pTexture);
	void addSprite(const std::string& name, TextureAtlas& atlas);
	void setupAtlas(TextureAtlas&);
	void setupAtlases(bool forceReset = false);

	const TextureAtlasSprite* getGuiSprite(const std::string&);

	// set smoothing for next texture to be loaded
	void setSmoothing(bool b)
	{
		m_bBlur = b;
	}

	// set smoothing for next texture to be loaded
	void setClampToEdge(bool b)
	{
		m_bClamp = b;
	}

	Textures();
	~Textures();

private:
	static bool MIPMAP;

protected:
	TextureMap m_textures;
	TextureAtlasMap m_atlases;
	int m_currBoundTex;
	bool m_bClamp;
	bool m_bBlur;
	std::vector<DynamicTexture*> m_dynamicTextures;
	TextureAtlas m_guiAtlas;
	TextureAtlas m_filteredGuiAtlas;
};

