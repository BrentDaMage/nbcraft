#include "common/Logger.hpp"

#include "client/app/App.hpp"
#include "client/app/NinecraftApp.hpp"

#include "AppPlatform_xdk360.hpp"

AppPlatform_xdk360 g_AppPlatform;
NinecraftApp* g_pApp;

void _setSize()
{
    XVIDEO_MODE VideoMode;
    XGetVideoMode(&VideoMode);
    Minecraft::SetViewportSize(Mth::Max<int>(VideoMode.dwDisplayWidth, 640), Mth::Max<int>(VideoMode.dwDisplayHeight, 480));

	// Hardcoded 1080p check to avoid failed D3D device creation attempt
	if (Minecraft::GetWidthP() == 1920 && Minecraft::GetHeightP() == 1080)
	{
		// too big, D3D9 Device creation will fail
		Minecraft::SetViewportSize(1280, 720);
	}
}

void _onKeyboardClosed()
{
	const XOVERLAPPED& xov = g_AppPlatform.m_vkOverlapped;

	g_AppPlatform.onHideKeyboard();

	if (xov.dwExtendedError == ERROR_SUCCESS)
		g_pApp->setTextboxText(g_AppPlatform.getKeyboardText());

	g_pApp->handleKeyboardClosed();
}

void _tickAppPlatform()
{
	if (g_AppPlatform.m_bVirtualKeyboard && XHasOverlappedIoCompleted(&g_AppPlatform.m_vkOverlapped) == TRUE)
	{
		_onKeyboardClosed();
	}
}

void __cdecl main()
{
	Logger::setSingleton(new Logger);

	_setSize();

	if (!g_AppPlatform.initGraphics(Minecraft::GetWidthP(), Minecraft::GetHeightP()))
		goto _cleanup;

	g_pApp = new NinecraftApp;
	g_AppPlatform.m_externalStorageDir = "savedrive:";

	// initialize the app
	g_pApp->init();
	g_pApp->sizeUpdate();
    g_pApp->start();

	while (!g_pApp->wantToQuit())
	{
		_tickAppPlatform();
		g_pApp->update();
		g_AppPlatform.swapBuffers();
	}

_cleanup:
	g_pApp->saveOptions();

	// Cleanup networking, renderer, sounds, textures, etc.
	delete g_pApp;
}
