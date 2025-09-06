inc_src = include_directories('../../src', '../../inc')
src_files = files([
    'svgdraw.c',
    'grid_item.c',
    'list_item.c'
])

gtk_dep = dependency('gtk4')
glib_dep = dependency('glib-2.0')
gobj_dep = dependency('gobject-2.0')
librsvg_dep = dependency('librsvg-2.0')
cairo_dep = dependency('cairo')

optc_dep = static_library(
    'liboptc', 
    sources: src_files,
    include_directories: inc_src,
    dependencies: [librsvg_dep, cairo_dep, gtk_dep, glib_dep, gobj_dep]
)