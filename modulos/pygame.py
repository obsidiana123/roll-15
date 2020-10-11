# Simple pygame program

# Import and initialize the pygame library
def pygame():
    import pygame
    import psutil
    pygame.init()

    #cores

    BLACK = (0, 0, 0)
    WHITE = (255, 255, 255)
    BLUE = (0, 0, 255)
    GREEN = (0, 255, 0)
    RED = (255, 0, 0)

    # Set up the drawing window
    screen = pygame.display.set_mode([500, 500])

    # Run until the user asks to quit
    running = True
    while running:
        #print(psutil.cpu_percent())  # Em porcentagem, uso da CPU
        #print(psutil.virtual_memory()._asdict())

        # Did the user click the window close button?
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Fill the background with white
        screen.fill((255, 255, 255))




###################################################################
        #pygame.draw.circle(screen, (BLUE), (250, 250), 75)# tred
        #pygame.draw.circle(screen, (BLUE), (250, 250), 75)  # tred
        #pygame.draw.circle(screen, (BLUE), (50, 250), 75)# visao
        #pygame.draw.circle(screen, (BLUE), (250, 50), 75)# audio
        #pygame.draw.circle(screen, (BLUE), (250, 250), 75)# comun
        #pygame.draw.circle(screen, (BLUE), (250, 250), 75)# pygame

        #pygame.draw.line(screen, RED, [10, 100], [630, 100], 5)

        pygame.draw.rect(screen, BLUE, [150, 50, 70, 70])# tred
        pygame.draw.rect(screen, BLUE, [25, 250, 70, 70])# visao
        pygame.draw.rect(screen, BLUE, [130, 250, 70, 70])# audio
        pygame.draw.rect(screen, BLUE, [250, 250, 70, 70])# comun
        pygame.draw.rect(screen, BLUE, [350, 250, 70, 70])# pygame

#######################################################################


        # Flip the display
        pygame.display.flip()

    # Done! Time to quit.
    pygame.quit()
