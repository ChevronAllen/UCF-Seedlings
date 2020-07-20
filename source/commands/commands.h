/**
 *  @file commands.h
 *  @brief includes for CommandObject and its children
 */
#include "../commands/commandObject.hpp"
#include "../commands/selectCommand.hpp"
#include "../commands/ifCommand.hpp"
#include "../commands/elseCommand.hpp"
#include "../commands/whileCommand.hpp"
#include "../commands/endCommand.hpp"
#include "../commands/labelCommand.hpp"
#include "../commands/gotoCommand.hpp"
#include "../commands/deleteCommand.hpp"
#include "../commands/userCommand.hpp"
#include "../commands/emptyCommand.hpp"
#include "../commands/moveCommand.hpp"
#include "../commands/colorCommand.hpp"
#include "../commands/scaleCommand.hpp"
#include "../commands/rotateCommand.hpp"
#include "../commands/createCommand.hpp"
#include "../commands/positionCommand.hpp"
#include "../commands/angleCommand.hpp"
#include "../commands/deleteCommand.hpp"


/*
---- Control Statements
SELECT [obj_name] -> 
IF [bool_expression] 
    -> if [bool_expression] then
LOOP [int] 
    -> while [int] > 0 do
WHILE [bool_expression] -> while [bool_expression] do
END    -> end
LABEL [label_name]
GOTO [label_name]

---- Object Manipulation
LEFT, RIGHT, UP, DOWN [double]
    -> apifunction([double],[double])
RED, BLUE, GREEN, YELLOW, ORANGE, PURPLE
    -> apifunction([color])
SCALE [x] [y], SCALE_X [x], SCALE_Y [y]
    -> apifuntion([x],[y])
ROTATE [double] 
    -> apifunction([double] , false) 
ANGLE [double] 
    -> apifunction([double] , true) 

CIRCLE [obj_name] 
RECTANGLE [obj_name]
TRIANGLE [obj_name]
PADDLE, etc [obj_name]
    -> apifunction([obj_name]) 

DELETE [obj_name]

---- Variables
VAR [var_name] [value] 
    -> [var_name] = [value]
DELETE_VAR [var_name]
    -> [var_name] = nil

---- OTHER
GET_X, GET_Y [var_name] 
GET_ANGLE [var_name]
* GET_SPEED_X, GET_SPEED_Y [var_name]

====== EXAMPLE - Paddle Game
SELECT ball
GET_Y by
SELECT paddle
GET_Y py
IF py > by
UP 1
END
IF py < by
DOWN 1
END
*/