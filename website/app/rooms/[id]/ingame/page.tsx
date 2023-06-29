'use client'
import Image from 'next/image'
import { useGlobalState, setGlobalState } from '../../../globals';
import { useEffect, useState } from 'react';
import { sendMsg, getJsonResponse } from '../../../websocket';
import { useRouter } from 'next/navigation';

const getStatusCode = process.env.GETONGOINGGAME_CODE;
const succesCode = process.env.SUCCESS;
const placeCardCode = process.env.PLACECARD_CODE;
const drawCardCode = process.env.DRAWCARD_CODE;
const closeTakiCode = process.env.CLOSETAKI_CODE;
const leaveGameCode = process.env.LEAVEGAME_CODE;
let isTakiOpen = false;
let lastCardColor = '';
let isplayerLeave = false;
let chooseColor = 'n';

const Lastcard = ({lastCardName} : {lastCardName : string}) => 
{
    if(lastCardName.includes('st')) lastCardName = 'nst';
    return (
        <div>
            <Image
                src={`/images/${lastCardName}.png`}
                alt=''
                height={150}
                width={150}
                className='rounded-lg shadow-md'
            />
        </div>
    )
}

const Backcard = ({CardName} : {CardName : string}) => 
{
    return (
        <div>
            <Image
                src={`/images/${CardName}.png`}
                alt=''
                height={150}
                width={150}
                className='rounded-lg shadow-md'
                onClick={handleTakeCard}
            />
        </div>
    )
}



function handleTakeCard()
{
    if (chooseColor == 'n')
    {
        sendToServer(drawCardCode!.charAt(0), '').then((res) => 
        {
           
        })
        .catch((error) => 
        {
            console.error(error);
        });
    }
}

function handleCardClick(cardName : string)
{
    if (chooseColor == 'n')
    {
        if (cardName == 'ncc') chooseColor = 'c';
        else
        {
            if ( cardName == 'nst') cardName = `${lastCardColor}${cardName[1]}${cardName[2]}`;
            sendToServer(placeCardCode!.charAt(0), `"cardId": "${cardName}"`).then((res) => 
            {
                if(res.status == succesCode)
                {
                    if(cardName.includes('ct') || cardName.includes('st')) isTakiOpen = true;
                    
                }
                
            })
            .catch((error) => 
            {
                console.error(error);
            });
        }
    }


    
}

const Deck = ({cardsDeck} : {cardsDeck : any}) => 
{
    return (
        <div className='flex justify-center gap-3'>
            {cardsDeck && cardsDeck.map((cardName, index) => (
                <div key={index}>
                    <Image
                        src={`/images/${cardName}.png`}
                        alt={cardName}
                        height={150}
                        width={150}
                        className='rounded-lg shadow-md'
                        onClick={() => { handleCardClick(cardName) }}
                    />
                </div>
            ))}
        </div>
    );
}



