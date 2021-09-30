interface JSIContactsInterface {
  getContactsAsync(): Promise<Record<Contact['contactId'], Contact>>;
}

// Globally injected JSI Function declarations
declare global {
  var JSIContacts: JSIContactsInterface;
}

export interface Item {
  id: string;
  label: string;
  value: string;
}

export interface PostalAddress {
  label: string;
  formattedAddress: string;
  street: string;
  pobox: string;
  neighborhood: string;
  city: string;
  region: string;
  state: string;
  postCode: string;
  country: string;
}

export interface InstantMessageAddress {
  username: string;
  service: string;
}

export interface Birthday {
  day: number;
  month: number;
  year: number;
}

export interface Contact {
  contactId: string;
  displayName: string;
  givenName: string;
  middleName: string;
  familyName: string;
  prefix: string;
  suffix: string;
  company: string;
  jobTitle: string;
  department: string;
  note: string;
  urls: Item[];
  instantMessengers: InstantMessageAddress[];
  hasPhoto: boolean;
  photoUri: string;
  emails: Item[];
  phones: Item[];
  postalAddresses: PostalAddress[];
  birthday: Birthday;
}

export function getContactsAsync(): Promise<
  Record<Contact['contactId'], Contact>
> {
  return JSIContacts.getContactsAsync();
}
