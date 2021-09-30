interface JSIContactsInterface {
  getContactsAsync(): Promise<Contact[]>;
}

// Globally injected JSI Function declarations
declare global {
  var JSIContacts: JSIContactsInterface;
}

export interface Contact {
  firstName: string;
}

export function getContactsAsync(): Promise<Contact[]> {
  return JSIContacts.getContactsAsync();
}
