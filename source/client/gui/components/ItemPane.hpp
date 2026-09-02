#pragma once

#include "client/renderer/Textures.hpp"
#include "world/inventory/Container.hpp"
#include "ScrollingPane.hpp"

class ItemPane : public ScrollingPane
{
public:
	class ICallback
	{
	public:
		virtual void onItemSelected(const ItemPane& itemPane, Container::StackID stackId) = 0;
		virtual void* getItems(const ItemPane& itemPane) = 0;
	};

public:
	ItemPane(ICallback& callback, Textures& textures, const IntRectangle& areaRect, int itemCount, int bottom, int screenHeight, bool isVertical);

protected:
	void _drawScrollBar(const ScrollBar& scrollBar);

public:
	void onSelect(int id, bool isSelected) override;

protected:
	Textures& m_textures;
	ICallback& m_callback;
	int m_screenHeight;
	bool m_bVertical;
	TextureAtlasSprite m_sprite1;
	TextureAtlasSprite m_sprite2;
};
