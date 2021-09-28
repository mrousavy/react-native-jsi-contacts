import { NativeModules, Platform } from 'react-native';

const LINKING_ERROR =
  `The package 'react-native-jsi-contacts' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo managed workflow\n';

const JsiContacts = NativeModules.JsiContacts
  ? NativeModules.JsiContacts
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

export interface Contact {
  firstName: string;
}

export function getContactsAsync(): Promise<Contact[]> {
  return JsiContacts.getContactsAsync();
}
