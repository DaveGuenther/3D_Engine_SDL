
# Compiler settings 
CC = clang++
CXXFLAGS = -c -std=c++17 -Wall
LDFLAGS = -lstdc++fs -lSDL2main -lSDL2 -lSDL2_image -I /usr/include/SDL2

# Makefile settings 
APPNAME = game
SRC = src
OBJ = obj
BUILD = build

OBJ_LIST = $(OBJ)/game.o $(OBJ)/Globals.o $(OBJ_actions_LIST) $(OBJ_core_LIST) $(OBJ_input_LIST) $(OBJ_materials_LIST) $(OBJ_objects_LIST) $(OBJ_render_LIST) $(OBJ_utility_LIST) $(OBJ)/preprocessor.o
OBJ_actions_LIST = $(OBJ)/Action_Interface.o $(OBJ)/Action_Updater.o 
OBJ_core_LIST= $(OBJ)/Engine_3D.o $(OBJ)/Frame_Rate_Manager.o $(OBJ)/GameState_Observer_Pattern.o 
OBJ_input_LIST= $(OBJ)/Event_Scanner.o $(OBJ)/Input_Parser.o $(OBJ)/KeyBindings.o
OBJ_materials_LIST = $(OBJ)/MaterialMapper.o $(OBJ)/MTL.o $(OBJ)/TextureList.o $(OBJ)/TexturePNG.o
OBJ_objects_LIST = $(OBJ)/OBJ_Chunk.o $(OBJ)/OBJ_Lex_normal.o $(OBJ)/OBJ_Lex_textureCoord.o $(OBJ)/OBJ_Lex_triFace.o $(OBJ)/OBJ_Lex_vertex.o $(OBJ)/OBJ.o
OBJ_render_LIST = $(OBJ)/AspectRatio.o $(OBJ)/Camera.o $(OBJ)/Clipper.o $(OBJ)/Frustum.o $(OBJ)/Rasterizer.o $(OBJ)/Renderer.o $(OBJ)/TrianglePipeline.o
OBJ_utility_LIST = $(OBJ)/Mat4x4.o $(OBJ)/Mesh_Pipeline.o $(OBJ)/Mesh.o $(OBJ)/nonVector_Math_Service.o $(OBJ)/Triangle_Modifier.o $(OBJ)/Triangle.o $(OBJ)/Vec2d.o $(OBJ)/Vec3d.o $(OBJ)/Vector_Math_Service.o

all: $(BUILD)/game

debug: CXXFLAGS += -g -D_GLIBCXX_DEBUG
debug: CCFLAGS += -g -D_GLIBCXX_DEBUG
debug: $(BUILD)/game

$(BUILD)/game: $(OBJ_LIST)
	$(info ***** Linking objects and building target *****)
	clang++ -std=c++17 -Wall -g $(OBJ_LIST) -o $(BUILD)/game $(LDFLAGS)

$(OBJ)/game.o: $(SRC)/game.cpp $(SRC)/core/Engine_3D.cpp $(SRC)/core/Engine_3D.h  
	$(info ***** Building game.o *****)
	clang++ $(CXXFLAGS) $(SRC)/game.cpp -o $(OBJ)/game.o

Globals_SRC = $(SRC)/globals.cpp $(SRC)/globals.h
$(OBJ)/Globals.o: $(Globals_SRC)
	$(info ***** Building Globals.o *****)
	clang++ $(CXXFLAGS) $(SRC)/globals.cpp -o $(OBJ)/Globals.o

Action_Interface_SRC = $(SRC)/actions/Action_Interface.cpp $(SRC)/actions/Action_Interface.h  
$(OBJ)/Action_Interface.o: $(Action_Interface_SRC) 
	$(info ***** Building Action_Interface.o *****)
	clang++ $(CXXFLAGS) $(SRC)/actions/Action_Interface.cpp -o $(OBJ)/Action_Interface.o

Action_Updater_SRC = $(SRC)/actions/Action_Updater.cpp $(SRC)/actions/Action_Updater.h  
$(OBJ)/Action_Updater.o: $(Action_Updater_SRC)
	$(info ***** Building Action_Updater.o *****)
	clang++ $(CXXFLAGS) $(SRC)/actions/Action_Updater.cpp -o $(OBJ)/Action_Updater.o

Engine_3D_SRC = $(SRC)/core/Engine_3D.cpp $(SRC)/core/Engine_3D.h  
$(OBJ)/Engine_3D.o: $(Engine_3D_SRC)
	$(info ***** Building Engine_3D.o *****)
	clang++ $(CXXFLAGS) $(SRC)/core/Engine_3D.cpp -o $(OBJ)/Engine_3D.o

