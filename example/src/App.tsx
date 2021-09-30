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
    console.log(`Contacts Permission: ${permission}`);
    const begin = global.performance.now();
    const contacts = await getContactsAsync();
    const end = global.performance.now();
    console.log(`Got: ${contacts.length} contacts in ${end - begin}ms.`);
    setResult(contacts);
  }, []);

  React.useEffect(() => {
    load();
  }, [load]);

  const str = React.useMemo(
    () => result.map((c) => c.displayName).join(', '),
    [result]
  );

  return (
    <View style={styles.container}>
      <FlatList
        data={result}
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
