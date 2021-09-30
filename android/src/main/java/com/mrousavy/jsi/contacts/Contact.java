package com.mrousavy.jsi.contacts;

import android.database.Cursor;
import android.provider.ContactsContract;
import android.text.TextUtils;

import com.facebook.jni.HybridData;
import com.facebook.proguard.annotations.DoNotStrip;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.WritableMap;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static android.provider.ContactsContract.CommonDataKinds.Contactables;
import static android.provider.ContactsContract.CommonDataKinds.Email;
import static android.provider.ContactsContract.CommonDataKinds.Event;
import static android.provider.ContactsContract.CommonDataKinds.Organization;
import static android.provider.ContactsContract.CommonDataKinds.Phone;
import static android.provider.ContactsContract.CommonDataKinds.StructuredName;
import static android.provider.ContactsContract.CommonDataKinds.Note;
import static android.provider.ContactsContract.CommonDataKinds.Website;
import static android.provider.ContactsContract.CommonDataKinds.Im;
import static android.provider.ContactsContract.CommonDataKinds.StructuredPostal;

public class Contact {
  @DoNotStrip
  public String contactId;
  @DoNotStrip
  public String rawContactId;
  @DoNotStrip
  public String displayName;
  @DoNotStrip
  public String givenName = "";
  @DoNotStrip
  public String middleName = "";
  @DoNotStrip
  public String familyName = "";
  @DoNotStrip
  public String prefix = "";
  @DoNotStrip
  public String suffix = "";
  @DoNotStrip
  public String company = "";
  @DoNotStrip
  public String jobTitle = "";
  @DoNotStrip
  public String department = "";
  @DoNotStrip
  public String note ="";
  @DoNotStrip
  public List<Item> urls = new ArrayList<>();
  @DoNotStrip
  public List<Item> instantMessengers = new ArrayList<>();
  @DoNotStrip
  public boolean hasPhoto = false;
  @DoNotStrip
  public String photoUri;
  @DoNotStrip
  public List<Item> emails = new ArrayList<>();
  @DoNotStrip
  public List<Item> phones = new ArrayList<>();
  @DoNotStrip
  public List<Map<String, String>> postalAddresses = new ArrayList<>();
  @DoNotStrip
  public Birthday birthday;

  public Contact(String contactId) {
    this.contactId = contactId;
  }

  public static class Item {
    @DoNotStrip
    public String label;
    @DoNotStrip
    public String value;
    @DoNotStrip
    public String id;

    public Item(String label, String value, String id) {
      this.id = id;
      this.label = label;
      this.value = value;
    }

    public Item(String label, String value) {
      this.label = label;
      this.value = value;
    }
  }

  public static class Birthday {
    @DoNotStrip
    public int year = 0;
    @DoNotStrip
    public int month = 0;
    @DoNotStrip
    public int day = 0;

    public Birthday(int year, int month, int day) {
      this.year = year;
      this.month = month;
      this.day = day;
    }

    public Birthday(int month, int day) {
      this.month = month;
      this.day = day;
    }
  }

  public static class PostalAddress {
    public static HashMap<String, String> postalAddressFromCursor(Cursor cursor) {
      HashMap<String, String> map = new HashMap<>();
      map.put("label", getLabel(cursor));
      putString(map, cursor, "formattedAddress", StructuredPostal.FORMATTED_ADDRESS);
      putString(map, cursor, "street", StructuredPostal.STREET);
      putString(map, cursor, "pobox", StructuredPostal.POBOX);
      putString(map, cursor, "neighborhood", StructuredPostal.NEIGHBORHOOD);
      putString(map, cursor, "city", StructuredPostal.CITY);
      putString(map, cursor, "region", StructuredPostal.REGION);
      putString(map, cursor, "state", StructuredPostal.REGION);
      putString(map, cursor, "postCode", StructuredPostal.POSTCODE);
      putString(map, cursor, "country", StructuredPostal.COUNTRY);
      return map;
    }

    private static void putString(HashMap<String, String> map, Cursor cursor, String key, String androidKey) {
      final String value = cursor.getString(cursor.getColumnIndex(androidKey));
      if (!TextUtils.isEmpty(value))
        map.put(key, value);
    }

    private static String getLabel(Cursor cursor) {
      switch (cursor.getInt(cursor.getColumnIndex(StructuredPostal.TYPE))) {
        case StructuredPostal.TYPE_HOME:
          return "home";
        case StructuredPostal.TYPE_WORK:
          return "work";
        case StructuredPostal.TYPE_CUSTOM:
          final String label = cursor.getString(cursor.getColumnIndex(StructuredPostal.LABEL));
          return label != null ? label : "";
      }
      return "other";
    }
  }
}
