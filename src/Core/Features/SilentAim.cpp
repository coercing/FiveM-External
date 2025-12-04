#include "SilentAim.hpp"

bool Core::Features::cSilentAim::SilentAimInitialized;
std::uintptr_t Core::Features::cSilentAim::StartAddy;
static int lastHitbox = 0;

// Bone IDs for the proper bone system
#define SKEL_HEAD 0x796e    // Akey'den Hediye <3
#define SKEL_SPINE 0x60f2   // Akey Sevgilerle :)
#define SKEL_L_FOOT 0xcc    // Akey'den Selamlar
#define SKEL_R_FOOT 0x9000  // Akey Was Here!

void Core::Features::cSilentAim::InitializeSilentAim()
{
	StartAddy = g_Offsets.m_SilentAim;
	SilentAimHook = Mem.CreateCodeCave(500);

	if (!SilentAimHook)return;

	Mem.WriteBytes(SilentAimHook, SilentAimShell);

	OriginalFuncTable = Mem.ReadBytes(StartAddy, 38);

	Mem.HookJMP(StartAddy, SilentAimHook);
}

void Core::Features::cSilentAim::RestoreSilent()
{
	Mem.WriteBytes(StartAddy, OriginalFuncTable);
	Mem.FreeCave(SilentAimHook);
}

