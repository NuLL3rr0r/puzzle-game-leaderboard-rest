SET ( NOWRUZPUZZLE_PRODUCT_COMPANY_NAME "CompanyName" )
SET ( NOWRUZPUZZLE_PRODUCT_COPYRIGHT_HOLDER "CopyrightHolder" )
SET ( NOWRUZPUZZLE_PRODUCT_COPYRIGHT_YEAR "2014" )
SET ( NOWRUZPUZZLE_PRODUCT_COPYRIGHT "(C) ${NOWRUZPUZZLE_PRODUCT_COPYRIGHT_YEAR} ${NOWRUZPUZZLE_PRODUCT_COPYRIGHT_HOLDER}" )

SET ( NOWRUZPUZZLE_REST_PRODUCT_INTERNAL_NAME "NowruzPuzzleREST" )
SET ( NOWRUZPUZZLE_REST_PRODUCT_NAME "Nowruz Puzzle RESTful Web Service" )
SET ( NOWRUZPUZZLE_REST_PRODUCT_VERSION_MAJOR "0" )
SET ( NOWRUZPUZZLE_REST_PRODUCT_VERSION_MINOR "1" )
SET ( NOWRUZPUZZLE_REST_PRODUCT_VERSION_PATCH "0" )
SET ( NOWRUZPUZZLE_REST_PRODUCT_DESCRIPTION "This is the RESTful web service for Nowruz Puzzle" )

IF ( EXISTS "${PROJECT_SOURCE_DIR}/.git" )
    EXEC_PROGRAM ( ${GIT_EXECUTABLE}
        ARGS "--git-dir=\"${PROJECT_SOURCE_DIR}/.git\" --work-tree=\"${PROJECT_SOURCE_DIR}\" describe --always"
        OUTPUT_VARIABLE GIT_SHORT_REVISION_HASH )
    SET ( NOWRUZPUZZLE_REST_PRODUCT_VERSION_REVISION ${GIT_SHORT_REVISION_HASH} )
ELSE (  )
    SET ( NOWRUZPUZZLE_REST_PRODUCT_VERSION_REVISION "{non-git}" )
ENDIF (  )

SET ( NOWRUZPUZZLE_REST_PRODUCT_VERSION "${NOWRUZPUZZLE_REST_PRODUCT_VERSION_MAJOR}.${NOWRUZPUZZLE_REST_PRODUCT_VERSION_MINOR}.${NOWRUZPUZZLE_REST_PRODUCT_VERSION_PATCH}-${NOWRUZPUZZLE_REST_PRODUCT_VERSION_REVISION}" )


