'''
Created on Dec 8, 2012

@author: sbobovyc
'''
import pygame
from wx.lib.pubsub import pub

# constants
OC_SCREEN_WIDTH = 800
OC_SCREEN_HEIGHT = 600
OC_FULLSCREEN_MODE = pygame.HWSURFACE | pygame.DOUBLEBUF | pygame.FULLSCREEN
OC_WINDOWED_MODE = pygame.HWSURFACE | pygame.DOUBLEBUF 
OC_DEFAULT_MODE = OC_WINDOWED_MODE

# messages
OC_WINDOWED = "WINDOWED"
OC_FULLSCREEN = "FULLSCREEN"

class Renderer(object):
    '''
    classdocs
    '''

    def __init__(self, debug=True):
        '''
        Constructor
        '''
        self.debug = debug
        # get some diagnostic info
        if self.debug:        
            print pygame.display.list_modes()
        
        
        self.display_surface = None
        self.terrain_surface = None
        
        if pygame.display.mode_ok((OC_SCREEN_WIDTH, OC_SCREEN_HEIGHT), OC_DEFAULT_MODE):            
            self.display_surface = pygame.display.set_mode((OC_SCREEN_WIDTH, OC_SCREEN_HEIGHT), OC_DEFAULT_MODE)
            if OC_DEFAULT_MODE != OC_FULLSCREEN_MODE: 
                self._fullscreen = False
        else:
            raise "Could not set requested display mode"
        self.terrain_surface = pygame.Surface(self.display_surface.get_size())
        self.terrain_surface.fill((255,0,0))

        if self.debug:
            print "Display bit depth:", self.display_surface.get_bitsize()
        
        # subscribe            
        pub.subscribe(self.fullscreen, OC_FULLSCREEN)
        pub.subscribe(self.windowed, OC_WINDOWED)
    
    def fullscreen(self):
        pygame.display.set_mode((OC_SCREEN_WIDTH, OC_SCREEN_HEIGHT), OC_FULLSCREEN_MODE)
        
    def windowed(self):
        pygame.display.set_mode((OC_SCREEN_WIDTH, OC_SCREEN_HEIGHT), OC_WINDOWED_MODE)    
        
    def draw(self, clock): 
        # blit everything to the display surface
        self.display_surface.blit(self.terrain_surface, (0,0))
        
        if self.debug:
            font = pygame.font.SysFont("None", 20)
            self.display_surface.blit(font.render("FPS: %f" % (clock.get_fps()), 0, (255, 255, 255)), (0,0))
        pygame.display.flip()
        
    def screenShot(self):
        self.saveSurface(pygame.surfarray.array3d(self.display_surface), "screen.png")
        
    def saveSurface(self, pixels, filename):
        try:
            surf = pygame.surfarray.make_surface(pixels)
        except IndexError:
            (width, height, colours) = pixels.shape
            surf = pygame.display.set_mode((width, height))
            pygame.surfarray.blit_array(surf, pixels)
        
        pygame.image.save(surf, filename)