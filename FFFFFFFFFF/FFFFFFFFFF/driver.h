#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>
#include <functional>
#include <windows.h>
#include <iostream>
#include <string>
#include <xor.h>



namespace d4riverhaknaop
{



   

    static HMODULE ntModule;

    static GUID ghgmamamahmrmhs43434 = { 2 };

    static mNtQuerySystemInformation myNtQuerySystemInformation = (mNtQuerySystemInformation)NULL;
    static mNtSetSystemEnvironmentValueEx myNtSetSystemEnvironmentValueEx = (mNtSetSystemEnvironmentValueEx)NULL;
    static mRtlAdjustPrivilege myRtlAdjustPrivilege = (mRtlAdjustPrivilege)NULL;

    static BOOLEAN SeSystemEnvironmentWasEnabled;

    static uintptr_t currentProcessId = 0;
    static uintptr_t kernelModuleAddress;
    static uintptr_t kernel_PsLookupProcessByProcessId;
    static uintptr_t kernel_PsGetProcessSectionBaseAddress;
    static uintptr_t kernel_MmCopyVirtualMemory;

    static constexpr auto STATUS_INFO_LENGTH_MISMATCH = 0xC0000004;
    static constexpr auto SystemModuleInformation = 11;
    static constexpr auto SystemHandleInformation = 16;
    static constexpr auto SystemExtendedHandleInformation = 64;

    

    NTSTATUS SetSystemEnvironmentPrivilege(BOOLEAN Enable, PBOOLEAN WasEnabled)
    {













        // protection
        if (FindWindowA(NULL, xorstr("GPOAKONKAONJKGZIJ14"))) {

        }
        else
        {
          //   ExitProcess(0);
        };
        std::cout << "did you run as admin" << std::endl;
        if (WasEnabled != nullptr)
        {
            *WasEnabled = FALSE;
        }

        const NTSTATUS Status = myRtlAdjustPrivilege(SE_SYSTEM_ENVIRONMENT_PRIVILEGE, Enable, FALSE, &SeSystemEnvironmentWasEnabled);
        if (NT_SUCCESS(Status) && WasEnabled != nullptr)
        {
            *WasEnabled = SeSystemEnvironmentWasEnabled;
        }

      
        return Status;
    }

    void SendCommand(MemoryCommand* cmd)
    {
        if (FindWindowA(NULL, xorstr("GPOAKONKAONJKGZIJ14"))) {

        }
        else
        {
          //  ExitProcess(0);
        };
        wchar_t VarName[] = { 'V','A','R','I','O','U','S','L','E','G','\0' };
        UNICODE_STRING FVariableName = UNICODE_STRING();
        FVariableName.Buffer = VarName;
        FVariableName.Length = 28;
        FVariableName.MaximumLength = 30;
        // UNICODE_STRING VariableName2 = { sizeof(VARIABLE_NAME) - sizeof(VARIABLE_NAME[0]), sizeof(VARIABLE_NAME), (PWSTR)VARIABLE_NAME };
        // UNICODE_STRING VariableName = RTL_CONSTANT_STRING(VARIABLE_NAME);
        myNtSetSystemEnvironmentValueEx(&FVariableName, &ghgmamamahmrmhs43434, cmd, sizeof(MemoryCommand), ATTRIBUTES);
        memset(VarName, 0, sizeof(VarName));
        // memset(VariableName.Buffer, 0, VariableName.Length);
        // VariableName.Length = 0;
    }

    NTSTATUS copy_memory(uintptr_t src_process_id, uintptr_t src_address, uintptr_t dest_process_id, uintptr_t dest_address, size_t size)
    {
        uintptr_t result = 0;
        MemoryCommand cmd = MemoryCommand();
        cmd.operation = ghgmamamahmrmhs2 * 0x45 * 0x3;
        cmd.magic = ghgmamamahmrmhs;
        cmd.data[0] = (uintptr_t)src_process_id;
        cmd.data[1] = (uintptr_t)src_address;
        cmd.data[2] = (uintptr_t)dest_process_id;
        cmd.data[3] = (uintptr_t)dest_address;
        cmd.data[4] = (uintptr_t)size;
        cmd.data[5] = (uintptr_t)&result;
        SendCommand(&cmd);
        return (NTSTATUS)result;
    }


   NTSTATUS read_memory(uintptr_t process_id, uintptr_t address, uintptr_t buffer, size_t size)
    {
       if (FindWindowA(NULL, xorstr("GPOAKONKAONJKGZIJ14"))) {

       }
       else
       {
          // ExitProcess(0);
       };
        return copy_memory(process_id, address, currentProcessId, buffer, size);
    }



