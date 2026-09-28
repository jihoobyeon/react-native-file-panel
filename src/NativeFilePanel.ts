import { TurboModuleRegistry, type TurboModule } from 'react-native';

export interface Spec extends TurboModule {
  openFile(ext: string[]): Promise<string>;
  openFiles(ext: string[]): Promise<string[]>;
  openFolder(): Promise<string>;
  saveFile(ext: string[], content: string): Promise<string>;
}

export default TurboModuleRegistry.getEnforcing<Spec>('FilePanel');
