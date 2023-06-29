#include "../Header Files/JsonResponsePacketSerializer.h"

std::string makeBuffer(std::string text, int len)
{
    std::string result = "";

    for (int i = 0; i < len - text.length(); i++)
    {
        result += "0";
    }

    result += text;
    return result;
}

std::vector<unsigned char> numToBin(int num)
{
    std::vector<unsigned char> result;
    result.push_back((num >> 24) & 0xFF);
    result.push_back((num >> 18) & 0xFF);
    result.push_back((num >> 8) & 0xFF);
    result.push_back(num & 0xFF);
    return result;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(ErrorResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"message", response.message} };

    message.push_back(ERROR_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(LoginResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(LOGIN_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(SignupResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(SIGNUP_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(LogoutResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(LOGOUT_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(GetRoomsResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };
    js["Rooms"] = nlohmann::json::array();
    for (auto& val : response.rooms) {
        js["Rooms"].push_back(val.toJson());
    }

    message.push_back(LOGOUT_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(GetPlayersInRoomResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js;
    js["PlayersInRoom"] = nlohmann::json::array();
    for (auto& val : response.players) {
        js["PlayersInRoom"].push_back(val);
    }
    message.push_back(PLAYERSINROOM_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(JoinRoomResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(JOINROOM_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(CreateRoomResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status}, {"roomId", response.roomId} };

    message.push_back(CREATEROOM_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(getHighScoreResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };
    js["HighScores"] = nlohmann::json::array();
    for (auto& val : response.statistics) {
        js["HighScores"].push_back(val);
    }

    message.push_back(HIGHSCORE_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(getPersonalStatsResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };
    js["UserStatistics"] = nlohmann::json::array();
    for (auto& val : response.statistics) {
        js["UserStatistics"].push_back(val);
    }

    message.push_back(PERSONALSTATS_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}




std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(CloseRoomResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(CLOSEROOM_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}


std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(StartGameResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(STARTGAME_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(GetRoomStateResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} , {"hasGameBegun", response.hasGameBegun} };
    js["Players"] = nlohmann::json::array();
    for (auto& val : response.players) {
        js["Players"].push_back(val);
    }

    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(LeaveRoomResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(LEAVEROOM_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(LeaveGameResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(LEAVEGAME_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(GetGameResultsResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };
    js["Results"] = nlohmann::json::array();
    for (auto& val : response.results) {
        js["Results"].push_back(val.toJson());
    }

    message.push_back(GETGAMERESULTS_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(DrawCardFromDeckResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(DRAWCARD_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(PlaceCardResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(PLACECARD_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(CallLastCardInHandResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(CALLLASTCARD_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(getOngoingGameStateResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} , {"gameDirection", response.gameDirection} , {"currentPlayer", response.currentPlayer} , {"lastCardPlay", response.lastCardPlay}, {"isGameEnd", response.isGameEnd} };
    js["currentCards"] = nlohmann::json::array();
    for (auto& val : response.currentCards) {
        js["currentCards"].push_back(val);
    }

    js["CardsPerPlayer"] = nlohmann::json::array();
    for (auto& val : response.CardsPerPlayer) {
        js["CardsPerPlayer"].push_back("{\"" + val.first + "\":" + std::to_string(val.second) + "}");
    }

    message.push_back(GETONGOINGGAME_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}

std::vector<unsigned char> JsonResponsePacketSerializer::SerializeResponse(closeTakiResponse response)
{
    std::vector<unsigned char> message;
    nlohmann::json js = { {"status", response.status} };

    message.push_back(CLOSETAKI_CODE);
    for (char c : nlohmann::to_string(js))
    {
        message.push_back(c);
    }
    return message;
}
