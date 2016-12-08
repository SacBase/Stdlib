# This file contains a function that parses a file with the
# description of sac filea belonging either to Core or to
# Ext build of the standard library.

FUNCTION (PARSE_CORE_EXT_CONFIG fname core_sac ext_sac core_xsac ext_xsac)
    SET (score)
    SET (sext)
    SET (xcore)
    SET (xext)


    FILE (READ ${fname} content)
    STRING (REPLACE "\n" ";" lines ${content})

    FOREACH (l ${lines})
        # Get rid of comments
        STRING (REGEX REPLACE "#.*$" "" l "${l}")

        # Get rid of spaces
        STRING (REGEX REPLACE "^[ \t]+" "" l "${l}")
        STRING (REGEX REPLACE "[ \t]+$" "" l "${l}")

        IF ("${l}" STREQUAL "")
            CONTINUE ()
        ENDIF ()

        # Parse the filename and the type
        STRING (REGEX MATCH "([a-zA-Z0-9_\.-/]+)(\.x?sac)[ \t]+(Core|Ext)" l_match ${l})
        IF (NOT l_match)
            MESSAGE (FATAL_ERROR "error while parsing file `${fname}':\n${l}")
        ENDIF ()

        SET (name "${CMAKE_MATCH_1}${CMAKE_MATCH_2}")
        SET (ext "${CMAKE_MATCH_2}")
        SET (type "${CMAKE_MATCH_3}")


        IF ("${type}" STREQUAL "Ext")
            IF ("${ext}" STREQUAL ".sac")
                LIST (APPEND sext "${name}")
            ELSE ()
                LIST (APPEND xext "${name}")
            ENDIF ()
        ELSE ()
            IF ("${ext}" STREQUAL ".sac")
                LIST (APPEND score "${name}")
            ELSE ()
                LIST (APPEND xcore "${name}")
            ENDIF ()
        ENDIF ()

        SET (${core_sac} ${score} PARENT_SCOPE)
        SET (${core_xsac} ${xcore} PARENT_SCOPE)
        SET (${ext_sac} ${sext} PARENT_SCOPE)
        SET (${ext_xsac} ${xext} PARENT_SCOPE)
    ENDFOREACH ()
ENDFUNCTION ()
