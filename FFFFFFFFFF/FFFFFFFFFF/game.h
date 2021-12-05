#pragma once

#include "defs.h"
#include "vector.h"
#include "offset.h"
#include <thread>
#include "base.h"
#pragma warning(once : 4996)
#include "Text.h"
#include <iomanip>
#include <ctime>
#include <iostream>
#include <chrono>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_impl_win32.h"
#include <vector>

#include <xor.h>
using namespace base;
namespace game
{
   
    template <typename T> static T read(uintptr_t pid, uintptr_t address) {
        return d4riverhaknaop::read<T>(pid, address);
    }

    template <typename T> static void write(uintptr_t pid, uintptr_t address, T& buffer) {
        return d4riverhaknaop::write<T>(pid, address, buffer);
    }


    static bool hmamhamamahm{ true };
    static bool goakna{ true };
    static bool hamghemag{ true };
    static bool d_h3adspz{ true };
    ImFont* SkeetFont;
    static bool hangamrgmam{ true };
    int numberwtf = 8; 
    static bool lines{ true };
    static bool health2distance{ true };
    static bool b0neaepa{ true };
    static bool teqrmasmrfa{ true };

    static int g_local_team_id;

    static uintptr_t g_local_player_controller;
    static uintptr_t g_local_player_pawn;
    static uintptr_t g_local_damage_handler;
    static uintptr_t g_camera_manager;

    static std::vector<Enemy> enemy_collection;

