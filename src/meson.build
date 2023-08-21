viral_sources = [
  'main.c',
  'viral-window.c',
  'viral-application.c',
  'viral-progress-icon.c',
  'viral-file-row.c',
  'viral-progress-info-popover.c',
  'corrupt.c'
]

# Generate UX files from blueprint files.
blueprints = custom_target('blueprints',
  input: files(
    'viral-window.blp',
    'viral-file-row.blp',
    'viral-progress-info-popover.blp',
    'viral-shortcuts.blp',
  ),
  output: '.',
  command: [find_program('blueprint-compiler'), 'batch-compile', '@OUTPUT@', '@CURRENT_SOURCE_DIR@', '@INPUT@'],
)

viral_sources += gnome.compile_resources('viral-resources',
  'viral.gresource.xml',
  dependencies: blueprints,
  c_name: 'viral'
)

executable('viral', viral_sources,
  dependencies: viral_deps,
  install: true,
)
