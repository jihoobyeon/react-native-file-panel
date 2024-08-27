const FilePanel = require('./NativeFilePanel').default;

export function openFile(ext?: string[]): Promise<string> {
  if (ext) {
    return FilePanel.openFile(ext);
  } else {
    return FilePanel.openFile(['*']);
  }
}

export function openFiles(ext?: string[]): Promise<string[]> {
  if (ext) {
    return FilePanel.openFiles(ext);
  } else {
    return FilePanel.openFiles(['*']);
  }
}

export function openFolder(): Promise<string> {
  return FilePanel.openFolder();
}

export function saveFile(content: string, ext?: string[]): Promise<void> {
  if (ext) {
    return FilePanel.saveFile(content, ext);
  } else {
    return FilePanel.saveFile(content, ['*']);
  }
}
