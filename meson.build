project('viral', 'c', version: '2.0.0')

i18n = import('i18n')
gnome = import('gnome')

# Get all dependencies for Viral. Secure Delete should fallback, unless this is being packaged.
viral_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.0'),
  dependency('gio-unix-2.0')
]

# Create config.h file entirely in Meson.
config_h = configuration_data()
config_h.set_quoted('PACKAGE_VERSION', meson.project_version())
config_h.set_quoted('GETTEXT_PACKAGE', 'viral')
config_h.set_quoted('LOCALEDIR', join_paths(get_option('prefix'), get_option('localedir')))
configure_file(output: 'viral-config.h', configuration: config_h)
add_project_arguments(['-I' + meson.project_build_root(),], language: 'c')

# Folders with individual meson.build files.
subdir('data')
subdir('src')
subdir('po')

# GNOME specific actions to perform.
gnome.post_install(
  gtk_update_icon_cache: true,
  update_desktop_database: true,
)
