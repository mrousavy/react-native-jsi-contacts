import * as React from 'react';

import { StyleSheet, View, Text } from 'react-native';
import { Contact, getContactsAsync } from 'react-native-jsi-contacts';

export default function App() {
  const [result, setResult] = React.useState<Contact[]>([]);

  React.useEffect(() => {
    getContactsAsync().then((contacts) => {
      console.log(`Got: ${JSON.stringify(contacts)}`);
      setResult(contacts);
    });
  }, []);

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
