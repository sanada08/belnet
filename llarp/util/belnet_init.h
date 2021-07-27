#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef Belnet_INIT
#if defined(_WIN32)
#define Belnet_INIT \
  DieInCaseSomehowThisGetsRunInWineButLikeWTFThatShouldNotHappenButJustInCaseHandleItWithAPopupOrSomeShit
#else
#define Belnet_INIT _belnet_non_shit_platform_INIT
#endif
#endif

  int
  Belnet_INIT(void);

#ifdef __cplusplus
}
#endif
