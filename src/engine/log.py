import logging

class Log():
    def __init__(self):
        self.logger = logging.getLogger('swe')
        self.hdlr = logging.FileHandler('swe.log')
        self.formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
        self.hdlr.setFormatter(self.formatter)
        self.logger.addHandler(self.hdlr) 
        self.logger.setLevel(logging.WARNING)

