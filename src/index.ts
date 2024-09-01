const FilePanel = require('./NativeFilePanel').default;

export function openFile(ext?: string | string[], defaultPath?: string): Promise<string> {
  if (defaultPath) {
    if (ext) {
      if (typeof ext === 'string') return FilePanel.openFile([ext], defaultPath);
      else return FilePanel.openFile(ext, defaultPath);
    } else return FilePanel.openFile(['*'], defaultPath);
  } else {
    if (ext) {
      if (typeof ext === 'string') return FilePanel.openFile([ext], '*');
      else return FilePanel.openFile(ext, '*');
    } else return FilePanel.openFile(['*'], '*');
  }
}

export function openFiles(ext?: string | string[], defaultPath?: string): Promise<string[]> {
  if (defaultPath) {
    if (ext) {
      if (typeof ext === 'string') return FilePanel.openFiles([ext], defaultPath);
      else return FilePanel.openFiles(ext, defaultPath);
    } else return FilePanel.openFiles(['*'], defaultPath);
  } else {
    if (ext) {
      if (typeof ext === 'string') return FilePanel.openFiles([ext], '*');
      else return FilePanel.openFiles(ext, '*');
    } else return FilePanel.openFiles(['*'], '*');
  }
}

export function openFolder(defaultPath?: string): Promise<string> {
  if (defaultPath) return FilePanel.openFolder(defaultPath);
  else return FilePanel.openFolder('*');
}

export function saveFile(ext: string | string[], content: string, defaultPath?: string): Promise<string> {
  if (defaultPath) {
    if (typeof ext === 'string') return FilePanel.saveFile([ext], content, defaultPath);
    else return FilePanel.saveFile(ext, content, defaultPath);
  } else {
    if (typeof ext === 'string') return FilePanel.saveFile([ext], content, '*');
    else return FilePanel.saveFile(ext, content, '*');
  }
}
