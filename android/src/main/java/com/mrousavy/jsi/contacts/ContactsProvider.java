/*
 * Original source code copied from https://github.com/morenoh149/react-native-contacts/blob/master/android/src/main/java/com/rt2zz/reactnativecontacts/ContactsProvider.java
 * All credits belongs to the original source.
 */

package com.mrousavy.jsi.contacts;

import android.content.ContentResolver;
import android.database.Cursor;
import android.net.Uri;
import android.provider.ContactsContract;
import androidx.annotation.NonNull;
import android.text.TextUtils;
import android.util.Log;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedHashMap;
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

public class ContactsProvider {
  public static final int ID_FOR_PROFILE_CONTACT = -1;

  private static final List<String> JUST_ME_PROJECTION = new ArrayList<String>() {{
    add((ContactsContract.Data._ID));
    add(ContactsContract.Data.CONTACT_ID);
    add(ContactsContract.Data.RAW_CONTACT_ID);
    add(ContactsContract.Data.LOOKUP_KEY);
    add(ContactsContract.Contacts.Data.MIMETYPE);
    add(ContactsContract.Profile.DISPLAY_NAME);
    add(Contactables.PHOTO_URI);
    add(StructuredName.DISPLAY_NAME);
    add(StructuredName.GIVEN_NAME);
    add(StructuredName.MIDDLE_NAME);
    add(StructuredName.FAMILY_NAME);
    add(StructuredName.PREFIX);
    add(StructuredName.SUFFIX);
    add(Phone.NUMBER);
    add(Phone.NORMALIZED_NUMBER);
    add(Phone.TYPE);
    add(Phone.LABEL);
    add(Email.DATA);
    add(Email.ADDRESS);
    add(Email.TYPE);
    add(Email.LABEL);
    add(Organization.COMPANY);
    add(Organization.TITLE);
    add(Organization.DEPARTMENT);
    add(StructuredPostal.FORMATTED_ADDRESS);
    add(StructuredPostal.TYPE);
    add(StructuredPostal.LABEL);
    add(StructuredPostal.STREET);
    add(StructuredPostal.POBOX);
    add(StructuredPostal.NEIGHBORHOOD);
    add(StructuredPostal.CITY);
    add(StructuredPostal.REGION);
    add(StructuredPostal.POSTCODE);
    add(StructuredPostal.COUNTRY);
    add(Note.NOTE);
    add(Website.URL);
    add(Im.DATA);
    add(Event.START_DATE);
    add(Event.TYPE);
  }};

  private static final List<String> FULL_PROJECTION = new ArrayList<String>() {{
    addAll(JUST_ME_PROJECTION);
  }};

  private final ContentResolver contentResolver;

  public ContactsProvider(ContentResolver contentResolver) {
    this.contentResolver = contentResolver;
  }

  public Map<String, Contact> getContacts() {
    Map<String, Contact> justMe;
    {
      try (Cursor cursor = contentResolver.query(
        Uri.withAppendedPath(ContactsContract.Profile.CONTENT_URI, ContactsContract.Contacts.Data.CONTENT_DIRECTORY),
        JUST_ME_PROJECTION.toArray(new String[JUST_ME_PROJECTION.size()]),
        null,
        null,
        null
      )) {
        justMe = loadContactsFrom(cursor);
      }
    }

    Map<String, Contact> everyoneElse;
    {
      try (Cursor cursor = contentResolver.query(
        ContactsContract.Data.CONTENT_URI,
        FULL_PROJECTION.toArray(new String[FULL_PROJECTION.size()]),
        ContactsContract.Data.MIMETYPE + "=? OR "
          + ContactsContract.Data.MIMETYPE + "=? OR "
          + ContactsContract.Data.MIMETYPE + "=? OR "
          + ContactsContract.Data.MIMETYPE + "=? OR "
          + ContactsContract.Data.MIMETYPE + "=? OR "
          + ContactsContract.Data.MIMETYPE + "=? OR "
          + ContactsContract.Data.MIMETYPE + "=? OR "
          + ContactsContract.Data.MIMETYPE + "=? OR "
          + ContactsContract.Data.MIMETYPE + "=?",
        new String[]{
          Email.CONTENT_ITEM_TYPE,
          Phone.CONTENT_ITEM_TYPE,
          StructuredName.CONTENT_ITEM_TYPE,
          Organization.CONTENT_ITEM_TYPE,
          StructuredPostal.CONTENT_ITEM_TYPE,
          Note.CONTENT_ITEM_TYPE,
          Website.CONTENT_ITEM_TYPE,
          Im.CONTENT_ITEM_TYPE,
          Event.CONTENT_ITEM_TYPE,
        },
        null
      )) {
        everyoneElse = loadContactsFrom(cursor);
      }
    }

    justMe.putAll(everyoneElse);
    return justMe;
  }

