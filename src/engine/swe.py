import pygame
from pygame.locals import *
 
class CApp:
    def __init__(self):
        self._running = True
        self._surf_display = None
        self._surf_image = None
	self.fps = pygame.time.Clock()

    def on_init(self):
        pygame.init()
        self._display_surf = pygame.display.set_mode((640,400), pygame.HWSURFACE | pygame.DOUBLEBUF)
        self._running = True
        self._surf_image = pygame.image.load("../utils/mapmaker/world_one_map.bmp").convert()
 
    def on_event(self, event):
        if event.type == QUIT:
            self._running = False
	if event.type == KEYDOWN:
	    if event.key == K_ESCAPE:
	        self._running = False
    def on_loop(self):
        pass
    def on_render(self):
        self._display_surf.blit(self._surf_image, (0,0))
	font = pygame.font.SysFont("None", 20)
	self._display_surf.blit(font.render("FPS: %f" % (self.fps.get_fps()), 0, (255, 0, 0)), (0,0))
	pygame.display.flip()
    def on_cleanup(self):
        pygame.quit()
 
    def on_execute(self):
        if self.on_init() == False:
            self._running = False
 
        while( self._running ):
	    self.fps.tick(30)	
	    pygame.display.set_caption("Scalable Warfare Engine")
            for event in pygame.event.get():
                self.on_event(event)
            self.on_loop()
            self.on_render()
        self.on_cleanup()
 
if __name__ == "__main__" :
    theApp = CApp()
    theApp.on_execute()
