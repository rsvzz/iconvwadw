inc_src = include_directories('../../src', '../../inc')
src_files = files([
    'app.cpp',
    'bxbody.cpp',
    'bxnav.cpp',
    'itemfiles.cpp',
    'gdview.cpp',
    'imgevt.cpp',
    'winimg.cpp',
    'svgcv.cpp'
])

gtk_dep = dependency('gtkmm-4.0')

mgtk_dep = static_library(
    'mgtk', 
    sources: src_files,
    include_directories: inc_src,
    dependencies: [gtk_dep]
)