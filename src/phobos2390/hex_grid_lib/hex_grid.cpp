/// @file phobos2390/hex_grid_lib/hex_grid.cpp

#include <phobos2390/hex_grid_lib/hex_grid.h>
#include <glm/gtc/matrix_transform.hpp>
//#include <SDL2/SDL2_gfxPrimitives.h>

namespace hex_grid_lib
{

struct hex_grid::Impl
{
public:
    glm::vec2 m_x;
    glm::vec2 m_y;
    glm::vec2 m_z;
    
    glm::vec2 m_a;
    glm::vec2 m_b;

    Impl(glm::vec2 x, glm::vec2 y)
    : m_x(x)
    , m_y(y)
    , m_z(x - y)
    , m_a(x + x - y)
    , m_b(y + y - x)
    {
    }
    
    virtual ~Impl(){}
    
    void render_line(SDL_Renderer* p_renderer, glm::vec2 start, glm::vec2 end)
    {
        SDL_RenderDrawLine(p_renderer, start.x, start.y, end.x, end.y);
        SDL_RenderDrawLine(p_renderer, end.x, end.y, start.x, start.y);
    }
};

hex_grid::hex_grid(glm::vec2 x, glm::vec2 y)
    :m_p_impl(new Impl(x, y))
{
}

hex_grid::~hex_grid()
{
    delete m_p_impl;
    m_p_impl = 0;
}

void hex_grid::render_single_hex(glm::vec2 center, SDL_Renderer* p_renderer)
{
    glm::vec2 path [] = { 
        m_p_impl->m_x,
        m_p_impl->m_y,
        -(m_p_impl->m_z),
        -(m_p_impl->m_x),
        -(m_p_impl->m_y),
        m_p_impl->m_z,
    };
    
    size_t path_size = sizeof(path)/sizeof(glm::vec2);
    
    glm::vec2 current = center - m_p_impl->m_y;
    
    for(uint32_t i = 0; i < path_size; i++)
    {
        uint32_t n = i;//(i + 1) % path_size;
        glm::vec2 next = current + path[n];
        m_p_impl->render_line(p_renderer, current, next);
        current = next;
    }
}

void hex_grid::render_single_solid_hex(glm::vec2 center, SDL_Renderer* p_renderer)
{
    glm::vec2 path [] = { 
        m_p_impl->m_x,
        m_p_impl->m_y,
        -(m_p_impl->m_z),
        -(m_p_impl->m_x),
        -(m_p_impl->m_y),
        m_p_impl->m_z,
    };
    
    size_t path_size = sizeof(path)/sizeof(glm::vec2);
    
    glm::vec2 current = center - m_p_impl->m_y;
    
    for(uint32_t i = 0; i < path_size; i++)
    {
        uint32_t n = i;//(i + 1) % path_size;
        glm::vec2 next = current + path[n];
        m_p_impl->render_line(p_renderer, center, center + path[n]);
        m_p_impl->render_line(p_renderer, current, next);
        current = next;
    }
}

glm::vec2 hex_grid::row_column_to_hex_center(int32_t row, int32_t column)
{
    return (m_p_impl->m_a * static_cast<float>(row)) + (m_p_impl->m_b * static_cast<float>(column));
}

glm::ivec2 hex_grid::point_transform(glm::vec2 center, glm::vec2 point)
{
    // normals of b and a to properly scale projection
    glm::vec2 b_n(-m_p_impl->m_b.y, m_p_impl->m_b.x);
    glm::vec2 a_n(-m_p_impl->m_a.y, m_p_impl->m_a.x);
    
    glm::vec2 p = point - center;
    
    // arbitrary normal projection
    float a_p = glm::dot(p,b_n) / glm::dot(m_p_impl->m_a,b_n);
    float b_p = glm::dot(p,a_n) / glm::dot(m_p_impl->m_b,a_n);
    
    int32_t a_i = glm::round(a_p);
    int32_t b_i = glm::round(b_p);
    
    glm::ivec2 rc_pos(a_i, b_i);
    
    return rc_pos;
}

}
