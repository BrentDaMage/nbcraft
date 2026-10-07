#include "FillingContainer.hpp"
#include "common/Logger.hpp"
#include "world/entity/Player.hpp"

#define C_INVALID_LINKED_SLOT -1

FillingContainer::FillingContainer(Size size, Size linkedSlotsCount, bool isUnlimited)
	: m_linkedSlots(nullptr)
	, m_size(size)
	, m_linkedSlotsCount(linkedSlotsCount)
	, m_bUnlimited(isUnlimited)
{
	if (linkedSlotsCount > 0)
	{
		m_linkedSlots = new StackID[m_linkedSlotsCount];
		std::fill(m_linkedSlots, &m_linkedSlots[m_linkedSlotsCount - 1], C_INVALID_LINKED_SLOT);
	}

	m_items.resize(size);
}

FillingContainer::~FillingContainer()
{
	_clear();

	if (m_linkedSlotsCount > 0)
		SAFE_DELETE_ARRAY(m_linkedSlots);
}

void FillingContainer::_release(StackID stackId)
{
	m_items[stackId] = ItemStack::EMPTY;
}

void FillingContainer::_clear()
{
	for (size_t i = 0; i < m_linkedSlotsCount; i++)
	{
		m_linkedSlots[i] = i;
	}

	m_items.resize(m_size);
	std::fill(m_items.begin(), m_items.end(), ItemStack::EMPTY);
}

void FillingContainer::_swapSlots(StackID stackIdA, StackID stackIdB)
{
	std::swap(m_items[stackIdA], m_items[stackIdB]);
}

ItemStack* FillingContainer::_tryGetLinked(int linkedIdx)
{
	StackID stackId = linkedIdx;

	if (linkedIdx >= 0 && linkedIdx <= m_linkedSlotsCount)
	{
		stackId = m_linkedSlots[linkedIdx];

		if (stackId > 0 && stackId >= m_linkedSlotsCount && stackId < m_size)
		{
			std::vector<ItemStack>& slotList = _getSlotList(stackId);

			return &slotList[stackId];
		}
	}
	
	return nullptr;
}

std::vector<ItemStack>& FillingContainer::_getSlotList(StackID index)
{
	return m_items;
}

ItemStack& FillingContainer::getItem(StackID index)
{
	//if (index < 0 || index >= m_size)
	//	return nullptr;

	if (index < m_linkedSlotsCount)
		index = m_linkedSlots[index];

	std::vector<ItemStack>& slotList = _getSlotList(index);
	return slotList[index];
}

ItemStack FillingContainer::removeItem(StackID index, int count)
{
	// a mish-mash of 0.3.3's FillingContainer and our SimpleContainer's impl
	ItemStack& itemStack = getItem(index);
	if (!itemStack.isEmpty())
	{
		ItemStack result = ItemStack::EMPTY;
		if (itemStack.m_count <= count)
		{
			result = itemStack;
			clearSlot(index);
			setContainerChanged(index);
			return result;
		}
		else
		{
			result = itemStack.remove(count);
			if (!itemStack.m_count)
				clearSlot(index);

			setContainerChanged(index);
			return result;
		}
	}

	return ItemStack::EMPTY;
}

void FillingContainer::setItem(StackID index, const ItemStack& item)
{
	std::vector<ItemStack>& slotList = _getSlotList(index);
	slotList[index] = item;

	if (!item.isEmpty() && item.m_count > getMaxStackSize())
		m_items[index].m_count = getMaxStackSize();

	setContainerChanged(index);
}

Container::Size FillingContainer::getContainerSize() const
{
	Size containerSize = m_size;
	Size slotCount = (Size)(m_items.size());
	if (containerSize != slotCount)
	{
		LOG_E("Error@getContainerSize: num items != InventorySize: %d != %d", slotCount, containerSize);
	}

	return containerSize;
}

int FillingContainer::getMaxStackSize() const
{
	return 254;
}

bool FillingContainer::stillValid(Player& player) const
{
	return !player.m_bRemoved;
}

bool FillingContainer::add(ItemStack& item)
{
	if (m_bUnlimited || item.isEmpty())
		return true;

	if (item.isDamaged())
	{
		SlotID freeSlot = _getFreeSlot();
		if (freeSlot < 0)
			return false;

		m_items[freeSlot] = item;
		_linkEmptySlot(freeSlot);

		item = ItemStack::EMPTY;

		return true;
	}

	// some fuck-ass shit
	ItemStack::Count count;
	for (ItemStack::Count i = 0; ; i = count)
	{
		count = _addResource(item);
		item.m_count = count;
		if (count <= 0 || count >= i)
			return i > count;
	}
}

void FillingContainer::doDrop(ItemStack& item, bool b)
{
	item = ItemStack::EMPTY;
}
