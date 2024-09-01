import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  openFile(ext: string[], defaultPath: string): Promise<string>;
  openFiles(ext: string[], defaultPath: string): Promise<string[]>;
  openFolder(defaultPath: string): Promise<string>;
  saveFile(ext: string[], content: string, defaultPath: string): Promise<string>;
}

export default TurboModuleRegistry.getEnforcing<Spec>('FilePanel');
