#include "../Header Files/JsonRequestPacketDeserializer.h"

int buffToInteger(std::vector<unsigned char> buffer)
{
    int result = (int)(buffer[1] << 24 | buffer[2] << 16 | buffer[3] << 8 | buffer[4]);
    return result;
}

nlohmann::json getJSON(std::vector<unsigned char> buffer)
{
    std::string data(buffer.begin() + STARTDATA, buffer.end());

    return nlohmann::json::parse(data);
}


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
    LoginRequest result;

    nlohmann::json js = getJSON(buffer);
    result.password = js["password"];
    result.username = js["username"];
    return result;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
    SignupRequest result;

    nlohmann::json js = getJSON(buffer);
    result.password = js["password"];
    result.username = js["username"];
    result.email = js["email"];
    return result;
}



GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<unsigned char> buffer)
{
    GetPlayersInRoomRequest result = GetPlayersInRoomRequest();

    nlohmann::json js = getJSON(buffer);
    result.roomId = js["roomId"];
    return result;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
    JoinRoomRequest result = JoinRoomRequest();

    nlohmann::json js = getJSON(buffer);
    result.roomId = js["roomId"];
    return result;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
    CreateRoomRequest result;

    nlohmann::json js = getJSON(buffer);
    result.roomName = js["roomName"];
    result.maxUsers = js["maxUsers"];
    result.answerTimeout = js["answerTimeout"];
    return result;
}


CloseRoomRequest JsonRequestPacketDeserializer::deserializeCloseRoomRequest(std::vector<unsigned char> buffer)
{
    CloseRoomRequest result;
    nlohmann::json js = getJSON(buffer);

    result.status = js["status"];

    return result;
}

StartGameRequest JsonRequestPacketDeserializer::deserializeStartGameRequest(std::vector<unsigned char> buffer)
{
    StartGameRequest result;
    nlohmann::json js = getJSON(buffer);

    result.status = js["status"];

    return result;
}

GetRoomStateRequest JsonRequestPacketDeserializer::deserializeGetRoomStateRequest(std::vector<unsigned char> buffer)
{
    GetRoomStateRequest result;
    nlohmann::json js = getJSON(buffer);

    result.status = js["status"];
    result.answerTimeout = js["answerTimeout"];
    result.hasGameBegun = js["hasGameBegun"];
    result.players = js["players"];

    return result;
}

LeaveRoomRequest JsonRequestPacketDeserializer::deserializeLeaveRoomRequest(std::vector<unsigned char> buffer)
{
    LeaveRoomRequest result;
    nlohmann::json js = getJSON(buffer);

    result.status = js["status"];

    return result;
}




PlaceCardRequest JsonRequestPacketDeserializer::deserializePlaceCardRequest(std::vector<unsigned char> buffer)
{
    PlaceCardRequest result;
    nlohmann::json js = getJSON(buffer);

    result.cardId = js["cardId"];

    return result;
}
