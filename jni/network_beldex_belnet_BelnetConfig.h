/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class network_beldex_belnet_BelnetConfig */

#ifndef _Included_network_beldex_belnet_BelnetConfig
#define _Included_network_beldex_belnet_BelnetConfig
#ifdef __cplusplus
extern "C"
{
#endif
  /*
   * Class:     network_beldex_belnet_BelnetConfig
   * Method:    Obtain
   * Signature: (Ljava/lang/String;)Ljava/nio/ByteBuffer;
   */
  JNIEXPORT jobject JNICALL
  Java_network_beldex_belnet_BelnetConfig_Obtain(JNIEnv*, jclass, jstring);

  /*
   * Class:     network_beldex_belnet_BelnetConfig
   * Method:    Free
   * Signature: (Ljava/nio/ByteBuffer;)V
   */
  JNIEXPORT void JNICALL
  Java_network_beldex_belnet_BelnetConfig_Free(JNIEnv*, jclass, jobject);

  /*
   * Class:     network_beldex_belnet_BelnetConfig
   * Method:    Load
   * Signature: ()Z
   */
  JNIEXPORT jboolean JNICALL
  Java_network_beldex_belnet_BelnetConfig_Load(JNIEnv*, jobject);

  /*
   * Class:     network_beldex_belnet_BelnetConfig
   * Method:    Save
   * Signature: ()Z
   */
  JNIEXPORT jboolean JNICALL
  Java_network_beldex_belnet_BelnetConfig_Save(JNIEnv*, jobject);

  /*
   * Class:     network_beldex_belnet_BelnetConfig
   * Method:    AddDefaultValue
   * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
   */
  JNIEXPORT void JNICALL
  Java_network_beldex_belnet_BelnetConfig_AddDefaultValue(
      JNIEnv*, jobject, jstring, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
