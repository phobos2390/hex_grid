/// @file phobos2390/hex_grid_lib/hex_grid.h

#ifndef HEX_GRID_LIB_HEX_GRID_H
#define HEX_GRID_LIB_HEX_GRID_H

#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <glm/glm.hpp>

namespace hex_grid_lib
{
    
class hex_grid
{
public:
    /// Creates class value
    hex_grid(glm::vec2 x, glm::vec2 y);

    /// Removes class value
    virtual ~hex_grid();
    
    void render_single_hex(glm::vec2 center, SDL_Renderer* p_renderer);

    void render_single_solid_hex(glm::vec2 center, SDL_Renderer* p_renderer);
    
    glm::vec2 row_column_to_hex_center(int32_t row, int32_t column);
    
    /// Finds the row, column hex grid value from arbitrary 2d point
    /// @param center origin of hex grid
    /// @param point point to find index of
    /// @return vector representing (row,column) for the hexes found
    glm::ivec2 point_transform(glm::vec2 center, glm::vec2 point);
private:
    struct Impl;
    Impl* m_p_impl;
};

}

#endif /* HEX_GRID_HEX_GRID_H */
