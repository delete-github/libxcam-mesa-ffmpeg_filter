lib_LTLIBRARIES = libxcam_gles.la

XCAM_GLES_CXXFLAGS = \
    $(XCAM_CXXFLAGS)                \
    $(LIBGL_CFLAGS)                 \
    -I$(top_srcdir)/xcore           \
    -I$(top_srcdir)/modules         \
    -I$(top_builddir)/shaders/glslx \
    $(NULL)

XCAM_GLES_LIBS = \
    $(LIBGL_LIBS) -lEGL                   \
    $(top_builddir)/xcore/libxcam_core.la \
    $(NULL)

if HAVE_OPENCV
XCAM_GLES_LIBS += $(top_builddir)/modules/ocv/libxcam_ocv.la
endif

if HAVE_GBM
XCAM_GLES_LIBS += $(LIBGL_LIBS) -lgbm
endif

xcam_gles_sources = \
    gles_std.cpp           \
    gl_buffer.cpp          \
    gl_texture.cpp         \
    gl_program.cpp         \
    gl_sync.cpp            \
    gl_shader.cpp          \
    gl_video_buffer.cpp    \
    gl_compute_program.cpp \
    gl_command.cpp         \
    gl_utils.cpp           \
    gl_image_shader.cpp    \
    gl_image_handler.cpp   \
    gl_copy_handler.cpp    \
    gl_dma_buffer_handler.cpp \
    gl_geomap_handler.cpp  \
    gl_blender.cpp         \
    gl_fastmap_blender.cpp \
    gl_stitcher.cpp        \
    egl/egl_utils.cpp      \
    egl/egl_base.cpp       \
    $(NULL)

libxcam_gles_la_SOURCES = \
    $(xcam_gles_sources) \
    $(NULL)

libxcam_gles_la_CXXFLAGS = \
    $(XCAM_GLES_CXXFLAGS) \
    $(NULL)

libxcam_gles_la_LIBADD = \
    $(XCAM_GLES_LIBS) \
    $(NULL)

libxcam_gles_la_LDFLAGS = \
    $(XCAM_LT_LDFLAGS) \
    $(NULL)

libxcam_glesincludedir = $(includedir)/xcam/gles

nobase_libxcam_glesinclude_HEADERS = \
    gles_std.h           \
    gl_buffer.h          \
    gl_program.h         \
    gl_sync.h            \
    gl_shader.h          \
    gl_video_buffer.h    \
    gl_compute_program.h \
    gl_command.h         \
    gl_utils.h           \
    gl_image_shader.h    \
    gl_image_handler.h   \
    gl_copy_handler.h    \
    gl_geomap_handler.h  \
    gl_blender.h         \
    gl_fastmap_blender.h \
    gl_stitcher.h        \
    egl/egl_utils.h      \
    egl/egl_base.h       \
    $(NULL)

libxcam_gles_la_LIBTOOLFLAGS = --tag=disable-static
