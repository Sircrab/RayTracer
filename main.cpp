#include "SceneParams.h"
#include "RenderParams.h"
#include "Renderer.h"
#include "Parser.h"


int main(int argc, char* argv[]) {
  RenderParams renderParams = Parser::parse_params(argc, argv);
  SceneMaterials sceneMaterials = Parser::parse_materials(renderParams);
  SceneParams sceneParams = Parser::parse_scene(renderParams, sceneMaterials);
  Renderer::do_render(sceneParams, renderParams,sceneMaterials);
  return 0;
}

