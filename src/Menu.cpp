#include "../pch.h"
#include "../include/Menu.hpp"
#include "SDK.hpp"
#include "config.h"
#include <algorithm>


std::string rand_str(const int len)
{
    std::string str;
    char c;
    int idx;
    for (idx = 0; idx < len; idx++)
    {
        c = 'a' + rand() % 26;
        str.push_back(c);
    }
    return str;
}
void Damage(SDK::APalCharacter* character, int32 damage)
{
    SDK::FPalDamageInfo  info = SDK::FPalDamageInfo();
    info.AttackElementType = SDK::EPalElementType::Normal;
    info.Attacker = Config.GetPalPlayerCharacter();
    info.AttackerGroupID = Config.GetPalPlayerState()->IndividualHandleId.PlayerUId;
    info.AttackerLevel = 50;
    info.AttackType = SDK::EPalAttackType::Weapon;
    info.bApplyNativeDamageValue = true;
    info.bAttackableToFriend = true;
    info.IgnoreShield = true;
    info.NativeDamageValue = damage;
    Config.GetPalPlayerState()->SendDamage_ToServer(character, info);
}

int InputTextCallback(ImGuiInputTextCallbackData* data) {
    char inputChar = data->EventChar;

    Config.Update(Config.inputTextBuffer);

    return 0;
}

CatchRate CRate;
CatchRate OldRate;

void DetourCatchRate(SDK::APalCaptureJudgeObject* p_this) {
    if (p_this) {
        //p_this->ChallengeCapture_ToServer(Config.localPlayer, Config.CatchRate);
        p_this->ChallengeCapture(Config.localPlayer, Config.CatchRate);
    }
}
void ToggleCatchRate(bool catchrate) {
    if (catchrate) {
        if (CRate == NULL) {
            CRate = (CatchRate)(Config.ClientBase + Config.offset_CatchRate);
            MH_CreateHook(CRate, DetourCatchRate, reinterpret_cast<void**>(OldRate));
            MH_EnableHook(CRate);
            return;
        }
        MH_EnableHook(CRate);
        return;
    }
    else
    {
        MH_DisableHook(CRate);

    }
}

namespace DX11_Base {

    //helper variables
    char inputBuffer_getFnAddr[100];
    char inputBuffer_getClass[100];
    char inputBuffer_setWaypoint[32];