    static ImU32 g_rrr_color = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 0.2f, 1.f, 1.f));
    static ImU32 g_rrr_color2 = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 0.2f, 1.f, 1.f));
    static ImU32 g_rrr_color3 = ImGui::ColorConvertFloat4ToU32(ImVec4(1, 0, 0.F, 1));
    static ImU32 g_color_white = ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1));

    static HANDLE handleOffset;

    Vector3 getBonePosition(Enemy enemy, int index)
    {
        size_t size = sizeof(FTransform);
        FTransform firstBone = read<FTransform>(g_pid, enemy.bone_array_ptr + (size * index));
        FTransform componentToWorld = read<FTransform>(g_pid, enemy.mesh_ptr + offset::component_to_world);
        D3DMATRIX matrix = MatrixMultiplication(firstBone.ToMatrixWithScale(), componentToWorld.ToMatrixWithScale());
        return Vector3(matrix._41, matrix._42, matrix._43);
    }

    void renderBoneLine(Vector3 first_bone_position, Vector3 second_bone_position, Vector3 position, Vector3 rotation, float fov)
    {
        Vector2 first_bone_screen_position = worldToScreen(first_bone_position, position, rotation, fov);
        ImVec2 fist_screen_position = ImVec2(first_bone_screen_position.x, first_bone_screen_position.y);
        Vector2 second_bone_screen_position = worldToScreen(second_bone_position, position, rotation, fov);
        ImVec2 second_screen_position = ImVec2(second_bone_screen_position.x, second_bone_screen_position.y);
        ImGui::GetOverlayDrawList()->AddLine(fist_screen_position, second_screen_position, g_rrr_color2);
    }

    void renderBox(Vector2 head_at_screen, float distance_modifier)
    {
        int head_x = head_at_screen.x;
        int head_y = head_at_screen.y;
        int start_x = head_x - 35 / distance_modifier;
        int start_y = head_y - 15 / distance_modifier;
        int end_x = head_x + 35 / distance_modifier;
        int end_y = head_y + 155 / distance_modifier;
        ImGui::GetOverlayDrawList()->AddRect(ImVec2(start_x, start_y), ImVec2(end_x, end_y), g_rrr_color3);
    }

    void renderBones(Enemy enemy, Vector3 position, Vector3 rotation, float fov)
    {
        Vector3 head_position = getBonePosition(enemy, 8);
        Vector3 neck_position;
        Vector3 chest_position = getBonePosition(enemy, 6);
        Vector3 l_upper_arm_position;
        Vector3 l_fore_arm_position;
        Vector3 l_hand_position;
        Vector3 r_upper_arm_position;
        Vector3 r_fore_arm_position;
        Vector3 r_hand_position;
        Vector3 stomach_position = getBonePosition(enemy, 4);
        Vector3 pelvis_position = getBonePosition(enemy, 3);
        Vector3 l_thigh_position;
        Vector3 l_knee_position;
        Vector3 l_foot_position;
        Vector3 r_thigh_position;
        Vector3 r_knee_position;
        Vector3 r_foot_position;
        if (enemy.bone_count == 102) { // MALE
            neck_position = getBonePosition(enemy, 19);

            l_upper_arm_position = getBonePosition(enemy, 21);
            l_fore_arm_position = getBonePosition(enemy, 22);
            l_hand_position = getBonePosition(enemy, 23);

            r_upper_arm_position = getBonePosition(enemy, 47);
            r_fore_arm_position = getBonePosition(enemy, 48);
            r_hand_position = getBonePosition(enemy, 49);

            l_thigh_position = getBonePosition(enemy, 75);
            l_knee_position = getBonePosition(enemy, 76);
            l_foot_position = getBonePosition(enemy, 78);

            r_thigh_position = getBonePosition(enemy, 82);
            r_knee_position = getBonePosition(enemy, 83);
            r_foot_position = getBonePosition(enemy, 85);
        }
        else if (enemy.bone_count == 99) { // FEMALE
            neck_position = getBonePosition(enemy, 19);

            l_upper_arm_position = getBonePosition(enemy, 21);
            l_fore_arm_position = getBonePosition(enemy, 40);
            l_hand_position = getBonePosition(enemy, 42);

            r_upper_arm_position = getBonePosition(enemy, 46);
            r_fore_arm_position = getBonePosition(enemy, 65);
            r_hand_position = getBonePosition(enemy, 67);

            l_thigh_position = getBonePosition(enemy, 78);
            l_knee_position = getBonePosition(enemy, 75);
            l_foot_position = getBonePosition(enemy, 77);

            r_thigh_position = getBonePosition(enemy, 80);
            r_knee_position = getBonePosition(enemy, 82);
            r_foot_position = getBonePosition(enemy, 84);
        }
        else if (enemy.bone_count == 103) { // BOT
            neck_position = getBonePosition(enemy, 9);

            l_upper_arm_position = getBonePosition(enemy, 33);
            l_fore_arm_position = getBonePosition(enemy, 30);
            l_hand_position = getBonePosition(enemy, 32);

            r_upper_arm_position = getBonePosition(enemy, 58);
            r_fore_arm_position = getBonePosition(enemy, 55);
            r_hand_position = getBonePosition(enemy, 57);

            l_thigh_position = getBonePosition(enemy, 63);
            l_knee_position = getBonePosition(enemy, 65);
            l_foot_position = getBonePosition(enemy, 69);

            r_thigh_position = getBonePosition(enemy, 77);
            r_knee_position = getBonePosition(enemy, 79);
            r_foot_position = getBonePosition(enemy, 83);
        }
        else {
            return;
        }

        renderBoneLine(head_position, neck_position, position, rotation, fov);
        renderBoneLine(neck_position, chest_position, position, rotation, fov);
        renderBoneLine(neck_position, l_upper_arm_position, position, rotation, fov);
        renderBoneLine(l_upper_arm_position, l_fore_arm_position, position, rotation, fov);
        renderBoneLine(l_fore_arm_position, l_hand_position, position, rotation, fov);
        renderBoneLine(neck_position, r_upper_arm_position, position, rotation, fov);
        renderBoneLine(r_upper_arm_position, r_fore_arm_position, position, rotation, fov);
        renderBoneLine(r_fore_arm_position, r_hand_position, position, rotation, fov);
        renderBoneLine(chest_position, stomach_position, position, rotation, fov);
        renderBoneLine(stomach_position, pelvis_position, position, rotation, fov);
        renderBoneLine(pelvis_position, l_thigh_position, position, rotation, fov);
        renderBoneLine(l_thigh_position, l_knee_position, position, rotation, fov);
        renderBoneLine(l_knee_position, l_foot_position, position, rotation, fov);
        renderBoneLine(pelvis_position, r_thigh_position, position, rotation, fov);
        renderBoneLine(r_thigh_position, r_knee_position, position, rotation, fov);
        renderBoneLine(r_knee_position, r_foot_position, position, rotation, fov);
    }
    static const char* keyNames[] =
    {
        "",
        "Left Mouse",
        "Right Mouse",
        "Cancel",
        "Middle Mouse",
        "Mouse 5",
        "Mouse 4",
        "",
        "Backspace",
        "Tab",
        "",
        "",
        "Clear",
        "Enter",
        "",
        "",
        "Shift",
        "Control",
        "Alt",
        "Pause",
        "Caps",
        "",
        "",
        "",
        "",
        "",
        "",
        "Escape",
        "",
        "",
        "",
        "",
        "Space",
        "Page Up",
        "Page Down",
        "End",
        "Home",
        "Left",
        "Up",
        "Right",
        "Down",
        "",
        "",
        "",
        "Print",
        "Insert",
        "Delete",
        "",
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z",
        "",
        "",
        "",
        "",
        "",
        "Numpad 0",
        "Numpad 1",
        "Numpad 2",
        "Numpad 3",
        "Numpad 4",
        "Numpad 5",
        "Numpad 6",
        "Numpad 7",
        "Numpad 8",
        "Numpad 9",
        "Multiply",
        "Add",
        "",
        "Subtract",
        "Decimal",
        "Divide",
        "F1",
        "F2",
        "F3",
        "F4",
        "F5",
        "F6",
        "F7",
        "F8",
        "F9",
        "F10",
        "F11",
        "F12",
    };
    namespace hotkeys
    {
        int a1mk3yt;
        int airstuckey;
    }
    static int keystatus = 0;
    static int realkey = 0;
    bool GetKey(int key)
    {
        realkey = key;
        return true;
    }
    void ChangeKey(void* blank)
    {
        keystatus = 1;
        while (true)
        {
            for (int i = 0; i < 0x87; i++)
            {
                if (GetKeyState(i) & 0x8000)
                {
                    hotkeys::a1mk3yt = i;
                    keystatus = 0;
                    return;
                }
            }
        }
    }


    void NormalizeAngles(Vector3& angle)
    {
        while (angle.x > 89.0f)
            angle.x -= 180.f;

        while (angle.x < -89.0f)
            angle.x += 180.f;

        while (angle.y > 180.f)
            angle.y -= 360.f;

        while (angle.y < -180.f)
            angle.y += 360.f;
    }

    Vector3 CaadadalcAngle(Vector3 src, Vector3 dst)
    {
        Vector3 angle;
        Vector3 delta = Vector3((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

        double hyp = sqrtf(delta.x * delta.x + delta.y * delta.y);

        angle.x = atanf(delta.z / hyp) * (180.0f / hyp);
        angle.y = atanf(delta.y / delta.x) * (180.0f / M_PI);
        angle.z = 0;
        if (delta.x >= 0.0) angle.y += 180.0f;

        return angle;
    }

    float GetFov(const Vector3 viewAngle, const Vector3 aimAngle)
    {
        Vector3 Delta = Vector3(aimAngle.x - viewAngle.x, aimAngle.y - viewAngle.y, aimAngle.z - viewAngle.z);
        NormalizeAngles(Delta);
        return sqrt(pow(Delta.x, 2.0f) + pow(Delta.y, 2.0f));
    }


    static float lmao = 1;
    int GetBestAimEntity(float* flFoV)
    {
        Vector3 camera_position = read<Vector3>(g_pid, g_camera_manager + offset::camera_position);
        std::vector<Enemy> local_enemy_collection = enemy_collection;
        if (local_enemy_collection.empty()) {
            return -1;
        }
        int dwIndex = -1;

        auto playerControllerViewAngles = read<Vector3>(g_pid, g_local_player_controller + 0x420);
        for (int i = 0; i < local_enemy_collection.size(); i++) {
            Enemy enemy = local_enemy_collection[i];
            float health = read<float>(g_pid, enemy.damage_handler_ptr + offset::health);

            Vector3 neck_position = getBonePosition(enemy, 7); // 8 = head bone
            Vector3 root_position = read<Vector3>(g_pid, enemy.root_component_ptr + offset::root_position);
            if (neck_position.z <= root_position.z) {
                continue;
            }

            if (hamghemag) {
                float last_render_time = read<float>(g_pid, enemy.mesh_ptr + offset::last_render_time);
                float last_submit_time = read<float>(g_pid, enemy.mesh_ptr + offset::last_submit_time);
                bool is_visible = last_render_time + 0.06F >= last_submit_time;
                bool dormant = read<bool>(g_pid, enemy.actor_ptr + offset::dormant);
                if (!dormant || !is_visible) {
                    continue;
                }
                Vector3 pLocalCameraRot = read<Vector3>(g_pid, g_local_player_controller + 0x420);
                // printf("pLocalCameraRot Pos : [%f] [%f] \n", pLocalCameraRot.x, pLocalCameraRot.y);
                Vector3 vecCaclculatedAngles = CalcAngle(camera_position, neck_position);
                Vector3 angleEx = CaadadalcAngle(camera_position, neck_position);
                Vector3 fin = Vector3(vecCaclculatedAngles.y, angleEx.y, 0);

                //  printf("vecCaclculatedAngl  : [%f] [%f]\n", vecCaclculatedAngles.x, vecCaclculatedAngles.y);
                //  Vector3 camera_rotation = read<Vector3>(g_pid, g_camera_manager + offset::camera_rotation);
             //  write<Vector3>(g_pid, g_local_player_controller + 0x420, vecCaclculatedAngles);
                float temp = GetFov(pLocalCameraRot, fin);
                //  printf("[%d]Entity :%f\n", i,temp);
                if (temp < *flFoV)
                {
                    dwIndex = i;
                    *flFoV = temp;
                }

            }

        }
        return dwIndex;
    }

    float smo0tie = 7;
    float smo0tie2 = 7;
    float fart = 6;
    void azmzot()
    {
        try
        {
            if (goakna) {
            Vector3 camera_position = read<Vector3>(g_pid, g_camera_manager + offset::camera_position);
            Vector3 camera_rotation = read<Vector3>(g_pid, g_camera_manager + offset::camera_rotation);
            float fOv = fart;
            int dwIndex = GetBestAimEntity(&fOv);
            if (dwIndex < 0) return;
            Vector3 pLocalCameraRot = read<Vector3>(g_pid, g_local_player_controller + 0x420);
            if (GetAsyncKeyState(hotkeys::a1mk3yt))
            {
                Enemy enemy = enemy_collection[dwIndex];
                Vector3 neck_position = getBonePosition(enemy, numberwtf); // 8 = head bone
                Vector3 root_position = read<Vector3>(g_pid, enemy.root_component_ptr + offset::root_position);
                if (neck_position.z <= root_position.z) {
                    return;
                }
                camera_position = read<Vector3>(g_pid, g_camera_manager + offset::camera_position);
                Vector3 localView = read<Vector3>(g_pid, g_local_player_controller + 0x420);
                Vector3 vecCaclculatedAngles = CalcAngle(camera_position, neck_position);
                Vector3 angleEx = CaadadalcAngle(camera_position, neck_position);
                Vector3 fin = Vector3(vecCaclculatedAngles.y, angleEx.y, 0);
                Vector3 delta = fin - localView;
                NormalizeAngles(delta);
                Vector3 TargetAngle = localView + (delta / smo0tie);
                NormalizeAngles(TargetAngle);

                // printf("pLocalCameraRot Pos : [%f] [%f] \n", pLocalCameraRot.x, pLocalCameraRot.y);
                // printf("vecCaclculatedAngl  : [%f] [%f]\n", fin.x, fin.y);
                Vector3 camera_rotation = read<Vector3>(g_pid, g_camera_manager + offset::camera_rotation);
                write<Vector3>(g_pid, g_local_player_controller + 0x420, TargetAngle);
                float temp = GetFov(pLocalCameraRot, vecCaclculatedAngles);
                if (temp > fOv)
                {
                    //break;
                }
                Sleep(1);
            }
        }
        }
        catch (std::exception e)
        {
            printf("ERROR : %s\n", e.what());
        }
    }


    void re3ndrezp()
    {
        std::vector<Enemy> local_enemy_collection = enemy_collection;

        if (local_enemy_collection.empty())
        {
            return;
        }


        Vector3 camera_position = read<Vector3>(g_pid, g_camera_manager + offset::camera_position);
        Vector3 camera_rotation = read<Vector3>(g_pid, g_camera_manager + offset::camera_rotation);
        float camera_fov = read<float>(g_pid, g_camera_manager + offset::camera_fov);

        for (int i = 0; i < local_enemy_collection.size(); i++)
        {
            Enemy enemy = local_enemy_collection[i];
            float health = read<float>(g_pid, enemy.damage_handler_ptr + offset::health);

            if (enemy.actor_ptr == g_local_player_pawn || health <= 0 || !enemy.mesh_ptr)
            {
                continue;
            }

            Vector3 head_position = getBonePosition(enemy, 7); // 8 = head bone
            Vector3 root_position = read<Vector3>(g_pid, enemy.root_component_ptr + offset::root_position);
            Vector2 vHeadBoneOut = worldToScreen(Vector3(head_position.x, head_position.y, head_position.z), camera_position, camera_rotation, camera_fov);
            Vector2 vRootBoneOut = worldToScreen(head_position, camera_position, camera_rotation, camera_fov);

            if (head_position.z <= root_position.z)
            {
                continue;
            }

            if (hamghemag)
            {
                float last_render_time = read<float>(g_pid, enemy.mesh_ptr + offset::last_render_time);
                float last_submit_time = read<float>(g_pid, enemy.mesh_ptr + offset::last_submit_time);
                bool is_visible = last_render_time + 0.06F >= last_submit_time;
                bool dormant = read<bool>(g_pid, enemy.actor_ptr + offset::dormant);

                if (!dormant || !is_visible)
                {
                    continue;
                }
            }

            Vector2 head_at_screen_vec = worldToScreen(head_position, camera_position, camera_rotation, camera_fov);
            ImVec2 head_at_screen = ImVec2(head_at_screen_vec.x, head_at_screen_vec.y);
            float distance_modifier = camera_position.Distance(head_position) * 0.001F;

            if (b0neaepa)
            {
                renderBones(enemy, camera_position, camera_rotation, camera_fov);
            }

            if (d_h3adspz)
            {
                Vector3 vHeadBone = getBonePosition(enemy, 8);
                Vector3 vRootBone = getBonePosition(enemy, 0);

                Vector2 vHeadBoneOut = worldToScreen(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z), camera_position, camera_rotation, camera_fov);
                Vector2 vRootBoneOut = worldToScreen(vRootBone, camera_position, camera_rotation, camera_fov);
                float BoxHeight = abs(vHeadBoneOut.y - vRootBoneOut.y);
                float BoxWidth = BoxHeight / 0.1f;
                DrawCircleFilled(vRootBoneOut.x, vHeadBoneOut.y, BoxHeight / 7, &Col.green);
            }

            if (health2distance) {
               char vida[100];
              sprintf(vida, "H:%2.f", health, 3.F, 8);
                char neme[64];
                sprintf_s(neme, "[%2.fm]", camera_position.Distance(head_position) * 0.01F);
                int head_x = head_at_screen.x;
                int head_y = head_at_screen.y;
                int start_x = head_x - 35 / distance_modifier;
                int start_y = head_y - 15 / distance_modifier;
                int hp_x = head_x + 10 / distance_modifier;
                int hp_y = head_y + -40 / distance_modifier;
                int dis_x = head_x - 50 / distance_modifier;
                int dis_y = head_y + -40 / distance_modifier;
                DrawString(13.0f, dis_x, dis_y - 5, &Col.white_, true, true, neme);
              //  ImGui::GetOverlayDrawList()->AddText(ImVec2(hp_x, hp_y), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 0, 0.F, 5)), (vida));
               // ImGui::GetOverlayDrawList()->AddText(ImVec2(dis_x, dis_y), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 0, 0.F, 5)), (neme));

            }
            if (hangamrgmam) {
                Vector3 vHeadBone = getBonePosition(enemy, 8);
                Vector3 vRootBone = getBonePosition(enemy, 0);

                Vector2 vHeadBoneOut = worldToScreen(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z), camera_position, camera_rotation, camera_fov);
                Vector2 vRootBoneOut = worldToScreen(vRootBone, camera_position, camera_rotation, camera_fov);

                float BoxHeight = abs(vHeadBoneOut.y - vRootBoneOut.y);
                float BoxWidth = BoxHeight / 1.8f;
                // DrawString(12, X.x, X.y + 5, &Col.white, true, true, vida);
                float PlayerHealth = read<float>(g_pid, enemy.damage_handler_ptr + offset::health);

                int dormant = read<int>(g_pid, enemy.damage_handler_ptr + 0x100);
                Vector3 cache_life = read<Vector3>(g_pid, enemy.damage_handler_ptr + offset::health);


                if (PlayerHealth > 100.0f || PlayerHealth <= 0.01f)
                {
                    continue;
                }
                DrawRightProgressBar(vRootBoneOut.x + 30, vHeadBoneOut.y, BoxWidth, BoxHeight, 5, PlayerHealth);
            }
            if (lines) {
                DrawLine(g_width / 2, 0, vHeadBoneOut.x, vHeadBoneOut.y, &Col.green, 3);

            }
            if (teqrmasmrfa)
            {

                int head_x = head_at_screen.x;
                int head_y = head_at_screen.y;
                int start_x = head_x - 35 / distance_modifier;
                int start_y = head_y - 15 / distance_modifier;
                int hp_x = head_x + 10 / distance_modifier;
                int hp_y = head_y + -40 / distance_modifier;
                int dis_x = head_x - 50 / distance_modifier;
                int dis_y = head_y + -40 / distance_modifier;
                Vector3 vHeadBone = getBonePosition(enemy, 8);
                Vector3 vRootBone = getBonePosition(enemy, 0);

                Vector2 vHeadBoneOut = worldToScreen(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z), camera_position, camera_rotation, camera_fov);
                Vector2 vRootBoneOut = worldToScreen(vRootBone, camera_position, camera_rotation, camera_fov);

                float BoxHeight = abs(vHeadBoneOut.y - vRootBoneOut.y);
                float BoxWidth = BoxHeight / 1.8f;

                DrawCornerBox(vRootBoneOut.x - BoxWidth / 2 + 1, vHeadBoneOut.y, BoxWidth, BoxHeight, 1, &Col.green);
                DrawCornerBox(vRootBoneOut.x - BoxWidth / 2 - 1, vHeadBoneOut.y, BoxWidth, BoxHeight, 1, &Col.green);
                DrawCornerBox(vRootBoneOut.x - BoxWidth / 2, vHeadBoneOut.y + 1, BoxWidth, BoxHeight, 1, &Col.green);
                DrawCornerBox(vRootBoneOut.x - BoxWidth / 2, vHeadBoneOut.y - 1, BoxWidth, BoxHeight, 1, &Col.green);
            }
        }
    }


    void handleOtherKeyPresses()
    {

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            z_oly_v1z1ble = !z_oly_v1z1ble;
            glfwSetWindowAttrib(g_window, GLFW_MOUSE_PASSTHROUGH, !z_oly_v1z1ble);
            if (z_oly_v1z1ble) {
                SetForegroundWindow(getOverlayWindow());
            }
            else {
                showValorantWindow();
            }
        }

    }
    static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
    {
        const char* const* items = (const char* const*)data;
        if (out_text)
            *out_text = items[idx];
        return true;
    }
    void HotkeyButton(int a1mk3yt, void* changekey, int status)
    {
        const char* preview_value = NULL;
        if (a1mk3yt >= 0 && a1mk3yt < IM_ARRAYSIZE(keyNames))
            Items_ArrayGetter(keyNames, a1mk3yt, &preview_value);

        std::string a1mk3yts;
        if (preview_value == NULL)
            a1mk3yts = "Select Key";
        else
            a1mk3yts = preview_value;

        if (status == 1)
        {
            a1mk3yts = "Press key to bind";
        }
        if (ImGui::Button(a1mk3yts.c_str(), ImVec2(125, 20)))
        {
            if (status == 0)
            {
                CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
            }
        }
    }
    namespace azmzott
    {

        bool fartov = false;

    }
    void runRenderTick()
    {
        overlayStart();

        if (hmamhamamahm) {
            re3ndrezp();
        }
        if (azmzott::fartov)
        {
            float ScreenCenterX = 1920 / 2.0f;
            float ScreenCenterY = 1080 / 2.0f;
            float radiusx = fart * (ScreenCenterX / 100);
            float radiusy = fart * (ScreenCenterY / 100);

            float calcradius = (radiusx + radiusy) / 2;
            ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), calcradius, 0xFF0000FF, 25);
        }


     
        if (z_oly_v1z1ble) {
            {
                float SpaceLineOne = 80.f;

                ImGui::BeginGroup;
                ImGui::Begin(xorstr("Visual Settings"), nullptr, ImGuiWindowFlags_NoResize);
                ImGui::SetWindowSize(xorstr("Aimbot Settings"), ImVec2(250, 250));
                ImGui::Checkbox(xorstr("ESP ON/OFF"), &hmamhamamahm);
                ImGui::Checkbox(xorstr("ESP Dormant Check"), &hamghemag);
                ImGui::Checkbox(xorstr("Health ESP"), &hangamrgmam);
                ImGui::Checkbox(xorstr("Box ESP"), &teqrmasmrfa);
                ImGui::Checkbox(xorstr("Lines ESP"), &lines);
                ImGui::Checkbox(xorstr("Head ESP"), &d_h3adspz);
                ImGui::Checkbox(xorstr("Bone ESP"), &b0neaepa);
                ImGui::Checkbox(xorstr("Distance ESP"), &health2distance);
                ImGui::End();

                ImGui::BeginGroup;
                ImGui::Begin(xorstr("Aimbot Settings"), nullptr, ImGuiWindowFlags_NoResize);
                ImGui::SetWindowSize(xorstr("Aimbot Settings"), ImVec2(350, 250));
               // ImGui::SetWindowPos(xorstr("Aimbot [Various UD]"), ImVec2(-10, 100));
                ImGui::Checkbox(xorstr("Aimbot ON/OFF"), &goakna);
                ImGui::Text(xorstr("Aim Key: ")), ImGui::SameLine(SpaceLineOne);
                HotkeyButton(hotkeys::a1mk3yt, ChangeKey, keystatus);
                ImGui::Checkbox(xorstr("Show FOV"), &azmzott::fartov);
                ImGui::InputInt(xorstr("Aim Postion"), &numberwtf, 0);
                ImGui::SliderFloat(xorstr("Aimbot Smooth"), &smo0tie, 0, 10);
                ImGui::SliderFloat(xorstr("FOV"), &fart, 0, 10);

                ImGui::End();

              
            }
        }

        overlayEnd();
    }



    std::vector<Enemy> getValidEnemies(uintptr_t actor_array, int actor_count)
    {
        std::vector<Enemy> temp_enemy_collection{};
        size_t size = sizeof(uintptr_t);

        for (int i = 0; i < actor_count; i++) {

            uintptr_t actor = read<uintptr_t>(g_pid, actor_array + (i * size));
            if (actor == 0x00) {
                continue;
            }
            uintptr_t unique_id = read<uintptr_t>(g_pid, actor + offset::unique_id);
            if (unique_id != 18743553) {
                continue;
            }
            uintptr_t mesh = read<uintptr_t>(g_pid, actor + offset::mesh_component);
            if (!mesh) {
                continue;
            }

            uintptr_t player_state = read<uintptr_t>(g_pid, actor + offset::player_state);
            uintptr_t team_component = read<uintptr_t>(g_pid, player_state + offset::team_component);
            int team_id = read<int>(g_pid, team_component + offset::team_id);
            int bone_count = read<int>(g_pid, mesh + offset::bone_count);
            bool is_bot = bone_count == 103;
            if (team_id == g_local_team_id && !is_bot) {
                continue;
            }

            uintptr_t damage_handler = read<uintptr_t>(g_pid, actor + offset::damage_handler);
            uintptr_t root_component = read<uintptr_t>(g_pid, actor + offset::root_component);
            uintptr_t bone_array = read<uintptr_t>(g_pid, mesh + offset::bone_array);

            Enemy enemy{
                actor,
                damage_handler,
                player_state,
                root_component,
                mesh,
                bone_array,
                bone_count,
                true
            };

            temp_enemy_collection.push_back(enemy);
        }

        return temp_enemy_collection;
    }

    uintptr_t decryptWorld(uintptr_t pid, uintptr_t base_address)
    {
        const auto key = read<uintptr_t>(pid, base_address + offset::uworld_key);
        //  print("key", (void*)key);
        const auto state = read<State>(pid, base_address + offset::uworld_state);
        //  print("state.keys", (void*)state.keys);
        const auto uworld_ptr = decrypt_uworld(key, (uintptr_t*)&state);
        //  print("uworld_ptr", (void*)uworld_ptr);
        return read<uintptr_t>(pid, uworld_ptr);
    }

    void getOffset(LPVOID lpParameter)
    {
        while (true) {
            uintptr_t world = decryptWorld(g_pid, g_base_address);
            //    print("world", (void*)world);
            uintptr_t game_instance = read<uintptr_t>(g_pid, world + offset::game_instance);
            //     print("game_instance", (void*)game_instance);
            uintptr_t persistent_level = read<uintptr_t>(g_pid, world + offset::persistent_level);
            //    print("persistent_level", (void*)persistent_level);
            uintptr_t local_player_array = read<uintptr_t>(g_pid, game_instance + offset::local_player_array);
            //  print("local_player_array", (void*)local_player_array);
            uintptr_t local_player = read<uintptr_t>(g_pid, local_player_array);
            //    print("local_player", (void*)local_player);
            uintptr_t local_player_controller = read<uintptr_t>(g_pid, local_player + offset::local_player_controller);
            //  print("local_player_controller", (void*)local_player_controller);
            uintptr_t local_player_pawn = read<uintptr_t>(g_pid, local_player_controller + offset::local_player_pawn);
            //  print("local_player_pawn", (void*)local_player_pawn);
            uintptr_t local_damage_handler = read<uintptr_t>(g_pid, local_player_pawn + offset::damage_handler);
            //   print("local_damage_handler", (void*)local_damage_handler);
            uintptr_t local_player_state = read<uintptr_t>(g_pid, local_player_pawn + offset::player_state);
            // print("local_player_state", (void*)local_player_state);
            uintptr_t local_team_component = read<uintptr_t>(g_pid, local_player_state + offset::team_component);
            //  print("local_team_component", (void*)local_team_component);
            uintptr_t camera_manager = read<uintptr_t>(g_pid, local_player_controller + offset::camera_manager);
            // print("camera_manager", (void*)camera_manager);
            uintptr_t actor_array = read<uintptr_t>(g_pid, persistent_level + offset::actor_array);
            //   print("actor_array", (void*)actor_array);

            int local_team_id = read<int>(g_pid, local_team_component + offset::team_id);
            int actor_count = read<int>(g_pid, persistent_level + offset::actor_count);

            g_local_player_controller = local_player_controller;
            g_local_player_pawn = local_player_pawn;
            g_local_damage_handler = local_damage_handler;
            g_camera_manager = camera_manager;
            g_local_team_id = local_team_id;
            enemy_collection = getValidEnemies(actor_array, actor_count);

            Sleep(10);
        }
    }

    void stop()
    {
        if (handleOffset) {
            CloseHandle(handleOffset);
        }
        cleanupWindow();
    }

    void run()
    {   
        if (initialize()) {

            handleOffset = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)getOffset, nullptr, NULL, nullptr);
            while (!glfwWindowShouldClose(g_window))
            {
                if (goakna && GetAsyncKeyState(hotkeys::a1mk3yt) < 0) {

                    azmzot();
                }
                runRenderTick();
                handleOtherKeyPresses();
            }
        }
    }
};
    //while (!glfwWindowShouldClose(g_window))
//{
//
//
//    if (aimbot && GetAsyncKeyState(hotkeys::a1mk3yt) < 0) {
//
//        aimbotgay();
//    }
//    runRenderTick();
//    handleKeyPresses();
//}
