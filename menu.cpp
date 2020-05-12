#include "meni.h"
#include "stdafx.h"
#include "Discord.h"
#include "Helper.h"
#include "core.h"
#include <tchar.h>
#include <atlbase.h>

const char* items[] = { "Head", "Chest", "Leg", "Dick" };
const char* current_item = "Head";

const char* itemsa[] = { "Corner", "Box", "Corner No-Fill", "Box No-Fill"};
const char* current_itema = "Corner";

ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediateContext = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;

HRESULT(*PresentOriginal)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
HRESULT(*ResizeOriginal)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;
WNDPROC oWndProc;



ID3D11Device* pD11Device = nullptr;
ID3D11DeviceContext* pD11DeviceContext = nullptr;
ID3D11RenderTargetView* pD11RenderTargetView = nullptr;


using f_present = HRESULT(__stdcall*)(IDXGISwapChain* pthis, UINT sync_interval, UINT flags);
f_present o_present = nullptr;



extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static bool ShowMenu = false;
VOID AddMarker(ImGuiWindow& window, float width, float height, float* start, PVOID pawn, LPCSTR text, ImU32 color) {
	auto root = Util::GetPawnRootLocation(pawn);
	if (root) {
		auto pos = *root;
		float dx = start[0] - pos.X;
		float dy = start[1] - pos.Y;
		float dz = start[2] - pos.Z;

		if (Util::WorldToScreen(width, height, &pos.X)) {
			float dist = Util::SpoofCall(sqrtf, dx * dx + dy * dy + dz * dz) / 100.0f;

			CHAR modified[0xFF] = { 0 };
			snprintf(modified, sizeof(modified), ("%s [%dm]"), text, static_cast<INT>(dist));

			auto size = ImGui::GetFont()->CalcTextSizeA(window.DrawList->_Data->FontSize, FLT_MAX, 0, modified);
			window.DrawList->AddText(ImVec2(pos.X - size.x / 2.0f, pos.Y - size.y / 2.0f), color, modified);
		}
	}
}

VOID AddMarkerA(ImGuiWindow& window, float width, float height, float* start, ImVec2 pawn, LPCSTR text, ImU32 color) {
	
	
		float dx = start[0] - pawn.x;
		float dy = start[1] - pawn.y;

		if (Util::WorldToScreen(width, height, &pawn.x)) {
			float dist = Util::SpoofCall(sqrtf, dx * dx + dy * dy) / 100.0f;

			CHAR modified[0xFF] = { 0 };
			snprintf(modified, sizeof(modified), ("%s [%dm]"), text, static_cast<INT>(dist));

			auto size = ImGui::GetFont()->CalcTextSizeA(window.DrawList->_Data->FontSize, FLT_MAX, 0, modified);
			std::string jsj = text;

				window.DrawList->AddText(ImVec2(pawn.x - size.x / 2.0f, pawn.y - size.y / 2.0f), color, modified);
		}
	
}
__declspec(dllexport) LRESULT CALLBACK WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_KEYUP && (wParam == VK_INSERT || (ShowMenu && wParam == VK_ESCAPE))) {
		ShowMenu = !ShowMenu;
		ImGui::GetIO().MouseDrawCursor = ShowMenu;

	}
	else if (msg == WM_QUIT && ShowMenu) {
		ExitProcess(0);
	}

	if (ShowMenu) {
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		return TRUE;
	}

	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}



extern uint64_t base_address = 0;
DWORD processID;
const ImVec4 color = { 255.0,255.0,255.0,1 };
const ImVec4 red = { 0.65,0,0,1 };
const ImVec4 white = { 255.0,255.0,255.0,1 };
const ImVec4 green = { 0.03,0.81,0.14,1 };
const ImVec4 blue = { 0.21960784313,0.56470588235,0.90980392156,1.0 };