  @NonNull
  private Map<String, Contact> loadContactsFrom(Cursor cursor) {
    Map<String, Contact> map = new LinkedHashMap<>();

    while (cursor != null && cursor.moveToNext()) {
      int columnIndexContactId = cursor.getColumnIndex(ContactsContract.Data.CONTACT_ID);
      int columnIndexId = cursor.getColumnIndex(ContactsContract.Data._ID);
      int columnIndexRawContactId = cursor.getColumnIndex(ContactsContract.Data.RAW_CONTACT_ID);
      String contactId;
      String id;
      String rawContactId;
      if (columnIndexContactId != -1) {
        contactId = cursor.getString(columnIndexContactId);
      } else {
        //todo - double check this, it may not be necessary any more
        contactId = String.valueOf(ID_FOR_PROFILE_CONTACT);//no contact id for 'ME' user
      }

      if (columnIndexId != -1) {
        id = cursor.getString(columnIndexId);
      } else {
        //todo - double check this, it may not be necessary any more
        id = String.valueOf(ID_FOR_PROFILE_CONTACT);//no contact id for 'ME' user
      }

      if (columnIndexRawContactId != -1) {
        rawContactId = cursor.getString(columnIndexRawContactId);
      } else {
        //todo - double check this, it may not be necessary any more
        rawContactId = String.valueOf(ID_FOR_PROFILE_CONTACT);//no contact id for 'ME' user
      }

      if (!map.containsKey(contactId)) {
        map.put(contactId, new Contact(contactId));
      }

      Contact contact = map.get(contactId);
      String mimeType = cursor.getString(cursor.getColumnIndex(ContactsContract.Data.MIMETYPE));
      String name = cursor.getString(cursor.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME));
      contact.rawContactId = rawContactId;
      if (!TextUtils.isEmpty(name) && TextUtils.isEmpty(contact.displayName)) {
        contact.displayName = name;
      }

      if (TextUtils.isEmpty(contact.photoUri)) {
        String rawPhotoURI = cursor.getString(cursor.getColumnIndex(Contactables.PHOTO_URI));
        if (!TextUtils.isEmpty(rawPhotoURI)) {
          contact.photoUri = rawPhotoURI;
          contact.hasPhoto = true;
        }
      }

      switch(mimeType) {
        case StructuredName.CONTENT_ITEM_TYPE:
          contact.givenName = cursor.getString(cursor.getColumnIndex(StructuredName.GIVEN_NAME));
          if (cursor.getString(cursor.getColumnIndex(StructuredName.MIDDLE_NAME)) != null) {
            contact.middleName = cursor.getString(cursor.getColumnIndex(StructuredName.MIDDLE_NAME));
          } else {
            contact.middleName = "";
          }
          if (cursor.getString(cursor.getColumnIndex(StructuredName.FAMILY_NAME)) != null) {
            contact.familyName = cursor.getString(cursor.getColumnIndex(StructuredName.FAMILY_NAME));
          } else {
            contact.familyName = "";
          }
          contact.prefix = cursor.getString(cursor.getColumnIndex(StructuredName.PREFIX));
          contact.suffix = cursor.getString(cursor.getColumnIndex(StructuredName.SUFFIX));
          break;
        case Phone.CONTENT_ITEM_TYPE:
          String phoneNumber = cursor.getString(cursor.getColumnIndex(Phone.NUMBER));
          int phoneType = cursor.getInt(cursor.getColumnIndex(Phone.TYPE));

          if (!TextUtils.isEmpty(phoneNumber)) {
            String label;
            switch (phoneType) {
              case Phone.TYPE_HOME:
                label = "home";
                break;
              case Phone.TYPE_WORK:
                label = "work";
                break;
              case Phone.TYPE_MOBILE:
                label = "mobile";
                break;
              case Phone.TYPE_OTHER:
                label = "other";
                break;
              default:
                label = "other";
            }
            contact.phones.add(new Contact.Item(label, phoneNumber, id));
          }
          break;
        case Email.CONTENT_ITEM_TYPE:
          String email = cursor.getString(cursor.getColumnIndex(Email.ADDRESS));
          int emailType = cursor.getInt(cursor.getColumnIndex(Email.TYPE));
          if (!TextUtils.isEmpty(email)) {
            String label;
            switch (emailType) {
              case Email.TYPE_HOME:
                label = "home";
                break;
              case Email.TYPE_WORK:
                label = "work";
                break;
              case Email.TYPE_MOBILE:
                label = "mobile";
                break;
              case Email.TYPE_OTHER:
                label = "other";
                break;
              case Email.TYPE_CUSTOM:
                if (cursor.getString(cursor.getColumnIndex(Email.LABEL)) != null) {
                  label = cursor.getString(cursor.getColumnIndex(Email.LABEL)).toLowerCase();
                } else {
                  label = "";
                }
                break;
              default:
                label = "other";
            }
            contact.emails.add(new Contact.Item(label, email, id));
          }
          break;
        case Website.CONTENT_ITEM_TYPE:
          String url = cursor.getString(cursor.getColumnIndex(Website.URL));
          int websiteType = cursor.getInt(cursor.getColumnIndex(Website.TYPE));
          if (!TextUtils.isEmpty(url)) {
            String label;
            switch (websiteType) {
              case Website.TYPE_HOMEPAGE:
                label = "homepage";
                break;
              case Website.TYPE_BLOG:
                label = "blog";
                break;
              case Website.TYPE_PROFILE:
                label = "profile";
                break;
              case Website.TYPE_HOME:
                label = "home";
                break;
              case Website.TYPE_WORK:
                label = "work";
                break;
              case Website.TYPE_FTP:
                label = "ftp";
                break;
              case Website.TYPE_CUSTOM:
                if (cursor.getString(cursor.getColumnIndex(Website.LABEL)) != null) {
                  label = cursor.getString(cursor.getColumnIndex(Website.LABEL)).toLowerCase();
                } else {
                  label = "";
                }
                break;
              default:
                label = "other";
            }
            contact.urls.add(new Contact.Item(label, url, id));
          }
          break;
        case Im.CONTENT_ITEM_TYPE:
          String username = cursor.getString(cursor.getColumnIndex(Im.DATA));
          int imType = cursor.getInt(cursor.getColumnIndex(Im.PROTOCOL));
          if (!TextUtils.isEmpty(username)) {
            String label;
            switch (imType) {
              case Im.PROTOCOL_AIM:
                label = "AIM";
                break;
              case Im.PROTOCOL_MSN:
                label = "MSN";
                break;
              case Im.PROTOCOL_YAHOO:
                label = "Yahoo";
                break;
              case Im.PROTOCOL_SKYPE:
                label = "Skype";
                break;
              case Im.PROTOCOL_QQ:
                label = "QQ";
                break;
              case Im.PROTOCOL_GOOGLE_TALK:
                label = "Google Talk";
                break;
              case Im.PROTOCOL_ICQ:
                label = "ICQ";
                break;
              case Im.PROTOCOL_JABBER:
                label = "Jabber";
                break;
              case Im.PROTOCOL_NETMEETING:
                label = "NetMeeting";
                break;
              case Im.PROTOCOL_CUSTOM:
                if (cursor.getString(cursor.getColumnIndex(Im.CUSTOM_PROTOCOL)) != null) {
                  label = cursor.getString(cursor.getColumnIndex(Im.CUSTOM_PROTOCOL));
                } else {
                  label = "";
                }
                break;
              default:
                label = "other";
            }
            contact.instantMessengers.add(new Contact.Item(label, username, id));
          }
          break;
        case Organization.CONTENT_ITEM_TYPE:
          contact.company = cursor.getString(cursor.getColumnIndex(Organization.COMPANY));
          contact.jobTitle = cursor.getString(cursor.getColumnIndex(Organization.TITLE));
          contact.department = cursor.getString(cursor.getColumnIndex(Organization.DEPARTMENT));
          break;
        case StructuredPostal.CONTENT_ITEM_TYPE:
          contact.postalAddresses.add(Contact.PostalAddress.postalAddressFromCursor(cursor));
          break;
        case Event.CONTENT_ITEM_TYPE:
          int eventType = cursor.getInt(cursor.getColumnIndex(Event.TYPE));
          if (eventType == Event.TYPE_BIRTHDAY) {
            try {
              String birthday = cursor.getString(cursor.getColumnIndex(Event.START_DATE)).replace("--", "");
              String[] yearMonthDay = birthday.split("-");
              List<String> yearMonthDayList = Arrays.asList(yearMonthDay);

              if (yearMonthDayList.size() == 2) {
                // birthday is formatted "12-31"
                int month = Integer.parseInt(yearMonthDayList.get(0));
                int day = Integer.parseInt(yearMonthDayList.get(1));
                if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
                  contact.birthday = new Contact.Birthday(month, day);
                }
              } else if (yearMonthDayList.size() == 3) {
                // birthday is formatted "1986-12-31"
                int year = Integer.parseInt(yearMonthDayList.get(0));
                int month = Integer.parseInt(yearMonthDayList.get(1));
                int day = Integer.parseInt(yearMonthDayList.get(2));
                if (year > 0 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
                  contact.birthday = new Contact.Birthday(year, month, day);
                }
              }
            } catch (NumberFormatException | ArrayIndexOutOfBoundsException | NullPointerException e) {
              // whoops, birthday isn't in the format we expect
              Log.w("ContactsProvider", e.toString());
            }
          }
          break;
        case Note.CONTENT_ITEM_TYPE:
          contact.note = cursor.getString(cursor.getColumnIndex(Note.NOTE));
          break;
      }
    }

    return map;
  }
}
