add_library(qjs
    STATIC
    quickjs-amalgam/quickjs-amalgam.c
)

target_include_directories(qjs PUBLIC
    quickjs-amalgam
)

target_compile_definitions(qjs PRIVATE
    QJS_BUILD_LIBC
)
