'''
Created on Dec 8, 2012

@author: sbobovyc
'''
from wx.lib.pubsub import pub

# messages
OC_VIEW_CHANGE = "VIEW_CHANGE"
OC_SET_VIEW = "SET_VIEW"
OC_SET_VIEW_ABOUT = "SET_VIEW_ABOUT"
(OC_ZOOM_1, OC_ZOOM_2, OC_ZOOM_3) = range(3)

class DisplayManager(object):
        '''
        This object is responsible for keeping track of where on the map the user
        is looking.
        '''
        def __init__(self, display_width, display_height, map_width, map_height, x=0, y=0, zoom=OC_ZOOM_2):
            '''
            Constructor
            '''            
            self.display_width = display_width
            self.display_height = display_height
            self.map_width = map_width
            self.map_height = map_height
            self.map_x = x
            self.map_y = y
            self.zoom_level = zoom
            
            #TODO subscribe to messages that have to do with display
            pub.subscribe(self.set_view, OC_SET_VIEW)
            pub.subscribe(self.set_view, OC_SET_VIEW_ABOUT) 
            pub.subscribe(self.calc_display_bounds, OC_VIEW_CHANGE)
            
        
        def set_view(self, x, y):
            self.map_x = x
            self.map_y = y

        def set_view_about(self, x, y):
            self.set_view(0, 0)
            x_displacement = x - (self.display_width / 2)
            y_displacement = y - (self.display_height / 2)
            self.calc_display_bounds(x_displacement, y_displacement)
            
        def calc_display_bounds(self, x_displacement, y_displacement):
            
            new_x = self.map_x + x_displacement
            new_y = self.map_y + y_displacement
            
            if new_x >= 0 and new_x+self.display_width < self.map_width:
                self.map_x = new_x
            elif new_x < 0:
                self.map_x = 0
            else:
                self.map_x = self.map_width - self.display_width
                
            if new_y >= 0 and new_y+self.display_height < self.map_height:
                self.map_y = new_y     
            elif new_y < 0:
                self.map_y = 0
            else:
                self.map_y = self.map_height - self.display_height                                       
        
        def get_bounds(self):
            return (self.map_x, self.map_y, self.map_x+self.display_width, self.map_y+self.display_height)
        
if __name__ == "__main__":
    DM = DisplayManager(800, 600, 1024, 1024)
    DM.calc_display_bounds(0,0)
    print DM.get_bounds()
    DM.calc_display_bounds(50,0)
    print DM.get_bounds()
    DM.calc_display_bounds(-10,0)
    print DM.get_bounds()
    DM.calc_display_bounds(-100,0)
    print DM.get_bounds()
    DM.calc_display_bounds(10000,0)
    print DM.get_bounds()
    DM.map_x = 0
    DM.map_y = 0
    DM.calc_display_bounds(0,100)
    print DM.get_bounds()
    
    print "test pubsub"
    pub.sendMessage(OC_SET_VIEW, x=0, y=0)
    pub.sendMessage(OC_VIEW_CHANGE, x_displacement=10, y_displacement=10)
    print DM.get_bounds()
    
    print "test set_view_about"
    DM.set_view_about(500, 500)
    print DM.get_bounds()
    
    print "test set_view_about"
    pub.sendMessage(OC_SET_VIEW_ABOUT, x=400, y=350)
    print DM.get_bounds()    