inc_src = include_directories('../../src', '../../inc')
src_files = files([
    'navbox.cpp',
    'boxbody.cpp',
    'svgconvert.cpp',
    'gdataview.cpp',
    'imagegestore.cpp',
    'file_item.cpp',
    'win_image_view.cpp',
    'list_view_content.cpp',
    'nav_split_view.cpp',
    'tool_view.cpp',
    'nav_content.cpp'
    
])

gtk_dep = dependency('gtk4')

mgtk_dep = static_library(
    'mgtk', 
    sources: src_files,
    include_directories: inc_src,
    dependencies: [gtk_dep]
)