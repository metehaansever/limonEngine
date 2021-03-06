//
// Created by engin on 6.06.2018.
//

#include "KillCowboyPlayer.h"
#include "CoinPickUpOnTrigger.h"
#include "MayanCoinPickup.h"
#include "MayanLever.h"
#include "DoorAnimationAction.h"
#include "WesternStoryStartupAction.h"
#include "WesternStoryAtGraveAction.h"
#include "WesternStoryAtSaloonAction.h"
#include "WesternStoryAtUndertakerAction.h"
#include "WesternStoryAtTrainAction.h"
#include "WesternStoryNewGameAction.h"

CoinPickUpOnTrigger::CoinPickUpOnTrigger(LimonAPI *limonAPI) : TriggerInterface(limonAPI) {}

std::vector<LimonAPI::ParameterRequest> CoinPickUpOnTrigger::getParameters() {
    std::vector<LimonAPI::ParameterRequest> parameters;
    LimonAPI::ParameterRequest pr;
    pr.valueType = LimonAPI::ParameterRequest::ValueTypes::LONG;
    pr.requestType = LimonAPI::ParameterRequest::RequestParameterTypes::GUI_TEXT;
    pr.description = "Counter GUI Element";
    parameters.push_back(pr);

    LimonAPI::ParameterRequest pr2;
    pr2.valueType = LimonAPI::ParameterRequest::ValueTypes::LONG;
    pr2.requestType = LimonAPI::ParameterRequest::RequestParameterTypes::MODEL;
    pr2.description = "Model to remove";
    parameters.push_back(pr2);

    LimonAPI::ParameterRequest pr3;
    pr3.valueType = LimonAPI::ParameterRequest::ValueTypes::LONG;
    pr3.requestType = LimonAPI::ParameterRequest::RequestParameterTypes::FREE_NUMBER;
    pr3.description = "Count to finish";
    parameters.push_back(pr3);

    return parameters;
}

bool CoinPickUpOnTrigger::run(std::vector<LimonAPI::ParameterRequest> parameters) {
    bool result;
    //FIXME there is no enum value for variable, there should be
    LimonAPI::ParameterRequest& coinPickupCount = limonAPI->getVariable("coinPickupCount");

    coinPickupCount.value.longValue++;
    if(coinPickupCount.value.longValue < parameters[2].value.longValue) {
        result = limonAPI->updateGuiText(parameters[0].value.longValue, std::to_string(coinPickupCount.value.longValue)) == 0;
    } else {
        result = limonAPI->removeGuiElement(parameters[0].value.longValue) == 0;
        result = limonAPI->addGuiText("./Data/Fonts/Helvetica-Normal.ttf", 64, "GameWinText", "Congratulations!", glm::vec3(50,255,50),glm::vec2(0.5f,0.5f), 0.0f) == 0 && result;
    }

    result = limonAPI->removeObject(parameters[1].value.longValue) == 0 && result;
    //play coin pickup sound
    limonAPI->playSound("./Data/Sounds/coinPickup.wav", glm::vec3(0, 0, 0), false, false);
    return result;
}

std::vector<LimonAPI::ParameterRequest> CoinPickUpOnTrigger::getResults() {
    return std::vector<LimonAPI::ParameterRequest>();//not feeding other triggers the result
}

void registerAsTrigger(std::map<std::string, TriggerInterface*(*)(LimonAPI*)>* triggerMap) {
    (*triggerMap)["CoinPickUpOnTrigger"] = &createT<CoinPickUpOnTrigger>;
    (*triggerMap)["MayanCoinPickup"] = &createT<MayanCoinPickup>;
    (*triggerMap)["MayanLever"] = &createT<MayanLever>;
    (*triggerMap)["DoorAnimationAction"] = &createT<DoorAnimationAction>;
    (*triggerMap)["KillCowboyPlayer"] = &createT<KillCowboyPlayer>;
    (*triggerMap)["WesternStoryNewGameAction"] = &createT<WesternStoryNewGameAction>;
    (*triggerMap)["WesternStoryStartup"] = &createT<WesternStoryStartupAction>;
    (*triggerMap)["WesternStoryAtGrave"] = &createT<WesternStoryAtGraveAction>;
    (*triggerMap)["WesternStoryAtUndertaker"] = &createT<WesternStoryAtUndertakerAction>;
    (*triggerMap)["WesternStoryAtSaloon"] = &createT<WesternStoryAtSaloonAction>;
    (*triggerMap)["WesternStoryAtTrain"] = &createT<WesternStoryAtTrainAction>;
}
