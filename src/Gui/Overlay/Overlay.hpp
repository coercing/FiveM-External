#include <Includes/Includes.hpp>

namespace Gui {

	static ID3D11Device* g_pd3dDevice;
	static ID3D11DeviceContext* g_pd3dDeviceContext;
	static IDXGISwapChain* g_pSwapChain;
	static UINT                     g_ResizeWidth, g_ResizeHeight;
	static ID3D11RenderTargetView* g_mainRenderTargetView;
	inline MSG Message = { NULL };

	class Overlay {
	private:
		static void CreateRenderTarget();
		static void CleanupRenderTarget();
		void LoadWeaponIcons();
		
		DWORD PrepareForUIAccess();
		static BOOL CheckForUIAccess(DWORD* pdwErr, DWORD* pfUIAccess);
		static DWORD CreateUIAccessToken(PHANDLE phToken);
		static DWORD GetWinLogonToken(DWORD dwSessionId, DWORD dwDesiredAccess, PHANDLE phToken);

		enum ZBID {
			ZBID_DEFAULT = 0,
			ZBID_DESKTOP = 1,
			ZBID_UIACCESS = 2,
			ZBID_IMMERSIVE_IHM = 3,
			ZBID_IMMERSIVE_NOTIFICATION = 4,
			ZBID_IMMERSIVE_APPCHROME = 5,
			ZBID_IMMERSIVE_MOGO = 6,
			ZBID_IMMERSIVE_EDGY = 7,
			ZBID_IMMERSIVE_INACTIVEMOBODY = 8,
			ZBID_IMMERSIVE_INACTIVEDOCK = 9,
			ZBID_IMMERSIVE_ACTIVEMOBODY = 10,
			ZBID_IMMERSIVE_ACTIVEDOCK = 11,
			ZBID_IMMERSIVE_BACKGROUND = 12,
			ZBID_IMMERSIVE_SEARCH = 13,
			ZBID_GENUINE_WINDOWS = 14,
			ZBID_IMMERSIVE_RESTRICTED = 15,
			ZBID_SYSTEM_TOOLS = 16,
			// Win10
			ZBID_LOCK = 17,
			ZBID_ABOVELOCK_UX = 18,
		};

		D3DX11_IMAGE_LOAD_INFO Info;
		ID3DX11ThreadPump* Pump{ nullptr };

	public:
		void CleanupDeviceD3D();
		bool CreateDeviceD3D(HWND hWnd);
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		bool particles = true;
		float backgroundAlpha = .97f;
		int particleCount = 70;
		float minSpeed = 1.0f;
		float maxSpeed = 20.0f;
		float minRadius = 1.0f;
		float maxRadius = 3.0f;

		bool streamProff = false;

		bool enableRGBParticles = false;
		bool enableRGBRocket = false;
		bool enableRGBInfos = false;
		bool enableRGBSidebarIcons = false;
		bool enableRGBSidebarSelectedIcon = false;


		float rgbSpeed = 0.1f;
		ImColor particlesColor = ImColor(229, 183, 190, 255 / 2);
		ImColor rocketColor = ImColor(229, 183, 190);
		ImColor infosColor = ImColor(229, 183, 190);
		ImColor sidebarIconsColor = ImColor(229, 183, 190);
		ImColor sidebarSelectedIconColor = ImColor(229, 183, 190);

		ImColor originalParticlesColor = ImColor(229, 183, 190, 255 / 2);
		ImColor originalRocketColor = ImColor(229, 183, 190);
		ImColor originalInfosColor = ImColor(229, 183, 190);
		ImColor originalSidebarIconsColor = ImColor(229, 183, 190);
		ImColor originalSidebarSelectedIconColor = ImColor(229, 183, 190);

		void Render();
		void Style();
		void Fonts();

		void RenderLogin();
		void DecorationLogin();
		void login_tab();
		void register_tab();
		void RenderTabLogin();
	};

	inline Overlay cOverlay;

}