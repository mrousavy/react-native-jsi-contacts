package com.mrousavy.jsi.contacts;

import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.provider.ContactsContract;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

import com.facebook.proguard.annotations.DoNotStrip;
import com.facebook.react.bridge.JavaScriptContextHolder;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.module.annotations.ReactModule;
import com.facebook.react.turbomodule.core.CallInvokerHolderImpl;

@ReactModule(name = JsiContactsModule.NAME)
public class JsiContactsModule extends ReactContextBaseJavaModule {
    public static final String NAME = "JsiContacts";
    static {
        System.loadLibrary("jsicontacts");
    }
    private static ContactsProvider contactsProvider;

    @Override
    @NonNull
    public String getName() {
        return NAME;
    }

    public static void install(ReactContext context) {
      JavaScriptContextHolder jsContext = context.getJavaScriptContextHolder();
      CallInvokerHolderImpl callInvokerHolder = (CallInvokerHolderImpl) context.getCatalystInstance().getJSCallInvokerHolder();
      contactsProvider = new ContactsProvider(context.getContentResolver());
      nativeInstall(jsContext.get(), callInvokerHolder);
    }

    private static native void nativeInstall(long jsiPtr, CallInvokerHolderImpl callInvoker);

    private static WritableArray getContactsAsync() {
      return contactsProvider.getContacts();
    }
}
