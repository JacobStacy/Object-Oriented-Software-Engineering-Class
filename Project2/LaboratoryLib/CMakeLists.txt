project(LaboratoryLib)

set(SOURCE_FILES
        pch.h
        Laboratory.h Laboratory.cpp LaboratoryFactory.cpp LaboratoryFactory.h LaboratoryStandin.cpp LaboratoryStandin.h
        Polygon.cpp Polygon.h
        LaboratoryDialog.cpp LaboratoryDialog.h include/laboratory-api.h GraphicsHelper.cpp GraphicsHelper.h Sparky.cpp Sparky.h FakeLaboratory.cpp FakeLaboratory.h LaboratoryFactoryOne.cpp LaboratoryFactoryOne.h ActualLaboratory.cpp ActualLaboratory.h Component.cpp Component.h Shape.cpp Shape.h EquipmentRack.cpp EquipmentRack.h ZeroPointModule.cpp ZeroPointModule.h LaboratoryFactoryTwo.cpp LaboratoryFactoryTwo.h)

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)