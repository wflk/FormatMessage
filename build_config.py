build_config = {
  "version": '0.1 alpha',
  "projects": {
    'FormatMessage': {
      "debug": True,
      "static link": True,
      "architecture": "x86",
      "files": {
        'FormatMessage.exe': {
          "sources": ['FormatMessage.obj'],
          "libs":    ['Kernel32.lib', 'Shell32.lib'],
        },
        'FormatMessage.obj': {
          "sources": ['FormatMessage.c']
        }
      }
    },
  }
}