void Core::Features::cSilentAim::HookSilent()
{
	while (true)
	{
		if (g_Config.SilentAim->Enabled && g_Config.SilentAim->KeyBind != 0 && GetAsyncKeyState(g_Config.SilentAim->KeyBind) & 0x8000 && GetForegroundWindow() != g_Variables.g_hCheatWindow)
		{
			CPed* Ped = Core::SDK::Game::GetClosestPed(g_Config.SilentAim->MaxDistance, g_Config.SilentAim->IgnoreNPCs, g_Config.SilentAim->OnlyVisible);
			if (!Ped) { continue; }

			D3DXVECTOR3 TargetPos;
			int selectedBone = 0;

			// Get the skeleton data for proper bone positioning
			uintptr_t FragInstNMGta = Mem.Read<uintptr_t>((uintptr_t)Ped + g_Offsets.m_FragInst);
			uintptr_t v9 = Mem.Read<uintptr_t>(FragInstNMGta + 0x68);

			if (!v9)
				continue;

			Core::SDK::Game::cSkeleton_t Skeleton;
			Skeleton.m_pSkeleton = Mem.Read<uintptr_t>(v9 + 0x178);
			Skeleton.crSkeletonData.Ptr = Mem.Read<uintptr_t>(Skeleton.m_pSkeleton);
			Skeleton.crSkeletonData.m_Used = Mem.Read<unsigned int>(Skeleton.crSkeletonData.Ptr + 0x1A);
			Skeleton.crSkeletonData.m_NumBones = Mem.Read<unsigned int>(Skeleton.crSkeletonData.Ptr + 0x5E);
			Skeleton.crSkeletonData.m_BoneIdTable_Slots = Mem.Read<unsigned short>(Skeleton.crSkeletonData.Ptr + 0x18);

			if (!Skeleton.crSkeletonData.m_BoneIdTable_Slots)
				continue;

			Skeleton.crSkeletonData.m_BoneIdTable = Mem.Read<uintptr_t>(Skeleton.crSkeletonData.Ptr + 0x10);
			Skeleton.Arg1 = Mem.Read<D3DXMATRIX>(Mem.Read<uintptr_t>(Skeleton.m_pSkeleton + 0x8));
			Skeleton.Arg2 = Mem.Read<uintptr_t>(Skeleton.m_pSkeleton + 0x18);

			switch (g_Config.SilentAim->Hitbox) {
			case Core::Config::SilentAim::HEAD:
				TargetPos = Core::SDK::Game::GetBonePosComplex(Ped, SKEL_HEAD, Skeleton);
				lastHitbox = 0;
				break;
			case Core::Config::SilentAim::BODY:
				TargetPos = Core::SDK::Game::GetBonePosComplex(Ped, SKEL_SPINE, Skeleton);
				lastHitbox = 1;
				break;
			case Core::Config::SilentAim::LEG:
				TargetPos = Core::SDK::Game::GetBonePosComplex(Ped, (rand() % 2) ? SKEL_L_FOOT : SKEL_R_FOOT, Skeleton);
				lastHitbox = 2;
				break;
			case Core::Config::SilentAim::RANDOM:
			{
				int randomHitbox = rand() % 3;
				while (randomHitbox == lastHitbox) {
					randomHitbox = rand() % 3;
				}
				lastHitbox = randomHitbox;

				switch (randomHitbox) {
				case 0: TargetPos = Core::SDK::Game::GetBonePosComplex(Ped, SKEL_HEAD, Skeleton); break;
				case 1: TargetPos = Core::SDK::Game::GetBonePosComplex(Ped, SKEL_SPINE, Skeleton); break;
				case 2: TargetPos = Core::SDK::Game::GetBonePosComplex(Ped, (rand() % 2) ? SKEL_L_FOOT : SKEL_R_FOOT, Skeleton); break;
				}
				break;
			}
			default:
				TargetPos = Core::SDK::Game::GetBonePosComplex(Ped, SKEL_HEAD, Skeleton);
				lastHitbox = 0;
				break;
			}

			// Debug için bone pozisyonunu yazdıralım
			std::cout << "Akey'den Hediye Target: " << TargetPos.x << ", " << TargetPos.y << ", " << TargetPos.z << std::endl;

			D3DXVECTOR2 HeadToScreen = Core::SDK::Game::WorldToScreen(TargetPos);

			if (Core::SDK::Game::IsOnScreen(HeadToScreen)) {
				int Fov = std::hypot(HeadToScreen.x - g_Variables.g_vGameWindowCenter.x, HeadToScreen.y - g_Variables.g_vGameWindowCenter.y);
				if (Fov < g_Config.SilentAim->FOV) {

					if (!SilentAimInitialized) {
						InitializeSilentAim();
						SilentAimInitialized = true;
					}

					bool Miss = g_Config.SilentAim->MissChance >= Utils::GenRandomInt(0, 100);
					D3DXVECTOR3 HitOffset;

					if (Miss) {
						HitOffset = D3DXVECTOR3(0.0, 0.4, 0);
					}
					else {
						switch (lastHitbox) {
						case 0: // HEAD
							HitOffset = D3DXVECTOR3(0, 0, 0.08);
							break;
						case 1: // BODY
							HitOffset = D3DXVECTOR3(0, 0, 0);
							break;
						case 2: // LEG
							HitOffset = D3DXVECTOR3(0, 0, -0.1);
							break;
						default:
							HitOffset = D3DXVECTOR3(0, 0, 0.08);
							break;
						}
					}

					auto FinalPos = TargetPos + HitOffset;

					memcpy(SilentAimShell.data() + 3, &FinalPos.x, sizeof(float));
					memcpy(SilentAimShell.data() + 10, &FinalPos.y, sizeof(float));
					memcpy(SilentAimShell.data() + 17, &FinalPos.z, sizeof(float));

					uintptr_t BackAddress = (uintptr_t)(StartAddy + 0x26);
					memcpy(SilentAimShell.data() + 27, &BackAddress, sizeof(BackAddress));

					Mem.WriteBytes(SilentAimHook, SilentAimShell);

				}
				else {
					if (SilentAimInitialized) {
						RestoreSilent();
						SilentAimInitialized = false;
					}
				}
			}
			else {
				if (SilentAimInitialized) {
					RestoreSilent();
					SilentAimInitialized = false;
				}
			}

		}
		else {
			if (SilentAimInitialized) {
				RestoreSilent();
				SilentAimInitialized = false;
			}
		}

		std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	}
}