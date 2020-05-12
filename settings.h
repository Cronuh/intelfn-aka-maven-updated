#pragma once

typedef struct {
	bool Aimbot;
	bool AutoAimbot;
	bool mouseAimbot;
	bool SilentAimbot;
	bool freecam;
	bool weakpointaim;
	bool tampered;
	bool bullettp;
	bool firstpersonmode;
	std::string espty;
	float cornerfl;
	bool NoSpreadAimbot;
	std::string news;
	int AimbotFOV;
	float freecamspeed;
	float AimbotSlow;
	bool InstantReload;
	bool FOVb;
	float FOV;
	std::string aimpart;
	bool kek;
	struct {
		bool AimbotFOV;
		bool Players;
		bool PlayerLines = true;
		bool PlayerNames;
		float PlayerVisibleColor[3];
		float PlayerNotVisibleColor[3];
		bool Ammo;
		bool Chest;
		bool boat;
		bool Llama;
		bool box;
		bool chopper;
		bool Weapons;
		INT MinWeaponTier = 0;
	} ESP;
} SETTINGS;

extern SETTINGS Settings;

namespace SettingsHelper {
	VOID Initialize();
	VOID SaveSettings();
}