import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  openFile(ext: string[]): Promise<object>;
  openFiles(ext: string[]): Promise<object[]>;
  openFolder(): Promise<object>;
  saveFile(content: unknown, ext: string[]): Promise<void>;
}

export default TurboModuleRegistry.getEnforcing<Spec>('FilePanel');
