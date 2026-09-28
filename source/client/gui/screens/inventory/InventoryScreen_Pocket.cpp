#include "InventoryScreen_Pocket.hpp"
#include "renderer/ShaderConstants.hpp"

InventoryScreen_Pocket::InventoryScreen_Pocket(Player* player)
    : m_pPlayer(player)
	, m_header("Select blocks")
	, m_btnExit("")
	, m_btnCraft("Craft")
	, m_btnMenu("Menu")
{
	m_inventoryPane = nullptr;
}

InventoryScreen_Pocket::~InventoryScreen_Pocket()
{
	SAFE_DELETE(m_inventoryPane);
}

void InventoryScreen_Pocket::_setupPositions()
{
    m_btnCraft.m_xPos = 0;
    m_btnCraft.m_yPos = 0;
    m_btnCraft.m_width = 48;

    m_btnExit.m_xPos = m_width - m_btnExit.m_width;
    m_btnExit.m_yPos = 0;

    m_header.m_yPos = 0;

    if (m_pPlayer && m_pPlayer->isCreative())
    {
        m_header.m_xPos = 0;
        m_header.m_width = m_width;
    }
    else
    {
        m_header.m_xPos = m_btnCraft.m_width;
        m_header.m_width = m_width - m_btnCraft.m_width;
    }

    m_header.m_textPosX = m_width / 2;

	m_clippingArea.x = 0;
	m_clippingArea.y = 0;
	m_clippingArea.w = Minecraft::GetWidthL();
	m_clippingArea.h = Gui::GuiScale * 24.0f;
}

void InventoryScreen_Pocket::_buttonClicked(Button* pButton)
{
	if (pButton->getId() == m_btnExit.getId())
		m_pMinecraft->setScreen(nullptr);
	else if (pButton->getId() == m_btnMenu.getId())
		m_pMinecraft->getScreenChooser()->pushPauseScreen();
	/*else if (pButton->getId() == m_btnCraft.getId())
		m_pMinecraft->setScreen(new CraftAutoScreen(m_pPlayer));
	else if (pButton->getId() == m_btnArmor.getId())
		m_pMinecraft->setScreen(new ArmorScreen(m_pPlayer));*/
}

bool InventoryScreen_Pocket::isAllowed(int slot)
{
	return slot >= 0 && slot < int(m_pPlayer->m_pInventory->getContainerSize());
}

void InventoryScreen_Pocket::init()
{
    int v4 = m_width - 20;
    if (m_width - 20 < 0)
        v4 = m_width + 11;
    int v5 = v4 >> 5;
    //dword188 = v5;
    v5 *= 32;
    int v6 = m_width - v5;

    IntRectangle areaRect(v6 / 2, 30, v5, m_height - 56);
	Container::Size containerSize = m_pPlayer->m_pInventory->getContainerSize();

	m_inventoryPane = new InventoryPane_Pocket(*this, *m_pMinecraft,
		areaRect,
        m_width,
        4.0f,
		containerSize - 9
	);
	m_inventoryPane->m_paddingX = v6 / 2;
	//this->dword184 = containerSize;
	//this->dword180 = (containerSize - 1) / this->dword188 + 1;

	ImageDef exitImg;
	{
		exitImg.name = "gui/spritesheet.png";
		exitImg.xOffset = 0;
		exitImg.yOffset = 1;
		exitImg.width = 18.0f;
		exitImg.height = 18.0f;
		exitImg.uv.x = 60;
		exitImg.uv.y = 0;
		exitImg.uv.w = 18;
		exitImg.uv.h = 18;
		exitImg.bUseCustomUV = true;
	}
	m_btnExit.setImageDef(exitImg);

	m_btnExit.m_width = 19;
	m_btnExit.m_height = 19;
	m_btnExit.m_bScaleOnPress = false;

	_setupPositions();

	_addElement(m_header);
	_addElement(m_btnExit);
	if (!m_pPlayer->isCreative())
		_addElement(m_btnCraft);
	//_addElement(m_btnMenu);
	_addElement(*m_inventoryPane);
}

void InventoryScreen_Pocket::render(float a)
{
    //glDisable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);

    Screen::render(a);
    m_inventoryPane->render(m_menuPointer, a);

	currentShaderColor = Color::WHITE;
    //Tesselator::instance.color(Color::WHITE);
    m_pMinecraft->m_pTextures->loadAndBindTexture("gui/itemframe.png");
    //glEnable(GL_BLEND);
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    blit(
        0, m_inventoryPane->m_rect.y - 6,
        0, 0,
        m_width,
        m_inventoryPane->m_rect.h + 12,
        215,
        256);

    //glDisable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
}

void InventoryScreen_Pocket::tick()
{
	m_inventoryPane->tick();
}

void InventoryScreen_Pocket::removed()
{
	m_pMinecraft->m_pGui->inventoryUpdated();
}

void InventoryScreen_Pocket::handleUserAction(const ActionInfo& info)
{
	if (!_useController() && m_pMinecraft->getOptions()->isAction(AID_INVENTORY, info))
	{
		m_pMinecraft->handleBack(false);
	}
	else
	{
		Screen::handleUserAction(info);
	}
}

bool InventoryScreen_Pocket::isPauseScreen()
{
	return false;
}

bool InventoryScreen_Pocket::addItem(const InventoryPane_Pocket& pane, int id)
{
	Inventory& inventory = *m_pPlayer->m_pInventory;
	Container::StackID stackId = inventory.getItem(id + 9);

	//inventory.moveToSelectionSlot(0, id + 9, 1);
	inventory.selectSlot(0);
	m_pMinecraft->m_pSoundEngine->playUI("random.pop2", 1.0f, 0.3f);
	//m_pMinecraft->m_pGui->flashSlot(0);
	return true;
}

std::vector<const ItemStack*> InventoryScreen_Pocket::getItems(const InventoryPane_Pocket& pane)
{
	std::vector<const ItemStack*> result;

    Inventory& inventory = *m_pPlayer->m_pInventory;
    size_t containerSize = inventory.getContainerSize();

	if (containerSize <= 9)
		return result;

	for (Container::StackID stackId = 0; stackId < containerSize; stackId++)
	{
		result.push_back(&inventory.getItem(stackId));
	}

	return result;
}
