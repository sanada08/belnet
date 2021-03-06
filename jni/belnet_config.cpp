#include "network_beldex_belnet_BelnetConfig.h"
#include <llarp.hpp>
#include <llarp/config/config.hpp>
#include "belnet_jni_common.hpp"

extern "C"
{
  JNIEXPORT jobject JNICALL
  Java_network_beldex_belnet_BelnetConfig_Obtain(JNIEnv* env, jclass, jstring dataDir)
  {
    auto conf = VisitStringAsStringView<llarp::Config*>(
        env, dataDir, [](std::string_view val) -> llarp::Config* {
          return new llarp::Config{val};
        });

    if (conf == nullptr)
      return nullptr;
    return env->NewDirectByteBuffer(conf, sizeof(llarp::Config));
  }

  JNIEXPORT void JNICALL
  Java_network_beldex_belnet_BelnetConfig_Free(JNIEnv* env, jclass, jobject buf)
  {
    auto ptr = FromBuffer<llarp::Config>(env, buf);
    delete ptr;
  }

  JNIEXPORT jboolean JNICALL
  Java_network_beldex_belnet_BelnetConfig_Load(JNIEnv* env, jobject self)
  {
    auto conf = GetImpl<llarp::Config>(env, self);
    if (conf == nullptr)
      return JNI_FALSE;
    if (conf->Load())
    {
      return JNI_TRUE;
    }
    return JNI_FALSE;
  }

  JNIEXPORT jboolean JNICALL
  Java_network_beldex_belnet_BelnetConfig_Save(JNIEnv* env, jobject self)
  {
    auto conf = GetImpl<llarp::Config>(env, self);
    if (conf == nullptr)
      return JNI_FALSE;
    try
    {
      conf->Save();
    }
    catch (...)
    {
      return JNI_FALSE;
    }
    return JNI_TRUE;
  }

  JNIEXPORT void JNICALL
  Java_network_beldex_belnet_BelnetConfig_AddDefaultValue(
      JNIEnv* env, jobject self, jstring section, jstring key, jstring value)
  {
    auto convert = [](std::string_view str) -> std::string { return std::string{str}; };

    const auto sect = VisitStringAsStringView<std::string>(env, section, convert);
    const auto k = VisitStringAsStringView<std::string>(env, key, convert);
    const auto v = VisitStringAsStringView<std::string>(env, value, convert);

    auto conf = GetImpl<llarp::Config>(env, self);
    if (conf)
    {
      conf->AddDefault(sect, k, v);
    }
  }
}
