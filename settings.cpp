#include "stdafx.h"

SETTINGS Settings = { 0 };

namespace SettingsHelper {
	VOID SaveSettings() {
		CHAR path[0xFF];
		GetTempPathA(sizeof(path) / sizeof(path[0]), path);
		strcat(path, ("fnambt.settings"));

		auto file = fopen(path, ("wb"));
		if (file) {
			fwrite(&Settings, sizeof(Settings), 1, file);
			fclose(file);
		}
	}

	VOID ResetSettings() {
		Settings = { 0 };
		Settings.Aimbot = true;
		Settings.AutoAimbot = false;
		Settings.NoSpreadAimbot = false;
		Settings.AimbotFOV = 300.0f;
		Settings.AimbotSlow = 0.0f;
		Settings.ESP.AimbotFOV = true;
		Settings.tampered = true;
		Settings.InstantReload = false;
		Settings.espty = "Corner";
		Settings.FOV = 100.0f;
		Settings.kek = false;
		Settings.cornerfl = 7.f;
		Settings.aimpart = "Head";
		Settings.FOVb = false;
		Settings.freecam = false;
		Settings.firstpersonmode = false;
		Settings.freecamspeed = 6;
		Settings.ESP.AimbotFOV = true;
		Settings.weakpointaim = true;
		Settings.ESP.box = true;
		Settings.ESP.Players = true;
		Settings.ESP.PlayerNames = true;
		Settings.ESP.PlayerVisibleColor[0] = 1.0f;
		Settings.ESP.PlayerVisibleColor[1] = 0.0f;
		Settings.ESP.PlayerVisibleColor[2] = 0.0f;
		Settings.ESP.PlayerNotVisibleColor[0] = 0.f;
		Settings.ESP.PlayerNotVisibleColor[1] = 0.f;
		Settings.ESP.PlayerNotVisibleColor[2] = 0.f;
		Settings.ESP.Chest= true;
		Settings.ESP.chopper = true;
		Settings.ESP.PlayerLines = true;
		Settings.ESP.Llama = true;
		Settings.ESP.boat = true;
		Settings.ESP.Weapons = true;
		Settings.ESP.MinWeaponTier = 0;
		Settings.ESP.Ammo = true;


		SaveSettings();
	}

	VOID Initialize() {
		CHAR path[0xFF] = { 0 };
		GetTempPathA(sizeof(path) / sizeof(path[0]), path);
		strcat(path, ("fnambt.settings"));

		auto file = fopen(path, ("rb"));
		if (file) {
			fseek(file, 0, SEEK_END);
			auto size = ftell(file);

			if (size == sizeof(Settings)) {
				fseek(file, 0, SEEK_SET);
				fread(&Settings, sizeof(Settings), 1, file);
				fclose(file);
			}
			else {
				fclose(file);
				ResetSettings();
			}
		}
		else {
			ResetSettings();
		}
	}
}