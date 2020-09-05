/// @file phobos2390/hex_grid_lib/test/hex_grid_test.cpp

#include <phobos2390/hex_grid_lib/hex_grid.h>
#include <catch2/catch.hpp>
#include <phobos2390/hex_grid_lib/hex_grid.h> // Testing include guard
#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <iostream>

using namespace hex_grid_lib;

TEST_CASE( "hex_grid_test", "stack" )
{
    glm::vec2 x (0,1);
    glm::vec2 y (1,0);
    hex_grid c(x,y);
}

TEST_CASE( "hex_grid_test.render_single_hex", "render_single_hex" )
{
    SDL_Surface* p_surface = SDL_CreateRGBSurface( 0
                                                 , 50
                                                 , 50
                                                 , 0x20
                                                 , 0x00FF0000
                                                 , 0x0000FF00
                                                 , 0x000000FF
                                                 , 0xFF000000);
    if(p_surface == NULL)
    {
        SDL_Log("Surface undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Renderer* p_renderer = SDL_CreateSoftwareRenderer(p_surface);
    if(p_renderer == NULL)
    {
        SDL_Log("Renderer undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(p_renderer, p_surface);
    if(p_texture == NULL)
    {
        SDL_Log("Texture undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    glm::vec2 center(25,25);
    glm::vec2 x (6,8);
    glm::vec2 y (0,10);
    hex_grid c(x,y);
    
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(p_renderer);

    SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    c.render_single_hex(center, p_renderer);
    SDL_RenderDrawPoint(p_renderer, center.x, center.y);
    SDL_RenderPresent(p_renderer);
    IMG_SavePNG(p_surface, "test_files/hexagon.png");
    
    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyTexture(p_texture);
    SDL_FreeSurface(p_surface);
}

TEST_CASE( "hex_grid_test.render_single_hex_symetric", "render_single_hex_symetric" )
{
    SDL_Surface* p_surface = SDL_CreateRGBSurface( 0
                                                 , 50
                                                 , 50
                                                 , 0x20
                                                 , 0x00FF0000
                                                 , 0x0000FF00
                                                 , 0x000000FF
                                                 , 0xFF000000);
    if(p_surface == NULL)
    {
        SDL_Log("Surface undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Renderer* p_renderer = SDL_CreateSoftwareRenderer(p_surface);
    if(p_renderer == NULL)
    {
        SDL_Log("Renderer undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(p_renderer, p_surface);
    if(p_texture == NULL)
    {
        SDL_Log("Texture undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    glm::vec2 center(25,25);
    glm::vec2 x (3,-3);
    glm::vec2 y (3,3);
    hex_grid c(x,y);
    
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(p_renderer);

    SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    c.render_single_hex(center, p_renderer);
    SDL_RenderDrawPoint(p_renderer, center.x, center.y);
    SDL_RenderPresent(p_renderer);
    IMG_SavePNG(p_surface, "test_files/hexagon_symmetric.png");
    
    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyTexture(p_texture);
    SDL_FreeSurface(p_surface);
}

TEST_CASE( "hex_grid_test.render_multiple_hexes", "render_multiple_hexes" )
{
    SDL_Surface* p_surface = SDL_CreateRGBSurface( 0
                                                 , 70
                                                 , 40
                                                 , 0x20
                                                 , 0x00FF0000
                                                 , 0x0000FF00
                                                 , 0x000000FF
                                                 , 0xFF000000);
    if(p_surface == NULL)
    {
        SDL_Log("Surface undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Renderer* p_renderer = SDL_CreateSoftwareRenderer(p_surface);
    if(p_renderer == NULL)
    {
        SDL_Log("Renderer undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(p_renderer, p_surface);
    if(p_texture == NULL)
    {
        SDL_Log("Texture undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    glm::vec2 center(4,4);
    glm::vec2 x (4,-2);
    glm::vec2 y (4,2);
    hex_grid c(x,y);
    
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(p_renderer);

    SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    for(uint32_t i = 0; i < 5; i++)
    {
        for(uint32_t j = 0; j < 5; j++)
        {
            glm::vec2 new_offset = c.row_column_to_hex_center(i,j);
            c.render_single_hex(center + new_offset, p_renderer);
            SDL_RenderDrawPoint( p_renderer, 
                                 center.x + new_offset.x, 
                                 center.y + new_offset.y);
        }
    }
    
    SDL_RenderPresent(p_renderer);

    IMG_SavePNG(p_surface, "test_files/multiple_hex.png");
    
    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyTexture(p_texture);
    SDL_FreeSurface(p_surface);
}

TEST_CASE( "hex_grid_test.render_multiple_hexes_grid", "render_multiple_hexes_grid" )
{
    SDL_Surface* p_surface = SDL_CreateRGBSurface( 0
                                                 , 70
                                                 , 70
                                                 , 0x20
                                                 , 0x00FF0000
                                                 , 0x0000FF00
                                                 , 0x000000FF
                                                 , 0xFF000000);
    if(p_surface == NULL)
    {
        SDL_Log("Surface undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Renderer* p_renderer = SDL_CreateSoftwareRenderer(p_surface);
    if(p_renderer == NULL)
    {
        SDL_Log("Renderer undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(p_renderer, p_surface);
    if(p_texture == NULL)
    {
        SDL_Log("Texture undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    glm::vec2 center(4,4);
    glm::vec2 x (-2,2);
    glm::vec2 y (2,2);
    hex_grid c(x,y);
    
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(p_renderer);

    SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    for(uint32_t i = 0; i < 10; i++)
    {
        for(uint32_t j = 0; j < 10; j++)
        {
            glm::vec2 new_offset = c.row_column_to_hex_center(i,j);
            c.render_single_hex(center + new_offset, p_renderer);
            SDL_RenderDrawPoint( p_renderer, 
                                 center.x + new_offset.x, 
                                 center.y + new_offset.y);
        }
    }
    
    SDL_RenderPresent(p_renderer);

    IMG_SavePNG(p_surface, "test_files/multiple_hex_2.png");
    
    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyTexture(p_texture);
    SDL_FreeSurface(p_surface);
}

TEST_CASE( "hex_grid_test.render_multiple_hexes_grid_thin", "render_multiple_hexes_grid_thin" )
{
    SDL_Surface* p_surface = SDL_CreateRGBSurface( 0
                                                 , 500
                                                 , 500
                                                 , 0x20
                                                 , 0x00FF0000
                                                 , 0x0000FF00
                                                 , 0x000000FF
                                                 , 0xFF000000);
    if(p_surface == NULL)
    {
        SDL_Log("Surface undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Renderer* p_renderer = SDL_CreateSoftwareRenderer(p_surface);
    if(p_renderer == NULL)
    {
        SDL_Log("Renderer undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(p_renderer, p_surface);
    if(p_texture == NULL)
    {
        SDL_Log("Texture undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    glm::vec2 center(200, 10);
    glm::vec2 x (-5,10);
    glm::vec2 y (5,10);
    hex_grid c(x,y);
    
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(p_renderer);

    SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    for(uint32_t i = 0; i < 10; i++)
    {
        for(uint32_t j = 0; j < 10; j++)
        {
            glm::vec2 new_offset = c.row_column_to_hex_center(i,j);
            c.render_single_hex(center + new_offset, p_renderer);
            SDL_RenderDrawPoint( p_renderer, 
                                 center.x + new_offset.x, 
                                 center.y + new_offset.y);
        }
    }
    
    SDL_RenderPresent(p_renderer);

    IMG_SavePNG(p_surface, "test_files/multiple_hex_3.png");
    
    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyTexture(p_texture);
    SDL_FreeSurface(p_surface);
}

void render_line(SDL_Renderer* p_renderer, glm::vec2 a, glm::vec2 b)
{
    SDL_RenderDrawLine(p_renderer, a.x, a.y, b.x, b.y);
    SDL_RenderDrawLine(p_renderer, b.x, b.y, a.x, a.y);
}

TEST_CASE( "hex_grid_test.render_multiple_hexes_grid_arrows", "render_multiple_hexes_grid_thin_arrows" )
{
    SDL_Surface* p_surface = SDL_CreateRGBSurface( 0
                                                 , 500
                                                 , 500
                                                 , 0x20
                                                 , 0x00FF0000
                                                 , 0x0000FF00
                                                 , 0x000000FF
                                                 , 0xFF000000);
    if(p_surface == NULL)
    {
        SDL_Log("Surface undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Renderer* p_renderer = SDL_CreateSoftwareRenderer(p_surface);
    if(p_renderer == NULL)
    {
        SDL_Log("Renderer undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(p_renderer, p_surface);
    if(p_texture == NULL)
    {
        SDL_Log("Texture undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    glm::vec2 center(200, 10);
    glm::vec2 x (-5,10);
    glm::vec2 y (5,10);
    hex_grid c(x,y);
    
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(p_renderer);

    SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    for(uint32_t i = 0; i < 3; i++)
    {
        for(uint32_t j = 0; j < 3; j++)
        {
            glm::vec2 new_offset = c.row_column_to_hex_center(i,j);
            c.render_single_hex(center + new_offset, p_renderer);
            SDL_RenderDrawPoint( p_renderer, 
                                 center.x + new_offset.x, 
                                 center.y + new_offset.y);
        }
    }
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

    render_line( p_renderer, 
                 center + c.row_column_to_hex_center(1,1), 
                 center + c.row_column_to_hex_center(2,1));

    SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    render_line( p_renderer, 
                 center + c.row_column_to_hex_center(1,1), 
                 center + c.row_column_to_hex_center(1,2));
    
    SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    render_line( p_renderer, 
                 center + c.row_column_to_hex_center(1,1), 
                 center + c.row_column_to_hex_center(2,2));

    SDL_RenderPresent(p_renderer);

    IMG_SavePNG(p_surface, "test_files/multiple_hex_4.png");
    
    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyTexture(p_texture);
    SDL_FreeSurface(p_surface);
}

TEST_CASE( "hex_grid_test.render_multiple_arbitrary_hexes_grid_arrows", "render_multiple_hexes_arbitrary_grid_thin_arrows" )
{
    SDL_Surface* p_surface = SDL_CreateRGBSurface( 0
                                                 , 500
                                                 , 500
                                                 , 0x20
                                                 , 0x00FF0000
                                                 , 0x0000FF00
                                                 , 0x000000FF
                                                 , 0xFF000000);
    if(p_surface == NULL)
    {
        SDL_Log("Surface undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Renderer* p_renderer = SDL_CreateSoftwareRenderer(p_surface);
    if(p_renderer == NULL)
    {
        SDL_Log("Renderer undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(p_renderer, p_surface);
    if(p_texture == NULL)
    {
        SDL_Log("Texture undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    glm::vec2 center(20, 20);
    glm::vec2 x (20,10);
    glm::vec2 y (10,20);
    hex_grid c(x,y);
    
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(p_renderer);

    SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    for(uint32_t i = 0; i < 10; i++)
    {
        for(uint32_t j = 0; j < 10; j++)
        {
            glm::vec2 new_offset = c.row_column_to_hex_center(i,j);
            c.render_single_hex(center + new_offset, p_renderer);
            SDL_RenderDrawPoint( p_renderer, 
                                 center.x + new_offset.x, 
                                 center.y + new_offset.y);
        }
    }
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

    render_line( p_renderer, 
                 center + c.row_column_to_hex_center(1,1), 
                 center + c.row_column_to_hex_center(2,1));

    SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    render_line( p_renderer, 
                 center + c.row_column_to_hex_center(1,1), 
                 center + c.row_column_to_hex_center(1,2));
    
    SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    render_line( p_renderer, 
                 center + c.row_column_to_hex_center(1,1), 
                 center + c.row_column_to_hex_center(2,2));

    SDL_RenderPresent(p_renderer);

    IMG_SavePNG(p_surface, "test_files/multiple_hex_5.png");
    
    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyTexture(p_texture);
    SDL_FreeSurface(p_surface);
}

TEST_CASE( "hex_grid_test.point_to_hex", "point_to_hex" )
{
    SDL_Surface* p_surface = SDL_CreateRGBSurface( 0
                                                 , 500
                                                 , 500
                                                 , 0x20
                                                 , 0x00FF0000
                                                 , 0x0000FF00
                                                 , 0x000000FF
                                                 , 0xFF000000);
    if(p_surface == NULL)
    {
        SDL_Log("Surface undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Renderer* p_renderer = SDL_CreateSoftwareRenderer(p_surface);
    if(p_renderer == NULL)
    {
        SDL_Log("Renderer undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    SDL_Texture* p_texture = SDL_CreateTextureFromSurface(p_renderer, p_surface);
    if(p_texture == NULL)
    {
        SDL_Log("Texture undefined %s", SDL_GetError());
        REQUIRE(false);
    }
    glm::vec2 center(20, 20);
    glm::vec2 x (20,10);
    glm::vec2 y (10,20);
    hex_grid c(x,y);
    
    glm::vec2 point(325,480);
    
    glm::vec2 p = point - center;
    glm::vec2 a = c.row_column_to_hex_center(1,0);
    glm::vec2 b = c.row_column_to_hex_center(0,1);
    float a_p = glm::dot(p,a) / glm::dot(a,a);
    float b_p = glm::dot(p,b) / glm::dot(b,b);
    
    int32_t a_i = glm::round(a_p);
    int32_t b_i = glm::round(b_p);
    
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(p_renderer);

    SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    for(uint32_t i = 0; i < 16; i++)
    {
        for(uint32_t j = 0; j < 16; j++)
        {
            glm::vec2 new_offset = c.row_column_to_hex_center(i,j);
            c.render_single_hex(center + new_offset, p_renderer);
            SDL_RenderDrawPoint( p_renderer, 
                                 center.x + new_offset.x, 
                                 center.y + new_offset.y);
        }
    }
    
    SDL_SetRenderDrawColor(p_renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
    
    std::cout << "a: " << b_p << " or " << b_i << " "
              << "b: " << a_p << " or " << a_i << "\n";
    
    c.render_single_hex(center + c.row_column_to_hex_center(a_i,b_i), p_renderer);

    SDL_RenderDrawPoint( p_renderer, 
                         point.x,
                         point.y);

    render_line( p_renderer, center, point);
    
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

    render_line( p_renderer, 
                 center + c.row_column_to_hex_center(1,1), 
                 center + c.row_column_to_hex_center(2,1));

    SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    render_line( p_renderer, 
                 center + c.row_column_to_hex_center(1,1), 
                 center + c.row_column_to_hex_center(1,2));
    
    SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    render_line( p_renderer, 
                 center + c.row_column_to_hex_center(1,1), 
                 center + c.row_column_to_hex_center(2,2));

    SDL_RenderPresent(p_renderer);

    IMG_SavePNG(p_surface, "test_files/multiple_hex_5.png");
    
    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyTexture(p_texture);
    SDL_FreeSurface(p_surface);
}
