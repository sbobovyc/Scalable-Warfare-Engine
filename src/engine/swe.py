import time
import pygame
from pygame.locals import *

from fileManager import FM
from log import Log

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
LEVEL_WIDTH = 1620
LEVEL_HEIGHT = 810

camera = pygame.rect.Rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT)

def move_camera(x, y):
    camera.x += x
    camera.y += y

    if camera.x < 0:
        camera.x = 0
    if camera.y < 0:
        camera.y = 0
    if camera.x+camera.width > LEVEL_WIDTH:
	camera.x = LEVEL_WIDTH-camera.width
    if camera.y+camera.height > LEVEL_HEIGHT:
	camera.y = LEVEL_HEIGHT-camera.height
    print camera.x, camera.y

class CApp:
    def __init__(self):
        self._running = True
        self._surf_display = None
        self._surf_image = None
	self.fps = pygame.time.Clock()
	
    def on_init(self):
        gameFM = FM("../../mods")
        gameLog = Log()
        pygame.init()
        self._display_surf = pygame.display.set_mode((SCREEN_WIDTH,SCREEN_HEIGHT), pygame.HWSURFACE | pygame.DOUBLEBUF)
        self._running = True
        t = time.time()
        self._surf_image = pygame.image.load("../../mods/main_game/maps/world_one_map.tif").convert()
        #self._surf_image = pygame.image.load(gameFM.retrieveFilePath("/maps/world_one_map.tif")).convert()
        gameLog.logger.info("Loading took %0.6f seconds" % (time.time() - t))
	print self._surf_image.get_size()
 
    def on_event(self, event):
	scroll_right = False

        if event.type == QUIT:
            self._running = False
	if event.type ==  MOUSEMOTION:
	    if event.buttons == (0,1,0):
	       move_camera(event.rel[0], event.rel[1])
	print event

    def on_loop(self):
	if pygame.key.get_pressed()[K_RIGHT]:
	    move_camera(10, 0)
	if pygame.key.get_pressed()[K_LEFT]:
	    move_camera(-10, 0)
	if pygame.key.get_pressed()[K_UP]:
	    move_camera(0, -10)
	if pygame.key.get_pressed()[K_DOWN]:
	    move_camera(0, 10)
 	if pygame.key.get_pressed()[K_ESCAPE]:
	    self._running = False       
    def on_render(self):
        self._display_surf.blit(self._surf_image.subsurface(camera), (0,0))
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
