#include "HookManager.h"
#include "AddressManager.h"
#include "Memory.h"

#include <MinHook.h>
#include <iostream>
#include <Windows.h>

// Function callback storage
std::function<bool(char* i_szPacket)> g_pRecvCallback;
std::function<bool(char* i_szPacket)> g_pSendCallback;

// Typedefs for original functions
typedef void(__cdecl* RecvFuncType)();
RecvFuncType g_pOrigRecvFunc = nullptr;

typedef void(__cdecl* SendFuncType)();
SendFuncType g_pOrigSendFunc = nullptr;

// Hook function for receiving packets
void __cdecl RecvPacketHook() {
    static char* s_szPacket;

    __asm {
        pushad
        pushfd
        mov s_szPacket, edx
    }

    std::cout << "RecvPacketHook: " << s_szPacket << std::endl; // Debugging log

    // Process the packet using the callback
    if (g_pRecvCallback(s_szPacket)) {
        s_szPacket[0] = 0x00; // Example modification if needed
    }

    __asm {
        popfd
        popad
    }

    // Call original function
    g_pOrigRecvFunc();
}

// Hook function for sending packets
void __cdecl SendPacketHook() {
    static char* s_szPacket;

    __asm {
        pushad
        pushfd
        mov s_szPacket, edx
    }

    if (s_szPacket) {
        std::cout << "SendPacketHook: " << s_szPacket << std::endl; // Debugging log

        // Use callback to determine if the packet should be blocked
        bool fBlockPacket = false;
        if (g_pSendCallback) {
            fBlockPacket = g_pSendCallback(s_szPacket);
        }

        if (fBlockPacket) {
            std::cout << "Blocking packet: " << s_szPacket << std::endl; // Debugging log
            __asm {
                popfd
                popad
            }
            return;
        }
    }

    __asm {
        popfd
        popad
    }

    g_pOrigSendFunc();
}

void HookManager::Initialize(std::function<bool(char* i_szPacket)> i_pRecvCallback, std::function<bool(char* i_szPacket)> i_pSendCallback) {
    g_pRecvCallback = i_pRecvCallback;
    g_pSendCallback = i_pSendCallback;

    if (MH_Initialize() != MH_OK) {
        std::cerr << "Failed to initialize MinHook!" << std::endl;
        return;
    }

    void* pRecvTarget = reinterpret_cast<void*>(AddressManager::Get(EAddress::ARecvHook));
    if (MH_CreateHook(pRecvTarget, &RecvPacketHook, reinterpret_cast<void**>(&g_pOrigRecvFunc)) != MH_OK) {
        std::cerr << "Failed to create Recv hook!" << std::endl;
        return;
    }

    void* pSendTarget = reinterpret_cast<void*>(AddressManager::Get(EAddress::ASendHook));
    if (MH_CreateHook(pSendTarget, &SendPacketHook, reinterpret_cast<void**>(&g_pOrigSendFunc)) != MH_OK) {
        std::cerr << "Failed to create Send hook!" << std::endl;
        return;
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
        std::cerr << "Failed to enable hooks!" << std::endl;
    }
}

void HookManager::Unhook() {
    if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK) {
        std::cerr << "Failed to disable hooks!" << std::endl;
    }

    if (MH_Uninitialize() != MH_OK) {
        std::cerr << "Failed to uninitialize MinHook!" << std::endl;
    }
}