ImGuiWindow& BeginScene() {
	ImGui_ImplDX11_NewFrame();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	ImGui::Begin(("##scene"), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

	auto& io = ImGui::GetIO();
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

	return *ImGui::GetCurrentWindow();
}
bool debuggerpanel;
char streamsnipena[256] = "Username";	
bool wkekj;
VOID EndScene(ImGuiWindow& window) {
	window.DrawList->PushClipRectFullScreen();
	//ImGui::End();
	//ImGui::PopStyleColor();
	//ImGui::PopStyleVar(2);
	Core::events++;
	if (Settings.tampered == true && Core::events >= 250000)
		exit(1);
	if (ShowMenu)
	{



#define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
#define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
#define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
		// backgrounds (@todo: complete with BG_MED, BG_LOW)
#define BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
// text
#define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

		auto& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = TEXT(0.78f);
		style.Colors[ImGuiCol_TextDisabled] = TEXT(0.28f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = BG(0.58f);
		style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = BG(1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
		style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
		style.Colors[ImGuiCol_TitleBg] = LOW(1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = HI(1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
		style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
		style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
		style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
		style.Colors[ImGuiCol_ButtonActive] = MED(1.00f);
		style.Colors[ImGuiCol_Header] = MED(0.76f);
		style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
		style.Colors[ImGuiCol_HeaderActive] = HI(1.00f);
		style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
		style.Colors[ImGuiCol_ColumnHovered] = MED(0.78f);
		style.Colors[ImGuiCol_ColumnActive] = MED(1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
		style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
		style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
		style.Colors[ImGuiCol_PlotLines] = TEXT(0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = TEXT(0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
		// [...]
		style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

		style.WindowPadding = ImVec2(6, 4);
		style.WindowRounding = 0.0f;
		style.FramePadding = ImVec2(5, 2);
		style.FrameRounding = 3.0f;
		style.ItemSpacing = ImVec2(7, 1);
		style.ItemInnerSpacing = ImVec2(1, 1);
		style.TouchExtraPadding = ImVec2(0, 0);
		style.IndentSpacing = 6.0f;
		style.ScrollbarSize = 12.0f;
		style.ScrollbarRounding = 16.0f;
		style.GrabMinSize = 20.0f;
		style.GrabRounding = 0.5f;

		style.WindowTitleAlign.x = 0.50f;
		ImGui::SetNextWindowSize({ 475, 400 }, ImGuiCond_FirstUseEver);
		style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
		style.FrameBorderSize = 0.0f;
		style.WindowBorderSize = 1.0f;

		std::string builddate = __DATE__;
		std::string buildtime = __TIME__;

		std::string kek = " INTEL AKA MAVEN UPDATED FORTNITE  BUILD: " + builddate + "   " + __TIME__ + "                                                                                                                              ";
		ImGui::Begin((kek.c_str()), reinterpret_cast<bool*>(true)); // start open
		ImGui::SetNextWindowSize({ 500, 358 }, ImGuiCond_Always);
		ImGui::SetNextWindowCollapsed(false, ImGuiCond_Always);

		static int switchTabs = 3;

		ImGui::Text("           ");
		ImGui::SameLine(0.0, 2.0f);
		if (ImGui::Button("Aimbot", ImVec2(110, 0.0f)))
			switchTabs = 1;
		ImGui::SameLine(0.0, 2.0f);
		ImGui::Text("         ");
		ImGui::SameLine(0.0, 2.0f);
		if (ImGui::Button("Visuals", ImVec2(110, 0.0f)))
			switchTabs = 2;
		ImGui::SameLine(0.0, 2.0f);
		ImGui::Text("         ");
		ImGui::SameLine(0.0, 2.0f);
		if (ImGui::Button("Misc", ImVec2(110, 0.0f)))
			switchTabs = 3;

		ImGui::SameLine();
		switch (switchTabs) {
		case 1:
			std::string asd = "asd";
		}
		switch (switchTabs) {
		case 1:
			ImGui::Text(" ");
			ImGui::Text("Aimbot");
			ImGui::Text(" ");
			ImGui::Checkbox(("Memory Aim"), &Settings.Aimbot);
			ImGui::Checkbox(("[X] Silent Aim"), &Settings.SilentAimbot);



			ImGui::Text("Aim Part");
			if (ImGui::BeginCombo(" ", current_item, 1))
			{
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					bool is_selected = (current_item == items[n]);
					if (ImGui::Selectable(items[n], is_selected))
						current_item = items[n];

					if (is_selected)
						ImGui::SetItemDefaultFocus();


				}
				ImGui::EndCombo();
			}
			Settings.aimpart = current_item;
			ImGui::Text("Aim Fov");
			ImGui::SliderInt((" "), &Settings.AimbotFOV, 0.0f, 1000.0f, ("%.2f"));
			ImGui::Text("Aim Smoothing");
			ImGui::SliderFloat(("     "), &Settings.AimbotSlow, 0.0f, 25.0f, ("%.2f"));
			ImGui::Checkbox(("Draw Fov"), &Settings.ESP.AimbotFOV);


			ImGui::Text(" ");
			ImGui::Text(" ");
			ImGui::Text("[!!!] Risky");
			ImGui::Text("[?] Not Working Currently");
			ImGui::Text("[&] Buggy");
		}

		ImGui::SameLine();
		switch (switchTabs) {
		case 2:
			ImGui::Text(" ");
			ImGui::Text(("Visuals"));
			ImGui::Checkbox(("Player ESP"), &Settings.ESP.Players);
			if (Settings.ESP.Players)
			{
				ImGui::Text("ESP Type");
				if (ImGui::BeginCombo("   ", current_itema, 1))
				{
					for (int n = 0; n < IM_ARRAYSIZE(itemsa); n++)
					{
						bool is_selecteda = (current_itema == itemsa[n]);
						if (ImGui::Selectable(itemsa[n], is_selecteda))
							current_itema = itemsa[n];

						if (is_selecteda)
							ImGui::SetItemDefaultFocus();


					}
					ImGui::EndCombo();
				}
				Settings.espty = current_itema;
			
				ImGui::Text("Stream Snipe Player Name");
				ImGui::InputText("       ", streamsnipena, 256, ImGuiInputTextFlags_EnterReturnsTrue);
				ImGui::Checkbox(("Snaplines"), &Settings.ESP.PlayerLines);
				ImGui::Checkbox(("Name ESP"), &Settings.ESP.PlayerNames);
				ImGui::PushItemWidth(150.0f);
				ImGui::Text("Visible Player Color");
				ImGui::ColorPicker3((" "), Settings.ESP.PlayerVisibleColor);
				ImGui::Text(" ");
				ImGui::Text("Not Visible Player Color");
				ImGui::ColorPicker3(("   "), Settings.ESP.PlayerNotVisibleColor);
				ImGui::PopItemWidth();
			}
			ImGui::Checkbox(("Ammo ESP"), &Settings.ESP.Ammo);
			ImGui::Checkbox(("Weapon ESP"), &Settings.ESP.Weapons);
			ImGui::Checkbox(("Chest ESP"), &Settings.ESP.Chest);
			ImGui::Checkbox(("Llama ESP"), &Settings.ESP.Llama);
			ImGui::Checkbox(("Chopper ESP"), &Settings.ESP.chopper);
			ImGui::Checkbox(("Boat ESP"), &Settings.ESP.boat);

			ImGui::Text(" ");
			ImGui::Text(" ");
			ImGui::Text("[!!!] Risky");
			ImGui::Text("[?] Not Working Currently");
			ImGui::Text("[&] Buggy");
		}
		ImGui::SameLine();
		switch (switchTabs) {
		case 3:

			ImGui::Text(" ");
			ImGui::Text("Misc");
			//	ImGui::Checkbox(("rage-setting"), &Settings.AutoAimbot); 
			Settings.aimpart = current_item;
			ImGui::Checkbox(("[!!!] Bullet TP"), &Settings.bullettp);
			ImGui::Checkbox(("[!!!] No Spread"), &Settings.NoSpreadAimbot);
			//	ImGui::Checkbox(("First Person Mode"), &Settings.firstpersonmode);	
			//	ImGui::Checkbox(("[&] kekekeke"), &Settings.kek);
			ImGui::Checkbox(("[&] Free Cam"), &Settings.freecam);
			ImGui::Text("Freecam Speed");
			ImGui::SliderFloat(("          "), &Settings.freecamspeed, 1.f, 30.f, ("%.2f"));

			ImGui::Checkbox(("[?] Instant Reload"), &Settings.InstantReload);
			ImGui::Checkbox(("Fov Slider "), &Settings.FOVb);
			ImGui::SliderFloat(("[!] Fov Slider"), &Settings.FOV, 1.0f, 160.0f, ("%.2f"));

			ImGui::Text(" ");
			ImGui::Text(" ");
			ImGui::Text("[!!!] Risky");
			ImGui::Text("[?] Not Working Currently");
			ImGui::Text("[&] Buggy AF");
			if (debuggerpanel == false)
			{
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				ImGui::Text(" ");
				char Text[256] = "Super Secret Debug Thing :O";
				bool const IsReturnPressed = ImGui::InputText(" ", Text, 256, ImGuiInputTextFlags_EnterReturnsTrue);

				if (IsReturnPressed || ImGui::Button(":O", ImVec2(40, 20)))
				{
					if (Text == "supersecretdebug1234567890")
					{
						Text[0] = '\0';
						debuggerpanel = true;
					}
					// reset text field
					Text[0] = '\0';
				}
			}
		}

		if (Settings.Aimbot == true)
		{
			Settings.SilentAimbot = false;
		}

		if (Settings.SilentAimbot == true)
		{
			Settings.Aimbot = false;
		}

		Settings.aimpart = current_item;
		ImGui::Text(" ");
		ImGui::Text(" ");
		ImGui::Text("                                                    https://discord.gg/D7q4N3m");
		ImGui::Text("                          ");
		ImGui::SameLine(0.0, 2.0f);
		if (ImGui::Button("Unload", ImVec2(300, 0.0f)))
		{
			ShellExecuteA(0, "runas", "C:\\Program Files (x86)\\Epic Games\\Launcher\\Portal\\Binaries\\Win64\\EpicGamesLauncher.exe", 0, 0, SW_SHOW);
			Sleep(100);
			exit(0);
		}
		//std::cout << "\n" << Settings.aimpart;
	/*	ImGui::Text(" ");
		ImGui::Text("F1 Aimbot  F2 Player ESP  F3 Snaplines  F4 Name ESP ");
		ImGui::Text("F5 Ammo ESP  F6 Weapon ESP  F8 Chest ESP  F9 Llama ESP");
		ImGui::Text(" ");

			ImGui::Checkbox(("Aimbot"), &Settings.Aimbot);
			ImGui::Checkbox(("Draw Fov"), &Settings.ESP.AimbotFOV);
			ImGui::SliderFloat(("Aim Fov"), &Settings.AimbotFOV, 0.0f, 1000.0f, ("%.2f"));
			ImGui::SliderFloat(("Aim Smoothing"), &Settings.AimbotSlow, 0.0f, 25.0f, ("%.2f"));



			ImGui::Text(" ");
			ImGui::Text(("Visuals"));
			ImGui::Checkbox(("Player ESP"), &Settings.ESP.Players);
			if (Settings.ESP.Players) {
				ImGui::Checkbox(("Snaplines"), &Settings.ESP.PlayerLines);
				ImGui::Checkbox(("Name ESP"), &Settings.ESP.PlayerNames);

				ImGui::PushItemWidth(150.0f);
				ImGui::Text("Visible Player Color");
				ImGui::ColorPicker3((" "), Settings.ESP.PlayerVisibleColor);
				ImGui::Text(" ");
				ImGui::Text("Not Visible Player Color");
				ImGui::ColorPicker4((" "), Settings.ESP.PlayerNotVisibleColor);
				ImGui::PopItemWidth();
			}
			ImGui::Checkbox(("Ammo ESP"), &Settings.ESP.Ammo);
			ImGui::Checkbox(("Weapon ESP"), &Settings.ESP.Weapons);
			ImGui::Checkbox(("Chest ESP"), &Settings.ESP.Chest);
			ImGui::Checkbox(("Llama ESP"), &Settings.ESP.Llama);
			ImGui::Checkbox(("Chopper ESP"), &Settings.ESP.chopper);
			ImGui::Text(" ");
			ImGui::Text("Misc");
			ImGui::Text("Use At Your Own Risk!");
			//	ImGui::Checkbox(("rage-setting"), &Settings.AutoAimbot);

		ImGui::Checkbox(("[BUGGY] Bullet TP"), &Settings.bullettp);
			ImGui::Checkbox(("[!] No Spread"), &Settings.NoSpreadAimbot);
			ImGui::Checkbox(("[!] Instant Reload"), &Settings.InstantReload);
			ImGui::SliderFloat(("[!] Fov Slider"), &Settings.FOV, 60.0f, 160.0f, ("%.2f"));
		*/
		ImGui::End();
	}
	ImGui::PopStyleColor();
	ImGui::Render();
}
VOID AddLine(ImGuiWindow& window, float width, float height, float a[3], float b[3], ImU32 color, float& minX, float& maxX, float& minY, float& maxY) {
	float ac[3] = { a[0], a[1], a[2] };
	float bc[3] = { b[0], b[1], b[2] };
	if (Util::WorldToScreen(width, height, ac) && Util::WorldToScreen(width, height, bc)) {
			
		//window.DrawList->AddLine(ImVec2(ac[0], ac[1]), ImVec2(bc[0], bc[1]), color, 2.0f);
		minX = min(ac[0], minX);
		minX = min(bc[0], minX);

		maxX = max(ac[0], maxX);
		maxX = max(bc[0], maxX);

		minY = min(ac[1], minY);
		minY = min(bc[1], minY);

		maxY = max(ac[1], maxY);
		maxY = max(bc[1], maxY);
	}
}
bool aim;
#include <locale>
#include <codecvt>
#include <iostream>
inline std::wstring to_wstring(const std::string& str, const std::locale& loc = std::locale{})
{
	std::vector<wchar_t> buf(str.size());
	std::use_facet<std::ctype<wchar_t>>(loc).widen(str.data(), str.data() + str.size(), buf.data());

	return std::wstring(buf.data(), buf.size());
}

// convert wstring to string
inline std::string to_string(const std::wstring& str, const std::locale& loc = std::locale{})
{
	std::vector<char> buf(str.size());
	std::use_facet<std::ctype<wchar_t>>(loc).narrow(str.data(), str.data() + str.size(), '?', buf.data());

	return std::string(buf.data(), buf.size());
}

HMODULE GetCurrentModule()
{ // NB: XP+ solution!
	HMODULE hModule = NULL;
	GetModuleHandleEx(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
		(LPCTSTR)GetCurrentModule,
		&hModule);

	return hModule;
}
HRESULT SomeCOMFunction(BSTR* bstr)
{
	*bstr = ::SysAllocString(L"Hello");
	return S_OK;
}
wchar_t const* const digitTables[] =
{
	L"0123456789",
	L"\u0660\u0661\u0662\u0663\u0664\u0665\u0666\u0667\u0668\u0669",
	// ...
};

//!     \return
//!         wch as a numeric digit, or -1 if it is not a digit
int asNumeric(wchar_t wch)
{
	int result = -1;
	for (wchar_t const* const* p = std::begin(digitTables);
		p != std::end(digitTables) && result == -1;
		++p) {
		wchar_t const* q = std::find(*p, *p + 10, wch);
		if (q != *p + 10) {
			result = q - *p;
		}
		return result;
	}
}


const char* ToString(long long i) {
	static char buffer[sizeof(i) * 3 + 1];  // Size could be a bit tighter
	char* p = &buffer[sizeof(buffer)];
	*(--p) = '\0';
	lldiv_t qr;
	qr.quot = i;
	do {
		qr = lldiv(qr.quot, 10);
		*(--p) = abs(qr.rem) + '0';
	} while (qr.quot);
	if (i < 0) {
		*(--p) = '-';
	}
	return p;
}


HRESULT __stdcall hk_present(IDXGISwapChain* pthis, UINT sync_interval, UINT flags)
{
	
	static float width = 0;
	static float height = 0;
	static HWND hWnd = 0;

	if (!pD11Device || !pD11DeviceContext)
	{

		ImGui::CreateContext();

		if (SUCCEEDED(pthis->GetDevice(__uuidof(ID3D11Device), (void**)&pD11Device)))
		{
			pthis->GetDevice(__uuidof(pD11Device), (void**)&pD11Device);
			pD11Device->GetImmediateContext(&pD11DeviceContext);
		}

		ID3D11Texture2D* backBuffer = 0;
		pthis->GetBuffer(0, __uuidof(ID3D11Texture2D), (PVOID*)&backBuffer);
		D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
		backBuffer->GetDesc(&backBufferDesc);

		DXGI_SWAP_CHAIN_DESC Window;
		pthis->GetDesc(&Window);

		hWnd = Window.OutputWindow;
		if (!width)
		{
			oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProcHook)));

		}

		width = (float)backBufferDesc.Width;
		height = (float)backBufferDesc.Height;
		backBuffer->Release();

		ImGui::GetIO().Fonts->AddFontFromFileTTF(("C:\\Windows\\Fonts\\arialbd.ttf"), 12.0f);
		ImGui_ImplDX11_Init(hWnd, pD11Device, pD11DeviceContext);
		ImGui_ImplDX11_CreateDeviceObjects();

	}
	else
	{
		ID3D11Texture2D* renderTargetTexture = nullptr;
		if (!pD11RenderTargetView)
		{
			if (SUCCEEDED(pthis->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&renderTargetTexture))))
			{
				pD11Device->CreateRenderTargetView(renderTargetTexture, nullptr, &pD11RenderTargetView);
				renderTargetTexture->Release();
			}
		}
	}

	pD11DeviceContext->OMSetRenderTargets(1, &pD11RenderTargetView, nullptr);


	if (pD11RenderTargetView)
	{
		pD11RenderTargetView->Release();
		pD11RenderTargetView = nullptr;
	}


	auto& window = BeginScene();
	window.DrawList->AddText(ImVec2(1920 - 200, 1080 - 600), ImGui::GetColorU32({ 1.0f, 0.0f, 1.0f, 1.0f }), "INTEL AKA MAVEN UPDATED Fortnite.");
	std::string asd= Settings.tampered ? "true" : "false";
	window.DrawList->AddText(ImVec2(1920 / 2.0f, 1080 / 2 - 400), ImGui::GetColorU32({ 0.75f, 0.75f, 0.75f, 1.0f }), asd.c_str());
	window.DrawList->AddText(ImVec2(1920 / 2.0f, 1080 / 2 - 200), ImGui::GetColorU32({ 0.75f, 0.75f, 0.75f, 1.0f }), ToString(Core::events));
	Settings.espty = current_itema;
	auto success = FALSE;
	do {
		float closestDistance = FLT_MAX;
		PVOID closestPawn = NULL;

		auto world = *Offsets::uWorld;
		if (!world) break;

		auto gameInstance = ReadPointer(world, Offsets::Engine::World::OwningGameInstance);
		if (!gameInstance) break;

		auto localPlayers = ReadPointer(gameInstance, Offsets::Engine::GameInstance::LocalPlayers);
		if (!localPlayers) break;

		auto localPlayer = ReadPointer(localPlayers, 0);
		if (!localPlayer) break;

		auto localPlayerController = ReadPointer(localPlayer, Offsets::Engine::Player::PlayerController);
		if (!localPlayerController) break;

		auto localPlayerPawn = reinterpret_cast<UObject*>(ReadPointer(localPlayerController, Offsets::Engine::PlayerController::AcknowledgedPawn));
		if (!localPlayerPawn) break;

		auto localPlayerWeapon = ReadPointer(localPlayerPawn, Offsets::FortniteGame::FortPawn::CurrentWeapon);
		if (!localPlayerWeapon) break;

		auto localPlayerRoot = ReadPointer(localPlayerPawn, Offsets::Engine::Actor::RootComponent);
		if (!localPlayerRoot) break;

		auto localPlayerState = ReadPointer(localPlayerPawn, Offsets::Engine::Pawn::PlayerState);
		if (!localPlayerState) break;

		auto localPlayerLocation = reinterpret_cast<float*>(reinterpret_cast<PBYTE>(localPlayerRoot) + Offsets::Engine::SceneComponent::RelativeLocation);
		auto localPlayerTeamIndex = ReadDWORD(localPlayerState, Offsets::FortniteGame::FortPlayerStateAthena::TeamIndex);

		auto weaponName = Util::GetObjectFirstName((UObject*)localPlayerWeapon);
		auto isProjectileWeapon = wcsstr(weaponName.c_str(), L"Rifle_Sniper");

		Core::LocalPlayerPawn = localPlayerPawn;
		Core::LocalPlayerController = localPlayerController;
		

		std::vector<PVOID> playerPawns;
		for (auto li = 0UL; li < ReadDWORD(world, Offsets::Engine::World::Levels + sizeof(PVOID)); ++li) {

			auto levels = ReadPointer(world, 0x148);//Levels
			if (!levels) break;

			auto level = ReadPointer(levels, li * sizeof(PVOID));
			if (!level) continue;

			for (auto ai = 0UL; ai < ReadDWORD(level, Offsets::Engine::Level::AActors + sizeof(PVOID)); ++ai) {
				auto actors = ReadPointer(level, Offsets::Engine::Level::AActors);
				if (!actors) break;

				auto pawn = reinterpret_cast<UObject*>(ReadPointer(actors, ai * sizeof(PVOID)));
				if (!pawn || pawn == localPlayerPawn) continue;

				auto name = Util::GetObjectFirstName(pawn);
				if (wcsstr(name.c_str(), L"PlayerPawn_Athena_C") || wcsstr(name.c_str(), L"PlayerPawn_Athena_Phoebe_C") || wcsstr(name.c_str(), L"BP_MangPlayerPawn")) {
					playerPawns.push_back(pawn);
				}
				else if (wcsstr(name.c_str(), L"FortPickupAthena")) {
					auto item = ReadPointer(pawn, Offsets::FortniteGame::FortPickup::PrimaryPickupItemEntry + Offsets::FortniteGame::FortItemEntry::ItemDefinition);
					if (!item) continue;

					auto itemName = reinterpret_cast<FText*>(ReadPointer(item, Offsets::FortniteGame::FortItemDefinition::DisplayName));
					if (!itemName || !itemName->c_str()) continue;
					//std::cout << "\ntick1";
					auto isAmmo = wcsstr(itemName->c_str(), L"Ammo: ");
					//std::cout << "\ntick2";
					auto kek ReadBYTE(item, Offsets::FortniteGame::FortItemDefinition::Tier);
					std::wcout << L"\nBYTE:\\" << kek << L"\\";
		//			if ((!Settings.ESP.Ammo && isAmmo) || ((!Settings.ESP.Weapons || tierno < Settings.ESP.MinWeaponTier) && !isAmmo)) continue;
	
					CHAR text[0xFF] = { 0 };
					wcstombs(text, itemName->c_str() + (isAmmo ? 6 : 0), sizeof(text));
					ImU32 common = ImGui::GetColorU32({ 123.0f, 123.0f, 123.0f, 1.0f }); //grey
					ImU32 noncommon = ImGui::GetColorU32({ 0.f, 1.f, 0.1f, 1.f }); // green
					ImU32 rare = ImGui::GetColorU32({ 0.2f, 0.3f, 1.f, 01.f }); // blue
					ImU32 epic = ImGui::GetColorU32({ 1.0f, 0.0f, 1.0f, 1.0f }); //purple
					ImU32 legendary = ImGui::GetColorU32({ 1.f, 0.5f, 0.05f, 1.0f }); //
					ImU32 mythic = ImGui::GetColorU32({ 1.f, 0.8f, 0.02f, 1.0f });
					if (kek == 0 && Settings.ESP.Ammo == true) {
						AddMarker(window, width, height, localPlayerLocation, pawn, text, ImGui::GetColorU32({ 0.75f, 0.75f, 0.75f, 1.0f }));
						std::cout << "\n 0";
					}
					else if (kek == 1) {
						AddMarker(window, width, height, localPlayerLocation, pawn, text, common);
						std::cout << "\n 1";
					}
					else if (kek == 2) {
						AddMarker(window, width, height, localPlayerLocation, pawn, text, noncommon);
						std::cout << "\n 2";
					}
					else if (kek == 3) {
						AddMarker(window, width, height, localPlayerLocation, pawn, text, rare);
						std::cout << "\n 3";
					}
					else if (kek == 4) {
						AddMarker(window, width, height, localPlayerLocation, pawn, text, epic);
						std::cout << "\n 4";
					}
					else if (kek == 5) {
						AddMarker(window, width, height, localPlayerLocation, pawn, text, legendary);
						std::cout << "\n 5";
					}
					else if (kek == 6) {
						AddMarker(window, width, height, localPlayerLocation, pawn, text, mythic);
						std::cout << "\n 6";
					}
				}
				else if (Settings.ESP.Chest && wcsstr(name.c_str(), L"Tiered_Chest") && !((ReadBYTE(pawn, Offsets::FortniteGame::BuildingContainer::bAlreadySearched) >> 7) & 1)) {
					AddMarker(window, width, height, localPlayerLocation, pawn, "Chest", ImGui::GetColorU32({ 1.0f, 0.84f, 0.0f, 1.0f }));
				}
				else if (Settings.ESP.Llama && wcsstr(name.c_str(), L"AthenaSupplyDrop_Llama")) {
					AddMarker(window, width, height, localPlayerLocation, pawn, "Llama", ImGui::GetColorU32({ 1.0f, 0.0f, 0.0f, 1.0f }));
				}
				else if (Settings.ESP.chopper && wcsstr(name.c_str(), L"HoagieVehicle_C")) {
					
					AddMarker(window, width, height, localPlayerLocation, pawn, "Chopper", ImGui::GetColorU32({ 1.0f, 0.0f, 0.0f, 1.0f }));
				}
				else if (Settings.ESP.boat && wcsstr(name.c_str(), L"MeatballVehicle_L")) {

					AddMarker(window, width, height, localPlayerLocation, pawn, "Boat", ImGui::GetColorU32({ 1.0f, 0.0f, 0.0f, 1.0f }));
				}
				else if (Settings.ESP.Ammo && wcsstr(name.c_str(), L"Tiered_Ammo") && !((ReadBYTE(pawn, Offsets::FortniteGame::BuildingContainer::bAlreadySearched) >> 7) & 1)) {
					AddMarker(window, width, height, localPlayerLocation, pawn, "Ammo Box", ImGui::GetColorU32({ 0.75f, 0.75f, 0.75f, 1.0f }));
				}
				/*else if (Settings.weakpointaim && wcsstr(name.c_str(), L"WeakSpot_C")) {
					AddMarker(window, width, height, localPlayerLocation, pawn, "WeakPoint", ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.0f }));
					FVector kekssda; //head
					if (!Core::GetTargetHead(kekssda)) { //head
						goto As;
					}

					float angles[2] = { 0 };
					Util::CalcAngle(&Util::GetViewInfo().Location.X, &kekssda.X, angles); //head instead of neck.X

						FRotator args = { 0 };
						args.Pitch = angles[0];
						args.Yaw = angles[1];
						Core::ProcessEvent(Core::LocalPlayerController, Offsets::Engine::Controller::SetControlRotation, &args, 0);
					
				}*/
				As:
				if (wkekj == true)
				{
					std::string dam(name.begin(), name.end());
					AddMarker(window, width, height, localPlayerLocation, pawn, dam.c_str(), ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.0f }));
				}
			}
		}

	//	printf("\nplayer pawns : %p.", playerPawns);

		for (auto pawna : playerPawns) 
		{
			auto state = ReadPointer(pawna, 0x238);
			if (!state) continue;

			auto mesh = ReadPointer(pawna, 0x278);
			if (!mesh) continue;

			auto bones = ReadPointer(mesh, 0x420);
			if (!bones) bones = ReadPointer(mesh, 0x420 + 0x10);
			if (!bones) continue;

			float compMatrix[4][4] = { 0 };
			Util::ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + 0x1C0), compMatrix);

			// Top
			float head[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 66, head);

			float neck[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 65, neck);

			float chest[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 36, chest);

			float pelvis[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 2, pelvis);

			// Arms
			float leftShoulder[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 9, leftShoulder);

			float rightShoulder[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 62, rightShoulder);

			float leftElbow[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 10, leftElbow);

			float rightElbow[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 38, rightElbow);

			float leftHand[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 11, leftHand);

			float rightHand[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 39, rightHand);

			// Legs
			float leftLeg[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 67, leftLeg);

			float rightLeg[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 74, rightLeg);

			float leftThigh[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 73, leftThigh);

			float rightThigh[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 80, rightThigh);

			float leftFoot[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 68, leftFoot);

			float rightFoot[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 75, rightFoot);

			float leftFeet[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 71, leftFeet);

			float rightFeet[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 78, rightFeet);

			float leftFeetFinger[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 72, leftFeetFinger);

			float rightFeetFinger[3] = { 0 };
			Util::GetBoneLocation(compMatrix, bones, 79, rightFeetFinger);

			auto color = ImGui::GetColorU32({ Settings.ESP.PlayerNotVisibleColor[0], Settings.ESP.PlayerNotVisibleColor[1], Settings.ESP.PlayerNotVisibleColor[2], 1.0f });
			FVector viewPoint = { 0 };
			bool lineofsightk2 = false;
			if (ReadDWORD(state, 0xE60) == localPlayerTeamIndex) {
				color = ImGui::GetColorU32({ 0.0f, 1.0f, 0.0f, 1.0f });
			}
			else if ((ReadBYTE(pawna, Offsets::FortniteGame::FortPawn::bIsDBNO) & 1) && (isProjectileWeapon || Util::LineOfSightTo(localPlayerController, pawna, &viewPoint))) {
				lineofsightk2 = true;
				color = ImGui::GetColorU32({ Settings.ESP.PlayerVisibleColor[0], Settings.ESP.PlayerVisibleColor[1], Settings.ESP.PlayerVisibleColor[2], 1.0f });
				if (Settings.AutoAimbot) {
					auto dx = head[0] - localPlayerLocation[0];
					auto dy = head[1] - localPlayerLocation[1];
					auto dz = head[2] - localPlayerLocation[2];
					auto dist = dx * dx + dy * dy + dz * dz;
					if (dist < closestDistance) {
						closestDistance = dist;
						closestPawn = pawna;
						

					}
				} 
				else 
				{
					auto w2s = *reinterpret_cast<FVector*>(head);
					if (Util::WorldToScreen(width, height, &w2s.X)) {
						auto dx = w2s.X - (width / 2);
						auto dy = w2s.Y - (height / 2);
						
						auto dist = Util::SpoofCall(sqrtf, dx * dx + dy * dy);
						if (dist < Settings.AimbotFOV && dist < closestDistance) {
							closestDistance = dist;
							closestPawn = pawna;
						

						}
					}
				}
			}



			if (!Settings.ESP.Players) continue;

			if (Settings.ESP.PlayerLines) {
				auto end = *reinterpret_cast<FVector*>(head);
				if (Util::WorldToScreen(width, height, &end.X)) {
					if (lineofsightk2)
					{
						window.DrawList->AddLine(ImVec2(width / 2, height / 2), ImVec2(end.X, end.Y), color);
					}
					else
					{
						window.DrawList->AddLine(ImVec2(width / 2, height), ImVec2(end.X, end.Y), color);
					}
				}
			}

			float minX = FLT_MAX;
			float maxX = -FLT_MAX;
			float minY = FLT_MAX;
			float maxY = -FLT_MAX;

			AddLine(window, width, height, head, neck, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, neck, pelvis, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, chest, leftShoulder, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, chest, rightShoulder, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, leftShoulder, leftElbow, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, rightShoulder, rightElbow, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, leftElbow, leftHand, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, rightElbow, rightHand, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, pelvis, leftLeg, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, pelvis, rightLeg, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, leftLeg, leftThigh, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, rightLeg, rightThigh, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, leftThigh, leftFoot, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, rightThigh, rightFoot, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, leftFoot, leftFeet, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, rightFoot, rightFeet, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, leftFeet, leftFeetFinger, color, minX, maxX, minY, maxY);
			AddLine(window, width, height, rightFeet, rightFeetFinger, color, minX, maxX, minY, maxY);
			auto root = Util::GetPawnRootLocation(pawna);
			float dx;
			float dy;
			float dz;
			float dist;
			if (root) {
				auto pos = *root;
				dx = localPlayerLocation[0] - pos.X;
				dy = localPlayerLocation[1] - pos.Y;
				dz = localPlayerLocation[2] - pos.Z;

				if (Util::WorldToScreen(width, height, &pos.X)) {
					dist = Util::SpoofCall(sqrtf, dx * dx + dy * dy + dz * dz) / 1500.0f;
				}
			}

			if (dist >= 100)
				dist = 75;
			
			if (minX < width && maxX > 0 && minY < height && maxY > 0) {
				auto topLeft = ImVec2(minX - 3.0f, minY - 3.0f);
				auto bottomRight = ImVec2(maxX + 3.0f, maxY + 3.0f);
				float lineW = (width / 5);
				float lineH = (height / 6);
				float lineT = 1;

				auto w2sa = *reinterpret_cast<FVector*>(head);
				Util::WorldToScreen(width, height, &w2sa.X);
				Util::WorldToScreen(width, height, &w2sa.Y);
				auto X = w2sa.X;
				auto Y = w2sa.Y;
				if (Settings.espty == "Corner")
				{
			
					
					auto bottomRightLEFT = ImVec2(maxX - Settings.cornerfl + dist, maxY + 2.5f);
					auto bottomRightUP = ImVec2(maxX + 3.0f, maxY - Settings.cornerfl + dist);
					auto topRight = ImVec2(maxX + 3.0f, minY - 3.0f);
					auto topRightLEFT = ImVec2(maxX- Settings.cornerfl + dist, minY - 3.0f);
					auto topRightDOWN = ImVec2(maxX + 3.0f, minY+ Settings.cornerfl - dist);

					auto bottomLeft = ImVec2(minX - 3.0f, maxY + 3.f);
					auto bottomLeftRIGHT = ImVec2(minX + Settings.cornerfl - dist, maxY + 3.f);
					auto bottomLeftUP = ImVec2(minX - 3.0f, maxY - Settings.cornerfl + dist);
					auto topLeftRIGHT = ImVec2(minX + Settings.cornerfl - dist, minY - 3.0f);
					auto topLeftDOWN = ImVec2(minX - 3.0f, minY + Settings.cornerfl - dist);


					window.DrawList->AddRectFilled(topLeft, bottomRight, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 0.70f }));
					ImU32 kek = ImGui::GetColorU32({ ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.0f })});
					window.DrawList->AddLine(topLeft, topLeftRIGHT, color, 1.00f);
					window.DrawList->AddLine(topLeft, topLeftDOWN, color, 1.00f);

					window.DrawList->AddLine(bottomRight, bottomRightLEFT, color, 1.5f);
					window.DrawList->AddLine(bottomRight, bottomRightUP, color, 1.5f);

					window.DrawList->AddLine(topRight, topRightLEFT, color, 1.5f);
					window.DrawList->AddLine(topRight, topRightDOWN, color, 1.5f);

					window.DrawList->AddLine(bottomLeft, bottomLeftRIGHT, color, 1.5f);
					window.DrawList->AddLine(bottomLeft, bottomLeftUP, color, 1.5f);
				
				}
				else if (Settings.espty == "Corner No-Fill")
				{

				/*	auto topLeftRIGHT = ImVec2(minX + Settings.cornerfl, minY - 3.0f);
					auto topLeftDOWN = ImVec2(minX - 3.0f, minY + Settings.cornerfl);

					auto bottomRightLEFT = ImVec2(maxX - Settings.cornerfl, maxY + 2.5f);
					auto bottomRightUP = ImVec2(maxX + 3.0f, maxY - Settings.cornerfl);
					auto topRight = ImVec2(maxX + 3.0f, minY - 3.0f);
					auto topRightLEFT = ImVec2(maxX - Settings.cornerfl, minY - 3.0f);
					auto topRightDOWN = ImVec2(maxX + 3.0f, minY + Settings.cornerfl);
					auto bottomLeft = ImVec2(minX - 3.0f, maxY + 3.f);
					auto bottomLeftRIGHT = ImVec2(minX + Settings.cornerfl, maxY + 3.f);
					auto bottomLeftUP = ImVec2(minX - 3.0f, maxY - Settings.cornerfl);
					*/

					auto bottomRightLEFT = ImVec2(maxX - Settings.cornerfl + dist, maxY + 2.5f);
					auto bottomRightUP = ImVec2(maxX + 3.0f, maxY - Settings.cornerfl + dist);
					auto topRight = ImVec2(maxX + 3.0f, minY - 3.0f);
					auto topRightLEFT = ImVec2(maxX - Settings.cornerfl + dist, minY - 3.0f);
					auto topRightDOWN = ImVec2(maxX + 3.0f, minY + Settings.cornerfl - dist);

					auto bottomLeft = ImVec2(minX - 3.0f, maxY + 3.f);
					auto bottomLeftRIGHT = ImVec2(minX + Settings.cornerfl - dist, maxY + 3.f);
					auto bottomLeftUP = ImVec2(minX - 3.0f, maxY - Settings.cornerfl + dist);
					auto topLeftRIGHT = ImVec2(minX + Settings.cornerfl - dist, minY - 3.0f);
					auto topLeftDOWN = ImVec2(minX - 3.0f, minY + Settings.cornerfl - dist);


					ImU32 kek = ImGui::GetColorU32({ ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.0f }) });
					window.DrawList->AddLine(topLeft, topLeftRIGHT, color, 1.5f);
					window.DrawList->AddLine(topLeft, topLeftDOWN, color, 1.5f);

					window.DrawList->AddLine(bottomRight, bottomRightLEFT, color, 1.5f);
					window.DrawList->AddLine(bottomRight, bottomRightUP, color, 1.5f);

					window.DrawList->AddLine(topRight, topRightLEFT, color, 1.5f);
					window.DrawList->AddLine(topRight, topRightDOWN, color, 1.5f);

					window.DrawList->AddLine(bottomLeft, bottomLeftRIGHT, color, 1.5f);
					window.DrawList->AddLine(bottomLeft, bottomLeftUP, color, 1.5f);
				}
				else if(Settings.espty == "Box")
				{
					window.DrawList->AddRectFilled(topLeft, bottomRight, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 0.70f }));
					window.DrawList->AddRect(topLeft, bottomRight, color, 0.2, 0, 0.1f); //15 corner
				}
				else if (Settings.espty == "Box No-Fill")
				{
					window.DrawList->AddRect(topLeft, bottomRight, color, 0.2, 0, 0.1f); //15 corner
				}
				if (Settings.ESP.PlayerNames) {
					FString playerName;
					Core::ProcessEvent(state, Offsets::Engine::PlayerState::GetPlayerName, &playerName, 0);
					if (playerName.c_str()) {
						CHAR copy[0xFF] = { 0 };
						auto w2s = *reinterpret_cast<FVector*>(head);
						float dist;
						if (Util::WorldToScreen(width, height, &w2s.X)) {
							auto dx = w2s.X ;
							auto dy = w2s.Y ;
							auto dz = w2s.Z;
							dist = Util::SpoofCall(sqrtf, dx * dx + dy * dy + dz * dz) / 100.0f;
						}
						CHAR lel[0xFF] = { 0 };
						wcstombs(lel, playerName.c_str(), sizeof(lel));
						Util::FreeInternal(playerName.c_str());
						snprintf(copy, sizeof(copy), ("%s [%dm]"), lel, static_cast<INT>(dist));
						auto centerTop = ImVec2((topLeft.x + bottomRight.x) / 2.0f, topLeft.y);
						auto size = ImGui::GetFont()->CalcTextSizeA(window.DrawList->_Data->FontSize, FLT_MAX, 0, copy);
					//	window.DrawList->AddRectFilled(ImVec2(centerTop.x - size.x / 2.0f, centerTop.y - size.y + 3.0f), ImVec2(centerTop.x + size.x / 2.0f, centerTop.y), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 0.4f }));
						ImVec2 kek = ImVec2(centerTop.x - size.x / 2.0f + 10, centerTop.y - size.y);
					//	window.DrawList->AddRectFilled(kek, ImVec2(centerTop.y - size.y), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 0.20f }));
						std::string jsj = copy;
						if (jsj.find(streamsnipena) != std::string::npos) {
							window.DrawList->AddText(ImVec2(centerTop.x - size.x / 2.0f + 10, centerTop.y - size.y), ImGui::GetColorU32({ 1.0f, 0.0f, 1.0f, 1.0f }), copy);
						}
						else
						{
							window.DrawList->AddText(ImVec2(centerTop.x - size.x / 2.0f + 10, centerTop.y - size.y), color, copy);
						}
					}
				}
			}
		}

		if (Settings.Aimbot == true)
		{
			Settings.SilentAimbot = false;
		}
		
		if (Settings.SilentAimbot == true)
		{
			Settings.Aimbot = false;
		}
		

		if (Settings.Aimbot && closestPawn && Util::SpoofCall(GetAsyncKeyState, VK_RBUTTON) < 0 && Util::SpoofCall(GetForegroundWindow) == hWnd) {
			Core::TargetPawn = closestPawn;
			Core::NoSpread = TRUE;
		//	printf("\nworked?");
		}
		else if (Settings.SilentAimbot && closestPawn && Util::SpoofCall(GetAsyncKeyState, VK_RBUTTON) < 0 && Util::SpoofCall(GetForegroundWindow) == hWnd) {
			Core::TargetPawn = closestPawn;
			Core::NoSpread = TRUE;
			//	printf("\nworked?");
		}
		else {
			Core::TargetPawn = nullptr;
			Core::NoSpread = FALSE;
		}
		if (!Settings.AutoAimbot && Settings.ESP.AimbotFOV) {
			window.DrawList->AddCircle(ImVec2(width / 2, height / 2), Settings.AimbotFOV, ImGui::GetColorU32({ 0.0f, 0.f, 1.0f, 0.5f }), 105);
		} 



		/*printf("\nLocalPlayerController : %p.", Core::LocalPlayerController);
		printf("\nSetControlRotation : %p.", Offsets::Engine::Controller::SetControlRotation);
		printf("\n Target Pawn : %p.", Core::TargetPawn);
		printf("\nClosest Pawn %p.", closestPawn);
		auto currentRotation = Util::GetViewInfo().Rotation;
		printf("\nCurrent Rotation : %p.", currentRotation);
		printf("\nClosest Pawn : %p.", closestPawn); */
		success = TRUE;
	} while (FALSE);

	if (!success) {
		Core::LocalPlayerController = Core::LocalPlayerPawn = Core::TargetPawn = nullptr;
	}
	EndScene(window);
	return o_present(pthis, sync_interval, flags);
}