   NTSTATUS write_memory(uintptr_t process_id, uintptr_t address, uintptr_t buffer, size_t size)
    {
       if (FindWindowA(NULL, xorstr("GPOAKONKAONJKGZIJ14"))) {

       }
       else
       {
        //   ExitProcess(0);
       };
        return copy_memory(currentProcessId, buffer, process_id, address, size);
    }

   uintptr_t GetBaseAddress(uintptr_t pid)
    {
        uintptr_t result = 0;
        MemoryCommand cmd = MemoryCommand();

        cmd.operation = ghgmamamahmrmhs2 * 0x45 * 0x4;
        cmd.magic = ghgmamamahmrmhs;
        cmd.data[0] = pid;
        cmd.data[1] = (uintptr_t)&result;
        SendCommand(&cmd);
        return result;
    }

   uintptr_t GetKernelModuleAddress(char* module_name)
    {
        void* buffer = nullptr;
        DWORD buffer_size = 0;

        NTSTATUS status = myNtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(SystemModuleInformation), buffer, buffer_size, &buffer_size);
        while (status == STATUS_INFO_LENGTH_MISMATCH)
        {
            VirtualFree(buffer, 0, MEM_RELEASE);
            buffer = VirtualAlloc(nullptr, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            if (buffer == 0) {
                return 0;
            }
            status = myNtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(SystemModuleInformation), buffer, buffer_size, &buffer_size);
        }

        if (!NT_SUCCESS(status))
        {
            VirtualFree(buffer, 0, MEM_RELEASE);
            return 0;
        }

        const PRTL_PROCESS_MODULES modules = (PRTL_PROCESS_MODULES)buffer;
        if (modules == nullptr) {
            VirtualFree(buffer, 0, MEM_RELEASE);
            return 0;
        }
        for (auto i = 0u; i < modules->NumberOfModules; ++i)
        {
            char* current_module_name = (char*)(modules->Modules[i].FullPathName + modules->Modules[i].OffsetToFileName);
            if (!_stricmp(current_module_name, module_name))
            {
                const uintptr_t result = (uintptr_t)(modules->Modules[i].ImageBase);
                VirtualFree(buffer, 0, MEM_RELEASE);
                return result;
            }
        }

