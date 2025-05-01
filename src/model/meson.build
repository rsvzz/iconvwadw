inc_src = include_directories('../../src', '../../inc')
src_files = files([
    'readdir.cpp',
    'readfile.cpp'
])

m_dep = static_library(
    'mlsdep', 
    sources: src_files,
    include_directories: inc_src
)