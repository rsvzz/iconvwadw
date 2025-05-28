inc_src = include_directories('../../src', '../../inc')
src_files = files([
    'csfile.c',
    'cstexture.c'
])

gtk_dep = dependency('gtk4')
librsvg_dep = dependency('librsvg-2.0')
cairo_dep = dependency('cairo')

optc_dep = static_library(
    'liboptc', 
    sources: src_files,
    include_directories: inc_src,
    dependencies: [librsvg_dep, cairo_dep, gtk_dep]
)