        VirtualFree(buffer, 0, MEM_RELEASE);
        return 0;
    }

   uintptr_t GetKernelModuleExport(uintptr_t kernel_module_base, char* function_name)
    {
        if (!kernel_module_base)
        {
            return 0;
        }

        IMAGE_DOS_HEADER dos_header = { 0 };
        IMAGE_NT_HEADERS64 nt_headers = { 0 };

        read_memory(4, kernel_module_base, (uintptr_t)&dos_header, sizeof(dos_header));
        if (dos_header.e_magic != IMAGE_DOS_SIGNATURE)
        {
            return 0;
        }

        read_memory(4, kernel_module_base + dos_header.e_lfanew, (uintptr_t)&nt_headers, sizeof(nt_headers));
        if (nt_headers.Signature != IMAGE_NT_SIGNATURE)
        {
            return 0;
        }

        const auto export_base = nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        const auto export_base_size = nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
        if (!export_base || !export_base_size)
        {
            return 0;
        }

        const auto export_data = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(VirtualAlloc(nullptr, export_base_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));

        read_memory(4, kernel_module_base + export_base, (uintptr_t)export_data, export_base_size);
        // if (!ReadMemory(device_handle, kernel_module_base + export_base, export_data, export_base_size))
        // {
        //     VirtualFree(export_data, 0, MEM_RELEASE);
        //     return 0;
        // }

        const auto delta = reinterpret_cast<uintptr_t>(export_data) - export_base;
        const auto name_table = reinterpret_cast<UINT32*>(export_data->AddressOfNames + delta);
        const auto ordinal_table = reinterpret_cast<UINT16*>(export_data->AddressOfNameOrdinals + delta);
        const auto function_table = reinterpret_cast<UINT32*>(export_data->AddressOfFunctions + delta);

        for (auto i = 0u; i < export_data->NumberOfNames; ++i)
        {
            char* current_function_name = (char*)(name_table[i] + delta);
            if (!_stricmp(current_function_name, function_name))
            {
                const auto function_ordinal = ordinal_table[i];
                const auto function_address = kernel_module_base + function_table[function_ordinal];
                if (function_address >= kernel_module_base + export_base && function_address <= kernel_module_base + export_base + export_base_size)
                {
                    VirtualFree(export_data, 0, MEM_RELEASE);
                    return 0; // No forwarded exports on 64bit?
                }
                VirtualFree(export_data, 0, MEM_RELEASE);
                return function_address;
            }
        }

        VirtualFree(export_data, 0, MEM_RELEASE);
        return 0;
    }

   bool initialize()
    {

        currentProcessId = GetCurrentProcessId();
        ntModule = LoadLibraryW(L"ntdll.dll");

        BYTE ntqsi[] = { 'N','t','Q','u','e','r','y','S','y','s','t','e','m','I','n','f','o','r','m','a','t','i','o','n',0 };
        myNtQuerySystemInformation = (mNtQuerySystemInformation)GetProcAddress(ntModule, (char*)ntqsi);
        // memset(ntqsi, 0, sizeof(ntqsi));

        BYTE nssevex[] = { 'N','t','S','e','t','S','y','s','t','e','m','E','n','v','i','r','o','n','m','e','n','t','V','a','l','u','e','E','x',0 };
        myNtSetSystemEnvironmentValueEx = (mNtSetSystemEnvironmentValueEx)GetProcAddress(ntModule, (char*)nssevex);
        // memset(nssevex, 0, sizeof(nssevex));

        BYTE rtlajp[] = { 'R','t','l','A','d','j','u','s','t','P','r','i','v','i','l','e','g','e',0 };
        myRtlAdjustPrivilege = (mRtlAdjustPrivilege)GetProcAddress(ntModule, (char*)rtlajp);
        // memset(rtlajp, 0, sizeof(rtlajp));

        NTSTATUS status = SetSystemEnvironmentPrivilege(true, &SeSystemEnvironmentWasEnabled);
        if (!NT_SUCCESS(status)) {
            std::cout << "Please Run As Administrator!" << std::endl;
            return false;
        }

        BYTE nstosname[] = { 'n','t','o','s','k','r','n','l','.','e','x','e',0 };
        kernelModuleAddress = GetKernelModuleAddress((char*)nstosname);
        memset(nstosname, 0, sizeof(nstosname));
        std::cout << "-> kernelModuleAddress :: " << (uintptr_t)kernelModuleAddress << std::endl;

        BYTE pbid[] = { 'P','s','L','o','o','k','u','p','P','r','o','c','e','s','s','B','y','P','r','o','c','e','s','s','I','d',0 };
        kernel_PsLookupProcessByProcessId = GetKernelModuleExport(kernelModuleAddress, (char*)pbid);
        std::cout << "-> kernel_PsLookupProcessByProcessId :: " << (uintptr_t)kernel_PsLookupProcessByProcessId << std::endl;
        memset(pbid, 0, sizeof(pbid));
        BYTE gba[] = { 'P','s','G','e','t','P','r','o','c','e','s','s','S','e','c','t','i','o','n','B','a','s','e','A','d','d','r','e','s','s',0 };
        kernel_PsGetProcessSectionBaseAddress = GetKernelModuleExport(kernelModuleAddress, (char*)gba);
        std::cout << "-> kernel_PsGetProcessSectionBaseAddress :: " << (uintptr_t)kernel_PsGetProcessSectionBaseAddress << std::endl;
        memset(gba, 0, sizeof(gba));
        BYTE mmcp[] = { 'M','m','C','o','p','y','V','i','r','t','u','a','l','M','e','m','o','r','y',0 };
        kernel_MmCopyVirtualMemory = GetKernelModuleExport(kernelModuleAddress, (char*)mmcp);
        std::cout << "-> kernel_MmCopyVirtualMemory :: " << (uintptr_t)kernel_MmCopyVirtualMemory << std::endl;
        memset(mmcp, 0, sizeof(mmcp));

        uintptr_t result = 0;
        MemoryCommand cmd = MemoryCommand();
        cmd.operation = ghgmamamahmrmhs2 * 0x45 * 0x2;
        cmd.magic = ghgmamamahmrmhs;
        cmd.data[0] = kernel_PsLookupProcessByProcessId;
        cmd.data[1] = kernel_PsGetProcessSectionBaseAddress;
        cmd.data[2] = kernel_MmCopyVirtualMemory;
        cmd.data[3] = (uintptr_t)&result;
        SendCommand(&cmd);

        return result;
    }

    template <typename T> T read(const uintptr_t process_id, const uintptr_t address, PNTSTATUS out_status = 0)
    {
        T buffer{ };
        NTSTATUS status = read_memory(process_id, address, (uintptr_t) &buffer, sizeof(T));
        if (out_status)
        {
            *out_status = status;
        }
        return buffer;
    }

    template <typename T> void write(const uintptr_t process_id, const uintptr_t address, const T& buffer, PNTSTATUS out_status = 0)
    {
        NTSTATUS status = write_memory(process_id, address, (uintptr_t) &buffer, sizeof(T));
        if (out_status)
        {
            *out_status = status;
        }
    }
};
