import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  openFile(ext: string[]): Promise<Buffer>;
  openFiles(ext: string[]): Promise<Buffer[]>;
  openFolder(): Promise<object>;
  saveFile(content: Buffer, ext: string[]): Promise<void>;
}

export default TurboModuleRegistry.getEnforcing<Spec>('FilePanel');
