# react-native-jsi-contacts

The current **react-native-contacts** library uses the _React Native Bridge_ to convert the native Java/Objective-C types to JavaScript values. This is asynchronous, batched, and serializes the huge contacts list in the native world (write into `WritableArray`/`WritableMap`, then let the Bridge convert to JSON), then deserializes it on the JavaScript side using JSON. It is therefore slow.

react-native-jsi-contacts uses JSI to be way faster.

* Direct invocation (no batching!)
* No JSON serialization happening
* Directly convert object into JSI Types
* Lazily get individual Contact fields (`jsi::HostObject` lazy-get)

## Performance

The library uses almost the same native "`getContacts()`" function as [react-native-contacts](https://github.com/morenoh149/react-native-contacts) (minor tweaks to not use the Bridge types `WritableArray`/`WritableMap`), so the only difference is the conversion speed.

For 25 contacts, I have measured an average speed increase of ~35%, this greatly scales with the amount of contacts you have though.

```
 LOG  JSI: Contacts Permission: granted
 LOG  JSI: Got: 25 contacts in 55.14947900176048ms.
 LOG  Bridge: Contacts Permission: granted
 LOG  Bridge: Got: 25 contacts in 74.15260401368141ms.
```

> For 25 contacts, the conversion between the native Java Contacts list and the JavaScript Contacts list takes only ~3 milliseconds!

## Installation

1. Install using npm/yarn
    ```sh
    npm install react-native-jsi-contacts
    ```

2. Add this code:

    ```java
    JsiContactsModule.install(reactApplicationContext);
    ```

    to your `JSIModulePackage`. See [the react-native-mmkv installation guide](https://github.com/mrousavy/react-native-mmkv/blob/master/INSTALL.md) on how to create a `JSIModulePackage`.

## Sponsors

<a href="https://www.galaxycard.in"><img src="https://www.galaxycard.in/img/logo.svg" align="right" height="50"></a>

This project is sponsored by [Galaxycard](https://www.galaxycard.in).

## Usage

```js
import { getContactsAsync } from "react-native-jsi-contacts";

const contacts = await getContactsAsync();
```

## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT

## Thanks

* Thanks to GalaxyCard for sponsoring this project
* Thanks to react-native-contacts for the native "`getContacts()`" implementation
