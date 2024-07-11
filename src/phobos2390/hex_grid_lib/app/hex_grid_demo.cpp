/* 
 * File:   hex_grid_demo.cpp
 * Author: James
 *
 * Created on August 29, 2020, 9:27 PM
 */

#include <iostream>
#include <phobos2390/hex_grid_lib/hex_grid.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

int main(int argc, char** argv) 
{ 
    SDL_Window * p_window = NULL;
    SDL_Renderer * p_renderer = NULL;
    int32_t error = 0;
    
    if (argc > 2)
    {
        error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
        if(error == 0)
        {
            glm::vec2 c(250, 250);
            
            p_window = SDL_CreateWindow( "Hex Grid"
                                       , SDL_WINDOWPOS_UNDEFINED
                                       , SDL_WINDOWPOS_UNDEFINED
                                       , 500
                                       , 500
                                       , 0);

            p_renderer = SDL_CreateRenderer( p_window
                                           , -1
                                           , SDL_RENDERER_SOFTWARE);
            
            float xa = 0;
            float xb = 0;
            float ya = 0;
            float yb = 0;
            
            sscanf(argv[1],"(%f,%f)", &xa, &xb);
            sscanf(argv[2],"(%f,%f)", &ya, &yb);
            
            std::cout << "(" << xa << ", " << xb << ") "
                      << "(" << ya << ", " << yb << ");\n";
            
            glm::vec2 x(xa, xb);
            glm::vec2 y(ya, yb);
            hex_grid_lib::hex_grid hex_grid(x,y);
            SDL_Event event;
            event.type = 0;
    
            bool continuing = true;
            
            while(continuing)
            {
                while(SDL_PollEvent(&event)) 
                {
                    if (event.type == SDL_QUIT) 
                    {
                        printf("SDL_QUIT\n");
                        continuing = false;
                    }
                }
                
                SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(p_renderer);

                SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                for(int32_t i = -3; i < 4; i++)
                {
                    for(int32_t j = -3; j < 4; j++)
                    {
                        glm::vec2 new_offset = c + hex_grid.row_column_to_hex_center(i,j);
                        hex_grid.render_single_hex(new_offset, p_renderer);
                        SDL_RenderDrawPoint( p_renderer, 
                                             new_offset.x, 
                                             new_offset.y);
                    }
                }
                
                int32_t x = 0;
                int32_t y = 0;
                
                SDL_GetMouseState(&x, &y);
                
                glm::vec2 p(x,y);
//                glm::vec2 c(0,0);
                
                glm::vec2 a = hex_grid.row_column_to_hex_center(1,0);
                glm::vec2 b = hex_grid.row_column_to_hex_center(0,1);
                
                glm::ivec2 rc = hex_grid.point_transform(c, p);
                
//                glm::vec2 a_n(-a.y, a.x);
//                glm::vec2 b_n(-b.y, b.x);
//                
//                float a_p = glm::dot(p,b_n) / glm::dot(a,b_n);
//                float b_p = glm::dot(p,a_n) / glm::dot(b,a_n);
//
//                int32_t a_i = glm::round(a_p);
//                int32_t b_i = glm::round(b_p);
//                
//                glm::vec2 s_a(a_i * a.x, a_i * a.y);
//                glm::vec2 s_b(b_i * b.x, b_i * b.y);
//                
//                glm::vec2 s_a_f(a_p * a.x, a_p * a.y);
//                glm::vec2 s_b_f(b_p * b.x, b_p * b.y);                

//                std::cout << "a: " << b_p << " or " << b_i << " "
//                          << "b: " << a_p << " or " << a_i << "\n";
//                fflush(stdout);
                
                SDL_SetRenderDrawColor(p_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
                
                hex_grid.render_single_hex(c + hex_grid.row_column_to_hex_center(rc.x,rc.y), p_renderer);
//                hex_grid.render_single_hex(hex_grid.row_column_to_hex_center(a_i,b_i), p_renderer);
                
//                SDL_SetRenderDrawColor(p_renderer, 90, 25, 128, SDL_ALPHA_OPAQUE);
//                
//                SDL_RenderDrawLine(p_renderer,0,0,x,y);
//                
//                SDL_SetRenderDrawColor(p_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
//                
//                SDL_RenderDrawLine(p_renderer,0,0,s_a_f.x,s_a_f.y);
//
//                SDL_RenderDrawLine(p_renderer,s_b_f.x,s_b_f.y,s_b_f.x + s_a_f.x,s_b_f.y + s_a_f.y);
//
//                SDL_RenderDrawLine(p_renderer,s_b_f.x,s_b_f.y,x,y);
//
//                SDL_SetRenderDrawColor(p_renderer, 126, 75, 0, SDL_ALPHA_OPAQUE);
//                
//                SDL_RenderDrawLine(p_renderer,0,0,s_b_f.x,s_b_f.y);
//
//                SDL_RenderDrawLine(p_renderer,s_a_f.x,s_a_f.y,s_b_f.x + s_a_f.x,s_b_f.y + s_a_f.y);
//
//                SDL_RenderDrawLine(p_renderer,s_a_f.x,s_a_f.y,x,y);
                
                SDL_RenderPresent(p_renderer);
                
                SDL_Delay(10);
            }

            SDL_DestroyRenderer(p_renderer);
            SDL_DestroyWindow(p_window);
            SDL_Quit();
        
        }
        else
        {
            SDL_Log("Error: %s\n", SDL_GetError());
        }
    }
    else
    {
        std::cout << "Usage: ./demo '(1,2)' '(2,1)'\n";
    }
    return 0;
}

