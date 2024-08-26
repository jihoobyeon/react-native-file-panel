const FilePanel = require('./NativeFilePanel').default;

export function openFile(ext?: string[]): Promise<Buffer> {
  if (ext) {
    return FilePanel.openFile(ext);
  } else {
    return FilePanel.openFile(['*']);
  }
}

export function openFiles(ext?: string[]): Promise<Buffer[]> {
  if (ext) {
    return FilePanel.openFiles(ext);
  } else {
    return FilePanel.openFiles(['*']);
  }
}

export async function openFolder(): Promise<Buffer> {
  return FilePanel.openFolder();
}

export function saveFile(content: Buffer, text?: string[]): Promise<Buffer[]> {
  if (ext) {
    return FilePanel.saveFile(content, ext);
  } else {
    return FilePanel.saveFile(content, ['*']);
  }
}