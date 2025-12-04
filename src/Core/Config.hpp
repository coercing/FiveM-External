#pragma once
#include <Includes/Includes.hpp>
#include <Includes/Utils.hpp>
#include <iostream>
#include <Security/LazyImporter.hpp>

static std::string CitizenFX;

namespace Core {

	class Config {
	public:

		struct General {
		public:
			inline static bool StreamProof = false;
			inline static bool WaterMark;
			inline static bool WaterMarkCol;
			inline static bool ArrayList;
			inline static bool ArrayListCol;
			inline static bool VSync = true;
			inline static int ProcessPriority = 0;
			inline static int MenuKey = VK_INSERT;
		} *General;

		struct Aimbot {
			enum HitboxType {
				HEAD = 0,
				BODY = 1,
				LEG = 2,
				RANDOM = 3
			};
		public:
			inline static bool Enabled;
			inline static bool ShowFov;
			inline static bool OnlyVisible;
			inline static bool IgnoreNPCs;
			inline static int HitBox = 0;
			inline static int FOV = 180;
			inline static int MaxDistance = 240;
			inline static int SmoothHorizontal = 12;
			inline static int SmoothVertical = 12;
			inline static int AimbotSpeed = 12;
			inline static int KeyBind;
			inline static int Hitbox = HEAD;
			inline static ImColor FovColor{ 255, 255, 255 };
		} *Aimbot;

		struct TriggerBot {
		public:
			inline static bool Enabled;
			inline static bool ShowFov;
			inline static bool OnlyVisible;
			inline static bool IgnoreNPCs;
			inline static bool SmartTrigger;
			inline static int FOV = 20;
			inline static int MaxDistance = 200;
			inline static int Delay = 0;
			inline static int KeyBind;
			inline static ImColor FovColor { 255, 255, 255 };
		} *TriggerBot;

		struct SilentAim {
		public:
			enum HitboxType {
				HEAD = 0,
				BODY = 1,
				LEG = 2,
				RANDOM = 3
			};

		public:
			inline static bool Enabled;
			inline static bool ShowFov;
			inline static bool OnlyVisible;
			inline static bool MagicBullets;
			inline static bool IgnoreNPCs;
			inline static int FOV = 40;
			inline static int MissChance = 0;
			inline static int MaxDistance = 200;
			inline static int KeyBind;
			inline static int Hitbox = HEAD;
			inline static ImColor FovColor{ 224, 94, 103, 200 };
		} *SilentAim;

		struct ESP {
		public:
			inline static bool UpdateCfgESP;
			inline static bool Enabled;
			inline static bool Box;
			inline static bool FilledBox;
			inline static int BoxState = 0;
			inline static bool Skeleton;
			inline static bool HealthBar;
			inline static ImVec2 HealthBarPos;
			inline static int HealthBarState = 0;
			inline static bool ArmorBar;
			inline static ImVec2 ArmorBarPos;
			inline static int ArmorBarState = 0;
			inline static bool WeaponName;
			inline static ImVec2 WeaponNamePos;
			inline static int WeaponNameState = 0;
			inline static bool SnapLines;
			inline static bool UserNames;
			inline static ImVec2 UserNamesPos;
			inline static int UserNamesState = 0;
			inline static bool HeadCircle;
			inline static bool IgnoreNPCs;
			inline static bool ShowLocalPlayer;
			inline static bool HighlightVisible;
			inline static bool IgnoreDead;
			inline static bool DistanceFromMe;
			inline static bool FriendsMarker;
			inline static int FriendsMarkerBind;
			inline static ImVec2 DistanceFromMePos;
			inline static int DistanceFromMeState = 0;
			inline static int MaxDistance = 200;
			inline static ImColor DistanceCol { 230, 230, 230, 255 };
			inline static ImColor UserNamesCol { 230, 230, 230, 255 };
			inline static ImColor WeaponNameCol { 230, 230, 230, 255 };
			inline static ImColor SkeletonCol { 255, 255, 255, 200 };
			inline static ImColor BoxCol { 255, 255, 255, 200 };
			inline static ImColor FilledBoxCol { 0, 0, 0, 40 };
			inline static ImColor SnapLinesCol { 255, 255, 255, 200 };
			inline static ImColor FriendCol { 255, 204, 0, 255 };
			inline static int KeyBind;
		} *ESP;

		struct VehicleESP {
		public:
			inline static bool Enabled;
			inline static bool SnapLines;
			inline static bool ShowLockUnlock;
			inline static bool VehName;
			inline static bool DistanceFromMe;
			inline static int MaxDistance = 200;
			inline static ImColor SnapLinesCol { 255, 255, 255, 200 };
		} *VehicleESP;

