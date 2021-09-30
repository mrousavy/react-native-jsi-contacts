import * as React from 'react';
import { StyleSheet, View, Text, Alert, FlatList } from 'react-native';
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

    console.log(`JSI: Contacts Permission: ${permission}`);
    const contacts = await getContactsAsync();
    const arr = Object.keys(contacts).map((key) => contacts[key]);
    setResult(arr);
  }, []);

  React.useEffect(() => {
    load();
  }, [load]);

  return (
    <View style={styles.container}>
      <FlatList
        data={result}
        keyExtractor={(contact) => contact.contactId}
        renderItem={({ item }) => (
          <Text style={{ marginTop: 5 }}>{item.displayName}</Text>
        )}
      />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    paddingVertical: 20,
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
