# header files
set( MODIFIERS_HEADER_BASENAMES
    KSModifiersMessage.h
    KSModDynamicEnhancement.h
    KSModSplitOnTurn.h
    KSModEventReport.h
)
set( MODIFIERS_HEADER_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)
foreach( BASENAME ${MODIFIERS_HEADER_BASENAMES} )
    list( APPEND MODIFIERS_HEADER_FILENAMES ${MODIFIERS_HEADER_PATH}/${BASENAME} )
endforeach( BASENAME )

# source files
set( MODIFIERS_SOURCE_BASENAMES
    KSModifiersMessage.cxx
    KSModDynamicEnhancement.cxx
    KSModSplitOnTurn.cxx
    KSModEventReport.cxx
)
set( MODIFIERS_SOURCE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)
foreach( BASENAME ${MODIFIERS_SOURCE_BASENAMES} )
    list( APPEND MODIFIERS_SOURCE_FILENAMES ${MODIFIERS_SOURCE_PATH}/${BASENAME} )
endforeach( BASENAME )

# data files
set( MODIFIERS_DATA_BASENAMES
)
set( MODIFIERS_DATA_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/Data
)
foreach( BASENAME ${MODIFIERS_DATA_BASENAMES} )
    list( APPEND MODIFIERS_DATA_FILENAMES ${MODIFIERS_DATA_PATH}/${BASENAME} )
endforeach( BASENAME )

# library
add_library( KassiopeiaModifiers SHARED
    ${MODIFIERS_SOURCE_FILENAMES} ${MODIFIERS_HEADER_FILENAMES} )
target_include_directories(KassiopeiaModifiers
    PUBLIC $<BUILD_INTERFACE:${MODIFIERS_HEADER_PATH}> $<INSTALL_INTERFACE:include> )
target_link_libraries( KassiopeiaModifiers
    PUBLIC
        KassiopeiaTrajectories
        KassiopeiaInteractions
)

# install
kasper_install_headers( ${MODIFIERS_HEADER_FILENAMES} )
kasper_install_data( ${MODIFIERS_DATA_FILENAMES} )
kasper_install_libraries( KassiopeiaModifiers )
