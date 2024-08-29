# react-native-file-panel
> A native module which implements file picker panel for React Native for Windows/macOS

## Installation
`yarn add react-native-file-panel`\
If you are using this library for macOS, you have to run `USE_HERMES=1 RCT_NEW_ARCH_ENABLED=1 bundle exec pod install` at `{your-project}/macos/` folder before build your app.

### Prerequisites
Your React Native app must be [New Architecture](https://reactnative.dev/docs/the-new-architecture/landing-page) app.

To make a new arch React Native app. follow [here](https://github.com/microsoft/react-native-windows/wiki/Using-the-new-architecture-templates) for Windows, and [here](https://github.com/reactwg/react-native-new-architecture/blob/main/docs/enable-apps.md) for macOS.\
If you are using this library for macOS, you have to modify `{your-project}/macos/Podfile` to `platform :macos, '11.0'`(or over 11.0) and `:hermes_enabled => true`.

## Usage
**`ext`(File extensions) must include `.`(dot)**

### `openFile(ext?: string|string[])`: `Promise<string>`
Opens a file picker panel which allows only to pick one file and open it.\
If file has picked, the file will be encoded to base64 string and sent inside to JavaScript context. so if it's text file, you have to decode that base64 string.

Sample code:
```
import { JSX } from 'react';
import { Button, View } from 'react-native';
import { openFile } from 'react-native-file-panel';

export default function App(): JSX.Element {
  return (
    <View>
      <Button title='TestAny' onPress={ async () => console.log(await openFile()) } />
      <Button title='TestTxt' onPress={ async () => console.log(await openFile('.txt')) } />
      <Button title='TestMulti' onPress={ async () => console.log(await openFile(['.txt', '.md'])) } />
    </View>
  );
}
```

### `openFiles(ext?: string|string[])`: `Promise<string[]>`
Opens a file picker panel which allows to pick more than one file and open it.\
Same as `openFile`, but returns an array of base64-encoded string.

Sample code:
```
import { JSX } from 'react';
import { Button, View } from 'react-native';
import { openFiles } from 'react-native-file-panel';

export default function App(): JSX.Element {
  return (
    <View>
      <Button title='TestAny' onPress={ async () => console.log(await openFiles()) } />
      <Button title='TestTxts' onPress={ async () => console.log(await openFiles('.txt')) } />
      <Button title='TestMulti' onPress={ async () => console.log(await openFiles(['.txt', '.md'])) } />
    </View>
  );
}
```

### `openFolder()`: `Promise<string[]>`
Opens a folder picker panel which allows to pick a folder and open it.\
If folder has picked, returns absolute path(Windows)/URI(macOS) of the folder.

Sample code:
```
import { JSX } from 'react';
import { Button, View } from 'react-native';
import { openFolder } from 'react-native-file-panel';

export default function App(): JSX.Element {
  return (
    <View>
      <Button title='TestFolder' onPress={ async () => console.log(await openFolder()) } />
    </View>
  );
}
```

### `saveFile(ext: string|string[], content: string)`: `Promise<void>`
Opens a file picker panel which allows to pick/make a file and save contents to it.\
**`content` must be base64-encoded string.**
**Least one file extension required.**

Sample code:
```
import { JSX } from 'react';
import { Button, View } from 'react-native';
import { saveFile } from 'react-native-file-panel';

export default function App(): JSX.Element {
  return (
    <View>
      <Button title='TestSave' onPress={ async () => await saveFile('.txt', 'VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZy4=') } />
    </View>
  );
}
```
