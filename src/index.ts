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

export function openFolder(): Promise<string> {
  return FilePanel.openFolder();
}

export function saveFile(content: string, ext: string | string[]): Promise<void> {
  if (typeof ext === 'string') return FilePanel.saveFile(content, [ext]);
  else return FilePanel.saveFile(content, ext);
}