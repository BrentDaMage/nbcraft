#include "VirtualKeyboardManager.hpp"

VirtualKeyboardManager::VirtualKeyboardManager()
{
    m_bHasQueuedState = false;
}

void VirtualKeyboardManager::_enqueue(LocalPlayerID playerId, const VirtualKeyboard* pKeyboard)
{
    if (m_bHasQueuedState)
    {
        if (!m_queuedState.bVisible && !pKeyboard)
            return; // we're already hidden
    }
    
    m_bHasQueuedState = true;
    
    m_queuedState.playerId = playerId;
    
    if (pKeyboard)
    {
        m_queuedState.keyboard = *pKeyboard;
        m_queuedState.bVisible = true;
    }
    else
    {
        m_queuedState.bVisible = false;
    }
}

void VirtualKeyboardManager::_applyState()
{
    if (m_queuedState.bVisible)
    {
        AppPlatform::singleton()->showKeyboard(m_queuedState.playerId, m_queuedState.keyboard);
    }
    else
    {
        AppPlatform::singleton()->hideKeyboard(m_queuedState.playerId);
    }
    
    m_bHasQueuedState = false;
}

void VirtualKeyboardManager::tick()
{
    if (!AppPlatform::singleton()->hasVirtualKeyboard())
        return;
    
    if (m_bHasQueuedState)
        _applyState();
}

void VirtualKeyboardManager::showKeyboard(LocalPlayerID playerId, const VirtualKeyboard& keyboard)
{
    _enqueue(playerId, &keyboard);
}

void VirtualKeyboardManager::hideKeyboard(LocalPlayerID playerId)
{
    _enqueue(playerId, nullptr);
}