Frame_Rate_Manager_SRC = $(SRC)/core/Frame_Rate_Manager.cpp $(SRC)/core/Frame_Rate_Manager.h  
$(OBJ)/Frame_Rate_Manager.o: $(SRC)/core/Frame_Rate_Manager.h
	$(info ***** Building Frame_Rate_Manager.o *****)
	clang++ $(CXXFLAGS) $(SRC)/core/Frame_Rate_Manager.cpp -o $(OBJ)/Frame_Rate_Manager.o

GameState_Observer_Pattern.o= $(SRC)/core/GameState_Observer_Pattern.cpp $(SRC)/core/GameState_Observer_Pattern.h  
$(OBJ)/GameState_Observer_Pattern.o: $(GameState_Observer_Pattern_SRC)
	$(info ***** Building GameState_Observer_Pattern.o *****)
	clang++ $(CXXFLAGS) $(SRC)/core/GameState_Observer_Pattern.cpp -o $(OBJ)/GameState_Observer_Pattern.o

Event_Scanner_SRC= $(SRC)/input/Event_Scanner.cpp $(SRC)/input/Event_Scanner.h  
$(OBJ)/Event_Scanner.o: $(Event_Scanner_SRC)
	$(info ***** Building Event_Scanner.o *****)
	clang++ $(CXXFLAGS) $(SRC)/input/Event_Scanner.cpp -o $(OBJ)/Event_Scanner.o

Input_Parser_SRC= $(SRC)/input/Input_Parser.cpp $(SRC)/input/Input_Parser.h  
$(OBJ)/Input_Parser.o: $(Input_Parser_SRC)
	$(info ***** Building Input_Parser.o *****)
	clang++ $(CXXFLAGS) $(SRC)/input/Input_Parser.cpp -o $(OBJ)/Input_Parser.o

KeyBindings_SRC= $(SRC)/input/KeyBindings.cpp $(SRC)/input/KeyBindings.h  
$(OBJ)/KeyBindings.o: $(KeyBindings_SRC)
	$(info ***** Building KeyBindings.o *****)
	clang++ $(CXXFLAGS) $(SRC)/input/KeyBindings.cpp -o $(OBJ)/KeyBindings.o

MaterialMapper_SRC= $(SRC)/materials/MaterialMapper.cpp $(SRC)/materials/MaterialMapper.h  
$(OBJ)/MaterialMapper.o: $(MaterialMapper_SRC)
	$(info ***** Building MaterialMapper.o *****)
	clang++ $(CXXFLAGS) $(SRC)/materials/MaterialMapper.cpp -o $(OBJ)/MaterialMapper.o

MTL_SRC= $(SRC)/materials/MTL.cpp $(SRC)/materials/MTL.h  
$(OBJ)/MTL.o: $(MTL_SRC)
	$(info ***** Building MTL.o *****)
	clang++ $(CXXFLAGS) $(SRC)/materials/MTL.cpp -o $(OBJ)/MTL.o

TextureList_SRC= $(SRC)/materials/TextureList.cpp $(SRC)/materials/TextureList.h  
$(OBJ)/TextureList.o: $(TextureList_SRC)
	$(info ***** Building TextureList.o *****)
	clang++ $(CXXFLAGS) $(SRC)/materials/TextureList.cpp -o $(OBJ)/TextureList.o


TexturePNG_SRC= $(SRC)/materials/TexturePNG.cpp $(SRC)/materials/TexturePNG.h  
$(OBJ)/TexturePNG.o: $(TexturePNG_SRC)
	$(info ***** Building TexturePNG.o *****)
	clang++ $(CXXFLAGS) $(SRC)/materials/TexturePNG.cpp -o $(OBJ)/TexturePNG.o

OBJ_Chunk_SRC= $(SRC)/objects/OBJ_Chunk.cpp $(SRC)/objects/OBJ_Chunk.h  
$(OBJ)/OBJ_Chunk.o: $(OBJ_Chunk_SRC)
	$(info ***** Building OBJ_Chunk.o *****)
	clang++ $(CXXFLAGS) $(SRC)/objects/OBJ_Chunk.cpp -o $(OBJ)/OBJ_Chunk.o