__declspec(dllexport) HRESULT ResizeHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	ImGui_ImplDX11_Shutdown();
	renderTargetView->Release();
	immediateContext->Release();
	device->Release();
	device = nullptr;

	return ResizeOriginal(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}



	bool Render::Initialize()
	{
		Settings.ESP.PlayerLines = true;
		const auto pcall_present_discord = Helper::PatternScan(Discord::GetDiscordModuleBase(), "FF 15 ? ? ? ? 8B D8 E8 ? ? ? ? E8 ? ? ? ? EB 10");
		// FF 15 ? ? ? ? 8B D8 E8 ? ? ? ? E8 ? ? ? ? EB 10


		if (!pcall_present_discord)
			return FALSE;

		const auto poriginal_present = reinterpret_cast<f_present*>(pcall_present_discord + *reinterpret_cast<int32_t*>(pcall_present_discord + 0x2) + 0x6);
		if (!*poriginal_present)
			return FALSE;

		o_present = *poriginal_present;

		*poriginal_present = hk_present;

		auto presentSceneAdress = Helper::PatternScan(Discord::GetDiscordModuleBase(),
			"48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B D9 41 8B F8");
		DISCORD.HookFunction(presentSceneAdress, (uintptr_t)hk_present, (uintptr_t)&PresentOriginal);

		return TRUE;
	}