'''
Created on Dec 6, 2012

@author: sbobovyc
'''
import pygame 
import numpy
from wx.lib.pubsub import pub
print "pubsub", pub.VERSION_STR

import OC_Renderer

# messages
OC_RIGHT_CLICK = "RIGHT_CLICK"

def saveSurface(pixels, filename):
    try:
        surf = pygame.surfarray.make_surface(pixels)
    except IndexError:
        (width, height, colours) = pixels.shape
        surf = pygame.display.set_mode((width, height))
        pygame.surfarray.blit_array(surf, pixels)
    
    pygame.image.save(surf, filename)
    
class Dot(object):
    def __init__(self, surface):
        self.surface = surface
        pub.subscribe(self.draw, OC_RIGHT_CLICK)
        
    def draw(self, position):
        pygame.draw.circle(self.surface, (255, 0, 0), position, 5)
        print "drawing"
    
    def delete(self):
        #pub.unsubscribe
        pass
        
class Application(object):
    def __init__(self):
        self._running = True
        self._fullscreen = True
        pygame.init()
        self.clock = pygame.time.Clock()
        
        
#        print "Display bit depth:", self._display_surf.get_bitsize()
#        self._background_surf = pygame.Surface(self._display_surf.get_size())
#        self._background_surf = pygame.image.load("world.png")
#        print "Image bit depth:", self._background_surf.get_bitsize()
#        self._background_surf = self._background_surf.convert() # will need this when loading images
       
        # game object        
        self.renderer = OC_Renderer.Renderer()
    
    def on_init(self):
        pygame.init()
    
    def on_event(self, event):        
        if event.type == pygame.QUIT:
            self._running = False
        
        if (event.type == pygame.KEYUP) or (event.type == pygame.KEYDOWN):             
            if (event.key == pygame.K_ESCAPE):
                self._running = False           
            if (event.key == pygame.K_F1) and (event.type == pygame.KEYDOWN):
                if self._fullscreen:
                    pub.sendMessage(OC_Renderer.OC_FULLSCREEN)                    
                else:
                    pub.sendMessage(OC_Renderer.OC_WINDOWED)
                self._fullscreen = not self._fullscreen     
            if (event.key == pygame.K_PRINT) and (event.type == pygame.KEYDOWN):
                self.renderer.screenShot()
                                 
        
        if (event.type == pygame.MOUSEBUTTONDOWN):
            if(event.button == 1):
                print "Left click"
                position = event.pos
                pub.sendMessage(OC_RIGHT_CLICK, position=position)                
        
        #print event
        
    def on_render(self):        
        self.renderer.draw(self.clock)
    
    def on_cleanup(self):
        pygame.quit()
        
    def on_execute(self):
        if self.on_init() == False:
            self._running = False
 
        while( self._running ):
            self.clock.tick(30)    
            pygame.display.set_caption("Open Combat")
            for event in pygame.event.get():
                self.on_event(event)
            self.on_render()        
        self.on_cleanup()
        
if __name__ == '__main__':
    App = Application()
    App.on_execute()
    