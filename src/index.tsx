const FilePanel = require('./NativeFilePanel').default;

export function openFile(ext?: string[]): Promise<object> {
  if (ext) {
    return FilePanel.openFile(ext);
  } else {
    return FilePanel.openFile(['*']);
  }
}

export function openFiles(ext?: string[]): Promise<object[]> {
  if (ext) {
    return FilePanel.openFiles(ext);
  } else {
    return FilePanel.openFiles(['*']);
  }
}

export function openFolder(): Promise<object> {
  return FilePanel.openFolder();
}

export function saveFile(content: unknown, ext?: string[]): Promise<void> {
  if (ext) {
    return FilePanel.saveFile(content, ext);
  } else {
    return FilePanel.saveFile(content, ['*']);
  }
}
