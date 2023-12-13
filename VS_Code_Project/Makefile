
# Compiler settings 
CC = clang++

ifeq ($(OS), Windows_NT) # we should only use make release for windows builds.  Development (make debug and profiling only happens on Linux)
	CXXFLAGS = -c -std=c++17 -Wall -I /c/SDL2/SDL2-2.26.1/x86_64-w64-mingw32/include -I /c/SDL2/SDL2-2.26.1/x86_64-w64-mingw32/include
	LDFLAGS =  -L /c/SDL2/SDL2-2.26.1/x86_64-w64-mingw32/lib -L /c/SDL2/SDL2-2.26.1/x86_64-w64-mingw32/lib -lSDL2main -lSDL2 -lSDL2_image
else
	CXXFLAGS = -c -std=c++17 -Wall
	LDFLAGS = -lstdc++fs -lSDL2main -lSDL2 -lSDL2_image -I /usr/include/SDL2
endif	

# Makefile settings 
APPNAME = game
SRC = src
OBJ = obj
BUILD = build

OBJ_LIST = $(OBJ)/game.o $(OBJ)/preprocessor.o $(OBJ)/Globals.o $(OBJ_actions_LIST) $(OBJ_core_LIST) $(OBJ_input_LIST) $(OBJ_materials_LIST) $(OBJ_objects_LIST) $(OBJ_render_LIST) $(OBJ_utility_LIST)
OBJ_actions_LIST = $(OBJ)/actions/Action_Interface.o $(OBJ)/actions/Action_Updater.o 
OBJ_core_LIST= $(OBJ)/core/Engine_3D.o $(OBJ)/core/Frame_Rate_Manager.o $(OBJ)/core/GameState_Observer_Pattern.o 
OBJ_input_LIST= $(OBJ)/input/Event_Scanner.o $(OBJ)/input/Input_Parser.o $(OBJ)/input/KeyBindings.o
OBJ_materials_LIST = $(OBJ)/materials/MaterialMapper.o $(OBJ)/materials/MTL.o $(OBJ)/materials/TextureList.o $(OBJ)/materials/TexturePNG.o
OBJ_objects_LIST = $(OBJ)/objects/OBJ_Chunk.o $(OBJ)/objects/OBJ_Lex_normal.o $(OBJ)/objects/OBJ_Lex_textureCoord.o $(OBJ)/objects/OBJ_Lex_triFace.o $(OBJ)/objects/OBJ_Lex_vertex.o $(OBJ)/objects/OBJ.o
OBJ_render_LIST = $(OBJ)/render/SDLTextureBlit.o $(OBJ)/render/AspectRatio.o $(OBJ)/render/Camera.o $(OBJ)/render/Clipper.o $(OBJ)/render/Frustum.o $(OBJ)/render/Rasterizer.o $(OBJ)/render/Renderer.o $(OBJ)/render/TrianglePipeline.o 
OBJ_utility_LIST = $(OBJ)/utility/Mat4x4.o $(OBJ)/utility/Mesh_Pipeline.o $(OBJ)/utility/Mesh.o $(OBJ)/utility/nonVector_Math_Service.o $(OBJ)/utility/Triangle_Modifier.o $(OBJ)/utility/Triangle.o $(OBJ)/utility/Vec2d.o $(OBJ)/utility/Vec3d.o $(OBJ)/utility/Vector_Math_Service.o

all: $(BUILD)/game

.PHONY: release
release: CXXFLAGS += -O0 -fno-inline-functions
release: clean
release: $(BUILD)/game

.PHONY: prof
prof: LDFLAGS += -lprofiler -ltcmalloc
prof: remove-executable
prof: debug
prof:
	bash profile.sh

.PHONY: debug
debug: clean
debug: LDFLAGS += -lprofiler -ltcmalloc
debug: CXXFLAGS += -O0 -fno-inline-functions -glldb -D_GLIBCXX_DEBUG
debug: $(BUILD)/game

