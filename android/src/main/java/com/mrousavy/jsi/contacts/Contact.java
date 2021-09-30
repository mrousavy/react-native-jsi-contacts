package com.mrousavy.jsi.contacts;

import android.database.Cursor;
import android.provider.ContactsContract;
import android.text.TextUtils;

import com.facebook.jni.HybridData;
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
  public String contactId;
  public String rawContactId;
  public String displayName;
  public String givenName = "";
  public String middleName = "";
  public String familyName = "";
  public String prefix = "";
  public String suffix = "";
  public String company = "";
  public String jobTitle = "";
  public String department = "";
  public String note ="";
  public List<Item> urls = new ArrayList<>();
  public List<Item> instantMessengers = new ArrayList<>();
  public boolean hasPhoto = false;
  public String photoUri;
  public List<Item> emails = new ArrayList<>();
  public List<Item> phones = new ArrayList<>();
  public List<Map<String, String>> postalAddresses = new ArrayList<>();
  public Birthday birthday;

  public Contact(String contactId) {
    this.contactId = contactId;
  }

  public static class Item {
    public String label;
    public String value;
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
    public int year = 0;
    public int month = 0;
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
