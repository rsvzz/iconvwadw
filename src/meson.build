inc_src = include_directories('../src', '../inc')
subdir('model_gtk')
subdir('model')

gtk_dep = dependency('gtkmm-4.0')

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