		struct Player {
		public:
			inline static float CurrentHealthValue;
			inline static float CurrentArmorValue;
			inline static bool FastRun;
			inline static float RunSpeed = 1.f;
			inline static bool InfiniteStamina;
			inline static bool WeaponOptions;
			inline static bool NoRecoilEnabled;
			inline static float RecoilValue;
			inline static bool NoSpreadEnabled;
			inline static float SpreadValue;
			inline static bool InfiniteAmmoEnabled;
			inline static bool NoReloadEnabled;
			inline static bool NoClipEnabled;
			inline static bool HandlingEditor;
			inline static int NoClipKey;
			inline static float NoClipSpeed = 2.0f;
			inline static bool InfiniteCombatRoll;
			inline static bool EnableGodMode;
			inline static bool VehicleGodMode;
			inline static bool SeatBelt;
			inline static bool ForceWeaponWheel;
			inline static bool ShrinkEnabled;
			inline static bool NoRagDollEnabled;
			inline static bool AntiHSEnabled;
			inline static bool KillAllPlayers;

			inline static bool StealCarEnabled;

			inline static bool FreeCam;
			inline static float FreeCamSpeed = 1.f;
			inline static int FreeCamKey;

			inline static int GodModeKey;

			inline static bool ExplosiveAmmoEnabled;
			inline static bool FireAmmoEnabled;
			inline static bool DamageBoost;
			inline static float Boost = 1.f;

			inline static bool BeastJumpEnabled;
			inline static bool SuperJumpEnabled;
			inline static bool SuperFistEnabled;
			inline static bool ExplosiveFistEnabled;
		} *Player;


		nlohmann::json ImColToJson( const ImColor & Col ) {
			return nlohmann::json::array( { Col.Value.x, Col.Value.y, Col.Value.z, Col.Value.w } );
		}

		ImColor JsonToImCol( const nlohmann::json & JsonCol ) {
			if ( JsonCol.is_array( ) && JsonCol.size( ) == 4 ) {
				float r = JsonCol[ 0 ];
				float g = JsonCol[ 1 ];
				float b = JsonCol[ 2 ];
				float a = JsonCol[ 3 ];
				return ImColor( r, g, b, a );
			}
			else {
				return ImColor( 0.0f, 0.0f, 0.0f, 1.0f );
			}
		}

