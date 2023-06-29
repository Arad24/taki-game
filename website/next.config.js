/** @type {import('next').NextConfig} */
const nextConfig = 
{
    env: {
        ERROR_CODE: '0',
        LOGIN_CODE: '1',
        SIGNUP_CODE: '2',
        LOGOUT_CODE: '3',
        GETROOMS_CODE: '4',
        JOINROOM_CODE: '5',
        CREATEROOM_CODE: '6',
        PLAYERSINROOM_CODE: '7',
        HIGHSCORE_CODE: '8',
        PERSONALSTATS_CODE: '9',
        CLOSEROOM_CODE: 'A',
        STARTGAME_CODE: 'B',
        GETROOMSTATE_CODE: 'C',
        LEAVEROOM_CODE: 'D',
        LEAVEGAME_CODE: 'E',
        DRAWCARD_CODE: 'F',
        CALLLASTCARD_CODE: 'G',
        PLACECARD_CODE: 'H',
        GETGAMERESULTS_CODE: 'I',
        GETONGOINGGAME_CODE: 'J',
        CLOSETAKI_CODE: 'K',
        SUCCESS: '1',
      },
};
   
module.exports = nextConfig;