    namespace Styles {
        void InitStyle()
        {
            ImGuiStyle& style = ImGui::GetStyle();
            ImVec4* colors = ImGui::GetStyle().Colors;

            //	STYLE PROPERTIES
            style.WindowPadding = ImVec2(15, 15);
            style.WindowRounding = 5.0f;
            style.FramePadding = ImVec2(5, 5);
            style.FrameRounding = 4.0f;
            style.ItemSpacing = ImVec2(12, 8);
            style.ItemInnerSpacing = ImVec2(8, 6);
            style.IndentSpacing = 25.0f;
            style.ScrollbarSize = 15.0f;
            style.ScrollbarRounding = 9.0f;
            style.GrabMinSize = 5.0f;
            style.GrabRounding = 3.0f;

            //  Base ImGui Styling , Aplying a custyom style is left up to you.
            ImGui::StyleColorsDark();

            /// EXAMPLE COLOR 
            //colors[ImGuiCol_FrameBg] = ImVec4(0, 0, 0, 0);

            //	COLORS
            if (g_Menu->dbg_RAINBOW_THEME) {
                //  RGB MODE STLYE PROPERTIES
                colors[ImGuiCol_Separator] = ImVec4(g_Menu->dbg_RAINBOW);
                colors[ImGuiCol_TitleBg] = ImVec4(0, 0, 0, 1.0f);
                colors[ImGuiCol_TitleBgActive] = ImVec4(0, 0, 0, 1.0f);
                colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0, 0, 0, 1.0f);
            }
            else {
                /// YOUR DEFAULT STYLE PROPERTIES HERE

                colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0, 230);
                colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
                colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
                colors[ImGuiCol_ButtonActive] = ImColor(239, 73, 88, 255);
                colors[ImGuiCol_ButtonHovered] = ImColor(173, 55, 65, 255);
                colors[ImGuiCol_FrameBg] = ImColor(31, 30, 31, 255);
                colors[ImGuiCol_FrameBgActive] = ImColor(44, 43, 44, 255);
                colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);
                colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
                colors[ImGuiCol_ChildBg] = ImColor(33, 34, 45, 200);
                colors[ImGuiCol_CheckMark] = ImColor(240, 50, 66, 255);
                colors[ImGuiCol_SliderGrab] = ImColor(240, 74, 88, 255);
                colors[ImGuiCol_SliderGrabActive] = ImColor(240, 50, 66, 255);
                colors[ImGuiCol_Header] = ImColor(240, 50, 66, 255);
                colors[ImGuiCol_HeaderHovered] = ImColor(240, 74, 88, 255);
                colors[ImGuiCol_HeaderActive] = ImColor(240, 50, 66, 255);
                colors[ImGuiCol_ResizeGrip] = ImColor(220, 50, 66, 120);
                colors[ImGuiCol_ResizeGripHovered] = ImColor(250, 50, 66, 140);
                colors[ImGuiCol_ResizeGripActive] = ImColor(240, 50, 66, 255);
                colors[ImGuiCol_SeparatorHovered] = ImColor(250, 50, 66, 140);
                colors[ImGuiCol_SeparatorActive] = ImColor(240, 50, 66, 255);
                colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.12f, 0.12f, 1.00f);
                colors[ImGuiCol_Tab] = ImVec4(0.58f, 0.18f, 0.18f, 0.86f);
                colors[ImGuiCol_TabHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
                colors[ImGuiCol_TabActive] = ImVec4(0.68f, 0.20f, 0.20f, 1.00f);
            }
        }
    }


    namespace Tabs 
    {
        void TABPlayer()
        {
            ImGui::Checkbox("PLAYER Speed", &Config.IsSpeedHack);

            ImGui::SliderFloat("Speed Multiply", &Config.SpeedModiflers, 1, 10);

            ImGui::Checkbox("Damage", &Config.IsAttackModiler);

            ImGui::SliderInt("Damage Multiply", &Config.DamageUp, 0, 2000);

            ImGui::Checkbox("DefenseHack", &Config.IsDefuseModiler);

            ImGui::SliderInt("Defense Multiply", &Config.DefuseUp, 0, 2000);

            ImGui::Checkbox("Infinited Ammo", &Config.IsInfinAmmo);

            ImGui::Checkbox("No Reload", &Config.NoReload);

            if (ImGui::Checkbox("FullBright", &Config.IsFullbright))
                SetFullbright(Config.IsFullbright);

            ImGui::Checkbox("InfStamina", &Config.IsInfStamina);

            ImGui::Checkbox("Godmode", &Config.IsMuteki);

            if (ImGui::Checkbox("Invisible (F4)", &Config.spec))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        Config.GetPalPlayerCharacter()->SetSpectatorMode(Config.spec);

                    }
                }
            }
                
            //ImGui::Checkbox("Revive", &Config.IsRevive);


            ImGui::InputText("Name Changer", Config.CharName, sizeof(Config.CharName));
            if (ImGui::Button("Rename", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();

                        wchar_t ws[255];
                        swprintf(ws, 255, L"%hs", Config.CharName);
                        Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->UpdateCharacterNickName_ToServer(Config.GetPalPlayerCharacter()->CharacterParameterComponent->IndividualHandle->ID, SDK::FString(ws));
                    }
                }
            }

            if (ImGui::Button("RandomName", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();
                        std::string s = rand_str(20);

                        wchar_t  ws[255];
                        swprintf(ws, 255, L"%hs", s.c_str());
                        sprintf_s(Config.CharName, "%hs", s.c_str());

                        Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->UpdateCharacterNickName_ToServer(Config.GetPalPlayerCharacter()->CharacterParameterComponent->IndividualHandle->ID, SDK::FString(ws));
                    }
                }
            }



            if (ImGui::Button("PrintCoords", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        SDK::FVector PlayerLocation = p_appc->K2_GetActorLocation();
                        std::string MyLocation = std::format("\nX: {} | Y: {} | Z: {}\n", PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);
                        g_Console->printdbg(MyLocation.c_str(), Console::Colors::green, p_appc);
                    }
                }
            }

            SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
            if (p_appc != NULL && Config.GetUWorld())
            {
                if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                {
                    SDK::FVector PlayerLocation = p_appc->K2_GetActorLocation();
                    std::string MyLocation = std::format("X: {} | Y: {} | Z: {}", PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);
                    ImGui::Text(MyLocation.c_str());
                }
            }
        }
        
        void TABMisc()
        {
            if (ImGui::Button("11111", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                SDK::UWorld* pWorld = Config.GetUWorld();
                SDK::UPalUtility* pUtility = Config.pPalUtility;
                if (!pWorld || !pUtility)
                    return;

                SDK::UPalGameSetting* pGameSettings = pUtility->GetGameSetting(pWorld);
                if (!pGameSettings)
                    return;

                pGameSettings->WorldmapUIMaskClearSize = 20000.f;
                pGameSettings->OverWeightSpeedZero_AddPercent = 0;
                pGameSettings->AutoHPRegene_Percent_perSecond = 100;
                pGameSettings->PlayerHPRateFromRespawn = 100;
                pGameSettings->BuildExp = 10000;
            }



            if (ImGui::Button("Fast Crafting", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
                SetCraftingSpeed(9999.f, false);
            if (ImGui::Button("Easy Pal Condensation", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
            {
                //auto ezcondenseAOB = signature("E8 ?? ?? ?? ?? 89 ?? ?? ?? 00 00 E9 ?? ?? ?? ?? 33").GetPointer();
                //BYTE patch[] = { 0x31, 0xC0, 0xFF, 0xC0, 0x90 };
                //memory::WriteToMemory(ezcondenseAOB, patch, 5);
                //Credit emoisback & Zanzer

                SDK::TMap<int32, int32> RankRequired = SDK::TMap<int32, int32>();
                SDK::UWorld* world = Config.GetUWorld();
                SDK::UPalUtility* aPalUtility = SDK::UPalUtility::GetDefaultObj();
                aPalUtility->GetGameSetting(world)->CharacterRankUpRequiredNumDefault = 1;
                aPalUtility->GetGameSetting(world)->CharacterRankUpRequiredNumMap = RankRequired;

            }

            if (ImGui::Button("ToggleFly", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                Config.IsToggledFly = !Config.IsToggledFly;
                ExploitFly(Config.IsToggledFly);
            }

            if (ImGui::Button("NormalHealth", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            SDK::FFixedPoint fixpoint = SDK::FFixedPoint();
                            fixpoint.Value = Config.GetPalPlayerCharacter()->CharacterParameterComponent->GetMaxHP().Value;
                            Config.GetPalPlayerCharacter()->ReviveCharacter_ToServer(fixpoint);
                        }
                    }
                }
            }

            if (ImGui::Button("GodHealth", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            SDK::FFixedPoint fixpoint = SDK::FFixedPoint();
                            fixpoint.Value = 99999999;
                            Config.GetPalPlayerCharacter()->ReviveCharacter_ToServer(fixpoint);
                        }
                    }
                }
            }

            if (ImGui::Button("MaxWeight", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->InventoryData->MaxInventoryWeight = Config.MaxWeight;
                        }
                    }
                }
            }

            if (ImGui::Button("Starter Pack", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25))) {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            SDK::UPalPlayerInventoryData* InventoryData = Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->GetInventoryData();
                            if (InventoryData != NULL) {
                                AddItemToInventoryByName(InventoryData, (char*)"AssaultRifle_Default5", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"AssaultRifleBullet", 1000);
                                AddItemToInventoryByName(InventoryData, (char*)"Launcher_Default_5", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"ExplosiveBullet", 50);
                                AddItemToInventoryByName(InventoryData, (char*)"PalSphere_Debug", 200);
                                AddItemToInventoryByName(InventoryData, (char*)"CornSoup", 20);
                                AddItemToInventoryByName(InventoryData, (char*)"Accessory_HeatResist_3", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"Accessory_CoolResist_3", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"AutoMealPouch_Tier1", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"AutoMealPouch_Tier2", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"AutoMealPouch_Tier3", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"AutoMealPouch_Tier4", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"AutoMealPouch_Tier5", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"Lantern", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"StealArmor_5", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"StealHelmet_5", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"Glider_Legendary", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"Shield_04", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"Pal_crystal_S", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"Wood", 8);
                                AddItemToInventoryByName(InventoryData, (char*)"Stone", 3);
                                AddItemToInventoryByName(InventoryData, (char*)"SkillUnlock_JetDragon", 1);
                                AddItemToInventoryByName(InventoryData, (char*)"SkillUnlock_Anubis", 1);
                            }
                        }
                    }
                }
            }

            if (ImGui::Button("Catch Rate", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                Config.isCatchRate = !Config.isCatchRate;
                ToggleCatchRate(Config.isCatchRate);
            }
            ImGui::InputFloat("Catch Rate Modifier", &Config.CatchRate);


        }
        void TABCageSpawner()
        {

            static char palSpawnCage[20] = "";
            std::initializer_list list = itemlist::pals;

            int cur_size = 0;

            static char pal_search[100];

            ImGui::InputText("Search", pal_search, IM_ARRAYSIZE(pal_search));
            ImGui::BeginListBox("##LIST_CAGE_MONSTERS", ImVec2(ImGui::GetContentRegionAvail().x, 500));
            for (const auto& pal : list) {
                std::istringstream ss(pal);
                std::string left_text, right_text;

                std::getline(ss, left_text, '|');
                std::getline(ss, right_text);

                auto right_to_lower = right_text;
                std::string pal_search_to_lower = pal_search;

                std::transform(right_to_lower.begin(), right_to_lower.end(), right_to_lower.begin(), ::tolower);
                std::transform(pal_search_to_lower.begin(), pal_search_to_lower.end(), pal_search_to_lower.begin(), ::tolower);

                if (pal_search[0] != '\0' && (right_to_lower.find(pal_search_to_lower) == std::string::npos))
                    continue;

                cur_size += right_text.length();

                ImGui::PushID(pal);
                if (ImGui::Selectable(right_text.c_str()))
                {
                    static SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();
                    wchar_t  ws[255];
                    swprintf(ws, 255, L"%hs", left_text.c_str());
                    SDK::FName Name = lib->Conv_StringToName(SDK::FString(ws));
                    Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->RequestSpawnMonsterForPlayer(Name, 1, 50);
                    strcpy_s(palSpawnCage, (char*)left_text.c_str());
                }
                ImGui::PopID();
            }

            ImGui::EndListBox();
            if (ImGui::Button("Add Pal To Nearby Cage", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))//
            {
                SDK::APalPlayerCharacter* pLocalPlayer = Config.GetPalPlayerCharacter();
                if (!pLocalPlayer)
                    return;

                std::vector<SDK::AActor*> actors;

                //if (!config::GetAllActorsofType(SDK::APalCapturedCage::StaticClass(), &actors, true))
                //    return;
                SDK::UWorld* world = Config.GetUWorld();
                SDK::TUObjectArray* objects = world->GObjects;

                auto draw = ImGui::GetBackgroundDrawList();

                for (int i = 0; i < objects->NumElements; ++i)//(auto actor : actors)
                {
                    SDK::UObject* object = objects->GetByIndex(i);
                    if (!object) continue;
                    if (!object->IsA(SDK::APalCapturedCage::StaticClass())) continue;

                    SDK::APalCapturedCage* cage = static_cast<SDK::APalCapturedCage*>(object); // Try to cast actor to APalCapturedCage
                    if (!cage) continue; // Skip to the next actor if casting fails

                    SDK::FVector actorLocation = cage->K2_GetActorLocation();
                    SDK::FVector localPlayerLocation = pLocalPlayer->K2_GetActorLocation();
                    float distanceTo = GetDistanceToActor(pLocalPlayer, cage);

                    if (distanceTo < 50)
                    {
                        static SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();

                        std::string palname = palSpawnCage;
                        wchar_t  ws[255];
                        swprintf(ws, 255, L"%hs", palname.c_str());
                        SDK::FName Name = lib->Conv_StringToName(SDK::FString(ws));

                        cage->SpawnPal(Name, 50);
                    }
                }
            }
        }
        void TABTeleporter()
        {
            ImGui::Checkbox("SafeTeleport", &Config.IsSafe);
            //ImGui::SameLine();
            //ImGui::Checkbox("Custom Waypoints", &Config.bisOpenWaypoints);
            if (ImGui::Button("Go Home (F6)", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
                RespawnLocalPlayer(Config.IsSafe);
            if (ImGui::Button("Tele To MapMarker (F2)", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
                TeleportToMapMarker();

            ImGui::InputFloat3("Pos", Config.Pos);
            ImGui::SameLine();
            if (ImGui::Button("Go To", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                SDK::FVector vector = { Config.Pos[0],Config.Pos[1],Config.Pos[2] };
                AnyWhereTP(vector, Config.IsSafe);
            }

            //  Waypoints
            ImGui::InputTextWithHint("##INPUT_SETWAYPOINT", "CUSTOM WAYPOINT NAME", inputBuffer_setWaypoint, 32);
            ImGui::SameLine();
            if (ImGui::Button("SET", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                std::string wpName = inputBuffer_setWaypoint;
                if (wpName.size() > 0)
                {
                    AddWaypointLocation(wpName);
                    memset(inputBuffer_setWaypoint, 0, 32);
                }
            }

            if (ImGui::BeginListBox("##LIST_LOCATIONS", ImVec2(ImGui::GetContentRegionAvail().x/2, 500)))
            {
                for (const auto& pair : database::locationMap)
                {
                    const std::string& locationName = pair.first;
                    if (ImGui::Selectable(locationName.c_str()))
                    {
                        SDK::FVector location = SDK::FVector(pair.second[0], pair.second[1], pair.second[2]);
                        AnyWhereTP(location, Config.IsSafe);
                    }
                }
                ImGui::EndListBox();
            }
            if (Config.db_waypoints.size() > 0)
            {
                ImGui::SameLine();
                if (ImGui::BeginListBox("##LIST_WAYPOINTS", { ImGui::GetContentRegionAvail().x/2, 250 }))
                {
                    DWORD index = -1;
                    for (auto waypoint : Config.db_waypoints)
                    {
                        index++;
                        ImGui::PushID(index);
                        //  ImGui::Checkbox("SHOW", &waypoint.bIsShown);
                        //  ImGui::SameLine();
                        if (ImGui::Selectable(waypoint.waypointName.c_str()))
                            AnyWhereTP(waypoint.waypointLocation, false);
                        ImGui::PopID();
                    }

                    ImGui::EndListBox();
                }
            }

        }

        void TABExploit()
        {
            ImGui::InputInt("EXP :", &Config.EXP);
            ImGui::SameLine();
            if (ImGui::Button("Give", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            if (Config.EXP >= 0)
                            {
                                Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->GrantExpForParty(Config.EXP);
                            }
                        }
                    }
                }
            }

            if (ImGui::Button("Max Level<50>", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->GrantExpForParty(99999999);
                        }
                    }
                }
            }
            if (ImGui::Button("Unlock Technologies", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                SDK::APalPlayerCharacter* pPalCharacter = Config.GetPalPlayerCharacter();

                if (!pPalCharacter)
                    return;

                auto Unlocked = pPalCharacter->GetPalPlayerController()->GetPalPlayerState()->TechnologyData->UnlockedTechnologyNameArray;

                SDK::TArray<SDK::FName> mos = {};
                SDK::UDataTableFunctionLibrary::GetDefaultObj()->GetDataTableRowNames(pPalCharacter->GetPalPlayerController()->GetPalPlayerState()->TechnologyData->TechnologyDataSet.RecipeUnlockDataTable, &mos);

                for (int i = 0; i < Unlocked.Count(); i++) {
                    //g_Console->printdbg("[+] %s already unlocked\n", Console::Colors::green, Unlocked[i].GetRawString().c_str());
                }

                for (int i = 0; i < mos.Count(); i++) {
                    bool skip = false;

                    for (int j = 0; j < Unlocked.Count(); j++)
                        if (mos[i].GetRawString() == Unlocked[j].GetRawString())
                            skip = true;

                    if (skip) continue;

                    //g_Console->printdbg("[+] Unlocking %s\n", Console::Colors::green, mos[i].GetRawString().c_str());
                    pPalCharacter->GetPalPlayerController()->Transmitter->Player->RequestUnlockTechnology_ToServer(mos[i]);
                }
            }
            if (ImGui::Button("Tech Books", ImVec2(130, 20))) {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            SDK::UPalPlayerInventoryData* InventoryData = Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->GetInventoryData();
                            if (InventoryData != NULL)
                                AddItemToInventoryByName(InventoryData, (char*)"TechnologyBook_G3", 50);
                        }
                    }
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Use Books (1st Slot)", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25))) {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState() != NULL)
                        {
                            SDK::UPalPlayerInventoryData* InventoryData = Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->GetInventoryData();
                            if (InventoryData != NULL) {
                                SDK::UPalItemContainerMultiHelper* InventoryMultiHelper = InventoryData->InventoryMultiHelper;
                                if (InventoryMultiHelper != NULL) {
                                    SDK::TArray<class SDK::UPalItemContainer*> Containers = InventoryMultiHelper->Containers;
                                    if (Containers.Count() == 0) {
                                        return;
                                    }

                                    SDK::UPalItemSlot* FirstSlot = Containers[0]->Get(0);

                                    if (FirstSlot != NULL)
                                    {
                                        SDK::FPalItemSlotId ID = FirstSlot->GetSlotId();
                                        for (int i = 0; i < FirstSlot->GetStackCount(); i++)
                                            Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->TechnologyData->RequestAddTechnologyPointByItem(ID);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (ImGui::Button("Unlock Pal skills", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
                SpawnMultiple_ItemsToInventory(config::QuickItemSet::pal_unlock_skills);
            if (ImGui::Button("All Effigies", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25))) //credit to bennett
            {
                SDK::APalPlayerCharacter* pPalCharacter = Config.GetPalPlayerCharacter();
                if (!pPalCharacter)
                    return;

                SDK::UWorld* world = Config.GetUWorld();
                if (!world)
                    return;

                SDK::TUObjectArray* objects = world->GObjects;

                for (int i = 0; i < objects->NumElements; ++i) {
                    SDK::UObject* object = objects->GetByIndex(i);

                    if (!object) continue;

                    if (!object->IsA(SDK::APalLevelObjectRelic::StaticClass()))
                        continue;

                    SDK::APalLevelObjectObtainable* relic = (SDK::APalLevelObjectObtainable*)object;
                    if (!relic) continue;

                    ((SDK::APalPlayerState*)pPalCharacter->PlayerState)->RequestObtainLevelObject_ToServer(relic);
                }
            }
            if (ImGui::Button("Unlock Fast Travel", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25))) //credit aaacaaac
            {
                std::vector<std::string> keyStrings = {
                    "6E03F8464BAD9E458B843AA30BE1CC8F","DDBBFFAF43D9219AE68DF98744DF0831","603ED0CD4CFB9AFDC9E11F805594CCE5","6282FE1E4029EDCDB14135AA4C171E4C","9FBB93D84811BE424A37C391DBFBB476","979BF2044C8E8FE559B598A95A83EDE3","923B781345D2AB7ECED6BABD6E97ECE8",
                    "16C7164C43E2B96BEDCC6696E2E592F7","D27AFCAD472164F000D33A8D8B61FE8B","41727100495D21DC905D309C53989914","6DB6B7B2431CA2EFFFC88EB45805BA6A","74270C2F45B8DCA66B6A1FAAA911D024","DF9FB9CB41B43052A9C74FA79A826A50","8CA5E9774FF1BBC1156ABCA09E616480",
                    "15314BE94E2FB8D018D5749BE9A318F0","79C561B747335A7A0A8FBF9FAE280E62","23B9E99C4A454B99220AF7B4A58FD8DE","A1BC65AA445619EF338E0388BC010648","BF8B123244ADB794A06EA8A10503FBDD","F8DF603B4C750B37D943C9AF6A911946","596996B948716D3FD2283C8B5C6E829C",
                    "28D514E74B51FD9EB078A891DB0787C2","ACAE5FB04D48DE4197443E9C0993086B","4D2F204549AB656CA1EA4B8E39C484F3","1BDEABA240B1699541C17F83E59E61DF","2BC5E46049E69D3549CFB58948BE3288","91DAC6F34D2A9FD7F01471B5166C6C02","41E36D9A4B2BA79A3AD1B7B83B16F77D",
                    "76B000914943BADDC56BCFBAE2BF051E","DC0ECF9241B4410C59EE619F56D1106A","71C4B2B2407F2BBBD77572A20C7FF0F5","EC94023A4CA571FF0FD19E90944F4231","2A2B744B41AC79964DAE6B89CAC51FC3","E0819EFB41581AEAC3A029B0EE2FE195","22095BFA48A46172F8D154B2EBEB7493",
                    "7C5E91514F6E84B0C1DEFFB52C7C4DBA","AECFED0D41AFEE11F30B4F9687BC3243","2EC07ACC4505CB726DE38A84246CA999","F8E5CB8143F4FA2F6213E6B454569F87","5F426B49469368B0C131D3A6DB8F7831","A277AE6341EF40D84D711EA52303353F","6231802D40C81C00445379AE238D9F90",
                    "F6C005A14B38FE0B57F1C7869FD899CB","7170881D44249E90902F728E240493AF","3E8E504B4A3975FD3862E1BC85A5D4F6","B001852C491FF5E70C4747BFF9972924","2DE1702048A1D4A82126168C49BE51A9","E88379634CB5B6117DA2E7B8810BFE0A","3697999C458BF8A3C7973382969FBDF9",
                    "65B10BB14ABDA9C2109167B21901D195","4669582D4081BF550AFB66A05D043A3D","FE90632845114C7FBFA4669D071E285F","5970E8E648D2A83AFDFF7C9151D9BEF5","B639B7ED4EE18A7AA09BA189EA703032","099440764403D1508D9BADADF4848697","B44AA24445864494E7569597ACCAEFC6",
                    "3A0F123947BE045BC415C6B061A5285A","F382ADAE4259150BF994FF873ECF242B", "866881DB443444AA7F4E7C8E5DCDAA29", "01ACCA6E4BDAA68220821FB05AB54E4D", "75BD9923489E2A4EBCED5A81175D5928", "513E166044565A0BD3360F94142577E8"
                };

                SDK::APalPlayerCharacter* pPalCharacter = Config.GetPalPlayerCharacter();

                for (const std::string& keyString : keyStrings)
                {
                    SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();
                    //Convert FNAME
                    wchar_t  ws[255];
                    swprintf(ws, 255, L"%hs", keyString.c_str());
                    SDK::FName FNameKS = lib->Conv_StringToName(SDK::FString(ws));

                    ((SDK::APalPlayerState*)pPalCharacter->PlayerState)->RequestUnlockFastTravelPoint_ToServer(FNameKS);
                }

            }
            if (ImGui::Button("Unlock Player Chests", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                SDK::UWorld* world = Config.GetUWorld();
                if (!world)
                    return;

                SDK::TUObjectArray* objects = world->GObjects;

                for (int i = 0; i < objects->NumElements; ++i) {
                    SDK::UObject* object = objects->GetByIndex(i);

                    if (!object) continue;

                    if (!object->IsA(SDK::UPalMapObjectPasswordLockModule::StaticClass())) {
                        continue;
                    }

                    SDK::UPalMapObjectPasswordLockModule* locked = (SDK::UPalMapObjectPasswordLockModule*)object;
                    if (!locked) {
                        continue;
                    }
                    locked->LockState = SDK::EPalMapObjectPasswordLockState::Unlock;
                }
            }
            if (ImGui::Button("Crash Server", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        SDK::UWorld* world = Config.GetUWorld();
                        if (!world) return;

                        SDK::TUObjectArray* objects = world->GObjects;

                        for (int i = 0; i < objects->NumElements; ++i) {
                            SDK::UObject* object = objects->GetByIndex(i);

                            if (!object) continue;

                            if (!object->IsA(SDK::APalMonsterCharacter::StaticClass())) {
                                continue;
                            }

                            SDK::APalMonsterCharacter* Monster = (SDK::APalMonsterCharacter*)object;

                            Config.GetPalPlayerCharacter()->GetPalPlayerController()->RequestLiftup_ToServer((SDK::APalCharacter*)object);
                        }

                    }
                }
            }
            if (ImGui::Button("Killaura", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (Config.GetPalPlayerCharacter() != NULL)
                {
                    if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                    {
                        if (Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState())
                        {
                            SDK::TArray<SDK::AActor*> T = Config.GetUWorld()->PersistentLevel->Actors;
                            for (int i = 0; i < T.Count(); i++)
                            {

                                if (T[i] != NULL)
                                {
                                    if (T[i]->IsA(SDK::APalCharacter::StaticClass()))
                                    {
                                        SDK::APalCharacter* monster = (SDK::APalCharacter*)T[i];
                                        if (monster->IsLocallyControlled())
                                        {
                                            continue;
                                        }
                                        Config.GetPalPlayerState()->SendDeath_ToServer(monster);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            

            if (ImGui::Checkbox("TELEPORT PALS TO XHAIR", &Config.IsTeleportAllToXhair) && !Config.IsTeleportAllToXhair)
                Config.mDebugEntCapDistance = 10.f;
            {
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                ImGui::SliderFloat("##ENT_CAP_DISTANCE", &Config.mDebugEntCapDistance, 1.0f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
            }
            if (ImGui::Checkbox("DEATH AURA", &Config.IsDeathAura) && !Config.IsDeathAura)
            {
                Config.mDeathAuraDistance = 10.0f;
                Config.mDeathAuraAmount = 1;
            }
            if (Config.IsDeathAura)
            {
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * .7);
                ImGui::SliderFloat("##AURA_DISTANCE", &Config.mDeathAuraDistance, 1.0f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                ImGui::SliderInt("##AURA_DMG", &Config.mDeathAuraAmount, 1, 10, "%d", ImGuiSliderFlags_AlwaysClamp);
            }
        }
        
        void TABConfig()
        {
            
            ImGui::Text("PalCrack Menu");
            ImGui::Text("Version: v1.0");
            ImGui::Text("This is just an Free ModMenu. if you paid for this you have been scammed");
            ImGui::Text("Credits to: bluesword007");
            ImGui::Text("Credits to: Palworld Offsets UnknownCheats.me");

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            if (ImGui::Button("Unload DLL", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25))) {
#if DEBUG
                g_Console->printdbg("\n\n[+] UNHOOK INITIALIZED [+]\n\n", Console::Colors::red);

#endif
                g_KillSwitch = TRUE;
            }
        }
        
        

        void TABItemSpawner()
        {
            static int num_to_add = 1;
            static int category = 0;

            ImGui::InputInt("Num To Add", &num_to_add);

            ImGui::Combo("Item Category", &category, "All Items\0Accessories\0Ammo\0Armor\0Crafting Materials\0Eggs\0Food\0Hats\0\Medicine\0Money\0Other\0Pal Spheres\0Saddles\0Seeds\0Tools\0Weapons\0Skill Fruit\0");

            std::initializer_list list = database::all;

            switch (category)
            {
            case 1:
                list = database::accessories;
            case 2:
                list = database::ammo;
                break;
            case 3:
                list = database::armor;
                break;
            case 4:
                list = database::craftingmaterials;
                break;
            case 5:
                list = database::eggs;
                break;
            case 6:
                list = database::food;
                break;
            case 7:
                list = database::hats;
                break;
            case 8:
                list = database::medicine;
                break;
            case 9:
                list = database::money;
                break;
            case 10:
                list = database::other;
                break;
            case 11:
                list = database::palspheres;
                break;
            case 12:
                list = database::saddles;
                break;
            case 13:
                list = database::seeds;
                break;
            case 14:
                list = database::toolss;
                break;
            case 15:
                list = database::weapons;
                break;
            case 16:
                list = database::skillfruit;
                break;
            default:
                list = database::all;
            }

            int cur_size = 0;

            static char item_search[100];

            ImGui::InputText("Search", item_search, IM_ARRAYSIZE(item_search));

            ImGui::BeginListBox("##LIST_ITEMS", ImVec2(ImGui::GetContentRegionAvail().x, 500));
            for (const auto& item : list) {
                std::istringstream ss(item);
                std::string left_text, right_text;

                std::getline(ss, left_text, '|');
                std::getline(ss, right_text);

                auto right_to_lower = right_text;
                std::string item_search_to_lower = item_search;

                std::transform(right_to_lower.begin(), right_to_lower.end(), right_to_lower.begin(), ::tolower);
                std::transform(item_search_to_lower.begin(), item_search_to_lower.end(), item_search_to_lower.begin(), ::tolower);

                if (item_search[0] != '\0' && (right_to_lower.find(item_search_to_lower) == std::string::npos))
                    continue;


                //ImGui::PushID(item);
                if (ImGui::Selectable(right_text.c_str()))
                {
                    SDK::UPalPlayerInventoryData* InventoryData = Config.GetPalPlayerCharacter()->GetPalPlayerController()->GetPalPlayerState()->GetInventoryData();
                    AddItemToInventoryByName(InventoryData, (char*)left_text.c_str(), num_to_add);
                }
                //ImGui::PopID();
            }
            ImGui::EndListBox();
        }

        void TABQuick()
        {
            if (ImGui::Button("Basic Items stack", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
                SpawnMultiple_ItemsToInventory(config::QuickItemSet::basic_items_stackable);

            if (ImGui::Button("Basic Items single", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
                SpawnMultiple_ItemsToInventory(config::QuickItemSet::basic_items_single);

            if (ImGui::Button("Unlock Pal skills", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
                SpawnMultiple_ItemsToInventory(config::QuickItemSet::pal_unlock_skills);

            if (ImGui::Button("Spheres", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
                SpawnMultiple_ItemsToInventory(config::QuickItemSet::spheres);

            if (ImGui::Button("Tools", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
                    SpawnMultiple_ItemsToInventory(config::QuickItemSet::tools);
        }
        
        
        void TABDebug()
        {
            if (ImGui::Checkbox("DEBUG ESP", &Config.isDebugESP) && !Config.isDebugESP)
                Config.mDebugESPDistance = 10.f;
            if (Config.isDebugESP)
            {
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
                ImGui::SliderFloat("##DISTANCE", &Config.mDebugESPDistance, 1.0f, 100.f, "%.0f", ImGuiSliderFlags_AlwaysClamp);
            }

            //  @TODO: print additional debug information
            if (ImGui::Button("PrintPlayerAddr", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
                if (p_appc)
                    g_Console->printdbg("\n\n[+] APalPlayerCharacter: 0x%llX\n", Console::Colors::green, p_appc);
                
            }
            if (ImGui::Button("Print All Players", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                
                SDK::TArray<SDK::APalCharacter*> OutPlayers;
                SDK::UPalUtility::GetDefaultObj()->GetAllPlayerCharacters(Config.GetUWorld(), &OutPlayers);
                for (int i = 0; i < OutPlayers.Count(); i++)
                {
                    std::string name;
                    SDK::FString fn;
                    OutPlayers[i]->CharacterParameterComponent->GetNickname(&fn);
                    name = fn.ToString();
                    g_Console->printdbg("\n[+] APalPlayerCharacter: %s\n", Console::Colors::green, name.c_str());
                }
            }
            
            if (ImGui::Button("Style Editor", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                g_GameVariables->m_ShowDemo = !g_GameVariables->m_ShowDemo;
            }
            if (ImGui::Button("RAINBOW THEME", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                g_Menu->dbg_RAINBOW_THEME = !g_Menu->dbg_RAINBOW_THEME;
            }
            ImGui::InputTextWithHint("##INPUT", "INPUT GOBJECT fn NAME", inputBuffer_getFnAddr, 100);
            ImGui::SameLine();
            if (ImGui::Button("GET fn", ImVec2(ImGui::GetContentRegionAvail().x, 20)))
            {
                std::string input = inputBuffer_getFnAddr;
                SDK::UFunction* object = SDK::UObject::FindObject<SDK::UFunction>(input);
                if (object)
                {
                    static __int64 dwHandle = reinterpret_cast<__int64>(GetModuleHandle(0));
                    void* fnAddr = object->ExecFunction;
                    unsigned __int64 fnOffset = (reinterpret_cast<__int64>(fnAddr) - dwHandle);
                    g_Console->printdbg("[+] Found [%s] -> 0x%llX\n", Console::Colors::yellow, input.c_str(), fnOffset);
                }
                else
                    g_Console->printdbg("[!] OBJECT [%s] NOT FOUND!\n", Console::Colors::red, input.c_str());
                memset(inputBuffer_getFnAddr, 0, 100);
            }

            //  Get Class pointer by name
            ImGui::InputTextWithHint("##INPUT_GETCLASS", "INPUT OBJECT CLASS NAME", inputBuffer_getClass, 100);
            ImGui::SameLine();
            if (ImGui::Button("GET CLASS", ImVec2(ImGui::GetContentRegionAvail().x, 20)))
            {
                std::string input = inputBuffer_getClass;
                SDK::UClass* czClass = SDK::UObject::FindObject<SDK::UClass>(input.c_str());
                if (czClass)
                {
                    static __int64 dwHandle = reinterpret_cast<__int64>(GetModuleHandle(0));
                    g_Console->printdbg("[+] Found [%s] -> 0x%llX\n", Console::Colors::yellow, input.c_str(), czClass->Class);
                }
                else
                    g_Console->printdbg("[!] CLASS [%s] NOT FOUND!\n", Console::Colors::red, input.c_str());

            }

            

            if (ImGui::Button("PRINT ENGINE GLOBALS", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {

                g_Console->printdbg("[+] [UNREAL ENGINE GLOBALS]\n"
                    "UWorld:\t\t\t0x%llX\n"
                    "ULocalPlayer:\t\t0x%llX\n"
                    "APalPlayerController:\t0x%llX\n"
                    "APalPlayerCharacter:\t0x%llX\n"
                    "APalPlayerState:\t0x%llX\n"
                    "UCharacterImpMan:\t0x%llX\n"
                    "UPalPlayerInventory:\t0x%llX\n"
                    "APalWeaponBase:\t\t0x%llX\n",
                    Console::Colors::yellow,
                    Config.gWorld,
                    Config.GetLocalPlayer(),
                    Config.GetPalPlayerController(),
                    Config.GetPalPlayerCharacter(),
                    Config.GetPalPlayerState(),
                    Config.GetCharacterImpManager(),
                    Config.GetInventoryComponent(),
                    Config.GetPlayerEquippedWeapon()
                );

            }

        }
        void TABPalSpawner()
        {
            static int level = 50,nameIdx,rank = 5,health = 10000, hunger = 10000,attk = 1000,defense = 1000,stamina = 1000,workspeed = 1000;
            static int passive1=64, passive2=55, passive3=50, passive4=39;
            static int skill1, skill2, skill3, skill4, skill5, skill6, skill7;
            static bool isBoss, isRare,isFemale,customStats,customSkills;
            static bool None, EmitFlame, Watering, Seeding, GenerateElectricity, Handcraft, Collection, Deforest, Mining, OilExtraction, ProductMedicine, Cool, Transport, MonsterFarm, Anyone, MAX;
            //const char* NameList = "Alpaca\0AmaterasuWolf\0Anubis\0BadCatgirl\0Baphomet\0Baphomet_Dark\0Bastet\0Bastet_Ice\0BeardedDragon\0BerryGoat\0BirdDragon\0BirdDragon_Ice\0BlackCentaur\0BlackFurDragon\0BlackGriffon\0BlackMetalDragon\0BlueberryFairy\0BlueDragon\0BluePlatypus\0Boar\0BrownRabbit\0CaptainPenguin\0Carbunclo\0CatBat\0CatMage\0CatVampire\0ChickenPal\0ColorfulBird\0CowPal\0CuteButterfly\0CuteFox\0CuteMole\0DarkAlien\0DarkCrow\0DarkMechaDragon\0DarkMutant\0DarkScorpion\0Deer\0Deer_Ground\0DreamDemon\0DrillGame\0Eagle\0ElecCat\0ElecLion\0ElecPanda\0FairyDragon\0FairyDragon_Water\0FeatherOstrich\0FengyunDeeper\0FireKirin\0FireKirin_Dark\0FlameBambi\0FlameBuffalo\0FlowerDinosaur\0FlowerDinosaur_Electric\0FlowerDoll\0FlowerRabbit\0FlyingManta\0FoxMage\0Ganesha\0Garm\0GhostBeast\0GhostRabbit\0GoldenHorse\0Gorilla\0GrassDragon\0GrassMammoth\0GrassMammoth_Ice\0GrassPanda\0GrassPanda_Electric\0GrassRabbitMan\0GuardianDog\0HadesBird\0HawkBird\0Hedgehog\0Hedgehog_Ice\0HerculesBeetle\0Horus\0IceDeer\0IceFox\0IceHorse\0IceHorse_Dark\0JetDragon\0Kelpie\0Kelpie_Fire\0KingAlpaca\0KingAlpaca_Ice\0KingBahamut\0Kirin\0Kitsunebi\0LavaGirl\0LazyCatfish\0LazyDragon\0LazyDragon_Electric\0LeafPrincess\0LilyQueen\0LilyQueen_Dark\0LittleBriarRose\0LizardMan\0LizardMan_Fire\0Manticore\0Manticore_Dark\0Monkey\0MopBaby\0MopKing\0Mutant\0NaughtyCat\0NegativeKoala\0NegativeOctopus\0NightBlueHorse\0NightFox\0NightLady\0Penguin\0PinkCat\0PinkKangaroo\0PinkLizard\0PinkRabbit\0PlantSlime\0QueenBee\0RaijinDaughter\0RedArmorBird\0RobinHood\0RobinHood_Ground\0Ronin\0SaintCentaur\0SakuraSaurus\0SakuraSaurus_Water\0ScorpionMan\0Serpent\0Serpent_Ground\0SharkKid\0SharkKid_Fire\0SheepBall\0SifuDog\0SkyDragon\0SoldierBee\0Suzaku\0Suzaku_Water\0SweetsSheep\0TentacleTurtle\0ThunderBird\0ThunderDog\0ThunderDragonMan\0Umihebi\0Umihebi_Fire\0VioletFairy\0VolcanicMonster\0VolcanicMonster_Ice\0VolcanoDragon\0WaterLizard\0WeaselDragon\0Werewolf\0WhiteMoth\0WhiteTiger\0Windchimes\0Windchimes_Ice\0WingGolem\0WizardOwl\0WoolFox\0Yeti\0Yeti_Grass\0GrassBoss\0ForestBoss\0DessertBoss\0VolcanoBoss\0SnowBoss";
            //const char* PassiveSkillList = "None\0 20% move Speed\0 30% MoveSpeed\0 20% Attk|20% Def|15% Movespeed\0 50% Work Speed\0 25% PlayerSpeed";
            //const wchar_t *PassiveSkillParams[] = {L"None", L"MoveSpeed_up_2", L"MoveSpeed_up_3", L"Legend", L"CraftSpeed_up2", L"TrainerWorkSpeed_UP_1"};
            //ImGui::Combo(":Pal Name", &nameIdx, database::pals_realnames,113);
            static char filter[30];
            
            static int currentIndex = 0;
            // Open combo box
            if (ImGui::BeginCombo(":Pal Name", database::pals_realnames[currentIndex]))
            {
                ImGui::InputText("Filter", filter, IM_ARRAYSIZE(filter));
                for (int i = 0; i < 113; ++i)
                {
                    // Apply the filter
                    std::string name_to_lower = database::pals_realnames[i];
                    std::string filter_to_lower = filter;

                    std::transform(name_to_lower.begin(), name_to_lower.end(), name_to_lower.begin(), ::tolower);
                    std::transform(filter_to_lower.begin(), filter_to_lower.end(), filter_to_lower.begin(), ::tolower);
                    if (filter_to_lower[0] != '\0' && (name_to_lower.find(filter_to_lower) == std::string::npos))
                        continue;
                    else
                    {
                        bool is_selected = (currentIndex == i);
                        if (ImGui::Selectable(database::pals_realnames[i], is_selected))
                        {
                            currentIndex = i;
                            nameIdx = i;
                        }
                            

                        if (is_selected)
                            ImGui::SetItemDefaultFocus(); // Set the initial focus when opening the combo
                    }
                }

                ImGui::EndCombo();
            }
            ImGui::InputInt("Rank (1-5)", &rank, 1, 5);
            ImGui::SliderInt("Level", &level, 1, 50);
            ImGui::Checkbox("Is Boss", &isBoss);
            ImGui::Checkbox("Is Shiny", &isRare);
            ImGui::Checkbox("Is Female", &isFemale);
            ImGui::Combo("Passive 1:", &passive1, database::passive_skill_name, 65); ImGui::SameLine(); ImGui::Text(database::passive_skill_descriptions[passive1]);
            ImGui::Combo("Passive 2:", &passive2, database::passive_skill_name, 65); ImGui::SameLine(); ImGui::Text(database::passive_skill_descriptions[passive2]);
            ImGui::Combo("Passive 3:", &passive3, database::passive_skill_name, 65); ImGui::SameLine(); ImGui::Text(database::passive_skill_descriptions[passive3]);
            ImGui::Combo("Passive 4:", &passive4, database::passive_skill_name, 65); ImGui::SameLine(); ImGui::Text(database::passive_skill_descriptions[passive4]);

            ImGui::Checkbox("Custom Stats:", &customStats);
            if (customStats)
            {
                ImGui::InputInt("Health", &health, 1, 1000000);
                ImGui::InputInt("Hunger", &hunger, 1, 1000000);
                ImGui::InputInt("attk", &attk, 1, 1000000);
                ImGui::InputInt("defense", &defense, 1, 1000000);
                ImGui::InputInt("stamina", &stamina, 1, 1000000);
                ImGui::InputInt("workspeed", &workspeed, 1, 1000000);
            }
            /*ImGui::Checkbox("Custom Skills:", &customSkills);
            if (customSkills)
            {
                ImGui::Combo("Equiped Skill 1", &skill1, NameList);
                ImGui::Combo("Equiped Skill 2", &skill2, NameList);
                ImGui::Combo("Equiped Skill 3", &skill3, NameList);
                ImGui::Combo("UnEquiped Skill 1", &skill4, NameList);
                ImGui::Combo("UnEquiped Skill 1", &skill5, NameList);
                ImGui::Combo("UnEquiped Skill 1", &skill6, NameList);
                ImGui::Combo("UnEquiped Skill 1", &skill7, NameList);

            }*/
            //ImGui::Text("SoTMaulder Menu");
            ImGui::Spacing();
            ImGui::Separator();
            

            if (ImGui::Button("Spawn This Pal", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25))) {
                SDK::UWorld* pWorld = Config.GetUWorld();
                SDK::UPalUtility* pUtility = Config.pPalUtility;
                SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();

                SDK::FGuid myPlayerId = Config.GetPalPlayerController()->GetPlayerUId();
                SDK::FGuid guid = SDK::UKismetGuidLibrary::GetDefaultObj()->NewGuid();

                static SDK::FPalIndividualCharacterSaveParameter initParameters;
                


                initParameters.NickName = SDK::FString(database::db_palnames[nameIdx]);
                initParameters.CharacterID = lib->Conv_StringToName(SDK::FString(database::pals_codenames[nameIdx]));

                initParameters.Rank = rank;
                initParameters.Level = level;
                initParameters.IsRarePal = isRare;
                initParameters.HP.Value = health*1000;
                initParameters.MaxHP.Value = health*1000;
                initParameters.MP.Value = stamina;
                initParameters.MaxMP.Value = stamina;
                initParameters.FullStomach = hunger;
                initParameters.MaxFullStomach = hunger;
                initParameters.SanityValue = 100;
                
                //initParameters.BaseCampWorkerEventProgressTime = 0.2f;
                //initParameters.PalReviveTimer = 0.001f;
                
                initParameters.CharacterClass = pUtility->GetNPCManager(pWorld)->NPCAIControllerBaseClass;

                //initParameters.Talent_Melee = attk;
                //initParameters.Talent_Shot = attk;
                //initParameters.UnusedStatusPoint = 5000;
                //initParameters.Talent_Defense = defense;
                //initParameters.Rank_Attack = attk;
                //initParameters.Rank_Defence = defense;
                initParameters.CraftSpeed = workspeed;
                initParameters.Gender = isFemale ? SDK::EPalGenderType::Female : SDK::EPalGenderType::Male;
                //SDK::TArray<SDK::FName> skills = {};
                
                
                if (passive1)initParameters.PassiveSkillList.Add(lib->Conv_StringToName(SDK::FString(database::passive_skill_list[passive1])));
                if (passive2)initParameters.PassiveSkillList.Add(lib->Conv_StringToName(SDK::FString(database::passive_skill_list[passive2])));
                if (passive3)initParameters.PassiveSkillList.Add(lib->Conv_StringToName(SDK::FString(database::passive_skill_list[passive3])));
                if (passive4)initParameters.PassiveSkillList.Add(lib->Conv_StringToName(SDK::FString(database::passive_skill_list[passive4])));

                //initParameters.EquipWaza.Add((SDK::EPalWazaID)1);
                
                //initParameters.MasteredWaza.Add((SDK::EPalWazaID)1);
                
                //initParameters.PassiveSkillList = skills;


                SDK::FPalWorkSuitabilityInfo tempData; 
                tempData.WorkSuitability = SDK::EPalWorkSuitability::MAX;
                tempData.Rank = 5000;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)1;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)2;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)3;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)4;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)5;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)6;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)7;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)8;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)9;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)10;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)11;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)12;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)13;
                initParameters.CraftSpeeds.Add(tempData);
                tempData.WorkSuitability = (SDK::EPalWorkSuitability)14;
                initParameters.CraftSpeeds.Add(tempData);

                SDK::FPalInstanceID instanceid = Config.GetPalPlayerCharacter()->CharacterParameterComponent->IndividualHandle->ID;
                instanceid.InstanceId = guid;

                SDK::FName Name = lib->Conv_StringToName(SDK::FString(L"None"));

                SDK::FNetworkActorSpawnParameters sp;
                sp.NetworkOwner = Config.GetPalPlayerCharacter();
                sp.Name = Name;
                sp.Owner = Config.GetPalPlayerCharacter();

                sp.SpawnLocation = Config.GetPalPlayerCharacter()->K2_GetActorLocation();
                sp.SpawnLocation.X += 100; sp.SpawnLocation.Y += 100;
                sp.SpawnRotation = Config.GetPalPlayerCharacter()->K2_GetActorRotation();
                sp.SpawnScale = { 0.2,0.2,0.2 };
                            
                
                sp.ControllerClass = pUtility->GetNPCManager(pWorld)->NPCAIControllerBaseClass.Get();//Config.GetPalPlayerCharacter()->AIControllerClass;

                sp.SpawnCollisionHandlingOverride = SDK::ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

                Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->CreateIndividualID_ToServer(initParameters, guid, myPlayerId.A);
                Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->CreateFixedIndividualID_ToServer(instanceid, initParameters, guid, myPlayerId.A);
                Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->SpawnIndividualActor_ToServer(instanceid, sp, guid);
                
            }
        }
        void TabEntityManager()
        {
            static bool FilterPlayer = true, FilterPals, FilterGuilds, FilterObjects;
            //if (ImGui::Begin("Manager", &g_GameVariables->m_ShowMenu, 96))
            {
                if (Config.GetUWorld() != NULL)
                {
                    ImGui::Checkbox("ENABLE ESP", &Config.IsESP);
                    ImGui::SameLine();
                    ImGui::Checkbox("Players", &FilterPlayer);
                    ImGui::SameLine();
                    ImGui::Checkbox("Pals", &FilterPals);
                    ImGui::SameLine();
                    ImGui::Checkbox("Guilds", &FilterGuilds);
                    ImGui::SameLine();
                    ImGui::Checkbox("Map Objects", &FilterObjects);
                    SDK::TArray<SDK::AActor*> T = Config.GetUWorld()->PersistentLevel->Actors;

                    ImGui::BeginChild("#EntityManager", ImVec2(0, 500), true);
                    for (int i = 0; i < T.Count(); i++)
                    {
                        SDK::AActor* Actor = T[i];

                        if (Actor == nullptr) continue;

                        SDK::APalCharacter* Character = (SDK::APalCharacter*)Actor;
                        std::string name;

                        bool Skip = true;

                        if (FilterPlayer && Actor->IsA(SDK::APalPlayerCharacter::StaticClass())) Skip = false;
                        if (FilterPals && Actor->IsA(SDK::APalCharacter::StaticClass())) Skip = false;
                        if (FilterGuilds && Actor->IsA(SDK::APalGuildInfo::StaticClass())) Skip = false;
                        if (FilterObjects && Actor->IsA(SDK::APalMapObject::StaticClass())) Skip = false;
                        if (Actor->IsA(SDK::APalCaptureJudgeObject::StaticClass())) Skip = false;

                        if (Skip) continue;

                        if (Actor->IsA(SDK::APalPlayerCharacter::StaticClass()))
                        {
                            if (!Character) { continue; }
                            SDK::FString fn;
                            Character->CharacterParameterComponent->GetNickname(&fn);
                            if (fn.IsValid())
                                name = fn.ToString();
                            else
                                name = "unknown";
                        }
                        else if (Actor->IsA(SDK::APalGuildInfo::StaticClass()))
                        {
                            name = Character->Name.GetRawString() + "[]" + ((SDK::APalGuildInfo*)Actor)->Guild->GuildName.ToString();
                            //name = name.substr(3);
                            //name = name.substr(0, name.length() - 13);
                        }

                        else
                        {
                            name = Character->Name.GetRawString();
                            name = name.substr(3);
                            name = name.substr(0, name.length() - 13);
                        }


                        ImGui::Text(name.c_str());
                        ImGui::SameLine();
                        ImGui::PushID(i);
                        if (ImGui::Button("TP"))
                        {
                            if (Config.GetPalPlayerCharacter() != NULL)
                            {
                                if (!Character) { continue; }
                                SDK::FVector vector = Character->K2_GetActorLocation();
                                AnyWhereTP(vector, Config.IsSafe);
                            }
                        }

                        if (Actor->IsA(SDK::APalCharacter::StaticClass())) {
                            ImGui::SameLine();
                            if (ImGui::Button("Kill"))
                            {
                                SendDamageToActor(Character, 99999999999);
                            }
                            ImGui::SameLine();
                            if (ImGui::Button("Set 1HP"))
                            {
                               Damage(Character, (Character->CharacterParameterComponent->GetHP().Value - 1) / 1000);
                            }
                            
                            if (!Actor->IsA(SDK::APalPlayerCharacter::StaticClass()))
                            {
                                ImGui::SameLine(); if (ImGui::Button("Clone")) {

                                    //Config.CloneCharacter = Character; 
                                    SDK::UKismetStringLibrary* lib = SDK::UKismetStringLibrary::GetDefaultObj();

                                    SDK::FGuid myPlayerId = Config.GetPalPlayerController()->GetPlayerUId();
                                    SDK::FGuid guid = SDK::UKismetGuidLibrary::GetDefaultObj()->NewGuid();

                                    SDK::FPalIndividualCharacterSaveParameter initParameters;
                                    initParameters = Character->GetCharacterParameterComponent()->GetIndividualParameter()->GetSaveParameter();
                                    /*Config.CloneParameters = *(SDK::FPalIndividualCharacterSaveParameter*)&initParameters;
                                    //initParameters.Level = 50;
                                    //initParameters.PassiveSkillList[0] = lib->Conv_StringToName(SDK::FString(L"Legend"));
                                    //SDK::APalPlayerCharacter* pPalCharacter = Config.GetPalPlayerCharacter();
                                    // = pPalCharacter->GetCharacterParameterComponent()->GetIndividualParameter()->IndividualId;
                                    auto count = initParameters.CraftSpeedRates.Values.Count();
                                    for(int i=0;i<count;i++)
                                    { 
                                        auto name = initParameters.CraftSpeedRates.Values[i].Key.ToString().c_str();
                                        auto value = initParameters.CraftSpeedRates.Values[i].Value;
                                        g_Console->printdbg("\n[+] name: %s\0 value: %f [+]", Console::Colors::green, name, value);
                                    }*/
                                    
                                    SDK::FPalInstanceID instanceid = Config.GetPalPlayerCharacter()->CharacterParameterComponent->IndividualHandle->ID;
                                    instanceid.InstanceId = guid;
                                                                        
                                    SDK::FName Name = lib->Conv_StringToName(SDK::FString(L"None"));

                                    SDK::FNetworkActorSpawnParameters sp;
                                    sp.NetworkOwner = Config.GetPalPlayerCharacter();
                                    sp.Name = Name;
                                    sp.Owner = Config.GetPalPlayerCharacter();

                                    sp.SpawnLocation = Config.GetPalPlayerCharacter()->K2_GetActorLocation();
                                    sp.SpawnLocation.X += 100; sp.SpawnLocation.Y += 100;
                                    sp.SpawnRotation = Config.GetPalPlayerCharacter()->K2_GetActorRotation();
                                    sp.SpawnScale = { 1.0,1.0,1.0 };

                                    SDK::UWorld* pWorld = Config.GetUWorld();
                                    SDK::UPalUtility* pUtility = Config.pPalUtility;
                                    sp.ControllerClass = pUtility->GetNPCManager(pWorld)->NPCAIControllerBaseClass.Get();//Character->AIControllerClass;
                                    //Config.CloneController = Character->AIControllerClass;
                                    sp.SpawnCollisionHandlingOverride = SDK::ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

                                    Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->CreateIndividualID_ToServer(initParameters, guid, myPlayerId.A);
                                    Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->CreateFixedIndividualID_ToServer(instanceid, initParameters, guid, myPlayerId.A);
                                    Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->SpawnIndividualActor_ToServer(instanceid, sp, guid);
                                    //Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->SpawnPhantomActor_SyncCheck(instanceid,0, guid);
                                    //Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->SpawnPhantomActor_ToServer(instanceid,sp, guid);
                                }
                            }
                            
                        }
                            
                        if (Actor->IsA(SDK::APalCharacter::StaticClass())) {
                            ImGui::SameLine();
                            if (ImGui::Button("MaxHP")) {
                                Damage(Character, -2147483647);
                            }
                        }
                        if (Character->IsA(SDK::APalPlayerCharacter::StaticClass()))
                        {
                            ImGui::SameLine();
                            if (ImGui::Button("BossFight"))
                            {
                                if (Config.GetPalPlayerCharacter() != NULL)
                                {
                                    auto controller = Config.GetPalPlayerCharacter()->GetPalPlayerController();
                                    
                                    if (controller != NULL)
                                    {
                                        SDK::FPalSyncTeleportRequestParameter tpParam;
                                        tpParam.bIsFadeOutSkip = true;
                                        tpParam.Location = { -321596.265032, 211085,-64908.850078047355 };
                                        //tpParam.Location = { -321248.80, 208959.95, 115.59 };
                                        tpParam.Rotation = 0;
                                        tpParam.bIsFadeOutSkip = true;
                                        
                                        controller->Transmitter->BossBattle->RequestBossBattleEntry_ToServer(SDK::EPalBossType::ElectricBoss, (SDK::APalPlayerCharacter*)Character);
                                        controller->Transmitter->BossBattle->RequestBossBattleStart_ToServer(SDK::EPalBossType::ElectricBoss, (SDK::APalPlayerCharacter*)Character);
                                        static_cast<SDK::APalPlayerState*>(Character->PlayerState)->GetSyncTeleportComp()->RequestSyncTeleportStart_ToServer(tpParam);
                                        static_cast<SDK::APalPlayerState*>(Character->PlayerState)->GetSyncTeleportComp()->RequestSyncTeleportMove_ToServer();
                                        static_cast<SDK::APalPlayerState*>(Character->PlayerState)->GetSyncTeleportComp()->RequestSyncTeleportEnd_ToServer();
                                        
                                        //controller->CutsceneComponent->SetAutoActivate(true);
                                        controller->CutsceneComponent->PlayCutsceneToServer();
                                    }
                                        
                                }
                            }
                        }
                        
                        if (Actor->IsA(SDK::APalPlayerCharacter::StaticClass())) {
                            ImGui::SameLine();
                            if (ImGui::Button("JoinGuild")) {
                                SDK::FGuid myPlayerId = Config.GetPalPlayerController()->GetPlayerUId();
                                SDK::FGuid playerId = SDK::UPalUtility::GetDefaultObj()->GetPlayerUIDByActor(Actor);

                                //g_Console->printdbg("\n\n[+] myPlayer GUID: %x\player GUID: %x [+]\n\n", Console::Colors::green, myPlayerId, playerId);

                                Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->Group->RequestJoinGuildForPlayer_ToServer(myPlayerId, playerId);
                            }
                        }
                        if (Actor->IsA(SDK::APalPlayerCharacter::StaticClass())) {
                            ImGui::SameLine();
                            if (ImGui::Button("JoinMe")) {
                                SDK::FGuid myPlayerId = Config.GetPalPlayerController()->GetPlayerUId();
                                SDK::FGuid playerId = SDK::UPalUtility::GetDefaultObj()->GetPlayerUIDByActor(Actor);

                                //g_Console->printdbg("\n\n[+] myPlayer GUID: %x\player GUID: %x [+]\n\n", Console::Colors::green, myPlayerId, playerId);

                                Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->Group->RequestJoinGuildForPlayer_ToServer(playerId, myPlayerId);
                            }
                        }
                        if (Actor->IsA(SDK::APalPlayerCharacter::StaticClass())) {
                            ImGui::SameLine();
                            if (ImGui::Button("StealLeader")) {
                                SDK::FGuid myPlayerId = Config.GetPalPlayerController()->GetPlayerUId();
                                SDK::FGuid playerId = SDK::UPalUtility::GetDefaultObj()->GetPlayerUIDByActor(Actor);


                                g_Console->printdbg("\n\n[+] myPlayer GUID: %x\player GUID: %x [+]\n\n", Console::Colors::green, myPlayerId, playerId);

                                //Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->Group->RequestJoinGuildForPlayer_ToServer(guid1, guid2);
                                Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->Group->RequestChangeGuildAdmin_ToServer(playerId, myPlayerId);
                            }
                        }
                        if (Actor->IsA(SDK::APalMapLevelObject::StaticClass())) {
                            ImGui::SameLine();
                            if (ImGui::Button("Destroy")) {
                                SDK::APalMapLevelObject* Object = (SDK::APalMapLevelObject*)Actor;

                                Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->MapObject->RequestDismantleObject_ToServer(Object->LevelObjectInstanceId);
                            }
                        }
                        if (Actor->IsA(SDK::APalCharacter::StaticClass())) {
                            ImGui::SameLine();
                            if (ImGui::Button("Freeze")) {
                                SDK::FStatusDynamicParameter statusParam;
                                Character->StatusComponent->AddStatus_ToServer(SDK::EPalStatusID::Freeze, statusParam, 256);
                            }
                        }
                        if (Character->IsA(SDK::APalPlayerCharacter::StaticClass()))
                        {
                            ImGui::SameLine();
                            if (ImGui::Button("Steal Name"))
                            {
                                if (Config.GetPalPlayerCharacter() != NULL)
                                {
                                    auto controller = Config.GetPalPlayerCharacter()->GetPalPlayerController();
                                    if (controller != NULL)
                                    {
                                        auto player = (SDK::APalPlayerCharacter*)Character;
                                        SDK::FString fakename;
                                        player->CharacterParameterComponent->GetNickname(&fakename);
                                        Config.GetPalPlayerCharacter()->GetPalPlayerController()->Transmitter->NetworkIndividualComponent->UpdateCharacterNickName_ToServer(Config.GetPalPlayerCharacter()->CharacterParameterComponent->IndividualHandle->ID, fakename);
                                    }
                                }
                            }
                        }


                        ImGui::PopID();
                    }
                    ImGui::EndChild();
                }
            }
            //ImGui::End();
        }
	}

	void Menu::Draw()
	{

		if (g_GameVariables->m_ShowMenu)
			MainMenu();

		if (g_GameVariables->m_ShowHud)
			HUD(&g_GameVariables->m_ShowHud);

		if (g_GameVariables->m_ShowDemo)
			ImGui::ShowDemoWindow();
	}
    inline static std::string a_replaceAll(std::string subject, const std::string& search,
        const std::string& replace) {
        size_t pos = 0;
        while ((pos = subject.find(search, pos)) != std::string::npos) {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
        return subject;
    }
    
	
    void Menu::MainMenu()
	{
        if (!g_GameVariables->m_ShowDemo)
            Styles::InitStyle();

        if (g_Menu->dbg_RAINBOW_THEME) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(g_Menu->dbg_RAINBOW));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(g_Menu->dbg_RAINBOW));
            ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(g_Menu->dbg_RAINBOW));
        }
        if (!ImGui::Begin("PalWorld ModMenu", &g_GameVariables->m_ShowMenu, 96))
        {
            ImGui::End();
            return;
        }
        if (g_Menu->dbg_RAINBOW_THEME) {
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
        }
        
        ImGuiContext* pImGui = GImGui;

        //  Display Menu Content
        //Tabs::TABMain();

        //ImGui::Text("W.I.P. Some Functions Might Not work.");

        if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Player"))
            {
                Tabs::TABPlayer();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Unlockers"))
            {
                Tabs::TABExploit();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Misc"))
            {
                Tabs::TABMisc();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("TELEPORT"))
            {
                Tabs::TABTeleporter();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Item Spawner"))
            {
                Tabs::TABItemSpawner();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Pal Spawner"))
            {
                Tabs::TABPalSpawner();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Cage Spawner"))
            {
                Tabs::TABCageSpawner();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Entity Manager"))
            {
                Tabs::TabEntityManager();
                ImGui::EndTabItem();
            }

#if DEBUG
            if (ImGui::BeginTabItem("DEBUG"))
            {
                Tabs::TABDebug();
                ImGui::EndTabItem();
            }
#endif
            if (ImGui::BeginTabItem("Info"))
            {
                Tabs::TABConfig();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();



        
	}

	void Menu::HUD(bool* p_open)
	{
        
        ImGui::SetNextWindowPos(g_D3D11Window->pViewport->WorkPos);
        ImGui::SetNextWindowSize(g_D3D11Window->pViewport->WorkSize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, NULL);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));
        if (!ImGui::Begin("##HUDWINDOW", (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs))
        {
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();
            ImGui::End();
            return;
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();

        auto ImDraw = ImGui::GetWindowDrawList();
        auto draw_size = g_D3D11Window->pViewport->WorkSize;
        auto center = ImVec2({ draw_size.x * .5f, draw_size.y * .5f });
        auto top_center = ImVec2({ draw_size.x * .5f, draw_size.y * 0.0f });

        if (Config.IsESP)
            ESP();

        if (Config.isDebugESP)
            ESP_DEBUG(Config.mDebugESPDistance);

        if (Config.db_waypoints.size() > 0)
            RenderWaypointsToScreen();

        ImGui::End();
	}

    void Menu::Loops()
    {

        if ((GetAsyncKeyState(VK_F4) & 1))//spectate
        {
            SDK::APalPlayerCharacter* p_appc = Config.GetPalPlayerCharacter();
            if (p_appc != NULL)
            {
                if (Config.GetPalPlayerCharacter()->GetPalPlayerController() != NULL)
                {
                    Config.spec = !Config.spec;
                    Config.GetPalPlayerCharacter()->SetSpectatorMode(Config.spec);
                    
                }
            }
        }
        
        if ((GetAsyncKeyState(VK_F2) & 1))
            TeleportToMapMarker();
        //  Respawn
        if ((GetAsyncKeyState(VK_F5) & 1))
            ReviveLocalPlayer();
            

        //  Revive Player
        if ((GetAsyncKeyState(VK_F6) & 1))
            RespawnLocalPlayer(Config.IsSafe);

        static bool restSpeedHack = false;
        if (Config.IsSpeedHack)
        {
            restSpeedHack = true;
            SpeedHack(Config.SpeedModiflers);
        }
        else if (restSpeedHack)
        {
            restSpeedHack = false;
            SpeedHack(1.0f); // Turn off the feature
        }

        //  
        static bool restAttModifier = false;
        if (Config.IsAttackModiler)
        {
            restAttModifier = true;
            SetPlayerAttackParam(Config.DamageUp*10);
        }
        else if (restAttModifier)
        {
            restAttModifier = false;
            SetPlayerAttackParam(1); // Turn off the feature
        }

        //  
        static bool restDefModifier = false;
        if (Config.IsDefuseModiler)
        {
            restDefModifier = true;
            SetPlayerDefenseParam(Config.DefuseUp*10);
        }
        else if (restDefModifier)
        {
            restDefModifier = false;
            SetPlayerDefenseParam(1); // Turn off the feature
        }
        
        //
        if (Config.IsTeleportAllToXhair)
            TeleportAllPalsToCrosshair(Config.mDebugEntCapDistance);
        
        //
        if (Config.IsDeathAura)
            DeathAura(Config.mDeathAuraAmount, Config.mDeathAuraDistance, true);

        //  
        if (Config.IsInfStamina)
            ResetStamina();

        if (Config.NoReload)
            NoReload();
        //  
        if (Config.GetPalPlayerCharacter() != NULL)
        {
            if (Config.GetPalPlayerCharacter()->ShooterComponent != NULL && Config.GetPalPlayerCharacter()->ShooterComponent->GetHasWeapon() != NULL && Config.GetPalPlayerCharacter()->ShooterComponent->CanShoot())
            {
                Config.GetPalPlayerCharacter()->ShooterComponent->GetHasWeapon()->IsRequiredBullet = !Config.IsInfinAmmo;
            }
        }

        //
        if (Config.IsMuteki)
        {
            if (Config.GetPalPlayerCharacter() && Config.GetPalPlayerCharacter()->CharacterParameterComponent && Config.GetPalPlayerCharacter()->CharacterParameterComponent->IndividualParameter)
            {
                if (Config.GetPalPlayerCharacter()->CharacterParameterComponent->IndividualParameter->GetHP().Value < INT_MAX)
                    Config.GetPalPlayerCharacter()->ReviveCharacter_ToServer(SDK::FFixedPoint(INT_MAX));
            }
        }
    }
}