const Players = ({ players, currPlayer }: { players: any; currPlayer: any }) => 
{
    const getPlayerData = (player: string) => 
    {
        const playerObject = JSON.parse(player.replace(/'/g, "\""));
        const playerName = Object.keys(playerObject)[0];
        const playerNumber = playerObject[playerName];
        return { playerName, playerNumber };
    };

    return (
    <div className="flex justify-center bg-white px-20 rounded-md shadow-md py-1">
        <div className="text-center text-lg flex justify-center gap-20">
        {players && players.map((player, index) => 
        {
            const { playerName, playerNumber } = getPlayerData(player);
            const classStyle = playerName == currPlayer ? 'font-bold text-xl text-blue-500' : '';

            return (
            <div key={index}>
                <p className={classStyle}>{playerName}</p>
                <p className={classStyle}>{playerNumber}</p>
            </div>
            );
        })}
        </div>
    </div>
    );
};
  
const Leavebutton = () => 
{
    return (
        <div className="justify-end mr-7 right-10 fixed">
        <button onClick={leaveGame} className="font-semibold border-red-500 text-red-500 border-2 px-3 py-1 rounded-sm hover:bg-red-500 transition-all duration-150 hover:text-white mt-4">
            Leave room
        </button>
        </div>
    );
};


function leaveGame()
{
    sendToServer(leaveGameCode!.charAt(0), '').then((res) => 
    {
        if(res.status == succesCode)
        {
            isplayerLeave = true;   

        }  
    })
    .catch((error) => 
    {
        console.error(error);
    });
}


const CloseTakiButton = () => 
{
    return (
        <div className="justify-end mr-7 right-10 fixed">
            <button onClick={closeTaki} className="font-semibold border-red-500 text-red-500 border-2 px-3 py-1 rounded-sm hover:bg-red-500 transition-all duration-150 hover:text-white mt-4">
                Close taki
            </button>
        </div>
    );
};

function closeTaki()
{
    sendToServer(closeTakiCode!.charAt(0), '').then((res) => 
    {
        if(res.status == succesCode)
        {
            isTakiOpen = false; 

        }    
    })
    .catch((error) => 
    {
        console.error(error);
    });
}


const ChooseColor = () => 
{
    const sendColor = (color : string) => 
    {
        sendToServer(placeCardCode!.charAt(0), `"cardId": "${color}cc"`).then((res) => 
        {
            console.log(res);
            if(res != '')
            {
                chooseColor = 'n';

            } 
        })
        .catch((error) => {
            console.error(error);
        });
    };
  
    return (
      <div className="flex flex-col justify-center items-center gap-2">
        <div className="flex gap-2">
          <div className="h-16 w-16 bg-blue-500" onClick={() => sendColor('b')}></div>
          <div className="h-16 w-16 bg-red-500" onClick={() => sendColor('r')}></div>
        </div>
        <div className="mt-2 flex gap-2">
          <div className="h-16 w-16 bg-green-500" onClick={() => sendColor('g')}></div>
          <div className="h-16 w-16 bg-yellow-300" onClick={() => sendColor('y')}></div>
        </div>
      </div>
    );
  };

export default function Page()
{
    const [playersList, setPlayers] = useState([]);
    const [currCards, setCurrCards] = useState([]);
    const [direction, setDir] = useState(true);
    const [lastCardPlayed, setLastCardPlayed] = useState('');
    const [currPlayer, setCurrPlayer] = useState('');
    const router = useRouter()
    

    useEffect(() => 
    {
        const resultsUrl = window.location.href.replace('ingame', 'results');  
        const interval = setInterval(() => 
        {
            if (isplayerLeave) router.push('/');

            sendToServer(getStatusCode!.charAt(0), '')
            .then((res) => {
              if (res) {
                console.log(res.isGameEnd)
                setPlayers(res.CardsPerPlayer);
                setCurrCards(res.currentCards);
                setDir(res.gameDirection);
                setLastCardPlayed(res.lastCardPlay);
                setCurrPlayer(res.currentPlayer);
                if (res.isGameEnd == true) router.push(resultsUrl);
                lastCardColor = res.lastCardPlay.charAt(0);
              }
              
            })
            .catch((error) => {
              console.error(error);
            });
        }, 1200);
    
        return () => {
          clearInterval(interval);
        };

    }, []);

    return (
        <main className="bg-slate-200 w-screen h-screen">
          <div className="flex mt-8 xl:ml-96 lg:ml-36 md:ml-44">
            <Image
                src={`/images/dir-${direction !== undefined ? direction.toString() : ''}.png`}
                alt={'dir-true'}
                height={10}
                width={60}
                className='xl:ml-96 lg:ml-36 md:ml-44 mr-10 rounded-lg h-16'
            />
            <Players players={playersList} currPlayer={currPlayer} />
            <Leavebutton />
          </div>
          <div className="flex pt-44 gap-20 justify-center">
            {chooseColor == 'c' && <ChooseColor />}
            <Lastcard lastCardName={lastCardPlayed} />
            <Backcard CardName='back' />
          </div>
          <div>
            {isTakiOpen && <CloseTakiButton />}
          </div>
          <div className="flex justify-center fixed bottom-20">
            <Deck cardsDeck={currCards} />
          </div>
        </main>
    );
}



async function sendToServer(code: string, msg : string)
{
    try 
    {
        const response = await sendMsg(code, msg);
        const jsnRes = getJsonResponse(response);

        if (jsnRes.status == succesCode)
        {
            return jsnRes;
        } 
        else 
        {
            return '';
        }
    } 
    catch (error) 
    {
        console.error(error);
        return false;
    }
}