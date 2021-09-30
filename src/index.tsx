interface JSIContactsInterface {
  getContactsAsync(): Promise<Contact[]>;
}

// Globally injected JSI Function declarations
declare global {
  var JSIContacts: JSIContactsInterface;
}

export interface EmailAddress {
  label: string;
  email: string;
}

export interface PhoneNumber {
  label: string;
  number: string;
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
  recordID: string;
  backTitle: string;
  company: string | null;
  emailAddresses: EmailAddress[];
  displayName: string;
  familyName: string;
  givenName: string;
  middleName: string;
  jobTitle: string;
  phoneNumbers: PhoneNumber[];
  hasThumbnail: boolean;
  thumbnailPath: string;
  postalAddresses: PostalAddress[];
  prefix: string;
  suffix: string;
  department: string;
  birthday: Birthday;
  imAddresses: InstantMessageAddress[];
  note: string;
}

export function getContactsAsync(): Promise<Contact[]> {
  return JSIContacts.getContactsAsync();
}
