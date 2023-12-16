#include <Windows.h>
#include <SetupAPI.h>
#include <devguid.h>
#include <iostream>
#pragma comment (lib, "SetupAPI.lib")

int main() {
    SetConsoleTitle(TEXT("CheatGlobal - p4n"));
    std::cout << "Made with ♥ by p4n" << std::endl;
    HDEVINFO devInfo;
    SP_DEVINFO_DATA devInfoData;
    devInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_HIDCLASS, 0, 0, DIGCF_PRESENT);
    if (devInfo == INVALID_HANDLE_VALUE) {
        std::cerr << "Aygıt bilgisi alınırken hata meydana geldi." << std::endl;
        return 1;
    }
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    for (DWORD i = 0; SetupDiEnumDeviceInfo(devInfo, i, &devInfoData); ++i) {
        char buf[1024];
        if (SetupDiGetDeviceRegistryProperty(devInfo, &devInfoData, SPDRP_FRIENDLYNAME, 0, (PBYTE)buf, sizeof(buf), 0)) {
            if (strstr(buf, "touch screen") != 0) {
                if (!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, devInfo, &devInfoData)) {
                    std::cerr << "Dokunmatik devre dışı bırakılırken bir hata meydana geldi." << std::endl;
                    SetupDiDestroyDeviceInfoList(devInfo);
                    return 1;
                }
                std::cout << "Dokunmatik başarıyla devre dışı bırakıldı." << std::endl;
                SetupDiDestroyDeviceInfoList(devInfo);
                return 0;
            }
        }
    }
    std::cerr << "Dokunmatik ekran bulunamadı." << std::endl;
    SetupDiDestroyDeviceInfoList(devInfo);
    return 1;
}
