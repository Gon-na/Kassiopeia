# header files
set( OPERATORS_HEADER_BASENAMES
    KSOperatorsMessage.h
    KSParticle.h
    KSParticleFactory.h
    KSMagneticField.h
    KSElectricField.h
    KSGenerator.h
    KSTrajectory.h
    KSSpace.h
    KSSpaceInteraction.h
    KSSpaceNavigator.h
    KSSurface.h
    KSSurfaceInteraction.h
    KSSurfaceNavigator.h
    KSSide.h
    KSStepModifier.h
    KSTrackModifier.h
    KSEventModifier.h
    KSRunModifier.h
    KSTerminator.h
    KSWriter.h
)
set( OPERATORS_HEADER_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)
foreach( BASENAME ${OPERATORS_HEADER_BASENAMES} )
    list( APPEND OPERATORS_HEADER_FILENAMES ${OPERATORS_HEADER_PATH}/${BASENAME} )
endforeach( BASENAME )

# source files
set( OPERATORS_SOURCE_BASENAMES
    KSOperatorsMessage.cxx
    KSParticle.cxx
    KSParticleFactory.cxx
    KSMagneticField.cxx
    KSElectricField.cxx
    KSGenerator.cxx
    KSTrajectory.cxx
    KSSpace.cxx
    KSSpaceInteraction.cxx
    KSSpaceNavigator.cxx
    KSSurface.cxx
    KSSurfaceInteraction.cxx
    KSSurfaceNavigator.cxx
    KSSide.cxx
    KSStepModifier.cxx
    KSTrackModifier.cxx
    KSEventModifier.cxx
    KSRunModifier.cxx
    KSTerminator.cxx
    KSWriter.cxx
)
set( OPERATORS_SOURCE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)
foreach( BASENAME ${OPERATORS_SOURCE_BASENAMES} )
    list( APPEND OPERATORS_SOURCE_FILENAMES ${OPERATORS_SOURCE_PATH}/${BASENAME} )
endforeach( BASENAME )

# library
add_library( KassiopeiaOperators SHARED
    ${OPERATORS_SOURCE_FILENAMES} ${OPERATORS_HEADER_FILENAMES} )
target_include_directories(KassiopeiaOperators
    PUBLIC $<BUILD_INTERFACE:${OPERATORS_HEADER_PATH}> $<INSTALL_INTERFACE:include> )
target_link_libraries( KassiopeiaOperators
    PUBLIC
        KGeoBagMath
        KassiopeiaObjects
)

# install
kasper_install_headers( ${OPERATORS_HEADER_FILENAMES} )
kasper_install_libraries( KassiopeiaOperators )