.PHONY: clean 
clean: remove-executable
	rm -f $(OBJ)/*.o 
	rm -f $(OBJ)/actions/*.o
	rm -f $(OBJ)/core/*.o
	rm -f $(OBJ)/input/*.o
	rm -f $(OBJ)/materials/*.o
	rm -f $(OBJ)/objects/*.o
	rm -f $(OBJ)/render/*.o
	rm -f $(OBJ)/utility/*.o
	rm -f $(BUILD)/game.gif
	rm -f $(BUILD)/*.prof
	rm -f $(BUILD)/*.callgrind


.PHONY: remove-executable 
remove-executable:
	rm -f $(BUILD)/game

$(BUILD)/game: $(OBJ_LIST)
	$(info ***** Linking objects and building target *****)
	$(CC) -std=c++17 -Wall -g $(OBJ_LIST) -o $(BUILD)/game $(LDFLAGS)

$(OBJ)/game.o: $(SRC)/game.cpp $(SRC)/core/Engine_3D.cpp $(SRC)/core/Engine_3D.h  
	$(info ***** Building game.o *****)
	echo $(OS)
	$(CC) $(CXXFLAGS) $(SRC)/game.cpp -o $(OBJ)/game.o

Globals_SRC = $(SRC)/globals.cpp $(SRC)/globals.h
$(OBJ)/Globals.o: $(Globals_SRC)
	$(info ***** Building Globals.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/globals.cpp -o $(OBJ)/Globals.o

Action_Interface_SRC = $(SRC)/actions/Action_Interface.cpp $(SRC)/actions/Action_Interface.h  
$(OBJ)/actions/Action_Interface.o: $(Action_Interface_SRC) 
	$(info ***** Building Action_Interface.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/actions/Action_Interface.cpp -o $(OBJ)/actions/Action_Interface.o

Action_Updater_SRC = $(SRC)/actions/Action_Updater.cpp $(SRC)/actions/Action_Updater.h  
$(OBJ)/actions/Action_Updater.o: $(Action_Updater_SRC)
	$(info ***** Building Action_Updater.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/actions/Action_Updater.cpp -o $(OBJ)/actions/Action_Updater.o

Engine_3D_SRC = $(SRC)/core/Engine_3D.cpp $(SRC)/core/Engine_3D.h  
$(OBJ)/core/Engine_3D.o: $(Engine_3D_SRC)
	$(info ***** Building Engine_3D.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/core/Engine_3D.cpp -o $(OBJ)/core/Engine_3D.o

Frame_Rate_Manager_SRC = $(SRC)/core/Frame_Rate_Manager.cpp $(SRC)/core/Frame_Rate_Manager.h  
$(OBJ)/core/Frame_Rate_Manager.o: $(SRC)/core/Frame_Rate_Manager.h
	$(info ***** Building Frame_Rate_Manager.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/core/Frame_Rate_Manager.cpp -o $(OBJ)/core/Frame_Rate_Manager.o

GameState_Observer_Pattern.o= $(SRC)/core/GameState_Observer_Pattern.cpp $(SRC)/core/GameState_Observer_Pattern.h  
$(OBJ)/core/GameState_Observer_Pattern.o: $(GameState_Observer_Pattern_SRC)
	$(info ***** Building GameState_Observer_Pattern.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/core/GameState_Observer_Pattern.cpp -o $(OBJ)/core/GameState_Observer_Pattern.o

Event_Scanner_SRC= $(SRC)/input/Event_Scanner.cpp $(SRC)/input/Event_Scanner.h  
$(OBJ)/input/Event_Scanner.o: $(Event_Scanner_SRC)
	$(info ***** Building Event_Scanner.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/input/Event_Scanner.cpp -o $(OBJ)/input/Event_Scanner.o

Input_Parser_SRC= $(SRC)/input/Input_Parser.cpp $(SRC)/input/Input_Parser.h  
$(OBJ)/input/Input_Parser.o: $(Input_Parser_SRC)
	$(info ***** Building Input_Parser.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/input/Input_Parser.cpp -o $(OBJ)/input/Input_Parser.o

KeyBindings_SRC= $(SRC)/input/KeyBindings.cpp $(SRC)/input/KeyBindings.h  
$(OBJ)/input/KeyBindings.o: $(KeyBindings_SRC)
	$(info ***** Building KeyBindings.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/input/KeyBindings.cpp -o $(OBJ)/input/KeyBindings.o

MaterialMapper_SRC= $(SRC)/materials/MaterialMapper.cpp $(SRC)/materials/MaterialMapper.h  
$(OBJ)/materials/MaterialMapper.o: $(MaterialMapper_SRC)
	$(info ***** Building MaterialMapper.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/materials/MaterialMapper.cpp -o $(OBJ)/materials/MaterialMapper.o

MTL_SRC= $(SRC)/materials/MTL.cpp $(SRC)/materials/MTL.h  
$(OBJ)/materials/MTL.o: $(MTL_SRC)
	$(info ***** Building MTL.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/materials/MTL.cpp -o $(OBJ)/materials/MTL.o

TextureList_SRC= $(SRC)/materials/TextureList.cpp $(SRC)/materials/TextureList.h  
$(OBJ)/materials/TextureList.o: $(TextureList_SRC)
	$(info ***** Building TextureList.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/materials/TextureList.cpp -o $(OBJ)/materials/TextureList.o


TexturePNG_SRC= $(SRC)/materials/TexturePNG.cpp $(SRC)/materials/TexturePNG.h  
$(OBJ)/materials/TexturePNG.o: $(TexturePNG_SRC)
	$(info ***** Building TexturePNG.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/materials/TexturePNG.cpp -o $(OBJ)/materials/TexturePNG.o

OBJ_Chunk_SRC= $(SRC)/objects/OBJ_Chunk.cpp $(SRC)/objects/OBJ_Chunk.h  
$(OBJ)/objects/OBJ_Chunk.o: $(OBJ_Chunk_SRC)
	$(info ***** Building OBJ_Chunk.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/objects/OBJ_Chunk.cpp -o $(OBJ)/objects/OBJ_Chunk.o

OBJ_Lex_normal_SRC= $(SRC)/objects/OBJ_Lex_normal.cpp $(SRC)/objects/OBJ_Lex_normal.h  
$(OBJ)/objects/OBJ_Lex_normal.o: $(OBJ_Lex_normal_SRC)
	$(info ***** Building OBJ_Lex_normal.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/objects/OBJ_Lex_normal.cpp -o $(OBJ)/objects/OBJ_Lex_normal.o

OBJ_Lex_textureCoord_SRC= $(SRC)/objects/OBJ_Lex_textureCoord.cpp $(SRC)/objects/OBJ_Lex_textureCoord.h  
$(OBJ)/objects/OBJ_Lex_textureCoord.o: $(OBJ_Lex_textureCoord_SRC)
	$(info ***** Building OBJ_Lex_textureCoord.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/objects/OBJ_Lex_textureCoord.cpp -o $(OBJ)/objects/OBJ_Lex_textureCoord.o

OBJ_Lex_triFace_SRC= $(SRC)/objects/OBJ_Lex_triFace.cpp $(SRC)/objects/OBJ_Lex_triFace.h  
$(OBJ)/objects/OBJ_Lex_triFace.o: $(OBJ_Lex_triFace_SRC)
	$(info ***** Building OBJ_Lex_triFace.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/objects/OBJ_Lex_triFace.cpp -o $(OBJ)/objects/OBJ_Lex_triFace.o


OBJ_Lex_vertex_SRC= $(SRC)/objects/OBJ_Lex_vertex.cpp $(SRC)/objects/OBJ_Lex_vertex.h  
$(OBJ)/objects/OBJ_Lex_vertex.o: $(OBJ_Lex_vertex_SRC)
	$(info ***** Building OBJ_Lex_vertex.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/objects/OBJ_Lex_vertex.cpp -o $(OBJ)/objects/OBJ_Lex_vertex.o


OBJ_SRC= $(SRC)/objects/OBJ.cpp $(SRC)/objects/OBJ.h  
$(OBJ)/objects/OBJ.o: $(OBJ_SRC)
	$(info ***** Building OBJ.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/objects/OBJ.cpp -o $(OBJ)/objects/OBJ.o

AspectRatio_SRC=$(SRC)/render/AspectRatio.h $(SRC)/render/AspectRatio.cpp  
$(OBJ)/render/AspectRatio.o: $(AspectRatio_SRC)
	$(info ***** Building AspectRatio.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/render/AspectRatio.cpp -o $(OBJ)/render/AspectRatio.o

Camera_SRC= $(SRC)/render/Camera.cpp $(SRC)/render/Camera.h  
$(OBJ)/render/Camera.o: $(Camera_SRC)
	$(info ***** Building Camera.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/render/Camera.cpp -o $(OBJ)/render/Camera.o

Clipper_SRC= $(SRC)/render/Clipper.cpp $(SRC)/render/Clipper.h  
$(OBJ)/render/Clipper.o: $(Clipper_SRC)
	$(info ***** Building Clipper.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/render/Clipper.cpp -o $(OBJ)/render/Clipper.o

Frustum_SRC= $(SRC)/render/Frustum.cpp $(SRC)/render/Frustum.h  
$(OBJ)/render/Frustum.o: $(Frustum_SRC)
	$(info ***** Building Frustum.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/render/Frustum.cpp -o $(OBJ)/render/Frustum.o

Rasterizer_SRC= $(SRC)/render/Rasterizer.cpp $(SRC)/render/Rasterizer.h  
$(OBJ)/render/Rasterizer.o: $(Rasterizer_SRC)
	$(info ***** Building Rasterizer.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/render/Rasterizer.cpp -o $(OBJ)/render/Rasterizer.o

Renderer_SRC= $(SRC)/render/Renderer.cpp $(SRC)/render/Renderer.h  
$(OBJ)/render/Renderer.o: $(Renderer_SRC)
	$(info ***** Building Renderer.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/render/Renderer.cpp -o $(OBJ)/render/Renderer.o

TrianglePipeline_SRC= $(SRC)/render/TrianglePipeline.cpp $(SRC)/render/TrianglePipeline.h  
$(OBJ)/render/TrianglePipeline.o: $(TrianglePipeline_SRC)
	$(info ***** Building TrianglePipeline.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/render/TrianglePipeline.cpp -o $(OBJ)/render/TrianglePipeline.o


Mat4x4_SRC= $(SRC)/utility/Mat4x4.cpp $(SRC)/utility/Mat4x4.h  
$(OBJ)/utility/Mat4x4.o: $(Mat4x4_SRC)
	$(info ***** Building Mat4x4.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/utility/Mat4x4.cpp -o $(OBJ)/utility/Mat4x4.o


Mesh_Pipeline_SRC= $(SRC)/utility/Mesh_Pipeline.cpp $(SRC)/utility/Mesh_Pipeline.h  
$(OBJ)/utility/Mesh_Pipeline.o: $(Mesh_Pipeline_SRC)
	$(info ***** Building Mesh_Pipeline.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/utility/Mesh_Pipeline.cpp -o $(OBJ)/utility/Mesh_Pipeline.o


Mesh_SRC= $(SRC)/utility/Mesh.cpp $(SRC)/utility/Mesh.h  
$(OBJ)/utility/Mesh.o: $(Mesh_SRC)
	$(info ***** Building Mesh.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/utility/Mesh.cpp -o $(OBJ)/utility/Mesh.o

nonVector_Math_Service_SRC= $(SRC)/utility/nonVector_Math_Service.cpp $(SRC)/utility/nonVector_Math_Service.h  
$(OBJ)/utility/nonVector_Math_Service.o: $(nonVector_Math_Service_SRC)
	$(info ***** Building nonVector_Math_Service.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/utility/nonVector_Math_Service.cpp -o $(OBJ)/utility/nonVector_Math_Service.o

Triangle_Modifier_SRC= $(SRC)/utility/Triangle_Modifier.cpp $(SRC)/utility/Triangle_Modifier.h  
$(OBJ)/utility/Triangle_Modifier.o: $(Triangle_Modifier_SRC)
	$(info ***** Building Triangle_Modifier.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/utility/Triangle_Modifier.cpp -o $(OBJ)/utility/Triangle_Modifier.o

Triangle_SRC= $(SRC)/utility/Triangle.cpp $(SRC)/utility/Triangle.h  
$(OBJ)/utility/Triangle.o: $(Triangle_SRC)
	$(info ***** Building Triangle.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/utility/Triangle.cpp -o $(OBJ)/utility/Triangle.o

Vec2d_SRC=$(SRC)/utility/Vec2d.h $(SRC)/utility/Vec2d.cpp  
$(OBJ)/utility/Vec2d.o: $(Vec2d_SRC)
	$(info ***** Building Vec2d.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/utility/Vec2d.cpp -o $(OBJ)/utility/Vec2d.o

Vec3d_SRC=$(SRC)/utility/Vec3d.h $(SRC)/utility/Vec3d.cpp  
$(OBJ)/utility/Vec3d.o: $(Vec3d_SRC)
	$(info ***** Building Vec3d.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/utility/Vec3d.cpp -o $(OBJ)/utility/Vec3d.o

Vector_Math_Service_SRC= $(SRC)/utility/Vector_Math_Service.cpp $(SRC)/utility/Vector_Math_Service.h  
$(OBJ)/utility/Vector_Math_Service.o: $(Vector_Math_Service_SRC)
	$(info ***** Building Vector_Math_Service.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/utility/Vector_Math_Service.cpp -o $(OBJ)/utility/Vector_Math_Service.o

SDLTextureBlit_SRC= $(SRC)/render/SDLTextureBlit.cpp $(SRC)/render/SDLTextureBlit.h  
$(OBJ)/render/SDLTextureBlit.o: $(SDLTextureBlit_SRC)
	$(info ***** Building SDLTextureBlit.o *****)
	$(CC) $(CXXFLAGS) $(SRC)/render/SDLTextureBlit.cpp -o $(OBJ)/render/SDLTextureBlit.o

$(OBJ)/preprocessor.o: $(SRC)/preprocessor.cpp 
	$(info ***** Building Crossplatform Preprocessor (preprocessor.o) *****)
	$(CC) $(CXXFLAGS) $(SRC)/preprocessor.cpp -o $(OBJ)/preprocessor.o

