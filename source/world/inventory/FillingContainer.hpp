#pragma once

#include <vector>

#include "BaseContainer.hpp"

class FillingContainer : public BaseContainer
{
public:
	FillingContainer(Size size, Size linkedSlotsCount, bool isUnlimited);
	~FillingContainer();

protected:
	void _release(StackID stackId);
	void _clear();
	void _swapSlots(StackID stackIdA, StackID stackIdB);
	ItemStack* _tryGetLinked(int linkedIdx);

protected:
	virtual std::vector<ItemStack>& _getSlotList(StackID index);

public:
	Size getNumLinkedSlots() const { return m_linkedSlotsCount; }

public:
	ItemStack& getItem(StackID index) override;
	ItemStack removeItem(StackID index, int count) override;
	void setItem(StackID index, const ItemStack& item) override;
	Size getContainerSize() const override;
	int getMaxStackSize() const override;
	bool stillValid(Player& player) const override;

public:
	virtual bool add(ItemStack& item);
	virtual void doDrop(ItemStack& item, bool b);

protected:
	StackID* m_linkedSlots;
	std::vector<ItemStack> m_items;
	Size m_size;
	Size m_linkedSlotsCount;
	bool m_bUnlimited;
};

