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

export function saveFile(ext: string | string[], content: string): Promise<string> {
  if (typeof ext === 'string') return FilePanel.saveFile([ext], content);
  else return FilePanel.saveFile(ext, content);
}
