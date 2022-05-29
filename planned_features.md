# Planned Features (calculator features)
- Milradian calculation based on type of mortar used
    - Calculation done with linear approximation of in-game milradian conversion values given
    - Implement mortar as a child of coordinate class
- Graphical interface (Qt) with in-game maps
    - Coordinates can be plotted and saved on a map

# Planned Features (non-calculator features)
- Track total personal ticket count accumulated through actions
- Track commander asset timing (planes and artillery)
- Track enemy armor assets
- Track enemy truck timers (logi, MSP)
- Overlay exclusion zone on map
    - Layer-specific objective locations and exclusion zones marked
- Overlay cap zones on map (warning: time-consuming data gathering)
- Place markers on map

# Misc. Things to do
- Verify if relative height between mortar and target affects calculations
- Add list of useful admin commands
- Add list of tank spawn commands

# To-do
- fix error handling
- rework string parsing in coordinate.cpp
- handle a larger variety of inputs in main.cpp
- state errors more elegantly in main.cpp
- Complete class hierarchy:
    - DistToMils: table...
    - Coordinate: x, y, SubCoordinate
        - Mortar: type, DistToMils*
    - Asset: name
        - Timed Asset: time
            - Commander Assets
        - Ticket Asset: ticket cost, amount
            - Tank
            - AT Guns
            - Transport Vehicles
        - (Timed and Ticket)
            - Command Car
            - Logistics Truck
            - MSP
    - Map: name, file (image)
        - Layer: type, vector of pt. Coordinates, Factions:struct:(vehicle name, amount)