OBJ_Lex_normal_SRC= $(SRC)/objects/OBJ_Lex_normal.cpp $(SRC)/objects/OBJ_Lex_normal.h  
$(OBJ)/OBJ_Lex_normal.o: $(OBJ_Lex_normal_SRC)
	$(info ***** Building OBJ_Lex_normal.o *****)
	clang++ $(CXXFLAGS) $(SRC)/objects/OBJ_Lex_normal.cpp -o $(OBJ)/OBJ_Lex_normal.o

OBJ_Lex_textureCoord_SRC= $(SRC)/objects/OBJ_Lex_textureCoord.cpp $(SRC)/objects/OBJ_Lex_textureCoord.h  
$(OBJ)/OBJ_Lex_textureCoord.o: $(OBJ_Lex_textureCoord_SRC)
	$(info ***** Building OBJ_Lex_textureCoord.o *****)
	clang++ $(CXXFLAGS) $(SRC)/objects/OBJ_Lex_textureCoord.cpp -o $(OBJ)/OBJ_Lex_textureCoord.o

OBJ_Lex_triFace_SRC= $(SRC)/objects/OBJ_Lex_triFace.cpp $(SRC)/objects/OBJ_Lex_triFace.h  
$(OBJ)/OBJ_Lex_triFace.o: $(OBJ_Lex_triFace_SRC)
	$(info ***** Building OBJ_Lex_triFace.o *****)
	clang++ $(CXXFLAGS) $(SRC)/objects/OBJ_Lex_triFace.cpp -o $(OBJ)/OBJ_Lex_triFace.o


OBJ_Lex_vertex_SRC= $(SRC)/objects/OBJ_Lex_vertex.cpp $(SRC)/objects/OBJ_Lex_vertex.h  
$(OBJ)/OBJ_Lex_vertex.o: $(OBJ_Lex_vertex_SRC)
	$(info ***** Building OBJ_Lex_vertex.o *****)
	clang++ $(CXXFLAGS) $(SRC)/objects/OBJ_Lex_vertex.cpp -o $(OBJ)/OBJ_Lex_vertex.o


OBJ_SRC= $(SRC)/objects/OBJ.cpp $(SRC)/objects/OBJ.h  
$(OBJ)/OBJ.o: $(OBJ_SRC)
	$(info ***** Building OBJ.o *****)
	clang++ $(CXXFLAGS) $(SRC)/objects/OBJ.cpp -o $(OBJ)/OBJ.o

AspectRatio_SRC=$(SRC)/render/AspectRatio.h $(SRC)/render/AspectRatio.cpp  
$(OBJ)/AspectRatio.o: $(AspectRatio_SRC)
	$(info ***** Building AspectRatio.o *****)
	clang++ $(CXXFLAGS) $(SRC)/render/AspectRatio.cpp -o $(OBJ)/AspectRatio.o

Camera_SRC= $(SRC)/render/Camera.cpp $(SRC)/render/Camera.h  
$(OBJ)/Camera.o: $(Camera_SRC)
	$(info ***** Building Camera.o *****)
	clang++ $(CXXFLAGS) $(SRC)/render/Camera.cpp -o $(OBJ)/Camera.o

Clipper_SRC= $(SRC)/render/Clipper.cpp $(SRC)/render/Clipper.h  
$(OBJ)/Clipper.o: $(Clipper_SRC)
	$(info ***** Building Clipper.o *****)
	clang++ $(CXXFLAGS) $(SRC)/render/Clipper.cpp -o $(OBJ)/Clipper.o

Frustum_SRC= $(SRC)/render/Frustum.cpp $(SRC)/render/Frustum.h  
$(OBJ)/Frustum.o: $(Frustum_SRC)
	$(info ***** Building Frustum.o *****)
	clang++ $(CXXFLAGS) $(SRC)/render/Frustum.cpp -o $(OBJ)/Frustum.o

Rasterizer_SRC= $(SRC)/render/Rasterizer.cpp $(SRC)/render/Rasterizer.h  
$(OBJ)/Rasterizer.o: $(Rasterizer_SRC)
	$(info ***** Building Rasterizer.o *****)
	clang++ $(CXXFLAGS) $(SRC)/render/Rasterizer.cpp -o $(OBJ)/Rasterizer.o

Renderer_SRC= $(SRC)/render/Renderer.cpp $(SRC)/render/Renderer.h  
$(OBJ)/Renderer.o: $(Renderer_SRC)
	$(info ***** Building Renderer.o *****)
	clang++ $(CXXFLAGS) $(SRC)/render/Renderer.cpp -o $(OBJ)/Renderer.o

