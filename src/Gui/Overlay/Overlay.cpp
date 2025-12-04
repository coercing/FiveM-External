#pragma once
#include "Overlay.hpp"

#include <Security/Api/api.hpp>
#include <Includes/ImGui/Files/imgui_freetype.h>
#include <Includes/CustomWidgets/Notify.hpp>
#include <Includes/ImGui/Images.hpp>
#include <Includes/ImGui/Fonts.hpp>
#include <Core/Core.hpp>
#include <Gui/Gui.hpp>
#include <dwmapi.h>
#include <tchar.h>
#include <thread>
#include <skstr.hpp>
#include <fonts.hpp>

#define FULLSCREEN_EX

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Gui
{
	typedef HWND(WINAPI* CreateWindowInBand)(_In_ DWORD dwExStyle, _In_opt_ ATOM atom, _In_opt_ LPCWSTR lpWindowName, _In_ DWORD dwStyle, _In_ int X, _In_ int Y, _In_ int nWidth, _In_ int nHeight, _In_opt_ HWND hWndParent, _In_opt_ HMENU hMenu, _In_opt_ HINSTANCE hInstance, _In_opt_ LPVOID lpParam, DWORD band);

	inline HHOOK hKeyboardHook;

	inline LRESULT CALLBACK KeyboardCallBack(int nCode, WPARAM wParam, LPARAM lParam)
	{
		if (nCode >= 0)
		{
			if (GetForegroundWindow() == g_Variables.g_hCheatWindow)
			{
				KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
				PostMessage(g_Variables.g_hCheatWindow, wParam, pKeyboard->vkCode, 0);
				//}
			}
			return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
		}
	}

	void Overlay::Render()
	{

#ifdef FULLSCREEN_EX
		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		CreateWindowInBand pCreateWindowInBand = reinterpret_cast<CreateWindowInBand>(GetProcAddress(LoadLibraryA(xorstr("user32.dll")), xorstr("CreateWindowInBand")));
		PrepareForUIAccess();
#endif // FULLSCREEN_EX

		WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, Overlay::WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L" ", NULL };
		ATOM RegClass = RegisterClassExW(&wc);

#ifdef FULLSCREEN_EX
		g_Variables.g_hCheatWindow = pCreateWindowInBand(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE, RegClass, L" ", WS_POPUP, static_cast<int>(g_Variables.g_vGameWindowPos.x), static_cast<int>(g_Variables.g_vGameWindowPos.y), static_cast<int>(g_Variables.g_vGameWindowSize.x), static_cast<int>(g_Variables.g_vGameWindowSize.y), NULL, NULL, wc.hInstance, NULL, 2/*ZBID_UIACCESS*/);
#else
		g_Variables.g_hCheatWindow = CreateWindowExW(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT, wc.lpszClassName, L" ", WS_POPUP, g_Variables.g_vGameWindowPos.x, g_Variables.g_vGameWindowPos.y, g_Variables.g_vGameWindowSize.x, g_Variables.g_vGameWindowSize.y, NULL, NULL, wc.hInstance, NULL);
#endif // FULLSCREEN_EX		

		SetLayeredWindowAttributes(g_Variables.g_hCheatWindow, RGB(0, 0, 0), 255, LWA_ALPHA);
		MARGINS Margin = { g_Variables.g_vGameWindowPos.x, g_Variables.g_vGameWindowPos.y, g_Variables.g_vGameWindowSize.x,g_Variables.g_vGameWindowSize.y };
		DwmExtendFrameIntoClientArea(g_Variables.g_hCheatWindow, &Margin);

		if (!CreateDeviceD3D(g_Variables.g_hCheatWindow))
		{
			CleanupDeviceD3D();
			UnregisterClassW(wc.lpszClassName, wc.hInstance);
			return;
		}

		ShowWindow(g_Variables.g_hCheatWindow, SW_SHOWDEFAULT);
		UpdateWindow(g_Variables.g_hCheatWindow);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		auto& style = ImGui::GetStyle();
		style.FramePadding = ImVec2(1, 0);
		style.FrameRounding = 3;
		style.WindowBorderSize = 0;
		style.ScrollbarRounding = 3;
		style.ScrollbarSize = 5;

		ImFontConfig font_config;
		font_config.PixelSnapH = false;
		font_config.OversampleH = 5;
		font_config.OversampleV = 5;
		font_config.RasterizerMultiply = 1.2f;

		static const ImWchar ranges[] = { 0x0020, 0x00FF, 0x0400, 0x052F, 0x2DE0, 0x2DFF, 0xA640, 0xA69F, 0xE000, 0xE226, 0 };
		io.Fonts->AddFontFromMemoryTTF(poppin_font, sizeof(poppin_font), 16, &font_config, ranges);
		tab_title = io.Fonts->AddFontFromFileTTF(skCrypt("C:\\Windows\\Fonts\\arialbd.ttf").decrypt(), 19.0f, &font_config, ranges);
		font_icon = io.Fonts->AddFontFromMemoryTTF(icon_font, sizeof(icon_font), 25.0f, &font_config, ranges);
		poppins = io.Fonts->AddFontFromMemoryTTF(poppin_font, sizeof(poppin_font), 25.0f, &font_config, ranges);
		io.IniFilename = NULL;
		io.LogFilename = NULL;

		Style();

		ImGui_ImplWin32_Init(g_Variables.g_hCheatWindow);
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

		Core::StartThreads();
		if (!Core::ThreadsStarted) return;

		std::thread([&]() { NotifyManager::Send(xorstr("Injected :)"), 4000); }).detach();

		static RECT old_rc;
		ZeroMemory(&Message, sizeof(MSG));

		while (Message.message != WM_QUIT)
		{
			if (PeekMessage(&Message, g_Variables.g_hCheatWindow, 0, 0, PM_REMOVE)) {
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}

			HWND ActiveWindow = GetForegroundWindow();

			if (GetAsyncKeyState(g_Config.General->MenuKey) & 1) {

				if (g_MenuInfo.IsOpen == false) {
					if (ActiveWindow == g_Variables.g_hGameWindow) {
						g_MenuInfo.IsOpen = true;

#ifdef FULLSCREEN_EX
						SetWindowLong(g_Variables.g_hCheatWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE);
#else
						SetWindowLong(g_Variables.g_hCheatWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
#endif // FULLSCREEN_EX		
					}
					else {
						SetWindowLong(g_Variables.g_hCheatWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
					}
				}
				else {
					g_MenuInfo.IsOpen = false;
					SetWindowLong(g_Variables.g_hCheatWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
				}
			}

			static float BgAlpha = 0.f;
			BgAlpha = ImLerp(BgAlpha, (g_MenuInfo.IsOpen && g_Variables.Logged) || (!g_Variables.Logged && g_MenuInfo.IsLoginOpen) ? 1.f : 0.f, ImGui::GetIO().DeltaTime * 8);

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			if (!g_Variables.Logged && g_MenuInfo.IsLoginOpen)
			{
				Gui::cOverlay.RenderLogin();
			}
			else if (g_Variables.Logged)
			{
				Gui::Rendering();
			}

			ImGui::EndFrame();

			const float ClearColor[4] = { 0 };
			g_pd3dDeviceContext->OMSetRenderTargets(1U, &g_mainRenderTargetView, NULL);
			g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, ClearColor);

			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			g_pSwapChain->Present(g_Config.General->VSync, 0U);
		}

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		CleanupDeviceD3D();
		DestroyWindow(g_Variables.g_hCheatWindow);
		UnregisterClassW(wc.lpszClassName, wc.hInstance);

#ifdef FULLSCREEN_EX
		UnhookWindowsHookEx(hKeyboardHook);
#endif // FULLSCREEN_EX
	}

	void Overlay::Fonts()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.IniFilename = nullptr;

		ImFontConfig Cfg;
		Cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;
		Cfg.FontDataOwnedByAtlas = false;

		ImFontConfig DrawCfg;
		DrawCfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_Bitmap;
		DrawCfg.FontDataOwnedByAtlas = false;

		ImGui::StyleColorsDark();

		auto& style = ImGui::GetStyle();
		auto& color = style.Colors;

		style.FramePadding = ImVec2(1, 0);
		style.FrameRounding = 3;
		style.WindowBorderSize = 0;
		style.ScrollbarRounding = 3;
		style.ScrollbarSize = 5;

		ImFontConfig font_config;
		font_config.PixelSnapH = false;
		font_config.OversampleH = 5;
		font_config.OversampleV = 5;
		font_config.RasterizerMultiply = 1.2f;

		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
			0x2DE0, 0x2DFF, // Cyrillic Extended-A
			0xA640, 0xA69F, // Cyrillic Extended-B
			0xE000, 0xE226, // icons
			0,
		};



		g_Variables.m_FontBig = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 20.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
		g_Variables.m_FontBigSmall = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 18.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
		g_Variables.m_FontNormal = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 18.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
		g_Variables.m_FontSecundary = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 16.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
		g_Variables.m_FontSmaller = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 14.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());

		g_Variables.m_DrawFont = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 12.f, &DrawCfg, io.Fonts->GetGlyphRangesCyrillic());

		//Font
		font_config.GlyphRanges = ranges;

		io.Fonts->AddFontFromMemoryTTF(poppin_font, sizeof(poppin_font), 16, &font_config, ranges);
		tab_title = io.Fonts->AddFontFromFileTTF(skCrypt("C:\\Windows\\Fonts\\arialbd.ttf").decrypt(), 19.0f, &font_config, ranges);
		font_icon = io.Fonts->AddFontFromMemoryTTF(icon_font, sizeof(icon_font), 25.0f, &font_config, ranges);
		poppins = io.Fonts->AddFontFromMemoryTTF(poppin_font, sizeof(poppin_font), 25.0f, &font_config, ranges);
		baloo = io.Fonts->AddFontFromMemoryTTF(baloo_font, sizeof(baloo_font), 25.0f, &font_config, ranges);
		io.IniFilename = NULL;
		io.LogFilename = NULL;

		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;
		io.Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);

		static const ImWchar FontAwesomeRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		static const ImWchar FontAwesomeRangesBrands[] = { ICON_MIN_FAB, ICON_MAX_FAB, 0 };

		ImFontConfig FontAwesomeConfig;
		FontAwesomeConfig.PixelSnapH = true;
		FontAwesomeConfig.GlyphMinAdvanceX = 19;

		g_Variables.FontAwesomeSolid = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome6Solid_compressed_data, sizeof(FontAwesome6Solid_compressed_size), 19, &FontAwesomeConfig, FontAwesomeRanges);
		g_Variables.FontAwesomeSolidSmall = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome6Solid_compressed_data, sizeof(FontAwesome6Solid_compressed_size), 16, &FontAwesomeConfig, FontAwesomeRanges);
		g_Variables.FontAwesomeRegular = io.Fonts->AddFontFromMemoryCompressedTTF(FontAwesome6Regular_compressed_data, sizeof(FontAwesome6Regular_compressed_size), 19, &FontAwesomeConfig, FontAwesomeRanges);

		g_Variables.m_Expand = io.Fonts->AddFontFromMemoryTTF(expand_binary, sizeof(expand_binary), 11.f, &Cfg, io.Fonts->GetGlyphRangesCyrillic());
	//}
	}

	void Overlay::Style()
	{
			ImGui::StyleColorsDark();

			ImGuiStyle* style = &ImGui::GetStyle();
			{
				style->WindowPadding = ImVec2(0, 0);
				style->WindowBorderSize = 0.f;
				style->ItemSpacing = ImVec2(12, 12);
				style->ScrollbarSize = 4.f;
			}

		if (g_Variables.Logo == nullptr)
		{
			D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, logo_binary, sizeof(logo_binary), &Info, Pump, &g_Variables.Logo, 0);
		}
	}

	bool Overlay::CreateDeviceD3D(HWND hWnd)
	{
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
		if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
			return false;

		CreateRenderTarget();
		return true;
	}

	void Overlay::CleanupDeviceD3D()
	{
		CleanupRenderTarget();

		if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
		if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
		if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	}

	void Overlay::CreateRenderTarget()
	{
		ID3D11Texture2D* pBackBuffer;
		g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
		pBackBuffer->Release();
	}

	void Overlay::CleanupRenderTarget()
	{
		if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
	}

	LRESULT CALLBACK Overlay::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg) {
		case WM_SIZE:
			if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED) {
				Overlay::CleanupRenderTarget();
				g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
				Overlay::CreateRenderTarget();
			}
			return 0;
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
			break;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	DWORD Overlay::GetWinLogonToken(DWORD dwSessionId, DWORD dwDesiredAccess, PHANDLE phToken)
	{
		DWORD dwErr;
		PRIVILEGE_SET ps;

		ps.PrivilegeCount = 1;
		ps.Control = PRIVILEGE_SET_ALL_NECESSARY;

		if (LookupPrivilegeValue(NULL, SE_TCB_NAME, &ps.Privilege[0].Luid)) {
			HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (INVALID_HANDLE_VALUE != hSnapshot) {
				BOOL bCont, bFound = FALSE;
				PROCESSENTRY32 pe;

				pe.dwSize = sizeof(pe);
				dwErr = ERROR_NOT_FOUND;

				for (bCont = Process32First(hSnapshot, &pe); bCont; bCont = Process32Next(hSnapshot, &pe)) {
					HANDLE hProcess;

					if (0 != _tcsicmp(pe.szExeFile, xorstr("winlogon.exe"))) {
						continue;
					}

					hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe.th32ProcessID);
					if (hProcess) {
						HANDLE hToken;
						DWORD dwRetLen, sid;

						if (OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_DUPLICATE, &hToken)) {
							BOOL fTcb;

							if (PrivilegeCheck(hToken, &ps, &fTcb) && fTcb) {
								if (GetTokenInformation(hToken, TokenSessionId, &sid, sizeof(sid), &dwRetLen) && sid == dwSessionId) {
									bFound = TRUE;
									if (DuplicateTokenEx(hToken, dwDesiredAccess, NULL, SecurityImpersonation, TokenImpersonation, phToken)) {
										dwErr = ERROR_SUCCESS;
									}
									else {
										dwErr = GetLastError();
									}
								}
							}
							CloseHandle(hToken);
						}
						CloseHandle(hProcess);
					}

					if (bFound) break;
				}

				CloseHandle(hSnapshot);
			}
			else {
				dwErr = GetLastError();
			}
		}
		else {
			dwErr = GetLastError();
		}


		return dwErr;
	}

	DWORD Overlay::CreateUIAccessToken(PHANDLE phToken)
	{
		DWORD dwErr;
		HANDLE hTokenSelf;

		if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_DUPLICATE, &hTokenSelf)) {
			DWORD dwSessionId, dwRetLen;

			if (GetTokenInformation(hTokenSelf, TokenSessionId, &dwSessionId, sizeof(dwSessionId), &dwRetLen)) {
				HANDLE hTokenSystem;

				dwErr = GetWinLogonToken(dwSessionId, TOKEN_IMPERSONATE, &hTokenSystem);
				if (ERROR_SUCCESS == dwErr) {
					if (SetThreadToken(NULL, hTokenSystem)) {
						if (DuplicateTokenEx(hTokenSelf, TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_DEFAULT, NULL, SecurityAnonymous, TokenPrimary, phToken)) {
							BOOL bUIAccess = TRUE;

							if (!SetTokenInformation(*phToken, TokenUIAccess, &bUIAccess, sizeof(bUIAccess))) {
								dwErr = GetLastError();
								CloseHandle(*phToken);
							}
						}
						else {
							dwErr = GetLastError();
						}
						RevertToSelf();
					}
					else {
						dwErr = GetLastError();
					}
					CloseHandle(hTokenSystem);
				}
			}
			else {
				dwErr = GetLastError();
			}

			CloseHandle(hTokenSelf);
		}
		else {
			dwErr = GetLastError();
		}

		return dwErr;
	}

	BOOL Overlay::CheckForUIAccess(DWORD* pdwErr, DWORD* pfUIAccess)
	{
		BOOL result = FALSE;
		HANDLE hToken;

		if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
			DWORD dwRetLen;

			if (GetTokenInformation(hToken, TokenUIAccess, pfUIAccess, sizeof(*pfUIAccess), &dwRetLen)) {
				result = TRUE;
			}
			else {
				*pdwErr = GetLastError();
			}
			CloseHandle(hToken);
		}
		else {
			*pdwErr = GetLastError();
		}

		return result;
	}

	DWORD Overlay::PrepareForUIAccess()
	{
		DWORD dwErr;
		HANDLE hTokenUIAccess;
		DWORD fUIAccess;

		if (CheckForUIAccess(&dwErr, &fUIAccess)) {
			if (fUIAccess) {
				dwErr = ERROR_SUCCESS;
			}
			else {
				dwErr = CreateUIAccessToken(&hTokenUIAccess);
				if (ERROR_SUCCESS == dwErr) {
					STARTUPINFO si;
					PROCESS_INFORMATION pi;

					GetStartupInfo(&si);
					if (CreateProcessAsUser(hTokenUIAccess, NULL, GetCommandLine(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
						CloseHandle(pi.hProcess), CloseHandle(pi.hThread);
						ExitProcess(0);
					}
					else {
						dwErr = GetLastError();
					}

					CloseHandle(hTokenUIAccess);
				}
			}
		}

		return dwErr;
	}

	void Overlay::RenderLogin()
	{
		ImGui::SetNextWindowSize(ImVec2(500 * 1.0f, 277 * 1.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, Gui::cOverlay.backgroundAlpha);
		ImGui::Begin(skCrypt("Rocket Login"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);
		{
			DecorationLogin();
			RenderTabLogin();
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
		NotifyManager::Render();
		ImGui::PopStyleVar(1);
		ImGui::PopStyleColor(1);
	}

	void Overlay::DecorationLogin()
	{
		auto draw = ImGui::GetWindowDrawList();
		ImVec2 pos = ImGui::GetWindowPos();

		draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + 161, pos.y + 277), ImColor(22, 22, 22, int(255 * ImGui::GetStyle().Alpha)), 10.f, ImDrawCornerFlags_Left); // left bg
		draw->AddRect(ImVec2(pos.x, pos.y), ImVec2(pos.x + 161, pos.y + 277), ImColor(50, 50, 50, int(255 * ImGui::GetStyle().Alpha)), 10.f, ImDrawCornerFlags_Left, 1);  // left bg

		draw->AddRectFilled(ImVec2(pos.x + 160, pos.y), ImVec2(pos.x + 500, pos.y + 277), ImColor(18, 18, 18, int(255 * ImGui::GetStyle().Alpha)), 10.f, ImDrawCornerFlags_Right); // right bg
		draw->AddRect(ImVec2(pos.x + 160, pos.y), ImVec2(pos.x + 500, pos.y + 277), ImColor(50, 50, 50, int(255 * ImGui::GetStyle().Alpha)), 10.f, ImDrawCornerFlags_Right, 1);  // right bg

		ImGui::SetCursorPos(ImVec2(30, -5));
		ImColor rocketColorWithAlpha = ImColor(Gui::cOverlay.rocketColor.Value.x, Gui::cOverlay.rocketColor.Value.y, Gui::cOverlay.rocketColor.Value.z, Gui::cOverlay.rocketColor.Value.w * ImGui::GetStyle().Alpha);
		ImColor infosColorWithAlpha = ImColor(Gui::cOverlay.infosColor.Value.x, Gui::cOverlay.infosColor.Value.y, Gui::cOverlay.infosColor.Value.z, Gui::cOverlay.infosColor.Value.w * ImGui::GetStyle().Alpha);
		//draw->AddText(baloo, 38, ImVec2(pos.x + 24, pos.y + 24), rocketColorWithAlpha, "");
		ImGui::SetCursorPos(ImVec2(34, 0));
		ImGui::Image(g_Variables.Logo, ImVec2(80, 80));
	}

	void Overlay::login_tab() {
		ImGui::SetCursorPos(ImVec2(169, 38));
		ImGui::MenuChild(skCrypt("Login"), ImVec2(320, 230));
		{
			ImGui::Spacing();

			ImGui::SetCursorPosX(20);
			ImGui::InputText(skCrypt("Username"), g_Variables.userLogin, sizeof(g_Variables.userLogin));

			ImGui::SetCursorPosX(20);
			ImGui::InputText(skCrypt("Password"), g_Variables.passLogin, sizeof(g_Variables.passLogin), ImGuiInputTextFlags_Password);

			ImGui::Spacing();
			ImGui::SetCursorPosX(20);

			if (ImGui::Button(skCrypt("Login"), ImVec2(320 - 38, 30))) {
				/*if (g_Variables.userLogin[0] != '\0' && g_Variables.passLogin[0] != '\0') {
					std::string result = g_Api.login(g_Variables.userLogin, g_Variables.passLogin);
					if (result == xorstr("success")) {
						g_Variables.Logged = true;
						NotifyManager::Send(xorstr("Login successful!"), 3000);
					}
					else {
						NotifyManager::Send(xorstr("Login failed: ") + result, 7000);
					}
				}
				else {
					NotifyManager::Send(xorstr("Username and password can't be empty"), 7000);
				}*/
			}
		}
		ImGui::EndChild();
	}

	void Overlay::register_tab() {
		ImGui::SetCursorPos(ImVec2(169, 38));
		ImGui::MenuChild(skCrypt("Register"), ImVec2(320, 230));
		{
			ImGui::Spacing();

			ImGui::SetCursorPosX(20);
			ImGui::InputText(skCrypt("Username"), g_Variables.userRegister, sizeof(g_Variables.userRegister));

			ImGui::SetCursorPosX(20);
			ImGui::InputText(skCrypt("Password"), g_Variables.passRegister, sizeof(g_Variables.passRegister), ImGuiInputTextFlags_Password);

			ImGui::SetCursorPosX(20);
			ImGui::InputText(skCrypt("License"), g_Variables.licenseRegister, sizeof(g_Variables.licenseRegister));

			ImGui::Spacing();
			ImGui::SetCursorPosX(20);
			//if (ImGui::Button(skCrypt("Register"), ImVec2(320 - 38, 30))) {
			/*	if (g_Variables.userRegister[0] != '\0' && g_Variables.passRegister[0] != '\0' && g_Variables.licenseRegister[0] != '\0') {
					std::string result = g_Api.register_with_key(
						g_Variables.userRegister,
						g_Variables.passRegister,
						g_Variables.licenseRegister
					);
					if (result == xorstr("success")) {
						g_Variables.Logged = true;
						NotifyManager::Send(xorstr("Registration successful!"), 3000);
					}
					else {
						NotifyManager::Send(xorstr("Registration failed: ") + result, 7000);
					}
				}
				else {
					NotifyManager::Send(xorstr("Username, password, and license can't be empty"), 7000);
				}
			}*/
		}
		ImGui::EndChild();
	}

	static int o_tabs;

	void Overlay::RenderTabLogin()
	{
		auto draw = ImGui::GetWindowDrawList();
		ImVec2 pos = ImGui::GetWindowPos();

		draw->AddText(poppins, 17, ImVec2(pos.x + 13, pos.y + 81), ImColor(105, 105, 105, int(255 * ImGui::GetStyle().Alpha)), skCrypt("Home"));

		ImGui::SetCursorPos(ImVec2(13, 99));
		if (ImGui::Rendertab("r", skCrypt("Login"), !o_tabs)) o_tabs = 0;

		ImGui::SetCursorPos(ImVec2(13, 136));
		if (ImGui::Rendertab("e", skCrypt("Register"), o_tabs == 1)) o_tabs = 1;

		ImGui::Spacing();
		ImGui::SetCursorPos(ImVec2(13, 230));
		if (ImGui::Button(skCrypt("Close"), ImVec2(135, 30))) {
			exit(0);
		}

		switch (o_tabs)
		{
		case 0: login_tab(); break;
		case 1: register_tab(); break;
		}
	}
}