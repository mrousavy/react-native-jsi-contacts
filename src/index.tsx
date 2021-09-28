// Globally injected JSI Function declarations
declare global {
  function __JSIContacts_getContactsAsync(): Promise<Contact[]>;
}

export interface Contact {
  firstName: string;
}

export function getContactsAsync(): Promise<Contact[]> {
  return __JSIContacts_getContactsAsync();
}