TrianglePipeline_SRC= $(SRC)/render/TrianglePipeline.cpp $(SRC)/render/TrianglePipeline.h  
$(OBJ)/TrianglePipeline.o: $(TrianglePipeline_SRC)
	$(info ***** Building TrianglePipeline.o *****)
	clang++ $(CXXFLAGS) $(SRC)/render/TrianglePipeline.cpp -o $(OBJ)/TrianglePipeline.o


Mat4x4_SRC= $(SRC)/utility/Mat4x4.cpp $(SRC)/utility/Mat4x4.h  
$(OBJ)/Mat4x4.o: $(Mat4x4_SRC)
	$(info ***** Building Mat4x4.o *****)
	clang++ $(CXXFLAGS) $(SRC)/utility/Mat4x4.cpp -o $(OBJ)/Mat4x4.o


Mesh_Pipeline_SRC= $(SRC)/utility/Mesh_Pipeline.cpp $(SRC)/utility/Mesh_Pipeline.h  
$(OBJ)/Mesh_Pipeline.o: $(Mesh_Pipeline_SRC)
	$(info ***** Building Mesh_Pipeline.o *****)
	clang++ $(CXXFLAGS) $(SRC)/utility/Mesh_Pipeline.cpp -o $(OBJ)/Mesh_Pipeline.o


Mesh_SRC= $(SRC)/utility/Mesh.cpp $(SRC)/utility/Mesh.h  
$(OBJ)/Mesh.o: $(Mesh_SRC)
	$(info ***** Building Mesh.o *****)
	clang++ $(CXXFLAGS) $(SRC)/utility/Mesh.cpp -o $(OBJ)/Mesh.o

nonVector_Math_Service_SRC= $(SRC)/utility/nonVector_Math_Service.cpp $(SRC)/utility/nonVector_Math_Service.h  
$(OBJ)/nonVector_Math_Service.o: $(nonVector_Math_Service_SRC)
	$(info ***** Building nonVector_Math_Service.o *****)
	clang++ $(CXXFLAGS) $(SRC)/utility/nonVector_Math_Service.cpp -o $(OBJ)/nonVector_Math_Service.o

Triangle_Modifier_SRC= $(SRC)/utility/Triangle_Modifier.cpp $(SRC)/utility/Triangle_Modifier.h  
$(OBJ)/Triangle_Modifier.o: $(Triangle_Modifier_SRC)
	$(info ***** Building Triangle_Modifier.o *****)
	clang++ $(CXXFLAGS) $(SRC)/utility/Triangle_Modifier.cpp -o $(OBJ)/Triangle_Modifier.o

Triangle_SRC= $(SRC)/utility/Triangle.cpp $(SRC)/utility/Triangle.h  
$(OBJ)/Triangle.o: $(Triangle_SRC)
	$(info ***** Building Triangle.o *****)
	clang++ $(CXXFLAGS) $(SRC)/utility/Triangle.cpp -o $(OBJ)/Triangle.o

Vec2d_SRC=$(SRC)/utility/Vec2d.h $(SRC)/utility/Vec2d.cpp  
$(OBJ)/Vec2d.o: $(Vec2d_SRC)
	$(info ***** Building Vec2d.o *****)
	clang++ $(CXXFLAGS) $(SRC)/utility/Vec2d.cpp -o $(OBJ)/Vec2d.o

Vec3d_SRC=$(SRC)/utility/Vec3d.h $(SRC)/utility/Vec3d.cpp  
$(OBJ)/Vec3d.o: $(Vec3d_SRC)
	$(info ***** Building Vec3d.o *****)
	clang++ $(CXXFLAGS) $(SRC)/utility/Vec3d.cpp -o $(OBJ)/Vec3d.o

Vector_Math_Service_SRC= $(SRC)/utility/Vector_Math_Service.cpp $(SRC)/utility/Vector_Math_Service.h  
$(OBJ)/Vector_Math_Service.o: $(Vector_Math_Service_SRC)
	$(info ***** Building Vector_Math_Service.o *****)
	clang++ $(CXXFLAGS) $(SRC)/utility/Vector_Math_Service.cpp -o $(OBJ)/Vector_Math_Service.o

$(OBJ)/preprocessor.o: $(SRC)/preprocessor.cpp 
	$(info ***** Building Crossplatform Preprocessor (preprocessor.o) *****)
	clang++ $(CXXFLAGS) $(SRC)/preprocessor.cpp -o $(OBJ)/preprocessor.o

.PHONY: clean #so that adding a file called src/clean doesn't mess up the makefile
clean:
	rm -f $(OBJ)/*.o $(BUILD)/main

