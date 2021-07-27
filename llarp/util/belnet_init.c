#include "belnet_init.h"
#if defined(_WIN32)
#include <windows.h>
#include <winuser.h>
#include <stdio.h>

int
Belnet_INIT(void)
{
  static const char*(CDECL * pwine_get_version)(void);
  HMODULE hntdll = GetModuleHandle("ntdll.dll");
  if (hntdll)
  {
    pwine_get_version = (void*)GetProcAddress(hntdll, "wine_get_version");
    if (pwine_get_version)
    {
      static const char* text =
          "dont run belnet in wine like wtf man we support linux and pretty "
          "much every flavour of BSD, and even some flavours of unix system "
          "5.x.\nThis Program Will now crash lmao.";
      static const char* title = "srsly fam wtf";
      MessageBoxA(NULL, text, title, MB_ICONHAND);
      abort();
    }
  }
  return 0;
}
#else
int
Belnet_INIT(void)
{
  return 0;
}

#endif
