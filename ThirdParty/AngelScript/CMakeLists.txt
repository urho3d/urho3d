# Define target name
set (TARGET_NAME AngelScript)

# Define source files
set (CPP_FILES
    source/as_atomic.cpp source/as_builder.cpp source/as_bytecode.cpp source/as_callfunc.cpp
    source/as_callfunc_x86.cpp source/as_compiler.cpp source/as_configgroup.cpp source/as_context.cpp 
    source/as_datatype.cpp source/as_gc.cpp source/as_generic.cpp source/as_globalproperty.cpp source/as_memory.cpp 
    source/as_module.cpp source/as_objecttype.cpp source/as_outputbuffer.cpp source/as_parser.cpp source/as_restore.cpp 
    source/as_scriptcode.cpp source/as_scriptengine.cpp source/as_scriptfunction.cpp source/as_scriptnode.cpp 
    source/as_scriptobject.cpp source/as_string.cpp source/as_string_util.cpp source/as_thread.cpp 
    source/as_tokenizer.cpp source/as_typeinfo.cpp source/as_variablescope.cpp
)

file (GLOB H_FILES
    include/*.h source/*.h
)

set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    include source
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
finalize_lib ()