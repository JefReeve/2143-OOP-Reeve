# Jeff Reeve's Basic epidemic simulation
###### The code uses python and pygame to simulate a disease's spread in a comunity.
###### Changing the numbers the config.json will allow control over most of the simulation.
## Config.json parameters:
#### "game" section's main variables are the width and height which change the game windows size
day = the amount of days that have passed, changing this will change the starting day
fps = frames per second, higher frames will make the simulation smoother but at the cost of computer resources
loop_count = amount of frames past(recomended not to change as it wont really make a difference exept to change the starting day)
#### "sim" section's parameters:
infection_rate = chance of the infection spreading from an infected to a susceptiple person, triggers once per collision

death_rate = chance of dying from the disease, triggers once on a random day within limits below

quarantine_rate = chance to get sent to quarantine, triggers once on a random day within limits below

population_count = starting number people, total population(includes infected)

num_infected = starting number of infected people

quarantine_days = how many days people spend in quarantine, releases after this amount of days regardless of condition

recover_lower_limit = least amount of days possible until recovery(picks a random day between this and recover_upper_limit)

recover_upper_limit = max amount of days possible until recovery(picks a random day between this and recover_lower_limit)

death_lower_limit = least amount of days possible until possible death(picks a random day between this and death_upper_limit)

death_upper_limit = max amount of days possible until possible death(picks a random day between this and death_lower_limit)

symptoms_lower_limit = least amount of days possible until possible quarantine(picks a random day between this and symptoms_upper_limit)

symptoms_upper_limit = max amount of days possible until possible quarantine(picks a random day between this and symptoms_lower_limit)