		static std::vector<std::string> GetConfigs() {
			static bool created_cfg = true;
			std::vector<std::string> configs;

			if (created_cfg) {
				char path[MAX_PATH];
				if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path))) {
					CitizenFX = std::string(path) + "\\discord\\";
					CreateDirectoryA(CitizenFX.c_str(), nullptr);
				}
				created_cfg = false;
			}

			// Lógica para carregar arquivos de configuração
			for (const auto& entry : std::filesystem::directory_iterator(CitizenFX)) {
				if (entry.is_regular_file() && entry.path().extension() == ".cfg") {
					configs.push_back(entry.path().filename().string());  // Adiciona o nome do arquivo .cfg
				}
			}

			return configs;
		}

		void OpenConfigFolder() {
			namespace fs = std::experimental::filesystem;

			std::wstring str = std::wstring(CitizenFX.begin(), CitizenFX.end());

			PIDLIST_ABSOLUTE pidl;
			if (SUCCEEDED(SHParseDisplayName(str.c_str(), 0, &pidl, 0, 0))) {
				// we don't want to actually select anything in the folder, so we pass an empty
				// PIDL in the array. if you want to select one or more items in the opened
				// folder you'd need to build the PIDL array appropriately
				ITEMIDLIST idNull = { 0 };
				LPCITEMIDLIST pidlNull[1] = { &idNull };
				LI_FN(SHOpenFolderAndSelectItems)(pidl, 1, pidlNull, 0);

				// LIFEEEEHAAAACK BITCH!!! (◣_◢)

			}
		}

		void CreateConfig(const std::string& configname) {
			if (configname.empty()) return;

			std::string fullPath = CitizenFX + configname + ".cfg";

			// Verifica se já existe
			std::ifstream test_file(fullPath);
			if (test_file.good()) {
				test_file.close();
				return;
			}
			test_file.close();

			// Garante que o diretório existe
			std::filesystem::path pathObj(fullPath);
			std::filesystem::create_directories(pathObj.parent_path());

			// Salva as configurações atuais no novo arquivo
			SaveCurrentConfigToFile(configname);
		}

		void ResetConfig() {
			//for ( auto &child : g_Vars.m_children ) {
			//	child->Load( g_Vars.m_json_default_cfg [ std::to_string( child->GetName( ) ) ] );
			//}
		}

		void SaveCurrentConfigToFile(const std::string& name) {
			try {
				std::string cleanName = name;
				// Remove .cfg se já estiver no nome
				if (cleanName.size() > 4 &&
					cleanName.substr(cleanName.size() - 4) == ".cfg") {
					cleanName = cleanName.substr(0, cleanName.size() - 4);
				}

				std::string fullPath = CitizenFX + cleanName + ".cfg";

				nlohmann::json CfgJson;

				auto& GeneralCfg = CfgJson["General"];
				auto& FeaturesCfg = CfgJson["Features"];

				// General
				GeneralCfg["StreamProof"] = Config::General->StreamProof;
				GeneralCfg["WaterMark"] = Config::General->WaterMark;
				GeneralCfg["ArrayList"] = Config::General->ArrayList;
				GeneralCfg["VSync"] = Config::General->VSync;
				GeneralCfg["ProcessPriority"] = Config::General->ProcessPriority;
				GeneralCfg["MenuKey"] = Config::General->MenuKey;

				// Features - Aimbot
				FeaturesCfg["Aimbot"]["Enabled"] = Config::Aimbot->Enabled;
				FeaturesCfg["Aimbot"]["ShowFov"] = Config::Aimbot->ShowFov;
				FeaturesCfg["Aimbot"]["OnlyVisible"] = Config::Aimbot->OnlyVisible;
				FeaturesCfg["Aimbot"]["IgnoreNPCs"] = Config::Aimbot->IgnoreNPCs;
				FeaturesCfg["Aimbot"]["HitBox"] = Config::Aimbot->HitBox;
				FeaturesCfg["Aimbot"]["FOV"] = Config::Aimbot->FOV;
				FeaturesCfg["Aimbot"]["MaxDistance"] = Config::Aimbot->MaxDistance;
				FeaturesCfg["Aimbot"]["AimbotSpeed"] = Config::Aimbot->AimbotSpeed;
				FeaturesCfg["Aimbot"]["KeyBind"] = Config::Aimbot->KeyBind;
				FeaturesCfg["Aimbot"]["FovColor"] = ImColToJson(Config::Aimbot->FovColor);

				// Features - TriggerBot
				FeaturesCfg["TriggerBot"]["Enabled"] = Config::TriggerBot->Enabled;
				FeaturesCfg["TriggerBot"]["ShowFov"] = Config::TriggerBot->ShowFov;
				FeaturesCfg["TriggerBot"]["OnlyVisible"] = Config::TriggerBot->OnlyVisible;
				FeaturesCfg["TriggerBot"]["IgnoreNPCs"] = Config::TriggerBot->IgnoreNPCs;
				FeaturesCfg["TriggerBot"]["FOV"] = Config::TriggerBot->FOV;
				FeaturesCfg["TriggerBot"]["MaxDistance"] = Config::TriggerBot->MaxDistance;
				FeaturesCfg["TriggerBot"]["Delay"] = Config::TriggerBot->Delay;
				FeaturesCfg["TriggerBot"]["KeyBind"] = Config::TriggerBot->KeyBind;
				FeaturesCfg["TriggerBot"]["FovColor"] = ImColToJson(Config::TriggerBot->FovColor);

				// Features - SilentAim
				FeaturesCfg["SilentAim"]["Enabled"] = Config::SilentAim->Enabled;
				FeaturesCfg["SilentAim"]["ShowFov"] = Config::SilentAim->ShowFov;
				FeaturesCfg["SilentAim"]["OnlyVisible"] = Config::SilentAim->OnlyVisible;
				FeaturesCfg["SilentAim"]["MagicBullets"] = Config::SilentAim->MagicBullets;
				FeaturesCfg["SilentAim"]["IgnoreNPCs"] = Config::SilentAim->IgnoreNPCs;
				FeaturesCfg["SilentAim"]["FOV"] = Config::SilentAim->FOV;
				FeaturesCfg["SilentAim"]["MissChance"] = Config::SilentAim->MissChance;
				FeaturesCfg["SilentAim"]["MaxDistance"] = Config::SilentAim->MaxDistance;
				FeaturesCfg["SilentAim"]["KeyBind"] = Config::SilentAim->KeyBind;
				FeaturesCfg["SilentAim"]["HitBox"] = Config::SilentAim->Hitbox;
				FeaturesCfg["SilentAim"]["FovColor"] = ImColToJson(Config::SilentAim->FovColor);

				// Features - ESP
				FeaturesCfg["ESP"]["Enabled"] = Config::ESP->Enabled;
				FeaturesCfg["ESP"]["Box"] = Config::ESP->Box;
				FeaturesCfg["ESP"]["FilledBox"] = Config::ESP->FilledBox;
				FeaturesCfg["ESP"]["BoxState"] = Config::ESP->BoxState;
				FeaturesCfg["ESP"]["Skeleton"] = Config::ESP->Skeleton;
				FeaturesCfg["ESP"]["HealthBar"] = Config::ESP->HealthBar;
				FeaturesCfg["ESP"]["HealthBarState"] = Config::ESP->HealthBarState;
				FeaturesCfg["ESP"]["ArmorBar"] = Config::ESP->ArmorBar;
				FeaturesCfg["ESP"]["ArmorBarState"] = Config::ESP->ArmorBarState;
				FeaturesCfg["ESP"]["WeaponName"] = Config::ESP->WeaponName;
				FeaturesCfg["ESP"]["WeaponNameState"] = Config::ESP->WeaponNameState;
				FeaturesCfg["ESP"]["SnapLines"] = Config::ESP->SnapLines;
				FeaturesCfg["ESP"]["UserNames"] = Config::ESP->UserNames;
				FeaturesCfg["ESP"]["UserNamesState"] = Config::ESP->UserNamesState;
				FeaturesCfg["ESP"]["HeadCircle"] = Config::ESP->HeadCircle;
				FeaturesCfg["ESP"]["IgnoreNPCs"] = Config::ESP->IgnoreNPCs;
				FeaturesCfg["ESP"]["ShowLocalPlayer"] = Config::ESP->ShowLocalPlayer;
				FeaturesCfg["ESP"]["HighlightVisible"] = Config::ESP->HighlightVisible;
				FeaturesCfg["ESP"]["IgnoreDead"] = Config::ESP->IgnoreDead;
				FeaturesCfg["ESP"]["DistanceFromMe"] = Config::ESP->DistanceFromMe;
				FeaturesCfg["ESP"]["DistanceFromMeState"] = Config::ESP->DistanceFromMeState;
				FeaturesCfg["ESP"]["MaxDistance"] = Config::ESP->MaxDistance;
				FeaturesCfg["ESP"]["FriendsMarker"] = Config::ESP->FriendsMarker;
				FeaturesCfg["ESP"]["FriendsMarkerBind"] = Config::ESP->FriendsMarkerBind;
				FeaturesCfg["ESP"]["DistanceCol"] = ImColToJson(Config::ESP->DistanceCol);
				FeaturesCfg["ESP"]["UserNamesCol"] = ImColToJson(Config::ESP->UserNamesCol);
				FeaturesCfg["ESP"]["WeaponNameCol"] = ImColToJson(Config::ESP->WeaponNameCol);
				FeaturesCfg["ESP"]["SkeletonCol"] = ImColToJson(Config::ESP->SkeletonCol);
				FeaturesCfg["ESP"]["BoxCol"] = ImColToJson(Config::ESP->BoxCol);
				FeaturesCfg["ESP"]["SnapLinesCol"] = ImColToJson(Config::ESP->SnapLinesCol);
				FeaturesCfg["ESP"]["FriendCol"] = ImColToJson(Config::ESP->FriendCol);

				// Features - VehicleESP
				FeaturesCfg["VehicleESP"]["Enabled"] = Config::VehicleESP->Enabled;
				FeaturesCfg["VehicleESP"]["SnapLines"] = Config::VehicleESP->SnapLines;
				FeaturesCfg["VehicleESP"]["ShowLockUnlock"] = Config::VehicleESP->ShowLockUnlock;
				FeaturesCfg["VehicleESP"]["VehName"] = Config::VehicleESP->VehName;
				FeaturesCfg["VehicleESP"]["DistanceFromMe"] = Config::VehicleESP->DistanceFromMe;
				FeaturesCfg["VehicleESP"]["MaxDistance"] = Config::VehicleESP->MaxDistance;
				FeaturesCfg["VehicleESP"]["SnapLinesCol"] = ImColToJson(Config::VehicleESP->SnapLinesCol);

				// Features - Player
				FeaturesCfg["Player"]["NoClipKey"] = Config::Player->NoClipKey;
				FeaturesCfg["Player"]["NoClipSpeed"] = Config::Player->NoClipSpeed;
				FeaturesCfg["Player"]["GodModeKey"] = Config::Player->GodModeKey;

				std::string jsonStr = CfgJson.dump();
				std::string encoded = Utils::EncodeB64(jsonStr);

				std::ofstream out(fullPath);
				if (!out.is_open())
					throw std::runtime_error("Erro ao abrir o arquivo para escrita.");

				out << "[vpx] - " << encoded;
				out.close();

				std::cout << "Config salva com sucesso: " << cleanName << std::endl;
			}
			catch (const std::exception& e) {
				std::cerr << "Erro ao salvar config: " << e.what() << std::endl;
			}
		}

		void LoadConfigFromFile(const std::string& name) {
			try {
				// Adiciona .cfg se não tiver
				std::string fullPath = CitizenFX + name;
				if (fullPath.size() <= 4 ||
					fullPath.substr(fullPath.size() - 4) != ".cfg") {
					fullPath += ".cfg";
				}

				std::ifstream in(fullPath);  // Abre o arquivo aqui
				if (!in.is_open())
					throw std::runtime_error("Arquivo não encontrado.");

				std::string encodedLine;
				std::getline(in, encodedLine);
				in.close();

				if (encodedLine.find("[vpx] - ") != std::string::npos)
					encodedLine = encodedLine.substr(8);

				std::string jsonStr = Utils::DecodeB64(encodedLine);
				nlohmann::json CfgJson = nlohmann::json::parse(jsonStr);

				// General
				auto& GeneralCfg = CfgJson["General"];
				Config::General->StreamProof = GeneralCfg["StreamProof"];
				Config::General->WaterMark = GeneralCfg["WaterMark"];
				Config::General->ArrayList = GeneralCfg["ArrayList"];
				Config::General->VSync = GeneralCfg["VSync"];
				Config::General->ProcessPriority = GeneralCfg["ProcessPriority"];
				Config::General->MenuKey = GeneralCfg["MenuKey"];

				// Aimbot
				auto& AimbotCfg = CfgJson["Features"]["Aimbot"];
				Config::Aimbot->Enabled = AimbotCfg["Enabled"];
				Config::Aimbot->ShowFov = AimbotCfg["ShowFov"];
				Config::Aimbot->OnlyVisible = AimbotCfg["OnlyVisible"];
				Config::Aimbot->IgnoreNPCs = AimbotCfg["IgnoreNPCs"];
				Config::Aimbot->HitBox = AimbotCfg["HitBox"];
				Config::Aimbot->FOV = AimbotCfg["FOV"];
				Config::Aimbot->MaxDistance = AimbotCfg["MaxDistance"];
				Config::Aimbot->AimbotSpeed = AimbotCfg["AimbotSpeed"];
				Config::Aimbot->KeyBind = AimbotCfg["KeyBind"];
				Config::Aimbot->FovColor = JsonToImCol(AimbotCfg["FovColor"]);

				// TriggerBot
				auto& TriggerCfg = CfgJson["Features"]["TriggerBot"];
				Config::TriggerBot->Enabled = TriggerCfg["Enabled"];
				Config::TriggerBot->ShowFov = TriggerCfg["ShowFov"];
				Config::TriggerBot->OnlyVisible = TriggerCfg["OnlyVisible"];
				Config::TriggerBot->IgnoreNPCs = TriggerCfg["IgnoreNPCs"];
				Config::TriggerBot->FOV = TriggerCfg["FOV"];
				Config::TriggerBot->MaxDistance = TriggerCfg["MaxDistance"];
				Config::TriggerBot->Delay = TriggerCfg["Delay"];
				Config::TriggerBot->KeyBind = TriggerCfg["KeyBind"];
				Config::TriggerBot->FovColor = JsonToImCol(TriggerCfg["FovColor"]);

				// SilentAim
				auto& SilentCfg = CfgJson["Features"]["SilentAim"];
				Config::SilentAim->Enabled = SilentCfg["Enabled"];
				Config::SilentAim->ShowFov = SilentCfg["ShowFov"];
				Config::SilentAim->OnlyVisible = SilentCfg["OnlyVisible"];
				Config::SilentAim->MagicBullets = SilentCfg["MagicBullets"];
				Config::SilentAim->IgnoreNPCs = SilentCfg["IgnoreNPCs"];
				Config::SilentAim->FOV = SilentCfg["FOV"];
				Config::SilentAim->MissChance = SilentCfg["MissChance"];
				Config::SilentAim->MaxDistance = SilentCfg["MaxDistance"];
				Config::SilentAim->KeyBind = SilentCfg["KeyBind"];
				Config::SilentAim->Hitbox = SilentCfg["HitBox"];
				Config::SilentAim->FovColor = JsonToImCol(SilentCfg["FovColor"]);

				// ESP
				auto& ESPCfg = CfgJson["Features"]["ESP"];
				Config::ESP->Enabled = ESPCfg["Enabled"];
				Config::ESP->Box = ESPCfg["Box"];
				Config::ESP->FilledBox = ESPCfg["FilledBox"];
				Config::ESP->BoxState = ESPCfg["BoxState"];
				Config::ESP->Skeleton = ESPCfg["Skeleton"];
				Config::ESP->HealthBar = ESPCfg["HealthBar"];
				Config::ESP->HealthBarState = ESPCfg["HealthBarState"];
				Config::ESP->ArmorBar = ESPCfg["ArmorBar"];
				Config::ESP->ArmorBarState = ESPCfg["ArmorBarState"];
				Config::ESP->WeaponName = ESPCfg["WeaponName"];
				Config::ESP->WeaponNameState = ESPCfg["WeaponNameState"];
				Config::ESP->SnapLines = ESPCfg["SnapLines"];
				Config::ESP->UserNames = ESPCfg["UserNames"];
				Config::ESP->UserNamesState = ESPCfg["UserNamesState"];
				Config::ESP->HeadCircle = ESPCfg["HeadCircle"];
				Config::ESP->IgnoreNPCs = ESPCfg["IgnoreNPCs"];
				Config::ESP->ShowLocalPlayer = ESPCfg["ShowLocalPlayer"];
				Config::ESP->HighlightVisible = ESPCfg["HighlightVisible"];
				Config::ESP->IgnoreDead = ESPCfg["IgnoreDead"];
				Config::ESP->DistanceFromMe = ESPCfg["DistanceFromMe"];
				Config::ESP->DistanceFromMeState = ESPCfg["DistanceFromMeState"];
				Config::ESP->MaxDistance = ESPCfg["MaxDistance"];
				Config::ESP->FriendsMarker = ESPCfg["FriendsMarker"];
				Config::ESP->FriendsMarkerBind = ESPCfg["FriendsMarkerBind"];
				Config::ESP->DistanceCol = JsonToImCol(ESPCfg["DistanceCol"]);
				Config::ESP->UserNamesCol = JsonToImCol(ESPCfg["UserNamesCol"]);
				Config::ESP->WeaponNameCol = JsonToImCol(ESPCfg["WeaponNameCol"]);
				Config::ESP->SkeletonCol = JsonToImCol(ESPCfg["SkeletonCol"]);
				Config::ESP->BoxCol = JsonToImCol(ESPCfg["BoxCol"]);
				Config::ESP->SnapLinesCol = JsonToImCol(ESPCfg["SnapLinesCol"]);
				Config::ESP->FriendCol = JsonToImCol(ESPCfg["FriendCol"]);

				// VehicleESP
				auto& VehCfg = CfgJson["Features"]["VehicleESP"];
				Config::VehicleESP->Enabled = VehCfg["Enabled"];
				Config::VehicleESP->SnapLines = VehCfg["SnapLines"];
				Config::VehicleESP->ShowLockUnlock = VehCfg["ShowLockUnlock"];
				Config::VehicleESP->VehName = VehCfg["VehName"];
				Config::VehicleESP->DistanceFromMe = VehCfg["DistanceFromMe"];
				Config::VehicleESP->MaxDistance = VehCfg["MaxDistance"];
				Config::VehicleESP->SnapLinesCol = JsonToImCol(VehCfg["SnapLinesCol"]);

				// Player
				auto& PlayerCfg = CfgJson["Features"]["Player"];
				Config::Player->NoClipKey = PlayerCfg["NoClipKey"];
				Config::Player->NoClipSpeed = PlayerCfg["NoClipSpeed"];
				Config::Player->GodModeKey = PlayerCfg["GodModeKey"];

				std::cout << "Config carregada com sucesso!" << std::endl;
			}
			catch (const std::exception& e) {
				std::cerr << "Erro ao carregar o arquivo de configuração: " << e.what() << std::endl;
			}
			catch (...) {
				std::cerr << "Erro desconhecido ao carregar a configuração!" << std::endl;
			}
		}





		std::string SaveCurrentConfig( std::string CfgName )
		{
			try {
				nlohmann::json CfgJson;
				auto& GeneralCfg = CfgJson[ xorstr( "General" ) ];
				auto& FeaturesCfg = CfgJson;

				//General
				GeneralCfg[ xorstr( "StreamProof" ) ] = General->StreamProof;
				GeneralCfg[ xorstr( "WaterMark" ) ] = General->WaterMark;
				GeneralCfg[ xorstr( "ArrayList" ) ] = General->ArrayList;
				GeneralCfg[ xorstr( "VSync" ) ] = General->VSync;
				GeneralCfg[ xorstr( "ProcessPriority" ) ] = General->ProcessPriority;
				GeneralCfg[ xorstr( "MenuKey" ) ] = General->MenuKey;

				// Features - Aimbot
				FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "Enabled" ) ] = Aimbot->Enabled;
				FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "ShowFov" ) ] = Aimbot->ShowFov;
				FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "OnlyVisible" ) ] = Aimbot->OnlyVisible;
				FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "IgnoreNPCs" ) ] = Aimbot->IgnoreNPCs;
				FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "FOV" ) ] = Aimbot->FOV;
				FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "MaxDistance" ) ] = Aimbot->MaxDistance;
				//FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "SmoothHorizontal" ) ] = Aimbot->SmoothHorizontal;
				//FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "SmoothVertical" ) ] = Aimbot->SmoothHorizontal;
				FeaturesCfg[xorstr("Aimbot")][xorstr("AimSpeed")] = Aimbot->AimbotSpeed;
				FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "KeyBind" ) ] = Aimbot->KeyBind;
				FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "FovColor" ) ] = ImColToJson( Aimbot->KeyBind );

				// Features - TriggerBot
				FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "Enabled" ) ] = TriggerBot->Enabled;
				FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "ShowFov" ) ] = TriggerBot->ShowFov;
				FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "OnlyVisible" ) ] = TriggerBot->OnlyVisible;
				FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "IgnoreNPCs" ) ] = TriggerBot->IgnoreNPCs;
				FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "FOV" ) ] = TriggerBot->FOV;
				FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "MaxDistance" ) ] = TriggerBot->MaxDistance;
				FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "Delay" ) ] = TriggerBot->Delay;
				FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "KeyBind" ) ] = TriggerBot->KeyBind;
				FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "FovColor" ) ] = ImColToJson( TriggerBot->KeyBind );

				// Features - SilentAim
				FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "Enabled" ) ] = SilentAim->Enabled;
				FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "ShowFov" ) ] = SilentAim->ShowFov;
				FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "OnlyVisible" ) ] = SilentAim->OnlyVisible;
				FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "IgnoreNPCs" ) ] = SilentAim->IgnoreNPCs;
				FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "FOV" ) ] = SilentAim->FOV;
				FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "MaxDistance" ) ] = SilentAim->MaxDistance;
				FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "KeyBind" ) ] = SilentAim->KeyBind;
				FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "MissChance" ) ] = SilentAim->MissChance;
				FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "MagicBullets" ) ] = SilentAim->MagicBullets;
				FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "FovColor" ) ] = ImColToJson( SilentAim->KeyBind );

				// Features - ESP
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Enabled" ) ] = ESP->Enabled;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Box" ) ] = ESP->Box;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "BoxState" ) ] = ESP->BoxState;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Skeleton" ) ] = ESP->Skeleton;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HealthBar" ) ] = ESP->HealthBar;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HealthBarState" ) ] = ESP->HealthBarState;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ArmorBar" ) ] = ESP->ArmorBar;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ArmorBarState" ) ] = ESP->ArmorBarState;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponName" ) ] = ESP->WeaponName;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponNameState" ) ] = ESP->WeaponNameState;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SnapLines" ) ] = ESP->SnapLines;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNames" ) ] = ESP->UserNames;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNamesState" ) ] = ESP->UserNamesState;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HeadCircle" ) ] = ESP->HeadCircle;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "IgnoreNPCs" ) ] = ESP->IgnoreNPCs;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HighlightVisible" ) ] = ESP->HighlightVisible;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "IgnoreDead" ) ] = ESP->IgnoreDead;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceFromMe" ) ] = ESP->DistanceFromMe;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceFromMeState" ) ] = ESP->DistanceFromMeState;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "MaxDistance" ) ] = ESP->MaxDistance;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ShowLocalPlayer" ) ] = ESP->ShowLocalPlayer;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "FriendsMarker" ) ] = ESP->FriendsMarker;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "FriendsMarkerBind" ) ] = ESP->FriendsMarkerBind;
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceCol" ) ] = ImColToJson( ESP->DistanceCol );
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNamesCol" ) ] = ImColToJson( ESP->UserNamesCol );
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponNameCol" ) ] = ImColToJson( ESP->WeaponNameCol );
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SkeletonCol" ) ] = ImColToJson( ESP->SkeletonCol );
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "BoxCol" ) ] = ImColToJson( ESP->BoxCol );
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SnapLinesCol" ) ] = ImColToJson( ESP->SnapLinesCol );
				FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "FriendCol" ) ] = ImColToJson( ESP->FriendCol );

				// Features - VehicleESP
				FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "Enabled" ) ] = VehicleESP->Enabled;
				FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "SnapLines" ) ] = VehicleESP->SnapLines;
				FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "ShowLockUnlock" ) ] = VehicleESP->ShowLockUnlock;
				FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "VehName" ) ] = VehicleESP->VehName;
				FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "DistanceFromMe" ) ] = VehicleESP->DistanceFromMe;
				FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "MaxDistance" ) ] = VehicleESP->MaxDistance;
				FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "SnapLinesCol" ) ] = ImColToJson( VehicleESP->SnapLinesCol );

				// Features - Player
				FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoClipKey" ) ] = Player->NoClipKey;
				FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoClipSpeed" ) ] = Player->NoClipSpeed;
				FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "GodModeKey" ) ] = Player->GodModeKey;

				std::string CfgJsonStr = CfgJson.dump( );

				Utils::PasteClipboard( Utils::EncodeB64( Utils::Str2Hex( Utils::EncodeB64( CfgJsonStr ) ) ).c_str( ) );

				return xorstr( "Config Exported to Clipboard." );
			}
			catch ( const std::exception & e ) {
				return xorstr( "Failed to save config." );
			}
		}

		std::string LoadCfg( std::string CfgName, std::string CfgCode )
		{
			try {
				std::string DecCfgCodeStr = Utils::DecodeB64( Utils::Hex2Str( Utils::DecodeB64( CfgCode ) ) );
				nlohmann::json CfgJson = nlohmann::json( ).parse( DecCfgCodeStr );

	
				auto& GeneralCfg = CfgJson[ xorstr( "General" ) ];
				auto& FeaturesCfg = CfgJson;

				// General
				if ( GeneralCfg != NULL )
				{
					General->StreamProof = GeneralCfg[ xorstr( "StreamProof" ) ];
					General->WaterMark = GeneralCfg[ xorstr( "WaterMark" ) ];
					General->ArrayList = GeneralCfg[ xorstr( "ArrayList" ) ];
					General->VSync = GeneralCfg[ xorstr( "VSync" ) ];
					General->ProcessPriority = GeneralCfg[ xorstr( "ProcessPriority" ) ];
					General->MenuKey = GeneralCfg[ xorstr( "MenuKey" ) ];
				}

				// Features - Aimbot
				Aimbot->Enabled = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "Enabled" ) ];
				Aimbot->ShowFov = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "ShowFov" ) ];
				Aimbot->OnlyVisible = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "OnlyVisible" ) ];
				Aimbot->IgnoreNPCs = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "IgnoreNPCs" ) ];
				Aimbot->FOV = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "FOV" ) ];
				Aimbot->MaxDistance = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "MaxDistance" ) ];
				//Aimbot->SmoothHorizontal = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "SmoothHorizontal" ) ];
				//Aimbot->SmoothVertical = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "SmoothVertical" ) ];
				Aimbot->AimbotSpeed = FeaturesCfg[xorstr("Aimbot")][xorstr("AimSpeed")];
				Aimbot->KeyBind = FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "KeyBind" ) ];
				Aimbot->FovColor = JsonToImCol( FeaturesCfg[ xorstr( "Aimbot" ) ][ xorstr( "FovColor" ) ] );

				// Features - TriggerBot
				TriggerBot->Enabled = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "Enabled" ) ];
				TriggerBot->ShowFov = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "ShowFov" ) ];
				TriggerBot->OnlyVisible = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "OnlyVisible" ) ];
				TriggerBot->IgnoreNPCs = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "IgnoreNPCs" ) ];
				TriggerBot->FOV = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "FOV" ) ];
				TriggerBot->MaxDistance = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "MaxDistance" ) ];
				TriggerBot->Delay = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "Delay" ) ];
				TriggerBot->KeyBind = FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "KeyBind" ) ];
				TriggerBot->FovColor = JsonToImCol( FeaturesCfg[ xorstr( "TriggerBot" ) ][ xorstr( "FovColor" ) ] );

				// Features - SilentAim
				SilentAim->Enabled = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "Enabled" ) ];
				SilentAim->ShowFov = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "ShowFov" ) ];
				SilentAim->OnlyVisible = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "OnlyVisible" ) ];
				SilentAim->IgnoreNPCs = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "IgnoreNPCs" ) ];
				SilentAim->FOV = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "FOV" ) ];
				SilentAim->MaxDistance = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "MaxDistance" ) ];
				SilentAim->KeyBind = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "KeyBind" ) ];
				SilentAim->MagicBullets = FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "MagicBullets" ) ];
				SilentAim->FovColor = JsonToImCol( FeaturesCfg[ xorstr( "SilentAim" ) ][ xorstr( "FovColor" ) ] );

				// Features - ESP
				ESP->Enabled = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Enabled" ) ];
				ESP->Box = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Box" ) ];
				ESP->BoxState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "BoxState" ) ];
				ESP->Skeleton = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "Skeleton" ) ];
				ESP->HealthBar = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HealthBar" ) ];
				ESP->HealthBarState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HealthBarState" ) ];
				ESP->ArmorBar = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ArmorBar" ) ];
				ESP->ArmorBarState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ArmorBarState" ) ];
				ESP->WeaponName = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponName" ) ];
				ESP->WeaponNameState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponNameState" ) ];
				ESP->SnapLines = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SnapLines" ) ];
				ESP->UserNames = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNames" ) ];
				ESP->UserNamesState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNamesState" ) ];
				ESP->HeadCircle = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HeadCircle" ) ];
				ESP->IgnoreNPCs = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "IgnoreNPCs" ) ];
				ESP->HighlightVisible = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "HighlightVisible" ) ];
				ESP->IgnoreDead = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "IgnoreDead" ) ];
				ESP->DistanceFromMe = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceFromMe" ) ];
				ESP->DistanceFromMeState = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceFromMeState" ) ];
				ESP->ShowLocalPlayer = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "ShowLocalPlayer" ) ];
				ESP->MaxDistance = FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "MaxDistance" ) ];
				ESP->DistanceCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "DistanceCol" ) ] );
				ESP->UserNamesCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "UserNamesCol" ) ] );
				ESP->WeaponNameCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "WeaponNameCol" ) ] );
				ESP->SkeletonCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SkeletonCol" ) ] );
				ESP->BoxCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "BoxCol" ) ] );
				ESP->SnapLinesCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "SnapLinesCol" ) ] );
				ESP->FriendCol = JsonToImCol( FeaturesCfg[ xorstr( "ESP" ) ][ xorstr( "FriendCol" ) ] );

				// Features - VehicleESP
				VehicleESP->Enabled = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "Enabled" ) ];
				VehicleESP->SnapLines = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "SnapLines" ) ];
				VehicleESP->ShowLockUnlock = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "ShowLockUnlock" ) ];
				VehicleESP->VehName = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "VehName" ) ];
				VehicleESP->DistanceFromMe = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "DistanceFromMe" ) ];
				VehicleESP->MaxDistance = FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "MaxDistance" ) ];
				VehicleESP->SnapLinesCol = JsonToImCol( FeaturesCfg[ xorstr( "VehicleESP" ) ][ xorstr( "SnapLinesCol" ) ] );

				// Features - Player
				Player->NoClipKey = FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoClipKey" ) ];
				Player->NoClipSpeed = FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "NoClipSpeed" ) ];
				Player->GodModeKey = FeaturesCfg[ xorstr( "Player" ) ][ xorstr( "GodModeKey" ) ];

				ESP->UpdateCfgESP = true;

				return xorstr( "Config loaded with success." );
			}
			catch ( const std::exception & e ) {
				//std::cout << e.what() << "\n";
				return xorstr( "Error Loading Config!");
			}
		}

	};

	inline Config g_Config;

}