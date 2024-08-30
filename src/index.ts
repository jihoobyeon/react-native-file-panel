const FilePanel = require('./NativeFilePanel').default;

export function openFile(ext?: string | string[]): Promise<string> {
  if (ext) {
    if (typeof ext === 'string') return FilePanel.openFile([ext]);
    else return FilePanel.openFile(ext);
  } else return FilePanel.openFile(['*']);
}

export function openFiles(ext?: string | string[]): Promise<string[]> {
  if (ext) {
    if (typeof ext === 'string') return FilePanel.openFiles([ext]);
    else return FilePanel.openFiles(ext);
  } else return FilePanel.openFiles(['*']);
}

export function openFolder(): Promise<{ path: string, files: string[] }> {
  return FilePanel.openFolder();
}

export function saveFile(ext: string | string[], content: string): Promise<void> {
  if (typeof ext === 'string') return FilePanel.saveFile([ext], content);
  else return FilePanel.saveFile(ext, content);
}

export const UserPath: string = FilePanel.getConstants().RCTUserPath;
export const BundlePath: string = FilePanel.getConstants().RCTBundlePath;
