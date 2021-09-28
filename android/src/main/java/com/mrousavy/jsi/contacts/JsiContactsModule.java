package com.mrousavy.jsi.contacts;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.JavaScriptContextHolder;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = JsiContactsModule.NAME)
public class JsiContactsModule extends ReactContextBaseJavaModule {
    public static final String NAME = "JsiContacts";
    static {
        System.loadLibrary("jsicontacts");
    }

    @Override
    @NonNull
    public String getName() {
        return NAME;
    }

    public static void install(JavaScriptContextHolder jsContext) {
        nativeInstall(jsContext.get());
    }

    private static native void nativeInstall(long jsiPtr);
}
