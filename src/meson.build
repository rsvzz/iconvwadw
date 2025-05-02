inc_src = include_directories('../src', '../inc')
subdir('model_gtk')
subdir('model')

gtk_dep = dependency('gtkmm-4.0')

syslocal = host_machine.system()

# Instala el archivo solo en Linux
if syslocal == 'linux'
   install_data('../data/io.github.rsvzz.iconvwadw.svg', install_dir: get_option('prefix') / 'share/icons/hicolor/scalable/apps')
   #install_data('../data/io.github.rsvzz.iconvwadw.metainfo.xml', install_dir: get_option('prefix') / 'share/metainfo')

   install_data(
    '../data/io.github.rsvzz.iconvwadw.desktop',
    install_dir: join_paths(get_option('prefix'), 'share/applications')
)
endif

executable('iconvwadw',
  sources: 'main.cpp',
  include_directories: [inc_src],
  dependencies: [gtk_dep],
  link_with: [
      mgtk_dep, m_dep
   ],
   install: true
  #link_args: ['/SUBSYSTEM:WINDOWS'] #windows,,
)