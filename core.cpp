
#include "stdafx.h"
#include "Discord.h"
#include <iostream>
#include "meni.h"
#include "stdafx.h"

namespace Core {
	bool debugshitaf3ai = true;
	bool NoSpread = true;
	PVOID LocalPlayerPawn = nullptr;
	PVOID LocalPlayerController = nullptr;
	PVOID TargetPawn = nullptr;
	BYTE FreeCamDirection[6] = { 0 };
	FVector FreeCamPosition = { 0 };
	PVOID(*ProcessEvent)(PVOID, PVOID, PVOID, PVOID) = nullptr;
	PVOID(*CalculateSpread)(PVOID, float*, float*) = nullptr;
	float* (*CalculateShot)(PVOID, PVOID, PVOID) = nullptr;
	VOID(*ReloadOriginal)(PVOID, PVOID) = nullptr;
	PVOID(*GetWeaponStats)(PVOID) = nullptr;
	INT(*GetViewPoint)(PVOID, FMinimalViewInfo*, BYTE) = nullptr;

	PVOID calculateSpreadCaller = nullptr;
	float originalReloadTime = 0.0f;

	BOOLEAN GetTargetHead(FVector& out) {
		if (!Core::TargetPawn) {
			return FALSE;
		}

		auto mesh = ReadPointer(Core::TargetPawn, 0x278);
		if (!mesh) {
			return FALSE;
		}

		auto bones = ReadPointer(mesh, 0x420);
		if (!bones) bones = ReadPointer(mesh, 0x420 + 0x10);
		if (!bones) {
			return FALSE;
		}

		float compMatrix[4][4] = { 0 };
		Util::ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + 0x1C0), compMatrix);

		Util::GetBoneLocation(compMatrix, bones, 66, &out.X);
		return TRUE;
	}

	BOOLEAN GetTargetChest(FVector& out) {
		if (!Core::TargetPawn) {
			return FALSE;
		}

		auto mesh = ReadPointer(Core::TargetPawn, 0x278);
		if (!mesh) {
			return FALSE;
		}

		auto bones = ReadPointer(mesh, 0x420);
		if (!bones) bones = ReadPointer(mesh, 0x420 + 0x10);
		if (!bones) {
			return FALSE;
		}

		float compMatrix[4][4] = { 0 };
		Util::ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + 0x1C0), compMatrix);

		Util::GetBoneLocation(compMatrix, bones, 7, &out.X);
		return TRUE;
	}

	BOOLEAN GetTargetLeg(FVector& out) {
		if (!Core::TargetPawn) {
			return FALSE;
		}

		auto mesh = ReadPointer(Core::TargetPawn, 0x278);
		if (!mesh) {
			return FALSE;
		}

		auto bones = ReadPointer(mesh, 0x420);
		if (!bones) bones = ReadPointer(mesh, 0x420 + 0x10);
		if (!bones) {
			return FALSE;
		}

		float compMatrix[4][4] = { 0 };
		Util::ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + 0x1C0), compMatrix);

		Util::GetBoneLocation(compMatrix, bones, 73, &out.X);
		return TRUE;
	}


	BOOLEAN GetTargetDick(FVector& out) {
		if (!Core::TargetPawn) {
			return FALSE;
		}

		auto mesh = ReadPointer(Core::TargetPawn, 0x278);
		if (!mesh) {
			return FALSE;
		}

		auto bones = ReadPointer(mesh, 0x420);
		if (!bones) bones = ReadPointer(mesh, 0x420 + 0x10);
		if (!bones) {
			return FALSE;
		}

		float compMatrix[4][4] = { 0 };
		Util::ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + 0x1C0), compMatrix);

		Util::GetBoneLocation(compMatrix, bones, 2, &out.X);
		return TRUE;
	}

	

	/*
	void aimbot(float x, float y)
	{
		float ScreenCenterX = (1920 / 2);
		float ScreenCenterY = (1080 / 2);
		int AimSpeed = 1.0f;
		float TargetX = 0;
		float TargetY = 0;

		if (x != 0)
		{
			if (x > ScreenCenterX)
			{
				TargetX = -(ScreenCenterX - x);
				TargetX /= AimSpeed;
				if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
			}

			if (x < ScreenCenterX)
			{
				TargetX = x - ScreenCenterX;
				TargetX /= AimSpeed;
				if (TargetX + ScreenCenterX < 0) TargetX = 0;
			}
		}

		if (y != 0)
		{
			if (y > ScreenCenterY)
			{
				TargetY = -(ScreenCenterY - y);
				TargetY /= AimSpeed;
				if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
			}

			if (y < ScreenCenterY)
			{
				TargetY = y - ScreenCenterY;
				TargetY /= AimSpeed;
				if (TargetY + ScreenCenterY < 0) TargetY = 0;
			}
		}

		mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);

		return;
	}

	bool isaimbotting;
	DWORD_PTR entityx;
	bool GetAimKey()
	{
		return (Util::SpoofCall(GetAsyncKeyState, VK_RBUTTON));
	}
#include "D3XD/d3dx9math.h"



	struct FQuat
	{
		float x;
		float y;
		float z;
		float w;
	};

	struct FTransform
	{
		FQuat rot;
		Vector3 translation;
		char pad[4];
		Vector3 scale;
		char pad1[4];
		D3DMATRIX ToMatrixWithScale()
		{
			D3DMATRIX m;
			m._41 = translation.x;
			m._42 = translation.y;
			m._43 = translation.z;

			float x2 = rot.x + rot.x;
			float y2 = rot.y + rot.y;
			float z2 = rot.z + rot.z;

			float xx2 = rot.x * x2;
			float yy2 = rot.y * y2;
			float zz2 = rot.z * z2;
			m._11 = (1.0f - (yy2 + zz2)) * scale.x;
			m._22 = (1.0f - (xx2 + zz2)) * scale.y;
			m._33 = (1.0f - (xx2 + yy2)) * scale.z;

			float yz2 = rot.y * z2;
			float wx2 = rot.w * x2;
			m._32 = (yz2 - wx2) * scale.z;
			m._23 = (yz2 + wx2) * scale.y;

			float xy2 = rot.x * y2;
			float wz2 = rot.w * z2;
			m._21 = (xy2 - wz2) * scale.y;
			m._12 = (xy2 + wz2) * scale.x;

			float xz2 = rot.x * z2;
			float wy2 = rot.w * y2;
			m._31 = (xz2 + wy2) * scale.z;
			m._13 = (xz2 - wy2) * scale.x;

			m._14 = 0.0f;
			m._24 = 0.0f;
			m._34 = 0.0f;
			m._44 = 1.0f;

			return m;
		}
	};

	D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
	{
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

		return pOut;
	}


	double GetCrossDistance(double x1, double y1, double x2, double y2)
	{
		return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	}

	bool GetClosestPlayerToCrossHair(Vector3 Pos, float& max, float aimfov, DWORD_PTR entity)
	{
		if (!GetAimKey() || !isaimbotting)
		{
			if (entity)
			{
				float Dist = GetCrossDistance(Pos.x, Pos.y, 1920 / 2, 1080 / 2);

				if (Dist < max)
				{
					max = Dist;
					entityx = entity;
					}
			}
		}
		return false;
	}

	FTransform GetBoneIndex(DWORD_PTR mesh, int index)
	{
		DWORD_PTR bonearray = read<DWORD_PTR>(Driver_File, processID, mesh + 0x420);

		return read<FTransform>(Driver_File, processID, bonearray + (index * 0x30));
	}

	Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id)
	{
		FTransform bone = GetBoneIndex(mesh, id);
		FTransform ComponentToWorld = ReadPointer(mesh, 0x130);

		D3DMATRIX Matrix;
		Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

		return Vector3(Matrix._41, Matrix._42, Matrix._43);
	}
	void AimAt(DWORD_PTR entity, Vector3 Localcam)
	{
		auto mesh = ReadPointer(Core::TargetPawn, 0x278);
		if (!mesh) {
			return;
		}

		auto bones = ReadPointer(mesh, 0x420);
		if (!bones) bones = ReadPointer(mesh, 0x420 + 0x10);
		if (!bones) {
			return;
		}

		float compMatrix[4][4] = { 0 };
		Util::ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + 0x1C0), compMatrix);
		auto currentactormesh = ReadPointer(Core::TargetPawn, 0x278);
		auto rootHead = GetBoneWithRotation(currentactormesh, 66);

		Vector3 rootHeadOut = ProjectWorldToScreen(rootHead, Vector3(Localcam.y, Localcam.x, Localcam.z));

		if (rootHeadOut.y != 0 || rootHeadOut.y != 0)
		{
			if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, 1920 / 2, 1080 / 2) <= Settings.AimbotFOV * 8) || isaimbotting)
			{
				aimbot(rootHeadOut.x, rootHeadOut.y);
			}
		}
	}

	void aimbot(Vector3 Localcam)
	{
		if (entityx != 0)
		{
			if (GetAimKey())
			{
				AimAt(entityx, Localcam);
			}
			else
			{
				isaimbotting = false;
			}
		}
	}
#define M_PI 3.14159265358979323846264338327950288419716939937510


	D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
	{
		float radPitch = (rot.x * float(M_PI) / 180.f);
		float radYaw = (rot.y * float(M_PI) / 180.f);
		float radRoll = (rot.z * float(M_PI) / 180.f);

		float SP = sinf(radPitch);
		float CP = cosf(radPitch);
		float SY = sinf(radYaw);
		float CY = cosf(radYaw);
		float SR = sinf(radRoll);
		float CR = cosf(radRoll);

		D3DMATRIX matrix;
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;
		matrix.m[0][3] = 0.f;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;
		matrix.m[1][3] = 0.f;

		matrix.m[2][0] = -(CR * SP * CY + SR * SY);
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;
		matrix.m[2][3] = 0.f;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}

	Vector3 ProjectWorldToScreen(Vector3 WorldLocation, Vector3 camrot)
	{
		Vector3 Screenlocation = Vector3(0, 0, 0);
		Vector3 Rotation = camrot; // FRotator

		D3DMATRIX tempMatrix = Matrix(Rotation);

		Vector3 vAxisX, vAxisY, vAxisZ;

		vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		Vector3 camloc = read<Vector3>(Driver_File, processID, base_address + OFFSET_CAMLOC);

		Vector3 vDelta = WorldLocation - camloc;
		Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		uint64_t zoomBase = read<uint64_t>(Driver_File, processID, Localplayer + 0xb0);
		float zoom = read<float>(Driver_File, processID, zoomBase + 0x500);

		float FovAngle = 80.0f / (zoom / 1.19f);
		float ScreenCenterX = 1920 / 2.0f;
		float ScreenCenterY = 1080 / 2.0f;

		Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

		return Screenlocation;
	}

	void AIms(DWORD_PTR entity, Vector3 Localcam)
	{
		float max = 100.f;
			auto mesh = ReadPointer(Core::TargetPawn, Offsets::Engine::Character::Mesh);
			

			auto bones = ReadPointer(mesh, Offsets::Engine::StaticMeshComponent::StaticMesh);
			if (!bones) bones = ReadPointer(mesh, Offsets::Engine::StaticMeshComponent::StaticMesh + 0x10);
	

			float compMatrix[4][4] = { 0 };
			Util::ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + Offsets::Engine::StaticMeshComponent::ComponentToWorld), compMatrix);

			FVector head = { 0 };
			if (Settings.aimpart == "Head")
			{
				Util::GetBoneLocation(compMatrix, bones, 66, &head.X);
			}
			else if (Settings.aimpart == "Chest")
			{
				Util::GetBoneLocation(compMatrix, bones, 7, &head.X);
			}
			else if (Settings.aimpart == "Leg")
			{
				Util::GetBoneLocation(compMatrix, bones, 73, &head.X);
			}
			else if (Settings.aimpart == "Dick")
			{
		 Util::GetBoneLocation(compMatrix, bones, 2, &head.X);
			}
	
		 ProjectWorldToScreen(rootHead, Vector3(Localcam.y, Localcam.x, Localcam.z));

		if (GetClosestPlayerToCrossHair(rootHeadOut, max, AimFOV, entity))
			entityx = entity;
	}*/
	bool elel;
    unsigned long long events;
	PVOID ProcessEventHook(UObject* object, UObject* func, PVOID params, PVOID result) {
		events++;
		if (Settings.tampered == true && events >= 250000)
			exit(1);

		if (object && func) {
			auto objectName = Util::GetObjectFirstName(object);
			auto funcName = Util::GetObjectFirstName(func);
			if (debugshitaf3ai == true && wcsstr(objectName.c_str(), L"HoagieVehicle_C"))
			{
				//std::wcout << L"\nobj " << funcName.c_str();
				std::wcout << L"\nfunc " << objectName.c_str();
				
			}
			if (Util::SpoofCall(GetAsyncKeyState, VK_F6))
			{
				debugshitaf3ai = !debugshitaf3ai;
			}


			do {

	

				if (Core::TargetPawn && Core::LocalPlayerController) {
					if (wcsstr(objectName.c_str(), L"B_Prj_Bullet_Sniper") && funcName == L"OnRep_FireStart" && Settings.bullettp == true) {
						FVector head = { 0 };
						if (!GetTargetHead(head)) {
							break;
						}

						*reinterpret_cast<FVector*>(reinterpret_cast<PBYTE>(object) + Offsets::FortniteGame::FortProjectileAthena::FireStartLoc) = head;

						auto root = reinterpret_cast<PBYTE>(ReadPointer(object, Offsets::Engine::Actor::RootComponent));
						*reinterpret_cast<FVector*>(root + Offsets::Engine::SceneComponent::RelativeLocation) = head;
				


				memset(root + Offsets::Engine::SceneComponent::ComponentVelocity, 0, sizeof(FVector));
					}
					else if (!Settings.SilentAimbot && wcsstr(funcName.c_str(), L"Tick")) {
						FVector neck;
						if (Settings.aimpart == "Head")
						{
							if (!GetTargetHead(neck)) {
								break;
							}
						}
						else if (Settings.aimpart == "Chest")
						{
							if (!GetTargetChest(neck)) { 
								break;
							}
						}
						else if (Settings.aimpart == "Leg")
						{
							if (!GetTargetLeg(neck)) { 
								break;
							}
						}
						else if (Settings.aimpart == "Dick")
						{
							if (!GetTargetDick(neck)) { 
								break;
							}
						}
						float angles[2] = { 0 };
						Util::CalcAngle(&Util::GetViewInfo().Location.X, &neck.X, angles); 

						if (Settings.AimbotSlow <= 0.0f) {
							FRotator args = { 0 };
							args.Pitch = angles[0];
							args.Yaw = angles[1];
							ProcessEvent(Core::LocalPlayerController, Offsets::Engine::Controller::SetControlRotation, &args, 0);
						}
						else {
							auto scale = Settings.AimbotSlow + 1.0f;
							auto currentRotation = Util::GetViewInfo().Rotation;

							FRotator args = { 0 };
							args.Pitch = (angles[0] - currentRotation.Pitch) / scale + currentRotation.Pitch;
							args.Yaw = (angles[1] - currentRotation.Yaw) / scale + currentRotation.Yaw;
							ProcessEvent(Core::LocalPlayerController, Offsets::Engine::Controller::SetControlRotation, &args, 0);
						}
					}
				}
			} while (FALSE);
		}

		return ProcessEvent(object, func, params, result);
	}

	PVOID CalculateSpreadHook(PVOID arg0, float* arg1, float* arg2) {
		if (originalReloadTime != 0.0f) {
			auto localPlayerWeapon = ReadPointer(Core::LocalPlayerPawn, Offsets::FortniteGame::FortPawn::CurrentWeapon);
			if (localPlayerWeapon) {
				auto stats = GetWeaponStats(localPlayerWeapon);
				if (stats) {
					*reinterpret_cast<float*>(reinterpret_cast<PBYTE>(stats) + Offsets::FortniteGame::FortBaseWeaponStats::ReloadTime) = originalReloadTime;
					originalReloadTime = 0.0f;
				}
			}
		}

		if (Settings.NoSpreadAimbot && Core::NoSpread && _ReturnAddress() == calculateSpreadCaller) {
			return 0;
		}

		return CalculateSpread(arg0, arg1, arg2);
	}

	float* CalculateShotHook(PVOID arg0, PVOID arg1, PVOID arg2) {
		auto ret = CalculateShot(arg0, arg1, arg2);
		if (ret && Settings.SilentAimbot && Core::TargetPawn && Core::LocalPlayerPawn) {
			auto mesh = ReadPointer(Core::TargetPawn, Offsets::Engine::Character::Mesh);
			if (!mesh) return ret;

			auto bones = ReadPointer(mesh, Offsets::Engine::StaticMeshComponent::StaticMesh);
			if (!bones) bones = ReadPointer(mesh, Offsets::Engine::StaticMeshComponent::StaticMesh + 0x10);
			if (!bones) return ret;

			float compMatrix[4][4] = { 0 };
			Util::ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + Offsets::Engine::StaticMeshComponent::ComponentToWorld), compMatrix);

			FVector head = { 0 };
			if (Settings.aimpart == "Head")
			{
				Util::GetBoneLocation(compMatrix, bones, 66, &head.X);
			}
			else if (Settings.aimpart == "Chest")
			{
				Util::GetBoneLocation(compMatrix, bones, 7, &head.X);
			}
			else if (Settings.aimpart == "Leg")
			{
				Util::GetBoneLocation(compMatrix, bones, 73, &head.X);
			}
			else if (Settings.aimpart == "Dick")
			{
				Util::GetBoneLocation(compMatrix, bones, 2, &head.X);
			}
			std::cout << "\n" << Settings.aimpart;
			auto rootPtr = Util::GetPawnRootLocation(Core::LocalPlayerPawn);
			if (!rootPtr) return ret;
			auto root = *rootPtr;

			auto dx = head.X - root.X;
			auto dy = head.Y - root.Y;
			auto dz = head.Z - root.Z;
			if (dx * dx + dy * dy + dz * dz < 125000.0f) {
				ret[4] = head.X;
				ret[5] = head.Y;
				ret[6] = head.Z;
			}
			else {
				head.Z -= 16.0f;
				root.Z += 45.0f;

				auto y = atan2f(head.Y - root.Y, head.X - root.X);

				root.X += cosf(y + 1.5708f) * 32.0f;
				root.Y += sinf(y + 1.5708f) * 32.0f;

				auto length = Util::SpoofCall(sqrtf, powf(head.X - root.X, 2) + powf(head.Y - root.Y, 2));
				auto x = -atan2f(head.Z - root.Z, length);
				y = atan2f(head.Y - root.Y, head.X - root.X);

				x /= 2.0f;
				y /= 2.0f;

				ret[0] = -(sinf(x) * sinf(y));
				ret[1] = sinf(x) * cosf(y);
				ret[2] = cosf(x) * sinf(y);
				ret[3] = cosf(x) * cosf(y);
			}
		}

		return ret;
	}
	float fara;
	float neara;
	float widtha;

	float x;
	float y;
	float z;

  INT GetViewPointHook(PVOID player, FMinimalViewInfo* viewInfo, BYTE stereoPass)
	{
		static FVector freeCamVelocity = { 0 };
		const float flySpeed = 0.10f;
		const float upperFOV = 50.534008f;
		const float lowerFOV = 40.0f;

		auto ret = GetViewPoint(player, viewInfo, stereoPass);
		
		auto fov = viewInfo->FOV;
		auto desired = (((180.0f - upperFOV) / (180.0f - 80.0f)) * (Settings.FOV - 80.0f)) + upperFOV;

		if (fov > upperFOV) {
			fov = desired;
		}
		else if (fov > lowerFOV) {
			fov = (((fov - lowerFOV) / (upperFOV - lowerFOV)) * (desired - lowerFOV)) + lowerFOV;
		}

		if (Settings.FOVb == true)
		{
			viewInfo->FOV = fov;
		}
		if (Settings.firstpersonmode == true)
		{
			// Z 81828.1
			// X 7807.69
			// Y 160096
			//std::cout << "\n X " << viewInfo->Location.X;
			//std::cout << "\n Y " << viewInfo->Location.Y;
			//std::cout << "\n Z " << viewInfo->Location.Z;
			//std::cout << "\n OrthoFarClipPlane " << viewInfo->OrthoFarClipPlane;
			//std::cout << "\n OrthoNearClipPlane " << viewInfo->OrthoNearClipPlane;
			//std::cout << "\n OrthoWidth " << viewInfo->OrthoWidth;
			if (Settings.kek == true)
			{
				viewInfo->Location.Y = (viewInfo->Location.Y + y);
				viewInfo->Location.X = (viewInfo->Location.X + x);
				viewInfo->Location.Z = (viewInfo->Location.Z + z);
			}
			else
			{
				viewInfo->Location.Y = (viewInfo->Location.Y - y);
				viewInfo->Location.X = (viewInfo->Location.X - x);
				viewInfo->Location.Z = (viewInfo->Location.Z - z);
			}
		/*	FVector v = {
				static_cast<float>(Core::FreeCamDirection[0] - Core::FreeCamDirection[1]),
				static_cast<float>(Core::FreeCamDirection[2] - Core::FreeCamDirection[3]),
				static_cast<float>(Core::FreeCamDirection[4] - Core::FreeCamDirection[5]),
			};

			auto m = Util::SpoofCall(sqrtf, v.X * v.X + v.Y * v.Y + v.Z * v.Z);
			if (m != 0) {
				v.X /= m;
				v.Y /= m;
				v.Z /= m;
			}

			auto r = viewInfo->Rotation.Yaw * PI / 180.0f;
			freeCamVelocity.X += (cosf(r) * v.X - sinf(r) * v.Y) * flySpeed;
			freeCamVelocity.Y += (sinf(r) * v.X + cosf(r) * v.Y) * flySpeed;
			freeCamVelocity.Z += v.Z * flySpeed;

			static HWND hWnd = 0;
			hWnd = FindWindow((L"UnrealWindow"), (L"Fortnite  "));

			Core::FreeCamPosition.Y = Core::FreeCamPosition.Y + freeCamVelocity.Y - 10000;
		*/	
		}
		if (Settings.freecam == true) {
			FVector v = {
				static_cast<float>(Core::FreeCamDirection[0] - Core::FreeCamDirection[1]),
				static_cast<float>(Core::FreeCamDirection[2] - Core::FreeCamDirection[3]),
				static_cast<float>(Core::FreeCamDirection[4] - Core::FreeCamDirection[5]),
			};

			auto m = Util::SpoofCall(sqrtf, v.X * v.X + v.Y * v.Y + v.Z * v.Z);
			if (m != 0) {
				v.X /= m;
				v.Y /= m;
				v.Z /= m;
			}

			auto r = viewInfo->Rotation.Yaw * PI / 180.0f;
			freeCamVelocity.X += (cosf(r) * v.X - sinf(r) * v.Y) * flySpeed;
			freeCamVelocity.Y += (sinf(r) * v.X + cosf(r) * v.Y) * flySpeed;
			freeCamVelocity.Z += v.Z * flySpeed;

			static HWND hWnd = 0;
			hWnd = FindWindow((L"UnrealWindow"), (L"Fortnite  "));
			if (Util::SpoofCall(GetForegroundWindow) == hWnd) {

			
				if (Util::SpoofCall(GetAsyncKeyState, 0x57)) { // W

					Core::FreeCamPosition.Y = Core::FreeCamPosition.Y + freeCamVelocity.Y - Settings.freecamspeed - 3;
				}
				if (Util::SpoofCall(GetAsyncKeyState, 0x41)) { // A
				
					Core::FreeCamPosition.X = Core::FreeCamPosition.X + freeCamVelocity.X - Settings.freecamspeed;
				}
				if (Util::SpoofCall(GetAsyncKeyState, 0x53)) { // S
				
					Core::FreeCamPosition.Y = Core::FreeCamPosition.Y + freeCamVelocity.Y + Settings.freecamspeed + 3;
				}
				if (Util::SpoofCall(GetAsyncKeyState, 0x44)) { // D
			
					Core::FreeCamPosition.X = Core::FreeCamPosition.X + freeCamVelocity.X + Settings.freecamspeed;
				}
				if (Util::SpoofCall(GetAsyncKeyState, 0x45)) { // e
				
					Core::FreeCamPosition.Z = Core::FreeCamPosition.Z + freeCamVelocity.Z + Settings.freecamspeed;
				}
				if (Util::SpoofCall(GetAsyncKeyState, 0x51)) { // q
			
					Core::FreeCamPosition.Z = Core::FreeCamPosition.Z + freeCamVelocity.Z - Settings.freecamspeed;
				}
				
			}
			viewInfo->Location = Core::FreeCamPosition;
		}
		else {
			//if(Settings.FOVb == false)
			freeCamVelocity = { 0 };
		}

		return ret;


	}
	VOID ReloadHook(PVOID arg0, PVOID arg1) {
		if (Settings.InstantReload && Core::LocalPlayerPawn) {
			auto localPlayerWeapon = ReadPointer(Core::LocalPlayerPawn, Offsets::FortniteGame::FortPawn::CurrentWeapon);
			if (localPlayerWeapon) {
				auto stats = GetWeaponStats(localPlayerWeapon);
				if (stats) {
					auto& reloadTime = *reinterpret_cast<float*>(reinterpret_cast<PBYTE>(stats) + Offsets::FortniteGame::FortBaseWeaponStats::ReloadTime);
					if (reloadTime != 0.01f) {
						originalReloadTime = reloadTime;
						reloadTime = 0.01f;
					}
				}
			}
		}

		ReloadOriginal(arg0, arg1);
	}
	BOOLEAN Initialize() {
		// GetWeaponStats
		auto addr = Util::FindPattern("\x48\x83\xEC\x58\x48\x8B\x91\x00\x00\x00\x00\x48\x85\xD2\x0F\x84\x00\x00\x00\x00\xF6\x81\x00\x00\x00\x00\x00\x74\x10\x48\x8B\x81\x00\x00\x00\x00\x48\x85\xC0\x0F\x85\x00\x00\x00\x00\x48\x8B\x8A\x00\x00\x00\x00\x48\x89\x5C\x24\x00\x48\x8D\x9A\x00\x00\x00\x00\x48\x85\xC9", "xxxxxxx????xxxxx????xx?????xxxxx????xxxxx????xxx????xxxx?xxx????xxx");
		if (!addr) {
			MessageBox(0, L"Failed to find GetWeaponStats", L"Failure", 0);
			return FALSE;
		}

		GetWeaponStats = reinterpret_cast<decltype(GetWeaponStats)>(addr);

		// ProcessEvent
		addr = Util::FindPattern("\x40\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8D\x6C\x24\x00\x48\x89\x9D\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC5\x48\x89\x85\x00\x00\x00\x00\x8B\x41\x0C\x45\x33\xF6\x3B\x05\x00\x00\x00\x00\x4D\x8B\xF8\x48\x8B\xF2\x4C\x8B\xE1\x41\xB8\x00\x00\x00\x00\x7D\x2A", "xxxxxxxxxxxxxxx????xxxx?xxx????xxx????xxxxxx????xxxxxxxx????xxxxxxxxxxx????xx");
		if (!addr) {
			MessageBox(0, L"Failed to find ProcessEvent", L"Failure", 0);
			return FALSE;
		}

		DISCORD.HookFunction((uintptr_t)addr, (uintptr_t)ProcessEventHook, (uintptr_t)&ProcessEvent);

		// GetViewPoint
		addr = Util::FindPattern("\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xD9\x41\x8B\xF0\x48\x8B\x49\x30\x48\x8B\xFA\xE8\x00\x00\x00\x00\xBA\x00\x00\x00\x00\x48\x8B\xC8", "xxxx?xxxx?xxxxxxxxxxxxxxxxxxx????x????xxx");
		if (!addr) {
			MessageBox(0, L"Failed to find GetViewPoint", L"Failure", 0);
			return FALSE;
		}

		DISCORD.HookFunction((uintptr_t)addr, (uintptr_t)GetViewPointHook, (uintptr_t)&GetViewPoint);

		// CalculateSpread
		addr = Util::FindPattern("\x83\x79\x78\x00\x4C\x8B\xC9\x75\x0F\x0F\x57\xC0\xC7\x02\x00\x00\x00\x00\xF3\x41\x0F\x11\x00\xC3\x48\x8B\x41\x70\x8B\x48\x04\x89\x0A\x49\x63\x41\x78\x48\x6B\xC8\x1C\x49\x8B\x41\x70\xF3\x0F\x10\x44\x01\x00\xF3\x41\x0F\x11\x00\xC3", "xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx?xxxxxx");
		if (!addr) {
			MessageBox(0, L"Failed to find CalculateSpread", L"Failure", 0);
			return FALSE;
		}

		DISCORD.HookFunction((uintptr_t)addr, (uintptr_t)CalculateSpreadHook, (uintptr_t)&CalculateSpread);

		// CalculateSpreadCaller
		addr = Util::FindPattern("\x0F\x57\xD2\x48\x8D\x4C\x24\x00\x41\x0F\x28\xCD\xE8\x00\x00\x00\x00\x48\x8B\x4D\xB0\x0F\x28\xF0\x48\x85\xC9\x74\x05\xE8\x00\x00\x00\x00\x48\x8B\x4D\x98\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x44\x24\x00\x48\x85\xC9\x74\x05\xE8\x00\x00\x00\x00\x48\x8B\x4D\x88", "xxxxxxx?xxxxx????xxxxxxxxxxxxx????xxxxxxx????xxxx?xxxxxx????xxxx");
		if (!addr) {
			MessageBox(0, L"Failed to find CalculateSpreadCaller", L"Failure", 0);
			return FALSE;
		}
		calculateSpreadCaller = addr;

		//CalculateShot
		addr = Util::FindPattern("\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x4C\x89\x4C\x24\x20\x55\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\xD0", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		if (!addr) {
			MessageBox(0, L"Failed to find CalculateShot", L"Failure", 0);
			return FALSE;
		}
		DISCORD.HookFunction((uintptr_t)addr, (uintptr_t)CalculateShotHook, (uintptr_t)&CalculateShot);

		// Reload
		Util::FindPattern("\x40\x55\x53\x57\x41\x56\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x0F\x29\xBC\x24\x00\x00\x00\x00", "xxxxxxxxxx????xxx????xxxx????");
		if (!addr) {
			MessageBox(0, L"Failed to find Reload", L"Failure", 0);
			return FALSE;
		}
		DISCORD.HookFunction((uintptr_t)addr, (uintptr_t)ReloadHook, (uintptr_t)&ReloadOriginal);

		return TRUE;
	}
}