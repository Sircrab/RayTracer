#include "SceneParams.h"
#include "RenderParams.h"
#include "Renderer.h"
#include "Parser.h"
#include "AABB.h"

int main(int argc, char* argv[]) {
  auto renderParams = Parser::parse_params(argc, argv);
  auto sceneMaterials = Parser::parse_materials(renderParams);
  auto sceneParams = Parser::parse_scene(renderParams, sceneMaterials);
  Renderer renderer(std::const_pointer_cast<const SceneParams>(sceneParams),
                    std::const_pointer_cast<const SceneMaterials>(sceneMaterials),
                    std::const_pointer_cast<const RenderParams>(renderParams));

  renderer.do_render();
  return 0;
}

