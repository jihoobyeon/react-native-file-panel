import { NativeModules } from 'react-native'

export function open(extension: string): Promise<string> { return NativeModules.Panel.open(extension) }
export function save(extension: string, content: string): Promise<string> { return NativeModules.Panel.save(extension, content) }
