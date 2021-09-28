#include <jni.h>
#include "example.h"

extern "C"
JNIEXPORT jint JNICALL
Java_com_mrousavy_jsi_contacts_JsiContactsModule_nativeInstall(JNIEnv *env, jclass type, jlong jsiRuntimePointer) {
    return example::multiply(a, b);
}
