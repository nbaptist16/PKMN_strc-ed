#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H
#include "View.h"
#include "Model.h"
#include "Point2D.h"

void DoMoveCommand(Model& model, int pokemon_id, Point2D p1);
void DoMoveToCenterCommand(Model& model, int pokemon_id, int center_id);
void DoMoveToGymCommand(Model& model, int pokemon_id, int gym_id);
void DoStopCommand(Model& model, int pokemon_id);
void DoGoCommand(Model& model, View& view);
void DoRunCommand(Model& model, View& view);
void DoTrainInGymCommand(Model& model, int pokemon_id, unsigned int training_units);
void DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int stamina_points);

//added battle and move to arena commands
void DoBattleCommand(Model& model, int pokemon_id, int rival_id);
void DoMoveToArenaCommand(Model& model, int pokemon_id, int arena_id);
#endif
