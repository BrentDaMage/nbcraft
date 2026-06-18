#include "ItemPane.hpp"
#include "client/gui/Gui.hpp"

ItemPane::ItemPane(ICallback& callback, Textures& textures, const IntRectangle& areaRect, int itemCount, int bottom, int screenHeight, bool isVertical)
    : ScrollingPane(
        (isVertical ? FLAG_NOSCROLLH : FLAG_NOSCROLLV) | FLAG_SCROLLFADE,
        areaRect,
        isVertical ? IntRectangle(0, 0, areaRect.w, 22) : IntRectangle(0, 0, 32, areaRect.h),
        isVertical ? 1 : itemCount,
        itemCount,
        Gui::GuiScale,
        IntRectangle()
    )
    , m_textures(textures)
    , m_callback(callback)
    , m_screenHeight(screenHeight)
    , m_bVertical(isVertical)
    , m_sprite1(20, 32, 8, 8, C_TEX_SPRITESHEET, C_TEX_SPRITESHEET_WIDTH, C_TEX_SPRITESHEET_HEIGHT)
    , m_sprite2(28, 32, 8, 8, C_TEX_SPRITESHEET, C_TEX_SPRITESHEET_WIDTH, C_TEX_SPRITESHEET_HEIGHT)
{
    m_area.left -= 4.0f;
    m_area.right += 4.0f;
    m_area.top = 0.0f;
    m_area.bottom = bottom;

    /*if ((areaRect.w + 4) != rect1.w || rect1.h != 22.0f)
    {
        m_pPatchLayer->m_size.x = areaRect.w + 4;
        m_pPatchLayer->m_size.y = 22.0f;

        v23 = 0;
        do
        {
            v24 = v23++;
            m_pPatchLayer->buildQuad(v24);
        } while (v23 != 9);
    }

    if ((areaRect.w + 4) != rect2.w || rect2.h != 22.0f)
    {
        m_pPatchLayer2->m_size.x = areaRect.w + 4;
        m_pPatchLayer2->m_size.y = 22.0f;

        v26 = 0;
        do
        {
            v27 = v26++;
            m_pPatchLayer2->buildQuad(v27);
        } while (v26 != 9);
    }*/
}