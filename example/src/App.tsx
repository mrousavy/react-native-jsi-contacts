import * as React from 'react';
import { StyleSheet, View, Text, Alert } from 'react-native';
import { Contact, getContactsAsync } from 'react-native-jsi-contacts';
import { check, PERMISSIONS, request } from 'react-native-permissions';

export default function App() {
  const [result, setResult] = React.useState<Contact[]>([]);

  const load = React.useCallback(async () => {
    const permission = await check(PERMISSIONS.ANDROID.READ_CONTACTS);
    if (permission !== 'granted') {
      const requestResult = await request(PERMISSIONS.ANDROID.READ_CONTACTS);
      if (requestResult !== 'granted') {
        Alert.alert(
          'Permission denied!',
          'Permission to access contacts has been denied.'
        );
      }
    }
    console.log(`Contacts Permission: ${permission}`);
    const contacts = await getContactsAsync();
    console.log(`Got: ${JSON.stringify(contacts)}`);
    setResult(contacts);
  }, []);

  React.useEffect(() => {
    load();
  }, [load]);

  const str = React.useMemo(
    () => result.map((c) => c.firstName).join(', '),
    [result]
  );

  return (
    <View style={styles.container}>
      <Text>Result: {str}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
