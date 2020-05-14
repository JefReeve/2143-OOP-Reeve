#!/usr/bin/env python3

# Import and initialize the pygame library
import pygame
import random
import math
import sys,os
import json

# list of colors
colors = ["blue", "light_blue", "yellow", "orange", "green"]

'''Open config.json for main variables of the simulation
'''
if os.path.isfile("config.json"):

    # open config for reading
    f = open("config.json","r")

    # read the file into a "data" variable
    data = f.read()

    # convert json into a python dictionary
    config = json.loads(data)

# Class to represent individual people
class Person(pygame.sprite.Sprite):
    """
    This class represents the ball.
    It derives from the "Sprite" class in Pygame
    """
    def __init__(self, **kwargs):
        """ Constructor. 
        """

        # Call the parent class (Sprite) constructor
        super().__init__()
        self.width = kwargs.get("width", 10)
        self.height = kwargs.get("height", 10)
        self.speed = kwargs.get("speed", 1)
        self.coord = kwargs.get("coord", None)
        self.color = kwargs.get("color", "green")
        self.infection_day = kwargs.get("infection_day", 9999)# day the person becomes infected
        self.death_day = random.randint(config["sim"]["death_lower_limit"],config["sim"]["death_upper_limit"])# amount of days after infection till death
        self.recover_day = random.randint(config["sim"]["recover_lower_limit"],config["sim"]["recover_upper_limit"])# amount of days after infection till recovery
        self.quarantine_day = random.randint(config["sim"]["symptoms_lower_limit"],config["sim"]["symptoms_upper_limit"])# amount of days after infection till put in quarantine
        self.quarantine_check = False # checks if the person is in quarantine
        
        if self.color == "yellow":
          self.state = "susceptible"
        elif self.color == "red":
          self.state = "infected"
        elif self.color == "green":
          self.state = "recoveered"
        else:
          self.state = "other"

        # choose sprite direction
        self.dx = 0
        self.dy = 0
        while self.dx + self.dy == 0:
            self.dx = random.choice([1, -1, 0])
            self.dy = random.choice([1, -1, 0])

        # give our sprite an image and resize it
        self.image = pygame.image.load(config["images"][self.color])
        self.image = pygame.transform.scale(self.image,
                                            (self.width, self.height))

        # set sprite position
        if self.coord == None:
            self.x = int(random.random() * config["game"]["width"])
            self.y = int(random.random() * config["game"]["height"])
        else:
            self.x = self.coord[0]
            self.y = self.coord[1]

        # sprite bounding rectangle
        self.rect = self.image.get_rect(center=(self.x, self.y))

    def __repr__(self):
        ''' Representation or a unambigous printout of your object
        '''
        return self.__str__()

    def __str__(self):
        ''' String printout of your object
        '''
        c = self.color
        s = self.speed
        x = self.x
        y = self.y
        r = self.rect 
        return f"Color: {c}, Speed: {s}, X: {x}, Y: {y}, Rect: {r} "

    def setDxDy(self, dx, dy):
        self.dx = dx
        self.dy = dy

    def getDxDy(self):
        return (self.dx, self.dy)

    def changeDirection(self, sides_contacted):
        if sides_contacted["top"]:
            self.dy = 1
        if sides_contacted["bottom"]:
            self.dy = -1
        if sides_contacted["left"]:
            self.dx = 1
        if sides_contacted["right"]:
            self.dx = -1

    def move(self):

        sides_contacted = self.checkWalls()

        self.changeDirection(sides_contacted)

        if self.dx < 0:
            self.rect.x -= self.speed
        elif self.dx > 0:
            self.rect.x += self.speed

        if self.dy < 0:
            self.rect.y -= self.speed
        elif self.dy > 0:
            self.rect.y += self.speed

    def checkCollide(self, other):
        sides_contacted = {
            "top": False,
            "bottom": False,
            "left": False,
            "right": False
        }

        if self.rect.colliderect(other.rect):

            if self.rect.top < other.rect.top:
                sides_contacted["bottom"] = True
                self.rect.y -= abs(self.rect.y - other.rect.y) // 8
            if self.rect.left < other.rect.left:
                sides_contacted["right"] = True
                self.rect.x -= abs(self.rect.x - other.rect.x) // 8
            if self.rect.right > other.rect.right:
                sides_contacted["left"] = True
                self.rect.x += abs(self.rect.x - other.rect.x) // 8
            if self.rect.bottom > other.rect.bottom:
                sides_contacted["top"] = True
                self.rect.y += abs(self.rect.y - other.rect.y) // 8

                  

            self.changeDirection(sides_contacted)

            return True

        return False

    def checkWalls(self):
        sides = {"top": False, "bottom": False, "left": False, "right": False}

        # different bounds if in quarantine
        if self.rect.top <= 0:
            sides["top"] = True
        if self.quarantine_check == True:
            if self.rect.left <= config["game"]["width"]//1.25:
                sides["left"] = True
        elif self.rect.left <= 0:
            sides["left"] = True
        if self.quarantine_check == True:
            if self.rect.right >= config["game"]["width"]:
                sides["right"] = True
        elif self.rect.right >= config["game"]["width"]//1.25:
            sides["right"] = True
        if self.rect.bottom >= config["game"]["height"]:
            sides["bottom"] = True

        return sides

    # checks for changes in a persons status(death, recoveries, getting put in and out of quarantine)
    def check_status(self):
        if config["game"]["loop_count"] / config["game"]["fps"] == self.infection_day + self.death_day:
            death = random.random()
            if death <= config["sim"]["death_rate"]:
                return 1

        if config["game"]["loop_count"] / config["game"]["fps"] == self.infection_day + self.recover_day:
            return 2

        if config["game"]["loop_count"] / config["game"]["fps"] == self.infection_day + self.quarantine_day:
            self.quarantine = random.random()
            if self.quarantine <= config["sim"]["quarantine_rate"]:
                self.rect.x = random.randint(config["game"]["width"]//1.25, config["game"]["width"])
                self.rect.y = random.randint(0, config["game"]["height"])
                return 3

        if config["game"]["loop_count"] / config["game"]["fps"] == self.infection_day + self.quarantine_day + config["sim"]["quarantine_days"]:
            self.quarantine_check = False
            return 4
        return 0


class Simulation:
    def __init__(self, **kwargs):
        self.population = []
        self.game_width = kwargs.get("width", 500)
        self.game_height = kwargs.get("height", 500)
        self.population_count = kwargs.get("population_count", 60)
        self.num_infected = kwargs.get("num_infected", 10)
        self.sprite_group = pygame.sprite.Group()
        self.screen = kwargs.get("screen", None)
        self.num_quarantined = 0
        self.num_dead = 0

        if self.screen == None:
            print(
                "Error: Simulation needs an instance of a pygame surface / screen!"
            )
            sys.exit()

    def populateSim(self, pos=None):
        for _ in range(self.num_infected):
          self.addInf()

        self.numsus = self.population_count - self.num_infected

        for _ in range(self.numsus):
          self.addSus()

    #adds person of random color(only red, gree, and yellow have any function)
    def addPerson(self, **kwargs):
        x = random.randint(0, self.game_width//1.25) # changed bounds to account for quarantine area
        y = random.randint(0, self.game_height)
        coord = kwargs.get("coord", [x, y])

        p = Person(color=random.choice(colors),
                   width=config["sprite"]["width"],
                   height=config["sprite"]["height"],
                   speed=config["sprite"]["speed"],
                   coord=coord)

        self.population.append(p)
        self.sprite_group.add(p)

    #adds susceptiple person(yellow)
    def addSus(self, **kwargs):
        x = random.randint(0, self.game_width//1.25) # changed bounds to account for quarantine area
        y = random.randint(0, self.game_height)
        coord = kwargs.get("coord", [x, y])

        p = Person(color="yellow",
                   width=config["sprite"]["width"],
                   height=config["sprite"]["height"],
                   speed=config["sprite"]["speed"],
                   infection_day=9999, # high infection day so it wont trigger recoveries or deaths before getting infected
                   coord=coord)

        self.population.append(p)
        self.sprite_group.add(p)

    #adds infected person(red)
    def addInf(self, **kwargs):

        x = random.randint(0, self.game_width//1.25) # changed bounds to account for quarantine area
        y = random.randint(0, self.game_height)
        coord = kwargs.get("coord", [x, y])

        p = Person(color="red",
                   width=config["sprite"]["width"],
                   height=config["sprite"]["height"],
                   speed=config["sprite"]["speed"],
                   infection_day=0,
                   coord=coord)

        self.population.append(p)
        self.sprite_group.add(p)

    def simRun(self):
        dead_list = []
        # loop through each person and call a move method
        for i in range(len(self.population)):
            self.population[i].move()
            for j in range(len(self.population)):
                if self.population[i] != self.population[j]:
                    collided = self.population[i].checkCollide(self.population[j])
                    if collided:
                        dx, dy = self.population[i].getDxDy()
                        self.population[j].setDxDy(dx * -1, dy * -1)
                        #if there was a collision check if infection spread
                        if self.population[i].state == "susceptible":
                            if self.population[j].state == "infected":
                                tempTest = random.random()
                                if tempTest <= config["sim"]["infection_rate"]:
                                    self.population[i].state = "infected"
                                    self.population[i].color = "red"
                                    self.population[i].image = pygame.image.load(config["images"][self.population[i].color])
                                    self.population[i].image = pygame.transform.scale(self.population[i].image,
                                                                (self.population[i].width, self.population[i].height))
                                    self.population[i].infection_day = config["game"]["loop_count"] / config["game"]["fps"]
                                    self.num_infected += 1                            
                        
                        # doubled up on this since sometimes infected people collide with susceptible people and vice versa
                        if self.population[i].state == "infected":
                            if self.population[j].state == "susceptible":
                                tempTest = random.random()
                                if tempTest <= config["sim"]["infection_rate"]:
                                    self.population[j].state = "infected"
                                    self.population[j].color = "red"
                                    self.population[j].image = pygame.image.load(config["images"][self.population[j].color])
                                    self.population[j].image = pygame.transform.scale(self.population[j].image,
                                                                (self.population[j].width, self.population[j].height))
                                    self.population[j].infection_day = config["game"]["loop_count"] / config["game"]["fps"]                            
                                    self.num_infected += 1

            # checks the status of infected and quarantined people
            if self.population[i].state == "infected" or self.population[i].quarantine_check == True:
                self.status = self.population[i].check_status() # 1 = death, 2 = recovery, 3 = quarantined, 4 = released from quarantine
                if self.status == 1 and self.population[i].state is not "recovered":
                    self.population_count -= 1
                    self.num_infected -= 1
                    self.population[i].state = "dead"
                    if self.population[i].quarantine_check == True:
                        self.num_quarantined -= 1
                        self.population[i].quarantine_check = False
                    dead_list.append(i)
                elif self.status == 2 and self.population[i].state is not "dead":
                    self.population[i].state = "recovered"
                    self.population[i].color = "green"
                    self.population[i].image = pygame.image.load(config["images"][self.population[i].color])
                    self.population[i].image = pygame.transform.scale(self.population[i].image,
                                                (self.population[i].width, self.population[i].height))
                    self.num_infected -= 1
                elif self.status == 3:
                    self.population[i].quarantine_check = True
                    self.num_quarantined += 1
                elif self.status == 4:
                    self.num_quarantined -= 1
        #removes dead people from population[] in seperate loop to avoid out of bounds
        dead_list.sort()
        while len(dead_list) is not 0:
            self.population[dead_list[0]].image = pygame.transform.scale(self.population[dead_list[0]].image,(0,0))
            self.population.pop(dead_list[0])
            dead_list.pop(0)
            self.num_dead += 1
            for x in range(len(dead_list)):
                dead_list[x] -= 1

        self.sprite_group.draw(self.screen)

    def get_num_infected(self):
        return self.num_infected

    def get_population_count(self):
        return self.population_count

    def get_num_quarantined(self):
        return self.num_quarantined

    def get_num_dead(self):
        return self.num_dead

class FontHelper:
    def __init__(self,**kwargs):
        self.screen = kwargs.get("screen", None)

        if not isinstance(self.screen, pygame.Surface):
            print("Error, FontHelper needs a 'pygame.Surface' to be passed in when constructed! Aborting.") 
            sys.exit()
        
        self.font_size = kwargs.get("font_size", 20)
        self.font_path = kwargs.get("font_path", './fonts/Roboto-Black.ttf')

        self.color = kwargs.get("color", (255,255,255))
        self.background = kwargs.get("background", (0,0,0))
        self.x = kwargs.get("x", 0)
        self.y = kwargs.get("y", 0)

        self.font = pygame.font.Font(self.font_path, self.font_size)

        self.location = None


    def printLocation(self,location):
        '''
        location can be a list with: [top,bottom,left,right]
            top,bottom,left,right = print at respective location in the center (top center, left center, etc.)
            top,right = print at top right corner
            bottom,left = print at bottem left corner
        location can be a tuple with: (x,y)
            gives exact location to print
        '''
        if isinstance(location, list):
            self.location = location
            self.x = -1
            self.y = -1
        
        if isinstance(location, tuple):
            self.x = location[0]
            self.y = location[1]
            self.location = None

    def print(self,text):
        if isinstance(text, list):
            text = ', '.join(map(str, text))
        elif not isinstance(text,str):
            text = str(text)

        # text to print, antialias, foregroundcolor, backgroundcolor (30, 255, 30), (30, 30, 255)
        text = self.font.render(text, True, self.color, self.background) 
        textRect = text.get_rect()

        if self.x >= 0 and self.y >= 0:
            textRect.x = self.x
            textRect.y = self.y
        else:
            textRect.x = config["game"]["width"] // 2
            textRect.y = config["game"]["height"] // 2
            if "top" in self.location:
                textRect.top = 0
            if "bottom" in self.location:
                textRect.bottom = config["game"]["height"]
            if "left" in self.location:
                textRect.left = 0           
            if "right" in self.location:
                textRect.right = config["game"]["width"]

        self.screen.blit(text, textRect) 
        



#__________________________________________________________________________

if __name__ == '__main__':
    pygame.init()
    pygame.display.set_caption('Corona Virus') 

    # Set up the drawing window
    screen = pygame.display.set_mode(
        [config["game"]["width"], config["game"]["height"]])


    sim = Simulation(screen=screen,
        width=config["game"]["width"],
        height=config["game"]["height"],
        population_count=config["sim"]["population_count"],
        num_infected=config["sim"]["num_infected"])

    sim.populateSim()

    # main stats output
    stats = FontHelper(screen=screen, font_size=16)
    stats.printLocation((0,0))
    day = 0

    # helps keep game loop running at
    # specific frames per second
    clock = pygame.time.Clock()

    # Run until the user asks to quit
    running = True

    #___ GAME LOOP ____________________________________________________________
    while running:
        # Fill the background with blackish
        # Do not do this after you draw sprites!
        screen.fill((30, 30, 30))

        # Did the user click the window close button?
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            # handle MOUSEBUTTONUP
            if event.type == pygame.MOUSEBUTTONUP:
                pos = pygame.mouse.get_pos()
                sim.addPerson(coord=pos)

        #___CONTROL SIMULATION HERE_____________________________________________________________
        
        # drawing rectangles
        rect_width = 2
        #right
        pygame.draw.rect(screen,(255,0,0),(config["game"]["width"]//1.25,0,config["game"]["width"]//5-rect_width//2,config["game"]["height"]),rect_width)

        sim.simRun()
        
        # calculates each of stats at the end of each frame
        pop = sim.get_population_count()
        inf = sim.get_num_infected()
        day = config["game"]["loop_count"] / config["game"]["fps"]
        dead = sim.get_num_dead()
        num_quarantined = sim.get_num_quarantined()
        stat_string = f"Day: {int(day)}, Population size: {pop}, Number of infected: {inf}, Number of dead: {dead}, Number of quarantined: {num_quarantined}"
        stats.print(stat_string)

        #___END CONTROL SIMULATION_____________________________________________________________

        # This keeps game loop running at a constant FPS
        clock.tick(config["game"]["fps"])  # FPS = frames per second

        # Count number of loops game runs (careful, this number could get LARGE)
        config["game"]["loop_count"] += 1

        # Flip the display (refresh the screen)
        pygame.display.flip()

#___ END GAME LOOP ____________________________________________________________
# Done! Time to quit.
    pygame.quit()
